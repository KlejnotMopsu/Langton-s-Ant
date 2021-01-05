// LangonesAnt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "board.h"
#include "values.h"
#include <Windows.h>
#include "utils.h"
#include <conio.h>
#include <chrono>

void test() {
	char a = _getch();
	char b = _getch();
	std::cout << "a: " << int(a) << "  b: " << int(b);
	exit(0);
}

void play(Board *g) {
	int delay = 500;
	bool paused = false;
	int delayInterval = 50;

	auto start = std::chrono::high_resolution_clock::now();
	while (1) {
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		
		if (!paused && (duration.count() % delay == 0)) {
			g->loop();
			Sleep(1);
		}

		
		setCursorPosition(0, g->getHeigth());
		std::cout << "LOOPS: " << g->getLoops();
		if (paused) std::cout << " P";
		else std::cout << "  ";

		if ((duration.count() % 50) == 0) {
			if (GetKeyState('E') & 0x8000) {
				delay -= delayInterval;
				if (delay < 50)
					delay = 50;
			}

			if (GetKeyState('Q') & 0x8000) {
				delay += delayInterval;
				if (delay > 1000)
					delay = 1000;
			}

			setCursorPosition(0, g->getHeigth() + 2); 
			std::cout << "DELAY: ";
			setCursorPosition(9, g->getHeigth() + 2);
			for (int i = 20; i >= 1; i--) {
				if (i == map(delay, 1000, 20))
					std::cout << 'O';
				else						
					std::cout << '-';
			}
			setCursorPosition(9, g->getHeigth() + 2 + 1);
			std::cout << "1s";
			setCursorPosition(9 + 18, g->getHeigth() + 2 + 1);
			std::cout << "50ms";
		}

		if (GetKeyState('P') & 0x8000) {
			paused ? paused = false : paused = true;
			Sleep(200);
		}

		if (GetKeyState(87) & 0x8000) {
			g->loop();
			Sleep(10);
		}

		if (GetKeyState(27) & 0x8000) {
			system("cls");
			Sleep(50);
			return;
		}

		if ((GetKeyState(32) & 0x8000)  &&  paused) {
			g->loop();
			Sleep(250);
		}
	}
}


int main(){
	//test();
	hidecursor();
	//setCursorPosition(0,0);
	Board *g = nullptr;
	
	int width = 20, heigth = 20;
	bool isOn = false;


	while (1) {
		int menuIndex = 1,
			startIndex = -1,
			continueIndex = -1,
			optionsIndex = -1,
			tutorialIndex = -1;
		
		if (isOn) {
			std::cout << menuIndex << ". Continue.\n"; continueIndex = (menuIndex++) + 48;
		}
		std::cout << menuIndex << ". Start new.\n"; startIndex = (menuIndex++)+48;
		std::cout << menuIndex << ". Options.\n"; optionsIndex = (menuIndex++)+48;
		std::cout << menuIndex << ". Tutorial.\n"; tutorialIndex = (menuIndex++)+48;
		std::cout << '0' << ". Exit.\n";

		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char choice = _getch();
		//std::cout << "Choice: " << int(choice) << " startIndex: " << int(startIndex) << '\n';

		if (choice == startIndex) {
			system("cls");
			if (g != nullptr)
				delete g;
			g = new Board(width, heigth);
			g->draw();
			isOn = true;
			play(g);
		}
		else if (choice == continueIndex) {
			system("cls");
			g->draw();
			play(g);
		}
		else if (choice == tutorialIndex) {
			system("cls");
			std::cout << "Controls:\n"
				"esc - bring menu\n"
				"e - speed up\n"
				"q - slow down\n"
				"p - pause / unpause\n"
				"w - fast forward\n"
				"space - loop once (only when board is paused)\n"
						;
			std::cout << "\nPress any button...";
			_getch();
			system("cls");
		}
		else if (choice == optionsIndex) {
			system("cls");
			bool exitFlag = false;

			while (1) {
				std::cout << ""
					"1. Change board size. (current - " << width << "x" << heigth << ")\n"
					"2. Hide cursor.\n"
					"0. Exit.\n"
					;
				char optChoice = _getch();

				switch (optChoice) {
				case '1':
					system("cls");
					std::cout << "Width - ";
					std::cin >> width;

					std::cout << "Height - ";
					std::cin >> heigth;
					system("cls");
					break;

				case '2':
					system("cls");
					hidecursor();
					system("cls");
					break;

				case '0':
					exitFlag = true;
					break;

				default:
					std::cout << "Unrecognised choice.";
					break;
				}

				if (exitFlag)
					break;
			}

			system("cls");
		}
		else if (choice == '0'){
			exit(0);
		}
		else{
			system("cls");
			setCursorPosition(0, menuIndex+1);
			std::cout << "Unrecognised choice.";
			setCursorPosition(0, 0);
		}

	}

	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
