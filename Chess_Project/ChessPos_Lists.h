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
bool isEmptyList(chessPosList* lst);
void freeList(chessPosList* lst);
chessPosArray*** validKnightMoves();
void printList(chessPosList* lst);
void display(chessPosList* lst);
void makeEmptyPosList(chessPosList* lst);
int isPosAppear(chessPosList* lst, char posFirstChar, char posSecondChar);
chessPosCell* createNewListNode(chessPos position, chessPosCell* nextNode);
void insertPosCellToEndList(chessPosList* lst, chessPosCell* node);
void deletePosCellFromEndList(chessPosList* lst);
void printValidMoves(chessPosArray*** valid_moves);
void freeValidMoves(chessPosArray*** valid_moves);