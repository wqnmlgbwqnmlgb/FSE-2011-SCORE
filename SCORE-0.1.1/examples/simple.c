/*
 * simple.c 
 * This is a simple example program to show how to set symbolic inputs
 * in a target program. The include/score.h header file provides SCORE_char, 
 * SCORE_unsigned_char, SCORE_int, etc. according to the type of variables, 
 * to specify symbolic inputs. These functions take two arguments: a variable
 * to be used as a symbolic input, and a name of the symbolic input, which 
 * can be anything. The name of a symbolic input is used to print a generated
 * test case. 
 */
#include <score.h>
#include <stdio.h>

int main(){
    // Test input a, b, c
    int a, b, c;

    SCORE_int(a, "a");
    SCORE_int(b, "b");
    SCORE_int(c, "c");
    
    if (a == 1){
        if (b == 2){
            if (c == 3*a + b){
                // Suppose that this is an error location
                printf("ERROR\n");
                return 1;
            }
        }
    }
    return 0;
}
