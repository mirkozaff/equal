#include "funzioni.h"
#include <stdio.h>

int main(int argc, char *argv[]){
char fname1[40], fname2[40];

    printf("Enter name of first file :") ;
    gets(fname1);

    printf("Enter name of second file:");
    gets(fname2);
    
    //sameFileCheck(fname1, fname2);

    printf("result: %d\n",check_dup_memmap(fname1, fname2));
    return (0);
}