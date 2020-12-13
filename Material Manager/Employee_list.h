#pragma once
#include<string>
#include<iostream>
#include"Employee.h"
using namespace std;

struct Employee_List
{
	Employee* array[500];
	int size=0;
	int max_size=500;

	Employee* find(string id)
	{
		for (int i = 0; i < size; i++)
		{
			if (id == array[i]->ID)
			{
				return array[i];
			}
		}
		return nullptr;
	}

	bool full()
	{
		return size == max_size;
	}
	bool empty()
	{
		return size == 0;
	}

	bool push_back(Employee data)
	{
		if (full())
		{
			return false;
		}
		array[size] = new Employee;
		*array[size] = data;
		size++;
		return true;
	}

	bool is_bill_id_existed(string id)
	{
		for (int i = 0; i < size; i++)
		{
			if (array[i]->bill_linkedlist_ptr == nullptr) continue;
			for (auto temp = array[i]->bill_linkedlist_ptr->head; temp != nullptr; temp = temp->next)
			{
				if (id == temp->bill.ID)
					return true;
			}
		}
		return false;
	}

	void pop_back()
	{
		if (empty())
		{
			cout << "Employee list is empty!\n";
			return;
		}
		delete array[size - 1];
		size--;
	}

	void insert_at(int position, Employee data)
	{
		if (position<0 || position>size || full())
		{
			cout << "invalid position!\n";
			return;
		}
		for (int i = size - 1; i >= position; i--)
		{
			array[i + 1] = array[i];
		}
		array[position] = new Employee;
		*array[position] = data;
		size++;
	}

	void delete_id(string id)
	{
		for (int i = 0; i < size; i++)
		{
			if (array[i]->ID == id)
			{
				delete_at(i);
				break;
			}
		}
	}

	void delete_at(int position)
	{
		if (position<0 || position>size - 1 || empty())
		{
			cout << "invalid position!\n";
			return;
		}
		delete array[position];
		for (int i = position; i < size - 1; i++)
		{
			array[i] = array[i + 1];
		}
		size--;
	}

	void clear()
	{
		for (int i = 0; i < size; i++)
		{
			delete array[i];
		}
		size = 0;
	}


};

