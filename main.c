/***************************************************************************************************************************************************
*Author			:	SHARAN
*Date			:	05/12/2024
*File			:	main.c
*Title			:	Driver function
*Description	:	This function acts like the driver function for the project inverted search
****************************************************************************************************************************************************/
#include "inverted_search.h"


int main(int argc, char *argv[])
{
	flist* filelist = NULL;		// Initialize a linked list to store file names.
	M_node *hash_table[28] = {NULL};

	if(read_and_validate(argc,argv,&filelist) != SUCCESS)
	{
		printf("ERROR: Read and Validation Failed\n");

	}
	else  
	{
		printf("INFO: Read and Validation Completed Successfully\n");
		int choice;
		int flag1 = 0 , flag2 = 0;
		do
		{
			printf("---------- MAIN MENU ----------\n");
	    	printf("Select your choice among following options: \n1. CREATE DATABASE\n2. DISPLAY DATABASE\n3. SEARCH DATABASE\n4. SAVE DATABASE\n5. UPDATE DATABASE\n6. EXIT\nEnter your choice: ");
	    	scanf("%d",&choice);
			switch (choice)
			{
				case 1:
					if (flag1 == 1 && flag2 == 1)
					{
						printf("INFO DATABASE ALREADY EXISTS\n");
					}
					else if(create_database(filelist,hash_table) == SUCCESS)
					{
						flag1 = 1;
						printf("INFO: Database created successfully\n");
					}
					else
					{
						printf("ERROR: Database creation failed\n");
					}
				break;
				case 2:
					if(flag1 == 0 && flag2 == 0)		// if database not created then display error message
					{
						printf("ERROR: Can't Display, as Database Empty\n");
					}
					else if(display_database(hash_table) == SUCCESS)
					{
						printf("INFO: Database Displayed successfully\n");
					}
					else
					{
						printf("ERROR: Database Display failed\n");
					}
					break;
				case 3:
					if(flag1 == 0 && flag2 == 0)		// if database not created then display error message
					{
						printf("ERROR: Can't Search, as Database Empty\n");
					}
					else if(search_database(hash_table) == SUCCESS)
					{
						printf("INFO: Search completed successfully\n");
					}
					else
					{
						printf("ERROR: Search failed\n");
					}
					break;
				case 4:
					if(flag1 == 0 && flag2 == 0)		// if database not created then display error message
					{
						printf("ERROR: Can't Save, as Database Empty\n");
					}
					else if(save_database(hash_table) == SUCCESS)
					{
						printf("INFO: Database saved successfully\n");
					}
					else
					{
						printf("ERROR: Database saving failed\n");
					}
					break;
				case 5:
					if (flag1 == 1)
					{
						printf("ERROR: Cannot update database since the database has already been created\n");
					}
					else if(update_database(hash_table) == SUCCESS)
					{
						printf("INFO: Database updated successfully\n");
						flag2 = 1;
					}
					else
					{
						printf("ERROR: Database update failed\n");
					}
					break;
					default:
					{
						printf("ERROR: Invalid choice\n");
					}
					break;
			}
		} while (choice != 6);
	}
}

