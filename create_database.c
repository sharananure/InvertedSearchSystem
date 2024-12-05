/***************************************************************************************************************************************************
*Author			: SHARAN
*Date			: 05/12/2024
*File			: create_database.c
*Title			: To create the database
*Description	: This file contains the implementation of the create_database function, which builds the hash table database for the inverted search project.
****************************************************************************************************************************************************/

#include "inverted_search.h"

int create_database(flist *head, M_node **hash_table)
{
	if (head == NULL)
	{
		return FAILURE;
	}

	flist *temp = head; // Pointer to traverse the file list.
	while (temp)
	{
		FILE *fptr = fopen(temp->f_name, "r"); // Open the current file in read mode.
		if (fptr == NULL)
		{
			printf("Could not open file %s \n", temp->f_name);
			return FAILURE;
		}
		char word[50];
		while (fscanf(fptr, "%s", word) == 1) // Read each word from the file.
		{
			// Get the index based on the first character of the word.
			int index = find_index(&word[0]);

			M_node *MainNode = hash_table[index];

			// Search for the word in the hash table.
			while (MainNode != NULL)
			{
				if (strcmp(MainNode->word, word) == 0) // Word found in the hash table.
				{
					// Check if the file is already associated with the word.
					S_node *SubNode = MainNode->s_link;
					while (SubNode != NULL)
					{
						if (strcmp(SubNode->f_name, temp->f_name) == 0)
						{
							// File already associated with the word; increment word count.
							SubNode->w_count++;
							break;
						}
						SubNode = SubNode->link;
					}
					if (SubNode == NULL)
					{
						// File not associated with the word; add a new sub-node.
						S_node *new_sub_node = malloc(sizeof(S_node)); // Create a new sub-node.
						if (new_sub_node == NULL)
						{
							printf("ERROR: Subnode creation Failed\n");
							return FAILURE;
						}

						strcpy(new_sub_node->f_name, temp->f_name);
						new_sub_node->w_count = 1;
						new_sub_node->link = MainNode->s_link;
						MainNode->s_link = new_sub_node;
						MainNode->f_count++;
					}
					break;
				}
				MainNode = MainNode->m_link;
			}
			if (MainNode == NULL)
			{
				// Word not found in the hash table; create new main node and sub-node.
				M_node *new_main_node = (M_node *)malloc(sizeof(M_node)); // Create a new main node.
				if (new_main_node == NULL)
				{
					printf("ERROR: Mainnode creation Failed\n");
					return FAILURE;
				}
				strcpy(new_main_node->word, word);
				new_main_node->f_count = 1;

				S_node *new_sub_node = (S_node *)malloc(sizeof(S_node)); // Create a new sub-node.
				if (new_sub_node == NULL)
				{
					printf("ERROR: Subnode creation Failed\n");
					return FAILURE;
				}
				strcpy(new_sub_node->f_name, temp->f_name);
				new_sub_node->w_count = 1;

				new_main_node->s_link = new_sub_node;
				new_main_node->m_link = hash_table[index];
				hash_table[index] = new_main_node;
			}
		}

		fclose(fptr); // Close the current file.
		temp = temp->link; // Move to the next file in the list.
	}
	return SUCCESS;
}

// Function to find the hash table index based on the first character of a word.
int find_index(char *str)
{
	if (str[0] >= 'a' && str[0] <= 'z')
	{
		return str[0] - 'a';
	}
	else if (str[0] >= 'A' && str[0] <= 'Z')
	{
		return str[0] - 'A';
	}
	else if (str[0] >= '0' && str[0] <= '9')
	{
		return 26; // Index for numerical characters.
	}
	else
	{
		return 27; // Index for special characters.
	}
}
