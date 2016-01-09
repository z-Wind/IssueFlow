
// Decision Tree.h : PROJECT_NAME 應用程式的主要標頭檔
//

#pragma once

#include <vector>
using std::vector;

#include "OptionBox.h"

typedef struct Multi_Node
{
	CString phenomenon;
	struct Multi_Node* parent;
	unsigned int layer;
	vector<struct Multi_Node* > option;

	Multi_Node()
	{
		phenomenon = "";
		parent = NULL;
		layer = 0;
		option.clear();
	}

	Multi_Node(CString str, struct Multi_Node* p)
	{
		phenomenon = str;
		parent = p;
		layer = (p == NULL)? 0 : p->layer + 1;
		option.clear();
	}

}multi_node;

typedef struct Binary_Node
{
	CString ask;
	struct Binary_Node* yes;
	struct Binary_Node* no;

	Binary_Node()
	{
		ask = "";
		yes = NULL;
		no = NULL;
	}

	Binary_Node(CString str)
	{
		ask = str;
		yes = NULL;
		no = NULL;
	}

}binary_node;

// CDecisionTree:
// 請參閱實作此類別的 Decision Tree.cpp
//

class CDecisionTree
{
private:
	// Insert Root Node with InputBox
	bool treeInsertRoot(multi_node* &root, multi_node* parent, CString title);
	// Insert Leaf Node with InputBox
	bool treeInsertLeaf(multi_node* &root, CString title);
public:
	CDecisionTree();
	CDecisionTree(CString start);

	multi_node* head;
	multi_node* now;
	bool changed;

	// Create New Root
	void treeCreateNewRoot(multi_node* &root, multi_node* parent, CString valStr);
	// Create New Leaf
	void treeCreateNewLeaf(multi_node* &root, CString valStr);
	// Add another Tree
	void addTree(multi_node* master, multi_node* slave);
	// display Tree
	void displayTree(multi_node* &root,CListBox* m_list);
	// save Data Base
	bool save_DB(CString filePath);
	// load Data Base
	bool load_DB(CString filePath);
	// preorder search & establish
	multi_node* preorder_SE(multi_node* root,CString search,bool &ask);
	// preorder save
	void preorder_save(multi_node* root,CStdioFile* DB);
	// preorder load
	void preorder_load(multi_node* &root,CStdioFile* DB);
	//get exe path
	CString GetFilePath();
	//free memory
	void freeMemory(multi_node* &root);
};