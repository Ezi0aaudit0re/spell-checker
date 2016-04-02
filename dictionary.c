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
        if(trav->alpha[tolower(word[i]) - 97] != NULL)
        {
            trav = trav->alpha[tolower(word[i]) - 97];
        }
            
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
    
    char c = 0;
    
    // iterate through every character 
    while(c != EOF) 
   {
       c = fgetc(file);
       
       
       if( c != '\n' && c != EOF)
       {
        //   if(c == '\')
        //         c = ALPHA_SIZE + OFFSET 
                
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

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
