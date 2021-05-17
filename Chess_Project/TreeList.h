#pragma once
#include "ChessPos_Lists.h"
typedef struct treeNode treeNode;
typedef struct treeNodeListCell treeNodeListCell;
typedef struct _pathTree
{
    treeNode* root;
}PathTree;
PathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void findAllPossibleKnightPathsRec(chessPosList lst, treeNode* root);
//void findAllPossibleKnightPathsRec(int*** positions_history, treeNode* root);
bool positionExistsInList(chessPosList lst, chessPos currPosition); /*Returns the new size of the positions dynamic array*/
int deleteRepeatableCells(chessPosArray** Curr, chessPosList lst);
//int deleteRepeatableCells(chessPosArray** Curr, int*** positions_history);
void getTableBoundaries(chessPos position, int* pStartingPositionRow, int* pStartingPositionCol);
treeNode* allocateNewTreeNode(treeNodeListCell** pTreeNode, char* position);
// void insertTreeNodeDataToEndList(treeNode* res, chessPos value);
// void insertTreeNodetoEndList(chessPosList* lst, treeNode* node);
void printTree(PathTree tree);
void printTreeRec(treeNode* root);
void printAllPossitionsRoutes(chessPosList* lst);
chessPosList* findknightPathCoveringAllBoard(PathTree* path_tree);
chessPosList* findknightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root,int* stop);