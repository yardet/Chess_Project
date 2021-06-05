#pragma once
#include "ChessPos_Lists.h"
typedef struct treeNode treeNode;
typedef struct treeNodeListCell treeNodeListCell;
typedef struct _pathTree
{
    treeNode* root;
}pathTree;

// Q1, Q3
//void getTableBoundaries(chessPos position, int* pStartingPositionRow, int* pStartingPositionCol);

// Q3
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void findAllPossibleKnightPathsRec(bool*** positions_history, treeNode* root, chessPosArray*** Possible_moves);
void deleteRepeatableCells(chessPosArray* Curr, bool** positions_history);
treeNode* allocateNewTreeNode(treeNodeListCell** pTreeNode, char* position);
void printTree(pathTree tree);
void printTreeRec(treeNode* root);

// Q4
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosList* findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, int* stop, int* possibleRoutesCounter);
void printAllPossitionsRoutes(chessPosList* lst);

// Not used
bool positionExistsInList(chessPosList lst, chessPos currPosition); /*Returns the new size of the positions dynamic array*/
void freePathTree(pathTree* path_tree);
void freePathTreeRec(treeNode* root);