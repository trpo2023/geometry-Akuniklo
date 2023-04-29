int check_word(char *a, char *b, int *error);
int find_close_bracket(char *a, int *length);
int check_first_num(char *a, int *ind_open_bracket, int *error);
int check_second_num(char *a, int *ind_first_num_elm, int *error);
int check_third_num(
    char *a, int *ind_second_num_elm, int *error, int *ind_close_bracket);
int check_close_bracket(
    char *a, int *ind_last_num_elm, int *length, int *error);
int check_unexpected_token(
    char *a, int *ind_close_bracket, int *length, int *error);
void token(
    char *a,
    float *x,
    float *y,
    float *rad,
    float *array_x,
    float *array_y,
    float *array_rad,
    int index);
void intersects(float *array_x, float *array_y, float *array_rad, int index);