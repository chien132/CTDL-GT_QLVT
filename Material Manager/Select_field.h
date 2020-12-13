#pragma once
#include "Draw.h"

struct Select_field
{
	int x, y, w, h;
	int select = 0;
	string* options;
	string name;
	int size = 0;

	void create(int x,int y,int w,int h,int options_count,string name)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->name = name;
		options = new string[options_count];
	}

	void draw_normal()
	{
		draw_rectangle(x, y, w, h, LIGHTGRAY, BLACK);
		gotoxy(x + 2, y );
		cout << name;

		gotoxy(x + 3 , y + h / 2);
		cout << "<<";
		gotoxy(x + w - 5, y + h / 2);
		cout << ">>";

		gotoxy(x + w / 2 - options[select].size() / 2, y + h / 2);
		cout << options[select];
	}

	void draw_hl()
	{
		draw_rectangle(x, y, w, h, GREEN, BLACK);
		gotoxy(x + 2, y );
		cout << name;

		gotoxy(x + 3, y + h / 2);
		cout << "<<";
		gotoxy(x + w - 5, y + h / 2);
		cout << ">>";

		SetColor(LIGHTGRAY);
		gotoxy(x + w / 2 - options[select].size() / 2, y + h / 2);
		cout << options[select];
	}

	void add_option(string option)
	{
		options[size] = option;
		size++;
	}

	int update()
	{
		ShowCursor(false);
		draw_hl();
		while(true)
		{
			if(kbhit())
			{
				char input = getch();

				switch (input)
				{
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
				case arrow_left:
					{
						select--;
						if(select < 0)
						{
							select = size - 1;
						}
						draw_hl();
					break;
					}
				case arrow_right:
					{
						select++;
						if (select > size - 1)
						{
							select = 0;
						}
						draw_hl();
					break;
					}
				}

			}
		}
	}

};
