#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ChessPos_Lists.h"
#include "TreeList.h"
#include "Additional functions.h"
#include "Files.h"

//#define DEBUG_Q1
//#define DEBUG_Q2
//#define DEBUG_Q3
//#define DEBUG_Q4
//#define DEBUG_Q5
//#define DEBUG_Q6
#define MENU

int main(int argc, char* argv[])
{
    int* tableSize, * initialRowPosition, * initialColPosition; // initial is the same meaning as starting
    tableSize = (int*)&TABLE_SIZE;
    initialRowPosition = (int*)&STARTING_POSITION_ROW;
    initialColPosition = (int*)&STARTING_POSITION_ROW;

    /*Q7*/
#ifdef MENU
    menu();
#endif // MENU

    /*Q1*/
#ifdef DEBUG_Q1

    * tableSize = 4;/*8x8*/
    *initialRowPosition = 0;/*1*/
    *initialColPosition = 0;/*A*/
    chessPos start;
    start[0] = 'A';
    start[1] = '1';
    getTableBoundaries(start, initialRowPosition, initialColPosition);
    chessPosArray*** valid_moves = validKnightMoves();
    printValidMoves(valid_moves);
    freeValidMoves(valid_moves);

#endif // DEBUG_Q1

    /*Q2*/
#ifdef DEBUG_Q2
    /*Example as shown in instructions*/
    chessPosCell node9 = { { 'E','1' }, NULL };
    chessPosCell node8 = { {'E', '1'}, &node9 };
    chessPosCell node7 = { {'E', '1'}, &node8 };
    chessPosCell node6 = { {'E', '1'}, &node7 };
    chessPosCell node5 = { {'A', '4'}, &node6 };
    chessPosCell node4 = { {'H', '5'}, &node5 };
    chessPosCell node3 = { {'D', '8'}, &node4 };
    chessPosCell node2 = { {'H', '5'}, &node3 };
    chessPosCell node1 = { {'A', '4'}, &node2 };

    chessPosList newList = { &node1, &node9 };
    display(&newList);
    //freeList(&newList);
#endif // DEBUG_Q2

    /*Q3*/
#ifdef DEBUG_Q3
    chessPos start;
    start[0] = 'A';
    start[1] = '1';
    PathTree tree;
    /*size-4x4*/
    *tableSize = 4;
    // getTableBoundaries(start, initialRowPosition, initialColPosition);
    tree = findAllPossibleKnightPaths(&start);
    free_path_tree(&tree);
    /*size-5x5*/
    //tableSize = 5;
    //getTableBoundaries(start, initialRowPosition, initialColPosition);
    //tree = findAllPossibleKnightPaths(&start);
    //free_path_tree(&tree);
#endif // DEBUG_Q3

    /*Q4*/
#ifdef DEBUG_Q4
    chessPosList* Path_cover_all_board;
    Path_cover_all_board= findknightPathCoveringAllBoard(&tree);
    freeList(Path_cover_all_board);
#endif // DEBUG_Q4

    /*Q5*/
#ifdef DEBUG_Q5
    int i = NULL;
    chessPosCell node5 = { {'E', '3'},NULL};
    chessPosCell node4 = { {'D', '1'}, &node5 };
    chessPosCell node3 = { {'B', '3'}, &node4 };
    chessPosCell node2 = { {'A', '4'}, &node3 };
    chessPosCell node1 = { {'C', '5'}, &node2 };

    chessPosList newList = { &node1, &node4 };

    char* str = (char*)malloc(19 * sizeof(char));
    str = "bytesInBinary.bin";
    saveListToBinFile(str, &newList);
#endif // DEBUG_Q5

    /*Q6*/
#ifdef DEBUG_Q6
    FILE* fp;
    fp = fopen(str, "rb");
    printCellsFromBinaryFile(fp);
    fclose(fp);
#endif // DEBUG_Q6
    return 0;
}