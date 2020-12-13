#pragma once
#include<iostream>
#include"FreeLibrary.h"

void welcome()
{
	cout<<"                                                                           ,*                                                                                      \n"
"                                                                                        &@@,@.                                                                                     \n"
"                                                                                      @@@   @                                                                                      \n"
"                                                                                    (@@   .@                                                                                       \n"
"                                         ,.                                        @@%   #@                                                                                        \n"
"                                   @@&    @@@#                                   .@@,   @(                                                                                         \n"
"                               .@@       @&@@.               @        @@@&       @@.  (@                                                                                           \n"
"                            *@*         .@@@&               @ (    @@@    @     @@,  @.     @@@@%                                          @@%@@                                   \n"
"                        .@@.            @@@@                @&    @@&    @/    @@@ *@     @@@@       @@@@%(     @@@@%   @@#              ,@&  @/                                   \n"
"                  .%@@@.                @@@@     @@%        @,   .@@   (@      @@ @      @@@.      @@@@    @@@%  ,@@( @@ @@%  @@@@       @@ (@            ,@@%.                    \n"
"                                        @@@#    .@&@#      & @@, @@ .@@        @@.      @@@       #@@&     .     @@@*@  #@@#@@ #@@@     @@%@          @@                           \n"
"                                         @@.    @@@@(     @     #@@*          ,@@      ,@@        @@@     (     @@@@@   @@@@@  &@@@     @@         @%                              \n"
"                                         ,@%  @@,@@@#    @       %@,        /&  @@     ,@@     .@ @@/   .,     @@@@&   /@@@@   @@@   .@ .@@    #@&                                 \n"
"                                           %@@.  #@@@  @          @@&    (@.     .@@@@@  &@@@@*   @@@  @      @@@@.    @@@%    @@@(@&     @@@@*                           ";
}

void draw_table(int x, int y, int w, int height, int column)
{
	int h = height * 2 + 1;
	SetColor(LIGHTGRAY);
	for (int i = 0; i < h; i++)
	{
		gotoxy(x, y + i);
		if (i == 0)    // Top
		{
			cout << char(UpLeftCorner) << string(w - 2, char(Horizontal)) << char(UpRightCorner);
		}
		else if (i == h - 1)  //Bottom
		{
			cout << char(DownLeftCorner) << string(w - 2, char(Horizontal)) << char(DownRightCorner);
		}
		else if (i % 2 == 0 && i != 1)    // line
		{
			cout << char(Vertical) << string(w - 2, '-') << char(Vertical);
			//	cout << char(Vertical) << string(w - 2, char(Horizontal)) << char(Vertical);
		}
		else   // slot
		{
			cout << char(Vertical) << string(w - 2, ' ') << char(Vertical);
		}
	}
	int a = x;
	for (int i = 1; i < column; i++)
	{
		a += w / column;
		for (int j = y + 1; j < h+y-1; j++)
		{
			gotoxy(a, j);
			cout << '|';
			//	cout << char(186);
		}
	}
	//SetColor(RED);
}

void  draw_rectangle(int x, int y, int width, int height, int color, int background = BLACK)
{
	SetColor(color);
	SetBGColor(background);
	for (int i = 0; i < height; i++)
	{
		gotoxy(x, y + i);
		if (i == 0)
		{
			cout << char(UpLeftCorner) << string(width - 2, char(Horizontal)) << char(UpRightCorner);
		}
		else if (i == height - 1)
		{
			cout << char(DownLeftCorner) << string(width - 2, char(Horizontal)) << char(DownRightCorner);
		}
		else
		{
			cout << char(Vertical) << string(width - 2, ' ') << char(Vertical);
		}
	}
	//	SetColor(WHITE);
}

void draw_beautiful_table(int x, int y, int w, int h, int* xx,int xx_size)
{
	draw_rectangle(x, y, w, h*2+1, WHITE);
	for(int i=1;i<h*2;i++)
	{
		if(i%2==0)
		{
			gotoxy(x + 1, y + i);
			cout << string(w - 2, '-');
		}
		for(int j=0;j<xx_size;j++)
		{
			gotoxy(xx[j], y + i);
			cout << char(Vertical);
		}
	}
}

void draw_circle(int x, int y, int radius_x, int radius_y)
{
	for (float a = 0; a < TWO_PI; a += 0.01)
	{
		float nx = radius_x * cos(a);
		float ny = radius_y * sin(a);
		gotoxy(x + nx, y + ny);
		cout << '.';
	}
}
void nani(int x, int y, int radius)
{
	draw_circle(x, y, radius * 2, radius);
}
