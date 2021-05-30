#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include "Additional functions.h"
#include <string.h>
#include "ChessPos_Lists.h"
#include "Files.h"
#include "TreeList.h"
#define NUM_OF_OPTIONS 5
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
    FILE* fp;
    bool* Op_arr = (bool*)malloc(sizeof(bool) * NUM_OF_OPTIONS);
    checkAllocation(Op_arr);
    char* file_name = (char*)malloc(sizeof(char) * 20);
    char* file_name_in= (char*)malloc(sizeof(char) * 20);
    chessPos starting_position;
    starting_position[0] = 'A';/*For default*/
    starting_position[1] = '1';
    for (int i = 0; i < NUM_OF_OPTIONS; i++)
    {
        Op_arr[i] = false;
    }
    PathTree tree;
    tree.root = NULL;
    chessPosList* Path_cover_all_board;
    makeEmptyPosList(&Path_cover_all_board);
   /* puts("Hello!\n1. Enter a knight's starting postion\n ");
    puts("2. Create all possible knight paths\n");
    puts("3. Find a knight path covering all borad\n");
    puts("4. Save knight path covering all board to file\n");
    puts("5. Load and display path from file\n");
    puts("6. Exit\n");*/
    Print_Menu(Op_arr);
    scanf("%d", &Selection);
    while (Selection != 6)
    {
        getchar();/*get the '\n'*/
        switch (Selection)
        {
        case 1:
            if (Op_arr[0])/*if we already chosen location and we want changing to another*/
            {
                Op_arr[0] = false;
                if (Op_arr[1])
                {
                    Op_arr[1] = false;
                    free_path_tree(&tree);
                }
                if (Op_arr[2])
                {
                    Op_arr[2] = false;
                    freeList(Path_cover_all_board);
                }
                if (Op_arr[3])
                    Op_arr[3] = false;
                if (Op_arr[4])
                    Op_arr[4] = false;
            }
            system("cls");
            puts("Enter here:");
            scanf("%c%c", &starting_position[0], &starting_position[1]);
            Position_integrity_check(starting_position);
            Op_arr[0] = true;
            break;
        case 2:
            if (!Op_arr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                Position_integrity_check(starting_position);
                Op_arr[0] = true;/*Location selection*/
            }
            tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                Op_arr[1] = true;
            else
                puts("error with the construction of the tree,try again\n");
            break;
        case 3:
            if (!Op_arr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                Position_integrity_check(starting_position);
                Op_arr[0] = true;
            }
            if (tree.root == NULL)
                tree = findAllPossibleKnightPaths(&starting_position);
            if (tree.root)
                Op_arr[1] = true;
            else
                puts("error with the construction of the tree,try again\n");
            Path_cover_all_board = findknightPathCoveringAllBoard(&tree);
            if (!Path_cover_all_board)
            {
                puts("There is no suitable route,Try choosing a different starting location\n");
                Op_arr[2] = false;
            }
            else
               Op_arr[2] = true;
            break;
        case 4:
            if (!Op_arr[0])
            {
                puts("Initial location not yet entered\n");
                puts("Enter here:");
                scanf("%c%c", &starting_position[0], &starting_position[1]);
                Position_integrity_check(starting_position);
                Op_arr[0] = true;
            }
            if (!!tree.root)
            {
                tree = findAllPossibleKnightPaths(&starting_position);
                if (tree.root)
                    Op_arr[1] = true;
                else
                {
                    Op_arr[1] = false;
                    puts("error with the construction of the tree,try again\n");
                    break;
                }       
            }
            if (!Op_arr[2])
            {
                Path_cover_all_board = findknightPathCoveringAllBoard(&tree);
                if (!Path_cover_all_board)
                    puts("There is no suitable route,Try choosing a different starting location\n");
                else
                    Op_arr[2] = true;
            }
            puts("enter file name:");
            scanf("%s", file_name);
            saveListToBinFile(file_name, Path_cover_all_board);
            Op_arr[3] = true;
            break;
        case 5:
            scanf("%s", file_name_in);
            fp = fopen( file_name_in, "rb");
            printCellsFromBinaryFile(fp);
            Op_arr[4] = true;
            fclose(fp);
        default:
            system("cls");
            puts("Error,Please select a valid number\n");
        }
        system("cls");
        Print_Menu(Op_arr);
        scanf("%d", &Selection);
    }
    system("cls");
    puts("Thanks you!\n");
    free(Op_arr);
    exit(-1);
}
void Position_integrity_check(chessPos position)
{
    while ((position[0] < 'A' || position[0] > TABLE_SIZE + 'A') ||( position[1]-'0' < 1 || position[1]-'0' > TABLE_SIZE))
    {
        puts("Error,Please select a valid position:");
        //printf("Enter here:");
        
        getchar();
        scanf("%c%c", &position[0], &position[1]);
    }
}
void Print_Menu(bool* Op_arr)
{
    for (int i = 0; i < NUM_OF_OPTIONS; i++)
    {
        if (Op_arr[i])
            printf("%d-DONE!\n", i + 1);
    }
    puts("1. Enter a knight's starting postion\n ");
    puts("2. Create all possible knight paths\n");
    puts("3. Find a knight path covering all borad\n");
    puts("4. Save knight path covering all board to file\n");
    puts("5. Load and display path from file\n");
    puts("6. Exit\n");
}