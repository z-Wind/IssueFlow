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
	UINT          m_TimerTicks;      //處理滾動的定時器所經過的時間
	UINT          m_nScrollTimerID;  //處理滾動的定時器
	CPoint        m_HoverPoint;      //鼠標位置
	UINT          m_nHoverTimerID;   //鼠標敏感定時器
	DWORD         m_dwDragStart;     //按下鼠標左鍵那一刻的時間
	BOOL          m_bDragging;       //標識是否正在拖動過程中
	CImageList*   m_pDragImage;      //拖動時顯示的圖像列表
	HTREEITEM     m_hItemDragS;      //被拖動的標籤
	HTREEITEM     m_hItemDragD;      //接受拖動的標籤
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


