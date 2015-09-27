/*
 * triangle.c
 * This program takes three integer inputs as lengths of three sides of a 
 * triangle, and determines a type of the triangle. 
 * 
 * This example is taken from "Software Testing: A Craftsman's Approach 2/e",
 * by P. C. Jorgensen. 
 */ 
#include <score.h>
#include <stdio.h>
int main() {
    int a,b,c, match=0;
    SCORE_int(a, "a"); SCORE_int(b, "b"); SCORE_int(c, "c");

    if(a <= 0 || b <= 0 || c <= 0) exit(1);

    // 0: Equilateral, 1:Isosceles,
    // 2: Not a triangle, 3:Scalene
    int result=1;

    if(a == b) match = match + 1;
    if(a == c) match = match + 2;
    if(b == c) match = match + 3;
    if(match == 0) {
        if(a + b <= c) result = 2;
        else if(b + c <= a) result = 2;
        else if(a + c <= b) result = 2;
        else result = 3;
    } else {
        if(match == 1) {
            if(a+b <= c) result = 2;
            else result = 1;
        } else {
            if(match == 2) {
                if(a+c <= b) result = 2;
                else result = 1;
            } else {
                if(match == 3) {
                    if(b + c <= a) result = 2;
                    else result = 1;
                } else result = 0;
            } 
        }
    }
    printf("result = %d\n", result);
    return 0;
}
