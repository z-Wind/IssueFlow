#pragma once
#include "afxcmn.h"
#include "resource.h"

#include "Decision Tree.h"
#include "TreeCtrlEx.h"


// CTreeWindow ��ܤ��

class CTreeWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CTreeWindow)

public:
	CTreeWindow(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CTreeWindow();

// ��ܤ�����
	enum { IDD = IDD_TREEWINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CDecisionTree* tree;
	CTreeCtrlEx m_treeCtrl;
	afx_msg void OnBnClickedOk();
};
