#define _CRT_SECURE_NO_WARNINGS
#include "TreeList.h"
#include "Additional functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 #include <string.h>

typedef struct treeNode
{
    chessPos position;
    treeNodeListCell* next_possible_positions;
}treeNode;
typedef struct treeNodeListCell
{
    treeNode* node;
    struct treeNodeListCell* next;
}treeNodeListCell;
//int possibleRoutesCounter = 0;

PathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    PathTree tree;
    tree.root = (treeNode*)malloc(sizeof(treeNode));
    if (tree.root);
    {
        chessPosList lst; /*a list of all the positions that have been played*/
        makeEmptyPosList(&lst);
        if (!startingPosition)
        {
            puts("Starting position is empty!\n");
            exit(ALLOCATION_FAILURE);
        }
        tree.root->position[0] = startingPosition[0][0];
        tree.root->position[1] = startingPosition[0][1];
        int** positions_history = (int**)malloc(sizeof(int*) * TABLE_SIZE);
        if (positions_history != NULL)
        {
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                positions_history[i] = (int*)malloc(sizeof(int) * TABLE_SIZE);
                if (positions_history[i] != NULL)
                {
                    for (int j = 0; j < TABLE_SIZE; j++)
                    {
                        positions_history[i][j] = 0;
                    }
                }
            }
        }
        findAllPossibleKnightPathsRec(lst, tree.root);
        //findAllPossibleKnightPathsRec(positions_history, tree.root);
        // printTree(tree);
    }
    return tree;
}
void findAllPossibleKnightPathsRec(chessPosList lst, treeNode* root)
//void findAllPossibleKnightPathsRec(int** positions_history, treeNode* root)
{
    chessPosArray* currPosition = validKnightMoves()[root->position[0] - 'A'][root->position[1] - '0' - 1];
    //int routeSize = deleteRepeatableCells(&currPosition, lst);
    int i;
    int routeSize = deleteRepeatableCells(&currPosition, lst);
    chessPosCell* node = createNewListNode(root->position, NULL);
    //positions_history[root->position[0] - 'A'][root->position[1] - '0' - 1] = 1;
    insertPosCellToEndList(&lst, node);

    if (currPosition->size == 0)
    {
        root->next_possible_positions = NULL;
        return;
    }
    else
    {
        treeNodeListCell* res = root->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell) * currPosition->size); /*allocation of posible positions*/
        if (res)
        {
            res->node = NULL;
        }
        treeNode* nextNode;
        for (i = 0; i < (int)currPosition->size; i++)
        {
            nextNode = allocateNewTreeNode(&res, currPosition->positions[i]);
            findAllPossibleKnightPathsRec(lst, nextNode);
            deletePosCellFromEndList(&lst);
            //positions_history[root->position[0] - 'A'][root->position[1] - '0' - 1] = 0;
        }
    }
}
chessPosList* findKnightPathCoveringAllBoard(PathTree* path_tree)
{
    //chessPosList** Path_list = (chessPosList**)malloc(sizeof(chessPosList*));
    chessPosList *Path_list=(chessPosList*)malloc(sizeof(chessPosList));
    makeEmptyPosList(Path_list);
    if (path_tree->root)
    {
        int* n = (int*)malloc(sizeof(int));
        if (n != NULL)
        {
            *n = 0;

            int* possibleRoutesCounter = (int*)malloc(sizeof(int));
            if (possibleRoutesCounter != NULL)
            {
                *(possibleRoutesCounter) = 0;
                Path_list = findKnightPathCoveringAllBoardRec(Path_list, path_tree->root, n, possibleRoutesCounter);
                if (Path_list)
                {
                    printAllPossitionsRoutes(Path_list);
                    return Path_list;
                }
                free(possibleRoutesCounter);
            }
        }
    }
    return NULL;
}
chessPosList* findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root,int* stop,int* possibleRoutesCounter)
{
    if (*stop==1)
    {
        return lst;
    }
    else
    {
        chessPosCell* node = createNewListNode(root->position, NULL);
        (*possibleRoutesCounter)++;
        insertPosCellToEndList(lst, node);
        treeNodeListCell* res = root->next_possible_positions;
        if (res == NULL)
        {
            if ((*possibleRoutesCounter) == TABLE_SIZE * TABLE_SIZE-1)
            {
                *stop = 1;
                findKnightPathCoveringAllBoardRec(lst, root, stop, possibleRoutesCounter);
            }
            return;
        }
        else
        {
            treeNodeListCell* currNode = res;
            treeNodeListCell* prevNode = res;
            while (currNode&&(*stop)==0)
            {
                prevNode = currNode;
                findKnightPathCoveringAllBoardRec(lst, prevNode->node,stop,possibleRoutesCounter);
                if ((*stop) == 1)
                {
                    return lst;
                }
                else
                {
                    currNode = currNode->next;
                    deletePosCellFromEndList(lst);
                    (*possibleRoutesCounter)--;
                } 
            }
            if ((*possibleRoutesCounter) == 1)
            {
                deletePosCellFromEndList(lst);
                return NULL;
            }  
        }
    }  
}
treeNode* allocateNewTreeNode(treeNodeListCell** pCurrNode, char* currPosition)
{
    if (!(*pCurrNode)->node) /*Begin of list*/
    {
        (*pCurrNode)->node = (treeNode*)malloc(sizeof(treeNode));
        if ((*pCurrNode)->node)
        {
            (*pCurrNode)->node->position[0] = currPosition[0];
            (*pCurrNode)->node->position[1] = currPosition[1];
            (*pCurrNode)->next = NULL;
        }
    }
    else
    {
        treeNodeListCell* currNode = (*pCurrNode), * prevNode = currNode;
        while (currNode != NULL)
        {
            prevNode = currNode;
            currNode = currNode->next;
        }
        if (!currPosition)
        {
            if (*pCurrNode)
            {
                (*pCurrNode)->node = NULL;
                currNode = NULL;
            }
        }
        else
        {
            currNode = (treeNodeListCell*)malloc(sizeof(treeNodeListCell)); // currNode = (chessPosCell*)malloc(sizeof(chessPosCell))
            if (currNode)
            {
                currNode->node = (treeNode*)malloc(sizeof(treeNode));
                if (currNode->node)
                {
                    checkAllocation(currNode->node);
                    currNode->node->position[0] = currPosition[0];
                    currNode->node->position[1] = currPosition[1];
                    if (prevNode)
                    {
                        prevNode->next = currNode;
                        prevNode->next->next = NULL;
                        return currNode->node; // return prevNode->next->node;
                    }
                }
            }
        }
    }
    if (*pCurrNode != NULL)
    {
        return (*pCurrNode)->node;
    }
    else
    {
        return NULL;
    }
}
bool positionExistsInList(chessPosList lst, chessPos currPosition) /*this function is not used*/
{
    if (isEmptyList(&lst))
    {
        return false;
    }
    else
    {
        chessPosCell* currNode = lst.head;
        while (currNode != NULL)
        {
            if (currNode->position[0] == currPosition[0] && currNode->position[1] == currPosition[1])
            {
                return true;
            }
            currNode = currNode->next;
        }
        return false;
    }
}
int deleteRepeatableCells(chessPosArray** currLst, chessPosList lst)
//int deleteRepeatableCells(chessPosArray** currLst, int*** positions_history)
{
    int oldLstSize = (*currLst)->size;
    int i, j, currLstSize = 1;
    if (isEmptyList(&lst))
    {
        return 0; // return;
    }
    else
    {
        int equivalentPositions = 0;
        chessPosCell* myNode = lst.head;
        chessPos* positions = (*currLst)->positions;
        while (myNode)
        {
            for (i = 0; i < oldLstSize - equivalentPositions; i++)
            {
                if (positions[i][0] == myNode->position[0] && positions[i][1] == myNode->position[1])
                //if((*positions_history)[positions[i][0] - 'A'][positions[i][1] - '0'-1]==1)
                {
                    
                    if (equivalentPositions != oldLstSize - 1)
                    {
                        for (j = i; j < oldLstSize - equivalentPositions; j++)
                        {
                            positions[j][0] = positions[j + 1][0];
                            positions[j][1] = positions[j + 1][1];
                        }
                    }
                    equivalentPositions++;
                    *(positions[oldLstSize - equivalentPositions]) = NULL; // to yarden - maybe we can delete the * and the warning will stop
                    i = -1; /*we removed one so we need to check again*/
                }
            }
            currLstSize++;
            myNode = myNode->next;
        }
        (*currLst)->size = oldLstSize - equivalentPositions;
        if (oldLstSize - equivalentPositions > 0)
        {
            (*currLst)->positions = realloc((*currLst)->positions, sizeof(chessPos) * ((*currLst)->size));
            checkAllocation((*currLst)->positions);
        }
        else
        {
            free((*currLst)->positions);
        }

    }
    return currLstSize;
}
void getTableBoundaries(chessPos position, int* pStartingPositionRow, int* pStartingPositionCol)
{
    int size = TABLE_SIZE, initialRowPositionTmp = position[0] - 'A', initialColPositionTmp = position[1] - '1';
    int reachedMaximumSize = 0;
    int i;
    if (initialRowPositionTmp + size <= 7)
    {
        /*There is no change in boundaries*/
        if (initialColPositionTmp + size > 7)
        {
            for (i = initialColPositionTmp; i >= initialColPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits*/
            {
                if (i + size <= 7)
                {
                    initialColPositionTmp = i + 1;
                    reachedMaximumSize = 1;
                }
            }
        }
    }
    else
    {
        if (initialColPositionTmp + size > 7)
        {
            for (i = initialColPositionTmp; i >= initialColPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits*/
            {
                if (i + size <= 7)
                {
                    initialColPositionTmp = i + 1;
                    reachedMaximumSize = 1;
                }
            }
        }
        for (i = initialRowPositionTmp; i >= initialRowPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits*/
        {
            if (i + size <= 7)
            {
                initialRowPositionTmp = i + 1;
                reachedMaximumSize = 1;
            }
        }
    }
    *pStartingPositionRow = initialRowPositionTmp;
    *pStartingPositionCol = initialColPositionTmp;
}
void printTree(PathTree tree)
{
    treeNode* node = tree.root;
    if (node)
    {
        printf("-----%c%c-----", node->position[0], node->position[1]);
        printTreeRec(node);
    }
}
void printTreeRec(treeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    else if (root->next_possible_positions != NULL)
    {
        treeNodeListCell* currNode = root->next_possible_positions;
        while (currNode != NULL)
        {
            printf("%c%c->", currNode->node->position[0], currNode->node->position[1]);
            printTreeRec(currNode->node);
            currNode = currNode->next;
        }
    }
    else
    {
        return;
    }
}
void printAllPossitionsRoutes(chessPosList* lst)
{
    chessPosCell* myNode = (*lst).head;
    while (myNode != NULL)
    {
        printf("%c%c->", myNode->position[0], myNode->position[1]);
        myNode = myNode->next;
    }
    puts("\n");
}
void freePathTree(PathTree* path_tree)
{
    treeNode* node = path_tree->root;
    if (node)
    {
        freePathTreeRec(node);
        free(node);
    }
}
void freePathTreeRec(treeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    else if (root->next_possible_positions != NULL)
    {
        treeNodeListCell* currNode = root->next_possible_positions;
        while (currNode != NULL)
        {
            //printf("%c%c->", currNode->node->position[0], currNode->node->position[1]);
            freePathTreeRec(currNode->node);
            treeNodeListCell* PrevNode = currNode;
            currNode = currNode->next;
            free(PrevNode->node);
            free(PrevNode);
        }
    }
    else
    {
        return;
    }
}