/*
successione di fibonacci
0 1 1 2 3 5 8 13 ...

*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

// in: posizione voluta
// out: numero alla posizione volta nella successione di fibonacci
int fibonacci_slow(int pos){
    if (pos == 1){
        return 0;
    }
    else if(pos == 2){
        return 1;
    }
    // per avere il numero alla posizione pos, devo sommare i numeri alle posizioni pos - 1 e pos -2
    return fibonacci_slow(pos - 1) + fibonacci_slow(pos - 2);
}

/*
parses a cstring and parses it to a long int.

input: string(array of char) that represents a long
output: long int that represents the string

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
    
    int parse_result = strtol(str, &endptr, 10);

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

int main(int argc, char* argv[argc + 1]) {
    if(argc > 1){
        int parsed_input = 0;

        parsed_input = (int) str_to_lint(argv[1]);  // FIXME long int casted to int, loss of info
        printf("%d\n", fibonacci_slow(parsed_input));
    }
    else{
        printf("Not enough args!\n");
    }

    return 0;
}