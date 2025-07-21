/*
Longest increasing subsequence problem
*/

#include "helper_lib.h"
#include <stdio.h>


/*
solves the lis problem with dynamic programming.

input: string of which we want to get the len of the lis
output: len of (one of) the lis(ses) of the string

original answer: what's the length of the lis of the string?
alternate answer on top of which we make our dp algorithm: what's the length of the lis of the string AT THIS PARTICULAR character of the string?
we reuse this info across computations to cache our results.

dynamic programming is about memorizing infos about something across computations.

without dp(and so without caching, saving info across computations), we would waste a lot of time by trying to directly getting the lis(normally, we are not caching): we would have
to check, for every character what comes before and after, a huge mess!
*/
int lis(char* input_string) {
    

    return 0;
}


int main(int argc, char* argv[argc + 1]) {

    if (argc > 1) {
        // TODO sanitize input 
        char* input_string = argv[1];

        puts("Input string:");
        printCString(input_string);

        lis(input_string);

        return 0;
    }
    else {
        puts("Not enough args, gimme 1 string!");

        return 1;
    }
}