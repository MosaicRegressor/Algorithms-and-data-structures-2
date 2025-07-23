#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
TODO
- check if malloc fails by checking if it returns NULL pointer 
- check into functions if the passed pointer is NULL as safety
*/


// NB there must be a nullbyte terminator at the end of the string!
void printCString(char* Cstring) {
    for (int i = 0; Cstring[i] != '\0'; i++){
        printf("%c", Cstring[i]);
    }
}

// NB there must be a nullbyte terminator at the end of the string!
int CString_len(char* Cstring) {
    int string_length = 0;

    for(char* chr = Cstring; *chr != '\0'; chr++) {
        string_length++;
    }

    return string_length;
}

/*
just iterate through the array.
*/
void print_arr(int* ptr_arr, int len_arr) {
    for(int i = 0; i < len_arr; i++) {
        printf("%d", ptr_arr[i]);
    }
    puts("");
}

/*
the user at runtime may input very big strings, let's allocate the caching tables in the heap.
a table is an array of pointers, to arrays of ints.
*/
int** alloc_table(int n_rows,int n_cols) {
    int** tbl = calloc(n_cols, sizeof(int*));   // TODO optimize! memory fragmentation!
                                                // set defined behavior, done by calloc

    // alloc the columns with the cell rows
    for(int col = 0; col < n_cols; col++) {
        tbl[col] = calloc(n_rows, sizeof(int));
    }

    /*
    done automatically by calloc

    // set each of the columns row cells to defined behavior
    for(int col = 0; col < n_cols; col++) {     // TODO slow!, is it that necessary?
        for(int row = 0; row < n_rows; row++) {
            tbl[col][row] = 0;
        }
    }

    */

    return tbl;
}


void dealloc_table(int* tbl[], int n_cols) {
    // deallocate table content
    for(int col = 0; col < n_cols; col++) { // iterate through the array that holds the columns, and deallocate each of them
        free(tbl[col]);
    }

    // deallocate table
    free(tbl);
}

void print_tbl(int* tbl[], int n_rows, int n_cols) {
    puts("print status of tbl");
    for(int row = 0; row < n_rows; row++){  // iterate through columns
        for(int col = 0; col < n_cols; col++) { // iterate through rows
            printf("%d", tbl[col][row]);
        }
        printf("\n");
    }
}



int max(int n1, int n2) {
    return (n1 < n2) ? n2 : n1;
}


/*
This wrapper makes sure that the inputted string is:
- a whole number
- of type long int FIXME make it UNSIGNED long int
- not a value which makes the input variable overflow or underflow

this is a wrapper for strtol.
how does strtol work:
it converts a string in a long int, while interpreting in a specified numeric base.
built in checks of strtol:
let's suppose strtol encounters a non valid chr.
- if endptr is not NULL, writes at endptr the address of the first non parsed char
- if str contains no valid number, return 0 and endptr points to str
- if the converted value is out of range of the type long, set errno(a global variable used by all libraries to save return values) at ERANGE and
returns LONG_MAX OR LONG_MIN, depending upon the value.
*/
long int str_to_lint(char* str){
    char* endptr = 0;
    errno = 0;
    
    long int parse_result = strtol(str, &endptr, 10);

    // check if string does not represent a value which is too big or small
    if((parse_result == LONG_MAX || parse_result == LONG_MIN) && errno == ERANGE) {
        printf("Input parse error: overflow or underflow\n");
        return 1;
    }

    // check if whole string is a number
    if(*endptr != '\0'){
        printf("Input parse error: input not numerical, parsing interrupted at: %c", *endptr);
        return 1;
    }

    // here you can put additional filters...

    // all checks passed, let's return
    return parse_result;
}


void print_int_array(int arr[], int arr_size) {
    for(int i = 0; i < arr_size; i++) {
        arr[i] = 0;
    }
}