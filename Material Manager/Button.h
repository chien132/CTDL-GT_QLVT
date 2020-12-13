#pragma once
#include "FreeLibrary.h"
#include "Draw.h"


struct Button
{
	int x, y, w, h;
	string name;

	void create(int x, int y, int w, int h, string name)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->name = name;
	}

	void draw_normal()
	{
		draw_rectangle(x, y, w, h, CYAN);
		gotoxy(x + w / 2 - name.size() / 2, y + h / 2);
		cout << name;
		SetBGColor(BLACK);
	}

	void draw_high_light()
	{
		draw_rectangle(x, y, w, h, RED,WHITE);
		gotoxy(x + w / 2 - name.size() / 2, y + h / 2);
		cout << name;
		SetBGColor(BLACK);
	}

	void draw_selected()
	{
		draw_rectangle(x, y, w, h, YELLOW,BLACK);
		gotoxy(x + w / 2 - name.size() / 2, y + h / 2);
		cout << name;
		Sleep(75);
		draw_rectangle(x, y, w, h, GREEN,WHITE);
		gotoxy(x + w / 2 - name.size() / 2, y + h / 2);
		cout << name;
		Sleep(75);
		draw_high_light();
		SetBGColor(BLACK);
	}

	int update()
	{
		ShowCursor(false);
		draw_high_light();

		while (true)
		{
			if (kbhit())
			{
				char input = getch();

				switch (input)
				{
				case tab:
				{
					draw_normal();
					return 1;
				}
				case arrow_down:
				{
					draw_normal();
					return 1;
				}
				case arrow_up:
				{
					draw_normal();
					return -1;
				}
				case enter:
				{
					draw_selected();
					return 0;
				}
				}

			}
		}
	}
};
