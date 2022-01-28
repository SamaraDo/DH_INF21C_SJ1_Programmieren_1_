#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
    printf("end of function\n");
}

void printList(listElement *start)
{

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\nCurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n\n\n", currElem->age);
        } while (currElem->nextElem != NULL);
    }
    printf("\n");
}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void delListElem(listElement *start){
    int numberOfToDelElem = 0;
    int isNumberInLst = 0; 
    listElement *currElem = start;
    listElement *PointertonextnextElem = start;
     if (start->nextElem == NULL) {printf("-------------------------------------\n| No Elements, that can be deleted. |\n-------------------------------------\n\n\n");} 
     else {printList(start);
      printf("--------------------------------------------------------------------------------------\n| Please type in the number of the Element that you want to delete (starting with 0) |\n--------------------------------------------------------------------------------------\n\n\n");
      isNumberInLst = scanf("%d", &numberOfToDelElem);
    if (isNumberInLst == 0 || numberOfToDelElem < 0 || numberOfToDelElem > getLenOfList(start)){
        printf("-----------------------------------------------------\n! Please enter the Number of an Element in the List. !\n-----------------------------------------------------\n\n\n");
    }
    else{
     for (int i = 0; i < numberOfToDelElem; i++) {
         if (currElem == NULL || currElem->nextElem == NULL){
             printf("----------------------------------------------------------\n! The element, that should be deleted is not in the list !----------------------------------------------------------\n\n\n"); }
         else{
              currElem = currElem->nextElem;
         } } 
      PointertonextnextElem = currElem->nextElem->nextElem;
      free(currElem->nextElem);
      currElem->nextElem = PointertonextnextElem; 
    printf("--------------------\n| Element deleted. |\n| New List:        |\n--------------------\n\n\n");
    printList(start);}}}

void delList(listElement *start)
{
    int choice = 0;
    listElement *currElem = start;
    listElement *PointertonextnextElem = start;
    if (start->nextElem == NULL) {printf("----------------------------------\n| No List, that can be deleted. |\n----------------------------------\n\n\n");} 
    else{
    printf("\n***********************************\nAre you sure, that you want to delete the whole list?\n\nType 1 for deleting the list.\nType 2 for printing the list to check.\n***********************************\n\n");
    scanf("%d", &choice);
    if (choice == 1){
         do
        {
            PointertonextnextElem = currElem->nextElem->nextElem;
            free(currElem->nextElem);
            currElem->nextElem = PointertonextnextElem; 
        } while (currElem->nextElem != NULL);
        printf("--------------------\n| List is deleted. |\n--------------------\n\n\n");
    }
    else if(choice == 2)
    {
        printList(start);
    }
    else
    {
        printf("--------------------------\n! Please type in 1 or 2. !\n---------------------------\n\n\n");
    }}}

void saveList(listElement *start) {
    FILE* filepointer;
    char filename[] = "name.txt"; 
    listElement *currElem = start;
    int i = 0;
    if (start->nextElem == NULL) {printf("------------------------------------\n! No Elements, that can be saved. !\n------------------------------------\n\n\n");} 
    else{
    printf("----------------------------------------------------\n|How should the File be named?.                     |\n|ALWAYS add '.txt' to the name: f.e. 'filename.txt'.|\n----------------------------------------------------\n\n\n");
    scanf(" %s", &filename);
    filepointer = fopen (filename, "w");  
    if(filepointer == NULL){
        printf("--------------------\n! Can't open file. !\n--------------------\n\n\n");
        fclose(filepointer);
        return;}
    else{
      currElem = currElem->nextElem;
      fprintf(filepointer,"%d\n", getLenOfList(start)); 
      for(currElem->nextElem; i < getLenOfList(start); currElem = currElem->nextElem) {
        fprintf(filepointer, "%s\n", currElem->lastName);
        fprintf(filepointer, "%s\n", currElem->firstName);
        fprintf(filepointer, "%d\n", currElem->age);  
        i++; }
      fclose(filepointer);
      printf("-----------------------------------\n| The following List is now saved: |\n-----------------------------------\n\n\n"); 
      printList(start);}}}

void loadElemList(listElement *start, FILE *filepointer)
{
    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("--------------------------\n! Can't reserve storage. !\n--------------------------\n\n\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
         currElem = currElem->nextElem; 
    currElem->nextElem = new;          
    new->nextElem = NULL;

    fscanf(filepointer, "%s", new->lastName);
    fscanf(filepointer, "%s", new->firstName);
    fscanf(filepointer, "%d", &(new->age));
}
   
void loadList(listElement *start)
{
    FILE* filepointer;
    int numbOfElem = 0;
    char filename[] = "name.txt"; 
    printf("---------------------------------------------------------------------------------------\n| Please type in the name of one of the following text- files, that you want to load: |\n---------------------------------------------------------------------------------------\n\n\n");
    system("dir *.txt");
    scanf(" %s", &filename);
    filepointer = fopen(filename, "r");
    if(filepointer == NULL)
    {
        printf("---------------------------------------------------------\n! Can't open file.                                     !\n! Have you checked, if you entered the right filename? !\n---------------------------------------------------------\n\n\n");
        fclose(filepointer);
        return;
    }
    else
    {
        printf("\n\n...\nloading data will be append to current list...\n...\n\n\n");
        fscanf(filepointer, "%d", &numbOfElem);
        for(int i = 0; i < numbOfElem; i++)
        {
            loadElemList(start, filepointer);
        }
        fclose(filepointer);
        printf("-----------------------\n| Textfile is loaded. |\n| Current list:       |\n-----------------------\n\n\n");
        printList(start);
    }
}


void exitFcn(listElement *start)
{
int choice = 1; 
 printf("\n***********************************\nDo you want to save the current list in a file before you leave?\n Type 1 or any letter for yes.\n Type 2 to leave without saving.\nIf any other number is typed, the program ends without saving.\n\n***********************************\n\n\n"); 
 scanf("%d", &choice);
 if (choice == 1)
 {
    saveList(start);
    printf("\n\n--------------------\n| Exiting Program. |\n--------------------\n\n\n");
 }
 else if (choice == 2)
 {
    printf("------------------------------------------------------------------\n| Changes will not be saved. Exiting the program without saving. |\n------------------------------------------------------------------\n\n\n");
 }
 else
 {
     printf("-----------------------------------------\n| Program will be ended without saving. |\n-----------------------------------------\n\n\n");
 }
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
