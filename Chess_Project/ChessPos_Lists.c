#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ChessPos_Lists.h"
#include "Additional functions.h"

chessPosArray*** validKnightMoves()
{
    chessPosArray*** possiblePositionsArr = (chessPosArray***)malloc(sizeof(chessPosArray**) * TABLE_SIZE);
    if (possiblePositionsArr)
    {
        int i, j, countPossiblePositions = 0;
        int initialRow = STARTING_POSITION_ROW; /*row boundary location*/
        int initialCol = STARTING_POSITION_COL; /*col boundary location*/
        int sizeOfTable = TABLE_SIZE;
        for (i = initialRow; i < initialRow + sizeOfTable; i++)
        {
            possiblePositionsArr[i] = (chessPosArray**)malloc(sizeof(chessPosArray) * (sizeOfTable));
            checkAllocation(possiblePositionsArr[i]);
            for (j = initialRow; j < initialRow + sizeOfTable; j++)
            {
                possiblePositionsArr[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray) + 1);
                checkAllocation(possiblePositionsArr[i][j]);
                possiblePositionsArr[i][j]->positions = (chessPos*)malloc(sizeof(chessPos) * (CHESS_ARRAY_SIZE));
                checkAllocation(possiblePositionsArr[i][j]->positions);
                if ((j + 1) < sizeOfTable + initialRow && (i - 2) >= initialRow) /*one right and two up*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 2 < sizeOfTable + initialRow && i - 1 >= initialRow) /*two right and one up*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 2 < sizeOfTable + initialRow && i + 1 < sizeOfTable + initialRow) /*two right and one down*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 1 < sizeOfTable + initialRow && i + 2 < sizeOfTable + initialRow) /*one right and two down*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 1 >= initialRow && i + 2 < sizeOfTable + initialRow) /*one left and two down*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 2 >= initialRow && i + 1 < sizeOfTable + initialRow) /*two left and one down*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 2 >= initialRow && i - 1 >= initialRow) /*two left and one up*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 1 >= initialRow && i - 2 >= initialRow) /*one left and two up*/
                {
                    //possiblePositionsArr[i][j]->positions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (count + 1));
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 1) + 1 + '0';
                    countPossiblePositions++;
                }
                chessPos* availablePositions = (chessPos*)realloc(possiblePositionsArr[i][j]->positions, sizeof(chessPos) * (countPossiblePositions));
                if (availablePositions)
                {
                    possiblePositionsArr[i][j]->positions = availablePositions;
                    possiblePositionsArr[i][j]->size = countPossiblePositions;
                    countPossiblePositions = 0;
                }
            }
        }
    }
    return possiblePositionsArr;
}
void printValidMoves(chessPosArray*** valid_moves)
{
    for (int i = STARTING_POSITION_ROW; i < STARTING_POSITION_ROW + TABLE_SIZE; i++)
    {
        for (int j = STARTING_POSITION_COL; j < STARTING_POSITION_COL + TABLE_SIZE; j++)
        {
            printf("%c%d->", i + 'A', j + 1);
            for (int k = 0; k < valid_moves[i][j]->size; k++)
            {
                printf("%c%c,", valid_moves[i][j]->positions[k][0], valid_moves[i][j]->positions[k][1]);
            }
            puts("\n");
        }
        puts("\n");
    }
}
void freeValidMoves(chessPosArray*** valid_moves)
{
    for (int i = STARTING_POSITION_ROW; i < STARTING_POSITION_ROW + TABLE_SIZE; i++)
    {
        for (int j = STARTING_POSITION_COL; j < STARTING_POSITION_COL + TABLE_SIZE; j++)
        {
            free(valid_moves[i][j]->positions);
            free(valid_moves[i][j]);
        }
        free(valid_moves[i]);
    }
    free(valid_moves);
}
void display(chessPosList* plst)
{
    int lstSize = 0;
    chessPosList tmpList;
    chessPosCell* node = plst->head, * tmpNode = node->next, * insertNodeToList;
    makeEmptyPosList(&tmpList);
    while (node != NULL)
    {
        while (tmpNode != NULL && node->position[0] == tmpNode->position[0] && node->position[1] == tmpNode->position[1]) // Cases of a row with an equal position
        {
            node->next = tmpNode->next;
            tmpNode->next = NULL;
            //  free(tmpNode);/* this will not work if there hasn't been an allocation for this memory before*/
            tmpNode = node->next;
        }
        if (tmpNode != NULL)
        {
            while (isPosAppear(&tmpList, tmpNode->position[0], tmpNode->position[1])) // Checks if the position already appears in the template (tmpList)
            {
                node->next = tmpNode->next;
                tmpNode->next = NULL;
                //  free(tmpNode);/* this will not work if there hasn't been an allocation for this memory before*/
                if (node->next != NULL)
                {
                    tmpNode = node->next;
                }
            }
        }
        if (isPosAppear(&tmpList, node->position[0], node->position[1])) // Checks if the position already appears in the template (tmpList)
        {
            if (tmpNode)
            {
                node->next = tmpNode->next;
                tmpNode->next = NULL;
            }
            // free(tmpNode);/* this will not work if there hasn't been an allocation for this memory before*/
        }
        insertNodeToList = createNewListNode(node->position, NULL);
        insertPosCellToEndList(&tmpList, insertNodeToList);
        node = node->next;
        if (node != NULL)
        {
            tmpNode = node->next;
        }
        lstSize++;
    }
    *plst = tmpList;
    printList(plst);
}
void printList(chessPosList* lst)
{
    chessPosCell* node = lst->head;
    int i, j, count = 1;
    char sign, chessArray[CHESS_ARRAY_SIZE][CHESS_ARRAY_SIZE][1];
    while (node != NULL)
    {
        chessArray[(int)node->position[0] - 65][(int)node->position[1] - 49][0] = count + '0';
        printf("%c%c ", node->position[0], node->position[1]);
        count++;
        node = node->next;

    }
    puts("\n");
    printf("    1 2 3 4 5 6 7 8  \n");
    for (i = 0; i < CHESS_ARRAY_SIZE; i++)
    {
        printf("%c->", i + 'A');
        for (j = 0; j < CHESS_ARRAY_SIZE; j++)
        {
            if (chessArray[i][j][0] > 1 && chessArray[i][j][0] <= 64)
                printf("|%c", chessArray[i][j][0]);
            else
                printf("| ");
        }
        printf("|");
        puts("\n");
    }
    puts("--------------------\n");
}
void makeEmptyPosList(chessPosList* lst)
{
    lst->head = lst->tail = NULL;
}
bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}
int isPosAppear(chessPosList* lst, char posFirstChar, char posSecondChar)
{
    chessPosCell* node = lst->head;
    while (node != NULL)
    {
        char lstFirstChar = node->position[0], lstSecondChar = node->position[1];
        if (lstFirstChar == posFirstChar && lstSecondChar == posSecondChar)
        {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
chessPosCell* createNewListNode(chessPos position, chessPosCell* nextNode)
{
    chessPosCell* node = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node)
    {
        node->position[0] = position[0];
        node->position[1] = position[1];
        node->next = nextNode;
    }
    else
    {
        exit(1);
    }
    return node;
}
void insertPosCellToEndList(chessPosList* lst, chessPosCell* node)
{
    if (isEmptyList(lst))
    {
        lst->head = lst->tail = node;
    }
    else
    {
        lst->tail->next = node;
        lst->tail = node;
    }
    node->next = NULL;
}
void deletePosCellFromEndList(chessPosList* lst)
{
    chessPosCell* currNode = lst->head, * prevNode = currNode;
    while (currNode->next != NULL)
    {
        prevNode = currNode;
        currNode = currNode->next;
    }
    free(currNode);
    prevNode->next = NULL;
    lst->tail = prevNode;
}
void freeList(chessPosList* lst)
{
    chessPosCell* curr, * next;
    curr = lst->head;
    while (curr != NULL)
    {
        next=curr;
        next = curr->next;
        free(curr->position);
        free(curr);
        curr = next;
    }
    lst->head = NULL;
    lst->tail = NULL;
}
