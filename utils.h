#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <Windows.h>
#include <iostream>

inline void hidecursor(){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


inline void setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

inline int map(int x, int fromHigh, int toHigh) {
	int res;
	res = (x*toHigh) / fromHigh;
	return res;
}

#endif