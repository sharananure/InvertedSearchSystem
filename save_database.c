/***************************************************************************************************************************************************
*Author         : SHARAN
*Date           : 05/12/2024
*File           : save_database.c
*Title          : To Save the Data
*Description    : This file contains the implementation of the save_database function. It writes the hash table contents to a user-specified .txt file.
                  The function ensures that the data is stored in a structured format for future use and validates the file name for correctness.
****************************************************************************************************************************************************/

#include "inverted_search.h"

int save_database(M_node **hash_table)
{
    char backup[50]; // Buffer to store the backup file name.
    printf("Enter the file name to save the database: ");
    scanf("%s", backup);

    // Open the file in write mode.
    FILE *fptr  = fopen(backup, "w");

    if (strstr(backup, ".txt") != NULL) // Validate if the file name ends with .txt.
    {
        for (int i = 0; i < 28; i++) // Iterate through each hash table index.
        {
            if (hash_table[i] != NULL) // If there are nodes at this index.
            {
                M_node *mainNode = hash_table[i]; // Traverse through all main nodes at index i.
                while (mainNode != NULL)
                {
                    // Write the main node information to the file.
                    fprintf(fptr,"#%d;", i);
                    fprintf(fptr, "%s;", mainNode->word);
                    fprintf(fptr, "%d;", mainNode->f_count);

                    S_node *subNode = mainNode->s_link; // Traverse the sub-node list linked to the main node.
                    while (subNode != NULL)
                    {
                        // Write sub-node information to the file.
                        fprintf(fptr, "%s;", subNode->f_name);
                        fprintf(fptr, "%d;", subNode->w_count);
                        subNode = subNode->link; // Move to the next sub-node.
                    }
                    fputs("#\n", fptr); // Mark the end of the main node entry.
                    mainNode = mainNode->m_link; // Move to the next main node.
                }
            }
        } 
    }
    else
    {
        printf("Invalid file name. Please enter a .txt file name.\n");
        return FAILURE;
    }

    fclose(fptr); // Close the file after writing.
    return SUCCESS;
}
