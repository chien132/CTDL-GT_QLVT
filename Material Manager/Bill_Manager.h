#pragma once
#include "Bill_linked_list.h"
#include "Insert.h"
#include "Material_Manager.h"
#include "Best_Selling.h"

long long int total_value(Bill_Node* node)
{
	long long int value = 0;

	for (int i = 0; i < node->bill.billbetail_list_ptr->size; i++)
	{
		int b = (node->bill.billbetail_list_ptr->array[i].Soluong * node->bill.billbetail_list_ptr->array[i].Dongia) * (1.0 + node->bill.billbetail_list_ptr->array[i].VAT / 100.0);
		value += b;
	}
	return value;
}

long long int total_value_details(Billdetails_list db_list)
{
	long long int value = 0;

	for (int i = 0; i < db_list.size; i++)
	{
		int b = (db_list.array[i].Soluong * db_list.array[i].Dongia) * (1.0 + db_list.array[i].VAT / 100.0);
		value += b;
	}
	return value;
}

Insert create_find_bill()
{
	Insert insert;
	insert.create(2, 1, 0);

	Text_field id_field;
	id_field.create(60, 5, 50, 3, " BILL ID ", 20);

	Button find_button;
	find_button.create(60 + 50 / 2 - 10, 9, 20, 3, "FIND");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 13, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_button(find_button);
	insert.add_button(back_button);

	return insert;
}

Bill* find_bill(Bill_linked_list& bill_list)
{
	Insert insert = create_find_bill();
	Bill* current_bill = nullptr;
	while (true)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0:
		{
			string id = insert.text_fields[0].text;
			current_bill = bill_list.find(id);
			if (current_bill != nullptr)
			{
				cls();
				return current_bill;
			}
			else
			{
				gotoxy(5, 1);
				cout << "Bill Not Found!";
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

void draw_bill_detail_list(Material_Tree& tree, Billdetails_list* db_list, int x, int y, int w, int h, int* xx)
{

	draw_beautiful_table(x, y, w, h, xx, 7);
	SetColor(CYAN);
	gotoxy(x + 1, y + 1); 	cout << "STT";
	gotoxy(xx[0] + 5, y + 1);	cout << "Ten Vat Tu";
	gotoxy(xx[1] + 2, y + 1);	cout << "Ma VT";
	gotoxy(xx[2] + 2, y + 1);	cout << "Don Vi Tinh";
	gotoxy(xx[3] + 2, y + 1);	cout << "So Luong";
	gotoxy(xx[4] + 2, y + 1);	cout << "Don Gia";
	gotoxy(xx[5] + 2, y + 1);	cout << "%VAT";
	gotoxy(xx[6] + 2, y + 1);	cout << "Thanh Tien";
	SetColor(WHITE);

	if (db_list != nullptr)
	{
		for (int i = 0; i < db_list->size; i++)
		{
			Bill_details current_detail = db_list->array[i];
			Material temp = tree.search(current_detail.MAVT)->material;

			gotoxy(x + 1, y + (i + 1) * 2 + 1); 	cout << i + 1;
			gotoxy(xx[0] + 5, y + (i + 1) * 2 + 1);	cout << temp.Name;
			gotoxy(xx[1] + 2, y + (i + 1) * 2 + 1);	cout << current_detail.MAVT;
			gotoxy(xx[2] + 2, y + (i + 1) * 2 + 1);	cout << temp.Cal_Unit;
			gotoxy(xx[3] + 2, y + (i + 1) * 2 + 1);	cout << current_detail.Soluong;
			gotoxy(xx[4] + 2, y + (i + 1) * 2 + 1);	cout << current_detail.Dongia;
			gotoxy(xx[5] + 2, y + (i + 1) * 2 + 1);	cout << current_detail.VAT;
			long long int tete = current_detail.Soluong * current_detail.Dongia * (current_detail.VAT / 100.0 + 1.0);
			gotoxy(xx[6] + 2, y + (i + 1) * 2 + 1);	cout << tete;
		}
	}
	gotoxy(130, 4);
	cout << "Tong hoa don: " << total_value_details(*db_list) << "               ";
}

Insert create_insert_bill_details(int x, int y)
{
	Insert insert;
	insert.create(3, 4, 0);

	Text_field id_field;
	id_field.create(x, y + 4, 50, 3, " MATERIAL ID ", 10);
	Text_field am_field;
	am_field.create(x, y + 8, 50, 3, " AMOUNT ", 30);
	am_field.only_number = true;
	Text_field price_field;
	price_field.create(x, y + 12, 50, 3, " PRICE ", 30);
	price_field.only_number = true;
	Text_field vat_field;
	vat_field.create(x, y + 16, 50, 3, " % VAT ", 30);
	vat_field.only_number = true;

	Button add_button;
	add_button.create(x + 50 / 2 - 5, y + 20, 10, 3, "ADD");
	Button back_button;
	back_button.create(x + 50 / 2 - 5, y + 24, 10, 3, "BACK");
	Button remove_button;
	remove_button.create(x + 50 / 2 - 10, y + 29, 20, 3, "REMOVE A DETAIL");

	insert.add_textfield(id_field);
	insert.add_textfield(am_field);
	insert.add_textfield(price_field);
	insert.add_textfield(vat_field);
	insert.add_button(add_button);
	insert.add_button(back_button);
	insert.add_button(remove_button);

	return insert;
}

Insert delete_detail(int x, int y)
{
	Insert insert;
	insert.create(2, 1, 0);

	Text_field id_field;
	id_field.create(x, y + 33, 50, 3, " Nhap So Thu Tu Can Xoa ", 2);
	id_field.only_number = true;
	Button ok_button, back_button;
	ok_button.create(x + 50 / 2 - 5, y + 37, 10, 3, "OK");
	back_button.create(x + 50 / 2 - 5, y + 41, 10, 3, "CANCEL");
	insert.add_textfield(id_field);
	insert.add_button(ok_button);
	insert.add_button(back_button);

	return insert;
}

void add_detail(Material_Tree& tree, Bill& bill, string type)
{
	int x = 1, y = 1;
	Bill_details bill_details;
	Insert insert = create_insert_bill_details(x, y);

	while (true)
	{
		insert.draw();
		int xx[7] = { 60,90,100,115,130,140,150 };
		draw_bill_detail_list(tree, bill.billbetail_list_ptr, 55, 5, 110, 21, xx);
		int action = insert.update();
		switch (action)
		{
		case 0: //add
		{
			bool error = false;
			bool enough = true;
			//kiem tra loi xong moi push vao
			for (int i = 0; i < insert.text_field_size; i++)
			{
				if (insert.text_fields[i].text.size() < 1)
				{
					error = true;
				}
			}
			Material_Node* temp = tree.search(insert.text_fields[0].text);
			if (temp == nullptr)
			{
				error = true;
			}
			if(type == "X"&&temp->material.Inventory_num==0)
			{
				gotoxy(1,36);
				cout<<"             Vat tu khong con hang !                ";
				break;
			}
			if (type == "X" && temp->material.Inventory_num < atoi(insert.text_fields[1].text.c_str()))
			{
				
				//cls();
				gotoxy(1,36);
				cout<<"Vat tu "<<temp->material.Name<<" khong con du so luong !";
				gotoxy(1,38);
				cout<<"Chi con lai "<<temp->material.Inventory_num<<' '<<temp->material.Cal_Unit;
				gotoxy(1,40);
				cout<<"Ban co muon mua "<<temp->material.Inventory_num<<' '<<temp->material.Cal_Unit<<' '<<temp->material.Name<<" ?";
				Button co,khong;
				co.create(16,42,20,3,"[ENTER] = Co");
				co.draw_normal();
				khong.create(16,45,20,3,"[ESC] = Khong");
				khong.draw_normal();
			
				bool loop=true;
				while(loop)
				{
					char input=getch();
					switch(input)
					{
						case enter:
							{
								insert.text_fields[1].text=to_string(temp->material.Inventory_num);
								loop=false;
								break;
							}
						case esc:
							{
								enough=false;
								loop=false;
								break;
							}
					}
				}
				cls();
			//	enough = false;
			}
			if (!error && enough)
			{
				cls();
				
				bill_details.MAVT = insert.text_fields[0].text;
				bill_details.Soluong = atoi(insert.text_fields[1].text.c_str());
				bill_details.Dongia = atoi(insert.text_fields[2].text.c_str());
				bill_details.VAT = atoi(insert.text_fields[3].text.c_str());
				if (bill.billbetail_list_ptr == nullptr)
				{
					bill.billbetail_list_ptr = new Billdetails_list;
				}
				bill.billbetail_list_ptr->push_back(bill_details);
				/*	temp->material.Inventory_num -= bill_details.Soluong;*/

				insert.text_fields[0].text = "";
				insert.text_fields[1].text = "";
				insert.text_fields[2].text = "";
				insert.text_fields[3].text = "";
			}
			else
			{
				gotoxy(70, 2);
				if (error) cout << "Ma vat tu khong ton tai hoac thieu thong tin !!";
			//	if (!enough) cout << "Khong du so luong vat tu !!";
		//		Sleep(1000);
			}
		//	cls();
			break;
		}

		case 1: //back
		{
			cls();
			return;
		}
		case 2:
		{
			Insert insert_delete = delete_detail(x, y);
			bool is_input = true;
			while (is_input)
			{
				insert_delete.draw();
				int action = insert_delete.update();
				switch (action)
				{
				case 0:
				{
					bill.billbetail_list_ptr->delete_at(atoi(insert_delete.text_fields[0].text.c_str()) - 1);
					/*cls();
					draw_bill_detail_list(tree, bill.billbetail_list_ptr, 55, 5, 110, 21, xx);
					is_input=false;
					break;*/
				}
				case 1:
				{
					cls();
					is_input = false;
					break;
				}
				}
			}

		}
		break;
		}
	}

}

Insert create_insert_bill(int x, int y)
{
	Insert insert;
	insert.create(3, 2, 1);

	Text_field id_field;
	id_field.create(x, y + 4, 50, 3, " BILL ID ", 20);
	Text_field date_field;
	date_field.create(x, y + 8, 50, 3, " DATE ", 30);
	date_field.date = true;

	Select_field type_field;
	type_field.create(x, y + 12, 50, 3, 2, " TYPE ");
	type_field.add_option("N");
	type_field.add_option("X");

	Button details_button;
	details_button.create(x + 50 / 2 - 15, y + 16, 30, 3, "ADD DETAILS");
	Button add_button;
	add_button.create(x + 50 / 2 - 10, y + 20, 20, 3, "ADD");
	Button back_button;
	back_button.create(x + 50 / 2 - 10, y + 24, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_textfield(date_field);
	insert.add_selectfield(type_field);
	insert.add_button(details_button);
	insert.add_button(add_button);
	insert.add_button(back_button);

	return insert;
}

void create_bill(Material_Tree& tree, Bill_linked_list* bill_list, Employee_List& e_list)
{
	Insert insert = create_insert_bill(1, 1);
	Bill new_bill;
	new_bill.billbetail_list_ptr = new Billdetails_list;
	while (true)
	{
		insert.draw();
		int x = 55, y = 5;
		int xx[7] = { 60,90,100,115,130,140,150 };
		draw_bill_detail_list(tree, new_bill.billbetail_list_ptr, 55, 5, 110, 21, xx);


		int action = insert.update();
		switch (action)
		{
		case 0: //add details
		{
			cls();

			add_detail(tree, new_bill, insert.select_fields[0].options[insert.select_fields[0].select]);
			if (new_bill.billbetail_list_ptr->size < 1)
			{
				delete new_bill.billbetail_list_ptr;
			}
			break;
		}
		case 1: //add
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
			if (e_list.is_bill_id_existed(insert.text_fields[0].text))
			{
				error = true;
			}
			if (!error)
			{
				new_bill.ID = insert.text_fields[0].text;
				new_bill.date.get_date(insert.text_fields[1].text);
				new_bill.Type = insert.select_fields[0].options[insert.select_fields[0].select];

				//
				for (int i = 0; i < new_bill.billbetail_list_ptr->size; i++)
				{
					Material_Node* node = tree.search(new_bill.billbetail_list_ptr->array[i].MAVT);
			//		Material_Node* node_name = tree.search_name(new_bill.billbetail_list_ptr->array[i]->MAVT);
					if (new_bill.Type == "X")
					{
						node->material.Inventory_num -= new_bill.billbetail_list_ptr->array[i].Soluong;
			//			node_name->material.Inventory_num -= new_bill.billbetail_list_ptr->array[i]->Soluong;
					}
					else
					{
						node->material.Inventory_num += new_bill.billbetail_list_ptr->array[i].Soluong;
			//			node_name->material.Inventory_num += new_bill.billbetail_list_ptr->array[i]->Soluong;
					}

				}


				bill_list->push_front(new_bill);
				
				cls();
				gotoxy(10,20);
				cout<<"                 Lap hoa don thanh cong !        ";
				draw_bill_detail_list(tree, new_bill.billbetail_list_ptr, 55, 5, 110, 21, xx);
			//	Sleep(1000);
				cin.get();
				new_bill.billbetail_list_ptr = new Billdetails_list;

				insert.text_fields[0].text = "";
				insert.text_fields[1].text = "";
				
				return;
			}
			else
			{
				gotoxy(70, 2);
				cout << "So Hoa Don Trung Hoac Thieu Thong Tin !!";
			//	Sleep(1000);
			//	cls();
			}

			break;
		}
		case 2: //back
		{
			cls();
		//	if (new_bill.billbetail_list_ptr->size < 1)
		//	{
		//		delete new_bill.billbetail_list_ptr;
		//	}
			return;
		}
		}
	}
}

void create_bill_main(Material_Tree& tree, Employee_List& e_list)
{
	Employee* emp;
	emp = find_employee(73, 5, e_list);

	if (emp != nullptr)
	{
		if (emp->bill_linkedlist_ptr == nullptr)
		{
			emp->bill_linkedlist_ptr = new Bill_linked_list;
		}
		create_bill(tree, emp->bill_linkedlist_ptr, e_list);

	}
}

bool insert_from_time_to_time(Insert& insert, Date& date_from, Date& date_to)
{
	bool isinput = true;
	insert.create(2, 2, 0);

	Text_field from_field, to_field;
	from_field.create(60, 10, 50, 3, "From Day", 10);
	from_field.date = true;
	to_field.create(60, 14, 50, 3, "To Day", 10);
	to_field.date = true;

	Button ok_button, back_button;
	ok_button.create(60 + 50 / 2 - 10, 20, 20, 3, "OK");
	back_button.create(60 + 50 / 2 - 10, 24, 20, 3, "BACK");

	insert.add_textfield(from_field);
	insert.add_textfield(to_field);
	insert.add_button(ok_button);
	insert.add_button(back_button);

	while (isinput)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0:
		{
			if (insert.text_fields[0].text.size() == 10 && insert.text_fields[1].text.size() == 10)
			{
				date_from.get_date(insert.text_fields[0].text);
				date_to.get_date(insert.text_fields[1].text);
				return true;
				break;
			}
			else
			{
				gotoxy(70, 5);
				cout << "Hay nhap dung dinh dang ngay !!";
				break;
			}
		}
		case 1:
		{
			cls();
			return false;
		}
		}
	}

}

void view_bill_by_id(Material_Tree& tree, Employee_List& e_list)
{
	bool loop = true;
	Insert insert = create_find_bill();
	while (loop)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0:
		{
			for (int i = 0; i < e_list.size; i++)
			{
				if (e_list.array[i]->bill_linkedlist_ptr == nullptr)continue;
				for (Bill_Node* find = e_list.array[i]->bill_linkedlist_ptr->head; find != nullptr; find = find->next)
				{
					if (find->bill.ID == insert.text_fields[0].text)
					{
						cls();
						int xx[7] = { 20,50,85,100,115,125,135 };
						draw_bill_detail_list(tree, find->bill.billbetail_list_ptr, 14, 5, 140, find->bill.billbetail_list_ptr->size + 1, xx);
						gotoxy(14, 1);
						cout << "Bam [Enter] de thoat";
						SetColor(RED);
						gotoxy(14, 4);
						cout << "Hoa Don So: " << find->bill.ID;
						gotoxy(50, 4);
						cout << "Nhan Vien Lap: " << e_list.array[i]->FName << ' ' << e_list.array[i]->LName;
						gotoxy(95, 4);
						cout << "Ngay Lap: " << find->bill.date.day << '/' << find->bill.date.month << '/' << find->bill.date.year;
						gotoxy(130, 4);
						cout << "Tong Tri Gia: " << total_value(find);
						SetColor(WHITE);
						cin.get();
						cls();
						loop = false;
					}
					else
					{
						gotoxy(72, 18);
						cout << "Ma hoa don khong ton tai !";


					}
				}
			}
			break;

		}
		case 1:
		{
			return;
		}
		}
	}
}

void view_bill_list_time(Material_Tree& tree, Employee_List& e_list)
{
	Date from_date, to_date;
	Insert insert;
	if (!insert_from_time_to_time(insert, from_date, to_date)) return;

	SetColor(WHITE);
	gotoxy(50, 1);
	cout << "========== BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN ==========";
	gotoxy(64, 3);
	cout << "TU NGAY: ";
	SetColor(CYAN);
	cout << from_date.day << '/' << from_date.month << '/' << from_date.year;
	SetColor(WHITE);
	cout << " DEN NGAY: ";
	SetColor(CYAN);
	cout << to_date.day << '/' << to_date.month << '/' << to_date.year;
	int x = 4, y = 5, w = 160, h = 20;
	int count = 0;
	int xx[4] = { 20,60,80,130 };
	draw_beautiful_table(x, y, w, h, xx, 4);
	gotoxy(x + 3, y + count + 1); cout << "So Hoa Don";
	gotoxy(xx[0] + 15, y + count + 1); cout << "Ngay Lap";
	gotoxy(xx[1] + 4, y + count + 1); cout << "Loai Hoa Don";
	gotoxy(xx[2] + 12, y + count + 1); cout << "Nhan Vien Lap Hoa Don";
	gotoxy(xx[3] + 7, y + count + 1); cout << "Tri Gia Hoa Don";

	////////////////
	////////////////

	for (int i = 0; i < e_list.size; i++)
	{
		if (e_list.array[i]->bill_linkedlist_ptr == nullptr)continue;
		for (Bill_Node* find = e_list.array[i]->bill_linkedlist_ptr->head; find != nullptr; find = find->next)
		{
			if (find->bill.date.before_day(to_date) && from_date.before_day(find->bill.date))
			{
				count += 2;
				Material_Node* temp_material_node = tree.search(find->bill.ID);

				gotoxy(x + 2, y + count + 1);		cout << find->bill.ID;
				gotoxy(xx[0] + 14, y + count + 1);	cout << find->bill.date.day << '/' << find->bill.date.month << '/' << find->bill.date.year;
				gotoxy(xx[1] + 10, y + count + 1);	cout << find->bill.Type << endl;
				gotoxy(xx[2] + 16, y + count + 1); cout << e_list.array[i]->LName << ' ' << e_list.array[i]->FName;
				gotoxy(xx[3] + 10, y + count + 1); cout << total_value(find);
			}
		}
	}
	cin.get();
	cls();
}

void view_10best_selling(Material_Tree& tree, Employee_List& e_list)
{
	Date date_from, date_to;
	Insert insert;
	if (!insert_from_time_to_time(insert, date_from, date_to)) return;

	//////////////////////
	//////////////////////
	cls();
	SetColor(WHITE);
	gotoxy(40, 1);
	cout << "========== BANG LIET KE 10 VAT TU CO DOANH THU CAO NHAT TRONG KHOANG THOI GIAN ==========";
	gotoxy(64, 3);
	cout << "TU NGAY: ";
	SetColor(CYAN);
	cout << date_from.day << '/' << date_from.month << '/' << date_from.year;
	SetColor(WHITE);
	cout << " DEN NGAY: ";
	SetColor(CYAN);
	cout << date_to.day << '/' << date_to.month << '/' << date_to.year;
	int x = 37, y = 7, w = 97, h = 11;
	int count = 0;
	int xx[3] = { 50,75,105 };


	////////////////
	////////////////

	long long int max = 0;
	Best_sell_list best_sell_list;
	best_sell_list.create(tree.size);

	for (int i = 0; i < e_list.size; i++)
	{
		if (e_list.array[i]->bill_linkedlist_ptr == nullptr)continue;
		for (Bill_Node* find = e_list.array[i]->bill_linkedlist_ptr->head; find != nullptr; find = find->next)
		{
			if (find->bill.date.before_day(date_to) && date_from.before_day(find->bill.date) && find->bill.Type == "X")
			{
				for (int j = 0; j < find->bill.billbetail_list_ptr->size; j++)
				{
					string mavt = find->bill.billbetail_list_ptr->array[j].MAVT;
					long long money = find->bill.billbetail_list_ptr->array[j].Soluong * find->bill.billbetail_list_ptr->array[j].Dongia * (1.0 + find->bill.billbetail_list_ptr->array[j].VAT / 100.0);
					best_sell_list.push(mavt, money);
				}

			}
		}
	}

	best_sell_list.sort_by_money();
	int c = 10;
	if (c > best_sell_list.size) c = best_sell_list.size;
	if(best_sell_list.size > 10)
	{
		if (best_sell_list.data[9].money == best_sell_list.data[10].money)
		{
			c += 1;
		}
	}
	
	draw_beautiful_table(x, y, w, c + 1, xx, 3);
	gotoxy(x + 3, y + count + 1); cout << "Rank";
	gotoxy(xx[0] + 10, y + count + 1); cout << "Ma Vat Tu";
	gotoxy(xx[1] + 4, y + count + 1); cout << "Ten Vat Tu";
	gotoxy(xx[2] + 9, y + count + 1); cout << "Tong Doanh Thu";

	for (int i = 0; i < c; i++)
	{
		if (best_sell_list.data[i].MAVT != "")
		{
			count += 2;
			gotoxy(x + 3, y + count + 1); cout << i + 1;
			gotoxy(xx[0] + 10, y + count + 1); cout << best_sell_list.data[i].MAVT;
			gotoxy(xx[1] + 4, y + count + 1); cout << tree.search(best_sell_list.data[i].MAVT)->material.Name;
			gotoxy(xx[2] + 9, y + count + 1); cout << best_sell_list.data[i].money;
		}
	}

	cin.get();
}
