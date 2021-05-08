#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
 
#define NAME_LEN 30
#define MAX_STUDENTS 50
#define HOME_LEN 15
#define SOURCE "studentList.txt"
#define STUDENT_SIZE 52
 
#define COL1 "ID"
#define COL2 "Name"
#define COL3 "Home land"
#define COL4 "Score"
/*
One students occupies 52 byte in file
ID = 3byte, name = 30byte, home = 15byte, score = 4
*/
 
int checkEmpty(FILE* filePtr);
void printList(FILE* filePtr);
void addStudent(FILE* filePtr);
 
struct classList
{
    uint8_t id;
    char name[NAME_LEN];
    char home[HOME_LEN];
    float score;
}student;
 
int main()
{
    int order;
    uint8_t choice;
    bool ask = 0;
    bool repeat = 0;
 
    FILE* fp = fopen(SOURCE, "r+");
 
    if (fp == NULL)
    {
        printf ("ERROR WITH FILE.\n");
    }
 
    printf ("STUDENT MANAGEMENT PROGRAM\n");
    do 
    {   
        
        repeat = 0;
        printf ("Please select your option:\n1. Printf Students' list\n2. Add Students\n");
        scanf ("%hhd", &choice);
        switch(choice)
        {
            case 1:
                if (checkEmpty(fp) == 1)
                {
                    printf ("File is empty.\n");
                }
                else if (checkEmpty(fp) == 0)
                {
                    printf ("%-3s%30s%15s%4s", COL1, COL2, COL3, COL4);
                    printList(fp);
                }
            break;
            case 2:
                addStudent(fp);
            break;
        }
        printf ("Do you want to continue?\n1. Yes\n2. No\n");
        scanf("%d", &ask);
        if (ask == 1)
        {
            repeat = 1;
        }
    }
    while(repeat == 1);
    fclose(fp);
    return 0;
}
 
int checkEmpty(FILE* filePtr)
{
    int check = fgetc(filePtr);
    if (check == EOF)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
void printList(FILE* filePtr)
{
    char buffer [STUDENT_SIZE];
    while(!feof(filePtr))
    {
        if (fgets(buffer, STUDENT_SIZE, filePtr) != NULL);
        {
            printf ("%s\n", buffer);
        }
    }
}
 
void addStudent(FILE* filePtr)
{
    int n = 0;
    char buffer [STUDENT_SIZE];
    printf ("How namy student do you want to add?\n");
    scanf ("%d", &n);
    printf ("Enter students' informations\n");
    int k = 0;
    while(k < n)
    {
        printf ("Student %d:\n", k+1);
        printf ("\tID: ");
        scanf ("%hhd", &student.id);
        while(getchar() != '\n');
 
        printf ("\tName: ");
        scanf ("%[^\n]s", &student.name);
        while(getchar() != '\n');
 
        printf ("\tHome land: ");
        scanf ("%[^\n]s", &student.home);
        while(getchar() != '\n');

        printf ("-------------------\n");
        printf ("\tScore: ");
        scanf ("%f", &student.score);
        printf ("-------------------\n");
        while(getchar() != '\n');
        printf ("+++++++++++++++++++\n");

        
        fseek(filePtr, k * STUDENT_SIZE, SEEK_CUR);

        fprintf(filePtr, "\n%-3d%-30s%-15s%-4.1f", student.id, student.name, student.home, student.score);
        k = k + 1;
    }
}