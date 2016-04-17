#include "winquake.h"
#include "quakedef.h"


int32 CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int32 ShowCode) {
  COM_ParseCommandLine(CommandLine);

  int a = Q_atoi("123") == 123;
  int b = Q_atoi("-1453") == -1453;
  int c = Q_atoi("0xF") == 15;

  int alpha = Q_atoi(com_largv[COM_IndexOfArg("-setAlpha") + 1]);
  int fov = Q_atoi(com_largv[COM_IndexOfArg("-fov") + 1]);

  return 0;
}