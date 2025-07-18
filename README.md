# Algorithms-and-data-structures-2

All c source files are compiled with gcc ver. 13.3.0, with flags -Werror -Wall -Wextra -pedantic -std=c11

compile command: gcc -Werror -Wall -Wextra -pedantic -std=c11 file.c -g -o file.out

memory errors are checked with Valgrind 3.22.0

memory check command: valgrind -s --leak-check=full ./file.out input1 input2