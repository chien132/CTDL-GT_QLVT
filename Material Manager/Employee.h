#pragma once
#include <string>
#include "Bill_linked_list.h"
using namespace std;
struct Employee {
	string ID;
	string LName;
	string FName;
	string Sex;
	Bill_linked_list* bill_linkedlist_ptr = nullptr;
};
