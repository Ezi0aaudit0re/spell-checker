#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

#define ALPHA_SIZE 26
#define OFFSET  97


typedef struct tries 
{
    bool x;
    struct tries* alpha[ALPHA_SIZE + 1];
}tries;


/**
 * A function that unload calls which is called recursively 
 */


tries* head = NULL;
int number = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    tries* trav = head;   
    for(int i = 0, n = strlen(word); i < n; i++ )
    {   
        if(trav->alpha[tolower(word[i]) - OFFSET] != NULL)
            trav = trav->alpha[tolower(word[i]) - OFFSET];
            
    }
    if(trav->x == true)
        return true;
    
     return false;    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    // open the file and check if it was opened properly
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
        printf("Something went wrong\n");
        
    head = malloc(sizeof(tries));
    tries* trav = head;
    
    unsigned int c = 0;
    
    // iterate through every character 
    while(c != EOF) 
   {
       c = fgetc(file);
       
       if( c != '\n' && c != EOF)
       {
                
            if ( trav->alpha[c - OFFSET] == NULL)
                trav->alpha[c - OFFSET] = malloc(sizeof(tries));
            
            trav = trav->alpha[c - OFFSET];
       }
       
       // update the value at that location and update head
       else if ( c == '\n')
       {
          number++;
          trav->x = true;
          trav = head;
       }
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(number != 0)
        return number;
    
    return 0;
}


void unloadtries(tries* head)
{
    
    for(int c = 1; c < ALPHA_SIZE ; c++ )
    {
        if(head->alpha[c] != NULL)
            unloadtries(head->alpha[c ]);
    }
    free(head);

}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // we create a function that takes in an argument and unloads
    unloadtries(head);
    return true;
}

