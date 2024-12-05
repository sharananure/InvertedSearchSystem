/***************************************************************************************************************************************************
*Author			: SHARAN
*Date			: 05/12/2024
*File			: database_functions.c
*Title			: Data Structures and Prototypes
*Description	: This file contains the definitions of structures and function prototypes used in the inverted search project.
****************************************************************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define SUCCESS 0  
#define FAILURE -1 
#define DUPLICATE -2 

// Structure representing an entry in the hash table.
typedef struct hash_table
{
    int index; // Index in the hash table.
    struct MainNode* link; // Pointer to the main node linked to this index.
} hash_t;

// Structure representing a node in the file list.
typedef struct file
{
    char f_name[25]; // Name of the file.
    struct file* link; // Pointer to the next file in the list.
} flist;

// Structure representing the main node in the hash table.
typedef struct MainNode
{
    char word[20]; // Word stored in the node.
    int f_count; // Count of files where this word appears.
    struct MainNode* m_link; // Pointer to the next main node.
    struct SubNode* s_link; // Pointer to the list of sub-nodes.
} M_node;

// Structure representing a sub-node linked to a main node.
typedef struct SubNode
{
    char f_name[20]; // Name of the file containing the word.
    int w_count; // Count of occurrences of the word in the file.
    struct SubNode* link; // Pointer to the next sub-node.
} S_node;

// Function prototypes.
int read_and_validate(int argc, char* argv[], flist** head); // Validates and reads input file names into a linked list.
int duplicate(flist *head, char* filename); // Checks for duplicate file names in the list.
int add_to_list(flist **head, char *filename); // Adds a file name to the linked list.
void print_list(flist* head); // Prints the file list.
int find_index(char *str); // Finds the index of a word in the hash table.
char* strdup(const char *src); // Duplicates a string (used as an alternative to strdup).

// Functions for database operations.
int create_database(flist *head, M_node **hash_table); // Creates the database from the file list.
int display_database(M_node **hash_table); // Displays the contents of the database.
int search_database(M_node **hash_table); // Searches for a word in the database.
int save_database(M_node **hash_table); // Saves the database to a file.
int update_database(M_node **hash_table); // Updates the database with new entries.
