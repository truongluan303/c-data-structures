/******************************************************************************
 * 
 * @file        hashtable.c
 * 
 * @author      Luan Truong
 * 
 * @brief       An implementation of hash table
 * 
 * @version     0.1
 * 
 * @date        April 2022
 * 
 *****************************************************************************/

#include <stdlib.h>
#include <time.h>

#define HASHSIZE        101

/******************************************************************************
 * @brief   A node to store one command's info in the hash table
 *****************************************************************************/
struct nlist {
    struct nlist*   next;       /* next entry in chain */
    int             pid;        /* the process ID */
    size_t          index;      /* the line index in the input text file */
    char*           command;    /* the command stored */
    struct tm*      starttime;  /* the start time */
    struct tm*      endtime;    /* the end time */
};

/******************************************************************************
 * @brief   Pointer table
 *****************************************************************************/
static struct nlist *hashtab[HASHSIZE];

/******************************************************************************
 * @brief   The hash function.
 * 
 * @param pid       The process ID to be hashed.
 * 
 * @return  The hash result based on the given process ID.
 *****************************************************************************/
unsigned hash(int pid)
{
    return pid % HASHSIZE;
}

/******************************************************************************
 * @brief   Look for the given pid in hashtab.
 * 
 * @param pid       The pid to look for.
 * 
 * @return  The node with the given pid. If no such node exists, return NULL.
 *****************************************************************************/
struct nlist* lookup(int pid)
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next) {
        if (pid == np->pid) {
            return np;  // found
        }
    }
    return NULL;        // not found
}

/******************************************************************************
 * @brief   Create a duplicate of a given string.
 * 
 * @param s         The string to create duplicate for.
 * 
 * @return  The duplicated string created.
 *****************************************************************************/
char *strdup(char *s)
{
    char* p = (char*) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/******************************************************************************
 * @brief   Insert a new process ID and its command to the hash table. In case
 *          the same process ID already existed in the table, replace its
 *          command and index with the new ones.
 * 
 * @param command       The command.
 * @param pid           The process ID.
 * @param index         The index.
 * 
 * @return  The node inserted (or modified)
 *****************************************************************************/
struct nlist* insert(char* command, int pid, int index)
{
    struct nlist*   np;
    unsigned        hashval;

    /*
    --  Case 1: The pid is not found.
    --  Create the pid using malloc.
    */
    if ((np = lookup(pid)) == NULL) { 
        // create the pid
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->command = strdup(command)) == NULL) {
            return NULL;
        }
        hashval             = hash(pid);
        np->next            = hashtab[hashval];
        hashtab[hashval]    = np;
   }
    /* 
    --  Case 2: The pid is already in the hashslot.
    --  Free the previous command to make room for the new one.
    */
    else {
        free((void*) np->command);
    }

    /*
    --  Assign the command and index to the node.
    */
    if ((np->command = strdup(command)) == NULL) {
        return NULL;
    }
    np->index = index;

    return np;
}
