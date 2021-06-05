#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include "Additional functions.h"
#include <string.h>
#include "ChessPos_Lists.h"
#include "Files_Bytes.h"
#include "TreeList.h"
#define NUM_OF_OPTIONS 6
#define FILE_LEN 20
void checkAllocation(void* res)
{
    if (!res)
    {
        fprintf(stderr, "Allocation failure... Exiting\nGood bye!\n");
        exit(FAILURE);
    }
}
void menu()
{
    int* tableSize = (int*)&TABLE_SIZE;
    *tableSize = 5;
    int Selection;
    FILE* fp;
    bool* operationArr = (bool*)malloc(sizeof(bool) * NUM_OF_OPTIONS);
    checkAllocation(operationArr);
    char* fileNameQ5 = (char*)malloc(sizeof(char) * FILE_LEN);
    checkAllocation(fileNameQ5);
    char* fileNameQ6 = (char*)malloc(sizeof(char) * FILE_LEN);
    checkAllocation(fileNameQ6);
    chessPos starting_position;
    starting_position[0] = 'A';/*For default*/
    starting_position[1] = '1';
    for (int i = 0; i < NUM_OF_OPTIONS; i++)
    {
        operationArr[i] = false;
    }
    pathTree tree;
    tree.root = NULL;
    chessPosList* pathCoverAllBoard;
    makeEmptyChessPosList(&pathCoverAllBoard);
    printMenu(operationArr);
    scanf("%d", &Selection);
    while (Selection != 6)
    {
        getchar(); /*get the '\n'*/
        switch (Selection)
        {
        case 1:
            operationArr[5] = false;
            if (operationArr[0])/*if we already chosen location and we want changing to another*/
            {
                operationArr[0] = false;
                if (operationArr[1])
                {
                    operationArr[1] = false;
                    freePathTree(&tree);
                }
                if (operationArr[2])
                {
                    operationArr[2] = false;
                    freeList(pathCoverAllBoard);
                }
                if (operationArr[3])
                    operationArr[3] = false;
                if (operationArr[4])
                    operationArr[4] = false;
            }
            system("cls");
            puts("Enter here:");
            scanf("%c%c", &starting_position[0], &starting_position[1]);
            positionIntegrityCheck(starting_position);
            operationArr[0] = true;
            break;
        case 2: // Q3
            operationArr[5] = false;
            if (!operationArr[0])
            {
                puts("Initial location has not been entered yet, enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                positionIntegrityCheck(starting_position);
                operationArr[0] = true;/*Location selection*/
            }
            tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                operationArr[1] = true;
            else
            {
                puts("Error with the construction of the tree - try again\n");
                system("PAUSE");
            }
            break;
        case 3: // Q4
            operationArr[5] = false;
            if (!operationArr[0])
            {
                puts("Initial location has not been entered yet, enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                positionIntegrityCheck(starting_position);
                operationArr[0] = true;
            }
            if (!operationArr[1])
                tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                operationArr[1] = true;
            else
            {
                puts("Error with the construction of the tree - try again\n");
                system("PAUSE");
            }
            pathCoverAllBoard = findKnightPathCoveringAllBoard(&tree);
            if (!pathCoverAllBoard)
            {
                puts("There is no suitable route, try choosing a different starting location\n");
                system("PAUSE");
                operationArr[2] = false;
            }
            else
                operationArr[2] = true;
            break;
        case 4: // Q5
            operationArr[5] = false;
            if (!operationArr[0])
            {
                puts("Initial location has not been entered yet, enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                positionIntegrityCheck(starting_position);
                operationArr[0] = true;
            }
            if (!operationArr[1])
            {
                tree = findAllPossibleKnightPaths(&starting_position);
                if (tree.root)
                    operationArr[1] = true;
                else
                {
                    operationArr[1] = false;
                    puts("Error with the construction of the tree - try again");
                    system("PAUSE");
                    break;
                }
            }
            if (!operationArr[2])
            {
                pathCoverAllBoard = findKnightPathCoveringAllBoard(&tree);
                if (!pathCoverAllBoard)
                {
                    puts("There is no suitable route, try choosing a different starting location");
                    system("PAUSE");
                    break;
                }
                else
                    operationArr[2] = true;
            }
            puts("Please enter file name:");
            scanf("%s", fileNameQ5);
            saveListToBinFile(fileNameQ5, pathCoverAllBoard);
            operationArr[3] = true;
            break;
        case 5: // Q6
            operationArr[5] = false;
            puts("Please enter file name:");
            scanf("%s", fileNameQ6);
            int returningValue = checkAndDisplayPathFromFile(fileNameQ6);
            if (returningValue == FAILURE)
            {
                puts("File not found");
            }
            else if (returningValue == 1)
            {
                puts("The path is not valid");
            }
            else if (returningValue == 2)
            {
                puts("The path is valid and it covers all board");
            }
            else
            {
                puts("The path is valid but it does not cover all board");
            }
            operationArr[4] = true;
            system("PAUSE"); /*waiting for 'enter' (just to see the print before the screen is cleared) */
            break;
        default:
            system("cls");
            operationArr[5] = true;
            break;
        }
        system("cls");
        printMenu(operationArr);/*print the menu again*/
        //fflush(&Selection);
        scanf("%d", &Selection);
    }
    if (tree.root && operationArr[1])
        freePathTree(&tree);
    if (pathCoverAllBoard && operationArr[2])
        freeList(pathCoverAllBoard);
    system("cls");
    puts("Thank you!\n");
    free(operationArr);
    exit(-1);
}
void positionIntegrityCheck(chessPos position)
{
    while ((position[0] < 'A' || position[0] > TABLE_SIZE + 'A') || (position[1] - '0' < 1 || position[1] - '0' > TABLE_SIZE))
    {

        puts("Error, please select a valid position - enter here:");
        fseek(stdin, 0, SEEK_END);/*clear the scanf*/
        scanf("%c%c", &position[0], &position[1]);
    }
}
void printMenu(bool* operationArr)
{
    for (int i = 0; i < NUM_OF_OPTIONS - 1; i++)
    {
        if (operationArr[i])
        {
            printf("Clause %d - DONE!\n", (i + 1));
        }
    }
    if (operationArr[NUM_OF_OPTIONS - 1])
    {
        puts("Error - please select a valid number\n");
        fseek(stdin, 0, SEEK_END);/*clear the scanf*/
    }
    puts("1. Enter a knight's starting postion");
    puts("2. Create all possible knight paths");
    puts("3. Find a knight path covering all board");
    puts("4. Save knight path covering all board to file");
    puts("5. Load and display path from file");
    puts("6. Exit");
}