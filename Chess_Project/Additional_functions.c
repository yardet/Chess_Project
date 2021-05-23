#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "Additional functions.h"
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
    *tableSize = 4;
    int Selection;
    chessPos starting_position;
    starting_position[0] = 'A';/*For default*/
    starting_position[1] = '1';
    PathTree tree;
    chessPosList* Path_cover_all_board;
    puts("Hello!\n1. Enter a knight's starting postion\n ");
    puts("2. Create all possible knight paths\n");
    puts("3. Find a knight path covering all borad\n");
    puts("4. Save knight path covering all board to file\n");
    puts("5. Load and display path from file\n");
    puts("6. Exit\n");
    scanf("%d", &Selection);
    while (Selection != 6)
    {
        getchar();/*get the '\n'*/
        switch (Selection)
        {
        case 1:
            system("cls");
            puts("Enter here:");
            scanf("%c%c",&starting_position[0],&starting_position[1]);
            Position_integrity_check(starting_position);
            break;
        case 2:
            tree = findAllPossibleKnightPaths(&starting_position);
            break;
        case 3:
            Path_cover_all_board=findknightPathCoveringAllBoard(&tree);
            break;
        default:
            system("cls");
            puts("Error,Please select a valid number\n");
            break;
        }

        system("cls");
        puts("Hello!\n1. Enter a knight's starting postion\n ");
        puts("2. Create all possible knight paths\n");
        puts("3. Find a knight path covering all borad\n");
        puts("4. Save knight path covering all board to file\n");
        puts("5. Load and display path from file\n");
        puts("6. Exit\n");
        scanf("%d", &Selection);

    }
    puts("Thanks you!\n");
    exit(-1);
}
void Position_integrity_check(chessPos position)
{
    while ((position[0] < 'A' || position[0] > TABLE_SIZE + 'A') &&( position[1] < 1 || position[1] > TABLE_SIZE))
    {
        puts("Error,Please select a valid position:");
        //printf("Enter here:");
        //getchar();
        scanf("%c%c", &position[0], &position[1]);
    }
}