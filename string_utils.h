#ifndef STRING_UTILS_H
#define STRING_UTILS_H

void eat_all_white_space(char ** Ptr);
bool contains(const char * String, const char * Word);
bool line_starts_with(const char * Line, const char * Word);
void read_next_line(const char * Data, char * Output, const int MaxOutputSize);
#endif