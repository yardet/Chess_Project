#pragma once
#include "ChessPos_Lists.h"
#include"TreeList.h"
#include "Additional functions.h"
#include <stdio.h>

void saveListToBinFile(char* file_name, chessPosList* pos_list);
int getPosListSize(chessPosCell* node);
unsigned short int getSizeInBytes(int size);
unsigned int getFiveCellsInBytes(chessPosCell** pnode);
void printCellsFromBinaryFile(FILE* file);