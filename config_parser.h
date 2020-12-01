#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "num_utils.h"
#include "string_utils.h"
#include "debug.h"
#include "output.h"

struct mapped_key{
    int KeyCode;
    int MappedKeyCode;
};

void parse_config(char * Data,
                  int * TurboKeysArray,
                  int * NumberOfTurboKeys,
                  mapped_key * MappedKeys,
                  int * NumberOfMappedKeys
                  );

#endif //CONFIG_PARSER_H
