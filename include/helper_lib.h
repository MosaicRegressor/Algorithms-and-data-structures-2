#ifndef HELPER_LIB
#define HELPER_LIB

/* @file
 * @brief library of helper functions
 */


/*
iterates through the cells of an array and prints the individual cell's content.

input: ptr to the array
output: void
*/
void print_int_array(int arr[], int arr_size);

/*
parses a cstring and parses it to a long int.

input: string(array of char) that represents a long
output: long int that represents the string
*/
long int str_to_lint(char* str);

/*
given two numbers, returns who is greater than the other.

input: the two numbers
output: the maximum number between the two
*/
int max(int n1, int n2);

/*
parses a cstring and parses it to a long int.

input: string(array of char) that represents a long
output: long int that represents the string
*/
long int str_to_lint(char* str);


/*
prints table that contains type int.

input: ptr to table, n of rows, n of columns
*/
void print_tbl(int* tbl[], int n_rows, int n_cols);

/*
deallocates table that contains type int

input: ptr to table, n of columns
*/
void dealloc_table(int* tbl[], int n_cols);

/*
allocate on the heap a table of size n x m and init it(set default behavior).

input: number of rows and columns
output: ptr to the table allocated in the heap
*/
int** alloc_table(int n_rows,int n_cols);

/*
get length of CString

input: ptr to the cstring
*/
int CString_len(char* Cstring);

/*
print the CString

input: ptr to the cstring
*/
void printCString(char* Cstring);

#endif