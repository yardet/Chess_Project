#pragma once
#include "ChessPos_Lists.h"
typedef struct treeNode treeNode;
typedef struct treeNodeListCell treeNodeListCell;
typedef struct _pathTree
{
    treeNode* root;
}PathTree;
PathTree findAllpossibleKnightPaths(chessPos* startingPosition);
