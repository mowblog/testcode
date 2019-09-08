
// socketDlg.h : header file
//

#pragma once


// CsocketDlg dialog
class CsocketDlg : public CDialogEx
{
// Construction
public:
	CsocketDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	//重载OnOk函数，默认按回车之后将focus 设置在 btn_send
	void CsocketDlg::OnOK()
	{
		m_btn_send.SetFocus();
	}


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CString m_conn;
	CString m_send;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();

	CButton m_btn_conn;
	CButton m_btn_send;
	CEdit m_edit_send;
	afx_msg void OnClickedButtonListen();
	afx_msg void OnClickedButtonInit();
	CEdit m_edit_conn;
	DWORD m_localip;
	DWORD m_server_ip;
	CIPAddressCtrl m_ip_localip;
	CIPAddressCtrl m_ip_serverip;

	static UINT MyTcpServer(LPVOID lParam);
	static UINT MyTcpClient(LPVOID lParam);
	static UINT MyUdpServer(LPVOID lParam);
	static UINT MyUdpClient(LPVOID lParam);

	CButton m_btn_release;
	afx_msg void OnClickedButtonRelease();
	CButton m_btn_init;
	CButton m_btn_listen;

	static BOOL ts_Status;
	CEdit m_edit_serverport;
	CEdit m_edit_localport;

	UINT m_localport;
	UINT m_serverport;
	CString m_mesg;
	CEdit m_edit_mesg;
};
