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
int t = 0;
//Probably irrelevant (not used-not deleted yet)
/*void getTableBoundaries(chessPos position, int* pStartingPositionRow, int* pStartingPositionCol)//
{
    int size = TABLE_SIZE, initialRowPositionTmp = position[0] - 'A', initialColPositionTmp = position[1] - '1';
    int reachedMaximumSize = 0;
    int i;
    if (initialRowPositionTmp + size <= 7)
    {
        /*There is no change in boundaries
        if (initialColPositionTmp + size > 7)
        {
            for (i = initialColPositionTmp; i >= initialColPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits
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
            for (i = initialColPositionTmp; i >= initialColPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits
            {
                if (i + size <= 7)
                {
                    initialColPositionTmp = i + 1;
                    reachedMaximumSize = 1;
                }
            }
        }
        for (i = initialRowPositionTmp; i >= initialRowPositionTmp - size && reachedMaximumSize == 0; i--) /*Finds out when it is within limits
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
}*/

//Q3
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    pathTree tree;
    tree.root = (treeNode*)malloc(sizeof(treeNode));
    if (tree.root);
    {
        if (!startingPosition)
        {
            puts("Starting position is empty!\n");
            exit(ALLOCATION_FAILURE);
        }
        tree.root->position[0] = startingPosition[0][0];
        tree.root->position[1] = startingPosition[0][1];
        bool** positions_history = getBooleanMatrix(TABLE_SIZE, TABLE_SIZE);
        if (positions_history)
        {
            chessPosArray*** Possible_moves = validKnightMoves();
            findAllPossibleKnightPathsRec(&positions_history, tree.root, Possible_moves);
            freeValidMoves(Possible_moves);
            freeBooleanMatrix(positions_history, TABLE_SIZE);
        }
        else
        {
            puts("error with array");
            exit(ALLOCATION_FAILURE);
        }
    }
    return tree;
}
void findAllPossibleKnightPathsRec(bool*** positions_history, treeNode* root, chessPosArray*** Possible_moves)
{
    chessPosArray* currPosition = (chessPosArray*)malloc(sizeof(chessPosArray));/*copy of possible moves*/
    checkAllocation(currPosition);
    currPosition->size = Possible_moves[root->position[0] - 'A'][root->position[1] - '1']->size;
    currPosition->positions = (chessPos*)malloc(sizeof(chessPos*)* currPosition->size);
    checkAllocation(currPosition->positions);
    int i;
    for (i = 0; i < currPosition->size; i++)
    {
        currPosition->positions[i][0] = Possible_moves[root->position[0] - 'A'][root->position[1] - '1']->positions[i][0];
        currPosition->positions[i][1] = Possible_moves[root->position[0] - 'A'][root->position[1] - '1']->positions[i][1];
    }  
    deleteRepeatableCells(currPosition, *positions_history);
    (*positions_history)[root->position[0] - 'A'][root->position[1] - '1'] = true;
    if (currPosition->size == 0)
    {
        t++;
        root->next_possible_positions = NULL;
        (*positions_history)[root->position[0] - 'A'][root->position[1] - '1'] = false;
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
        for (i = 0; i < currPosition->size; i++)
        {
            nextNode = allocateNewTreeNode(&res, currPosition->positions[i]);
            findAllPossibleKnightPathsRec(positions_history, nextNode, Possible_moves);
        }     
        (*positions_history)[root->position[0] - 'A'][root->position[1] - '1'] = false;
        free(currPosition->positions);
        free(currPosition);
        return;
    }
}
void deleteRepeatableCells(chessPosArray* currLst, bool** positions_history)
{
    int oldLstSize = (currLst)->size;
    int i, j, currLstSize = 1;
    int equivalentPositions = 0;
    chessPos* positions = (currLst)->positions;
    for (i = 0; i < oldLstSize - equivalentPositions; i++)
    {
        if(positions_history[positions[i][0] - 'A'][positions[i][1] - '1']==true)
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
    (currLst)->size = oldLstSize - equivalentPositions;
    if (oldLstSize - equivalentPositions > 0)
    {
        (currLst)->positions = realloc((currLst)->positions, sizeof(chessPos) * ((currLst)->size));
        checkAllocation((currLst)->positions);
    }
    else
    {
        free((currLst)->positions);
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

void printTree(pathTree tree)
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

// Q4
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
    chessPosList * pathList =(chessPosList*)malloc(sizeof(chessPosList));
    makeEmptyChessPosList(pathList);
    if (path_tree->root)
    {
        int* possibleRouteIsFound = (int*)malloc(sizeof(int));
        if (possibleRouteIsFound != NULL)
        {
            *possibleRouteIsFound = 0;
            int* possibleRoutesCounter = (int*)malloc(sizeof(int));
            if (possibleRoutesCounter != NULL)
            {
                *(possibleRoutesCounter) = 0;
                pathList = findKnightPathCoveringAllBoardRec(pathList, path_tree->root, possibleRouteIsFound, possibleRoutesCounter);
                if (pathList)
                {
                    printAllPossitionsRoutes(pathList);
                    return pathList;
                }
                free(possibleRoutesCounter);
            }
        }
    }
    return NULL;
}
chessPosList* findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root,int* possibleRouteIsFound,int* possibleRoutesCounter)
{
    if (*possibleRouteIsFound == 1)
    {
        return lst;
    }
    else
    {
        chessPosCell* node = createNewListNode(root->position, NULL);
        (*possibleRoutesCounter)++;
        insertChessPosCellToEndList(lst, node);
        treeNodeListCell* res = root->next_possible_positions;
        if (res == NULL)
        {
            if ((*possibleRoutesCounter) == TABLE_SIZE * TABLE_SIZE)
            {
                *possibleRouteIsFound = 1;
                findKnightPathCoveringAllBoardRec(lst, root, possibleRouteIsFound, possibleRoutesCounter);
            }
            return;
        }
        else
        {
            treeNodeListCell* currNode = res;
            treeNodeListCell* prevNode = res;
            while (currNode != NULL && (*possibleRouteIsFound) == 0)
            {
                prevNode = currNode;/*remeber the currnode before he becomes null*/
                findKnightPathCoveringAllBoardRec(lst, prevNode->node, possibleRouteIsFound,possibleRoutesCounter);
                if ((*possibleRouteIsFound) == 1)
                {
                    return lst;
                }
                else
                {
                    currNode = currNode->next;
                    deleteLastChessPosCellFromList(lst);
                    (*possibleRoutesCounter)--;
                } 
            }
            if ((*possibleRoutesCounter) == 1)
            {
                deleteLastChessPosCellFromList(lst);
                return NULL;
            }  
        }
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

// Not used
bool positionExistsInList(chessPosList lst, chessPos currPosition)
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

void freePathTree(pathTree* path_tree)
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