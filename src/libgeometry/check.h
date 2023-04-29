void check_word(char *a, char *b, int *error, int *ind_open_bracket);
void find_close_bracket(char *a, int *length, int *ind_close_bracket);
void check_first_num(
    char *a, int *ind_open_bracket, int *ind_first_num_elm, int *error);
void check_second_num(
    char *a, int *ind_first_num_elm, int *ind_second_num_elm, int *error);
void check_third_num(
    char *a,
    int *ind_second_num_elm,
    int *ind_last_num_elm,
    int *error,
    int *ind_close_bracket);
void check_close_bracket(
    char *a,
    int *ind_last_num_elm,
    int *length,
    int *ind_close_bracket,
    int *error);
void check_unexpected_token(
    char *a, int *ind_close_bracket, int *length, int *error);