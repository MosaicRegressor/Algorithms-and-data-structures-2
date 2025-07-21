/*
Longest increasing subsequence problem
*/

#include "helper_lib.h"
#include <stdio.h>

int main(int argc, char* argv[argc + 1]) {

    if (argc > 2) {
        // TODO sanitize input 
        char* input_string = argv[1];

        puts("Input string:");
        printCString(input_string);
        

        return 0;
    }
    else {
        puts("Not enough args, gimme 1 string!");

        return 1;
    }
}