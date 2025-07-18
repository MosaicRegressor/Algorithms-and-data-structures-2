/*
longest common subsequence problem

find lenght(the optimum) of the longest common subsequence between two strings
then find one of the substrings with that length, between the optimum

a subsequence can be contiguous but doesn't have to be, it just has to be a sequence! you can't choose characters at random order
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// NB there must be a nullbyte terminator at the end of the string!
void printCString(char* Cstring){
    for (int i = 0; Cstring[i] != '\0'; i++){
        printf("%c", Cstring[i]);
    }
    printf("\n");
}

// NB there must be a nullbyte terminator at the end of the string!
int CString_len(char* Cstring){

    int string_length = 0;

    for(char* chr = Cstring; *chr != '\0'; chr++) {
        string_length++;
    }

    return string_length;
}

// TODO
// exponentital time!!! it recomputes already certain known common subsequences
// FIXME it doesn't manager to find all the optimum values, it just takes the first part of a string
// int lcs_length_bruteforce(char* X, char* Y){
//     int tmp_x = 0;
//     int i = 0;
//     int lcs_len = 0;
//     int tmp_y = 0;
//     int y = 0;

//     int Y_len = CString_len(Y);
//     int X_len = CString_len(X);
//     for(int y = 0; y < Y_len; y++) {
//         tmp_x= 0;
//         for(tmp_y = y; tmp_y < Y_len; tmp_y++){
//             i = tmp_x;
//             while(X[i] != Y[tmp_y] || X[i] == '\0') {
//                 i++;
//             }
//             if(X[i] == Y[tmp_y]){
//                 tmp_x = i;
//                 lcs_len++;
//             }
//             tmp_y++;
//         }
//         y++;
//     }
//     return lcs_len;
// }


/*
allocate on the heap a table of size n x m and init it(set default behavior).

input: number of rows and columns
output: ptr to the table allocated in the heap

the user at runtime may input very big strings, let's allocate the caching tables in the heap.
a table is an array of pointers, to arrays of ints.
*/
int** alloc_table(int n_rows,int n_cols) {
    int** tbl = malloc(sizeof(int*) * n_cols);  // TODO optimize! memory fragmentation!

    // init the empty table, set defined behavior
    for(int col = 0; col < n_cols; col++) {
        tbl[col] = NULL;
    }

    // alloc the columns with the cell rows
    for(int col = 0; col < n_cols; col++) {
        tbl[col] = malloc(sizeof(int) * n_rows);
    }

    // set each of the columns row cells to defined behavior
    for(int col = 0; col < n_cols; col++) {     // TODO slow!, is it that necessary?
        for(int row = 0; row < n_rows; row++) {
            tbl[col][row] = 0;
        }
    }

    return tbl;
}

/*
deallocate the table
*/
void dealloc_table(int* tbl[], int n_cols) {
    // deallocate table content
    for(int col = 0; col < n_cols; col++) { // iterate through the array that holds the columns, and deallocate each of them
        free(tbl[col]);
    }

    // deallocate table
    free(tbl);
}

void print_tbl(int* tbl[], int n_rows, int n_cols) {
    for(int row = 0; row < n_rows; row++){  // iterate through columns
        for(int col = 0; col < n_cols; col++) { // iterate through rows
            printf("%d", tbl[col][row]);
        }
        printf("\n");
    }
}

/*
computes the optimal solutions for the lcs problem given 2 strings as input. 

input: strings where to find the lcs
output: diplayed the length and the optimal solution

this problem is solved "fast" due to the implementation of dynamic programming, which uses the optimal substructure of the
problem to chache the subproblems.

this dynamic algo uses 2 tables to do memoization(caching):
- cache_tbl_get_length_sol, it tracks the length of the optimal solution
- cache_tbl_get_sol, it pinpoints the exact solution
*/
int lcs(char* str_Y, char* str_X){  // Y will be placed as columns, X as rows
    int len_y_cols = CString_len(str_Y); // n, columns
    int len_x_rows = CString_len(str_X); // m, rows

    int** cache_tbl_get_length_sol = alloc_table(len_x_rows, len_y_cols);
    int** cache_tbl_get_sol = alloc_table(len_x_rows, len_y_cols);

    puts("Length cache table:");
    print_tbl(cache_tbl_get_length_sol, len_x_rows, len_y_cols);
    puts("");
    puts("build opt. sol. cache table:");
    print_tbl(cache_tbl_get_sol, len_x_rows, len_y_cols);




    dealloc_table(cache_tbl_get_sol, len_y_cols);
    dealloc_table(cache_tbl_get_length_sol, len_y_cols);

    return 0;
}


int main(int argc, char* argv[argc + 1]) {
    if (argc > 2) { // nb, in argc also the file name is included!
        // THE STRING X IS THE ROWS, THE STRING Y IS THE COLUMNS
        char* Y = argv[2];
        char* X = argv[1];

        puts("Input:");
        printf("Y(columns): "); printCString(Y);
        printf("X(rows): "); printCString(X);

        lcs(Y, X);
    }
    else {
        puts("Not enough args! Gimme 2 strings!");
    }

    return 0;
}