#pragma once

#include "resource.h"

// CInputBox 對話方塊

class CInputBox : public CDialogEx
{
	DECLARE_DYNAMIC(CInputBox)

public:
	CInputBox(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CInputBox();
	virtual BOOL OnInitDialog();

// 對話方塊資料
	enum { IDD = IDD_INPUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

public:
	CString m_input;
	CString title;
};
