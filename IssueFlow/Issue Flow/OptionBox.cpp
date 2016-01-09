// OpitionBox.cpp : 實作檔
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "OptionBox.h"
#include "afxdialogex.h"


// COpitionBox 對話方塊

IMPLEMENT_DYNAMIC(COpitionBox, CDialogEx)

COpitionBox::COpitionBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpitionBox::IDD, pParent)
{
	normal = true;
}

COpitionBox::~COpitionBox()
{
}

void COpitionBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(COpitionBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &COpitionBox::OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_LIST1, &COpitionBox::OnLbnDblclkList1)
END_MESSAGE_MAP()


// COpitionBox 訊息處理常式
BOOL COpitionBox::OnInitDialog()
{
	CDialog::OnInitDialog();

   // TODO: Add extra initialization here
	CRect Rect_P; 
	CWnd* p = GetParent();
	p->GetWindowRect(&Rect_P);

	CRect Rect1;
	GetWindowRect(&Rect1);

	SetWindowPos(NULL,Rect_P.left,Rect_P.top-Rect1.Height(),Rect1.Width(),Rect1.Height(),SWP_SHOWWINDOW);

	for(unsigned int i=0; i<list.size(); i++)
	{
		m_list.AddString(list[i]);
	}
	m_list.SetCurSel(0);

	GetDlgItem(IDCANCEL)->ShowWindow(normal);

	return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void COpitionBox::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if((m_list.GetCurSel()-1) == -1)
	{
		create = true;
		sel = m_list.GetCount() -1;
	}
	else
	{
		create = false;
		sel = m_list.GetCurSel()-1;
	}

	CDialogEx::OnOK();
}


void COpitionBox::OnLbnDblclkList1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	OnBnClickedOk();
}
