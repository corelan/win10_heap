// Large_Alloc2.cpp : Defines the entry point for the console application.
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


	for (int i = 1; i <= 0x500 ; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x40000-8);
		memset(hChunk, 'A', 0x40000-8);
		printf("[%d] Allocated chunk at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();

	return 0;

}