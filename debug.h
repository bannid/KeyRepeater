#ifndef DEBUG_H
#define DEBUG_H

#if defined(DEBUG)
#define Assert(expression) if(!(expression))*(int*)0 = 0
#endif

#endif