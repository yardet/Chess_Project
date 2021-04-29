#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALLOCATION_FAILURE -1
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


/*typedef struct _treeNode
{
    chessPos position;
    treeNodeListCell* next_possible_positions;
}treeNode;
typedef struct __treeNodeListCell
{
    treeNode* node;
    struct __treeNodeListCell* next;
}treeNodeListCell;*/

//void insertDataToEndList(chessPosList* res, int num);
bool isEmptyList(chessPosList* lst);
void freeList(chessPosList* lst);
chessPosArray*** validKnightMoves();
void printList(chessPosList* lst);
void check_allocation(void* res);
void display(chessPosList* lst);
void makeEmptyPosList(chessPosList* lst);
int isPosAppear(chessPosList* lst, char posFirstChar, char posSecondChar);
chessPosCell* createNewListNode(chessPos position, chessPosCell* nextNode);
void insertPosCellToEndList(chessPosList* lst, chessPosCell* node);
void Print_valid_moves(chessPosArray*** valid_moves);
void Free_valid_moves(chessPosArray*** valid_moves);
void main()
{
    chessPosArray*** valid_moves = validKnightMoves();
    Print_valid_moves(valid_moves);
    chessPosCell node9 = { { 'E','1' }, NULL };
    chessPosCell node8 = { {'E', '1'}, &node9 };
    chessPosCell node7 = { {'E', '1'}, &node8 };
    chessPosCell node6 = { {'E', '1'}, &node7 };
    chessPosCell node5 = { {'A', '4'}, &node6 };
    chessPosCell node4 = { {'H', '5'}, &node5 };
    chessPosCell node3 = { {'D', '8'}, &node4 };
    chessPosCell node2 = { {'H', '5'}, &node3 };
    chessPosCell node1 = { {'A', '4'}, &node2 };

    chessPosList newList = { &node1, &node9 };
    display(&newList);
    //freeList(&newList);
    Free_valid_moves(valid_moves);
}

chessPosArray*** validKnightMoves()
{
    chessPosArray*** arr = (chessPosArray***)malloc(sizeof(chessPosArray**) * 8);
    check_allocation(arr);
    int i, j;
    int count = 0;
    for (i = 0; i < 8; i++)
    {
        arr[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * 8);
        check_allocation(arr[i]);
        for (j = 0; j < 8; j++)
        {
            arr[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
            check_allocation(arr[i][j]);
            arr[i][j]->positions = (chessPos*)malloc(sizeof(chessPos));
            check_allocation(arr[i][j]->positions);
            if ((j + 1) <= 7 && (i - 2) >= 0)/*one right and two up*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i - 2) + 'A';
                arr[i][j]->positions[count][1] = (j + 1) + 1 + '0';
                count++;
            }
            if (j + 2 <= 7 && i - 1 >= 0)/*two right and one up*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i - 1) + 'A';
                arr[i][j]->positions[count][1] = (j + 2) + 1 + '0';
                count++;
            }
            if (j + 2 <= 7 && i + 1 <= 7)/*two right and one down*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i + 1) + 'A';
                arr[i][j]->positions[count][1] = (j + 2) + 1 + '0';
                count++;
            }
            if (j + 1 <= 7 && i + 2 <= 7)/*one right and two down*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i + 2) + 'A';
                arr[i][j]->positions[count][1] = (j + 1) + 1 + '0';
                count++;
            }
            if (j - 1 >= 0 && i + 2 <= 7)/*one left and two down*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i + 2) + 'A';
                arr[i][j]->positions[count][1] = (j - 1) + 1 + '0';
                count++;
            }
            if (j - 2 >= 0 && i + 1 <= 7)/*two left and one down*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i + 1) + 'A';
                arr[i][j]->positions[count][1] = (j - 2) + 1 + '0';
                count++;
            }
            if (j - 2 >= 0 && i - 1 >= 0)/*two left and one up*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i - 1) + 'A';
                arr[i][j]->positions[count][1] = (j - 2) + 1 + '0';
                count++;
            }
            if (j - 1 >= 0 && i - 2 >= 0)/*one left and two up*/
            {
                arr[i][j]->positions = (chessPos*)realloc(arr[i][j]->positions, sizeof(chessPos) * (count + 1));
                arr[i][j]->positions[count][0] = (i - 2) + 'A';
                arr[i][j]->positions[count][1] = (j - 1) + 1 + '0';
                count++;
            }
            arr[i][j]->size = count;
            count = 0;
        }
        puts("\n");
    }
    return arr;
}
void Print_valid_moves(chessPosArray*** valid_moves)
{
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
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
void Free_valid_moves(chessPosArray*** valid_moves)
{
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            free(valid_moves[i][j]->positions);
            free(valid_moves[i][j]);
        }
        free(valid_moves[i]);
    }
    free(valid_moves);
}
void display(chessPosList* lst)
{
    int lstSize = 0;
    chessPosList tmpList;
    makeEmptyPosList(&tmpList);
    chessPosCell* node = lst->head, * insertNode;
    chessPosCell* tmpNode = tmpNode = node->next;
    while (node != NULL)
    {
        while (tmpNode != NULL && node->position[0] == tmpNode->position[0] && node->position[1] == tmpNode->position[1]) // Cases of a row of the same position
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
            node->next = tmpNode->next; /*useless warning*/
            tmpNode->next = NULL;
            // free(tmpNode);/* this will not work if there hasn't been an allocation for this memory before*/
        }
        insertNode = createNewListNode(node->position, NULL);
        insertPosCellToEndList(&tmpList, insertNode);
        node = node->next;
        if (node != NULL)
        {
            tmpNode = node->next;
        }
        lstSize++;
    }
    *lst = tmpList;
    printList(lst);
}
void printList(chessPosList* lst)
{
    chessPosCell* node = lst->head;
    int j;
    int i;
    int count = 1;
    char sign;
    char chessarray[8][8][1];
    while (node)
    {
        chessarray[(int)node->position[0] - 65][(int)node->position[1] - 49][0] = count + '0';
        printf("%c%c ", node->position[0], node->position[1]);
        count++;
        node = node->next;

    }
    puts("\n");
    printf("    1 2 3 4 5 6 7 8  \n");
    for (i = 0; i < 8; i++)
    {
        printf("%c->", i + 'A');
        for (j = 0; j < 8; j++)
        {
            if (chessarray[i][j][0] > 1 && chessarray[i][j][0] <= 64)
                printf("|%c", chessarray[i][j][0]);
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
    check_allocation(node);
    node->position[0] = position[0];
    node->position[1] = position[1];
    node->next = nextNode;

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
void freeList(chessPosList* lst)
{
    chessPosCell* curr;
    chessPosCell* next;
    curr = lst->head;
    while (curr)
    {
        next = curr->next;
        free(curr->position);
        free(curr);
        curr = next;
    }
    lst->head = NULL;
    lst->tail = NULL;
}
void check_allocation(void* res)
{
    if (!res)
    {
        fprintf(stderr, "Allocation failure in \nExiting...\n");
        exit(ALLOCATION_FAILURE);
    }
}


