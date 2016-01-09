#pragma once

#include "Decision Tree.h"

// CTreeCtrlEx

class CTreeCtrlEx : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlEx)
private:
	int			m_sCopy;
	HTREEITEM	m_hitemCopy;

	HTREEITEM CopyBranch(HTREEITEM oldItem, HTREEITEM newParent, HTREEITEM iPosition);
	void SetNewParent(HTREEITEM newPosition, HTREEITEM oldPosition);

	// for drag & drop
	UINT          m_TimerTicks;      //�B�z�u�ʪ��w�ɾ��Ҹg�L���ɶ�
	UINT          m_nScrollTimerID;  //�B�z�u�ʪ��w�ɾ�
	CPoint        m_HoverPoint;      //���Ц�m
	UINT          m_nHoverTimerID;   //���бӷP�w�ɾ�
	DWORD         m_dwDragStart;     //���U���Х��䨺�@�誺�ɶ�
	BOOL          m_bDragging;       //���ѬO�_���b��ʹL�{��
	CImageList*   m_pDragImage;      //��ʮ���ܪ��Ϲ��C��
	HTREEITEM     m_hItemDragS;      //�Q��ʪ�����
	HTREEITEM     m_hItemDragD;      //������ʪ�����
	CImageList* CreateDragImageEx(HTREEITEM hItem);
	//{{AFX_MSG(CTreeCtrlEx)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

public:
	CTreeCtrlEx();
	virtual ~CTreeCtrlEx();

	void createTree(multi_node* root,HTREEITEM hItem);
	void updateTree(multi_node* &root,HTREEITEM hItem);
	void expandAll(HTREEITEM hItem);
	void collapseAll(HTREEITEM hItem);

protected:
	DECLARE_MESSAGE_MAP()

public:
	CDecisionTree* tree;

	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnRename();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnExpandall();
	afx_msg void OnCollapseall();
	afx_msg void OnRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint ptMousePos);	
};


