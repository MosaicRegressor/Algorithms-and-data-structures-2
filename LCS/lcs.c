/*
longest common subsequence problem

find lenght(the optimum) of the longest common subsequence between two strings
then find one of the substrings with that length, between the optimum

a subsequence can be contiguous but doesn't have to be, it just has to be a sequence! you can't choose characters at random order
*/

#include <stdio.h>
#include <stdlib.h>
#include "helper_lib.h"

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
computes the optimal solutions for the lcs problem given 2 strings as input. 

input: strings where to find the lcs
output: diplayed the length and the optimal solution

this problem is solved "fast" due to the implementation of dynamic programming, which uses the optimal substructure of the
problem to chache the subproblems.

this dynamic algo uses 2 tables to do memoization(caching):
- cache_tbl_get_length_sol, it tracks the length of the optimal solution
    - it contains the lenghts of the optimal subproblems
- cache_tbl_get_sol, it pinpoints the exact solution
    - it contains an encoding: if in that cell a diagonal movement was done, write 3, ...

just fill the table with every possible combination, then visit it.
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

    // fill the tables

    // zero the first row
    for (int col = 0; col < len_y_cols; col++) {
        cache_tbl_get_length_sol[col][0] = 0;
    }
    // zero the first column
    for (int row = 0; row < len_x_rows; row++){
        cache_tbl_get_length_sol[0][row] = 0;
    }

    // let's implement the optimal substructure
    /*
    this is what slows down the most the algorithm, it's beacuse of nested for loops.
    the time complexity is theta(number_of_columns * number_of_rows), polinomial(not exponential!), approx. n^2
    the space complexity is n^2 too.
    */
    for(int r = 1; r < len_x_rows; r++) { // iterate through rows, i
        for(int c = 1; c < len_y_cols; c++) {     // iterate though columns, j
            // case1, Xi and Yj are equal: diagonal movement, sum 1 to the diagonal value and write to the cell
            if(str_X[r] == str_Y[c]) {
                cache_tbl_get_length_sol[c][r] = cache_tbl_get_length_sol[c - 1][r - 1] + 1;
                cache_tbl_get_sol[c][r] = 3;
            }
            else{
                cache_tbl_get_length_sol[c][r] = max(
                                                    cache_tbl_get_length_sol[c - 1][r],
                                                    cache_tbl_get_length_sol[c][r - 1]
                                                    );
                
                /* // FIXME implement retrieval of optimal solution

                // TODO implement max_position
                cache_tbl_get_sol[c][r] = max_position(
                                            cache_tbl_get_length_sol[c - 1][r],
                                            cache_tbl_get_length_sol[c][r - 1]
                                            );
                */

            }
        }
    }

    int lcs_len = cache_tbl_get_length_sol[len_y_cols - 1][len_x_rows - 1];
    // TODO build the lcs and return it in a struct with lcs_len!

    dealloc_table(cache_tbl_get_sol, len_y_cols);
    dealloc_table(cache_tbl_get_length_sol, len_y_cols);

    return lcs_len;
}


int main(int argc, char* argv[argc + 1]) {
    if (argc > 2) { // nb, in argc also the file name is included!
        // THE STRING X IS THE ROWS, THE STRING Y IS THE COLUMNS
        char* Y = argv[2];
        char* X = argv[1];

        puts("Input:");
        printf("Y(columns): ");
        printCString(Y);
        
        printf("X(rows): ");
        printCString(X);

        int lcs_len = lcs(Y, X);
        printf("Length of LCS: %d\n", lcs_len);
        

        // TODO print the lcs

        return 0;
    }
    else {
        puts("Not enough args! Gimme 2 strings!");
        return 1;
    }
}