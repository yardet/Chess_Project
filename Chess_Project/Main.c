#define _CRT_SECURE_NO_WARNINGS
#include "ChessPos_Lists.h"
#include "TreeList.h"
#include "Additional functions.h"

//#define DEBUG_Q1
//#define DEBUG_Q2
//#define DEBUG_Q3
//#define DEBUG_Q4
#define MENU

int main(int argc, char* argv[])
{
    int* tableSize, * initialRowPosition, * initialColPosition; // initial is the same meaning as starting
    tableSize = (int*)&TABLE_SIZE;
    initialRowPosition = (int*)&STARTING_POSITION_ROW;
    initialColPosition = (int*)&STARTING_POSITION_ROW;
#ifdef MENU
    /*size-5x5*/
    tableSize = 5;
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
    /*size-5x5*/
    /*tableSize = 5;
    getTableBoundaries(start, initialRowPosition, initialColPosition);
    tree = findAllPossibleKnightPaths(&start);*/
#endif // DEBUG_Q3

    return 0;
}