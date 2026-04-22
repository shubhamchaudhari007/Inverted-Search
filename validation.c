#include "Inverted.h"   // Header file containing structure definitions and function prototypes

// Function to validate input files passed through command-line arguments
Status validate(int argc, char *argv[], Slist **head)
{
    printf("==========================================\n");
    printf("%-15s","Validating Files\n");   // Display validation heading
    printf("==========================================\n");

    // Loop through all input files (starting from argv[1])
    for (int i = 1; i < argc; i++)
    {
        // Check whether file has valid .txt extension
        if (checkExtension(argv[i]) == SUCCESS)
        {

            FILE *fp;   // File pointer for opening file
            fp = fopen(argv[i], "r");   // Open file in read mode

            // Check if file opened successfully
            if (fp != NULL)
            {
                // Check whether file is not empty
                if (FilenotEmpty(fp) == SUCCESS)
                {

                    // Check whether file is already present in linked list
                    if (DuplicateFile(*head, argv[i]) != SUCCESS)
                    {
                        // Store file name into linked list
                        if(storeFileLL(head, argv[i]) == SUCCESS){
                        
                            printf("Info : %s read SuccessFully \n", argv[i]);   // Success message
    
                        }else{
                            printf("Fail to store %s \n",argv[i]);
                        }
                        
                    }
                    else
                    {
                        // Error message if duplicate file is found
                        printf("Error : %s given File Already Present \n", argv[i]);
                        continue;   // Skip to next file
                    }
                }
                else
                {
                    // Error message if file is empty
                    printf("Error : File %s is Empty\n", argv[i]);
                    continue;   // Skip to next file
                }
            }
            else
            {
                // Error message if file does not exist or cannot be opened
                printf("Error : Can not read %s file it not exist in directory \n", argv[i]);
                continue;   // Skip to next file
            }

            fclose(fp);   // Close the opened file
        }
        else
        {
            // Error message if file extension is not .txt
            printf("Error : extension Mismatch %s file must Contains .txt extension \n",argv[i]);
            continue;   // Skip to next file
        }
    }

    //return FAILURE;   // Previously considered failure return (currently not used)
    printf("==========================================\n");

    return SUCCESS;   // Return success after validating all files
}
