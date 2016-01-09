
// Decision Tree.cpp : 定義應用程式的類別行為。
//

#include "stdafx.h"
#include "Decision Tree.h"
#include "InputBox.h"

// CDecisionTreeApp 初始設定

CDecisionTree::CDecisionTree()
{
	head = NULL;
	CString path = GetFilePath();
	load_DB(path + "\\DB.bin");
	now = head;
	changed = false;
}

CDecisionTree::CDecisionTree(CString start)
{
	treeCreateNewRoot(head,NULL,start);
	CString path = GetFilePath();
	load_DB(path + "\\DB.bin");
	now = head;
	changed = true;
}

// Create New Root
void CDecisionTree::treeCreateNewRoot(multi_node* &root, multi_node* parent, CString valStr)
{
	root = new multi_node(valStr,parent);
	changed = true;
}

// Create New Leaf
void CDecisionTree::treeCreateNewLeaf(multi_node* &root, CString valStr)
{
	root->option.push_back(new multi_node(valStr,root));
	changed = true;
}

// Insert Leaf Node with InputBox
bool CDecisionTree::treeInsertLeaf(multi_node* &root, CString title)
{
	CInputBox ph;
	ph.m_input = "";
	ph.title = title;
	while(ph.m_input.IsEmpty())
	{
		if(ph.DoModal() == IDCANCEL)
		{
			return false;
		}
	}
	treeCreateNewLeaf(root,ph.m_input);
	return true;
}

// Insert Root Node with InputBox
bool CDecisionTree::treeInsertRoot(multi_node* &root, multi_node* parent, CString title)
{
	CInputBox ph;
	ph.m_input = "";
	ph.title = title;
	while(ph.m_input.IsEmpty())
	{
		if(ph.DoModal() == IDCANCEL)
		{
			return false;
		}
	}
	treeCreateNewRoot(root,parent,ph.m_input);
	return true;
}

// Add another Tree
void CDecisionTree::addTree(multi_node* master, multi_node* slave)
{
	multi_node* node;
	bool ask = false;
	for(unsigned int i = 0; i<slave->option.size(); i++)
	{
		node = preorder_SE(master,slave->option[i]->phenomenon,ask);
		addTree(node,slave->option[i]);
	}
}

// display Tree
void CDecisionTree::displayTree(multi_node* &root,CListBox* m_list)
{
	if(root == NULL)//head
	{
		if(treeInsertRoot(root,NULL,"輸入新的開頭"))
		{
			displayTree(root,m_list);
		}
	}
	else
	{
		now = root;

		m_list->InsertString(m_list->GetCount(),root->phenomenon);
		if(root->option.empty())
		{
			if(treeInsertLeaf(root,"輸入新的分支"))
			{
				displayTree(root->option[0],m_list);
			}
		}
		else
		{
			COpitionBox optionBox;
			optionBox.list.push_back("Create New Phenomenon");
			for(unsigned int i=0; i<root->option.size(); i++)
			{
				optionBox.list.push_back(root->option[i]->phenomenon);
			}
			if( optionBox.DoModal() == IDCANCEL)
			{
				return;
			}
			
			if( optionBox.create )
			{
				if(treeInsertLeaf(root,"輸入新的分支"))
				{
					displayTree(root->option[optionBox.sel],m_list);
				}
			}
			else
			{
				displayTree(root->option[optionBox.sel],m_list);
			}
		}
	}
}

// save Data Base
bool CDecisionTree::save_DB(CString filePath)
{
	CStdioFile DB;
	if(DB.Open(filePath,CFile::modeCreate|CFile::modeWrite))
	{
		preorder_save(head,&DB);

		DB.Close();
		changed = false;
		return true;
	}
	else
	{
		return false;
	}
}

// load Data Base
bool CDecisionTree::load_DB(CString filePath)
{
	CStdioFile DB;
	if(DB.Open(filePath,CFile::modeRead))
	{
		freeMemory(head);
		preorder_load(head,&DB);

		DB.Close();
		changed = false;
		return true;
	}
	else
	{
		return false;
	}
}

// preorder search & establish
multi_node* CDecisionTree::preorder_SE(multi_node* root,CString search, bool &ask)
{
	unsigned int i;
	multi_node* sel = NULL;

	for(i=0; i<root->option.size(); i++)
	{
		if(root->option[i]->phenomenon == search)
		{
			sel = root->option[i];
			break;
		}
	}

	if(i == root->option.size())
	{
		if(ask)
		{
			if(::MessageBoxA(NULL,"找不到對應分支，是否建立？\r\n" + search,"警告",MB_YESNO) == IDNO)
			{
				return sel;
			}
			else
			{
				ask = false;
			}
		}
		if(root->option.size()>0)
		{
			COpitionBox optionBox;
			optionBox.normal = false;
			optionBox.list.push_back("輸入的資料：\"" + search + "\"，以下為已內建資料");
			for(unsigned int i=0; i<root->option.size(); i++)
			{
				optionBox.list.push_back(root->option[i]->phenomenon);
			}
			if( optionBox.DoModal() == IDCANCEL)
			{
				treeCreateNewLeaf(root,search);
				sel = root->option[root->option.size()-1];
			}
			else
			{
				if(optionBox.create)
				{
					treeCreateNewLeaf(root,search);
					sel = root->option[root->option.size()-1];
				}
				else
				{
					sel = root->option[optionBox.sel];
				}
			}
		}
		else
		{
			treeCreateNewLeaf(root,search);
			sel = root->option[root->option.size()-1];	
		}

		return sel;
	}
	else
	{
		return sel;
	}
}

// preorder save
void CDecisionTree::preorder_save(multi_node* root,CStdioFile* DB)
{
	CString valStr;
	valStr = root->phenomenon + "\n";
	DB->WriteString(valStr);

	if(!root->option.size() == 0)
	{
		for(unsigned int i=0;i<root->option.size();i++)
		{
			preorder_save(root->option[i],DB);
		}
		valStr = "NULL\n";
		DB->WriteString(valStr);
	}
	else
	{
		valStr = "NULL\n";
		DB->WriteString(valStr);
	}
}

// preorder load
void CDecisionTree::preorder_load(multi_node* &root,CStdioFile* DB)
{	
	CString valStr;
	BOOL read = DB->ReadString(valStr);

	if(root == NULL && read == TRUE)//head
	{
		treeCreateNewRoot(root,NULL,valStr);
		preorder_load(root,DB);
	}
	else
	{
		while(valStr.Compare("NULL") != 0 && read == TRUE)
		{
			treeCreateNewLeaf(root,valStr);
			preorder_load(root->option[root->option.size()-1],DB);
			read = DB->ReadString(valStr);
		}
	}
}

//free memory
void CDecisionTree::freeMemory(multi_node* &root)
{
	if(root == NULL)
	{
		return;
	}
	for(unsigned int i=0;i<root->option.size();i++)
	{
		freeMemory(root->option[i]);
	}
	root->option.clear();
	delete root;
	root = NULL;
}

//get exe path
CString CDecisionTree::GetFilePath() 
{ 
    CString  strdir,tmpdir; 
	GetModuleFileName(NULL,tmpdir.GetBuffer(_MAX_PATH),_MAX_PATH); 
	tmpdir.ReleaseBuffer();
    strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));
    return strdir; 
} 