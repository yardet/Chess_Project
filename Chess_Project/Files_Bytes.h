#pragma once
#include "Additional functions.h"
#include <stdio.h>
#include <stdbool.h>
#define BITWISE_SHIFT 3

// Q5
void saveListToBinFile(char* file_name, chessPosList* pos_list);
int getPosListSize(chessPosCell* node);
unsigned short int getSizeInBytes(int size);
unsigned int getFiveCellsInBytes(chessPosCell** pnode);

// Q6
int checkAndDisplayPathFromFile(char* file_name);
chessPosList getCellsFromBinaryFile(FILE* file);