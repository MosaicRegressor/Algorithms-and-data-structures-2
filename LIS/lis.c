/*
Longest increasing subsequence problem
*/

#include "helper_lib.h"
#include <stdio.h>
#include <stdlib.h>


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


to cache the info, we use an array.
*/
int lis(char* input_string) {
    int len_input_str = CString_len(input_string);  // the n
    
    int* cache_arr = calloc(len_input_str, sizeof(int));
    print_arr(cache_arr, len_input_str);

    // base case, one character
    cache_arr[0] = 1;

    // generic case
    int max = 0;
    // generic C[i] calculates max between the values which are lower than him
    for(int i = 1; i < len_input_str; i++) {
        // compute the max of the previous ones, step by step, if you don't find anything, the maximum is zero
        max = 0;
        // determine who has the biggest value between the previous ones
        for(int j = 0; j < (i - 1); j++) {
            if(cache_arr[j] > max && input_string[j] < input_string[i]) { // find the best result which is also compatible with the character 
                max = cache_arr[j];
            }
        }
        // now i got the max between all the predecessors, which is also compatible with the value in exam
        cache_arr[i] = max + 1;
        print_arr(cache_arr, len_input_str);
    }
    // now let's get the biggest between all of the calculated values
    int max_tot = 0;
    for(int i = 0; i < len_input_str; i++){
        if(cache_arr[i] > max_tot){
            max_tot = cache_arr[i];
        }
    }
    free(cache_arr);

    return max_tot;
}


int main(int argc, char* argv[argc + 1]) {

    if (argc > 1) {
        // TODO sanitize input 
        char* input_string = argv[1];

        puts("Input string:");
        printCString(input_string);
        puts("");

        printf("Len of LIS: %d\n", lis(input_string));

        return 0;
    }
    else {
        puts("Not enough args, gimme 1 string!");

        return 1;
    }
}