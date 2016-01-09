// InputBox.cpp : 實作檔
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "InputBox.h"
#include "afxdialogex.h"


// CInputBox 對話方塊

IMPLEMENT_DYNAMIC(CInputBox, CDialogEx)

CInputBox::CInputBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputBox::IDD, pParent)
	, m_input(_T(""))
{
}

CInputBox::~CInputBox()
{
}

void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CInputBox, CDialogEx)
END_MESSAGE_MAP()


// CInputBox 訊息處理常式

BOOL CInputBox::OnInitDialog()
{
	CDialog::OnInitDialog();

   // TODO: Add extra initialization here
	CRect Rect_P; 
	CWnd* p = GetParent();
	p->GetWindowRect(&Rect_P);

	CRect Rect1;
	GetWindowRect(&Rect1);

	SetWindowPos(NULL,Rect_P.left,Rect_P.top-Rect1.Height(),Rect1.Width(),Rect1.Height(),SWP_SHOWWINDOW);

	GetDlgItem(IDC_EDIT1)->SetFocus();
	SetWindowText(title);

	return FALSE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}