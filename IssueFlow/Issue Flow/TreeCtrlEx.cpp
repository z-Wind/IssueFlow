// TreeCtrlEx.cpp : ��@��
//

#include "stdafx.h"
#include "Issue Flow.h"
#include "TreeCtrlEx.h"

#include "InputBox.h"

#define   DRAG_DELAY   60

// CTreeCtrlEx

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

CTreeCtrlEx::CTreeCtrlEx()
{
	m_pDragImage = NULL;
	m_sCopy = MF_GRAYED;
	m_bDragging = FALSE;
}

CTreeCtrlEx::~CTreeCtrlEx()
{
}

//ON_NOTIFY is used when handling notifications in the parent window of the control
//ON_NOTIFY_REFLECT - when handling them in the control itself.
BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	ON_COMMAND(IDM_INSERT, &CTreeCtrlEx::OnInsert)
	ON_COMMAND(IDM_DELETE, &CTreeCtrlEx::OnDelete)
	ON_COMMAND(IDM_RENAME, &CTreeCtrlEx::OnRename)
	ON_COMMAND(IDM_COPY, &CTreeCtrlEx::OnCopy)
	ON_COMMAND(IDM_PASTE, &CTreeCtrlEx::OnPaste)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CTreeCtrlEx::OnRClick)
	ON_WM_CONTEXTMENU()
//{{AFX_MSG_MAP(CTreeCtrlEx)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_EXPANDALL, &CTreeCtrlEx::OnExpandall)
	ON_COMMAND(IDM_COLLAPSEALL, &CTreeCtrlEx::OnCollapseall)
END_MESSAGE_MAP()



// CTreeCtrlEx �T���B�z�`��

void CTreeCtrlEx::OnInsert()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	CInputBox ph;
	ph.m_input = "";
	ph.title = "�إߤ���";
	while(ph.m_input.IsEmpty())
	{
		if(ph.DoModal() == IDCANCEL)
		{
			return;
		}
	}
	HTREEITEM htItem = GetSelectedItem();
	InsertItem(ph.m_input,htItem,TVI_LAST);
}


void CTreeCtrlEx::OnDelete()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	if(MessageBoxA("Delete �u" + GetItemText(GetSelectedItem()) + "�v","Warning",MB_YESNO) == IDYES)
	{
		DeleteItem(GetSelectedItem());
	}
}


void CTreeCtrlEx::OnRename()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	CInputBox ph;
	ph.m_input = "";
	ph.title = "�إߤ���";
	while(ph.m_input.IsEmpty())
	{
		ph.m_input = GetItemText(GetSelectedItem());
		if(ph.DoModal() == IDCANCEL)
		{
			return;
		}
	}
	
	SetItemText(GetSelectedItem(),ph.m_input);
}


void CTreeCtrlEx::OnCopy()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_hitemCopy = GetSelectedItem();
	m_sCopy = MF_ENABLED;
}

void CTreeCtrlEx::OnPaste()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	HTREEITEM  htiNewTemp = CopyBranch( m_hitemCopy,NULL,TVI_LAST );
	HTREEITEM  htiNew = CopyBranch( htiNewTemp,GetSelectedItem(),TVI_LAST );
	DeleteItem( htiNewTemp );

	expandAll(GetSelectedItem());
	//Expand( GetSelectedItem(),TVE_EXPAND );
}

void CTreeCtrlEx::OnExpandall()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	expandAll(GetSelectedItem());
}

void CTreeCtrlEx::OnCollapseall()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	collapseAll(GetSelectedItem());
}

void CTreeCtrlEx::OnRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �b���[�J����i���B�z�`���{���X
	
	// Send WM_CONTEXTMENU to self
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_hWnd, GetMessagePos());
	// Mark message as handled and suppress default handling
	*pResult = 1;
}

void CTreeCtrlEx::OnContextMenu(CWnd* pWnd, CPoint ptMousePos) 
{
	// TODO: �b���[�J�z���T���B�z�`���{���X
	UINT uFlags ;

	ScreenToClient(&ptMousePos);

	HTREEITEM htItem;

	htItem = HitTest(ptMousePos, &uFlags);
	if(htItem == NULL || !(TVHT_ONITEM & uFlags))
	{
		return;
	}

	CMenu menu;
	CMenu* pPopup;

	SelectItem(htItem);
	
	menu.LoadMenu(IDR_CONTEXT_MENU);
	// the font popup is stored in a resource
	pPopup = menu.GetSubMenu(0);//����Ĥ@�Ӽu�X���A�ҥH�Ĥ@�ӵ�楲�����l���

	pPopup->EnableMenuItem (IDM_PASTE, m_sCopy);
	if(GetSelectedItem() == GetRootItem())
		pPopup->EnableMenuItem (IDM_DELETE, MF_GRAYED);

	ClientToScreen(&ptMousePos);//�����e���Ъ���m�A�H�K�ϱo���i�H���H���� 
	pPopup->TrackPopupMenu( TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this );
}

void CTreeCtrlEx::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	//�p�G�O�L�N�즲�A�h���ާ@
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	//�o��Ω��ʮ���ܪ��Ϲ��C��
	m_pDragImage = CreateDragImageEx( m_hItemDragS );
	if( !m_pDragImage )
		return;

	m_bDragging = true;
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint  pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt );  //"this"�N�즲�ʧ@����b�ӵ��f
	SetCapture();

	m_nScrollTimerID = SetTimer( 2,40,NULL );
}

void CTreeCtrlEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM  hItem;
	UINT       flags;

	//�˴����бӷP�w�ɾ��O�_�s�b,�p�G�s�b�h�R��,�R����A�w��
	if( m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,500,NULL );  //�w�ɬ� 0.8 ��h�۰ʮi�}
	m_HoverPoint = point;

	if( m_bDragging )
	{
		CPoint  pt = point;
		CImageList::DragMove( pt );
		CImageList::DragShowNolock( false );  //�קK���иg�L�ɯd�U���ݪ�����

		//���иg�L�ɰ��G���
		if( (hItem = HitTest(point,&flags)) != NULL )
		{
			SelectDropTarget( hItem );
			m_hItemDragD = hItem;
		}

		//����سQ�즲�쥪��t�ɡA�N���ة�b�ڤU
		CRect  rect;
		GetClientRect( &rect );
		if( point.x < rect.left + 20 )
			m_hItemDragD = NULL;
		CImageList::DragShowNolock( true );
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CTreeCtrlEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if( m_bDragging )
	{
		m_bDragging = FALSE;
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;

		SelectDropTarget( NULL );
		
		if( m_hItemDragS == m_hItemDragD )
		{
			KillTimer( m_nScrollTimerID );
			return;
		}

		Expand( m_hItemDragD,TVE_EXPAND );

		HTREEITEM  htiParent = m_hItemDragD;
		while( (htiParent = GetParentItem(htiParent)) != NULL )
		{
			if( htiParent == m_hItemDragS )
			{
				HTREEITEM  htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
				HTREEITEM  htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
				DeleteItem( htiNewTemp );
				SelectItem( htiNew );
				KillTimer( m_nScrollTimerID );
				return;
			}
		}

		HTREEITEM  htiNew = CopyBranch( m_hItemDragS,m_hItemDragD,TVI_LAST );
		DeleteItem( m_hItemDragS );
		SelectItem( htiNew );
		expandAll(GetSelectedItem());
		KillTimer( m_nScrollTimerID );
	}
}

void CTreeCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//�B�z�L�N�즲
	m_dwDragStart = GetTickCount();
	
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CTreeCtrlEx::OnTimer(UINT nIDEvent) 
{
	//���бӷP�`�I
	if( nIDEvent == m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
		HTREEITEM  trItem = 0;
		UINT  uFlag = 0;
		trItem = HitTest( m_HoverPoint,&uFlag );
		if( trItem && m_bDragging )
		{
			CImageList::DragShowNolock( false );  //�קK���иg�L�ɯd�U���ݪ�����
			SelectItem( trItem );
			Expand( trItem,TVE_EXPAND );
		}
	}
	//�B�z�즲�L�{�����u�ʰ��D
	else if( nIDEvent == m_nScrollTimerID )
	{
		m_TimerTicks++;
		CPoint  pt;
		GetCursorPos( &pt );
		CRect  rect;
		GetClientRect( &rect );
		ClientToScreen( &rect );

		HTREEITEM  hItem = GetFirstVisibleItem();
		
		if( pt.y < rect.top +10 )
		{
			//�V�W�u��
			int  slowscroll = 6 - (rect.top + 10 - pt.y )/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEUP );
				SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
		else if( pt.y > rect.bottom - 10 )
		{
			//�V�U�u��
			int  slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEDOWN );
				int  nCount = GetVisibleCount();
				for( int i=0 ; i<nCount-1 ; i++ )
					hItem = GetNextVisibleItem( hItem );
				if( hItem )
					SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
	}
	else
		CTreeCtrl::OnTimer(nIDEvent);
}

CImageList* CTreeCtrlEx::CreateDragImageEx(HTREEITEM hItem)
{
	if(GetImageList(TVSIL_NORMAL) != NULL)
		return CreateDragImage(hItem);

	CRect rect;
	GetItemRect(hItem, rect, TRUE);
	rect.top = rect.left = 0;

	// Create bitmap
	CClientDC	dc (this);
	CDC 		memDC;	

	if(!memDC.CreateCompatibleDC(&dc))
		return NULL;

	CBitmap bitmap;
	if(!bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()))
		return NULL;

	CBitmap* pOldMemDCBitmap = memDC.SelectObject( &bitmap );
	CFont* pOldFont = memDC.SelectObject(GetFont());

	memDC.FillSolidRect(&rect, RGB(0, 255, 0)); // Here green is used as mask color
	memDC.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	memDC.TextOut(rect.left, rect.top, GetItemText(hItem));

	memDC.SelectObject( pOldFont );
	memDC.SelectObject( pOldMemDCBitmap );

	// Create imagelist
	CImageList* pImageList = new CImageList;
	pImageList->Create(rect.Width(), rect.Height(), 
	 ILC_COLOR | ILC_MASK, 0, 1);
	pImageList->Add(&bitmap, RGB(0, 255, 0)); // Here green is used as mask color

	return pImageList;
}


HTREEITEM CTreeCtrlEx::CopyBranch(HTREEITEM oldItem, HTREEITEM newParent, HTREEITEM iPosition)
{

	HTREEITEM newItem = InsertItem( GetItemText(oldItem), newParent,iPosition);

	SetNewParent(newItem,oldItem);

	return newItem;

}

void CTreeCtrlEx::SetNewParent(HTREEITEM newPosition, HTREEITEM oldPosition)
{

	HTREEITEM oldChild = GetChildItem(oldPosition);

	HTREEITEM newChild;

	while(oldChild)
	{
		newChild = InsertItem( GetItemText(oldChild), newPosition,TVI_LAST );
		SetNewParent(newChild,oldChild);
		oldChild = GetNextItem(oldChild, TVGN_NEXT); 
	}

}

void CTreeCtrlEx::createTree(multi_node* root,HTREEITEM hItem)
{
	if(root == NULL)
	{
		return;
	}
	
	HTREEITEM hSubItem;

	hSubItem = InsertItem(root->phenomenon,hItem);//�K�[�@�Ӥl���I
	for(unsigned int i=0; i<root->option.size(); i++)
	{
		createTree(root->option[i],hSubItem);
	}
}

void CTreeCtrlEx::updateTree(multi_node* &root,HTREEITEM hItem)
{
	if(root == NULL)//head
	{
		tree->treeCreateNewRoot(root,NULL,GetItemText(hItem));
		updateTree(root,hItem);
	}
	else
	{
		HTREEITEM hSubItem;
		unsigned int i = 0;

		hSubItem = GetNextItem(hItem,TVGN_CHILD);
		while( hSubItem != NULL)
		{
			tree->treeCreateNewLeaf(root,GetItemText(hSubItem));
			updateTree(root->option[i],hSubItem);
			i++;
			hSubItem = GetNextSiblingItem(hSubItem);
		}
	}
}

void CTreeCtrlEx::expandAll(HTREEITEM hItem)
{
	Expand(hItem,TVE_EXPAND);
	HTREEITEM hsubItem = GetNextItem(hItem,TVGN_CHILD);
	while (hsubItem != NULL)
	{
		expandAll(hsubItem);
		hsubItem = GetNextSiblingItem(hsubItem);
	} 
}

void CTreeCtrlEx::collapseAll(HTREEITEM hItem)
{
	Expand(hItem,TVE_COLLAPSE);
	HTREEITEM hsubItem = GetNextItem(hItem,TVGN_CHILD);
	while (hsubItem != NULL)
	{
		collapseAll(hsubItem);
		hsubItem = GetNextSiblingItem(hsubItem);
	} 
}