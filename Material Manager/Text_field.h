#pragma once
#include <string>
#include "Draw.h"

struct Text_field
{
	string name;
	string text;
	int max_display;
	int x, y, w, h;

	bool date = false;
	bool only_number = false;
	bool read_only = false;

	void create(int x, int y, int w, int h, string name, int max_display)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->name = name;
		this->max_display = max_display;
		this->text = "";
	}


	void draw_normal()
	{
		draw_rectangle(x, y, w, h, LIGHTGRAY, BLACK);
		gotoxy(x + 2, y);
		cout << name;

		gotoxy(x + 1, y + h / 2);
		cout << text;
	}

	void draw_hl()
	{
		draw_rectangle(x, y, w, h, GREEN, BLACK);
		gotoxy(x + 2, y);
		cout << name;

		gotoxy(x + 1, y + h / 2);
		cout << text;
	}

	void cut_space()
	{
		for (int i = 0; i < text.size();)
		{
			if (text[i] == ' ' && text[i + 1] == ' ')
			{
				text.erase(text.begin() + i + 1);
			}
			else
			{
				i++;
			}
		}
		if (!text.empty() && text[0] == ' ')
		{
			text.erase(text.begin());
		}
		if (!text.empty() && text[text.size() - 1] == ' ')
		{
			text.pop_back();
		}
	}

	bool fix_day()
	{
		if (text.size() == 10)
		{
			string d = string(1, text[0]) + string(1, text[1]);    //
			string m = string(1, text[3]) + string(1, text[4]);
			string y = string(1, text[6]) + string(1, text[7]) + string(1, text[8]) + string(1, text[9]);
			//	d = data[0] + data[1];   // SAI   -  se chuyen thanh so vd A => 65
			int id = atoi(d.c_str());
			int im = atoi(m.c_str());
			int ym = atoi(y.c_str());
			
			if(ym < 1999)
			{
				ym = 1999;
				text[6] = '1';
				text[7] = '9';
				text[8] = '9';
				text[9] = '9';
			}
			
			if(ym > 2019)
			{
				ym = 1999;
				text[6] = '2';
				text[7] = '0';
				text[8] = '1';
				text[9] = '9';
			}

			if (im > 12)
			{
				im = 12;
				text[3] = '1';
				text[4] = '2';
			}
			if (im < 1)
			{
				im = 1;
				text[3] = '0';
				text[4] = '1';
			}
			if(id<1)
			{
				id=1;
				text[0]='0';
				text[1]='1';
			}

			if (id > 31)
			{
				switch (im)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
				{
					text[0] = '3';
					text[1] = '1';
					break;
				}
				case 4:
				case 6:
				case 9:
				case 11:
				{
					text[0] = '3';
					text[1] = '0';
					break;
				}
				case 2:
				{
					text[0] = '2';
					text[1] = '9';
					break;
				}
				}
			}
			return true;
		}
		return false;
	}

	int update()
	{
		ShowCursor(true);
		draw_hl();

		while (true)
		{
			if (kbhit())
			{
				char input = getch();
				if (input == tab)
				{
					cut_space();
					if (date)fix_day();
					draw_normal();
					return 1;
				}

				else if (input == -32)
				{
					input = getch();

					switch (input)
					{
					case arrow_down:
					{
						cut_space();
						if (date)fix_day();
						draw_normal();
						return 1;
					}
					case arrow_up:
					{
						cut_space();
						if (date)fix_day();
						draw_normal();
						return -1;
					}
					}

				}
				else if (input == backspace && !read_only)
				{
					if (text.empty() == false)
					{
						text.pop_back();
						gotoxy(x + 1 + text.size(), y + h / 2);
						cout << "  ";

						gotoxy(x + 1, y + h / 2);
						cout << text;
					}
				}
				else if (input >= 32 && input <= 128)
				{
					if (read_only)
					{

					}

					else if (only_number)
					{
						if (input >= '0' && input <= '9' && text.size() < max_display)
						{
							text += input;
							gotoxy(x + 1, y + h / 2);
							cout << text;
						}
					}


					else if (date)
					{
						if (input >= '0' && input <= '9' && text.size() < 10)
						{
							text += input;
							if (text.size() == 2 || text.size() == 5)
							{
								text += '/';
							}
							gotoxy(x + 1, y + h / 2);
							cout << text;
						}

					}
					else if (text.size() < max_display) {
						text += input;
						gotoxy(x + 1, y + h / 2);
						cout << text;
					}
				}
			}

		}

	}

};
