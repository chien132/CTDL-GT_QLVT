#include "Random_names.h"


void Random_names::random()
{
	for (int i = 0; i < 3; i++) {
		int r = rand() % names.size();
		swap(names[i], names[r]);
	}
	for (int i = 0; i < 3; i++) {
		int r = rand() % ho.size();
		swap(ho[i], ho[r]);
	}
}

void Random_names::add_name(string name)
{
	names.push_back(name);
}

void Random_names::add_ho(string ho)
{
	this->ho.push_back(ho);
}

Employee Random_names::get()
{
	random();
	static int auto_id = 0;
	Employee emp;
	emp.ID = to_string(auto_id++);
	emp.FName = names[0];
	emp.LName = ho[0];

	int r = rand() % 2;
	if (r == 0)
	{
		emp.Sex = "MALE";
	}
	else if (r == 1)
	{
		emp.Sex = "FEMALE";
	}


	return emp;
}

Random_names::Random_names()
{
	add_name("Duy");
	add_name("Ghe");
	add_name("Bao");
	add_name("Kun");
	add_name("Hoa");
	add_name("Choa");
	add_name("Meo");
	add_name("Mao");
	add_name("Lan");
	add_name("Thanh");
	add_name("Lieu");
	add_name("Ngoc");
	add_name("Chien");
	add_name("Minh");
	add_name("Tran");
	add_name("Nguyen");
	add_name("Pham");
	add_name("Nam");
	add_name("An");
	add_name("Vinh");
	add_name("Linh");
	add_name("Do");
	add_name("Bach");
	add_name("Tuyet");
	add_name("Duong");
	add_name("Le");
	add_name("Van");
	add_name("May");
	add_name("Thao");
	add_name("Thinh");
	add_name("Thien");
	add_name("Xe");
	add_name("Chuot");
	add_name("Thoai");
	add_name("Studio");
	add_name("Lap");
	add_name("Trinh");
	add_name("Qua");
	add_name("Mon");
	add_name("Giai");
	add_name("Thuat");
	
	add_ho("Tran");
	add_ho("Lieu");
	add_ho("Nguyen");
	add_ho("Pham");
	add_ho("Vinh");
	add_ho("Do");
	add_ho("Le");
	add_ho("Duong");
	add_ho("Visual");
	add_ho("Lap");
	add_ho("Dang");
	add_ho("Hoang");

}



Random_names::~Random_names()
{
}
