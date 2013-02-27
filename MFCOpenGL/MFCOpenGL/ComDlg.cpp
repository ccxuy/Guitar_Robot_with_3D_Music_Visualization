
// ComDlg.cpp : 实现文件
//

#include <iostream>
#include <fstream>
#include <time.h> 
using namespace std;


#include "stdafx.h"
#include "Com.h"
#include "ComDlg.h"
#include "afxdialogex.h"

#include   <stdio.h> 
#include   <dos.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//extern bool g_NoteEight2Jump; volatile
bool g_NoteWholeJump = false;
bool g_NoteHalfJump = false;
bool g_NoteFourthJump = false;
bool g_NoteEightJump = false;
bool g_NoteSixteenthJump = false;
bool g_NoteThirtySecondJump = false;
bool g_NoteEight2Jump = false;

CButton m_button2;

CByteArray hexdata;
// CComDlg 对话框

CString hexarray_S[10],m_sendDD;
		CByteArray senda;
		char* hexarray_S2[10];
		//int flag = 0;
		BYTE m_sendD[10];
		BYTE m_sendD1[10];
		BYTE m_sendD2[1][3][10];//m_sendD2[String][Fret][Value]
		BYTE m_sendD3[3][12][7]; //m_sendD3[String][Fret][Value]
		BYTE m_sendClose[3][3][10];
		BYTE m_sendCloseAll[10];
		BYTE m_sendCloseAll2[7];
		CByteArray arrayA;
		CByteArray arrayC; //For test
		CByteArray arrayD; //关闭串口

		boolean flag1 = false;  //标志1弦开或关
		boolean flag2 = false;  //标志2弦开或关
		boolean flag3 = false;  //标志3弦开或关

CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComDlg::IDD, pParent)
	
	, m_rdata(_T(""))
	
	//, m_send_data(0)
	, m_send(_T(""))
	, m_port(1)
	, m_band(4800)
	, m_port1(4)
    , m_band1(9600)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_com);

	DDX_Text(pDX, IDC_EDIT2, m_rdata);

	DDX_Control(pDX, IDC_EDIT2, m_show_data);
	//DDX_Text(pDX, IDC_EDIT4, m_send_data);
	//DDX_Text(pDX, IDC_EDIT4, m_send);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxShort(pDX, m_port, 0, 30);
	DDX_Text(pDX, IDC_EDIT3, m_band);
	//DDX_Text(pDX, IDC_EDIT5, m_band);
	//DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	//DDX_Control(pDX, IDC_COMBO2, m_combox);
	DDX_Control(pDX, IDC_MSCOMM2, m_com1);
	DDX_Text(pDX, IDC_EDIT5, m_band1);
	DDX_Text(pDX, IDC_EDIT4, m_port1);
}

BEGIN_MESSAGE_MAP(CComDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CComDlg::OnBnClickedButton2)
//	ON_WM_CREATE()
//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
ON_BN_CLICKED(IDC_BUTTON3, &CComDlg::OnBnClickedButton3)
//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
//ON_BN_CLICKED(IDC_BUTTON1, &CComDlg::OnBnClickedButton1)
ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
ON_EN_CHANGE(IDC_EDIT3, &CComDlg::OnEnChangeEdit3)
ON_EN_CHANGE(IDC_EDIT2, &CComDlg::OnEnChangeEdit2)
//ON_EN_CHANGE(IDC_EDIT5, &CComDlg::OnEnChangeEdit5)
ON_COMMAND(IDC_MSCOMM2, &CComDlg::OnMscomm2)
ON_EN_CHANGE(IDC_EDIT4, &CComDlg::OnEnChangeEdit4)
ON_EN_CHANGE(IDC_EDIT5, &CComDlg::OnEnChangeEdit5)
ON_BN_CLICKED(IDC_BUTTON6, &CComDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CComDlg 消息处理程序

BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//CBitmap   m_Nextmap;
	
	//m_Nextmap.LoadBitmap(IDB_BITMAP3);
	//HBITMAP   hBitmap   =   (HBITMAP)   m_Nextmap.GetSafeHandle(); 
   // m_button2.SetBitmap(hBitmap); 
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
CString m_band0;
CString m_bandT;
UpdateData(TRUE);
m_band0.Format(_T("%d,n,8,1"),m_band);
m_bandT.Format(_T("%d,n,8,1"),m_band1);

	if(!m_com.get_PortOpen())
	{

		m_com.put_Settings(m_band0);
		m_com1.put_Settings(m_bandT);

		m_com.put_CommPort(m_port);
	    m_com1.put_CommPort(m_port1);

		m_com.put_PortOpen(TRUE);  //打开串口
		m_com1.put_PortOpen(TRUE);

		//m_com.put_RThreshold(11);
        m_button2.SetWindowText(_T("关闭串口"));
		//m_com.put_RThreshold(11);
		//m_com.put_InputLen(10);
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP1)));
		//UpdateData(FALSE);
	}
	else
	{
		m_com.put_PortOpen(FALSE);//关闭串口
		m_com1.put_PortOpen(FALSE);
		m_button2.SetWindowText(_T("打开串口"));
		//m_com.put_InputLen(10);
		//m_com.put_RThreshold(11);
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP2)));
	
	}
}


//int CComDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}
BEGIN_EVENTSINK_MAP(CComDlg, CDialogEx)
	ON_EVENT(CComDlg, IDC_MSCOMM1, 1, CComDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CComDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	UpdateData(true);
	//VARIANT variant_inp;
	COleVariant   myVar; 
	COleSafeArray safearray_inp;
	long len,k;
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.
	//char rxdata[10];
	CString strtemp;//
	if(m_com.get_CommEvent()==2) //事件值为2表示接收缓冲区内有字符
	{

		myVar.Attach(m_com.get_Input());
		//variant_inp=m_com.get_Input(); //读缓冲区
		safearray_inp=myVar; //VARIANT型变量转换为ColeSafeArray型变量
	    len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		//len=2;
		//m_com.put_RThreshold(8);
		for(k=0;k <len;k++){
			safearray_inp.GetElement(&k,&rxdata[k]); //转换为BYTE型数组
		   for(k=0;k <len;k++)  //将数组转换为Cstring型变量
		   { 
			   BYTE bt= 0xCC; //字符型
			   strtemp.Format(_T("%02x"),bt);//将字符送入临时变量strtemp存放
			   //String2Hex(strtemp,hexdata);
			//m_strRXData+=strtemp; //加入接收编辑框对应字符串

		}
	}
	UpdateData(TRUE); //更新编辑框内容 
	m_rdata+=" ";
	m_rdata += strtemp;
	UpdateData(FALSE);
	m_show_data.LineScroll(m_show_data.GetLineCount());

	


	}


}


//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CComDlg::OnBnClickedButton3()
{
		FILE *stream;
		char *context = NULL;
	    errno_t err;;
		err = fopen_s(&stream,"C:\\result.txt","r+");
		
		if(err)
        {
           printf("Error!The txt file does not exit!\n");
		   exit(0);
        }
		
		static char oneLine[2048];
	    static char deltaTime[10];
	    static char string[10];
	    static char fret[10];
		static char note[10];

		int stringI,fretI,deltaTimeI, sLoop,noteTT;
		
		
		arrayA.SetSize(20);
		arrayC.SetSize(20);
        arrayD.SetSize(20);


		//16 继电器吸合
		//1吸合
		m_sendD2[0][0][0]=0xCC;//Header1,Defined by producer
		m_sendD2[0][0][1]=0xDD;//Header2
		m_sendD2[0][0][2]=0xA1;//Write/Read,Defined by producer
		m_sendD2[0][0][3]=0x00;//Address,to verify the different version of product,defined by producer
		m_sendD2[0][0][4]=0xFF;//Data1//controls channel 9~16
		m_sendD2[0][0][5]=0xFF;//Data2//controls channel 1~8
		m_sendD2[0][0][6]=0x00;//Select1//Defined which operation will be execute(channel 9~16)
		m_sendD2[0][0][7]=0x01;//Select2//Defined which operation will be execute(channel 1~8)
		m_sendD2[0][0][8]=0xA0;//CHS1,Add from [][][2]~[][][7]
		m_sendD2[0][0][9]=0x40;//CHS2,Add from [][][2]~[][][8]
	    //2 吸合
		m_sendD2[0][1][0]=0xCC;
		m_sendD2[0][1][1]=0xDD;
		m_sendD2[0][1][2]=0xA1;
		m_sendD2[0][1][3]=0x00;
		m_sendD2[0][1][4]=0xFF;
		m_sendD2[0][1][5]=0xFF;
		m_sendD2[0][1][6]=0x00;
		m_sendD2[0][1][7]=0x02;
		m_sendD2[0][1][8]=0xA1;
		m_sendD2[0][1][9]=0x42;

		// 3吸合
		
		m_sendD2[0][2][0]=0xCC;//Header1,Defined by producer
		m_sendD2[0][2][1]=0xDD;//Header2
		m_sendD2[0][2][2]=0xA1;//Write/Read,Defined by producer
		m_sendD2[0][2][3]=0x00;//Address,to verify the different version of product,defined by producer
		m_sendD2[0][2][4]=0xFF;//Data1//controls channel 9~16
		m_sendD2[0][2][5]=0xFF;//Data2//controls channel 1~8
		m_sendD2[0][2][6]=0x00;//Select1//Defined which operation will be execute(channel 9~16)
		m_sendD2[0][2][7]=0x04;//Select2//Defined which operation will be execute(channel 1~8)
		m_sendD2[0][2][8]=0xA3;//CHS1,Add from [][][2]~[][][7]
		m_sendD2[0][2][9]=0x46;//CHS2,Add from [][][2]~[][][8]
		
		//关闭1,2,3弦
		m_sendCloseAll[0]=0xCC;
		m_sendCloseAll[1]=0xDD;
		m_sendCloseAll[2]=0xA1;
		m_sendCloseAll[3]=0x00;
		m_sendCloseAll[4]=0xFF;
		m_sendCloseAll[5]=0xF0;
		m_sendCloseAll[6]=0x00;
		m_sendCloseAll[7]=0x07;
		m_sendCloseAll[8]=0x97;
		m_sendCloseAll[9]=0x2E;

		//关闭1弦;2,3亮
		m_sendClose[0][0][0]=0xCC;
		m_sendClose[0][0][1]=0xDD;
		m_sendClose[0][0][2]=0xA1;
		m_sendClose[0][0][3]=0x00;
		m_sendClose[0][0][4]=0xFF;
		m_sendClose[0][0][5]=0xFE;
		m_sendClose[0][0][6]=0x00;
		m_sendClose[0][0][7]=0x07;
		m_sendClose[0][0][8]=0xA5;
		m_sendClose[0][0][9]=0x4A;

		//关闭1,2;3亮
		m_sendClose[0][1][0]=0xCC;
		m_sendClose[0][1][1]=0xDD;
		m_sendClose[0][1][2]=0xA1;
		m_sendClose[0][1][3]=0x00;
		m_sendClose[0][1][4]=0xFF;
		m_sendClose[0][1][5]=0xFC;
		m_sendClose[0][1][6]=0x00;
		m_sendClose[0][1][7]=0x07;
		m_sendClose[0][1][8]=0xA3;
		m_sendClose[0][1][9]=0x46;

	    //关闭1,3;2亮
		m_sendClose[0][2][0]=0xCC;
		m_sendClose[0][2][1]=0xDD;
		m_sendClose[0][2][2]=0xA1;
		m_sendClose[0][2][3]=0x00;
		m_sendClose[0][2][4]=0xFF;
		m_sendClose[0][2][5]=0xFA;
		m_sendClose[0][2][6]=0x00;
		m_sendClose[0][2][7]=0x07;
		m_sendClose[0][2][8]=0xA1;
		m_sendClose[0][2][9]=0x42;

		//关闭2弦;1,3亮
		m_sendClose[1][0][0]=0xCC;
		m_sendClose[1][0][1]=0xDD;
		m_sendClose[1][0][2]=0xA1;
		m_sendClose[1][0][3]=0x00;
		m_sendClose[1][0][4]=0xFF;
		m_sendClose[1][0][5]=0xFD;
		m_sendClose[1][0][6]=0x00;
		m_sendClose[1][0][7]=0x07;
		m_sendClose[1][0][8]=0xA4;
		m_sendClose[1][0][9]=0x48;

		//关闭2,3弦;1亮
		m_sendClose[1][1][0]=0xCC;
		m_sendClose[1][1][1]=0xDD;
		m_sendClose[1][1][2]=0xA1;
		m_sendClose[1][1][3]=0x00;
		m_sendClose[1][1][4]=0xFF;
		m_sendClose[1][1][5]=0xF9;
		m_sendClose[1][1][6]=0x00;
		m_sendClose[1][1][7]=0x07;
		m_sendClose[1][1][8]=0xA0;
		m_sendClose[1][1][9]=0x40;


		//关闭3弦;1,2亮
		m_sendClose[2][0][0]=0xCC;
		m_sendClose[2][0][1]=0xDD;
		m_sendClose[2][0][2]=0xA1;
		m_sendClose[2][0][3]=0x00;
		m_sendClose[2][0][4]=0xFF;
		m_sendClose[2][0][5]=0xFB;
		m_sendClose[2][0][6]=0x00;
		m_sendClose[2][0][7]=0x07;
		m_sendClose[2][0][8]=0xA2;
		m_sendClose[2][0][9]=0x44;

		m_sendCloseAll2[0]=0x10;
		m_sendCloseAll2[1]=0x00;
		m_sendCloseAll2[2]=0xFF;
		m_sendCloseAll2[3]=0xFF;
		m_sendCloseAll2[4]=0xFF;
		m_sendCloseAll2[5]=0xFF;
		m_sendCloseAll2[6]=0x50;

		// 32路继电器板吸合
		// 1吸合  1 弦
		m_sendD3[0][0][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][0][1]=0x00;//Header2
		m_sendD3[0][0][2]=0xFE;//Write/Read,Defined by producer
		m_sendD3[0][0][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][0][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][0][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][0][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)

		// 2吸合
		m_sendD3[0][1][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][1][1]=0x00;//Header2
		m_sendD3[0][1][2]=0xFD;//Write/Read,Defined by producer
		m_sendD3[0][1][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][1][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][1][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][1][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)

		// 3吸合
		m_sendD3[0][2][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][2][1]=0x00;//Header2
		m_sendD3[0][2][2]=0xFB;//Write/Read,Defined by producer
		m_sendD3[0][2][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][2][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][2][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][2][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)
		// 4 吸合
		m_sendD3[0][3][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][3][1]=0x00;//Header2
		m_sendD3[0][3][2]=0xF7;//Write/Read,Defined by producer
		m_sendD3[0][3][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][3][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][3][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][3][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)
		//5 吸合
		m_sendD3[0][4][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][4][1]=0x00;//Header2
		m_sendD3[0][4][2]=0xEF;//Write/Read,Defined by producer
		m_sendD3[0][4][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][4][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][4][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][4][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)
		//6 吸合
		m_sendD3[0][5][0]=0x10;//Header1,Defined by producer
		m_sendD3[0][5][1]=0x00;//Header2
		m_sendD3[0][5][2]=0xDF;//Write/Read,Defined by producer
		m_sendD3[0][5][3]=0xFF;//Address,to verify the different version of product,defined by producer
		m_sendD3[0][5][4]=0xFF;//Data1//controls channel 9~16
		m_sendD3[0][5][5]=0xFF;//Data2//controls channel 1~8
		m_sendD3[0][5][6]=0x50;//Select1//Defined which operation will be execute(channel 9~16)
		// 7 吸合
		m_sendD3[0][6][0]=0x10; // the command
		m_sendD3[0][6][1]=0x00; // expand of address
		m_sendD3[0][6][2]=0xBF; // data D0
		m_sendD3[0][6][3]=0xFF; // D1
		m_sendD3[0][6][4]=0xFF; // D2
		m_sendD3[0][6][5]=0xFF; // D3
		m_sendD3[0][6][6]=0x50; // the end of command

		// 8 吸合
		m_sendD3[0][7][0]=0x10; // the command
		m_sendD3[0][7][1]=0x00; // expand of address
		m_sendD3[0][7][2]=0x7F; // data D0
		m_sendD3[0][7][3]=0xFF; // D1
		m_sendD3[0][7][4]=0xFF; // D2
		m_sendD3[0][7][5]=0xFF; // D3
		m_sendD3[0][7][6]=0x50; // the end of command


		// 9 吸合
		m_sendD3[0][8][0]=0x10; // the command
		m_sendD3[0][8][1]=0x00; // expand of address
		m_sendD3[0][8][2]=0xFF; // data D0
		m_sendD3[0][8][3]=0xFE; // D1
		m_sendD3[0][8][4]=0xFF; // D2
		m_sendD3[0][8][5]=0xFF; // D3
		m_sendD3[0][8][6]=0x50; // the end of command

		
		// 10 吸合
		m_sendD3[0][9][0]=0x10; // the command
		m_sendD3[0][9][1]=0x00; // expand of address
		m_sendD3[0][9][2]=0xFF; // data D0
		m_sendD3[0][9][3]=0xFD; // D1
		m_sendD3[0][9][4]=0xFF; // D2
		m_sendD3[0][9][5]=0xFF; // D3
		m_sendD3[0][9][6]=0x50; // the end of command


		
		// 11 吸合  2弦
		m_sendD3[1][0][0]=0x10; // the command
		m_sendD3[1][0][1]=0x00; // expand of address
		m_sendD3[1][0][2]=0xFF; // data D0
		m_sendD3[1][0][3]=0xFB; // D1
		m_sendD3[1][0][4]=0xFF; // D2
		m_sendD3[1][0][5]=0xFF; // D3
		m_sendD3[1][0][6]=0x50; // the end of command

		
		// 12 吸合 
		m_sendD3[1][1][0]=0x10; // the command
		m_sendD3[1][1][1]=0x00; // expand of address
		m_sendD3[1][1][2]=0xFF; // data D0
		m_sendD3[1][1][3]=0xF7; // D1
		m_sendD3[1][1][4]=0xFF; // D2
		m_sendD3[1][1][5]=0xFF; // D3
		m_sendD3[1][1][6]=0x50; // the end of command

		// 13 吸合 
		m_sendD3[1][2][0]=0x10; // the command
		m_sendD3[1][2][1]=0x00; // expand of address
		m_sendD3[1][2][2]=0xFF; // data D0
		m_sendD3[1][2][3]=0xEF; // D1
		m_sendD3[1][2][4]=0xFF; // D2
		m_sendD3[1][2][5]=0xFF; // D3
		m_sendD3[1][2][6]=0x50; // the end of command

		// 14 吸合 
		m_sendD3[1][3][0]=0x10; // the command
		m_sendD3[1][3][1]=0x00; // expand of address
		m_sendD3[1][3][2]=0xFF; // data D0
		m_sendD3[1][3][3]=0xDF; // D1
		m_sendD3[1][3][4]=0xFF; // D2
		m_sendD3[1][3][5]=0xFF; // D3
		m_sendD3[1][3][6]=0x50; // the end of command

		// 15 吸合 
		m_sendD3[1][4][0]=0x10; // the command
		m_sendD3[1][4][1]=0x00; // expand of address
		m_sendD3[1][4][2]=0xFF; // data D0
		m_sendD3[1][4][3]=0xBF; // D1
		m_sendD3[1][4][4]=0xFF; // D2
		m_sendD3[1][4][5]=0xFF; // D3
		m_sendD3[1][4][6]=0x50; // the end of command

		// 16 吸合 
		m_sendD3[1][5][0]=0x10; // the command
		m_sendD3[1][5][1]=0x00; // expand of address
		m_sendD3[1][5][2]=0xFF; // data D0
		m_sendD3[1][5][3]=0x7F; // D1
		m_sendD3[1][5][4]=0xFF; // D2
		m_sendD3[1][5][5]=0xFF; // D3
		m_sendD3[1][5][6]=0x50; // the end of command

		// 17 吸合 
		m_sendD3[1][6][0]=0x10; // the command
		m_sendD3[1][6][1]=0x00; // expand of address
		m_sendD3[1][6][2]=0xFF; // data D0
		m_sendD3[1][6][3]=0xFF; // D1
		m_sendD3[1][6][4]=0xFE; // D2
		m_sendD3[1][6][5]=0xFF; // D3
		m_sendD3[1][6][6]=0x50; // the end of command

		// 18 吸合 
		m_sendD3[1][7][0]=0x10; // the command
		m_sendD3[1][7][1]=0x00; // expand of address
		m_sendD3[1][7][2]=0xFF; // data D0
		m_sendD3[1][7][3]=0xFF; // D1
		m_sendD3[1][7][4]=0xFD; // D2
		m_sendD3[1][7][5]=0xFF; // D3
		m_sendD3[1][7][6]=0x50; // the end of command

		// 19 吸合 
		m_sendD3[1][8][0]=0x10; // the command
		m_sendD3[1][8][1]=0x00; // expand of address
		m_sendD3[1][8][2]=0xFF; // data D0
		m_sendD3[1][8][3]=0xFF; // D1
		m_sendD3[1][8][4]=0xFB; // D2
		m_sendD3[1][8][5]=0xFF; // D3
		m_sendD3[1][8][6]=0x50; // the end of command

		// 20 吸合 
		m_sendD3[1][9][0]=0x10; // the command
		m_sendD3[1][9][1]=0x00; // expand of address
		m_sendD3[1][9][2]=0xFF; // data D0
		m_sendD3[1][9][3]=0xFF; // D1
		m_sendD3[1][9][4]=0xF7; // D2
		m_sendD3[1][9][5]=0xFF; // D3
		m_sendD3[1][9][6]=0x50; // the end of command

		//21 吸合 3弦 
		m_sendD3[2][0][0]=0x10; // the command
		m_sendD3[2][0][1]=0x00; // expand of address
		m_sendD3[2][0][2]=0xFF; // data D0
		m_sendD3[2][0][3]=0xFF; // D1
		m_sendD3[2][0][4]=0xEF; // D2
		m_sendD3[2][0][5]=0xFF; // D3
		m_sendD3[2][0][6]=0x50; // the end of command


		// 22吸合
		m_sendD3[2][1][0]=0x10; // the command
		m_sendD3[2][1][1]=0x00; // expand of address
		m_sendD3[2][1][2]=0xFF; // data D0
		m_sendD3[2][1][3]=0xFF; // D1
		m_sendD3[2][1][4]=0xDF; // D2
		m_sendD3[2][1][5]=0xFF; // D3
		m_sendD3[2][1][6]=0x50; // the end of command

		// 23吸合
		m_sendD3[2][2][0]=0x10; // the command
		m_sendD3[2][2][1]=0x00; // expand of address
		m_sendD3[2][2][2]=0xFF; // data D0
		m_sendD3[2][2][3]=0xFF; // D1
		m_sendD3[2][2][4]=0xBF; // D2
		m_sendD3[2][2][5]=0xFF; // D3
		m_sendD3[2][2][6]=0x50; // the end of command

		// 24吸合
		m_sendD3[2][3][0]=0x10; // the command
		m_sendD3[2][3][1]=0x00; // expand of address
		m_sendD3[2][3][2]=0xFF; // data D0
		m_sendD3[2][3][3]=0xFF; // D1
		m_sendD3[2][3][4]=0x7F; // D2
		m_sendD3[2][3][5]=0xFF; // D3
		m_sendD3[2][3][6]=0x50; // the end of command

		// 25吸合
		m_sendD3[2][4][0]=0x10; // the command
		m_sendD3[2][4][1]=0x00; // expand of address
		m_sendD3[2][4][2]=0xFF; // data D0
		m_sendD3[2][4][3]=0xFF; // D1
		m_sendD3[2][4][4]=0xFF; // D2
		m_sendD3[2][4][5]=0xFE; // D3
		m_sendD3[2][4][6]=0x50; // the end of command

		// 26吸合
		m_sendD3[2][5][0]=0x10; // the command
		m_sendD3[2][5][1]=0x00; // expand of address
		m_sendD3[2][5][2]=0xFF; // data D0
		m_sendD3[2][5][3]=0xFF; // D1
		m_sendD3[2][5][4]=0xFF; // D2
		m_sendD3[2][5][5]=0xFD; // D3
		m_sendD3[2][5][6]=0x50; // the end of command

		// 27吸合
		m_sendD3[2][6][0]=0x10; // the command
		m_sendD3[2][6][1]=0x00; // expand of address
		m_sendD3[2][6][2]=0xFF; // data D0
		m_sendD3[2][6][3]=0xFF; // D1
		m_sendD3[2][6][4]=0xFF; // D2
		m_sendD3[2][6][5]=0xFB; // D3
		m_sendD3[2][6][6]=0x50; // the end of command

		// 28吸合
		m_sendD3[2][7][0]=0x10; // the command
		m_sendD3[2][7][1]=0x00; // expand of address
		m_sendD3[2][7][2]=0xFF; // data D0
		m_sendD3[2][7][3]=0xFF; // D1
		m_sendD3[2][7][4]=0xFF; // D2
		m_sendD3[2][7][5]=0xF7; // D3
		m_sendD3[2][7][6]=0x50; // the end of command

		// 29吸合
		m_sendD3[2][8][0]=0x10; // the command
		m_sendD3[2][8][1]=0x00; // expand of address
		m_sendD3[2][8][2]=0xFF; // data D0
		m_sendD3[2][8][3]=0xFF; // D1
		m_sendD3[2][8][4]=0xFF; // D2
		m_sendD3[2][8][5]=0xEF; // D3
		m_sendD3[2][8][6]=0x50; // the end of command

		// 30吸合  1弦控制器
		m_sendD3[2][9][0]=0x10; // the command
		m_sendD3[2][9][1]=0x00; // expand of address
		m_sendD3[2][9][2]=0xFF; // data D0
		m_sendD3[2][9][3]=0xFF; // D1
		m_sendD3[2][9][4]=0xFF; // D2
		m_sendD3[2][9][5]=0xDF; // D3
		m_sendD3[2][9][6]=0x50; // the end of command


		// 31吸合  2弦控制器
		m_sendD3[2][10][0]=0x10; // the command
		m_sendD3[2][10][1]=0x00; // expand of address
		m_sendD3[2][10][2]=0xFF; // data D0
		m_sendD3[2][10][3]=0xFF; // D1
		m_sendD3[2][10][4]=0xFF; // D2
		m_sendD3[2][10][5]=0xBF; // D3
		m_sendD3[2][10][6]=0x50; // the end of command

		// 32吸合  3弦控制器
		m_sendD3[2][11][0]=0x10; // the command
		m_sendD3[2][11][1]=0x00; // expand of address
		m_sendD3[2][11][2]=0xFF; // data D0
		m_sendD3[2][11][3]=0xFF; // D1
		m_sendD3[2][11][4]=0xFF; // D2
		m_sendD3[2][11][5]=0x7F; // D3
		m_sendD3[2][11][6]=0x50; // the end of command

		//g_NoteEight2Jump=true;
		//从文件中读取解析码
		 while((fgets(oneLine,20,stream))!=NULL)
          {
             strcpy_s(deltaTime,strtok_s(oneLine,";",&context));
             strcpy_s(string,strtok_s(NULL,";",&context));
             strcpy_s(fret,strtok_s(NULL,";",&context));
			 strcpy_s(note,strtok_s(NULL,";",&context));
			 // convert into integer
			 stringI = atoi(string);
			 fretI = atoi(fret);
			 deltaTimeI = atoi(deltaTime);
			 noteTT = atoi(note);

			 if(!arrayA.IsEmpty()){
				 arrayA.RemoveAll();
				 Sleep(130);
			 }

			 for(sLoop = 0;sLoop < 7;sLoop++){
				 arrayA.Add(m_sendD3[stringI][fretI][sLoop]);
	         }
			 
			 m_com.put_Output(COleVariant(arrayA));

			 //控制端
			 if(!arrayC.IsEmpty()){
				 arrayC.RemoveAll();
				 Sleep(250);
			 }

			g_ChangeCount++;
			g_ComData=stringI;

			 switch(noteTT){
			
			case 68:
			case 69:
			case 70:  g_NoteWholeJump = true;
				      break;     
			case 71:
			case 72:
			case 73:  g_NoteHalfJump = true;
				      break;
			case 74:
		    case 75:
			case 76:  g_NoteFourthJump = true;
				      break;
			case 77:
			case 78:
			case 79:  g_NoteEightJump = true;
			          break;
			case 80:
			case 81:
			case 82:  g_NoteSixteenthJump = true;
				      break;
			case 83:
			case 84:
			case 85:  g_NoteThirtySecondJump = true;
				      break;
			 }





			 //g_NoteEight2Jump=true;
			 //拨动一弦
			 if(stringI == 0){
				 if(flag1 == false){
				 
					 for(sLoop = 0;sLoop < 10;sLoop++)
				    {
					  arrayC.Add(m_sendD2[0][0][sLoop]);
	                }
			     
					 m_com1.put_Output(COleVariant(arrayC));
					 flag1 = true;
				 }else{
					  //2,3弦开
					  if(flag2 == true && flag3 == true){
					  for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[0][0][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag1 = false;
				 }else if(flag2 == true && flag3 == false){     //仅2开
					  for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[0][2][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag1 = false; 
					}else if(flag2 == false && flag3 == true){  //仅3开
						 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[0][1][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag1 = false; 
				 }else{                                        //全关
					  for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendCloseAll[sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag1 = false;
					}
				 }
			   
			 }

			  //拨动二弦
			  if(stringI == 1){
				 if(flag2 == false){
				 for(sLoop = 0;sLoop < 10;sLoop++)
				 {
					arrayC.Add(m_sendD2[0][1][sLoop]);
	             }
			     m_com1.put_Output(COleVariant(arrayC));
				 flag2 = true;
				 }else{
					 if(flag1 == true && flag3 == true){       //关2； 1、3亮
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[1][0][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag2 = false;
				 }else if(flag1 == true && flag3 == false){   //关2,3；1亮
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[1][1][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag2 = false;
					 }else if(flag1 ==false && flag3 == true){  //关2,1；3亮
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[0][1][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag2 = false;
				 }else{                                        //全关
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendCloseAll[sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag2 = false;
					 }
				 }

			 }


			  //拨动三弦
			 if(stringI == 2){
				 if(flag3 == false){
				 for(sLoop = 0;sLoop < 10;sLoop++)
				 {
					arrayC.Add(m_sendD2[0][2][sLoop]);
	             }
			     m_com1.put_Output(COleVariant(arrayC));
				 flag3 = true;
				 }else{
					 if(flag1==true && flag2==true){             //1,2开；3关
					  for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[2][0][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag3 = false;
				 }else if(flag1==false && flag2==true){            //2开；1、3关
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendClose[0][2][sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag3 = false;
					 }else if(flag1==true && flag2==false){     // 1开；2、3关
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				       arrayD.Add(m_sendClose[1][1][sLoop]);
					 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag3 = false;
				 }else{                                       //全关
					 for(sLoop = 0;sLoop < 10;sLoop++)
					 {
				        arrayD.Add(m_sendCloseAll[sLoop]);
	                 }
					  m_com1.put_Output(COleVariant(arrayD));
					  flag3 = false;
					 }
				 }
			 }

			 //Sleep(130);
			 arrayD.RemoveAll();
			
			 /* 
			 for(sLoop = 0;sLoop < 10;sLoop++)
			{
				arrayD.Add(m_sendClose[sLoop]);
	        }
			  
				
			 m_com1.put_Output(COleVariant(arrayD));
			
			*/
			 
			 Sleep(deltaTimeI * 1.5 + 130);
          }
			 fclose(stream);
			 Sleep(5000);
			 arrayD.RemoveAll();
			 for(sLoop = 0;sLoop < 10;sLoop++)
			{
			  arrayD.Add(m_sendCloseAll[sLoop]);
	        }
			 m_com1.put_Output(COleVariant(arrayD));
			 arrayA.RemoveAll();
			 for(sLoop = 0;sLoop < 7;sLoop++){
				 arrayA.Add(m_sendCloseAll2[sLoop]);
	         }
			 
			 m_com.put_Output(COleVariant(arrayA));
}

//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CComDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString xx("221");
	m_rdata.Empty();
	UpdateData(FALSE);
	//m_combox.ShowDropDown( TRUE);
}


// 由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
int CComDlg::String2Hex(CString str, CByteArray & senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}


// 功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
char CComDlg::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}


void CComDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CComDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CComDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CComDlg::OnMscomm2()
{
	// TODO: Add your command handler code here
	// TODO: 在此处添加消息处理程序代码
	UpdateData(true);
	COleVariant   myVar; 
	//VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len,k;
    BYTE rxdata[3]; //设置BYTE数组 An 8-bit integer that is not signed.
	//char rxdata[10];
	CString strtemp;//
	if(m_com1.get_CommEvent()==2) //事件值为2表示接收缓冲区内有字符
	{
		myVar.Attach(m_com1.get_Input());
		//variant_inp=m_com1.get_Input(); //读缓冲区
		safearray_inp=myVar; //VARIANT型变量转换为ColeSafeArray型变量
	    len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		//len=2;
		//m_com.put_RThreshold(8);
		for(k=0;k <len;k++){
			safearray_inp.GetElement(&k,&rxdata[k]); //转换为BYTE型数组
		   for(k=0;k <len;k++)  //将数组转换为Cstring型变量
		   { 
			   BYTE bt= 0xDD; //字符型
			   strtemp.Format(_T("%02x"),bt);//将字符送入临时变量strtemp存放
			   //String2Hex(strtemp,hexdata);
			//m_strRXData+=strtemp; //加入接收编辑框对应字符串

		}
	}
	UpdateData(TRUE); //更新编辑框内容 
	m_rdata+=" ";
	m_rdata += strtemp;
	UpdateData(FALSE);
	m_show_data.LineScroll(m_show_data.GetLineCount());

	


	}


}


void CComDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CComDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CComDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	WinExec("H:\\ustlmidi.exe",1);
}
