/***************************************************************************************************************************************************
*Author         : SHARAN
*Date           : 05/12/2024
*File           : validation.c
*Title          : To Validate Input Files with Enhanced Error Handling
*Description    : This file contains the implementation of the read_and_validate function. It reads input files, validates their existence, 
*                 checks for proper file extensions, ensures that files are not empty, and adds valid files to a linked list. 
*                 The function handles errors such as missing files, invalid file types, and empty files with appropriate messages.
***************************************************************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "inverted_search.h"

// Function to read input files and validate them
int read_and_validate(int argc, char* argv[], flist** head)
{
    int valid_files = 0;  // Counter for valid files

    // Check if no input files are provided
    if(argc <= 1)
    {
        printf("ERROR: No input files provided\n");
        return FAILURE;  // Return failure if no files are given
    }

    FILE *file = NULL;  // Pointer for file handling

    // Loop through each argument passed (which are filenames)
    for(int i = 1; i < argc; i++)
    {
        char *filename = argv[i];  // Current filename
        file = fopen(argv[i], "r");  // Try to open the file in read mode
        
        // Check if the file could not be opened
        if(file == NULL)
        {
            printf("ERROR: file -> %s is not present in directory\n", filename);
            continue;  // Skip to the next file if the current one can't be opened
        }
        
        // Check if the file has a .txt extension
        if(strstr(filename, ".txt") != NULL)
        {
            fseek(file, 0, SEEK_END);  // Move the file pointer to the end
            int size = ftell(file);  // Get the size of the file
            rewind(file);  // Move the file pointer back to the beginning

            // If the file size is greater than 0, attempt to add it to the list
            if(size > 0)
            {
                // Add the file to the list if not a duplicate
                if(add_to_list(head, filename) == SUCCESS)
                {
                    printf("INFO: File -> %s added to list\n", filename);
                    valid_files++;  // Increment valid files counter
                }
                else if(add_to_list(head, filename) == DUPLICATE)
                {
                    printf("INFO: File -> %s is a duplicate and won't be added again\n", filename);
                }
                else
                {
                    printf("ERROR: File -> %s could not be added to list\n", filename);
                }
            }
            else  // If the file is empty
            {
                if(add_to_list(head, filename) == DUPLICATE)
                {
                    printf("INFO: File -> %s is a duplicate and won't be added again\n", filename);
                }
                else
                {
                    printf("ERROR: File -> %s is empty\n", filename);
                }
            }
    
        }
        else  // If the file does not have a .txt extension
        {
            printf("ERROR: File -> %s is not a .txt file\n", filename);
        }

    }
    
    // If at least one valid file was added, return SUCCESS, otherwise FAILURE
    if (valid_files > 0)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}
