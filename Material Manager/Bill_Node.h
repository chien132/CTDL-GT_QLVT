#pragma once
#include "Bill.h"

struct Bill_Node
{
	Bill bill;
	Bill_Node* next=nullptr;  
};
