
// Com.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComApp:
// �йش����ʵ�֣������ Com.cpp
//

class CComApp : public CWinApp
{
public:
	CComApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

//extern CComApp theApp;

static unsigned int g_ChangeCount;
static unsigned int g_ComData;
extern bool g_NoteWholeJump;
extern bool g_NoteHalfJump;
extern bool g_NoteFourthJump;
extern bool g_NoteEightJump;
extern bool g_NoteSixteenthJump;
extern bool g_NoteThirtySecondJump;
extern bool g_NoteEight2Jump;