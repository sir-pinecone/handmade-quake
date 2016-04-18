#include "quakedef.h"


uint32 com_numArgs = 0;
const char *com_largv[MAX_NUM_ARGS + 2];

void COM_ParseCommandLine(char *commandLine) {
  com_largv[0] = '\0';
  com_numArgs = 1;

  while (*commandLine && com_numArgs < MAX_NUM_ARGS + 1) {
    while (*commandLine && ((*commandLine <= 32) || (*commandLine > 126)))
      commandLine++;

    if (*commandLine) {
      // Store pointer to the start of the arg
      com_largv[com_numArgs++] = commandLine;

      // Move to the end of the arg 
      while (*commandLine && (*commandLine > 32) && (*commandLine < 127))
        commandLine++;

      if (*commandLine) {
        // Terminate the space in order to complete the single cmd string
        *commandLine = '\0';
        commandLine++;
      }
    }
  }

  // Make it safe to always get the value that comes after the last arg   
  com_largv[com_numArgs] = '\0';
}

int32 COM_IndexOfArg(const char *arg) {
  for (uint32 i = 1; i < com_numArgs; i++) {
    if (!Q_strcmp(arg, com_largv[i]))
      return i;
  }
  // We zeroed the value at index 0 so this is safe
  return 0;
}