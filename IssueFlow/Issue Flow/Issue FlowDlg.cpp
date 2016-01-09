
// Issue FlowDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "Issue FlowDlg.h"
#include "afxdialogex.h"

#include "TreeWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIssueFlowDlg ��ܤ��

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


// CIssueFlowDlg �T���B�z�`��

BOOL CIssueFlowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	ShowControl(true);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CIssueFlowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CIssueFlowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIssueFlowDlg::OnBnClickedJudge()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ShowControl(false);
	m_list.ResetContent();
	tree.displayTree(tree.head,&m_list);
	ShowControl(true);
}

void CIssueFlowDlg::OnBnClickedContjudge()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ShowControl(false);
	CString valStr;
	bool ask = true;

	m_list.GetText(0,valStr);

	if(tree.head == NULL)
	{
		if(::MessageBoxA(NULL,"�L DB�A�O�_�� log �إߡH\r\n" + valStr,"ĵ�i",MB_YESNO) == IDNO)
		{
			ShowControl(true);
			return;
		}
		ask = false;
		tree.treeCreateNewRoot(tree.head, NULL, valStr);
	}


	if(valStr.Compare(tree.head->phenomenon) != 0)
	{
		if(::MessageBoxA(NULL,"�}�Y���@�ˡA�O�_�~��H\r\n" + valStr + "\r\n" + tree.head->phenomenon,"ĵ�i",MB_YESNO) == IDNO)
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
	// TODO: �b���[�J����i���B�z�`���{���X
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
	// TODO: �b���[�J����i���B�z�`���{���X
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
	// TODO: �b���[�J����i���B�z�`���{���X
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
	// TODO: �b���[�J����i���B�z�`���{���X
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if(tree.changed)
	{
		if( ::MessageBoxA(NULL,"DB �O�_�s�ɡH","ask",MB_YESNO) == IDYES )
		{
			OnBnClickedSavedb();
		}
	}
	CDialogEx::OnClose();
}

void CIssueFlowDlg::OnBnClickedPrevious()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ShowControl(false);
	m_list.DeleteString(m_list.GetCount()-1);
	tree.now = tree.now->parent;
	ShowControl(true);

}

void CIssueFlowDlg::OnBnClickedEdittree()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ShowControl(false);

	CTreeWindow treewindow;
	treewindow.tree = &tree;
	treewindow.DoModal();

	ShowControl(true);
}


void CIssueFlowDlg::OnBnClickedAddtree()
{
	// TODO: �b���[�J����i���B�z�`���{���X
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
			if(::MessageBoxA(NULL,"�}�Y���@�ˡA�O�_�~��H\r\n" + oTree.head->phenomenon + "\r\n" + tree.head->phenomenon,"ĵ�i",MB_YESNO) == IDNO)
			{
				ShowControl(true);
				return;
			}
		}
		tree.addTree(tree.head,oTree.head);
	}
	ShowControl(true);
}
