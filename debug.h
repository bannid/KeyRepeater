#ifndef DEBUG_H
#define DEBUG_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if defined(DEBUG)
#define Assert(expression) if(!(expression))*(int*)0 = 0
#define DEBUG_OUTPUT(string) std_output(string); std_output("\n");
#endif

#if !defined(DEBUG)
#define Assert(expression) 
#define DEBUG_OUTPUT(string)
#endif

#endif