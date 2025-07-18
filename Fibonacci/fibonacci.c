/*
fibonacci's succession:
0 1 1 2 3 5 8 13 ...
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

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


/*
iterates through the cells of an array and prints the individual cell's content.

input: ptr to the array
output: void
*/
void print_int_array(int arr[], int arr_size) {
    for(int i = 0; i < arr_size; i++) {
        arr[i] = 0;
    }
}


/*
gives number at a certain position in fibonacci succession

input: position of wanted number in fib. succession
output: number at the wante position in fibonacci succession

problem: it is damn slow!
that's because this implementation recalculates the same subproblems multiple times.
The nodes of the recursion tree explode, the average time is exponential! as a matter of fact, starting from input >40
the response time start to get noticeably slower.
*/
int fibonacci_slow(int pos){    // FIXME the position is an unsigned int
    if (pos == 1){
        return 0;
    }
    else if(pos == 2){
        return 1;
    }
    // to get tge number at the position specified by pos, i have to sumthe number at the positions pos - 1 e pos -2
    return fibonacci_slow(pos - 1) + fibonacci_slow(pos - 2);
}

/*
a bit because O is a power of n, which is not that fast, but way faster compared to 2^N.

we achieved this optimization by caching the recurrent subproblems' solutions: this technique is called dynamic programming.
Dynamic programming introduces some overhead, which is given by accessing and storing the caching table, but if the upsides are higher than the downsides, it's the way to go.

For simplicity, in this piece of code we suppose that pos is > 2.
*/
int fibonacci_a_bit_faster(int pos){    // FIXME position is an unsigned int   
    int cache[] = {0, 0};

    cache[0] = 0;   // first value in fibonacci's succession
    cache[1] = 1;

    // to optimize the occupied space, we just keep the numbers we need to compute the next number, not all of them
    int tmp = 0;
    for(int i = 2; i < pos; i++) {
        tmp = cache[1];
        cache[1] = cache[i - 2] + cache[i - 1];
        cache[0] = tmp;
    }

    int fib_num_at_pos = cache[1];

    free(cache);

    return fib_num_at_pos;
}


int main(int argc, char* argv[argc + 1]) {
    if(argc > 1){
        int parsed_input = 0;

        parsed_input = (int) str_to_lint(argv[1]);  // FIXME long int casted to int, loss of info
        
        puts("Start fibonacci with dynamic programming:");
        printf("%d\n", fibonacci_a_bit_faster(parsed_input));

        puts("Start fibonacci without dynamic programming:");
        printf("%d\n", fibonacci_slow(parsed_input));
    }
    else{
        printf("Not enough args!\n");
    }

    return 0;
}