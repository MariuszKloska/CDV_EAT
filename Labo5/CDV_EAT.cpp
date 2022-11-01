#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include "ascii.cpp"
#include "menuF.cpp"
#include "Userlog.cpp"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int menuNavigation = 1, pressedKey, checkstring = 0, hour, randomTable;
string menuPositions[10][10][10];
bool menuCanBeChoose[1000];
int menuSpaceScreen = 20; // Odległość ramki od lewej krawędzi ekranu
int menuWide = 80; // Szerokośc menu minimum tyle co ma znaków najdłuższa pozycja w menu
string logedUser = "niezalogowany", filename;
fstream menuFromFile;
fstream userfile;
fstream order;
fstream dataFile;
string trash, valueHelper, onlyHour, deliveryAdressCity, deliveryAdressStreet, deliveryHouseNumber, CurrentTime, table, resHour;
double basketValue = 0, productValue;

void logo();
void plsLogin();
void emptyBasket()
{
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	logo();
	putSpace(menuSpaceScreen + menuWide / 4);
	cout << "   Najpierw cos dodaj do koszyka !";
	menuNavigation = 1;
	Sleep(2000);
}
void fileToFile() {
	userfile.open(logedUser + "_data.txt", ios::in | ios::out | ios::app);
	dataFile.open(logedUser + ".txt", ios::in | ios::out);
	string line, result;
	bool first = true;
	while (getline(dataFile, line)) {
		if (first) {
			first = false;
			continue;
		}
		result = result + line + "\n";

	}
	cout << result;
	userfile << result;

	userfile.close();
	dataFile.close();
}
void tableRes()
{
	system("cls");

	if (logedUser != "niezalogowany") {
		if (basketValue != 0)
		{
			cout << "\n\n\n\n\n\n\n";
			logo();
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Zaraz dokonamy rezerwacji panstwa stolika !\n";
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Na ktora godzine przygotowac stolik : ";
			cin >> resHour;
			randomTable = (rand() % 20) + 1;

			userfile.open(logedUser + "_data.txt", ios::out);
			userfile << "Uzytkownik : " << logedUser;
			userfile << endl << "Rezerwacja złozona o godz: " << CurrentTime;
			userfile << endl << "Godzina rezerwacji stolika : " << resHour;
			userfile << endl << "Nr Stolika : " << randomTable;
			userfile << endl << "Wartosc zamowienia : " << basketValue << " PLN";
			userfile.close();

			cout << endl;
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Gratulujemy ! Rezerwacja zostala przyjeta\n";
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "    Twoj nr stolika to : " << randomTable << endl;
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Osoba na ktora dokonano rezerwacji : " << logedUser << endl;
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Godzina na ktora zarezerwowano stolik: " << resHour << endl;
			fileToFile();
			menuNavigation = 1;
			Sleep(5000);
		}
		else
			emptyBasket();
	}
	else
		plsLogin();
}


void deliveryEat()
{
	system("cls");

	if (logedUser != "niezalogowany") {
		if (basketValue != 0)
		{
			cout << "\n\n\n\n\n\n\n";
			logo();
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Podaj adres dostawy \n";
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Podaj miasto: ";
			cin >> deliveryAdressCity;
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Podaj nazwe ulicy: ";
			cin >> deliveryAdressStreet;
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Podaj nr domu: ";
			cin >> deliveryHouseNumber;

			//wpisz wszystko do data txt i wypisz na koncu
			userfile.open(logedUser + "_data.txt", ios::out);
			userfile << "Uzytkownik : " << logedUser;
			userfile << endl << "Zamownienie złozone o godz: " << CurrentTime;
			userfile << endl << "Miejscowosc : " << deliveryAdressCity;
			userfile << endl << "Ulica : " << deliveryAdressStreet;
			userfile << endl << "Nr domu : " << deliveryHouseNumber;
			userfile << endl << "Wartosc zamowienia : " << basketValue << " PLN";
			userfile.close();
			fileToFile();
			cout << endl;
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "Gratulujemy ! Zamowienie zostalo przyjete\n";
			putSpace(menuSpaceScreen + menuWide / 4);
			cout << "   Szacunkowy czas dostawy to 45 min";
			userfile.open(logedUser + "_data.txt", ios::out);
			string line;
			while (getline(dataFile, line)) {
				cout << line << endl;
			}
			userfile.close();
			menuNavigation = 1;
			Sleep(10000);
		}
		else
			emptyBasket();
	}
	else
		plsLogin();
}



void plsLogin()
{
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	logo();
	putSpace(menuSpaceScreen + menuWide / 4);
	cout << "Aby wybrac ta opcje nalezy sie zalogowac !";
	menuNavigation = 1;
	Sleep(2000);
}
string showHour()

{
	time_t czas;
	struct tm* data;
	char godzina[80];

	time(&czas);
	data = localtime(&czas);

	strftime(godzina, 80, "%H", data);
	return godzina;
}

string showTime()

{
	time_t czas;
	struct tm* data;
	char godzina[80];

	time(&czas);
	data = localtime(&czas);

	strftime(godzina, 80, "%H:%M", data);
	return godzina;
}


void addToBasket()
{
	userfile.open(logedUser + ".txt", ios::out | ios::app);
	userfile << endl << menuNavigation % 10 << " X " << menuPositions[menuNavigation / 100][(menuNavigation / 10) % 10][0];
	userfile.close();
	trash = menuPositions[menuNavigation / 100][(menuNavigation / 10) % 10][0];
	valueHelper = trash.substr((trash.size() - 9), (trash.size() - 5));
	productValue = atof(valueHelper.c_str());
	basketValue = basketValue + ((menuNavigation % 10) * productValue);
}

void logUser()
{
	system("cls");
	if (logedUser == "niezalogowany")
	{
		cout << "\n\n\n\n\n\n\n";
		logo();
		putSpace(menuSpaceScreen + menuWide / 3);
		cout << "Podaj Login : ";
		cin >> logedUser;
		filename = logedUser + ".txt";
		userfile.open(filename, ios::in);

		if (userfile.good())
		{
			cout << "\n\n";
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Zalogowano jako : " << logedUser << endl << endl;
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Trwa przekierowywanie...";
			Sleep(3000);
			userfile.close();
			userfile.open(filename, ios::out);
			userfile << "Nazwa uzytkownika : " << logedUser;
			userfile.close();
		}
		else
		{
			cout << "\n\n";
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Nie odnaleziono uzytkownika!\n\n";
			logedUser = "niezalogowany";
			Sleep(1200);
		}

	}

	else
	{
		cout << "\n\n\n\n\n\n\n";
		logo();
		putSpace(menuSpaceScreen + 20);
		cout << "Jetes zalogowany, nejpierw sie wyloguj";
		Sleep(1200);
	}
}

void regUser()
{
	if (logedUser == "niezalogowany") {
		system("cls");
		cout << "\n\n\n\n\n\n\n";
		logo();
		putSpace(menuSpaceScreen + menuWide / 4);
		cout << "Zarejestruj sie! Podaj swoj login : ";
		cin >> logedUser;
		filename = logedUser + ".txt";
		userfile.open(filename, ios::in);
		if (userfile.good())
		{
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Podana nazwa jest juz zajeta\n\n";
			logedUser = "niezalogowany";
			Sleep(3000);
		}
		else
		{
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Utworzono nowe konto\n\n";
			Sleep(200);
			putSpace(menuSpaceScreen + menuWide / 3);
			cout << "Trwa przekierowywanie...";
			Sleep(3000);
			userfile.close();
			userfile.open(filename, ios::out);
			userfile << "Nazwa uzytkownika : " << logedUser;
		}
		userfile.close();
	}
	else
	{
		system("cls");
		putSpace(menuSpaceScreen + menuWide / 3);
		cout << "\n\n\n\n\n\n\n";
		logo();
		putSpace(menuSpaceScreen + menuWide / 3);
		cout << "Jestes juz zalogowany\n\n";
		putSpace(menuSpaceScreen + menuWide / 3);
		cout << "Trwa przekierowywanie...";
		Sleep(3000);

	}
}

void logOut() {
	logedUser = "niezalogowany";
	userfile.close();
}

void orderHistory() {
	order.open(logedUser + ".txt", ios::in);
	int i = 0;
	while (!order.eof())
	{
		if (i != 0)
		{
			getline(order, menuPositions[2][2][i]);
			menuCanBeChoose[220 + i] = 1;
		}
		else
		{
			getline(order, trash);
		}
		i++;
	}

	order.close();
	if (i == 1)
	{
		menuPositions[2][2][1] = "Koszyk jest pusty ";
	}
}

void loadMenuNames() //Błędy w wyświetlaniu można rozwiązać dodatkową spacją w nazwie nie chce budować kolejego ifa występują dla nazw o nieparzystej liczbie znaków 
{	// pozycja 1 w menu i pozycja 9 czyli ostatnia muszą być wybieralne  ale nie muszą nic robić 
	// używajćie parzystej liczby znaków !
	menuPositions[1][0][0] = "Logowanie/Rejestracja ";		menuCanBeChoose[100] = 1;
	menuPositions[2][0][0] = "Moj Koszyk";					menuCanBeChoose[200] = 1;
	menuPositions[3][0][0] = "----------------------------";
	menuPositions[4][0][0] = "Menu - sniadania";			menuCanBeChoose[400] = 1;
	menuPositions[5][0][0] = "Menu - dania obiadowe ";		menuCanBeChoose[500] = 1;
	menuPositions[6][0][0] = "Menu - desery ";				menuCanBeChoose[600] = 1;
	menuPositions[7][0][0] = "Menu - napoje ";				menuCanBeChoose[700] = 1;
	menuPositions[8][0][0] = "Zakoncz zamowienie";			menuCanBeChoose[800] = 1;
	menuPositions[9][0][0] = " Wyjscie  ";					menuCanBeChoose[900] = 1;

	menuPositions[1][1][0] = "Logowanie ";										menuCanBeChoose[110] = 1;
	menuPositions[1][2][0] = "Rejestracja ";									menuCanBeChoose[120] = 1;
	menuPositions[1][3][0] = "Wylogowanie ";									menuCanBeChoose[130] = 1;
	menuPositions[1][9][0] = "Wstecz";											menuCanBeChoose[190] = 1;

	menuPositions[2][1][0] = "Historia zamowien ";					menuCanBeChoose[210] = 1;
	menuPositions[2][2][0] = "Moje zamowienie ";					menuCanBeChoose[220] = 1;
	menuPositions[2][3][0] = "Zamow ponownie";						menuCanBeChoose[230] = 1;
	menuPositions[2][9][0] = "Wstecz";								menuCanBeChoose[290] = 1;
	menuPositions[2][2][9] = "Wstecz";								menuCanBeChoose[229] = 1;


	menuFromFile.open("MenuSniadania.txt", ios::in);
	for (int loadllop = 1; !menuFromFile.eof(); loadllop++)
	{
		getline(menuFromFile, menuPositions[4][loadllop][0]);
		menuCanBeChoose[400 + loadllop * 10] = 1;
	}
	menuFromFile.close();
	menuPositions[4][9][0] = "Wstecz";		menuCanBeChoose[490] = 1;

	menuFromFile.open("MenuObiady.txt", ios::in);
	for (int loadllop = 1; !menuFromFile.eof(); loadllop++)
	{
		getline(menuFromFile, menuPositions[5][loadllop][0]);
		menuCanBeChoose[500 + loadllop * 10] = 1;
	}
	menuFromFile.close();
	menuPositions[5][9][0] = "Wstecz";		menuCanBeChoose[590] = 1;

	menuFromFile.open("MenuDesery.txt", ios::in);
	for (int loadllop = 1; !menuFromFile.eof(); loadllop++)
	{
		getline(menuFromFile, menuPositions[6][loadllop][0]);
		menuCanBeChoose[600 + loadllop * 10] = 1;
	}
	menuFromFile.close();
	menuPositions[6][9][0] = "Wstecz";		menuCanBeChoose[690] = 1;

	menuFromFile.open("MenuNapoje.txt", ios::in);
	for (int loadllop = 1; !menuFromFile.eof(); loadllop++)
	{
		getline(menuFromFile, menuPositions[7][loadllop][0]);
		menuCanBeChoose[700 + loadllop * 10] = 1;
	}
	menuFromFile.close();
	menuPositions[7][9][0] = "Wstecz";		menuCanBeChoose[790] = 1;

	menuPositions[8][1][0] = "Zamow z dostawa ";		menuCanBeChoose[810] = 1;
	menuPositions[8][2][0] = "Zarezerwuj stolik ";	menuCanBeChoose[820] = 1;
	menuPositions[8][9][0] = "Wstecz";				menuCanBeChoose[890] = 1;

	menuPositions[9][2][0] = "Czy napewno chcesz wyjsc ?";	menuCanBeChoose[920] = 0;
	menuPositions[9][3][0] = " Tak  ";						menuCanBeChoose[930] = 1;
	menuPositions[9][4][0] = " Nie  ";						menuCanBeChoose[940] = 1;

	int optionaddeter = 410;
	while (optionaddeter < 800)
	{
		while (menuCanBeChoose[optionaddeter] != 0)
		{
			menuPositions[optionaddeter / 100][(optionaddeter / 10) % 10][1] = "Dodaj 1 szt.";				menuCanBeChoose[optionaddeter + 1] = 1;
			menuPositions[optionaddeter / 100][(optionaddeter / 10) % 10][2] = "Dodaj 2 szt.";				menuCanBeChoose[optionaddeter + 2] = 1;
			menuPositions[optionaddeter / 100][(optionaddeter / 10) % 10][3] = "Dodaj 3 szt.";				menuCanBeChoose[optionaddeter + 3] = 1;
			menuPositions[optionaddeter / 100][(optionaddeter / 10) % 10][4] = "Dodaj 4 szt.";				menuCanBeChoose[optionaddeter + 4] = 1;
			menuPositions[optionaddeter / 100][(optionaddeter / 10) % 10][9] = "Wstecz";					menuCanBeChoose[optionaddeter + 9] = 1;
			optionaddeter += 10;
		}
		optionaddeter = (optionaddeter / 100) * 100 + 110;
	}

}
void logo()
{

	putSpace(menuSpaceScreen + (menuWide - 37) / 2);
	cout << "   __|  _ \\ \\ \\   /    __|    \\ __ __|" << endl;
	putSpace(menuSpaceScreen + (menuWide - 37) / 2);
	cout << "  (     |  | \\ \\ /     _|    _ \\   |   " << endl;
	putSpace(menuSpaceScreen + (menuWide - 37) / 2);
	cout << " \\___| ___/   \\_/     ___| _/  _\\ _|   " << endl;
}
void loading()
{
	short timeWait = 5;
	HideCursor();

	for (short percent = 1; percent < 101; percent++) {
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		logo();
		putSpace(menuSpaceScreen + (menuWide / 2) - 16);
		if (percent < 33)
			cout << "Szukanie przypraw         : " << percent << " %\n";
		else if (percent >= 33 && percent < 66)
			cout << "Obieranie warzyw          : " << percent << " %\n";
		else
			cout << "Nakrywanie stolikow       : " << percent << " %\n";

		putSpace(menuSpaceScreen + 16);
		for (short symbolLoop = 0; symbolLoop < percent; symbolLoop += 2)
			cout << char(178);

		Sleep(timeWait);
	}
}
void menuTopBorderDeepZero()
{
	putSpace(menuSpaceScreen);  cout << (char)(201); putHorLine(menuWide); cout << (char)(187); cout << endl;
}
void menuLegend(short extraspace)
{
	putSpace(menuSpaceScreen); if (extraspace == 1) { cout << (char)(200); }
	if (extraspace == 2) { cout << (char)(200) << (char)(186); }
	cout << (char)(204); putHorLine(menuWide); cout << (char)(185) << endl;
	if (extraspace == 2)
	{
		putSpace(menuSpaceScreen + extraspace - 1); cout << (char)(200) << (char)(186) << (char)(24) << (char)(25) << (char)(26) << ":nawigacja  "; putSpace(menuWide - 15); cout << (char)(186) << endl;
	}
	else
	{
		putSpace(menuSpaceScreen + extraspace); cout << (char)(186) << (char)(24) << (char)(25) << (char)(26) << ":nawigacja  "; putSpace(menuWide - 15); cout << (char)(186) << endl;

	}

	putSpace(menuSpaceScreen + extraspace); cout << (char)(186) << "Enter:zatwiedz "; putSpace(menuWide - 15); cout << (char)(186) << endl;
	putSpace(menuSpaceScreen + extraspace); cout << (char)(186) << "Esc:wyjscie    "; putSpace(menuWide - 15); cout << (char)(186) << endl;
	putSpace(menuSpaceScreen + extraspace); cout << (char)(200); putHorLine(menuWide); cout << (char)(188) << endl;

}
void menuLoops()
{
	// deep zero loops 
	if (menuNavigation <= 10)
	{
		if (menuNavigation == 10 && pressedKey == 80)
		{
			menuNavigation = 1;
		}
		if (menuNavigation == 10 && pressedKey == 72) // nie wiem czemu nie działa
		{
			menuNavigation = 11;
		}
		if (menuNavigation == 0)
		{
			menuNavigation = 9;
		}
		while (menuCanBeChoose[menuNavigation * 100] != 1 && pressedKey == 80)
		{
			menuNavigation++;
		}
		while (menuCanBeChoose[menuNavigation * 100] != 1 && pressedKey == 72)
		{
			menuNavigation--;
		}
	}
	// deep one loops
	if (menuNavigation > 10 && menuNavigation < 90)
	{
		;
		if ((menuNavigation % 10) == 0 && pressedKey == 80)
		{
			menuNavigation -= 9;
		}
		if ((menuNavigation % 10) == 0 && pressedKey == 72)
		{
			menuNavigation += 9;
		}

		while (menuCanBeChoose[menuNavigation * 10] != 1 && pressedKey == 80 || menuNavigation % 10 == 0)
		{
			menuNavigation++;
		}
		while (menuCanBeChoose[menuNavigation * 10] != 1 && pressedKey == 72 || menuNavigation % 10 == 0)
		{
			menuNavigation--;
		}

	}
	// deep two loops
	if (menuNavigation > 100)
	{
		;
		if ((menuNavigation % 10) == 0 && pressedKey == 80)
		{
			menuNavigation -= 9;
		}
		if ((menuNavigation % 10) == 0 && pressedKey == 72)
		{
			menuNavigation += 9;
		}

		while (menuCanBeChoose[menuNavigation] != 1 && pressedKey == 80 || menuNavigation % 10 == 0)
		{
			menuNavigation++;
		}
		while (menuCanBeChoose[menuNavigation] != 1 && pressedKey == 72 || menuNavigation % 10 == 0)
		{
			menuNavigation--;
		}

	}
	// osobny loop dla exit menu 
	if (menuNavigation == 95) { menuNavigation = 93; }
	if (menuNavigation == 92) { menuNavigation = 94; }
}
void menuControl()
{
	switch (pressedKey)
	{
	case 80: // strzalka w dol
	{
		menuNavigation++;
		break;
	}
	case 72: // strzalka w gore
	{
		menuNavigation--;
		break;
	}
	}
}
void displayMenuDeepTwo()
{
	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(201); putHorLine(menuWide); cout << (char)(187); cout << endl;
	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(186) << (char)(201); putHorLine(menuWide); cout << (char)(187); cout << endl;

	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(186) << (char)(186); putSpace((menuWide - menuPositions[menuNavigation / 100][0][0].length() - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][0].length() - 18) / 2);
	cout << "Menu glowne > " << menuPositions[menuNavigation / 100][0][0] << " >  " << menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][0];
	putSpace((menuWide - menuPositions[menuNavigation / 100][0][0].length() - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][0].length() - 18) / 2); cout << (char)(186); cout << endl;

	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(186) << (char)(204); putHorLine(menuWide); cout << (char)(185); cout << endl;
	for (short positionsInMenu = 0; positionsInMenu < 9; positionsInMenu++)
	{
		if (menuNavigation == (positionsInMenu + 1) + (menuNavigation / 10) * 10)
		{
			putSpace(menuSpaceScreen); cout << (char)(186) << (char)(186) << (char)(204);
			putHorLine((menuWide - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu].length()) / 2);
			cout << menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu];
			putHorLine((menuWide - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu].length()) / 2);
			cout << (char)(185) << endl;
		}
		else
		{
			putSpace(menuSpaceScreen); cout << (char)(186) << (char)(186) << (char)(186);
			putSpace((menuWide - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu].length()) / 2);
			cout << menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu];
			putSpace((menuWide - menuPositions[menuNavigation / 100][(((menuNavigation / 10) % 10))][(menuNavigation / 10 * 10) % 10 + 1 + positionsInMenu].length()) / 2);
			cout << (char)(186) << endl;
		}
	}
}
void displayMenuDeepOne()
{
	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(201); putHorLine(menuWide); cout << (char)(187); cout << endl;
	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(186); putSpace((menuWide - menuPositions[menuNavigation / 10][0][0].length() - 14) / 2); cout << "Menu glowne > " << menuPositions[menuNavigation / 10][0][0]; putSpace((menuWide - menuPositions[menuNavigation / 10][0][0].length() - 14) / 2); cout << (char)(186); cout << endl;
	putSpace(menuSpaceScreen);  cout << (char)(186) << (char)(204); putHorLine(menuWide); cout << (char)(185); cout << endl;
	for (short positionsInMenu = 0; positionsInMenu < 9; positionsInMenu++)
	{
		if (menuNavigation == (positionsInMenu + 1) + (menuNavigation / 10) * 10)
		{
			putSpace(menuSpaceScreen); cout << (char)(186) << (char)(204);
			putHorLine((menuWide - menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0].length()) / 2);
			cout << menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0];
			putHorLine((menuWide - menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0].length()) / 2);
			cout << (char)(185) << endl;
		}
		else
		{
			putSpace(menuSpaceScreen); cout << (char)(186) << (char)(186);
			putSpace((menuWide - menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0].length()) / 2);
			cout << menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0];
			putSpace((menuWide - menuPositions[menuNavigation / 10][((((menuNavigation / 10) * 10) + 1) % 10) + positionsInMenu][0].length()) / 2);
			cout << (char)(186) << endl;
		}
	}
}
void displayMenuDeepZero()
{
	for (short positionsInMenu = 1; positionsInMenu < 10; positionsInMenu++)
	{
		if (menuNavigation == positionsInMenu)
		{
			putSpace(menuSpaceScreen); cout << (char)(204);
			putHorLine((menuWide - menuPositions[positionsInMenu][0][0].length()) / 2);
			cout << menuPositions[positionsInMenu][0][0];
			putHorLine((menuWide - menuPositions[positionsInMenu][0][0].length()) / 2);
			cout << (char)(185) << endl;
		}
		else
		{
			putSpace(menuSpaceScreen); cout << (char)(186);
			putSpace((menuWide - menuPositions[positionsInMenu][0][0].length()) / 2);
			cout << menuPositions[positionsInMenu][0][0];
			putSpace((menuWide - menuPositions[positionsInMenu][0][0].length()) / 2);
			cout << (char)(186) << endl;
		}
	}
}

int main()
{
	loading();
	do
	{

		HideCursor();
		system("cls");
		loadMenuNames();
		orderHistory();
		cout << "Ostatnio wcisniety klawisz : " << pressedKey << endl;
		cout << "Pozycja w menu : " << menuNavigation << endl << endl;
		logo();
		menuTopBorderDeepZero();

		if (menuNavigation < 10)
		{
			displayMenuDeepZero();
			menuLegend(0);
		}
		else if (menuNavigation > 10 && menuNavigation < 100)
		{
			displayMenuDeepOne();
			menuLegend(1);
		}
		else
		{
			displayMenuDeepTwo();
			menuLegend(2);
		}
		CurrentTime = showTime();
		putSpace(menuSpaceScreen);
		cout << "Godzina:" << CurrentTime;
		onlyHour = showHour();
		hour = atoi(onlyHour.c_str());
		if (hour > 22 || hour < 10)
		{
			putSpace(menuSpaceScreen + 10);
			cout << "Restauracja jest teraz nieczynna\n";
		}
		else
		{
			putSpace(menuSpaceScreen + 10);
			cout << "Restauracja jest teraz otwarta\n";
		}
		putSpace(menuSpaceScreen);
		cout << "Wartosc koszyka : " << basketValue << " PLN";
		putSpace(menuSpaceScreen);
		cout << "Zalogowany jako : " << logedUser;

		pressedKey = _getch();
		menuControl();
		menuLoops();

		//odwołania do podmenu i funkcji nalepiej z plików 
		if (pressedKey == 77 || pressedKey == 13)
		{

			switch (menuNavigation)
			{
			case 8:  menuNavigation = (menuNavigation * 10) + 1; pressedKey = 0; break;
			case 9:  menuNavigation = menuNavigation * 10 + 3; pressedKey = 0; break;
			case 22:  menuNavigation = (menuNavigation * 10) + 1; pressedKey = 0; break;
			case 11: logUser(); pressedKey = 0; menuNavigation = 1; break;
			case 12: regUser(); pressedKey = 0; menuNavigation = 1; break;
			case 13: logOut(); pressedKey = 0;  menuNavigation = 1; break;
			case 81: deliveryEat(); break;
			case 82: tableRes(); break;
			case 93: pressedKey = 27; break;
			case 94: menuNavigation /= 10; pressedKey = 0; break;
			default:
				if (menuNavigation % 10 == 9)
				{
					menuNavigation /= 10; pressedKey = 0;
				}

				else if (menuNavigation > 400 && menuNavigation < 800)
				{
					if (logedUser == "niezalogowany")
					{
						plsLogin();
					}
					else
					{
						addToBasket(); break;
					}
				}

				else if (menuNavigation > 40 && menuNavigation < 79)
				{
					pressedKey = 0;  menuNavigation = (menuNavigation * 10) + 1;
				}

				else if (menuNavigation > 13 && menuNavigation < 19)
				{
					pressedKey = 0;  menuNavigation = (menuNavigation * 10) + 1;
				}
				else if (menuNavigation > 0 && menuNavigation < 8)
				{
					pressedKey = 0; menuNavigation = (menuNavigation * 10) + 1;
				}
			}

		}
		else if (pressedKey == 75)
		{
			menuNavigation /= 10;
		}

	} while (pressedKey != 27); //Esc zeby wyjsc

}