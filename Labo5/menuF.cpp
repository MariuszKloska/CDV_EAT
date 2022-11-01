#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#ifndef menuF_hpp
#define menuF_hpp

using namespace std;

inline void HideCursor() // hide i show coursor gotowa funcja z neta nie do wymyœlenia na moim etapie mog³em tylko przepisaæ
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

inline void ShowCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	if (hCCI.bVisible != TRUE)
	{
		hCCI.bVisible = TRUE;
		::SetConsoleCursorInfo(hConsoleOut, &hCCI);
	}
}

inline void putSpace(short spacenumber)
{
	for (short horizontalLine = 0; horizontalLine < spacenumber; horizontalLine++) cout << " ";
}

inline void putHorLine(short lengthOfLines)
{
	for (short horizontalLine = 0; horizontalLine < lengthOfLines; horizontalLine++) cout << (char)(205);
}


#endif