#include <stdint.h>
#include <windows.h>


#define internal static
#define global_variable static

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


#define MAX_NUM_ARGS 50

global_variable int32 numArgs = 0; 
// Pad by 2 so that we can zero the first element and last element at largv[numArgs]
global_variable const char *largv[MAX_NUM_ARGS + 2]; 

int32 Q_strcmp(const char *s1, const char *s2) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;
  while (*p1 == *p2) {
    if (!*p1) {
      return 0;
    }
    p1++;
    p2++;
  }
  return ((*p1 < *p2) ? -1 : 1);
}

/* Custom string to number coercion. Supports signed decimal or hex values. */
int32 Q_atoi(const char *str) {
  int32 sign = 1;
  int32 val = 0;
  char c;

  if (!str) {
    return 0;
  }
  
  if (*str == '-') {
    sign = -1;
    str++;
  }

  // hex
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    str += 2;
    while (1) {
      c = *str++;
      if (c >= '0' && c <= '9') {
        val = val * 16 + (c - '0');
      }
      else if (c >= 'a' && c <= 'f') {
        val = val * 16 + c - 'a' + 10;
      }
      else if (c >= 'A' && c <= 'F') {
        val = val * 16 + c - 'A' + 10;
      }
      else {
        return sign * val;
      }
    }
  }
  
  // decimal
  while (1) {
    c = *str++;
    if (c < '0' || c > '9') {
      return sign * val;
    }
    val = val * 10 + (c - '0'); // '0' is 48 so c - '0' gives us the numerical version of the ascii number.
  }
}

int32 COM_IndexOfArg(const char *arg) {
  for (int32 i = 1; i < numArgs; i++) {
    if (!Q_strcmp(arg, largv[i]))
      return i;
  }
  // We zeroed the value at index 0 so this is safe
  return 0; 
}

int32 CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int32 ShowCode) {
  largv[0] = '\0';
  numArgs++;

  while (*CommandLine && numArgs < MAX_NUM_ARGS + 1) {
    while (*CommandLine && ((*CommandLine <= 32) || (*CommandLine > 126)))
      CommandLine++;

    if (*CommandLine) {
      // Store pointer to the start of the arg
      largv[numArgs++] = CommandLine;

      // Move to the end of the arg 
      while (*CommandLine && (*CommandLine > 32) && (*CommandLine < 127))
        CommandLine++;

      if (*CommandLine) {
        // Terminate the space in order to complete the single cmd string
        *CommandLine = '\0';
        CommandLine++;
      }
    }
  }

  // Make it safe to always get the value that comes after the last arg   
  largv[numArgs] = '\0';                                                                                                                            

  int a = Q_atoi("123") == 123;
  int b = Q_atoi("-1453") == -1453;
  int c = Q_atoi("0xF") == 15;

  int alpha = Q_atoi(largv[COM_IndexOfArg("-setAlpha") + 1]);
  int fov = Q_atoi(largv[COM_IndexOfArg("-fov") + 1]);

  return 0;
}