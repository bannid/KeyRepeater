#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "num_utils.h"
#include "string_utils.h"
#include "debug.h"

void parse_config(char * Data,
                  int * TurboKeysArray,
                  int * NumberOfTurboKeys);

#endif //CONFIG_PARSER_H
