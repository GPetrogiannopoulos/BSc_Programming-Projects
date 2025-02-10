// PETROGIANNOPOULOS GEORGIOS , AM: 2022201900182
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>  //used by: isalpha, isdigit, isalnum

union semanticinfo{
    int i;
    char* s;
};

FILE* openfile() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "input.txt", "r");
    if (err != 0) {
        printf("File was not opened\n");
        return 0;
    }
    return fp;
}

int yylex(FILE* fp,union semanticinfo *sem) {
    char nextcharacter;
    int state = 0, characters = 0; // d = counter for non digit numbers

    while ((nextcharacter = fgetc(fp)) != EOF) {
        //DFA
        switch (state) {
        case 0:
            if (isalpha(nextcharacter)) {
                state = 1;
                sem->s = (char*)malloc(sizeof(char) * 100); // allocate memory for union's string: s
                sem->s[characters] = nextcharacter;
                characters++;
            }
            else if (isdigit(nextcharacter)) {
                state = 2;
                sem->i = nextcharacter - '0'; // for the first number
            }
            break;
        case 1:
            if (isalnum(nextcharacter)) {
                sem->s[characters] = nextcharacter;
                characters++;
            }
            else {
                sem->s[characters] = '\0'; // define string termination
                return 1;
            }
            break;
        case 2:
            if (isdigit(nextcharacter)) {
                sem->i = ((sem->i) * 10) + (nextcharacter-'0');      // (previous number*10) + next number
            }
            else{
                return 2;
            }
            break;
        }
    }  
    fclose(fp); // closing the file returns 0 
}

int main(int argc, char** argv){
    int tokentype = 0 ;
    union semanticinfo sem ;
    FILE *fp = openfile();
    
    while ( (tokentype = (yylex(fp, &sem)) ) != EOF) {
        if (tokentype == 1) {
            printf("-------------\nstring: %s\n", sem.s);
            free(sem.s);
        }
        else if (tokentype == 2) {
            printf("-------------\nnumber: %d\n-------------\n", sem.i);
        }
        else if(tokentype == 0){
            printf("End of file\n-------------\n");
        }
    }

    return 0;
}
