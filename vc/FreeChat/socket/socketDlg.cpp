// socketDlg.cpp : implementation file
//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "stdafx.h"
#include "socket.h"
#include "socketDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

#define MAXLENGTH 200 //tcp send/recv buff size
#define MAXLENGTH_U 200 //udp sendto/recvfm buff size

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//socket全局变量
	
//tcp socket
static SOCKET TR_sock;
static SOCKET TL_sock;
static SOCKET sockConn; //tcp connect
//udp socket
static SOCKET UR_sock;
static SOCKET UL_sock;
//socket地址
//tcp socket addr
static SOCKADDR_IN TR_addr;
static SOCKADDR_IN TL_addr;
//udp socket addr
static SOCKADDR_IN UR_addr;
static SOCKADDR_IN UL_addr;

//Local IP and Port 
DWORD local_IP;
UINT local_port;
	
//Server IP and Port
DWORD server_IP;
UINT server_port;
//hostname buff
char host_name[100];
//tcp & udp send/recv buff
char sendTBuf[MAXLENGTH];
char recvTBuf[MAXLENGTH];
char sendUBuf[MAXLENGTH_U];
char recvUBuf[MAXLENGTH_U];
//handle of the thread
CWinThread* ptd_tcpS;
CWinThread* ptd_udpS;
CWinThread* ptd_tcpC;
CWinThread* ptd_udpC;

//标志位
static int EndThread = 0; //线程结束标志位
static unsigned int EnRelease = 0; //Release标志位


// CAboutDlg dialog used for App About



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsocketDlg dialog




CsocketDlg::CsocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsocketDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_edit_conn.SetWindowTextA(_T(""));
	//m_edit_send.SetWindowTextA(_T(""));
	m_mesg = _T("How to start: \r\n"
		"1. run the tool on both local PC-A and remote PC-B \r\n"
		"2. input IP and PORT of PC-A and PC-B \r\n"
		"3. click \"initialize\" on both PC-A and PC-B \r\n" 
		"4. click \"listen\" on both PC-A and PC-B to start the tcp&udp service \r\n" 
		"5. click \"connect\" on both PC-A and PC-B to connect each other\r\n" 
		"6. type the mesg and click \"send\" to send it to each other \r\n");

	m_localport = 9999;
	m_serverport = 9999;
	m_localip = 2130706433;
	m_server_ip = 2130706433;
}

void CsocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONNECT, m_conn);
	DDX_Text(pDX, IDC_EDIT_SEND, m_send);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btn_conn);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btn_send);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Control(pDX, IDC_EDIT_CONNECT, m_edit_conn);
	DDX_IPAddress(pDX, IDC_IPADDRESS_LOCAL, m_localip);
	DDX_IPAddress(pDX, IDC_IPADDRESS_SERVER, m_server_ip);
	DDX_Control(pDX, IDC_IPADDRESS_LOCAL, m_ip_localip);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ip_serverip);
	DDX_Control(pDX, IDC_BUTTON_RELEASE, m_btn_release);
	DDX_Control(pDX, IDC_BUTTON_INIT, m_btn_init);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btn_listen);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_edit_serverport);
	DDX_Control(pDX, IDC_EDIT_LOCAL_PORT, m_edit_localport);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_localport);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_localport);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_serverport);
	DDX_Text(pDX, IDC_EDIT_MESG, m_mesg);
	DDX_Control(pDX, IDC_EDIT_MESG, m_edit_mesg);
}

BEGIN_MESSAGE_MAP(CsocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CsocketDlg::OnClickedButtonConnect)
ON_BN_CLICKED(IDC_BUTTON_SEND, &CsocketDlg::OnClickedButtonSend)
ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CsocketDlg::OnClickedButtonListen)
ON_BN_CLICKED(IDC_BUTTON_INIT, &CsocketDlg::OnClickedButtonInit)
ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CsocketDlg::OnClickedButtonRelease)
END_MESSAGE_MAP()


// CsocketDlg message handlers

BOOL CsocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_edit_conn.SetSel(-1,-1); //设置edit_conn自动滚动到底部


	//设置焦点
//	m_btn_conn.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CsocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//设置tcp一直处在监听状态
int tcp_keep_alive(SOCKET socketfd)
{
int keepAlive = 1;
int keepIdle = 10;
int keepInterval = 10;
int keepCount = 10;
int reuseaddr = 1;
//设置tcp链接处于激活状态
if(setsockopt(socketfd,SOL_SOCKET,SO_KEEPALIVE, (char *)&keepAlive,sizeof(int)) == -1){
	//return WSAGetLastError();
	return -1;
}
//设置tcp地址可以复用
if(setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR, (char *)&reuseaddr,sizeof(int)) == -1){
	//return WSAGetLastError();
	return -1;
}
return 0;
}


UINT CsocketDlg::MyTcpServer(LPVOID lParam)
{
	CsocketDlg* pp = (CsocketDlg*)lParam;
	CString mesg;
	int ret,error;
	
	pp->m_edit_conn.SetSel(-1,-1);

	ret = tcp_keep_alive(TL_sock);
	error = WSAGetLastError();
	if( ret == -1){
		mesg.Format(_T("tcps.1 setsockopt failed: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}
	else{
		mesg.Format(_T("tcps.1 setsockopt: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}

	ret = bind(TL_sock,(SOCKADDR*)&TL_addr,sizeof(SOCKADDR));
	error = WSAGetLastError();
	if(ret!=0 && !EnRelease){
		mesg.Format(_T("tcps.2 bind failed: %d,please release and retry"),error);
		pp->MessageBox(mesg);
		return error;
	}
	else{
		mesg.Format(_T("tcps.2 bind: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");		
	}

	ret = listen(TL_sock,5);
	error = WSAGetLastError();
	if(ret!=0 && !EnRelease){
		mesg.Format(_T("tcps.3 listen failed: %d,please release and retry"),error);
		pp->MessageBox(mesg);
		return error;
	}
	else{
		mesg.Format(_T("tcps.3 listen: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");		
	}

	SOCKADDR_IN addrClient;
	int saddr = sizeof(SOCKADDR);
	sockConn=accept(TL_sock,(SOCKADDR*)&addrClient,&saddr);
	error = WSAGetLastError();
	if(sockConn == INVALID_SOCKET && !EnRelease){
		if(error == 10004){
			mesg.Format(_T("tcps.4 accept canceled"));
			pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
		}
		else{
			mesg.Format(_T("tcps.4 accept failed: %d,please release and retry"),error);
			pp->MessageBox(mesg);
			return error;
		}
	}
	else{
		mesg.Format(_T("tcps.4 accept: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}

	//char* ipCli = inet_ntoa(addrClient.sin_addr);

	do
	{
		ret = recv(sockConn,recvTBuf,MAXLENGTH,0);
		error = WSAGetLastError();
		if(ret<0 && !EnRelease){
			if(error == 10004){ /*recv被取消*/
				mesg.Format(_T("tcps.5 recv canceled\r\n"));
				pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
			}else{
			mesg.Format(_T("tcps.5 recv: %d \r\n close tcps socket"),error);
			pp->MessageBox(mesg);
			}
			shutdown(sockConn,SD_SEND);
			return 0;
		}
		else{
				mesg.Format(_T("%s"),recvTBuf);
				pp->m_edit_mesg.ReplaceSel(mesg + "\r\n");
			}
		memset(recvTBuf,0,MAXLENGTH);
	}while(ret>0);
	return 0;
}

UINT CsocketDlg::MyUdpServer(LPVOID lParam)
{
	CsocketDlg* pp = (CsocketDlg*)lParam;

	CString mesg;
	int ret,error;

	pp->m_edit_conn.SetSel(-1,-1);

	ret = bind(UL_sock,(SOCKADDR*)&UL_addr,sizeof(SOCKADDR));
	error = WSAGetLastError();
	if(ret !=0 && !EnRelease){
		mesg.Format(_T("udps.1 bind failed: %d,please release and retry"),error);
		pp->MessageBox(mesg);
		return error;
	}
	else{
		mesg.Format(_T("udps.1 bind: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);

	do{
		ret = recvfrom(UL_sock,recvUBuf,MAXLENGTH_U,0,(SOCKADDR*)&addrClient,&len);
		error = WSAGetLastError();
		if(ret < 0 && !EnRelease){
			if(error == 10004){
				mesg.Format(_T("udps.2 recvfrom canceled"));
				pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
				closesocket(UL_sock);
			}else{
				mesg.Format(_T("udps.2 recvfrom failed: %d"),error);
				pp->MessageBox(mesg);
				closesocket(UL_sock);
				return error;
			}
		}else{
			mesg.Format(_T("%s"),recvUBuf);
			pp->m_edit_mesg.ReplaceSel(mesg + "\r\n");
		}
		memset(recvUBuf,0,MAXLENGTH_U);
	}while(ret>0);
	return 0;
}

UINT CsocketDlg::MyTcpClient(LPVOID lParam)
{
	CsocketDlg* pp = (CsocketDlg*) lParam;
	CString mesg;
	int ret,error;
	int len = sizeof(sockaddr);

	pp->m_edit_conn.SetSel(-1,-1);
	//设置socket option
	ret = tcp_keep_alive(TR_sock);
	error = WSAGetLastError();
	if( ret < 0){
		mesg.Format(_T("tcpc.1 setsockopt failed: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}
	else{
		mesg.Format(_T("tcpc.1 setsockopt: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}

	//链接服务器
	ret = connect(TR_sock,(SOCKADDR*)&TR_addr,sizeof(SOCKADDR));
	error = WSAGetLastError();
	if(ret<0 && !EnRelease){
		mesg.Format(_T("tcpc.2 connect failed: %d,please release and retry"),error);
		pp->MessageBox(mesg);
		return error;
	}
	else{
		mesg.Format(_T("tpcc.2 connect: %d"),error);
		pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	}
	return 0;
}

UINT CsocketDlg::MyUdpClient(LPVOID lParam)
{
	//链接远端UDP Server
	CsocketDlg *pp = (CsocketDlg *)lParam;
	//CString mesg=_T("udpc.1");
	//pp->m_edit_conn.ReplaceSel(mesg + "\r\n");
	//udp无需建立链接，直接设置标志位
	return 0;
}

void CsocketDlg::OnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	LPVOID pParam=NULL;
	UINT nStackSize=0;
	DWORD dwCreateFlags=0;
	LPSECURITY_ATTRIBUTES lpSecurityAttrs=NULL;
	
	ptd_tcpC = AfxBeginThread(MyTcpClient,
                      this,
					  THREAD_PRIORITY_NORMAL, 
					  0,
					  0,
					  NULL
					);
 
	ptd_udpC = AfxBeginThread(MyUdpClient,
                      this,
					  THREAD_PRIORITY_NORMAL, 
					  0,
					  0,
					  NULL
					);
	
	DWORD exitcode=0,exitcode2=0;
	WaitForSingleObject(ptd_tcpC,INFINITE);
	GetExitCodeThread(ptd_tcpC,&exitcode);
	WaitForSingleObject(ptd_udpC,INFINITE);
	GetExitCodeThread(ptd_udpC,&exitcode2);
	if(exitcode !=0 || exitcode2 != 0)
		MessageBox(_T("connnect to server failed, please retry"));
	else 
		m_btn_conn.EnableWindow(false);
}


void CsocketDlg::OnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	CString msgsend ;
	CString mesg;
	int ret,error;

	m_edit_send.GetWindowTextA(msgsend);
	m_edit_send.SetWindowTextA(_T(""));
	
	//设置焦点为输入框
	m_edit_send.SetFocus();

	//udp send
	int len = sizeof(sockaddr);
	in_addr localIP;
	localIP.S_un.S_addr = htonl(server_IP);
	sprintf_s(sendUBuf,"(udp:)%s@%s:",host_name,inet_ntoa(localIP));
	//sendto(UR_sock, sendUBuf, MAXLENGTH_U, 0, (SOCKADDR*)&UR_addr, len);
	sendto(UR_sock, sendUBuf, strlen(sendUBuf), 0, (SOCKADDR*)&UR_addr, len);
	Sleep(200);// ensure the udp data first arrive to the server

	//发送tcp数据
	char *ts1 = (char*)msgsend.GetBuffer(msgsend.GetLength());
	sprintf_s(sendTBuf,"(tcp:)%s",ts1);

	//显示本地发送的消息
	m_edit_mesg.SetSel(-1,-1);
	mesg.Format(_T("%s:\r\n%s\r\n"),host_name,ts1);
	m_edit_mesg.ReplaceSel(mesg);

	//tcp send
	ret = send(TR_sock,sendTBuf,strlen(sendTBuf),0);
	error = WSAGetLastError();
	if(ret<0 && !EnRelease){
		mesg.Format(_T("tcpc send to tcps failed: %d"),error);
		MessageBox(mesg);
	}
	memset(sendUBuf,0,MAXLENGTH_U);
	memset(sendTBuf,0,MAXLENGTH);
}

void CsocketDlg::OnClickedButtonListen()
{
	// TODO: Add your control notification handler code here
	LPVOID pParam=NULL;
	UINT nStackSize=0;
	DWORD dwCreateFlags=0;
	LPSECURITY_ATTRIBUTES lpSecurityAttrs=NULL;
	
	//lpSecurityAttrs->lpSecurityDescriptor=THREAD_ALL_ACCESS;
	ptd_tcpS = AfxBeginThread(MyTcpServer,
                      this,
					  THREAD_PRIORITY_NORMAL, 
					  0,
					  0,
					  NULL
					);

	ptd_udpS = AfxBeginThread(MyUdpServer,
                      this,
					  THREAD_PRIORITY_NORMAL, 
					  0,
					  0,
					  NULL
					);
	
	DWORD exitcode=1,exitcode2=1;
	//WaitForSingleObject(ptd_tcpS,INFINITE);
	//WaitForSingleObject(ptd_udpS,INFINITE);
	//GetExitCodeThread(ptd_udpS,&exitcode2);
	m_btn_listen.EnableWindow(false);
}



void CsocketDlg::OnClickedButtonInit()
{
	// TODO: Add your control notification handler code here
	//socket初始化

	WORD wVersionRequested;
	WSADATA wsaData;
	int ret,error;
	CString strIP, mesg;

	//
	EnRelease = 0;

	//清空m_mesg
	m_edit_mesg.SetWindowTextA(_T(""));

	wVersionRequested = MAKEWORD( 2, 2 );

	ret = WSAStartup( wVersionRequested, &wsaData );
	error = WSAGetLastError();
	if ( ret != 0 ) {
		mesg.Format(_T("WSAStartup failed: %d,pease retry"),error);
		MessageBox(mesg);
	}
	else{
		m_edit_conn.SetSel(-1,-1);
		mesg.Format(_T("WSAStartup: %d"),error);
		m_edit_conn.ReplaceSel(mesg + "\r\n");
	}

	//get local port and IP address
	UpdateData(TRUE);
	local_port=m_localport;
	m_ip_localip.GetAddress(local_IP);	
	//get remote IP and Port
	server_port=m_serverport;
	m_ip_serverip.GetAddress(server_IP);
	UpdateData(FALSE);

	/*
	m_ip_localip.GetWindowText(strIP);
	mesg = _T("listen with ip:")+ strIP;
	m_edit_conn.ReplaceSel(mesg + "\r\n");
	mesg.Format(_T("port:%u"), local_port);
	m_edit_conn.ReplaceSel(mesg + "\r\n");
	*/

	//initialize local tcp server
	TL_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//TL_addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	TL_addr.sin_addr.S_un.S_addr=htonl(local_IP);
	TL_addr.sin_family=AF_INET;
	TL_addr.sin_port=htons(local_port);


	//initialize local udp server
	UL_sock = socket(AF_INET,SOCK_DGRAM,0);
	//UL_addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	UL_addr.sin_addr.S_un.S_addr=htonl(local_IP);
	UL_addr.sin_family=AF_INET;
	UL_addr.sin_port=htons(local_port);

	//initialize local tcp client
	TR_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	TR_addr.sin_addr.S_un.S_addr=htonl(server_IP);
	TR_addr.sin_family=AF_INET;
	TR_addr.sin_port=htons(server_port);

	//initialize local udp client
	UR_sock = socket(AF_INET,SOCK_DGRAM,0);
	UR_addr.sin_addr.S_un.S_addr=htonl(server_IP);
	UR_addr.sin_family=AF_INET;
	UR_addr.sin_port=htons(server_port);

	//initialize the local hostname
	ret = gethostname(host_name, sizeof(host_name));
	error = WSAGetLastError();
	if(ret != 0 ){
		mesg.Format(_T("get hostname failed: %d"),error);
		m_edit_conn.ReplaceSel(mesg + "\r\n");
	}
	//初始化完成之后禁用按钮
	if((TL_sock==INVALID_SOCKET) || (UL_sock==INVALID_SOCKET) || (TR_sock==INVALID_SOCKET) || (UR_sock==INVALID_SOCKET))
		MessageBox(_T("socket initialize failed"));
	else
		m_btn_init.EnableWindow(false);
}


void CsocketDlg::OnClickedButtonRelease()
{
	// TODO: Add your control notification handler code here
	EnRelease = 1;
	short timer = 6; //10 seconds to release the source
	CString mesg;
	//1.结束进程
	/*
	TerminateThread(ptd_tcpS, 800);
	TerminateThread(ptd_tcpC, 800);
	TerminateThread(ptd_udpS, 800);
	TerminateThread(ptd_udpC, 800);
	
	shutdown(sockConn,2);
	shutdown(TR_sock,2);
	shutdown(UR_sock,2);
	shutdown(UL_sock,2);
	shutdown(TL_sock,2);
	*/
	closesocket(sockConn);
	closesocket(TR_sock);
	closesocket(UR_sock);
	closesocket(UL_sock);
	closesocket(TL_sock);
	TR_sock = INVALID_SOCKET;
	UR_sock = INVALID_SOCKET;
	UL_sock = INVALID_SOCKET;
	TL_sock = INVALID_SOCKET;

	memset(sendTBuf,0,MAXLENGTH);
	memset(recvTBuf,0,MAXLENGTH);
	memset(sendUBuf,0,MAXLENGTH_U);
	memset(recvUBuf,0,MAXLENGTH_U);

	WSACleanup();

	/*
	do
	{
		mesg.Format(_T("(%d)"),timer);
		m_btn_release.SetWindowTextA(mesg);
		Sleep(1000);
		timer--;
	}while(timer>0);
	*/
	//3.使能button
	m_btn_init.EnableWindow(true);
	m_btn_conn.EnableWindow(true);
	m_btn_listen.EnableWindow(true);

						//4. clear m_edit_conn
		//UpdateData(FALSE);

		//m_mesg = _T("");
		//m_conn = _T("");
		//UpdateData(TRUE);

	//mesg.Format(_T("(4)release"));
	//m_btn_release.SetWindowTextA(mesg);
	m_edit_mesg.SetWindowTextA(_T(""));
	m_edit_conn.SetWindowTextA(_T(""));

}
