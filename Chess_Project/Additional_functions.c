#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include "Additional functions.h"
#include <string.h>
#include "ChessPos_Lists.h"
#include "Files.h"
#include "TreeList.h"
#define NUM_OF_OPTIONS 5
#define FILE_LEN 20
void checkAllocation(void* res)
{
    if (!res)
    {
        fprintf(stderr, "Allocation failure in \nExiting...\n");
        exit(ALLOCATION_FAILURE);
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
    char* file_name = (char*)malloc(sizeof(char) * FILE_LEN);
    char* file_name_in= (char*)malloc(sizeof(char) * FILE_LEN);
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
        getchar();/*get the '\n'*/
        switch (Selection)
        {
        case 1:
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
        case 2:
            if (!operationArr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                positionIntegrityCheck(starting_position);
                operationArr[0] = true;/*Location selection*/
            }
            tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                operationArr[1] = true;
            else
                puts("error with the construction of the tree,try again\n");
            break;
        case 3:
            if (!operationArr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                positionIntegrityCheck(starting_position);
                operationArr[0] = true;
            }
            if (!operationArr[1])
                tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                operationArr[1] = true;
            else
                puts("error with the construction of the tree,try again\n");
            pathCoverAllBoard = findKnightPathCoveringAllBoard(&tree);
            if (!pathCoverAllBoard)
            {
                puts("There is no suitable route,Try choosing a different starting location\n");
                operationArr[2] = false;
            }
            else
                operationArr[2] = true;
            break;
        case 4:
            if (!operationArr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
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
                    puts("error with the construction of the tree,try again\n");
                    break;
                }       
            }
            if (!operationArr[2])
            {
                pathCoverAllBoard = findKnightPathCoveringAllBoard(&tree);
                if (!pathCoverAllBoard)
                    puts("There is no suitable route,Try choosing a different starting location\n");
                else
                    operationArr[2] = true;
            }
            puts("enter file name:");
            scanf("%s", file_name);
            saveListToBinFile(file_name, pathCoverAllBoard);
            operationArr[3] = true;
            break;
        case 5:
            puts("enter file name:");
            scanf("%s", file_name_in);
            fp = fopen(file_name_in, "rb");
            checkAllocation(fp);
            chessPosList* pos_list= getCellsFromBinaryFile(fp);
            display(pos_list);
            operationArr[4] = true;
            fclose(fp);
            system("PASUE");/*waiting for 'enter'(Just to see the print before the screen is cleared) */
            break;
        default:
            system("cls");
            puts("Error,Please select a valid number\n");
        }
        system("cls");
        printMenu(operationArr);/*print the menu again*/
        scanf("%d", &Selection);
    }
    if (tree.root)
        freePathTree(&tree);
    if (pathCoverAllBoard)
        freeList(pathCoverAllBoard);
    system("cls");
    puts("Thanks you!\n");
    free(operationArr);
    exit(-1);
}
void positionIntegrityCheck(chessPos position)
{
    while ((position[0] < 'A' || position[0] > TABLE_SIZE + 'A') ||( position[1]-'0' < 1 || position[1]-'0' > TABLE_SIZE))
    {
        puts("Error,Please select a valid position:");
        printf("Enter here:");
        scanf("%c%c", &position[0], &position[1]);
    }
}
void printMenu(bool* operationArr)
{
    for (int i = 0; i < NUM_OF_OPTIONS; i++)
    {
        if (operationArr[i])
            printf("%d-DONE!\n", i + 1);
    }
    puts("1. Enter a knight's starting postion\n ");
    puts("2. Create all possible knight paths\n");
    puts("3. Find a knight path covering all borad\n");
    puts("4. Save knight path covering all board to file\n");
    puts("5. Load and display path from file\n");
    puts("6. Exit\n");
}