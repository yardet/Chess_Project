#define _CRT_SECURE_NO_WARNINGS
#include "Files_Bytes.h"
#include <stdlib.h>
#include <string.h>

// Q5
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

//Q6
int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	if (!fp)
	{
		return FAILURE;
	}
	chessPosList listToCheck = getCellsFromBinaryFile(fp);
	if (!isValidPath(listToCheck))
	{
		return 1;
	}
	display(&listToCheck);
	if (isPathCoveringAllBoard(listToCheck))
	{
		return 2;
	}
	return 3;
}

chessPosList getCellsFromBinaryFile(FILE* file)
{
	chessPosList posLst;
	makeEmptyChessPosList(&posLst);
	chessPosCell* currNode;
	chessPos currPosition;
	int i, numOfInsertedCells = 0;
	unsigned int bitwiseFromFile;
	unsigned short int numberOfCells;
	unsigned int mask;
	unsigned int bitwiseRowToInsert, bitwiseColToInsert;

	fread(&numberOfCells, sizeof(unsigned short int), 1, file);
	for (i = 0; i < numberOfCells / 5; i++)
	{
		mask = (1 << ((sizeof(int) * 8) - 1)) + (1 << ((sizeof(int) * 8) - 2)) + (1 << ((sizeof(int) * 8) - 3));
		fread(&bitwiseFromFile, sizeof(int), 1, file);
		for (numOfInsertedCells = 0; numOfInsertedCells < 5; numOfInsertedCells++)
		{
			bitwiseRowToInsert = bitwiseFromFile & mask;
			bitwiseColToInsert = bitwiseFromFile & (mask >> BITWISE_SHIFT);
			currPosition[0] = (bitwiseRowToInsert >> (2 * BITWISE_SHIFT * (5 - numOfInsertedCells) - 1)) + 'A';
			currPosition[1] = (bitwiseColToInsert >> (2 * BITWISE_SHIFT * (4 - numOfInsertedCells) + 2)) + '1';
			currNode = createNewListNode(currPosition, NULL);
			insertChessPosCellToEndList(&posLst, currNode);
			mask = mask >> 2 * BITWISE_SHIFT;
		}
	}
	mask = (1 << ((sizeof(int) * 8) - 1)) + (1 << ((sizeof(int) * 8) - 2)) + (1 << ((sizeof(int) * 8) - 3));
	fread(&bitwiseFromFile, sizeof(int), 1, file);
	for (i = 0; i < numberOfCells % 5; i++)
	{
		bitwiseRowToInsert = bitwiseFromFile & mask;
		bitwiseColToInsert = bitwiseFromFile & (mask >> BITWISE_SHIFT);
		currPosition[0] = (bitwiseRowToInsert >> (2 * BITWISE_SHIFT * (5 - i) - 1)) + 'A';
		currPosition[1] = (bitwiseColToInsert >> (2 * BITWISE_SHIFT * (4 - i) + 2)) + '1';
		currNode = createNewListNode(currPosition, NULL);
		insertChessPosCellToEndList(&posLst, currNode);
		mask = mask >> 2 * BITWISE_SHIFT;
	}
	return posLst;
}