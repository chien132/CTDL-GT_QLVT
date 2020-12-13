#pragma once
#include"Material.h"

struct Material_Node {
	Material material;
	int height;

	Material_Node* left = nullptr;
	Material_Node* right = nullptr;
};