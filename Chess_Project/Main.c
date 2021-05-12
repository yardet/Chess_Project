#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALLOCATION_FAILURE -1
#include "ChessPos_Lists.h"
#include "TreeList.h"

//#define debug_q1
//#define debug_q2
#define debug_q3
//#define debug_q4



int main()
{
    int* table_size, * start_position_row, * start_position_col;
    table_size = (int*)&TABLE_SIZE;
    start_position_row = (int*)&START_POSITION_ROW;
    start_position_col = (int*)&START_POSITION_COL;
    /*Q1*/
#ifdef debug_q1
    
    *table_size = 4;/*8x8*/
    *start_position_row = 0;/*1*/
    *start_position_col = 0;/*A*/
    chessPos start;
    start[0] = 'A';
    start[1] = '1';
    Finding_Table_Boundaries(start, start_position_row, start_position_col);
    chessPosArray*** valid_moves = validKnightMoves();
    Print_valid_moves(valid_moves);
    Free_valid_moves(valid_moves);
    
#endif // debug_q1
    /*Q2*/
#ifdef debug_q2
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
    //freeList(&newList); problem
#endif // debug_q2

    /*Q3*/
#ifdef debug_q3
    chessPos start;
    start[0] = 'A';
    start[1] = '1';
    PathTree tree;
    /*size-4x4*/
    //*table_size = 4;
    //Finding_Table_Boundaries(start, start_position_row, start_position_col);
    //tree= findAllPossibleKnightPaths(&start);
    /*size-5x5*/
    *table_size = 5;
    //Finding_Table_Boundaries(start, start_position_row, start_position_col);
    tree = findAllPossibleKnightPaths(&start);
#endif // debug_q3

    
    return 0;
}




