#include <string>
#include "Menu.h"
#include "Material_Tree.h"
#include "Employee_Manager.h"
#include "Database.h"
#include "Bill_Manager.h"
#include "Material_Manager.h"
#include "Random_names.h"

using namespace std;

int main()
{
	resizeConsole(1366, 768);
	//FullScreen();

	Employee_List e_list;
	read_emp_list(e_list);

	Material_Tree material_tree;
	read_material_tree(material_tree);

	//Random_names r;
	//for(int i=0;i<50;i++)
	//{
	//	e_list.push_back(r.get());
	//}

//	cout<<char(97)<<endl<<char(122); cin.get();

	Menu menu;
	menu.create(20);
	menu.add_button(60, 5, 50, 3, "Material Modifies");
	menu.add_button(60, 9, 50, 3, "View Materials");
	menu.add_button(60, 13, 50, 3, "Employee Modifies");
	menu.add_button(60, 17, 50, 3, "View Employees");
	menu.add_button(60, 21, 50, 3, "Make An Invoice");
	menu.add_button(60, 25, 50, 3, "View An Invoice");
	menu.add_button(60, 29, 50, 3, "View Invoices From.... to....");
	menu.add_button(60, 33, 50, 3, "10 Best Selling Material");
	menu.add_button(60, 37, 50, 3, "Exit");

	while (1)
	{
		/*auto save
		save_material_tree(material_tree);
		save_employee_list(e_list); */

		cls();
		menu.draw();
		int action = menu.update();
		switch (action)
		{
		case 0: // Cap nhat vat tu
		{
			cls();
			material_modifies(material_tree, e_list);
			break;
		}
		case 1: // In danh sach vat tu ton kho
		{
			cls();
			view_material(material_tree);
			break;
		}
		case 2: // Cap nhat nhan vien
		{
			cls();
			employee_modifies(e_list);
			break;
		}
		case 3: // Xem danh sach nhan vien
		{
			cls();
			watch_employee_list(e_list);
			break;
		}
		case 4: // Lap hoa don
		{
			cls();
			create_bill_main(material_tree, e_list);
			break;
		}
		case 5: // In hoa don
		{
			cls();
			view_bill_by_id(material_tree, e_list);
			break;
		}
		case 6: // Thong ke hoa don trong 1 khoang thoi gian
		{
			cls();
			view_bill_list_time(material_tree, e_list);
			break;
		}
		case 7: // In 10 vat tu co doanh thu cao nhat trong 1 khoang thoi gian
		{
			cls();
			view_10best_selling(material_tree, e_list);
			break;
		}
		case 8:
		{
			save_and_free_memory(e_list, material_tree);
			return 0;
		}
		}
	}
}
