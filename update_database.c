/***************************************************************************************************************************************************
*Author         : SHARAN
*Date           : 05/12/2024
*File           : update_database.c
*Title          : To Update the Data with Enhanced Validation
*Description    : This file contains the implementation of the update_database function. It reads a backup file, validates its content, and updates
                  the hash table with new main nodes and their associated sub-nodes. Proper error handling and memory management ensure robustness.
****************************************************************************************************************************************************/

#include "inverted_search.h"

// Function to check if a string represents a number manually
int is_digit(char *str) 
{
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] < '0' || str[i] > '9') 
        {
            return 0; // False if any character is not a digit
        }
    }
    return 1; // True if all characters are digits
}

int update_database(M_node **hash_table) 
{
    char f_name[50];
    printf("Enter the backup file name: ");
    scanf("%s", f_name);

    FILE *fptr = fopen(f_name, "r");
    if (fptr == NULL) 
    {
        printf("ERROR: Could not open file %s\n", f_name);
        return FAILURE;
    }

    if (strstr(f_name, ".txt") == NULL) 
    {
        printf("ERROR: File %s is not a text file\n", f_name);
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);

    if (size == 0) 
    {
        printf("ERROR: File %s is empty.\n", f_name);
        return FAILURE;
    }

    char str[200];

    while (fgets(str, sizeof(str), fptr) != NULL) 
    {
        // Check if the line starts with '#'
        if (str[0] != '#') 
        {
            printf("ERROR: Invalid format. Line does not start with '#'.\n");
            return FAILURE;
        }

        // Tokenize and validate
        char *token = strtok(&str[1], ";"); // Skip '#'

        if (token == NULL || is_digit(token) == 0) 
        {
            printf("ERROR: Invalid index format.\n");
            return FAILURE;
        }
        int index = atoi(token); // Convert index to integer

        token = strtok(NULL, ";");
        if (token == NULL || strlen(token) == 0) 
        {
            printf("ERROR: Missing or invalid word.\n");
            return FAILURE;
        }
        char word[50];
        strcpy(word, token); // Store the word

        token = strtok(NULL, ";");
        if (token == NULL || is_digit(token) == 0) 
        {
            printf("ERROR: Invalid file count.\n");
            return FAILURE;
        }
        int f_count = atoi(token); // Convert file count to integer

        // Allocate memory for a new main node
        M_node *New_MainNode = malloc(sizeof(M_node));
        if (New_MainNode == NULL) 
        {
            printf("ERROR: Could not allocate memory for new Main Node.\n");
            return FAILURE;
        }
        strcpy(New_MainNode->word, word);
        New_MainNode->f_count = f_count;
        New_MainNode->s_link = NULL;
        New_MainNode->m_link = NULL;

        // Loop through file details
        for (int i = 0; i < f_count; i++) 
        {
            token = strtok(NULL, ";");
            if (token == NULL || strlen(token) == 0) 
            {
                printf("ERROR: Missing or invalid file name.\n");
                return FAILURE;
            }
            char file_name[50];
            strcpy(file_name, token);

            token = strtok(NULL, ";");
            if (token == NULL || is_digit(token) == 0) 
            {
                printf("ERROR: Invalid word count.\n");
                return FAILURE;
            }
            int w_count = atoi(token); // Convert word count to integer

            // Allocate memory for a new sub node
            S_node *New_SubNode = malloc(sizeof(S_node));
            if (New_SubNode == NULL) 
            {
                printf("ERROR: Could not allocate memory for Sub Node.\n");
                return FAILURE;
            }

            strcpy(New_SubNode->f_name, file_name);
            New_SubNode->w_count = w_count;
            New_SubNode->link = NULL;

            // Add sub node to the main node's sub-node list
            if (New_MainNode->s_link == NULL) 
            {
                New_MainNode->s_link = New_SubNode;
            } 
            else 
            {
                S_node *temp = New_MainNode->s_link;
                while (temp->link != NULL) 
                {
                    temp = temp->link;
                }
                temp->link = New_SubNode;
            }
        }

        // Add main node to the hash table
        if (hash_table[index] == NULL) 
        {
            hash_table[index] = New_MainNode;
        } 
        else 
        {
            M_node *temp = hash_table[index];
            while (temp->m_link != NULL) 
            {
                temp = temp->m_link;
            }
            temp->m_link = New_MainNode;
        }
    }

    fclose(fptr);
    return SUCCESS;
}
