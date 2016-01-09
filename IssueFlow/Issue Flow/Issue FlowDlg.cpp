
// Issue FlowDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "Issue FlowDlg.h"
#include "afxdialogex.h"

#include "TreeWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIssueFlowDlg 對話方塊

CIssueFlowDlg::CIssueFlowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIssueFlowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIssueFlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CIssueFlowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_JUDGE, &CIssueFlowDlg::OnBnClickedJudge)
	ON_BN_CLICKED(IDC_SAVELOG, &CIssueFlowDlg::OnBnClickedSavelog)
	ON_BN_CLICKED(IDC_SAVEDB, &CIssueFlowDlg::OnBnClickedSavedb)
	ON_BN_CLICKED(IDC_LOADDB, &CIssueFlowDlg::OnBnClickedLoaddb)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_EDITTREE, &CIssueFlowDlg::OnBnClickedEdittree)
	ON_BN_CLICKED(IDC_CONTJUDGE, &CIssueFlowDlg::OnBnClickedContjudge)
	ON_BN_CLICKED(IDC_LOADLOG, &CIssueFlowDlg::OnBnClickedLoadlog)
	ON_BN_CLICKED(IDC_PREVIOUS, &CIssueFlowDlg::OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_ADDTREE, &CIssueFlowDlg::OnBnClickedAddtree)
END_MESSAGE_MAP()


// CIssueFlowDlg 訊息處理常式

BOOL CIssueFlowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	ShowControl(true);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CIssueFlowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CIssueFlowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIssueFlowDlg::OnBnClickedJudge()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);
	m_list.ResetContent();
	tree.displayTree(tree.head,&m_list);
	ShowControl(true);
}

void CIssueFlowDlg::OnBnClickedContjudge()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);
	CString valStr;
	bool ask = true;

	m_list.GetText(0,valStr);

	if(tree.head == NULL)
	{
		if(::MessageBoxA(NULL,"無 DB，是否依 log 建立？\r\n" + valStr,"警告",MB_YESNO) == IDNO)
		{
			ShowControl(true);
			return;
		}
		ask = false;
		tree.treeCreateNewRoot(tree.head, NULL, valStr);
	}


	if(valStr.Compare(tree.head->phenomenon) != 0)
	{
		if(::MessageBoxA(NULL,"開頭不一樣，是否繼續？\r\n" + valStr + "\r\n" + tree.head->phenomenon,"警告",MB_YESNO) == IDNO)
		{
			ShowControl(true);
			return;
		}
		else
		{
			m_list.DeleteString(0);
			m_list.InsertString(0,tree.head->phenomenon);
		}
	}

	multi_node* sel = tree.head;
	int i;

	for(i=1; i<m_list.GetCount(); i++)
	{
		m_list.GetText(i,valStr);
		if((sel=tree.preorder_SE(sel,valStr,ask)) == NULL)
		{
			break;
		}
		m_list.DeleteString(i);
		m_list.InsertString(i,sel->phenomenon);
	}

	if(i == m_list.GetCount())
	{
		m_list.DeleteString(m_list.GetCount()-1);
		tree.displayTree(sel,&m_list);
	}

	ShowControl(true);
}

void CIssueFlowDlg::OnBnClickedSavelog()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);

	CFileDialog file_path(false,"log","Flow_" + tree.head->phenomenon,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,_T("log|*.log*|All Files(*.*)|*||"));
	CString path = tree.GetFilePath();
	file_path.m_ofn.lpstrInitialDir = path;
    if(file_path.DoModal() == IDOK)
	{
		CStdioFile log;
		CString valStr;

		log.Open(file_path.GetFileName(),CFile::modeCreate|CFile::modeWrite);

		for(int i=0;i<m_list.GetCount();i++)
		{
			m_list.GetText(i,valStr);
			valStr += "\n";
			log.WriteString(valStr);
		}
		log.Close();
	}
	ShowControl(true);
}

void CIssueFlowDlg::OnBnClickedLoadlog()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);

	CFileDialog file_path(true,"log","Flow",OFN_HIDEREADONLY|OFN_CREATEPROMPT,_T("log|*.log*|All Files(*.*)|*||"));
	CString path = tree.GetFilePath();
	file_path.m_ofn.lpstrInitialDir = path;
    if(file_path.DoModal() == IDOK)
	{
		m_list.ResetContent();
		CStdioFile log;
		CString valStr;

		log.Open(file_path.GetFileName(),CFile::modeRead);

		while( log.ReadString(valStr) == TRUE)
		{
			m_list.AddString(valStr);
		}

		log.Close();
	}
	ShowControl(true);
}


void CIssueFlowDlg::OnBnClickedSavedb()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);
	CFileDialog file_path(false,"bin","DB_" + tree.head->phenomenon,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,_T("bin|*.bin*|All Files(*.*)|*||"));
	CString path = tree.GetFilePath();
	file_path.m_ofn.lpstrInitialDir = path;
    if(file_path.DoModal() == IDOK)
	{
		tree.save_DB(file_path.GetPathName());
	}
	/*tree.save_DB(tree.GetFilePath() + "\\DB.bin");*/
	ShowControl(true);
}


void CIssueFlowDlg::OnBnClickedLoaddb()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);

	CFileDialog file_path(true,"bin","DB",OFN_HIDEREADONLY|OFN_CREATEPROMPT,_T("bin|*.bin*|All Files(*.*)|*||"));
	CString path = tree.GetFilePath();
	file_path.m_ofn.lpstrInitialDir = path;
    if(file_path.DoModal() == IDOK)
	{
		tree.load_DB(file_path.GetPathName());
	}
	ShowControl(true);
}

// enable control like buttons
void CIssueFlowDlg::ShowControl(bool show)
{
	GetDlgItem(IDC_JUDGE)->EnableWindow(show);
	GetDlgItem(IDC_CONTJUDGE)->EnableWindow(show && m_list.GetCount()>0);
	GetDlgItem(IDC_SAVEDB)->EnableWindow(show && tree.head != NULL);
	GetDlgItem(IDC_LOADDB)->EnableWindow(show);
	GetDlgItem(IDC_SAVELOG)->EnableWindow(show && m_list.GetCount()>0);
	GetDlgItem(IDC_LOADLOG)->EnableWindow(show);
	GetDlgItem(IDC_PREVIOUS)->EnableWindow(show && m_list.GetCount()>1);
	GetDlgItem(IDC_ADDTREE)->EnableWindow(show && tree.head != NULL);
	GetDlgItem(IDC_EDITTREE)->EnableWindow(show && tree.head != NULL);
}

void CIssueFlowDlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(tree.changed)
	{
		if( ::MessageBoxA(NULL,"DB 是否存檔？","ask",MB_YESNO) == IDYES )
		{
			OnBnClickedSavedb();
		}
	}
	CDialogEx::OnClose();
}

void CIssueFlowDlg::OnBnClickedPrevious()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);
	m_list.DeleteString(m_list.GetCount()-1);
	tree.now = tree.now->parent;
	ShowControl(true);

}

void CIssueFlowDlg::OnBnClickedEdittree()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);

	CTreeWindow treewindow;
	treewindow.tree = &tree;
	treewindow.DoModal();

	ShowControl(true);
}


void CIssueFlowDlg::OnBnClickedAddtree()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	ShowControl(false);

	CDecisionTree oTree;

	CFileDialog file_path(true,"bin","DB",OFN_HIDEREADONLY|OFN_CREATEPROMPT,_T("bin|*.bin*|All Files(*.*)|*||"));
	CString path = tree.GetFilePath();
	file_path.m_ofn.lpstrInitialDir = path;
    if(file_path.DoModal() == IDOK)
	{
		oTree.load_DB(file_path.GetPathName());

		if(oTree.head->phenomenon.Compare(tree.head->phenomenon) != 0)
		{
			if(::MessageBoxA(NULL,"開頭不一樣，是否繼續？\r\n" + oTree.head->phenomenon + "\r\n" + tree.head->phenomenon,"警告",MB_YESNO) == IDNO)
			{
				ShowControl(true);
				return;
			}
		}
		tree.addTree(tree.head,oTree.head);
	}
	ShowControl(true);
}
