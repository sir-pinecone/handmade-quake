#include <windows.h>

// CHALLENGE: write my own version of the strcmp function.

#define MAX_NUM_ARGVS 50

int numArgs = 0; 
const char *largv[MAX_NUM_ARGVS];

int COM_IndexOfArg(char *arg) {
  for (int i = 1; i < numArgs; i++) {
    if (!strcmp(arg, largv[i]))
      return i;
  }
  // We zeroed the value at index 0 so this is safe
  return 0; 
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode) {
  largv[0] = '\0';
  numArgs++;

  while (*CommandLine && numArgs < MAX_NUM_ARGVS) {
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

  if (numArgs < MAX_NUM_ARGVS) {
    // Explicitly clear the garbage from the first unused command line slot 
    largv[numArgs] = '\0';
  }

  return 0;
}