#pragma once
#include "Employee_list.h"
#include "Insert.h"



Insert create_insert_employee()
{
	Insert insert;
	insert.create(2, 3, 1);

	Text_field id_field;
	id_field.create(60, 5, 50, 3, " ID ", 15);
	Text_field fname_field;
	fname_field.create(60, 9, 50, 3, " FIRST NAME ", 30);
	Text_field lname_field;
	lname_field.create(60, 13, 50, 3, " LAST NAME ", 30);

	Select_field sex_field;
	sex_field.create(60, 17, 50, 3, 2, " SEX ");
	sex_field.add_option("MALE");
	sex_field.add_option("FEMALE");

	Button add_button;
	add_button.create(60 + 50 / 2 - 10, 21, 20, 3, "ADD");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 25, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_textfield(fname_field);
	insert.add_textfield(lname_field);

	insert.add_selectfield(sex_field);
	insert.add_button(add_button);
	insert.add_button(back_button);

	return insert;
}

Insert create_find_employee(int x, int y)
{

	Insert insert;
	insert.create(2, 1, 0);

	Text_field id_field;
	id_field.create(x - 2, y + 2, 23, 3, " EMPLOYEE ID ", 15);
	Button find_button;
	find_button.create(x + 3, y + 8, 14, 3, "OK");
	Button back_button;
	back_button.create(x + 3, y + 12, 14, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_button(find_button);
	insert.add_button(back_button);

	return insert;
}

Employee* find_employee(int x, int y, Employee_List& employee_list)
{
	Insert insert = create_find_employee(x, y);
	Employee* current_employee = nullptr;
	while (true)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0:
		{
			string id = insert.text_fields[0].text;
			current_employee = employee_list.find(id);
			if (current_employee != nullptr)
			{
				cls();
				return current_employee;
			}
			else
			{
				gotoxy(70, 3);
				cout << " Khong tim thay nhan vien !    ";
			}
			break;
		}
		case 1:
		{
			cls();
			return nullptr;
			break;
		}
		}
	}
}

Insert insert_edit_employee()
{
	Insert insert;
	insert.create(3, 3, 1);

	Text_field fname_field;
	fname_field.create(60, 5, 50, 3, " FIRST NAME ", 30);
	Text_field lname_field;
	lname_field.create(60, 9, 50, 3, " LAST NAME ", 30);

	Select_field sex_field;
	sex_field.create(60, 13, 50, 3, 2, " SEX ");
	sex_field.add_option("MALE");
	sex_field.add_option("FEMALE");

	Button save_button;
	save_button.create(60 + 50 / 2 - 10, 17, 20, 3, "SAVE");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 21, 20, 3, "BACK");
	Button del_button;
	del_button.create(60 + 50 / 2 - 10, 29, 20, 3, "DELETE");

	insert.add_textfield(fname_field);
	insert.add_textfield(lname_field);
	insert.add_selectfield(sex_field);
	insert.add_button(save_button);
	insert.add_button(back_button);
	insert.add_button(del_button);

	return insert;
}

void edit_delete_employee(Employee_List& emp_list)
{
	Employee* temp = find_employee(73, 5, emp_list);
	if (temp == nullptr)
	{
		return;
	}

	Insert insert = insert_edit_employee();
	insert.text_fields[0].text = temp->FName;
	insert.text_fields[1].text = temp->LName;
	for (int i = 0; i < insert.select_fields[0].size; i++)
	{
		if (insert.select_fields[0].options[i] == temp->Sex)
		{
			insert.select_fields[0].select = i;
		}
	}
	while (true)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0: //save
		{
			bool error = false;
			//kiem tra loi xong moi push vao
			for (int i = 0; i < insert.text_field_size; i++)
			{
				if (insert.text_fields[i].text.size() < 1)
				{
					error = true;
				}
			}
			if (!error)
			{
				temp->FName = insert.text_fields[0].text;
				temp->LName = insert.text_fields[1].text;
				temp->Sex = insert.select_fields[0].options[insert.select_fields[0].select];
				gotoxy(60, 2);
				cout << "         Da cap nhat thong tin nhan vien !         ";
				Sleep(1000);
				cls();
			}
			else
			{
				gotoxy(60, 2);
				cout << "         Khong duoc de trong thong tin !!             ";
				break;
			}

			return;
		}
		case 1: //back
		{
			cls();
			return;
		}
		case 2: //delete
		{

			if (temp->bill_linkedlist_ptr!=nullptr && temp->bill_linkedlist_ptr->size > 0)
			{
				gotoxy(60, 2);
				cout << "    Khong the xoa nhan vien da lap hoa don !                     ";
				break;
			}




			emp_list.delete_id(temp->ID);
			gotoxy(60, 2);
			cout << "                Da xoa nhan vien !                     ";
			Sleep(1000);
			cls();
			return;
		}
		}
	}

}

void add_employee(Employee_List& employee_list)
{

	Insert insert = create_insert_employee();
	while (1)
	{

		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0: //add
		{
			bool error = false;
			//kiem tra loi xong moi push vao
			for (int i = 0; i < insert.text_field_size; i++)
			{
				if (insert.text_fields[i].text.size() < 1)
				{
					error = true;
				}
			}
			Employee* temp = employee_list.find(insert.text_fields[0].text);
			if (temp != nullptr && insert.text_fields[0].text == temp->ID)
			{
				error = true;
			}
			if (!error)
			{
				Employee new_employee;
				new_employee.ID = insert.text_fields[0].text;
				new_employee.FName = insert.text_fields[1].text;
				new_employee.LName = insert.text_fields[2].text;

				int select_sex = insert.select_fields[0].select;
				new_employee.Sex = insert.select_fields[0].options[select_sex];


				if (employee_list.push_back(new_employee))
				{
					gotoxy(60, 2);
					cout << "                Da them nhan vien !                    ";
					Sleep(1000);
					cls();
					return;
				}
				else
				{
					cls();
					gotoxy(60, 10);
					cout << "            Danh sach nhan vien da day           ";
					Sleep(1000);
					return;
				}

				//sau khi nhap xong cho no empty
				insert.text_fields[0].text = "";
				insert.text_fields[1].text = "";
				insert.text_fields[2].text = "";
			}
			else
			{
				gotoxy(60, 2);
				cout << "   Ma nhan vien bi trung hoac thieu thong tin !!";
				//	Sleep(1000);
				//	cls();
			}



			break;
		}
		case 1: //back
		{
			cls();
			return;
		}
		}
	}
}

void sort_employee_list(Employee_List& emplist)
{
	for (int i = 0; i < emplist.size; i++)
	{
		for (int j = i; j < emplist.size; j++)
		{
			if (emplist.array[j]->FName < emplist.array[i]->FName)
			{
				swap(emplist.array[j], emplist.array[i]);
			}
			else if (emplist.array[i]->FName == emplist.array[j]->FName)
			{
				if (emplist.array[j]->LName < emplist.array[i]->LName)
				{
					swap(emplist.array[j], emplist.array[i]);
				}
			}
		}
	}

}

void draw_employees(int start, int end, int max, Employee_List& employee_list)
{
	sort_employee_list(employee_list);

	int col = 5;
	int x = 25;
	int y = 4;
	int w = 120;
	draw_table(x, y - 1, w, max + 1, col);

	x = 23;
	int page_number = employee_list.size / max + 1;
	if (employee_list.size % max == 0) page_number--;
	gotoxy(70, (y + max + 2) * 2);
	cout << " <<<< Dang xem trang " << start / max + 1 << '/' << page_number << " >>>> ";
	gotoxy(25, (y + max + 4) * 2);
	cout << "Tong so nhan vien: " << employee_list.size;
	gotoxy(25, (y + max + 5) * 2);
	cout << "Bam ESC the thoat ra menu";

	SetColor(CYAN);
	gotoxy(x + w / col * 0.5, y);
	cout << "STT";
	gotoxy(x + w / col * 1.5, y);
	cout << "ID";
	gotoxy(x + w / col * 2.5, y);
	cout << "FIRST NAME";
	gotoxy(x + w / col * 3.5, y);
	cout << "LAST NAME";
	gotoxy(x + w / col * 4.5, y);
	cout << "SEX";

	y += 3;
	for (int i = start; i < end; i++)
	{
		gotoxy(x + w / col * 0.5, y + (i - start) * 2 - 1);
		cout << i + 1;
		gotoxy(x + w / col * 1.5, y + (i - start) * 2 - 1);
		cout << employee_list.array[i]->ID;
		gotoxy(x + w / col * 2.5, y + (i - start) * 2 - 1);
		cout << employee_list.array[i]->FName;
		gotoxy(x + w / col * 3.5, y + (i - start) * 2 - 1);
		cout << employee_list.array[i]->LName;
		gotoxy(x + w / col * 4.5, y + (i - start) * 2 - 1);
		cout << employee_list.array[i]->Sex;
	}
	//cin.get();
}

void watch_employee_list(Employee_List& list)
{
	int start = 0;
	int max = 10;
	int end;


	if (list.size < max)
	{
		end = list.size;
	}
	else
	{
		end = max;
	}

	draw_employees(start, end, max, list);
	while (true)
	{
		if (kbhit())
		{
			char input = getch();
			switch (input)
			{
			case arrow_right:
			{
				start += max;
				end += max;
				if (start >= list.size)
				{
					start -= max;
				}
				if (end > list.size)
				{
					end = list.size;
				}
				//cls();
				draw_employees(start, end, max, list);
				break;
			}
			case arrow_left:
			{
				start -= max;
				end -= max;
				if (start <= 0)
				{
					start = 0;
					if (list.size < max)
					{
						end = list.size;
					}
					else
					{
						end = start + max;
					}
				}
				else
				{
					end = start + max;
				}
				//cls();
				draw_employees(start, end, max, list);
				break;
			}
			case enter:
			case esc: {
				return;
			}

			}
		}
	}
}

void employee_modifies(Employee_List& list)
{
	Menu emp_menu;
	emp_menu.create(3);
	emp_menu.add_button(60, 5, 50, 3, "Add New Employee");
	emp_menu.add_button(60, 9, 50, 3, "Edit A Employee");
	emp_menu.add_button(60, 17, 50, 3, "Back To Main Menu");

	while (true)
	{
		emp_menu.draw();
		int action = emp_menu.update();
		switch (action)
		{
		case 0:
		{
			cls();
			add_employee(list);
			break;
		}
		case 1:
		{
			cls();
			edit_delete_employee(list);
			break;
		}
		case 2:
		{
			return;
		}
		}
	}
}
