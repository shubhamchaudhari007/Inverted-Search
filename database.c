#include "Inverted.h"   // Header file containing all required structure definitions and prototypes

// Function to create the inverted index database using hash table and file list
Status create_DB(H_node *hasharr, Slist *head)
{
    Slist *currhead = head;   // Pointer to traverse through the file linked list

    // Loop through all the files in the linked list
    while (currhead != NULL)
    {
        printf("\n============================================================\n");
        printf("Processing file: %s\n", currhead->filename);

        FILE *fp = fopen(currhead->filename, "r");   // Open the current file in read mode
        if (fp == NULL)
        {
            printf("Error : Failure to open %s file\n", currhead->filename);
            currhead = currhead->link;
            continue;   // Skip this file if it cannot be opened
        }

        char buffer[100];   // Buffer to store each word read from file

        // Read each word from the file
        while (fscanf(fp, "%s", buffer) != EOF)
        {
            int index;

            // Calculate hash index based on first character of the word
            if (isupper(buffer[0]))
            {
                index = buffer[0] - 65;
            }
            else if (islower(buffer[0]))
            {
                index = buffer[0] - 97;
            }
            else
            {
                index = 26;   // Special index for non-alphabet characters
            }

            // If no main node exists at this hash index
            if (hasharr[index].mlink == NULL)
            {
                M_node *M_new = create_Main_node(buffer);   // Create new main node for the word

                S_node *S_new1 = create_sub_node(currhead->filename);  // Create sub node for file
                M_new->slink = S_new1;                       // Link sub node to main node
                hasharr[index].mlink = M_new;                // Store main node in hash table
            }
            else
            {
                int flag = 0;         // Flag to check if word already exists
                M_node *temp = hasharr[index].mlink;
                M_node *M_backup = NULL;
                M_node *prev_M = NULL;

                // Traverse main linked list for the word
                while (temp != NULL)
                {
                    if (!strcmp(temp->word, buffer))
                    {
                        flag = 1;      // Word found
                        M_backup = temp;
                    }
                    prev_M = temp;
                    temp = temp->mlink;
                }

                // If word already exists
                if (flag)
                {
                    S_node *temp2 = M_backup->slink;
                    int flag1 = 0;     // Flag to check if file already exists for that word
                    S_node *S_backup = NULL;
                    S_node *prev_s = NULL;

                    // Traverse sub node list
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp2->File_name, currhead->filename))
                        {
                            flag1 = 1;     // File already exists
                            S_backup = temp2;
                        }
                        prev_s = temp2;
                        temp2 = temp2->slink;
                    }

                    // If file is already present, increment word count
                    if (flag1)
                    {
                        S_backup->no_words += 1;
                    }
                    else
                    {
                        // Create new sub node for a new file
                        S_node *new2 = create_sub_node(currhead->filename);
                        M_backup->no_file += 1;

                        if (prev_s == NULL)
                        {
                            M_backup->slink = new2;
                        }
                        else
                        {
                            prev_s->slink = new2;
                        }
                    }
                }
                else
                {
                    // If word is not already present, create new main and sub nodes
                    M_node *new_M = create_Main_node(buffer);

                    S_node *new_s = create_sub_node(currhead->filename);

                    new_M->slink = new_s;      // Link sub node to main node
                    prev_M->mlink = new_M;    // Attach new main node at end
                }
            }
        }

        fclose(fp);   // Close the current file
        printf("SUCCESSFUL creation of database for file : %s ", currhead->filename);

        currhead = currhead->link;   // Move to next file
    }

    printf("\n============================================================\n");
    return SUCCESS;   // Database creation completed successfully
}

// Function to display the entire inverted index database
Status Display_DB(H_node *hasharr)
{
    printf("====================================================================================\n");
    printf("%-6s | %-20s | %-10s | %-20s\n",
           "Index", "Word", "File Count", "Files (FileName : Count)");
    printf("====================================================================================\n");

    // Traverse through hash table
    for (int i = 0; i < Hash_Size; i++)
    {
        if (hasharr[i].mlink != NULL)
        {
            M_node *temp = hasharr[i].mlink;

            // Traverse main node list at each index
            while (temp != NULL)
            {
                printf("%-6d | %-20s | %-10d | ", hasharr[i].index, temp->word, temp->no_file);

                S_node *temp2 = temp->slink;
                int first = 1;

                // Traverse sub node list for each word
                while (temp2 != NULL)
                {
                    if (!first)
                        printf("                                           | ");

                    printf("%-12s : %-3d\n", temp2->File_name, temp2->no_words);

                    first = 0;
                    temp2 = temp2->slink;
                }

                printf("\n");
                temp = temp->mlink;
            }
        }
    }

    printf("====================================================================================\n");
    return SUCCESS;   // Display completed successfully
}

// Function to search a word in the database
Status Search_DB(H_node *hasharr, char *str)
{
    int index;

    // Calculate hash index based on first character of the word
    if (isupper(str[0]))
    {
        index = str[0] - 65;
    }
    else if (islower(str[0]))
    {
        index = str[0] - 97;
    }
    else
    {
        index = 26;
    }

    int found = 0;   // Flag to check if word is found
    M_node *M_temp = hasharr[index].mlink;

    printf("==========================================\n");

    // Traverse main node list for given index
    while (M_temp != NULL)
    {
        if (!strcmp(M_temp->word, str))
        {
            printf("Word %s is present in %d files \n", str, M_temp->no_file);

            S_node *s_temp = M_temp->slink;
            found = 1;

            // Traverse sub node list to display file-wise count
            while (s_temp != NULL)
            {
                printf("In File : %s  %d times\n", s_temp->File_name, s_temp->no_words);
                s_temp = s_temp->slink;
            }
        }
        M_temp = M_temp->mlink;
    }

    // If word is not found in database
    if (!found)
    {
        printf("Word %s not found in database\n", str);
    }

    printf("==========================================\n");
    return SUCCESS;
}

// Function to save the database into a file
Status Save_DB(H_node *hasharr)
{
    char str[100];

    printf("Enter File Name : \n");
    scanf(" %s", str);

    // Validate file extension before saving
    if (checkExtension(str) == SUCCESS)
    {
        FILE *fp;
        fp = fopen(str, "w");   // Open file in write mode
        if(fp == NULL)
            return FAILURE;
        // Traverse through hash table and store data
        for (int i = 0; i < Hash_Size; i++)
        {

            if (hasharr[i].mlink != NULL)
            {
                M_node *mtemp = hasharr[i].mlink;

                while (mtemp != NULL)
                {
                    fprintf(fp, "#%d|%s|%d|", i, mtemp->word, mtemp->no_file);

                    S_node *stemp = mtemp->slink;

                    // Write all sub node data
                    while (stemp != NULL)
                    {
                        fprintf(fp, "%s|%d|", stemp->File_name, stemp->no_words);
                        stemp = stemp->slink;
                    }

                    fprintf(fp, "#\n");
                    mtemp = mtemp->mlink;
                }
            }
        }

        fclose(fp);   // Close file after saving
    }
    else
    {
        printf("File Extension Mismatch file Should contains .txt Extension\n");
        return FAILURE;
    }

    return SUCCESS;
}

// Function to update the database from an existing saved file
Status Update_DB(H_node *hasharr, Slist **head)
{
    char str[100];

    printf("Enter File Name for Update \n");
    scanf(" %[^\n]", str);

    // Validate file extension
    if(checkExtension(str) != SUCCESS){
        printf("File Extension Mismatch file Should contains .txt Extension\n");
        return FAILURE;
    }

    FILE *fp;
    fp = fopen(str, "r");   // Open file in read mode
    if(fp == NULL)
        return FAILURE;
    // Check if file is empty
    if(FilenotEmpty(fp) == FAILURE){
        printf("File is Empty Can not update the data\n");
        return FAILURE;
    }

    int indexu;

    // Validate whether file follows correct database format
    if (checkFiletype(fp) == SUCCESS)
    {

        // Read data from file and update database
        while (fscanf(fp, "#%d|", &indexu) == 1)
        {

            M_node *new = malloc(sizeof(M_node));
            if(new == NULL)
                return FAILURE;
            fscanf(fp, "%[^|]|%d|", new->word, &new->no_file);
            new->mlink = NULL;
            new->slink = NULL;

            // Insert new main node into hash table
            if (hasharr[indexu].mlink == NULL)
                hasharr[indexu].mlink = new;
            else
            {
                M_node *mtemp = hasharr[indexu].mlink;
                while (mtemp->mlink != NULL)
                {
                    mtemp = mtemp->mlink;
                }
                mtemp->mlink = new;
            }

            S_node *stemp;

            // Read and insert all corresponding sub nodes
            for (int i = 0; i < new->no_file; i++)
            {
                S_node *snew = malloc(sizeof(S_node));
                if(snew == NULL)
                    return FAILURE;
                fscanf(fp, "%[^|]|%d|", snew->File_name, &snew->no_words);

                // Remove duplicate file names from file list
                if (DuplicateFile(*head, snew->File_name) == SUCCESS)
                {
                    removeDuplicate(head, snew->File_name);
                }

                snew->slink = NULL;

                if (new->slink == NULL)
                    new->slink = snew;
                else
                {
                    stemp = new->slink;
                    while (stemp->slink != NULL)
                    {
                        stemp = stemp->slink;
                    }
                    stemp->slink = snew;
                }
            }

            fscanf(fp, "#\n");   // Skip ending marker
        }

        fclose(fp);   // Close update file
    }
    else
    {
        printf("File Data is Not matching with Format , Invalid File data \n");
        return FAILURE;
    }

    return SUCCESS;   // Update completed successfully
}
