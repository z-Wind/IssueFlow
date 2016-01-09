
// Issue FlowDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"
#include "Decision Tree.h"


// CIssueFlowDlg ��ܤ��
class CIssueFlowDlg : public CDialogEx
{
// �غc
public:
	CIssueFlowDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_ISSUEFLOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// enable control like buttons
	void ShowControl(bool show);
public:
	CDecisionTree tree;
	CListBox m_list;

	afx_msg void OnBnClickedJudge();
	afx_msg void OnBnClickedSavelog();
	afx_msg void OnBnClickedSavedb();
	afx_msg void OnBnClickedLoaddb();
	afx_msg void OnClose();
	afx_msg void OnBnClickedEdittree();
	afx_msg void OnBnClickedContjudge();
	afx_msg void OnBnClickedLoadlog();
	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedAddtree();
};
