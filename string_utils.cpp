#include "string_utils.h"

void eat_all_white_space(char ** Ptr){
    while(**Ptr == '\t' ||
          **Ptr == '\r' ||
          **Ptr == '\n' ||
          **Ptr == ' '){
        *Ptr+=1;
    }
}

bool string_contains(const char * String,
                     const char * Word){
    int WordShifted = 0;
    while(*String != '\0'){
        if(*String == *Word){
            Word++;
            WordShifted++;
            if(*Word == '\0'){
                return true;
            }
        }
        else{
            Word -= WordShifted;
        }
        String++;
    }
    return(false);
}

bool line_starts_with(const char * Line, 
                      const char * Word){
    
    while(*Word != '\0'){
        if(*Line == '\0'){
            return false;
        }
        if(*Word++ != *Line++){
            return false;
        }
    }
    return(true);
}

void read_next_line(const char * Data,
                    char * Output,
                    const int BufferLength){
    int Size = 0;
    while(*Data != '\n' && 
          *Data != '\r'){
        if(*Data != '\t' &&
           *Data != ' '){
            *Output++ = *Data++;
            Size++;
            Assert(Size < BufferLength);
        }
        else{
            Data++;
        }
    }
    *Output = '\0';
}

int string_length(const char * String){
    int Length = 0;
    while(*String != '\0'){
        String++;
        Length++;
    }
    return(Length);
}


bool compare_strings(const char * StringFirst,
                     const char * StringSecond){
    if(string_length(StringFirst) != string_length(StringSecond)){
        return false;
    }
    while(*StringFirst != '\0'){
        if(*StringFirst++ != *StringSecond++){
            return false;
        }
    }
    return true;
}

void split_string(const char * String,
                  char * Output,
                  int BufferSize,
                  char Token){
    int Size = 0;
    while(*String != Token){
        *Output++ = *String++;
        Size++;
        Assert(Size < BufferSize);
    }
    *Output = '\0';
}

void forward_string_pointer_upto(char ** Ptr,
                                 char Token){
    bool NotFound = false;
    char * Backup = *Ptr;
    while(**Ptr != Token){
        *Ptr += 1;
        if(**Ptr == '\0'){
            //If the token is not found until the end of the string,
            //then we do not forward the string anywhere.
            NotFound = true;
            *Ptr = Backup;
            break;
        }
    }
    if(!NotFound){
        //Skip the token as well.
        *Ptr += 1;
    }
}

void forward_string_pointer_to_next_line(char **Ptr){
    forward_string_pointer_upto(Ptr,
                                '\n');
}