#pragma once
#include <stdbool.h>
#define CHESS_ARRAY_SIZE 8
const int STARTING_POSITION_ROW;
const int STARTING_POSITION_COL;
const int TABLE_SIZE;
typedef char chessPos[2];
typedef struct _chessPosCell
{
    chessPos position;
    struct _chessPosCell* next;
} chessPosCell;
typedef struct _chessPosArray
{
    unsigned int size;
    chessPos* positions;
}chessPosArray;
typedef struct __chessPosList
{
    chessPosCell* head;
    chessPosCell* tail;
}chessPosList;

// Q1
chessPosArray*** validKnightMoves(); // Used in Q3
void printValidMoves(chessPosArray*** valid_moves);
void freeValidMoves(chessPosArray*** valid_moves);

// Q2
chessPosList getExampleChessPosList();
void display(chessPosList* lst); // Used in Q6
bool** getBooleanMatrix(int rowSize, int colSize);
void makeEmptyChessPosList(chessPosList* lst);
chessPosCell* createNewListNode(chessPos position, chessPosCell* nextNode); // Used in Q3
void insertChessPosCellToEndList(chessPosList* lst, chessPosCell* node); // Used in Q3
bool isEmptyList(chessPosList* lst);
void freeBooleanMatrix(bool** arr, int rowSize);
void printList(chessPosList* lst);
void freeList(chessPosList* lst);
void free_int_chess_array(int*** chess_array);
int*** allocation_int_chess_array();

// Q3, Q4
void deleteLastChessPosCellFromList(chessPosList* lst);

// Q6
bool isValidPath(chessPosList lst);
bool isPathCoveringAllBoard(chessPosList lst);