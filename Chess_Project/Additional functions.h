#pragma once
#include "ChessPos_Lists.h"
#include"TreeList.h"
#define ALLOCATION_FAILURE -1
void checkAllocation(void* res);
void menu();
void positionIntegrityCheck(chessPos position);
void printMenu(bool* Op_arr);