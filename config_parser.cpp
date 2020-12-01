#include "config_parser.h"
#define MAX_LINE_LENGTH 100

void parse_config(char * Data,
                  int * TurboKeysArray,
                  int * NumberOfTurboKeys){
    
    eat_all_white_space(&Data);
    char LineBuffer[MAX_LINE_LENGTH + 1];
    read_next_line((const char*)Data,
                   LineBuffer,
                   MAX_LINE_LENGTH);
    if(compare_strings(LineBuffer,"turboList{")){
        DEBUG_OUTPUT("Parsing turbo list");
        //Goto the next line
        forward_string_pointer_upto(&Data,
                                    '\n');
        eat_all_white_space(&Data);
        read_next_line((const char*)Data,
                       LineBuffer,
                       MAX_LINE_LENGTH);
        if(!compare_strings(LineBuffer,"}")){
            int KeyCode = char_hex_convert_to_decimal(LineBuffer);
            TurboKeysArray[*NumberOfTurboKeys++] = KeyCode;
        }
        
    }
    else if(compare_strings(LineBuffer,"keyMapping{")){
        DEBUG_OUTPUT("Parsing key mappings");
    }
}