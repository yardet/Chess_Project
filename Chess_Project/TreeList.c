#define _CRT_SECURE_NO_WARNINGS
#include "TreeList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALLOCATION_FAILURE -1
int num_of_full_tracks = 0;
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
PathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    PathTree tree;
    tree.root= (treeNode*)malloc(sizeof(treeNode));
    check_allocation(tree.root);
    chessPosList lst; /*a list of all the positions that have been played*/
    makeEmptyPosList(&lst);
    if (!startingPosition)
    {
        puts("The starting position is empthy!\n");
        exit(-1);
    }
    tree.root->position[0] = startingPosition[0][0];
    tree.root->position[1] = startingPosition[0][1];
    findAllPossibleKnightPathsRec(lst,tree.root);
 //   printTree(tree);
    return tree;
}
void findAllPossibleKnightPathsRec(chessPosList lst, treeNode* root)
{
    int i;
    chessPosArray* Curr = validKnightMoves()[root->position[0] - 'A'][root->position[1] - '0' -1 ];/*Current position*/
    int array_size=deleteRepeatableCells(&Curr, lst, root->position);      
    chessPosCell* node = createNewListNode(root->position, NULL);
    insertPosCellToEndList(&lst, node);
       
    if (Curr->size == 0)
    { 
        if (array_size == TABLE_SIZE*TABLE_SIZE)
        {
            //print_tracks(&lst);//just a test for question 4
            num_of_full_tracks++;//just a test for question 4
        }
        root->next_possible_positions = NULL;
        return;
    }     
    else
    {
        treeNodeListCell* res=root->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell) * Curr->size);/*allocation of posible positions*/
        check_allocation(root->next_possible_positions);
        res->node = NULL;
        treeNode* next;
        for (i = 0; i < Curr->size; i++)
        {

            next=allocation_Tree_Node(&res, Curr->positions[i]);    
            findAllPossibleKnightPathsRec(lst, next); 
            deletePosCellFromEndList(&lst);
        }
    } 
}
treeNode* allocation_Tree_Node(treeNodeListCell** curr, char* _position)
{

    if (!(*curr)->node)/*Begin of list*/
    {
        (*curr)->node = (treeNode*)malloc(sizeof(treeNode));
        check_allocation((*curr)->node);
        (*curr)->node->position[0] = _position[0];
        (*curr)->node->position[1] = _position[1];
        (*curr)->next = NULL;
    }
    else
    { 
        treeNodeListCell* prev = (*curr);
        treeNodeListCell* prev_old=prev;
        while (prev)
        {
            //if (prev->next == NULL)
                //break;
            prev_old = prev;
            prev = prev->next;
        }
        if (!_position)
        {
            (*curr)->node = NULL;
            prev = NULL;
        }
        else
        {
            prev = (chessPosCell*)malloc(sizeof(chessPosCell));
            check_allocation(prev);
            prev->node = (treeNode*)malloc(sizeof(treeNode));
            check_allocation(prev->node);
            prev->node->position[0] = _position[0];
            prev->node->position[1] = _position[1];
            prev_old->next = prev;
            prev_old->next->next = NULL;
            return prev_old->next->node;
        }
    }
    return (*curr)->node;
}
bool Is_exist_in_list( chessPosList lst, chessPos curr_position)
{
    if (isEmptyList(&lst))
    {
        return false;
    }
    else
    {
        chessPosCell* myNode = lst.head;
        while (myNode)
        {
            if (myNode->position[0] == curr_position[0] && myNode->position[1] == curr_position[1])
            {
                return true;
            }
            else
            {
                myNode = myNode->next;
            }
        }
    }
}
int deleteRepeatableCells(chessPosArray** Curr, chessPosList lst)
{
    int old_size = (*Curr)->size;
    int i, j, array_size = 1;
    if (isEmptyList(&lst))
    {
        return;
    }
    else
    {
        int equivalentPositions = 0;
        chessPosCell* myNode = lst.head;
        chessPos* positions = (*Curr)->positions;
        while (myNode)
        {
            for (i = 0; i < old_size- equivalentPositions; i++)
            {
                if (positions[i][0] == myNode->position[0] && positions[i][1] == myNode->position[1])
                {
                    if (equivalentPositions != old_size-1)
                    {  
                        for (j = i; j < old_size - equivalentPositions; j++)
                        {
                            positions[j][0] = positions[j + 1][0];
                            positions[j][1] = positions[j + 1][1];
                        }
                    }
                    equivalentPositions++;
                    *positions[old_size - equivalentPositions] = NULL;
                    i=-1;/*we removed one so we need to check again*/
                }
            }
            array_size++;
            myNode = myNode->next;
        }
        (*Curr)->size= old_size - equivalentPositions;
        (*Curr)->positions=realloc((*Curr)->positions, sizeof(chessPos) * ((*Curr)->size)+1);
        check_allocation((*Curr)->positions);
        if (old_size - equivalentPositions == 0)
        {
            free((*Curr)->positions);
        }

    }
    return array_size;
}
void Finding_Table_Boundaries(chessPos position, int* start_position_row, int* start_position_col)
{
    int size = TABLE_SIZE;
    int starting_col = position[1] -'1';
    int starting_row = position[0] -'A';
    bool is_good = false;
    if (starting_row + size <= 7)
    {
        
            /*There is no change in boundaries */
        if (starting_col + size > 7)
        {
            for (int i = starting_col; i >= starting_col-size; i--)/*Find out when it is within limits*/
            {
                if (i + size <= 7)
                {
                    starting_col = i + 1;
                    break;
                }
            }
        }
    }
    else
    {
        if (starting_col + size > 7)
        {
            for (int i = starting_col;i >= starting_col - size; i--)/*Find out when it is within limits*/
            {
                if (i + size <= 7)
                {
                    starting_col = i +1;
                    break;
                }
            }
        }
        is_good = false;
        for (int i = starting_row; i >= starting_row - size; i--)/*Find out when it is within limits*/
        {
            if (i + size <= 7)
            {
                starting_row = i +1;
                break;
            }
        }
    }
    *start_position_row = starting_row;
    *start_position_col = starting_col;
}

/*void insertTreeNodeDataToEndList(treeNode* res, chessPos value)
{

}
void insertTreeNodetoEndList(chessPosList* lst, treeNode* node)
{

}*/
void printTree(PathTree tree)
{
    treeNode* node = tree.root;
    if (node)
    {
        printf("-----%c%c-----", node->position[0], node->position[1]);
        printTreeRec(node);
    }
        
    
}
treeNode* printTreeRec(treeNode* root)
{
    
    treeNodeListCell* prev;
    if (!root)
        return;
    if (root->next_possible_positions)
    {
        prev = root->next_possible_positions;
        while (prev)
        {
            
            printf("%c%c--", printTreeRec(prev->node)->position[0], printTreeRec(prev->node)->position[1]);
            printTreeRec(prev->node);
            prev = prev->next;
        }
    }
    else
    {
        return;
    }


        
}

void print_tracks(chessPosList* lst)
{
    chessPosCell* myNode = (*lst).head;
    while (myNode)
    {
        printf("%c%c->", myNode->position[0], myNode->position[1]);
        myNode = myNode->next;
    }
    puts("\n");
}