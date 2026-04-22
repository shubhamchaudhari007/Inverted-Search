/*

Name : Shubham Sanjay Chaudhari
Date : 07 / 12 / 2025
Batch Id: 25021C_306
language : C programming
Project :

💠Inverted Search in C

    The Inverted Search Engine is a file-based search system developed using the C programming language and Data
    Structures. The main goal of this project is to efficiently search for words across multiple text files using
    the Inverted Index technique. Unlike normal searching where each file is scanned individually, an inverted 
    search stores a mapping of every unique word to the list of files in which it appears along with its frequency.

    This project uses a combination of Linked Lists and Hash Tables to implement a fast and memory-efficient 
    inverted index. Each word is stored as a Main Node (M_node) in a hash table, and for each word, a linked list
    of Sub Nodes (S_node) is maintained to store the filenames and the number of occurrences of that word in each 
    file.

The system supports the following operations through a menu-driven interface:
    • Create Database from multiple input text files
    • Display Database in structured format
    • Search for a word across all indexed files
    • Save Database into a file
    • Update Database from a previously saved file

Before creating the database, all input files are validated for:
    • Correct .txt extension
    • File existence
    • Non-empty files
    • Duplicate file entries

    • Each file is parsed word by word, and the database is built using a hash-based indexing technique for fast 
    retrieval. The project also supports saving the database in a structured format and restoring it later, making 
    the system persistent.

Key Features
    • Efficient word-based searching using Inverted Index
    • Supports multiple files
    • Hash Table + Linked List based implementation
    • Fast search performance
    • Persistent storage using Save and Update features
    • Duplicate file prevention
    • Menu-driven and user-friendly interface
    • Handles large datasets efficiently

Applications
    • Search engines
    • Plagiarism detection systems
    • Information retrieval systems
    • Text indexing tools
    • Digital libraries
    • File content searching

Conclusion

    The Inverted Search Engine successfully demonstrates the practical use of Hashing, Linked Lists, File Handling, 
    and Data Structures to build a fast and efficient search mechanism. By converting raw file data into an 
    inverted index, the project reduces search time drastically and provides accurate, file-specific results. This 
    project is an excellent example of a real-world application of data structures in solving complex searching 
    problems.

*/
#include "Inverted.h"   // Header file containing all required structure definitions and prototypes

int main(int argc, char *argv[])
{

    // Check if no file names are passed through command line
    if (argc == 1)
    {
        printf("================================================\n");
        printf("Please enter File Names along with ./a.out \n");   // User guidance message
        printf("Usage : ./a.out <filename.txt> ... \n");          // Proper usage instruction
        printf("================================================\n");
        return 1;   // Exit program if no files are given
    }

    Slist *head = NULL;   // Head pointer for storing validated file names
    validate(argc, argv, &head);   // Validate input files and store in linked list

    H_node hasharr[Hash_Size];     // Declare hash table
    initialize_hash(hasharr);     // Initialize hash table

    int choice;           // Variable to store user menu choice
    char ch;              // Variable to control loop continuation
    int checkcreate = 1;  // Flag to ensure database is created only once
    int checkupdate = 1;  // Flag to ensure database is updated only once

    do
    {
        printf("\n==========================================\n");
        printf("1. Create DataBase\n");   // Menu option 1
        printf("2. Display DataBase\n");  // Menu option 2
        printf("3. Search DataBase\n");   // Menu option 3
        printf("4. Save Database\n");     // Menu option 4
        printf("5. Update DataBase\n");   // Menu option 5
        printf("==========================================\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);   // Read user choice

        switch (choice)
        {
        case 1:
            // Create Database option

            if (create_DB(hasharr, head) == SUCCESS)
            {
                checkcreate = 0;   // Mark database as created
                printf("Creation of database Successfull\n");
                printf("==========================================\n");

            }
            break;

        case 2:
            // Display Database
            Display_DB(hasharr);
            break;

        case 3:
        {
            // Search Database option
            char str[50];   // Buffer to store search word
            printf("Enter the Word You want to search : ");
            scanf(" %s", str);   // Read word to be searched
            Search_DB(hasharr, str);   // Perform search
        }
        break;

        case 4:
            // Save Database to file
            if (Save_DB(hasharr) == SUCCESS)
            {
                printf("Data Saved Successfull \n");
                printf("==========================================\n");
            }
            break;

        case 5:
            // Update Database from saved file
            if (checkcreate)     // Update only if database is not created already
            {
                if (checkupdate)   // Ensure update happens only once
                {
                    if (Update_DB(hasharr, &head) == SUCCESS)
                    {
                        printf("DataBase Updated SuccessFully\n");
                        checkupdate = 0;   // Mark update as completed
                    }else{
                        printf("\n Failed to Update \n");   // Update failed message
                    }
                }else{
                    printf("DataBase already updated \n");   // Prevent repeated updates
                }
            }else{
                printf("DataBase Created Then we can not update database with another file \n");
            }
            printf("==========================================\n");

            break;

        default:
            printf("Invalid Choice\n");   // Invalid menu choice message
        }

        printf("Do You Want To Continue ? \n");
        printf("Enter Y/y to continue or n/N to discontinue.\n");
        getchar();            // Consume leftover newline character
        scanf("%c", &ch);    // Read user continuation choice

    } while (ch != 'N' && ch != 'n');   // Loop until user chooses to exit
    
    freeDatabase(hasharr);      //free the memory of hash table and nodes
    freeFileList(head);         //free memory of linked list
}
