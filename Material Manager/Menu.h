#pragma once
#include "Button.h"

struct Menu
{
	int size = 0;
	int select = 0;
	Button *button;

	void create(int buttons_count)
	{
		button = new Button[buttons_count];
	}

	void add_button(int x,int y,int w,int h,string name)
	{
		Button new_button;
		new_button.create(x, y, w, h, name);
		button[size] = new_button;
		size++;
	}

	void draw()
	{
		for(int i = 0 ; i < size;i++)
		{
			button[i].draw_normal();
		}
	}

	int update()
	{
		ShowCursor(false);
		while (true) {
			int action = button[select].update();

			if(action == 0)
			{
				return select;
			}

			select += action;

			if (select > size - 1)
			{
				select = 0;
			}
			else if (select < 0)
			{
				select = size - 1;
			}
		}
	}

};
