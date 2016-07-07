// Large_Alloc1.cpp : Defines the entry point for the console application.
//

// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;

int main()
{
	HANDLE hChunk;
	HANDLE hDefaultHeap;

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();


	for (int i = 1; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x7ffb0);
		memset(hChunk, 'A', 0x7ffb0);
		printf("[%d] Allocated chunk of 0x7ffb0 bytes at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();

	return 0;

}
