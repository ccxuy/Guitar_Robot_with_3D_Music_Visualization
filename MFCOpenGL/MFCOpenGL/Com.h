
// Com.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CComApp:
// 有关此类的实现，请参阅 Com.cpp
//

class CComApp : public CWinApp
{
public:
	CComApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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