#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ChessPos_Lists.h"
#include "Additional functions.h"

// Q1
chessPosArray*** validKnightMoves()
{
    chessPosArray*** possiblePositionsArr = (chessPosArray***)malloc(sizeof(chessPosArray**) * TABLE_SIZE);
    if (possiblePositionsArr)
    {
        int i, j, countPossiblePositions = 0;
        int initialRow = STARTING_POSITION_ROW; /*row boundary location*/
        int initialCol = STARTING_POSITION_COL; /*col boundary location*/
        for (i = initialRow; i < initialRow + TABLE_SIZE; i++)
        {
            possiblePositionsArr[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * TABLE_SIZE);
            checkAllocation(possiblePositionsArr[i]);
            for (j = initialRow; j < initialRow + TABLE_SIZE; j++)
            {
                possiblePositionsArr[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
                checkAllocation(possiblePositionsArr[i][j]);
                possiblePositionsArr[i][j]->positions = (chessPos*)malloc(sizeof(chessPos) * (CHESS_ARRAY_SIZE));
                checkAllocation(possiblePositionsArr[i][j]->positions);
                if ((j + 1) < TABLE_SIZE + initialRow && (i - 2) >= initialRow) /*one right and two up*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 2 < TABLE_SIZE + initialRow && i - 1 >= initialRow) /*two right and one up*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 2 < TABLE_SIZE + initialRow && i + 1 < TABLE_SIZE + initialRow) /*two right and one down*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j + 1 < TABLE_SIZE + initialRow && i + 2 < TABLE_SIZE + initialRow) /*one right and two down*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j + 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 1 >= initialRow && i + 2 < TABLE_SIZE + initialRow) /*one left and two down*/
                {

                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 2) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 1) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 2 >= initialRow && i + 1 < TABLE_SIZE + initialRow) /*two left and one down*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i + 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 2 >= initialRow && i - 1 >= initialRow) /*two left and one up*/
                {
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][0] = (i - 1) + 'A';
                    possiblePositionsArr[i][j]->positions[countPossiblePositions][1] = (j - 2) + 1 + '0';
                    countPossiblePositions++;
                }
                if (j - 1 >= initialRow && i - 2 >= initialRow) /*one left and two up*/
                {
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
                else
                {
                    exit(FAILURE);
                }
            }
        }
    }
    return possiblePositionsArr;
}
void printValidMoves(chessPosArray*** valid_moves)/*Test function- irrelevant to project requirements*/
{
    for (int i = STARTING_POSITION_ROW; i < STARTING_POSITION_ROW + TABLE_SIZE; i++)
    {
        for (int j = STARTING_POSITION_COL; j < STARTING_POSITION_COL + TABLE_SIZE; j++)
        {
            printf("%c%d->", i + 'A', j + 1);
            for (int k = 0; k < (int)valid_moves[i][j]->size; k++)
            {
                printf("%c%c,", valid_moves[i][j]->positions[k][0], valid_moves[i][j]->positions[k][1]);
            }
            puts("\n");
        }
        puts("NULL");
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

//Q2
chessPosList getExampleChessPosList()
{
    /*Example as shown in instructions*/
    chessPosCell* node6 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node6)
    {
        node6->position[0] = 'E';
        node6->position[1] = '1';
        node6->next = NULL;
    }
    chessPosCell* node5 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node5)
    {
        node5->position[0] = 'A';
        node5->position[1] = '4';
        node5->next = node6;
    }
    chessPosCell* node4 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node4)
    {
        node4->position[0] = 'H';
        node4->position[1] = '5';
        node4->next = node5;
    }
    chessPosCell* node3 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node3)
    {
        node3->position[0] = 'D';
        node3->position[1] = '8';
        node3->next = node4;
    }
    chessPosCell* node2 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node2)
    {
        node2->position[0] = 'H';
        node2->position[1] = '5';
        node2->next = node3;
    }
    chessPosCell* node1 = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node1)
    {
        node1->position[0] = 'A';
        node1->position[1] = '4';
        node1->next = node2;
    }

    chessPosList newList = { node1, node6 };
    return newList;
}

void display(chessPosList* lst)
{
    int i, j;
    bool** allAppearingCellsInBoard = getBooleanMatrix(TABLE_SIZE, TABLE_SIZE);
    chessPosCell* currNode = lst->head, * nextNode = currNode->next, * prevNode, * insertNodeToList;
    makeEmptyChessPosList(lst);
    while (currNode != NULL)
    {
        while (nextNode != NULL && currNode->position[0] == nextNode->position[0] && currNode->position[1] == nextNode->position[1]) // Cases of a row with an equal position
        {
            currNode->next = nextNode->next;
            nextNode->next = NULL;
            free(nextNode);/* this will not work if there hasn't been an allocation for this memory before*/
            nextNode = currNode->next;
        }
        if (nextNode != NULL)
        {
            while (allAppearingCellsInBoard[nextNode->position[0] - 'A'][nextNode->position[1] - '1'] == true) // Checks if the position already appears in the template (tmpList)
            {
                currNode->next = nextNode->next;
                nextNode->next = NULL;
                free(nextNode); // this will not work if there hasn't been an allocation for this memory before
                if (currNode->next != NULL)
                {
                    nextNode = currNode->next;
                }
            }
        }
        if (allAppearingCellsInBoard[currNode->position[0] - 'A'][currNode->position[1] - '1'] == true) // Checks if the position already appears in the template (tmpList)
        {
            if (nextNode)
            {
                currNode->next = nextNode->next;
                nextNode->next = NULL;
            }
        }
        insertNodeToList = createNewListNode(currNode->position, NULL);
        insertChessPosCellToEndList(lst, insertNodeToList);
        allAppearingCellsInBoard[currNode->position[0] - 'A'][currNode->position[1] - '1'] = true;
        prevNode = currNode;
        currNode = currNode->next;
        free(prevNode);
        if (currNode != NULL)
        {
            nextNode = currNode->next;
        }
    }
    freeBooleanMatrix(allAppearingCellsInBoard, TABLE_SIZE);
    printList(lst);
}

bool** getBooleanMatrix(int rowSize, int colSize)
{
    int i, j;
    bool** arr = (bool**)malloc(rowSize * sizeof(bool*));
    if (arr)
    {
        for (i = 0; i < rowSize; i++)
        {
            arr[i] = (bool*)malloc(colSize * sizeof(bool));
            if (arr[i])
            {
                for (j = 0; j < colSize; j++)
                {
                    arr[i][j] = false;
                }
            }
        }
    }

    return arr;
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

void makeEmptyChessPosList(chessPosList* lst)
{
    lst->head = lst->tail = NULL;
}

void insertChessPosCellToEndList(chessPosList* lst, chessPosCell* node)
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

bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

void freeBooleanMatrix(bool** arr, int rowSize)
{
    int i;
    for (i = 0; i < rowSize; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void printList(chessPosList* lst)/*print the list*/
{
    chessPosCell* node = lst->head;
    int i, j, count = 1;
    int*** chessArray = allocation_int_chess_array();
    while (node != NULL)
    {
        chessArray[node->position[0] - 'A'][node->position[1] - '1'][0] = count;
        printf("%c%c->", node->position[0], node->position[1]);
        count++;
        node = node->next;

    }
    puts("NULL\n");
    printf("%*c", 2, ' ');
    for (i = 0; i < TABLE_SIZE; i++)
    {
        printf("%*d", 3, i + 1);
    }
    printf("\n");
    for (i = 0; i < TABLE_SIZE; i++)
    {
        printf("%c->", i + 'A');
        for (j = 0; j < TABLE_SIZE; j++)
        {
            if (chessArray[i][j][0] >= 1 && chessArray[i][j][0] <= TABLE_SIZE * TABLE_SIZE)
            {
                if (chessArray[i][j][0] >= 10)
                    printf("|%*d", 2, chessArray[i][j][0]);
                else
                    printf("|%d ", chessArray[i][j][0]);
            }
            else
                printf("|  ");
        }
        printf("|");
        puts("\n");
    }
    puts("--------------------\n");
    free_int_chess_array(chessArray);
}
int*** allocation_int_chess_array()
{
    int*** chessArray = (int***)malloc(sizeof(int**) * TABLE_SIZE);
    checkAllocation(chessArray);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        chessArray[i] = (int**)malloc(sizeof(int*) * TABLE_SIZE);
        checkAllocation(chessArray[i]);
        for (int j = 0; j < TABLE_SIZE; j++)
        {
            chessArray[i][j] = (int*)malloc(sizeof(int));
            checkAllocation(chessArray[i][j]);
        }
    }
    return chessArray;
}
void free_int_chess_array(int*** chess_array)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (int j = 0; j < TABLE_SIZE; j++)
        {
            free(chess_array[i][j]);
        }
        free(chess_array[i]);
    }
    free(chess_array);
}
void freeList(chessPosList* lst)
{
    chessPosCell* currNode = lst->head, * nextNode;
    while (currNode != NULL)
    {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    lst->head = NULL;
    lst->tail = NULL;
}

// Q3, Q4
void deleteLastChessPosCellFromList(chessPosList* lst)
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

// Q6
bool isValidPath(chessPosList lst)
{
    chessPosCell* currNode = lst.head, * nextNode = currNode->next;
    while (nextNode != NULL)
    {
        // Row cases
        if (currNode->position[0] == 'A' && (nextNode->position[0] != 'B' && nextNode->position[0] != 'C'))
        {
            return false;
        }
        else if (currNode->position[0] == 'B' && (nextNode->position[0] != 'A' && nextNode->position[0] != 'C' && nextNode->position[0] != 'D'))
        {
            return false;
        }
        else if (currNode->position[0] == 'C' && (nextNode->position[0] != 'A' && nextNode->position[0] != 'B' && nextNode->position[0] != 'D' && nextNode->position[0] != 'E'))
        {
            return false;
        }
        else if (currNode->position[0] == 'D' && (nextNode->position[0] != 'B' && nextNode->position[0] != 'C' && nextNode->position[0] != 'E' && nextNode->position[0] != 'F'))
        {
            return false;
        }
        else if (currNode->position[0] == 'E' && (nextNode->position[0] != 'C' && nextNode->position[0] != 'D' && nextNode->position[0] != 'F' && nextNode->position[0] != 'G'))
        {
            return false;
        }
        else if (currNode->position[0] == 'F' && (nextNode->position[0] != 'D' && nextNode->position[0] != 'E' && nextNode->position[0] != 'G' && nextNode->position[0] != 'H'))
        {
            return false;
        }
        else if (currNode->position[0] == 'G' && (nextNode->position[0] != 'E' && nextNode->position[0] != 'F' && nextNode->position[0] != 'H'))
        {
            return false;
        }
        else if (currNode->position[0] == 'H' && (nextNode->position[0] != 'F' && nextNode->position[0] != 'G'))
        {
            return false;
        }
        // Column cases
        if (currNode->position[1] == '1' && (nextNode->position[1] != '2' && nextNode->position[1] != '3'))
        {
            return false;
        }
        else if (currNode->position[1] == '2' && (nextNode->position[1] != '1' && nextNode->position[1] != '3' && nextNode->position[1] != '4'))
        {
            return false;
        }
        else if (currNode->position[1] == '3' && (nextNode->position[1] != '1' && nextNode->position[1] != '2' && nextNode->position[1] != '4' && nextNode->position[1] != '5'))
        {
            return false;
        }
        else if (currNode->position[1] == '4' && (nextNode->position[1] != '2' && nextNode->position[1] != '3' && nextNode->position[1] != '5' && nextNode->position[1] != '6'))
        {
            return false;
        }
        else if (currNode->position[1] == '5' && (nextNode->position[1] != '3' && nextNode->position[1] != '4' && nextNode->position[1] != '6' && nextNode->position[1] != '7'))
        {
            return false;
        }
        else if (currNode->position[1] == '6' && (nextNode->position[1] != '4' && nextNode->position[1] != '5' && nextNode->position[1] != '7' && nextNode->position[1] != '8'))
        {
            return false;
        }
        else if (currNode->position[1] == '7' && (nextNode->position[1] != '5' && nextNode->position[1] != '6' && nextNode->position[1] != '8'))
        {
            return false;
        }
        else if (currNode->position[1] == '8' && (nextNode->position[1] != '6' && nextNode->position[1] != '7'))
        {
            return false;
        }

        currNode = nextNode;
        nextNode = nextNode->next;
    }
    return true;
}

bool isPathCoveringAllBoard(chessPosList lst)
{
    chessPosCell* currNode = lst.head;
    bool** allAppearingCellsInBoard = getBooleanMatrix(TABLE_SIZE, TABLE_SIZE);
    while (currNode != NULL)
    {
        allAppearingCellsInBoard[currNode->position[0] - 'A'][currNode->position[1] - '1'] = true;
        currNode = currNode->next;
    }
    int i, j;
    for (i = 0; i < TABLE_SIZE; i++)
    {
        for (j = 0; j < TABLE_SIZE; j++)
        {
            if (allAppearingCellsInBoard[i][j] == false)
            {
                freeBooleanMatrix(allAppearingCellsInBoard, TABLE_SIZE);
                return false;
            }
        }
    }
    freeBooleanMatrix(allAppearingCellsInBoard, TABLE_SIZE);
    return true;
}