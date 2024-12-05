# Inverted Search System


/***************************************************************************************************************************************************
* Author         : Sharan
* Date           : 05/12/2024
* File           : Various source files (.c) in the project
* Title          : Inverted Search System
* Description    : This project implements an Inverted Search system for efficient text-based searching by indexing words across multiple files. 
*                  The system supports database creation, updating, searching, displaying, and backup functionalities to manage large datasets 
*                  effectively.
***************************************************************************************************************************************************/

# 🚀 Project Overview
  The Inverted Search System is a C-based application designed to efficiently search for words across multiple text files using an 
  inverted index data structure. It processes input files, indexes words, and provides fast search capabilities, making it ideal 
  for handling large datasets.

# ✨ Features
  - Create an Inverted Index from multiple text files.
  - Efficient search capabilities for quick retrieval.
  - Display the entire database (index) for user review.
  - Update the index with new words or files dynamically.
  - Save and restore the database from a backup file.

# 📁 File Structure
   Inverted_Search/
       main.c                   // Main driver program
       create_database.c         // Handles inverted index creation
       add_to_list.c             // Manages addition of new words to index
       display_database.c        // Displays the complete inverted index
       search_database.c         // Handles word search operations
       update_database.c         // Updates the database with new files/words
       save_database.c           // Saves the current database to a file
       validation.c              // Validates user inputs and file integrity
       inverted_search.h         // Header file containing function prototypes
       f1.txt, f2.txt            // Sample text files for demonstration
       backup.txt                // Backup file for database restoration
       makefile                  // Automates build process using make
       README.md                 // Project documentation


