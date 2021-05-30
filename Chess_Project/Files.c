#define _CRT_SECURE_NO_WARNINGS
#include "Files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	chessPosCell* curr = pos_list->head;
	int posListSize = getPosListSize(curr);
	FILE* fp = fopen(file_name, "wb");
	checkAllocation(fp);
	unsigned short int posListSizeBytes = getSizeInBytes(posListSize);
	fwrite(&posListSizeBytes, sizeof(unsigned short int), 1, fp);
	while (curr != NULL)
	{
		int upToFiveChessPosCellsInBytes = getFiveCellsInBytes(&curr);
		fwrite(&upToFiveChessPosCellsInBytes, sizeof(unsigned int), 1, fp);
	}
	fclose(fp);
}

int getPosListSize(chessPosCell* node)
{
	int size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return size;
}

unsigned short int getSizeInBytes(int size)
{
	unsigned short int rightMask = 1;
	unsigned short int sizeInBytes = 0;
	int i;
	for (i = 0; i < sizeof(unsigned short int) * 8; i++)
	{
		sizeInBytes += rightMask << i & size % 2 << i;
		size = size / 2;
	}

	return sizeInBytes;
}

unsigned int getFiveCellsInBytes(chessPosCell** pnode)
{
	unsigned char rowValue, colValue;
	unsigned int resInBytes = 0;
	unsigned int shiftSize = 29;
	unsigned int leftMask = (1 << 31) + (1 << 30) + (1 << 29);
	int numOfLoops = 0;
	while (numOfLoops < 5 && *pnode != NULL)
	{
		rowValue = (*pnode)->position[0] - 'A';
		resInBytes += rowValue << shiftSize & leftMask;
		leftMask = leftMask >> 3;
		shiftSize = shiftSize - 3;
		colValue = (*pnode)->position[1] - '1';
		resInBytes += colValue << shiftSize & leftMask;
		leftMask = leftMask >> 3;
		shiftSize = shiftSize - 3;
		*pnode = (*pnode)->next;
		numOfLoops++;
	}
	return resInBytes;
}

void printCellsFromBinaryFile(FILE* file)
{
	int i, j;
	int toPrint;
	unsigned short int numberOfCells;
	unsigned int valuesInBytes;
	fread(&numberOfCells, sizeof(unsigned short int), 1, file);
	fread(&valuesInBytes, sizeof(unsigned int), 1, file);
	for (i = 0; i < numberOfCells / 5; i++)
	{
		unsigned int leftMask = (1 << (31 * (i +  1) - 0)) + (1 << (31 * (i + 1) - 1)) + (1 << (31 * (i + 1) - 2));
		int shiftSize = 29;
		for (j = 0; j < 5; j++)
		{
			toPrint = valuesInBytes & leftMask;
			toPrint = (toPrint >> shiftSize) + 'A';
			printf("%c", (char)toPrint);
			leftMask = leftMask >> 3;
			shiftSize = shiftSize - 3;
			toPrint = valuesInBytes & leftMask;
			toPrint = (toPrint >> shiftSize) + '1';
			printf("%c->", (char)toPrint);
			leftMask = leftMask >> 3;
			shiftSize = shiftSize - 3;
		}
	}
	puts("NULL\n");
}