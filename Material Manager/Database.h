#pragma once
#include<fstream>
#include "Employee_Manager.h"
#include <functional>


using namespace std;

/////////////////////////////////////       Save         Bill                /////////////////

void save_bill_details(Bill_details bill_details, ofstream& file)
{
	file << bill_details.MAVT << ',';
	file << bill_details.Soluong << ',';
	file << bill_details.Dongia << ',';
	file << bill_details.VAT << endl;
}

void save_bill_details_list(Billdetails_list* billdetails_list, ofstream& file)
{
	if(billdetails_list==nullptr)
	{
		file << 0 << endl;
		return;
	}
	file << billdetails_list->size << '\n';
	for (int i = 0; i < billdetails_list->size; i++)
	{
		save_bill_details(billdetails_list->array[i], file);
	}
}


void save_bill(Bill bill, ofstream& file)
{
	file << bill.ID << ',';
	file << bill.date.day << ',';
	file << bill.date.month << ',';
	file << bill.date.year << ',';
	file << bill.Type << endl;
}

void save_bill_linked_list(Bill_linked_list* bill_linked_list, ofstream& file)
{
	if(bill_linked_list==nullptr)
	{
		file << 0 << endl;
		return;
	}
	file << bill_linked_list->size << '\n';
	for (Bill_Node* temp = bill_linked_list->head; temp != nullptr; temp = temp->next)
	{
		save_bill(temp->bill, file);
		save_bill_details_list(temp->bill.billbetail_list_ptr, file);
	}
}

/////////////////////////////////////       Read         Bill                /////////////////

Bill_details read_bill_details(ifstream& file)
{
	Bill_details bill_details;
	getline(file, bill_details.MAVT, ',');

	string temp;
	getline(file, temp, ',');
	bill_details.Soluong = atoi(temp.c_str());
	getline(file, temp, ',');
	bill_details.Dongia=atoi(temp.c_str());
	getline(file, temp);
	bill_details.VAT=atoi(temp.c_str());


	return bill_details;
}

void read_bill_details_list(Billdetails_list* billdetails_list, ifstream& file)
{
	int size = 0;
	file >> size;
	string line;
	getline(file, line); //xuong hang

	for (int i = 0; i < size; i++)
	{
		Bill_details bill_details = read_bill_details(file);
		billdetails_list->push_back(bill_details);
	}
}

void read_bill(Bill &bill, ifstream& file)
{
	getline(file, bill.ID, ',');
	string temp;
	getline(file, temp, ',');
	bill.date.day = atoi(temp.c_str());
	getline(file, temp, ',');
	bill.date.month = atoi(temp.c_str());
	getline(file, temp, ',');
	bill.date.year = atoi(temp.c_str());
	getline(file, bill.Type);
}

void read_bill_linked_list(Bill_linked_list* bill_linked_list,ifstream &file)
{
	int size = 0;
	file >> size;
	string temp;
	getline(file, temp);
	for(int i=0;i<size;i++)
	{
		Bill bill;
		Billdetails_list* billdetails_list = new Billdetails_list;

		read_bill(bill, file);
		read_bill_details_list(billdetails_list,file);
		bill_linked_list->push_front(bill);
		bill_linked_list->head->bill.billbetail_list_ptr = billdetails_list;

		/*      PUSH BACK     
		bill_linked_list->push_back(bill);
		auto temp= bill_linked_list->head;
		for ( temp ; temp->next != nullptr; temp = temp->next);
		temp->bill.billbetail_list_ptr = billdetails_list;*/
	}
}



///////////////////////////////////////////////////////////////// Employee          Save

void save_employee(Employee employee, ofstream& file)
{
	file << employee.ID << ',';
	file << employee.FName << ',';
	file << employee.LName << ',';
	file << employee.Sex << endl;
}

void save_employee_list(Employee_List employee_list)
{
	ofstream file("Data/EmployeeList.csv");
	file << employee_list.size << '\n';
	for (int i = 0; i < employee_list.size; i++)
	{
		save_employee(*employee_list.array[i], file);
		save_bill_linked_list(employee_list.array[i]->bill_linkedlist_ptr, file);
	}
	file.close();
}

////////////////////////////////////// Employee     Read   /////////////////


void read_employee(Employee& emp, ifstream& file)
{
	getline(file, emp.ID, ',');
	getline(file, emp.FName, ',');
	getline(file, emp.LName, ',');
	getline(file, emp.Sex);
}

void read_emp_list(Employee_List& emp_list)
{
	ifstream file("Data/EmployeeList.csv");
	if(file.is_open()==false)
	{
		return;
	}
	int size=0;
	string temp;
	file >> size;
	getline(file, temp);
	
	for (int i = 0; i < size; i++)
	{
		Employee emp;
		read_employee(emp, file);
		//debug
		//cout << emp.ID << " " << emp.FName << ' ' << emp.LName << ' ' << emp.Sex;
		//cin.get();

		Bill_linked_list* bill_linked_list = new Bill_linked_list;
		read_bill_linked_list(bill_linked_list, file);
		emp_list.push_back(emp);
		if (bill_linked_list->head == nullptr) continue;
		emp_list.array[emp_list.size - 1]->bill_linkedlist_ptr = bill_linked_list;
	}
	file.close();
}


/////////////////////////////////////////         Material       Save        /////////////////
 
void save_material(Material& material,ofstream&file)
{
	file << material.ID << ',';
	file << material.Name << ',';
	file << material.Cal_Unit << ',';
	file << material.Inventory_num << endl;
}

void save_material_tree_recursive(Material_Node* node,ofstream&file)
{
	if(node==nullptr)
	{
		return;
	}
	///// LNR auto sort theo id
	save_material_tree_recursive(node->left, file);
	save_material(node->material, file);
	save_material_tree_recursive(node->right, file);

}

void save_material_tree(Material_Tree& tree)
{
	ofstream file("Data/Material_Tree.csv");
	file << tree.size << endl;
	save_material_tree_recursive(tree.root, file);
	file.close();
}

//////////////////////////////////////          Material         Read ////////////

void read_material(Material&material,ifstream&file)
{
	string temp;
	getline(file, material.ID, ',');
	getline(file, material.Name, ',');
	getline(file, material.Cal_Unit, ',');
	getline(file, temp);
	material.Inventory_num = atoi(temp.c_str());
}



void read_material_tree(Material_Tree& tree)
{
	ifstream file("Data/Material_Tree.csv");
	if(!file.is_open())
	{
		return;
	}
	int size;
	string temp;
	file >> size;
	getline(file, temp);

	for(int i=0;i<size;i++)
	{
		Material material;
		read_material(material, file);
		tree.insert(material);
	}
	file.close();
}


void save_and_free_memory(Employee_List&e_list,Material_Tree&material_tree)
{
	save_employee_list(e_list);
	save_material_tree(material_tree);
	material_tree.clear_recursive(material_tree.root);
	cls();
	gotoxy(80, 20);
	SetColor(WHITE);
	cout << "Da Luu Du Lieu !";
//	Sleep(500);
	gotoxy(76, 22);
	cout << "Dang Thoat Chuong Trinh";
//	Sleep(500);
}
