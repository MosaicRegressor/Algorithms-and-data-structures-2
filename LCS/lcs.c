/*
longest common subsequence problem

find lenght(the optimum) of the longest common subsequence between two strings
then find one of the substrings with that length, between the optimum

a subsequence can be contiguous but doesn't have to be, it just has to be a sequence! you can't choose characters at random order
*/
#include <string.h>
#include <stdio.h>

// NB there must be a nullbyte terminator at the end of the string!
void printCString(char* Cstring){
    for (int i = 0; Cstring[i] != '\0'; i++){
        printf("%c", Cstring[i]);
    }
    printf("\n");
}

// NB there must be a nullbyte terminator at the end of the string!
int CString_len(char* Cstring){

    int string_length = 0;

    for(char* chr = Cstring; *chr != '\0'; chr++) {
        string_length++;
    }

    return string_length;
}

// exponentital time!!! it recomputes already certain known common subsequences
int lcs_length_bruteforce(char* X, char* Y){
    int tmp_x = 0;
    int i = 0;
    int lcs_len = 0;
    int tmp_y = 0;
    int y = 0;

    int Y_len = CString_len(Y);
    int X_len = CString_len(X);
    for(int y = 0; y < Y_len; y++) {
        tmp_x= 0;
        for(tmp_y = y; tmp_y < Y_len; tmp_y++){
            i = tmp_x;
            while(X[i] != Y[tmp_y] || X[i] == '\0') {
                i++;
            }
            if(X[i] == Y[tmp_y]){
                tmp_x = i;
                lcs_len++;
            }
            tmp_y++;
        }
        y++;
    }
    return lcs_len;
}


// TODO
// int lcs_lenght_dyn_prog(char* X, char* Y);

int main(int argc, char* argv[argc + 1]) {
    if (argc > 1) {
        char* X = argv[1];
        char* Y = argv[2];

        puts("Input:");
        printCString(X);
        printCString(Y);

        printf("Lcs length: ");
        printf("%d\n", lcs_length_bruteforce(X, Y));
    }
    else {
        puts("Not enough args!");
    }

    return 0;
}