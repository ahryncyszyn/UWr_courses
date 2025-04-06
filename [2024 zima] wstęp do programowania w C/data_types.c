#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{

    // data types
    char a = 'a';                               // single char             %c
    char b[] = "abc";                           // array of chars          %s
    char b2[] = {'a', 'b', 'c', '\0'};          // string = array of chars

    float c = 3.1415;                           // 4 bytes                 %f
    double d = 3.1415926;                       // 8 bytes                 %lf
    bool e = true;                              // 1 byte                  %d
    char f = 127;                               // 1 byte (-128, 127)      %d / %c
    unsigned char g = 255;                      // 1 byte (0, 255)         %d / %c
    short h = 32767;                            // 2 bytes                 %d
    int i = 2147483647;                         // 4 bytes                 %d
    unsigned int j = 8089898908;                // 4 bytes                 %u
    long long int k = 92233720743928;           // 8 bytes                 %lld
    unsigned long long int l = 99999;           // 8 bytes                 %llu

    // formatting printing
    // %.1 = decimal precision
    // %1 = minimum field width
    // %- = left align

    // constant = value can not be changed
    const float PI = 3.14;

    // input + output
    char name[25];  // number of bytes
    int age;
    printf("Whats your name?\n");
    fgets(name, 25, stdin);                     // reads in the spaces, includes a newline
    name[strlen(name) - 1] = '\0';              // removes the newline

    printf("Whats your age?\n");
    scanf("%d", &age);                          // & = address of, breaks after a space
    printf("Hello, %s!\n", name);
    printf("You are %d years old!\n", age);

}