#pragma once
#include "afxwin.h"
#include "resource.h"
#include <vector>
using std::vector;

// COpitionBox ��ܤ��

class COpitionBox : public CDialogEx
{
	DECLARE_DYNAMIC(COpitionBox)

public:
	COpitionBox(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~COpitionBox();
	virtual BOOL OnInitDialog();

// ��ܤ�����
	enum { IDD = IDD_OPTIONDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

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
