#include "funzioni.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>


void printdir(char *dir, int depth)
{
    DIR * dp;
    DIR * d1;
    DIR * d2;
    
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }

    chdir(dir);

    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            // Found a directory, but ignore . and ..
            if(strcmp(".", entry-> d_name) == 0 || strcmp("..", entry->d_name) == 0){
                continue;
            }
            printf("%*s%s/\n", depth,"", entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else {
        	printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

void sameFileCheck(char * fname1, char * fname2){
    
    FILE *fp1, *fp2;
    int ch1, ch2;
    
    fp1 = fopen( fname1,  "r" );
    fp2 = fopen( fname2,  "r" ) ;

    if ( fp1 == NULL )
       {
       printf("Cannot open %s for reading ", fname1 );
       exit(1);
       }
    else if (fp2 == NULL)
       {
       printf("Cannot open %s for reading ", fname2 );
       exit(1);
       }
    else {
        ch1  =  getc( fp1 ) ;
        ch2  =  getc( fp2 ) ;

        while( (ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2))
        {
            ch1 = getc(fp1);
            ch2 = getc(fp2) ;
        }

        if (ch1 == ch2)
            printf("Files are identical");
        else if (ch1 !=  ch2)
            printf("Files are Not identical");

        fclose ( fp1 );
        fclose ( fp2 );
       }
    return(0);
}
