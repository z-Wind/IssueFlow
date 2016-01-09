
// Issue FlowDlg.h : 標頭檔
//

#pragma once
#include "afxwin.h"
#include "Decision Tree.h"


// CIssueFlowDlg 對話方塊
class CIssueFlowDlg : public CDialogEx
{
// 建構
public:
	CIssueFlowDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_ISSUEFLOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
