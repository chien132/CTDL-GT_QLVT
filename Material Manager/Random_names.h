#pragma once
#include <string>
#include <vector>
#include "Employee.h"
using namespace std;

class Random_names
{
	vector<string> names;
	vector<string> ho;
	int count = 0;

	void random();
public:
	void add_name(string name);
	void add_ho(string ho);
	Employee get();
	Random_names();
	~Random_names();
};

