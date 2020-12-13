#pragma once
#include<string>
#include"freeLibrary.h"
#include<iostream>
#include"Bill_details.h"
using namespace std;

struct Billdetails_list
{
	Bill_details array[20];
	int size;
	int max_size=20;
	bool full()
	{
		return size == max_size;
	}
	bool empty()
	{
		return size == 0;
	}
	bool push_back(Bill_details data)
	{
		if (full())
		{
			//	cout << "List is full!\n";
			return false;
		}
		array[size] = data;
		size++;
		return true;
	}
	bool pop_back()
	{
		if (empty())
		{
			return false;
		}
		size--;
		return true;
	}
	bool insert_at(int position, Bill_details data)
	{
		if (position<0 || position>size || full())
		{
			return false;
		}

		for (int i = size - 1; i >= position; i--)
		{
			array[i + 1] = array[i];
		}
		array[position] = data;
		size++;
		return true;
	}
	bool delete_at(int position)
	{
		if (position<0 || position>size - 1 || empty())
		{
			return false;
		}
		for (int i = position; i < size - 1; i++)
		{
			array[i] = array[i + 1];
		}
		size--;
		return true;
	}


};

