#include "pch.h"
#include "btree.h"


btree::btree()
{
    root = nullptr;
}

void btree::destroy_tree(node* leaf)
{
    if (leaf != nullptr)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void btree::insert(const int key, node* leaf) const
{
    if (key < leaf->value)
    {
        if (leaf->left != nullptr)
            insert(key, leaf->left);
        else
        {
            leaf->left = new node;
            leaf->left->value = key;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if (key >= leaf->value)
    {
        if (leaf->right != nullptr)
            insert(key, leaf->right);
        else
        {
            leaf->right = new node;
            leaf->right->value = key;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
        }
    }
}

void btree::insert(const int key)
{
    if (root != nullptr)
    {
        insert(key, root);
    }
    else
    {
        root = new node;
        root->value = key;
        root->left = nullptr;
        root->right = nullptr;
    }
}

node* btree::search(const int key) const
{
    return search(key, root);
}

void btree::traverse(node* root, const std::function<void(node*)>& callback)
{
    if (root != nullptr)
    {
        traverse(root->left, callback);
        callback(root);
        traverse(root->right, callback);
    }
}

node* btree::get_root() const
{
    return root;
}

node* btree::search(const int key, node* leaf) const
{
    if (leaf != nullptr)
    {
        if (key == leaf->value)
            return leaf;
        if (key < leaf->value)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else return nullptr;
}

btree::~btree()
{
    destroy_tree(root);
}
