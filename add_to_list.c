#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "inverted_search.h"


// Function to insert a new node at the end of a linked list
int add_to_list(flist **head, char *data)
{
    // Allocate memory for a new node
    flist *new_node = malloc(sizeof(flist));
    if (new_node == NULL)
    {                        
        return FAILURE;     //printf("ERROR: Memory allocation failed for new node\n");
    }

    // Copy the file name into the f_name array
    strcpy(new_node->f_name, data);

    new_node->link = NULL;

    // Handle empty list case
    if (*head == NULL)
    {
        *head = new_node;
        //printf("INFO: File %s added to list\n", data);
        return SUCCESS;
    }

    flist *temp = *head;

    // Traverse the list and check for duplicates
    while (temp)
    {
        if (strcmp(temp->f_name, data) == 0)
        {
            //printf("INFO: File %s is a duplicate and won't be added again\n", data);
            free(new_node); // Free the node memory
            return DUPLICATE;
        }
        if (temp->link == NULL) // If we reach the last node
            break;
        temp = temp->link;
    }

    // Append the new node to the end of the list
    temp->link = new_node;
    return SUCCESS;
}
