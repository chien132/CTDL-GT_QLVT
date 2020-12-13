#pragma once
#include "Bill_Node.h"

struct Best_sell_node
{

	long long money = 0;
	string MAVT="";

};



struct Best_sell_list
{
	Best_sell_node* data;

	int size = 0;
	int max_size;

	void create(int max_size)
	{
		data = new Best_sell_node[max_size];
		this->max_size = max_size;
	}

	void sort_by_money()
	{
		for(int i=0;i<size;i++)
		{
			for(int j=i;j<size;j++)
			{
				if (data[j].money > data[i].money) swap(data[j], data[i]);
			}
		}
	}

	void push(string MAVT, long long money)
	{
		int i = is_contain(MAVT);
		if(i!=-1)
		{
			data[i].money += money;
		}
		else
		{
			Best_sell_node node;
			node.MAVT = MAVT;
			node.money = money;
			data[size] = node;
			size++;
		}
	}

	int is_contain(string MAVT)
	{
		for (int i = 0; i < size; i++)
		{
			if (MAVT == data[i].MAVT) return i;
		}
		return -1;
	}

	bool is_full()
	{
		return size == max_size;
	}
};
