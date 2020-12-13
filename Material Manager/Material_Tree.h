#pragma once
#include "Material_Node.h"
#include <algorithm>
#include <iostream>

struct Material_Tree {
	Material_Node* root = nullptr;

	int size = 0;
	int size_by_name = 0;

	//ham se dung
	void insert(Material material)
	{
		root = insert_recursive(material, root);
	}

	void remove(string id)
	{
		root = remove_recursive(id, root);
	}

	//De qui


	Material_Node* insert_recursive(Material material, Material_Node* node) {
		if (node == nullptr)
		{
			node = new Material_Node;
			node->material = material;
			size++;
		}

		if (material.ID.compare(node->material.ID) < 0)
		{
			node->left = insert_recursive(material, node->left);

			///////////////////////             A    V    L             //////////////////////////

			/*if (get_height(node->left) - get_height(node->right) >= 2)
			{
				if (material.ID.compare(node->left->material.ID) < 0)
				{
					node = rotate_right(node);
				}
				else
				{
					node = rotate_left_then_right(node);
				}
			}*/

			///////////////////////             A    V    L             //////////////////////////

		}

		else if (material.ID.compare(node->material.ID) > 0)
		{
			node->right = insert_recursive(material, node->right);

			///////////////////////             A    V    L             //////////////////////////

			/*if (get_height(node->left) - get_height(node->right) >= 2)
			{
				if (material.ID.compare(node->right->material.ID) > 0)
				{
					node = rotate_left(node);
				}
				else
				{
					node = rotate_right_then_left(node);
				}
			}*/

			///////////////////////             A    V    L             //////////////////////////
		}


		///////////////////////             A    V    L             //////////////////////////

		/*node->height = max(get_height(node->left), get_height(node->right)) + 1;*/

		///////////////////////             A    V    L             //////////////////////////

		return node;
	}

	Material_Node* find_min(Material_Node* node)
	{
		Material_Node* temp = node;
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp;
	}

	Material_Node* search_recursive(Material_Node* node, string id)
	{
		if (node == nullptr || node->material.ID == id)
		{
			return node;
		}
		if (id.compare(node->material.ID) < 0)
		{
			return search_recursive(node->left, id);
		}

		return search_recursive(node->right, id);

	}
	
	void clear_recursive(Material_Node* node)
	{
		if(node==nullptr)
		{
			return;
		}
		clear_recursive(node->left);
		clear_recursive(node->right);
		delete node;
	}
	

	Material_Node* search(string id)
	{
		return search_recursive(root, id);
	}
	

	Material_Node* remove_recursive(string id, Material_Node* node)
	{
		if (node == nullptr)
		{
			return node;
		}

		if (id.compare(node->material.ID) < 0)
		{
			node->left = remove_recursive(id, node->left);
		}
		else if (id.compare(node->material.ID) > 0)
		{
			node->right = remove_recursive(id, node->right);
		}
		else
		{
			//tim thay node can xoa

			//truong hop leaf node
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
				size--;
			}
			else if (node->left == nullptr)
			{
				Material_Node* temp = node;
				node = node->right;
				delete  temp;
				size--;
			}
			else if (node->right == nullptr)
			{
				Material_Node* temp = node;
				node = node->left;
				delete temp;
				size--;
			}
			else
			{
				Material_Node* temp = find_min(node->right);  //tim node nho nhat ben phai
				node->material = temp->material;
				node->right = remove_recursive(temp->material.ID, node->right);
			}
		}

		// sau khi xoa xong:
		///////////////////////             A    V    L             //////////////////////////

		//if (node == nullptr)
		//{
		//	return node;
		//}
		//node->height = max(get_height(node->left), get_height(node->right)) + 1;

		//if (get_height(node->left) - get_height(node->right) > 1)
		//{
		//	if (get_height(node->left->left) - get_height(node->left->right) > 0)
		//	{
		//		node = rotate_right(node);
		//	}
		//	else
		//	{
		//		rotate_left_then_right(node);
		//	}
		//}
		//if (get_height(node->right) - get_height(node->left) > 1)
		//{
		//	if (get_height(node->right->right) - get_height(node->right->left) > 0)
		//	{
		//		node = rotate_left(node);
		//	}
		//	else
		//	{
		//		node = rotate_right_then_left(node);
		//	}
		//}

		///////////////////////             A    V    L             //////////////////////////

		return node;
	}

	///////////////////////             A    V    L             //////////////////////////

	//int get_height(Material_Node* node)
	//{
	//	if (node == nullptr)
	//	{
	//		return -1;
	//	}
	//	return node->height;
	//}

	//Material_Node* rotate_right(Material_Node* node)
	//{
	//	Material_Node* temp = node->left;
	//	node->left = temp->right;
	//	temp->right = node;
	//	// update height
	//	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	//	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;
	//	return temp;
	//}
	//Material_Node* rotate_left(Material_Node* node)
	//{
	//	Material_Node* temp = node->right;
	//	node->right = temp->left;
	//	temp->left = node;
	//	// update height
	//	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	//	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;
	//	return temp;
	//}
	//Material_Node* rotate_left_then_right(Material_Node* node)
	//{
	//	node->left = rotate_left(node->left);
	//	return rotate_right(node);
	//}
	//Material_Node* rotate_right_then_left(Material_Node* node)
	//{
	//	node->right = rotate_right(node->right);
	//	return rotate_left(node);
	//}

	///////////////////////             A    V    L             //////////////////////////

};
