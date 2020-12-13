#pragma once
#pragma warning(disable:4996)
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <cmath>
#include "enums.h"
#define  TWO_PI 6.28318530718

using namespace std;

BOOL WINAPI ConsoleHandler(DWORD dwCtrlEvent);

void Beep_beep();

void set_color_2(short x);

void ShowCursor(bool Visible);

void gotoxy(short x, short y);

int whereX();

int whereY();

void UnicodeMode();
void Console_OriginalMode();

void clreol();
void SetColor(WORD color);
void SetBGColor(WORD color);

///////////////////////

void my_Console_mode();

void resizeConsole(int width, int height);

void cls();

void FullScreen();

void CleanScreen(HANDLE hConsole);

void setTextSize(int x, int y);

WORD getKey();
