
// MFCOpenGL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCOpenGLApp:
// �йش����ʵ�֣������ MFCOpenGL.cpp
//

class CMFCOpenGLApp : public CWinApp
{
public:
	CMFCOpenGLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

//extern CMFCOpenGLApp theApp;