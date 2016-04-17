#pragma once

#define MAX_NUM_ARGS 50

extern uint32 com_numArgs;
// Pad by 2 so that we can zero the first element and last element at com_largv[numArgs]
extern const char *com_largv[MAX_NUM_ARGS + 2];

void COM_ParseCommandLine(char *commandLine);
int32 COM_IndexOfArg(const char *arg);