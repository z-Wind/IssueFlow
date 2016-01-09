#pragma once
#include "afxcmn.h"
#include "resource.h"

#include "Decision Tree.h"
#include "TreeCtrlEx.h"


// CTreeWindow 對話方塊

class CTreeWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CTreeWindow)

public:
	CTreeWindow(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CTreeWindow();

// 對話方塊資料
	enum { IDD = IDD_TREEWINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CDecisionTree* tree;
	CTreeCtrlEx m_treeCtrl;
	afx_msg void OnBnClickedOk();
};
