#pragma once
#include "ChessPos_Lists.h"
#include"TreeList.h"
#define ALLOCATION_FAILURE -1
void checkAllocation(void* res);
void menu();
void Position_integrity_check(chessPos position);
void Print_Menu(bool* Op_arr);