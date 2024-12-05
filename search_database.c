/***************************************************************************************************************************************************
*Author         : SHARAN
*Date           : 05/12/2024
*File           : search_database.c
*Title          : To search the words
*Description    : This file implements the search_database function. It allows the user to input a word, searches for it in the hash table, and 
                  displays the details of its occurrences, including the file names and word counts for each file where it appears.
****************************************************************************************************************************************************/

#include "inverted_search.h"

int search_database(M_node **hash_table)
{
	char word[100]; // Buffer to store the word to search.
	printf("Enter the word to search: ");
	scanf("%s", word);

	// Find the index in the hash table based on the first character of the word.
	int index = find_index(&word[0]);

	M_node *main_search_node = hash_table[index]; // Pointer to traverse the main nodes at the index.
	while (main_search_node != NULL)
	{
		if (strcmp(main_search_node->word, word) == 0) // If the word matches a main node.
		{
			// Display word and file count information.
			printf("Index: %d\n", index);
			printf("Word: %s\n", main_search_node->word);
			printf("File Count: %d\n", main_search_node->f_count);

			S_node *sub_search_node = main_search_node->s_link; // Pointer to traverse sub-nodes.

			while (sub_search_node != NULL)
			{
				// Display file name and word count for each occurrence.
				printf("File Name: %s\nWord Count: %d\n", sub_search_node->f_name, sub_search_node->w_count);
				sub_search_node = sub_search_node->link; // Move to the next sub-node.
			}
			return SUCCESS; // Word found; return success.
		}
		main_search_node = main_search_node->m_link; // Move to the next main node.
	}
	return FAILURE; // Word not found; return failure.
}
