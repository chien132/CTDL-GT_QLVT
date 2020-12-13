#pragma once
#include "Button.h"
#include "Text_field.h"
#include "Select_field.h"

struct Insert
{
	Button* buttons;
	Text_field* text_fields;
	Select_field* select_fields;

	int buttons_size = 0;
	int text_field_size = 0;
	int select_field_size = 0;

	void create(int buttons_count, int text_fields_count,int select_field_count)
	{
		buttons = new Button[buttons_count]; // create buttons  = size
		text_fields = new Text_field[text_fields_count];
		select_fields = new Select_field[select_field_count];
	}

	void add_button(Button new_button)
	{
		buttons[buttons_size] = new_button;
		buttons_size++;
	}

	void add_textfield(Text_field new_text_field)
	{
		text_fields[text_field_size] = new_text_field;
		text_field_size++;
	}

	void add_selectfield(Select_field new_select_field)
	{
		select_fields[select_field_size] = new_select_field;
		select_field_size++;
	}

	void draw()
	{
		for(int i = 0 ; i < buttons_size;i++)
		{
			buttons[i].draw_normal();
		}
		for(int i = 0 ; i < text_field_size;i++)
		{
			text_fields[i].draw_normal();
		}
		for(int i = 0 ; i< select_field_size;i++)
		{
			select_fields[i].draw_normal();
		}

	}

	int update()
	{
		int current_text = 0;
		int current_button = -100;
		int current_select = -100;

		while(true)
		{
			if (current_text != -100) 
			{
				current_text += text_fields[current_text].update();

				if (current_text > text_field_size -  1)
				{
					current_text = -100;
					current_select = 0;
					if(select_field_size == 0)
					{
						current_select = -100;
						current_button = 0;
					}
				}
				else if (current_text < 0)
				{
					current_text = -100;
					current_button = buttons_size - 1;
				}
			}
			if(current_select != -100)
			{
				current_select += select_fields[current_select].update();
				if(current_select > select_field_size - 1)
				{
					current_select = -100;
					current_button = 0;
				}
				else if(current_select < 0)
				{
					current_select = -100;
					current_text = text_field_size -1;
				}
			}
			if(current_button != -100)
			{
				int action = buttons[current_button].update();

				if(action == 0)
				{
					return current_button;
				}

				current_button += action;

				if(current_button > buttons_size-1)
				{
					current_button = -100;
					current_text = 0;
				}
				else if(current_button < 0)
				{
					current_button = -100;
					current_select = select_field_size - 1;
					if(select_field_size == 0)
					{
						current_select = -100;
						current_text = text_field_size - 1;
					}
				}

			}

		}
	}
};
