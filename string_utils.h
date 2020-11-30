#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include "debug.h"

void eat_all_white_space(char ** Ptr);
bool string_contains(const char * String, const char * Word);
bool line_starts_with(const char * Line, const char * Word);
void read_next_line(const char * Data, char * Output, const int BufferLength);
int string_length(const char * String);
void split_string(const char * String,
                  char * Output,
                  int BufferSize,
                  char Token);
void forward_string_pointer_upto(char ** Ptr,
                                 char Token);
#endif