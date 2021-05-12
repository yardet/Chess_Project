#pragma once
#include "ChessPos_Lists.h"
typedef struct treeNode treeNode;
typedef struct treeNodeListCell treeNodeListCell;
typedef struct _pathTree
{
    treeNode* root;
}PathTree;
PathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void findAllPossibleKnightPathsRec(chessPosList lst,treeNode* root);
bool Is_exist_in_list( chessPosList lst, chessPos curr_position); /*Returns the new size of the positions dynamic array*/
void Swap(chessPos*** first, chessPos*** second);
int deleteRepeatableCells(chessPosArray** Curr, chessPosList lst);
void Finding_Table_Boundaries(chessPos position, int* start_position_row, int* start_position_col);
treeNode* allocation_Tree_Node(treeNodeListCell** curr,char* position);
void insertTreeNodeDataToEndList(treeNode* res, chessPos value);
void insertTreeNodetoEndList(chessPosList* lst, treeNode* node);
void printTree(PathTree tree);
treeNode* printTreeRec(treeNode* root);
void get_lst(chessPosList* lst);