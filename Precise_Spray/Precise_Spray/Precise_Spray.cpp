// Precise_Spray.cpp : Defines the entry point for the console application.
//

// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;


void print_content(int memaddress)
{
	int* pcontent = (int*)memaddress;
	int content = *pcontent;
	printf(">> Contents at 0x%08x: %08x\n", memaddress, content);
}


int main()
{
	HANDLE hChunk;
	HANDLE hDefaultHeap;
	std::string junkstr;
	std::string smallstr;
	std::string largestr;
	std::string markerstr = "$$$$";

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();

	junkstr = "";
	smallstr = "";
	largestr = "";

	while (junkstr.size() < 0xbc4)
	{
		junkstr += "\x20";
	}
	smallstr += junkstr;
	smallstr += markerstr;
	
	while (smallstr.size() < 0x1000)
	{
		smallstr += "\x20";
	}

	while (largestr.size() < 0x40000)
	{
		largestr += smallstr;
	}


	for (int i = 1; i <= 0x500; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x40000 - 8);
		memcpy(hChunk, largestr.c_str(), 0x40000 - 8);
		//printf("[%d] Allocated chunk at 0x%p\n", i, hChunk);
	}

	printf("Spray done, check 0x0c0c0c0c\n");

	print_content(0x0c0c0c0c);

	cin.ignore();

	return 0;

}