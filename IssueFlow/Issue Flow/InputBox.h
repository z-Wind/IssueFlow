#pragma once

#include "resource.h"

// CInputBox ��ܤ��

class CInputBox : public CDialogEx
{
	DECLARE_DYNAMIC(CInputBox)

public:
	CInputBox(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CInputBox();
	virtual BOOL OnInitDialog();

// ��ܤ�����
	enum { IDD = IDD_INPUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

public:
	CString m_input;
	CString title;
};
