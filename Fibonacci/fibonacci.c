/*
fibonacci's succession:
0 1 1 2 3 5 8 13 ...
*/

#include <stdio.h>
#include <stdlib.h>
#include "helper_lib.h"

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

        return 0;
    }
    else{
        printf("Not enough args!\n");

        return 1;
    }
}