
// Issue Flow.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CIssueFlowApp:
// �аѾ\��@�����O�� Issue Flow.cpp
//

class CIssueFlowApp : public CWinApp
{
public:
	CIssueFlowApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CIssueFlowApp theApp;