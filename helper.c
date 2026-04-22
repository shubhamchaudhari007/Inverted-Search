#include "Inverted.h"   // Header file containing structure definitions and function prototypes

// Function to check whether the given file has ".txt" extension
Status checkExtension(char *str)
{
    int len = strlen(str);        // Get length of the filename string
    char *ext = ".txt";          // Required file extension
    if(len < 4)
        return FAILURE;
    // Compare last 4 characters of filename with ".txt"
    if (!strcmp(&str[len - 4], ext))
    {
        return SUCCESS;         // Extension matched
    }
    return FAILURE;             // Extension mismatch
}

// Function to check whether a file is empty or not
Status FilenotEmpty(FILE *fp)
{
    if(fp == NULL){
        return FAILURE;
    }
    fseek(fp, 0, SEEK_END);      // Move file pointer to end of file

    // If file size is zero, file is empty
    if (ftell(fp) == 0)
    {
        return FAILURE;         // File is empty
    }

    rewind(fp);                 // Reset file pointer to beginning
    return SUCCESS;             // File is not empty
}

// Function to check whether a file name is already present in the linked list
Status DuplicateFile(Slist *head, char *str)
{

    // If list is empty, no duplicate exists
    if (head == NULL)
    {
        return FAILURE;
    }
    else
    {
        Slist *temp = head;     // Temporary pointer to traverse list

        // Traverse through the list to check for duplicate filename
        while (temp != NULL)
        {
            if (!strcmp(temp->filename, str))   // Compare stored filename with given filename
            {
                return SUCCESS;   // Duplicate found
            }
            temp = temp->link;   // Move to next node
        }
        return FAILURE;          // No duplicate found
    }
}

// Function to store a validated file name into the linked list
Status storeFileLL(Slist **head, char *str)
{
    Slist *new = malloc(sizeof(Slist));   // Allocate memory for new node
    if(new == NULL){
        return FAILURE;
    }
    strcpy(new->filename, str);           // Copy filename into node
    new->link = NULL;                     // Initialize link to NULL

    // If linked list is empty, new node becomes head
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        Slist *temp = *head;              // Temporary pointer for traversal

        // Traverse to the last node
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;                 // Attach new node at the end
    }
    return SUCCESS;                        // Return success after storing file
}

// Function to initialize the hash table
Status initialize_hash(H_node *arr)
{
    // Loop through all hash indices
    for (int i = 0; i < Hash_Size; i++)
    {
        arr[i].index = i;      // Assign index number
        arr[i].mlink = NULL;  // Initialize main node link as NULL
    }
    return SUCCESS;            // Hash table initialized successfully
}

// Function to create a main node for inverted index
M_node *create_Main_node(char *str)
{
    M_node *new = (M_node *)malloc(sizeof(M_node));   // Allocate memory for main node
    strcpy(new->word, str);                           // Store word
    new->no_file = 1;                                 // Initialize file count to 1
    new->slink = NULL;                                // Initialize sub list pointer
    new->mlink = NULL;                                // Initialize main link pointer
    return new;                                       // Return created main node
}

// Function to create a sub node for file-wise word count
S_node *create_sub_node(char *str)
{
    S_node *new = (S_node *)malloc(sizeof(S_node));   // Allocate memory for sub node
    strcpy(new->File_name, str);                      // Store file name
    new->no_words = 1;                                // Initialize word count to 1
    new->slink = NULL;                                // Initialize next sub node pointer
    return new;                                       // Return created sub node
}

// Function to remove a duplicate filename from the linked list
Status removeDuplicate(Slist **head, char *str)
{
    Slist *temp = *head;    // Temporary pointer to traverse list
    Slist *prev = NULL;    // Pointer to store previous node
    int flag = 0;          // Flag to check whether duplicate is found

    // Traverse list to find matching filename
    while (temp != NULL)
    {
        if (!strcmp(temp->filename, str))   // Duplicate found
        {
            flag = 1;
            break;
        }
        prev = temp;
        temp = temp->link;
    }

    // If duplicate was found
    if (flag)
    {
        // If duplicate is at head
        if (prev == NULL)
        {
            *head = (*head)->link;   // Move head to next node
            free(temp);              // Free duplicate node
        }
        else
        {
            prev->link = temp->link; // Bypass duplicate node
            free(temp);              // Free duplicate node
        }
    }
    else
    {
        return FAILURE;              // Duplicate not found
    }
    return SUCCESS;                  // Duplicate removed successfully
}

// Function to check whether file is valid based on special format
Status checkFiletype(FILE *fp)
{
    char ch1, ch2, ch3;   // Variables to hold first and last characters

    ch1 = fgetc(fp);            // Read first character to validate format

    fseek(fp, -3, SEEK_END);    // Move file pointer to second last position
    ch2 = fgetc(fp);            // Read second last character
    ch3 = fgetc(fp);
    // Check whether file begins and ends with '#'
    if (ch1 == '#' && ch2 == '|' && ch3 == '#')
    {
        rewind(fp);             // Reset file pointer to beginning
        return SUCCESS;         // File format is valid
    }
    else
    {
        rewind(fp);             // Reset file pointer to beginning
        return FAILURE;         // File format is invalid
    }
}

void freeFileList(Slist *head)      //free the memory of linked list
{
    Slist *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->link;
        free(temp);
    }
}

void freeDatabase(H_node *hasharr)      //free the memory of hash table and the main node and sub node also
{
    for (int i = 0; i < Hash_Size; i++)
    {
        M_node *mtemp = hasharr[i].mlink;
        while (mtemp != NULL)
        {
            S_node *stemp = mtemp->slink;
            while (stemp != NULL)
            {
                S_node *sdel = stemp;
                stemp = stemp->slink;
                free(sdel);   //  free sub node
            }

            M_node *mdel = mtemp;
            mtemp = mtemp->mlink;
            free(mdel);   //  free main node
        }
        hasharr[i].mlink = NULL;
    }
}
