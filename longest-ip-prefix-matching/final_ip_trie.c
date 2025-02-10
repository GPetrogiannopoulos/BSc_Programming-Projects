/*
Petrogiannopoulos Georgios
2022201900182
dit19182@uop.gr

Drakopoulos Theodoros
2022201900052
dit19052@uop.gr         
*/ 

// TODO -> THE IPS THAT WE READ SHOULD HAVE THEIR PREFIX ALSO IN THE TREE NOT ONLY THEIR BINARY
//         SO EVERY IP WE READ HAS 2 PARTS BINARY AND PREFIX WHICH WE ADD TO THE TREE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef int treeItem;
typedef struct treenode *treelink;

struct treenode
{
    treeItem data;
    treelink left, right;
};

void displaytree(treelink root);
void disp(treeItem *displaymat, int idx, treelink root);
int treeheight(treelink root);
treelink createleaf(treeItem data);

int * ip_prefix(int *prefix_length, char* input, char* option); // returns an array that contains the prefix

int main()
{
    int prefix_length, i , binary_length;
    int* prefix;
    int* binary;
    int* user_input;
    char input[20];
    char option[20];

    treelink root = NULL;
    root = createleaf(3);               //add value to root
    treelink tmproot = root;

    // read from file
    static const char filename[] = "routingtable.txt";
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        char line [128]; 
        while ( fgets ( line, sizeof line, file ) != NULL )     // read a line
        {
            printf("\n");
            fputs ( line, stdout );                             // print line from the file 
           
            prefix = ip_prefix(&prefix_length,line,"prefix");   // passing prefix_length's address as a parameter to "return" it to main

            // add the prefixes to the tree
            tmproot = root;
            for(i=0;i<prefix_length;i++)
            {
                if(prefix[i] == 1)
                {
                    if(tmproot->right == NULL)
                    {
                        tmproot->right = createleaf(prefix[i]);
                    }
                    tmproot = tmproot->right;
                }
                else 
                {
                    if(tmproot->left == NULL)
                    {
                        tmproot->left = createleaf(prefix[i]);
                    }
                    tmproot = tmproot->left;
                }
            }
        }
        fclose ( file );
    }
    else
    {
        perror ( filename ); 
    }
    //-----------------

    input:
    printf("\nEnter ip address:");
    scanf("%s", input);                 // read ip as string

    binary = ip_prefix(&prefix_length,input,"binary");   // passing prefix_length's address as a parameter to "return" it to main   
    int temp=-1;    // store the current position of the bit in the binary number

    // search the input ip in the tree
    printf("\n--> common: ");
    tmproot = root;
    for(i=0;i<32;i++)
    {
        if(binary[i] == 1)
        {
            if(tmproot->right!=NULL)
            {
                if( (binary[i] == tmproot->right->data) && temp==i-1 )  // temp= i-1 check equal bits continuity
                {    
                    printf("%d",binary[i]);
                    tmproot = tmproot->right;
                    temp=i;     
                }
            }
        }
        else 
        {
            if(tmproot->left!=NULL)
            {
                if( (binary[i] == tmproot->left->data) && temp==i-1 )  // temp= i-1 check equal bits continuity
                {    
                    printf("%d",binary[i]);
                    tmproot = tmproot->left;
                    temp=i;     
                }
            }
        }
    }
    printf("\n\n");
    // ---------------------------

    char answer;
    printf("Do you want to search another ip? press y for yes n, for no\n");
    do{
        answer=getchar();
    }while( (answer!='y') && (answer!='n') );
    if(answer=='y')
    {
        goto input;
    }
    printf("exiting\n");

    //displaytree(root);

    free(binary);
    free(prefix);

    return 0;   
}


void displaytree(treelink root)
{
    int i, j, k = 0, l, num = 1;
    
    int height = treeheight(root);
    
    int maxcount = pow(2,height+1)-1;
    
    treeItem *displaymat = (treeItem*)malloc(maxcount*sizeof(treeItem));
    
    for (i = 0; i < maxcount; i++)
        displaymat[i]=3;
    
    disp(displaymat, 0, root);
    
    int firstchar = maxcount/2;
    
    int delta = maxcount;
    
    for(i = 0; i <= height; i++)
    {
        for(j = 0; j < firstchar; j++)
        {
            printf(" ");
        }   
        
        for(j = 0; j < num; j++)
        {
            printf("%d", displaymat[k]);
            k++;
            
            for(l = 0; l < delta; l++)
                printf(" ");
        }
    
        num = 2*num;
        delta = delta/2;
        firstchar = firstchar/2;
        
        printf("\n");
    }
    free(displaymat);
}

void disp(treeItem *displaymat, int idx, treelink root){
    
    if(root == NULL)
    
        return;
    
    displaymat[idx] = root->data;
    
    disp(displaymat, 2*idx+1, root->left);
    
    disp(displaymat, 2*idx+2, root->right);
    
}

int treeheight(treelink root)
{
    int lheight, rheight;
    
    if (root == NULL){
        
        return -1;
    } 
    
    lheight = treeheight(root->left);
    
    rheight = treeheight(root->right);
    
    if (lheight > rheight)
    
        return lheight + 1;
        
    else
    
        return rheight + 1;

}

treelink createleaf(treeItem data)
{
    
    treelink tmproot = (treelink)malloc(sizeof *tmproot);
    
    tmproot->data = data;
                            
    tmproot->left = NULL;
                    
    tmproot->right = NULL;  
}


int * ip_prefix(int *prefix_length, char* input, char* option) //returns an array that contains the prefix 
{
    int i=0, j,k;       
    int ip[4];          // array to store ip seperated by "."
    
    int *binary;
    binary = (int *)malloc(sizeof(int)*32);

    int * bin;
    char * piece;
    char* temp;         // pointer containing prefix length

    if(option=="prefix")
    {
        // separate prefix bits from the other binary's bits
        for(k=0;k<strlen(input);k++)
        {
            if(input[k]=='/')  // search for the " / " in the binary number
            {
                temp = &input[k];
                temp++;
                break;
            }
        }
        
        if(temp[1] < '0' || temp[1] > '9')
            temp[1] = '\0';

        if(strlen(temp) > 1)
        {
            *prefix_length = (temp[0]-'0')*10 + temp[1]-'0';
        }
        else
            *prefix_length = temp[0]-'0';
        // ---------------------------
    }

    piece = strtok(input, ".");     // split . seperated ip , first call to the function strtok will return first piece in the string, subsequent calls to the function with null as first parameter will return subsequent pieces
    do 
    {
        ip[i++] = atoi(piece);      // atoi(string) converts string to integer, store pieced string into integer array
        piece = strtok(NULL, ".");  // this is subsequent call
    }while (piece && i < 4);

    // loop through ip's e.g 192.168.0.1 first loop will process ip[0] which has 192 stored
    for (j = 0; j < 4; j++)  
    {
         // takes an integer as input
        // returns binary stored in integer array
        int a = ip[j];
        int * num = (int * ) malloc(sizeof(int) * 8); // allocating memory for 8 integers
        for (i = 0; i <= 7; i++) 
        {
            num[7 - i] = a % 2;
            a = a / 2;
        }
        bin = num;
        
        for (i = 0; i < 8; i++) 
        {
            binary[j * 8 + i] = bin[i];     // store converted binary into correct position in 32 binary array
        }
    }
    // ---------------------------

    // printing ip's binary
    printf("> binary: ");
    for (i = 0; i < 32; i++)    
    {
        if (i > 0 && (i) % 8 == 0) printf("."); // print a "." after printing 8 digits
        printf("%d", binary[i]);                // print binary values of given ip saved in this int array
    }
    printf("\n");

    int *prefix;    
    prefix = (int*)malloc(*prefix_length*sizeof(int));
    if(option=="prefix")
    {
        printf("> prefix: ");
        for(i=0;i<*prefix_length;i++)               // taking the first e bits of the ip ( a.b.c.d/e ) 
        {
            prefix[i] = binary[i];
            printf("%d",prefix[i]);
        }
        printf("\n");
    }
    // ---------------------------

    if(option == "prefix")
    {
        return prefix;
    }
    else if(option == "binary")
    {
        return binary;
    }
}





                            
