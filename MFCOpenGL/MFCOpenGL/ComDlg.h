
// ComDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"


// CComDlg �Ի���
class CComDlg : public CDialogEx
{
// ����
public:
	CComDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_com;
	
	CString m_rdata;
	afx_msg void OnBnClickedButton2();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	
//	afx_msg void OnEnChangeEdit1();
	CEdit m_show_data;
	afx_msg void OnBnClickedButton3();
	//int m_send_data;
	CString m_send;
//	afx_msg void OnEnChangeEdit1();
	short m_port,m_port1;
	int m_band,m_band1;
	afx_msg void OnBnClickedButton1();
	// �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
	int String2Hex(CString str, CByteArray & senddata);
	// ���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
	char ConvertHexChar(char ch);
	//CButton m_button2;
	CButton m_button2;
	//CComboBox m_combox;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	//afx_msg void OnEnChangeEdit5();
	//afx_msg void OnEnChangeEdit4();
	afx_msg void OnMscomm2();
	CMscomm1 m_com1;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton6();
};
