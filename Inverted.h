#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define Hash_Size 27

typedef enum sts{
    FAILURE,
    SUCCESS
}Status;

typedef struct Sub_node{
    int no_words;
    char File_name[50];
    struct Sub_node *slink; 
}S_node;

typedef struct Main_node{
    int no_file;
    char word[30];
    struct Sub_node *slink;
    struct Main_node *mlink;   
}M_node;

typedef struct hash_node{
    int index;
    struct Main_node *mlink;
}H_node;

typedef struct node{
    char filename[50];
    struct node *link;
}Slist;

Status checkExtension(char *str);
Status FilenotEmpty(FILE *fp);
Status storeFileLL(Slist **head, char *str);
Status DuplicateFile(Slist *head, char *str);
Status validate(int argc, char *argv[], Slist **head);
Status initialize_hash(H_node *arr);
Status create_DB(H_node *hasharr,Slist *head);
Status Display_DB(H_node *hasharr);
Status Update_DB(H_node *hasharr,Slist **head);
Status Save_DB(H_node *hasharr);
Status Search_DB(H_node *hasharr,char *str);
S_node *create_sub_node(char *str);
M_node *create_Main_node(char *str);
Status removeDuplicate(Slist **head, char *str);
Status checkFiletype(FILE *fp);
void freeDatabase(H_node *hasharr);
void freeFileList(Slist *head);

#endif