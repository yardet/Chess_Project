#pragma once
#include "ChessPos_Lists.h"
#include"TreeList.h"
#define FAILURE -1

void checkAllocation(void* res);
void menu();
void positionIntegrityCheck(chessPos position);
void printMenu(bool* operationArr);