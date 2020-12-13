#pragma once
#include "Material_Tree.h"
#include <stack>

Insert create_insert_material()
{
	Insert insert;
	insert.create(2, 4, 0);

	Text_field id_field;
	id_field.create(60, 5, 50, 3, " ID ", 10);
	id_field.read_only = true;
	Text_field name_field;
	name_field.create(60, 9, 50, 3, " NAME ", 30);
	Text_field cu_field;
	cu_field.create(60, 13, 50, 3, " CALCULATOR UNIT ", 30);
	Text_field in_field;
	in_field.create(60, 17, 50, 3, " INVENTORY NUMBER ", 30);
	in_field.only_number = true;

	Button add_button;
	add_button.create(60 + 50 / 2 - 10, 21, 20, 3, "ADD");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 25, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_textfield(name_field);
	insert.add_textfield(cu_field);
	insert.add_textfield(in_field);
	insert.add_button(add_button);
	insert.add_button(back_button);

	return insert;
}

Insert create_find_material()
{
	Insert insert;
	insert.create(2, 1, 0);

	Text_field id_field;
	id_field.create(60, 5, 50, 3, " MATERIAL ID ", 10);

	Button find_button;
	find_button.create(60 + 50 / 2 - 10, 9, 20, 3, "OK");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 13, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_button(find_button);
	insert.add_button(back_button);

	return insert;
}

Insert insert_invnum_only()
{
	Insert insert;
	insert.create(2, 4, 0);

	Text_field id_field;
	id_field.create(60, 5, 50, 3, " ID ", 10);
	id_field.read_only = true;
	Text_field name_field;
	name_field.create(60, 9, 50, 3, " NAME ", 30);
	name_field.read_only = true;
	Text_field cu_field;
	cu_field.create(60, 13, 50, 3, " CALCULATOR UNIT ", 30);
	cu_field.read_only = true;
	Text_field in_field;
	in_field.create(60, 17, 50, 3, " INVENTORY NUMBER ", 30);
	in_field.only_number = true;

	Button add_button;
	add_button.create(60 + 50 / 2 - 10, 21, 20, 3, "ADD");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 25, 20, 3, "BACK");

	insert.add_textfield(id_field);
	insert.add_textfield(name_field);
	insert.add_textfield(cu_field);
	insert.add_textfield(in_field);
	insert.add_button(add_button);
	insert.add_button(back_button);

	return insert;
}

void add_material(Material_Tree& material_tree)
{
	Material material;
	Insert insert1 = create_find_material();
	bool loop;
	while (true)
	{
		loop = true;
		insert1.text_fields[0].text = "";
		//cls();
		insert1.draw();
		int action = insert1.update();
		switch (action)
		{
		case 0:
		{
			material.ID = insert1.text_fields[0].text;
			Material_Node* temp = material_tree.search(material.ID);
			if (temp != nullptr && material.ID == temp->material.ID)
			{
				gotoxy(73, 3);
				cout << "Ma Vat Tu Da Ton Tai !";
				//	Sleep(1000);
				break;
			}
			else if (temp == nullptr && material.ID != "")
			{
				cls();
				Insert insert = create_insert_material();
				insert.text_fields[0].text = material.ID;
				while (loop)
				{
					insert.draw();
					int action = insert.update();
					switch (action)
					{
					case 0:
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
							material.ID = insert.text_fields[0].text;
							material.Name = insert.text_fields[1].text;
							material.Cal_Unit = insert.text_fields[2].text;
							material.Inventory_num = atoi(insert.text_fields[3].text.c_str());


							material_tree.insert(material);

							insert.text_fields[0].text = "";
							insert.text_fields[1].text = "";
							insert.text_fields[2].text = "";
							insert.text_fields[3].text = "";
							gotoxy(70, 2);
							cout << "      Da them vat tu !                     ";
							Sleep(500);
							cls();
							return;
						}
						else
						{
							gotoxy(70, 2);
							cout << "Khong duoc de trong thong tin !!";
							break;
						}

						loop = false;
						break;
					}
					case 1:
					{
						cls();
						loop = false;
					}
					}
				}
			}
			break;
		}
		case 1:
		{
			cls();
			return;
		}
		}
	}



}

Material_Node* find_material(Material_Tree& tree)
{
	Insert insert = create_find_material();
	Material_Node* current_material = nullptr;
	while (true)
	{
		insert.draw();
		int action = insert.update();
		switch (action)
		{
		case 0:
		{
			string id = insert.text_fields[0].text;
			current_material = tree.search(id);
			if (current_material != nullptr)
			{
				cls();

				return current_material;
			}
			else
			{
				gotoxy(73, 2);
				cout << "Khong tim thay ma vat tu !";
				//	Sleep(1000);
			}
			//cls();
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

Insert insert_edit_del_material()
{
	Insert insert;
	insert.create(3, 3, 0);

	Text_field name_field;
	name_field.create(60, 5, 50, 3, " NAME ", 30);
	Text_field cu_field;
	cu_field.create(60, 9, 50, 3, " CALCULATOR UNIT ", 30);
	Text_field in_field;
	in_field.create(60, 13, 50, 3, " INVENTORY NUMBER ", 30);
	in_field.only_number = true;
	in_field.read_only = true;

	Button add_button;
	add_button.create(60 + 50 / 2 - 10, 17, 20, 3, "SAVE");
	Button back_button;
	back_button.create(60 + 50 / 2 - 10, 21, 20, 3, "BACK");
	Button del_button;
	del_button.create(60 + 50 / 2 - 10, 29, 20, 3, "DELETE");

	insert.add_textfield(name_field);
	insert.add_textfield(cu_field);
	insert.add_textfield(in_field);
	insert.add_button(add_button);
	insert.add_button(back_button);
	insert.add_button(del_button);

	return insert;
}

void edit_del_material(Material_Tree& material_tree, Employee_List& e_list)
{
	Material_Node* node = find_material(material_tree);

	if (node == nullptr)
	{
		return;
	}

	Insert insert = insert_edit_del_material();
	insert.text_fields[0].text = node->material.Name;
	insert.text_fields[1].text = node->material.Cal_Unit;
	insert.text_fields[2].text = to_string(node->material.Inventory_num);

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
				node->material.Name = insert.text_fields[0].text;
				node->material.Cal_Unit = insert.text_fields[1].text;
				node->material.Inventory_num = atoi(insert.text_fields[2].text.c_str());

				gotoxy(70, 2);
				cout << "Da cap nhat thong tin vat tu !";
				Sleep(1000);
				cls();
			}
			else
			{
				gotoxy(70, 2);
				cout << "Khong duoc de trong thong tin !!                         ";
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
			bool is_selled = false;
			for (int i = 0; i < e_list.size; i++)
			{
				if (e_list.array[i]->bill_linkedlist_ptr == nullptr)continue;
				for (Bill_Node* find = e_list.array[i]->bill_linkedlist_ptr->head; find != nullptr && find->bill.Type == "X"; find = find->next)
				{
					for (int j = 0; j < find->bill.billbetail_list_ptr->size; j++)
					{
						if (node->material.ID == find->bill.billbetail_list_ptr->array[j].MAVT)
						{
							is_selled = true;
						}
					}
				}
			}
			if (node->material.Inventory_num == 0 && !is_selled)
			{
				material_tree.remove(node->material.ID);
				gotoxy(70, 2);
				cout << "       Da xoa vat tu !                     ";
				Sleep(1000);
				cls();
				return;
			}
			else
			{
				gotoxy(70, 2);
				cout << "   Khong the xoa vat tu nay !                         ";
				break;
			}
		}
		}
	}
}

void material_modifies(Material_Tree& material_tree, Employee_List& e_list)
{
	Menu menu_material;
	menu_material.create(3);
	menu_material.add_button(60, 9, 50, 3, "Add New Material");
	menu_material.add_button(60, 13, 50, 3, "Edit A Material");
	menu_material.add_button(60, 21, 50, 3, "Back To Main Menu");
	while (true)
	{
		menu_material.draw();
		int action = menu_material.update();
		switch (action)
		{
		case 0:
		{
			cls();
			add_material(material_tree);
			break;
		}
		case 1:
		{
			cls();
			edit_del_material(material_tree, e_list);
			break;
		}
		case 2:
		{
			cls();
			return;
		}
		}
	}
}

struct Material_stack
{
	int STACKSIZE = 50;
	Material node[50];
	int sp = -1;
	int push(Material_stack& st, Material m)
	{
		if (st.sp == STACKSIZE - 1)  return 0;
		st.node[++st.sp] = m;
		return 1;
	}
	int pop(Material_stack& st, Material& m)
	{
		if (st.sp == -1)  return 0;
		m = st.node[st.sp--];
		return 1;
	}
};

void LNR(Material_Node* node, Material_stack& st)    // lam lai bang mang
{
	if (node == nullptr)
	{
		return;
	}
	LNR(node->left, st);
	st.push(st, node->material);
	LNR(node->right, st);
}


void view_material(Material_Tree& tree)
{
	int x = 37, y = 4, w = 97, h = tree.size + 1;
	SetColor(WHITE);
	gotoxy(57, 1);
	cout << "========== BANG LIET KE CAC VAT TU CON TON KHO ==========";

	int xx[3] = { 50,85,105 };
	draw_beautiful_table(x, y, w, h, xx, 3);
	gotoxy(x + 3, y + 1); cout << "Ma Vat Tu";
	gotoxy(xx[0] + 10, y + 1); cout << "Ten Vat Tu";
	gotoxy(xx[1] + 4, y + 1); cout << "Don Vi Tinh";
	gotoxy(xx[2] + 9, y + 1); cout << "So Luong Ton";

	Material_stack st;
	LNR(tree.root, st);
	Material array[50];
	for (int i = 0; i < tree.size; i++)
	{
		st.pop(st, array[i]);
	}
	for (int i = 0; i < tree.size; i++)
	{
		for (int j = i; j < tree.size; j++)
		{
			if (array[j].Name < array[i].Name) swap(array[i], array[j]);
		}
	}
	for (int i = 0; i < tree.size; i++)
	{
		gotoxy(x + 3, y + 3);
		cout << array[i].ID;
		gotoxy(50 + 10, y + 3);
		cout << array[i].Name;
		gotoxy(85 + 4, y + 3);
		cout << array[i].Cal_Unit;
		gotoxy(105 + 9, y + 3);
		cout << array[i].Inventory_num;
		y += 2;
	}
	cin.get();
}


