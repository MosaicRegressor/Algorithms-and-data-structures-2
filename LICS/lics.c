/*
longest increasing(growing) subsequence problem

find a common subsequence between the two input strings, which is the longest and growing
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "helper_lib.h"

/*
TODO
test cases: check with input that contains duplicate characters.
*/

/*
input: pointer to the table, col and row at the cell at which the computation paused(it contains the char to attach)
output: length of the comaptible lics

we are iterating between the past computations.
a past computation is the length of a lics that end at a ceratin character. 
we must find the length of a lics whose last char is compatible(lower than) with the character in input.
*/
int get_max_prev_comp_lics_len(int* tbl[static 1], int susp_col, int susp_row, char* Y){ // tbl has at least one lement, not null
    int max = 0;
    
    bool is_compatible = false;
    int len_lics = 0;
    for(int row = 0; row < susp_row; row++) {
        for(int col = 0; col < susp_col; col++) { // we make sure to find till one step before the char we want to attach
            if(row == susp_row && col == susp_col) {    // TODO refactor! bad hack!
                break;
            }

            len_lics = tbl[col][row];
            is_compatible = len_lics != 0 && Y[col] < Y[susp_col];
            
            if (is_compatible && len_lics > max) {     // if we are looking at a lics that ends with a compatible char, and its its last char is compatible with the char that we want to attach
                max = tbl[col][row];
            }
        }
    }
    return max;
}


/*
Finds the maximum value in the table.
*/
int find_max_tot(int* tbl[static 1], int n_cols, int n_rows) {
    int max = 0;
    int cell_value = 0;
    for(int row = 0; row < n_rows; row++) {
        for(int col = 0; col < n_cols; col++) {
            cell_value = tbl[col][row];
            if(cell_value > max) {
                max = cell_value;
            }
        }
    }
    return max;
}


/*
we are using dynamic programming.

rules to compute the len of the lics up to a certain point:
1. it must be a subsequence
2. it must be common between X and Y
3. it must be increasing
4. it must be the longest

remember: we are computing the lics UP TO A CERTAIN CHARACTER(we keep reusing this info, this alternate problem is what makes caching possible)

we got two strings, X and Y.
we align them with a matrix.
We start iterating through the strings step by step(the rule #1 is satisfied).
We compare the two characters.
If we got two different characters, we are breaking the rule #2, so the len of the lics up to that point is 0.
If we got two characters that are equal rule #1 is satisfied, therefore we look at the previously computed results: between them we find the
lengths of licses that end with a compatible character(to safisfy rule #3), and we pick the max between them(to satisfy rule #4)   

due to dynamic programming, the execution time goes from 2^n to n^4, so cool!! :))
*/

/*
Y columns
X rows
                    Y
        --------------------------
X       |0 1 0 0 0 0 0 0 0 2 0 0 0
        |0 2 0 0 0 4 0 0 3 0 0 ...
        |
        |
*/

int lics(char X[], char Y[]) {    
    puts("Input strings");
    printCString(Y);
    puts("");
    printCString(X);
    puts("");

    int len_y = CString_len(Y);
    int len_x = CString_len(X);
    
    int n_cols = len_y;
    int n_rows = len_x; 

    int** cache_tbl = alloc_table(n_rows, n_cols);
    print_tbl(cache_tbl, n_rows, n_cols);
    // now everything is perfectly balanced, as all things should be(we got defined behaviour) 


    // let's iterate step by step through the strings
    for(int row = 0; row < n_rows; row++) {
        for(int col = 0; col < n_cols; col++) {
            if(Y[col] != X[row]) {
                cache_tbl[col][row] = 0;
            } else {
                // X[i] and Y[j] are equal
                // let's get the length of the longest previous compatible lics we should attach the current char to
                int len_prev_lics = get_max_prev_comp_lics_len(cache_tbl, col, row, Y);

                // then we attach it
                cache_tbl[col][row] = len_prev_lics + 1;
            }
        }
    }
    print_tbl(cache_tbl, n_rows, n_cols);

    int max_tot = 0;
    max_tot = find_max_tot(cache_tbl, n_cols, n_rows);

    dealloc_table(cache_tbl, n_cols);
    return max_tot;
}

int main(int argc, char* argv[argc + 1]) {
    if(argc > 2){

        char* X = argv[1];
        char* Y = argv[2]; 

        printf("La lics è lunga: %d", lics(X, Y));

        return 0;
    }
    else{
        printf("Not enough args!\n");

        return 1;
    }
}