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

#define MAX_NUM_ARGVS 50

global_variable int32 numArgs = 0; 
global_variable const char *largv[MAX_NUM_ARGVS + 1];

int32 COM_IndexOfArg(char *arg) {
  for (int32 i = 1; i < numArgs; i++) {
    if (!strcmp(arg, largv[i]))
      return i;
  }
  // We zeroed the value at index 0 so this is safe
  return 0; 
}

int32 CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int32 ShowCode) {
  largv[0] = '\0';
  numArgs++;

  while (*CommandLine && numArgs < MAX_NUM_ARGVS + 1) {
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

  return 0;
}