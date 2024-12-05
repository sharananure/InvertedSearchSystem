/***************************************************************************************************************************************************
*Author         : SHARAN
*Date           : 05/12/2024
*File           : display_database.c
*Title          : To display the results
*Description    : This file contains the implementation of the display_database function. It traverses the hash table and prints all the words, 
                  their file counts, and word occurrences in a structured format. Additional features include selecting the file with the maximum
                  word matches and advanced search options using stored word weightage for more accurate results.
****************************************************************************************************************************************************/

#include "inverted_search.h"

int display_database(M_node **hash_table)
{
    printf("-------------------------------------------------------------\n");
    printf("index     word         f_count     f_name         w_count\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < 28; i++) // Loop through each hash table index
    {
        if (hash_table[i] != NULL) // If there are nodes at this index
        {
            M_node *temp1 = hash_table[i]; // Traverse through all M_nodes at index i
            while (temp1 != NULL)
            {
                // Print the word and its file count
                printf("%-9d%-13s%-12d", i, temp1->word, temp1->f_count);

                // Traverse the S_node list linked from this M_node
                S_node *temp2 = temp1->s_link;
                int first_subnode = 1; // Track whether this is the first subnode for formatting
                while (temp2 != NULL)
                {
                    if (!first_subnode)
                        printf("%-34s", ""); // Indent subsequent subnodes for alignment
                    printf("%-14s%-15d\n", temp2->f_name, temp2->w_count);

                    temp2 = temp2->link; // Move to the next S_node
                    first_subnode = 0;
                }

                printf("-------------------------------------------------------------\n");
                temp1 = temp1->m_link; // Move to the next M_node in the list (linked by m_link)
            }
        }
    }

    return SUCCESS;
}
