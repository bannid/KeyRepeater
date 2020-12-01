#include "config_parser.h"
#define MAX_LINE_LENGTH 100

void parse_config(char * Data,
                  int * TurboKeysArray,
                  int * NumberOfTurboKeys,
                  mapped_key * MappedKeys,
                  int * NumberOfMappedKeys
                  ){
    char LineBuffer[MAX_LINE_LENGTH + 1];
    for(int i = 0; i<2; i++){
        eat_all_white_space(&Data);
        read_next_line((const char*)Data,
                       LineBuffer,
                       MAX_LINE_LENGTH);
        if(compare_strings(LineBuffer,"turboList{")){
            DEBUG_OUTPUT("Parsing turbo list");
            for(;;){
                forward_string_pointer_to_next_line(&Data);
                eat_all_white_space(&Data);
                read_next_line((const char*)Data,
                               LineBuffer,
                               MAX_LINE_LENGTH);
                if(!compare_strings(LineBuffer,"}")){
                    int KeyCode = char_hex_convert_to_decimal(LineBuffer);
                    TurboKeysArray[*NumberOfTurboKeys] = KeyCode;
                    *NumberOfTurboKeys += 1;
                }
                else{
                    forward_string_pointer_to_next_line(&Data);
                    break;
                }
                
                // TODO(NAME): Check if the config file is not formatted 
                //correctly and handle it.
            }
            
        }
        else if(compare_strings(LineBuffer,"keyMappings{")){
            DEBUG_OUTPUT("Parsing key mappings");
            for(;;){
                char * LineBufferPointer = LineBuffer;
                forward_string_pointer_to_next_line(&Data);
                eat_all_white_space(&Data);
                read_next_line((const char*)Data,
                               LineBufferPointer,
                               MAX_LINE_LENGTH);
                if(!compare_strings(LineBufferPointer,"}")){
                    char SplittedString[MAX_LINE_LENGTH/2];
                    split_string(LineBufferPointer,
                                 SplittedString,
                                 MAX_LINE_LENGTH/2,
                                 ':');
                    int KeyCode = char_hex_convert_to_decimal(SplittedString);
                    forward_string_pointer_upto(&LineBufferPointer,
                                                ':');
                    int MappedKeyCode = char_hex_convert_to_decimal(LineBufferPointer);
                    MappedKeys[*NumberOfMappedKeys].KeyCode = KeyCode;
                    MappedKeys[*NumberOfMappedKeys].MappedKeyCode = MappedKeyCode;
                    *NumberOfMappedKeys+=1;
                    
                }
                else{
                    forward_string_pointer_to_next_line(&Data);
                    break;
                }
                
                // TODO(NAME): Check if the config file is not formatted 
                //correctly and handle it.
            }
        }
    }
}