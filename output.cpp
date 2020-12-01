#include "output.h"

static HANDLE ConsoleHandle = INVALID_HANDLE_VALUE;

void initialize_std_output(){
    ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void std_output(const char * String){
    if(ConsoleHandle != INVALID_HANDLE_VALUE){
        WriteConsole(ConsoleHandle,
                     (const VOID*)String,
                     string_length(String),
                     NULL,
                     NULL
                     );
    }
}