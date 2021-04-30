#define _CRT_SECURE_NO_WARNINGS
#include "TreeList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALLOCATION_FAILURE -1
typedef struct treeNode
{
    chessPos position;
    treeNodeListCell* next_possible_positions;
}treeNode;
typedef struct treeNodeListCell
{
    treeNode* node;
    struct _treeNodeListCell* next;
}treeNodeListCell;
PathTree findAllpossibleKnightPaths(chessPos* startingPosition)
{
    PathTree* res=(PathTree*)malloc(sizeof(PathTree));
    res->root = (treeNode*)malloc(sizeof(treeNode));
    res->root->next_possible_positions = (treeNodeListCell**)malloc(sizeof(treeNodeListCell*));
    res->root->next_possible_positions->node= (treeNode*)malloc(sizeof(treeNode));
    res->root->position[0] = '1';
    res->root->next_possible_positions->node->position[0] = '2';
    printf("%c", res->root->next_possible_positions->node->position[0]);
    return *res;
}