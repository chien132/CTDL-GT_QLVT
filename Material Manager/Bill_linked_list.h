#pragma once
#include "Bill_Node.h"

struct Bill_linked_list
{
	Bill_Node* head = nullptr;
	int size = 0;

	Bill* find(string id)
	{
		for (Bill_Node* temp = head; temp != nullptr; temp = temp->next)
		{
			if (id == temp->bill.ID)
			{
				return &temp->bill;
			}
		}
		return nullptr;
	}

	void push_front(Bill bill)
	{
		Bill_Node* new_node = new  Bill_Node;
		new_node->bill = bill;
		if(head==nullptr) //if empty
		{
			head = new_node;
		}
		else
		{
			new_node->next = head;
			head = new_node;
		}
		size++;
	}

	void push_front(Bill_Node *bill_node)
	{
		if (head == nullptr) //if empty
		{
			head = bill_node;
		}
		else
		{
			bill_node->next = head;
			head = bill_node;
		}
		size++;
	}

	void pop_front(){
		if(head==nullptr){
			return;
		}
		Bill_Node* temp=head;
		head=head->next;
		delete temp;
		size--;
	}
	void push_back(Bill bill){
		Bill_Node* new_node = new Bill_Node;
		new_node->bill=bill;
		
		if(head==nullptr){
			head = new_node;
			size++;
			return;
		}
		
		Bill_Node* current=head;
		while(current->next!=nullptr){
			current=current->next;
		}
		current->next=new_node;
		size++;
	}
	

};
