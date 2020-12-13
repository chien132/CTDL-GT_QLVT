#pragma once
#include<iostream>
#include"Bill_details.h"
using namespace std;

struct Billdetails_array
{
	//int array[100]; //neu biet truoc so luong danh sach
	int* array;
	int size = 0;
	int max_size=20;

	Billdetails_array()
	{
		this->array = new int[max_size];
		this->size = 0;
	}
	bool full()
	{
		return size == max_size;
	}
	bool empty()
	{
		return size == 0;
	}
	void push_back( int data)
	{
		if (full())
		{
			cout << "List is full!\n";
			return;
		}
		array[size] = data;
		size++;
	}
	void pop_back()
	{
		if (empty())
		{
			cout << "Danh sach rong!\n";
			return;
		}
		size--;
	}
	void insert_at( int position, int data)
	{
		if (position<0 || position>size || full())
		{
			cout << "invalid position!\n";
			return;
		}
		size++;
		for (int i = size + 1; i >= position; i--)
		{
			array[i + 1] = array[i];
		}
		array[position] = data;
	}
	void remove_at( int position)
	{
		if (position<0 || position>size - 1)
		{
			cout << "invalid position!\n";
			return;
		}
		for (int i = position; i < size - 1; i++)
		{
			array[i] = array[i + 1];
		}
		size--;
	}
};