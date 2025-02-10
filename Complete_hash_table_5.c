/*
Petrogiannopoulos Georgios
2022201900182
dit19182@uop.gr

Drakopoulos Theodoros
2022201900052
dit19052@uop.gr
*/ 

/* description:

    > functions:

      > for hashtable:
          hash_function
          create_item
          free_item
          create_table
          free_hashtable
          ht_insert
          print_hashtable

      > for handling the ID and collision lists
          allocate_list
          linkedlist_insert
          linkedlist_remove
          free_linkedlist
          create_ID_buckets
          create_overflow_buckets
          handle_ID
          handle_collision

      > for the commands
          stats
          query

    > structs:
        ht_item
        Linkedlist
        HashTable
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 500000 // Size of the Hash Table

unsigned long hash_function(char* str) {   // simply sums the ASCII value of the string
    unsigned long i = 0;
    int j;
    for (j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;   //  return a number within the capacity of the hash table. Otherwise, it may access an unbound memory location(error).
}

typedef struct Ht_item Ht_item;
// Define the Hash Table Item here
struct Ht_item {
    char* key;
    char* value;
    int DF;
};

typedef struct LinkedList LinkedList;
// Define the Linkedlist here
struct LinkedList {
    Ht_item* item; 
    LinkedList* next;
};

typedef struct HashTable HashTable;
// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    LinkedList** overflow_buckets;
    LinkedList** ID_buckets;
    int size;
    int count;
};

static LinkedList* allocate_list () {
    // Allocates memory for a Linkedlist pointer
    LinkedList* list = (LinkedList*) calloc (1, sizeof(LinkedList));
    return list;
}

static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    // Inserts the item onto the Linked List
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
    
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;
    while (temp->next) {
        temp = temp->next;
    }
    
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    
    return list;
}

static Ht_item* linkedlist_remove(LinkedList* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    if (!list)
        return;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

static LinkedList** create_ID_buckets(HashTable* table) {
    // Create the ID buckets an array of linkedlists
    LinkedList** id_buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    int i;
    for (i=0; i<table->size; i++)
        id_buckets[i] = NULL;
    return id_buckets;
}

//collision is implemented with separate chaining: creates independent chains for all items that have the same hash index
static LinkedList** create_overflow_buckets(HashTable* table) {
    // Create the overflow buckets an array of linkedlists
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    int i;
    for (i=0; i<table->size; i++)
        buckets[i] = NULL;
    return buckets;
}

static void free_ID_buckets(HashTable* table) {
    // Free all the ID bucket lists
    LinkedList** id_buckets = table->ID_buckets;
    int i;
    for (i=0; i<table->size; i++)
        free_linkedlist(id_buckets[i]);
    free(id_buckets);
}

static void free_overflow_buckets(HashTable* table) {
    // Free all the overflow bucket lists
    LinkedList** buckets = table->overflow_buckets;
    int i;
    for (i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}

Ht_item* create_item(char* key, char* value) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) calloc (strlen(key) + 1, sizeof(char));
    item->value = (char*) calloc (strlen(value) + 1, sizeof(char));
    
    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    int i;
    for (i=0; i<table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);
    table->ID_buckets = create_ID_buckets(table);

    return table;
}

void free_item(Ht_item* item) {
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}

void free_hashtable(HashTable* table) {
    // Frees the hashtable
    int i;
    for (i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    //free_ID_buckets(table);
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void handle_ID(HashTable* table, unsigned long index, Ht_item* item) { 
    // insert ID to the current items's ID list
    LinkedList* head = table->ID_buckets[index];

    if (head == NULL) {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->ID_buckets[index] = head;
        return;
    }
    else {
        // Insert to the list
        table->ID_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
    // insert ID to the overflow list (collision)
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }

void ht_insert(HashTable* table, char* key, char* value) // insert item in the hashtable 
{ 
        Ht_item* item = create_item(key, value);  // Create the item
        int index = hash_function(value);         // Compute the index which is produced by the value h(value)
        Ht_item* current_item = table->items[index]; 
    
      if(table->items[index]) // check if item is already in hashtable
      {
        table->items[index]->DF ++;
        handle_ID(table, index, item);  // insert id in id list
        return;
      }
      else    // item is not in hashtable
      {
        if (current_item == NULL) 
        {
          if (table->count == table->size) {// Key does not exist.
              // Hash Table Full
              printf("Insert Error: Hash Table is full\n");
              // Remove the create item
              free_item(item);
              return;
          }
          
          handle_ID(table, index, item);  // insert id in id list
          // insert in hashtable
          table->items[index] = item;  
          table->count++;
          return;
        }
        else if (strcmp(current_item->value, value) != 0){
          //  Collision
          handle_collision(table, index, item);
          return;
          }
      }
}

int stats(HashTable* table, char* value)
{
  int index = hash_function(value);

  if (table->items[index]) 
  {
    return (table->items[index]->DF)+1; 
  }
  else{
    return 0;
  }
}

void query(HashTable* table, char* value) // Searches given value in the hashtable
{
  int index = hash_function(value);
  Ht_item* item = table->items[index];
  LinkedList* head2 = table->ID_buckets[index];

  if (table->items[index]) 
  {
    if (table->ID_buckets[index]) {
      LinkedList* head2 = table->ID_buckets[index];
      while (head2) {
          printf(" %s,", head2->item->key);
          head2 = head2->next;
      }
    }
  }
  else{
    printf("No documents found!");
  }
}

void queryOR(HashTable* table, char* value1, char* value2) // queryOR only for 2 values
{
  int index1 = hash_function(value1);
  int index2 = hash_function(value2);

        if (table->items[index1]) {
             if (table->ID_buckets[index1]) {
                LinkedList* head1 = table->ID_buckets[index1];
                while (head1) {
                    printf(" %s,", head1->item->key);
                    head1 = head1->next;
                }
            }
            printf("\n");
        }
        if (table->items[index2]) {
             if (table->ID_buckets[index2]) {
                LinkedList* head2 = table->ID_buckets[index2];
                while (head2) {
                    printf(" %s,", head2->item->key);
                    head2 = head2->next;
                }
            }
            printf("\n");
        }
}

void print_hashtable(HashTable* table) { // prints the hashtable
    printf("\n-------------------\n");
    int i;
    for (i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s, DF:%d", i, table->items[i]->key, table->items[i]->value, table->items[i]->DF);
            if (table->overflow_buckets[i]) {
                printf("\n\t=> Overflow Bucket: \n");
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("\tKey:%s, Value:%s \n", head->item->key, head->item->value);
                    head = head->next;
                }
            }
             if (table->ID_buckets[i]) {
                printf("\n\t=>ID:");
                LinkedList* head2 = table->ID_buckets[i];
                while (head2) {
                    printf(" %s,", head2->item->key);
                    head2 = head2->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}

void file_input_process(HashTable* ht,char const* fileName)  // opens given file , reads and extracts ID , words line by line
{
          FILE* file = fopen(fileName, "r");  // open file 

          if(file==NULL){  // file existence check
            printf("\n Unable to open : %s ", fileName);
            exit(1); 
          }
          else
            printf("\n1 document loaded and indexed!\n");

          char line[1000];
          while (fgets(line, sizeof(line), file)) // read file line by line
          {
              int i=0,j=0,k=0;
              char substr[1000][1000]={0}; // for splitting the line by space and removing repeated words

              for(i=0;i<=strlen(line);i++){ // convert all uppercase to lowercase
                if( (line[i]>=65) && (line[i]<=90) )
                  line[i]=line[i]+32;

                if(!( (line[i]>='a'&&line[i]<='z') || (line[i]>='0'&& line[i]<='9') || line[i]=='\0' ) ) // remove symbols
                {
                  line[i]=' ';  
                }
              }

              while(line[k]!='\0') //splitting line to substrings
              {
                  j=0;
                  while(line[k]!=' '&& line[k]!='\0')
                  {
                      substr[i][j]=line[k];
                      k++;
                      j++;
                  }
                  substr[i][j]='\0';
                  i++;
                  if(line[k]!='\0')
                  {
                      k++;
                  }        
              }
              
             //Removing repeated words 
             int len=i;
             for(i=0;i<len;i++)
              {
                for(j=i+1;j<len;)
                {
                  if(strcmp(substr[i],substr[j])==0)
                  {     
                    for(k=j;k<len;k++)
                    {
                      strcpy(substr[k],substr[k+1]);
                    }
                    len--;
                  }
                  else
                  {
                    j++;
                  } 
                }
              }
            
            // substr contains every substring of the line separated by space
              for(i=1;i<len;i++) 
              {
                if(i!=1)
                  ht_insert(ht, substr[1], substr[i]); // sunstr[1] = ID , substr[i]=words
              }
          }
          fclose(file);
}

void keyboard_input(HashTable* ht)
{
        start:
        printf("Insert command: ");
        char str[100];
        char splitStrings[6][30]; //can store 6 words of 30 characters
        int i,l,j=0,k=0,count=0,result;
    
          fgets(str, sizeof(str), stdin);
          str[strlen(str)-1]='\0';     // remove newline
    
          for(i=0;i<=(strlen(str));i++)
          {
              // if space or NULL found, assign NULL into splitStrings[cnt]
              if(str[i]==' '||str[i]=='\0')
              {
                  splitStrings[count][j]='\0';
                  count++;  //for next word
                  j=0;    //for next word, init index to 0
              }
              else
              {
                  splitStrings[count][j]=str[i];
                  j++;
              }
          }

        // stats (only 1 word)
        if(strcmp(splitStrings[0],"stats")==0)
        {        
          printf("\nstats:\n");
          printf("-------------------\n");
          printf("%d Documents\n",stats(ht,splitStrings[1]));
          printf("-------------------\n");
        }

        // query (only 1 word) 
        if(strcmp(splitStrings[0],"query")==0)
        {        
         printf("\nquery:\n");
          printf("-------------------\n");
          query(ht,splitStrings[1]);
          printf("\n-------------------\n");
        }

        if(strcmp(splitStrings[0],"load")==0)
        {        
          printf("-------------------\n");
          file_input_process(ht,splitStrings[1]);
          printf("\n-------------------\n");
          goto start;
        }

        // queueOR
        if(strcmp(splitStrings[0],"queryOR")==0)
        {
          printf("\nqueueOR:\n");
          printf("-------------------\n");
        
          queryOR(ht,splitStrings[1],splitStrings[2]); 
          printf("\n-------------------\n");
        }
}

int main() 
{
    HashTable* ht = create_table(CAPACITY);

    // collision example:
    //ht_insert(ht, "12345", "Hel");
    //ht_insert(ht, "1234", "Cau"); // collision Cau and Hel have same index, so cau will not be inserted 

    keyboard_input(ht);
     
    // print hashtable
    //printf("\nhashtable");
    //print_hashtable(ht);

    free_hashtable(ht);
    return 0;
}