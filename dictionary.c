#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

typedef struct tries 
{
    bool x;
    struct tries* alpha[27];
}tries;

// tries* head = NULL;

// int main(void)
// {
//     load("dictionaries/small");
// }

tries* head = NULL;

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
   head = malloc(sizeof(tries));

    // open the file and check if it was opened properly
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
        printf("Something went wrong\n");
    
   
    char a;
    // iterate through every character 
    while((a =fgetc(file)) != EOF) 
   {
        tries* trav = head;
        // if(!trav->alpha[c-97]) 
        //     trav->alpha[c - 97] = malloc(sizeof(tries));
        char word[LENGTH + 1];
        int index = 0;
        char c;
        //fseek(file, -1, SEEK_CUR);
        while( (c = fgetc(file)) != '\n')
        {
            word[index] = c;
            index++;
            
        }
        word[index] = '\0';
        for(int i = 0; i < index; i++)
        {
            
            if(trav != NULL && !trav->alpha[word[i] - 97])
                trav->alpha[word[i] - 97] = malloc(sizeof(tries));
                
            if(word[i+1] != '\0')
                trav = trav->alpha[word[i] - 97];
            else
                trav->x = true;
                
        }
               
        // if (c == '\n')
        //     trav->x = true;
       fseek(file, index, SEEK_CUR); 
       
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
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
