// TreeWindow.cpp : ��@��
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "TreeWindow.h"
#include "afxdialogex.h"

#include "resource.h"

// CTreeWindow ��ܤ��

IMPLEMENT_DYNAMIC(CTreeWindow, CDialogEx)

CTreeWindow::CTreeWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTreeWindow::IDD, pParent)
{

}

CTreeWindow::~CTreeWindow()
{
}

void CTreeWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
}


BEGIN_MESSAGE_MAP(CTreeWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTreeWindow::OnBnClickedOk)
END_MESSAGE_MAP()


// CTreeWindow �T���B�z�`��
BOOL CTreeWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	
	HTREEITEM hItem = TVI_ROOT;
	m_treeCtrl.createTree(tree->head,hItem);
	m_treeCtrl.expandAll(m_treeCtrl.GetRootItem());
	m_treeCtrl.Select(m_treeCtrl.GetRootItem(),TVGN_FIRSTVISIBLE);
	m_treeCtrl.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTreeWindow::OnBnClickedOk()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	tree->freeMemory(tree->head);
	HTREEITEM hItem = m_treeCtrl.GetRootItem( );//�o��ڵ��I�C 
	m_treeCtrl.tree = tree;
	m_treeCtrl.updateTree(tree->head,hItem);

	CDialogEx::OnOK();
}