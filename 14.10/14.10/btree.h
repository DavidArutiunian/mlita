#pragma once
#include "node.h"
#include <functional>

class btree
{
public:
	btree();
	~btree();

	void insert(int key);
	node *search(int key) const;
    static void traverse(node *root, const std::function<void(node *)>& callback);
	node * get_root() const;

private:
    static void destroy_tree(node *leaf);
	void insert(int key, node *leaf) const;
	node *search(int key, node *leaf) const;

	node *root;
};
