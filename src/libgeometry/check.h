#ifndef CHECK_H
#define CHECK_H

int check_circle_word(char* a, char* b, int* error);

int search_close_index(char* a, int* length);

int check_first_number(char* a, int* open_index, int* error);

int check_second_number(char* a, int* first_index, int* error);

int check_third_number(
        char* a, int* second_index, int* close_index, int* error);

int get_close_index(char* a, int* third_index, int* length, int* error);

int check_unexpected_tokens(char* a, int* close_index, int* length, int* error);

void parse_circle_expression(char* a, float* x, float* y, float* rad);

void find_intersections(float* x_arr, float* y_arr, float* rad_arr, int amount);

#endif /* CHECK_H */
