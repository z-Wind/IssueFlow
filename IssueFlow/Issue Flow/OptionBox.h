#pragma once
#include "afxwin.h"
#include "resource.h"
#include <vector>
using std::vector;

// COpitionBox 對話方塊

class COpitionBox : public CDialogEx
{
	DECLARE_DYNAMIC(COpitionBox)

public:
	COpitionBox(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~COpitionBox();
	virtual BOOL OnInitDialog();

// 對話方塊資料
	enum { IDD = IDD_OPTIONDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	vector<CString> list;
	bool create;
	bool normal;
	int sel;

	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnDblclkList1();
};
