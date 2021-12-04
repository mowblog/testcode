
// LDKEvaluationDlg.cpp : implementation file
//

#include <stdlib.h>

#include "stdafx.h"
#include "LDKEvaluation.h"
#include "LDKEvaluationDlg.h"
#include "afxdialogex.h"
#include "vendor_code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//define global variable to store the edit info
CString Feature;
CString Handle;
CString Input;
CString Output;
CString Status;
CString Offset;
CString Length;
CString Scope;
CString Format;
CString Fileid;
CString Timer;
UINT DoCycle(LPVOID pParam);
LDK ldk;

//parameter struct for thread
#define MAXTHREADNUM 50
struct myThreadParam {
	int feature;
	CString scope;
	CString format;
	int fileid;
	int offset;
	int length;
	CString input;

	int Flag[8];
	UINT counts;
	UINT sleeptime;
	CLDKEvaluationDlg *pDlg;
} pParam[MAXTHREADNUM] = { 0 };
int threadIndex = 0;
BOOL myThreadFlag=true;
//handle of thread
CWinThread *pcycle[MAXTHREADNUM];
//Edit Control support Ctrl+A

// CLDKEvaluationDlg dialog

CLDKEvaluationDlg::CLDKEvaluationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LDKEVALUATION_DIALOG, pParent)
	, m_edit_value_feature(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLDKEvaluationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_cmb_format);
	DDX_Control(pDX, IDC_COMBO_SCOPE, m_cmb_scope);
	DDX_Control(pDX, IDC_EDIT_FEATURE, m_edit_feature);
	DDX_Control(pDX, IDC_EDIT_FORMAT, m_edit_format);
	DDX_Control(pDX, IDC_EDIT_HANDLE, m_edit_handle);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_input);
	DDX_Control(pDX, IDC_EDIT_LENGTH, m_edit_length);
	DDX_Control(pDX, IDC_EDIT_OFFSET, m_edit_offset);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edit_output);
	DDX_Control(pDX, IDC_EDIT_SCOPE, m_edit_scope);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_edit_status);
	DDX_Control(pDX, IDC_EDIT_FILEID, m_edit_fileid);
	DDX_Text(pDX, IDC_EDIT_FEATURE, m_edit_value_feature);
	DDV_MinMaxInt(pDX, m_edit_value_feature, -100, 65535);
	DDX_Control(pDX, IDC_CHECK_1LOGIN, m_ck_1login);
	DDX_Control(pDX, IDC_CHECK_2LOGINSCOPE, m_ck_2loginscope);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_ck_cycle);
	DDX_Control(pDX, IDC_CHECK_3GETINFO, m_ck_3getinfo);
	DDX_Control(pDX, IDC_CHECK_4READ, m_ck_4read);
	DDX_Control(pDX, IDC_CHECK_5WRITE, m_ck_5write);
	DDX_Control(pDX, IDC_CHECK_6ENCRYPT, m_ck_6encrypt);
	DDX_Control(pDX, IDC_CHECK_7DECRYPT, m_ck_7decrypt);
	DDX_Control(pDX, IDC_CHECK_8LOGOUT, m_ck_8logout);
	DDX_Control(pDX, IDC_BUTTON_START, m_btn_start);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btn_stop);
	DDX_Control(pDX, IDC_EDIT_CYCLECOUNT, m_edit_cyclecount);
	DDX_Control(pDX, IDC_EDIT_SLEEPTIME, m_edit_sleeptime);
	DDX_Control(pDX, IDC_EDIT_TIMER, m_edit_timer);
}

BEGIN_MESSAGE_MAP(CLDKEvaluationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CLDKEvaluationDlg::OnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CLDKEvaluationDlg::OnClickedButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_GETINFO, &CLDKEvaluationDlg::OnClickedButtonGetinfo)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLDKEvaluationDlg::OnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CLDKEvaluationDlg::OnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CLDKEvaluationDlg::OnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CLDKEvaluationDlg::OnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN_SCOPE, &CLDKEvaluationDlg::OnClickedButtonLoginScope)
	ON_CBN_SELCHANGE(IDC_COMBO_FORMAT, &CLDKEvaluationDlg::OnSelchangeComboFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_SCOPE, &CLDKEvaluationDlg::OnSelchangeComboScope)

ON_BN_CLICKED(IDC_BUTTON_START, &CLDKEvaluationDlg::OnClickedButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CLDKEvaluationDlg::OnClickedButtonStop)
ON_BN_CLICKED(IDC_CHECK_CYCLE, &CLDKEvaluationDlg::OnClickedCheckCycle)

END_MESSAGE_MAP()


// CLDKEvaluationDlg message handlers

BOOL CLDKEvaluationDlg::OnInitDialog()
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
	//initialize the scope and format
	//ldk = LDK((char*)vendor_Code);
	m_edit_feature.SetWindowText("0");
	m_edit_fileid.SetWindowText("65524");
	m_edit_offset.SetWindowText("0");
	m_edit_length.SetWindowText("16");

	m_cmb_scope.InsertString(0,_T("specify host"));
	m_cmb_scope.InsertString(1,_T("specify ip"));
	m_cmb_scope.InsertString(2,_T("specify keyid"));
	m_cmb_scope.InsertString(3,_T("specify product"));
	m_cmb_scope.InsertString(4,_T("HL only"));
	m_cmb_scope.InsertString(5,_T("unfiltered"));
	m_cmb_scope.SetCurSel(5);
	m_edit_scope.SetWindowText(scope_default);

	m_cmb_format.InsertString(0,_T("accessible keys"));
	m_cmb_format.InsertString(1,_T("get lincese status"));
	m_cmb_format.InsertString(2,_T("feature information"));
	m_cmb_format.InsertString(3,_T("get v2c"));
	m_cmb_format.InsertString(4,_T("get fingerprint"));
	m_cmb_format.SetCurSel(0);
	m_edit_format.SetWindowText(format0);

	m_ck_1login.ShowWindow(false);
	m_ck_2loginscope.ShowWindow(false);
	m_ck_3getinfo.ShowWindow(false);
	m_ck_4read.ShowWindow(false);
	m_ck_5write.ShowWindow(false);
	m_ck_6encrypt.ShowWindow(false);
	m_ck_7decrypt.ShowWindow(false);
	m_ck_8logout.ShowWindow(false);

	m_edit_cyclecount.SetWindowText("200");
	m_edit_sleeptime.SetWindowText("5");
	m_btn_start.EnableWindow(false);
	m_btn_stop.EnableWindow(false);
	//pParam = (struct myThreadParam*)calloc(sizeof(struct myThreadParam), 1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//void CLDKEvaluationDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
//		CDialogEx::OnSysCommand(nID, lParam);
//	}
//}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLDKEvaluationDlg::OnPaint()
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
HCURSOR CLDKEvaluationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLDKEvaluationDlg::OnClickedButtonDecrypt()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString DecryptBuf;
	m_edit_length.GetWindowText(Length);
	m_edit_input.GetWindowText(DecryptBuf);
	if (DecryptBuf.IsEmpty())
	{
		AfxMessageBox("Input is NULL", MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (!ldk.CHECKHEXSTRING(DecryptBuf))
	{
		AfxMessageBox(_T("please input hex"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (DecryptBuf.GetLength() < 32)
	{
		AfxMessageBox("string length is short than 16 Bytes", MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString DecryptedBuf = ldk.Decrypt(DecryptBuf);
	Status.Format("%d", ldk.status);
	m_edit_output.SetWindowText(DecryptedBuf);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonEncrypt()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString EncryptBuf;
	m_edit_input.GetWindowText(EncryptBuf);
	m_edit_length.GetWindowText(Length);
	if (EncryptBuf.IsEmpty())
	{
		AfxMessageBox("Input is NULL", MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (!ldk.CHECKHEXSTRING(EncryptBuf))
	{
		AfxMessageBox(_T("please input hex"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (EncryptBuf.GetLength() < 32)
	{
		AfxMessageBox("Encrypt string length is short than 16 Bytes", MB_OK | MB_ICONERROR, 0);
		return;
	}

	CString EncryptedBuf =ldk.Encrypt(EncryptBuf);
	Status.Format("%d", ldk.status);
	m_edit_status.SetWindowText(Status);
	m_edit_output.SetWindowText(EncryptedBuf);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonGetinfo()
{
	// TODO: Add your control notification handler code here
	CString Info;
	m_edit_scope.GetWindowText(Scope);
	m_edit_format.GetWindowText(Format);

	Output = ldk.GetInfo(Scope, Format);
	Status.Format("%d", ldk.status);
	Output.Replace("\n", "\r\n");
	m_edit_status.SetWindowText(Status);
	m_edit_output.SetWindowText(Output);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox(L"this is a test", MB_OK | MB_ICONINFORMATION, 0);
	//ChaspFeature feature = ChaspFeature::fromFeature(1);
	m_edit_feature.GetWindowText(Feature);
	//ldk.Login(_tstoi(feature));
	//UpdateData(true);
	int f = atoi(Feature);
	ldk.Login(f);

	Status.Format(_T("%d"), ldk.status);
	m_edit_status.SetWindowText(Status);
	if (!ldk.status) {
		Handle.Format("%X", ldk.hc->handle);
	}
	else {
		Handle.Format("%X", 0);
	}
	m_edit_handle.SetWindowText(Handle);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	ldk.Logout();
	if (ldk.status == -1)
	{
		AfxMessageBox(_T("there has no handle to release"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	else
	{
		if (ldk.hc != NULL)
		{
			Status.Format("%d", ldk.status);
			Handle.Format("%X", ldk.hc->handle);
		}
		else {
			Status.Format("%d", 0);
			Handle.Format("%X", 0);

		}
		m_edit_status.SetWindowText(Status);
		m_edit_handle.SetWindowText(Handle);
	}
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonRead()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	
	m_edit_length.GetWindowText(Length);
	m_edit_offset.GetWindowText(Offset);
	m_edit_fileid.GetWindowText(Fileid);
	CString ReadBuf;
	//buf.GetBufferSetLength(_tstoi(length));
	ReadBuf = ldk.Read(atoi(Fileid), atoi(Offset), atoi(Length));
	
	Status.Format("%d", ldk.status);
	m_edit_status.SetWindowText(Status);
	m_edit_output.SetWindowText(ReadBuf);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonWrite()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	
	CString WriteBuf;
	m_edit_length.GetWindowText(Length);
	m_edit_offset.GetWindowText(Offset);
	m_edit_fileid.GetWindowText(Fileid);
	m_edit_input.GetWindowText(WriteBuf);
	if (!ldk.CHECKHEXSTRING(WriteBuf))
	{
		AfxMessageBox(_T("please input hex"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (WriteBuf.IsEmpty())
	{
		AfxMessageBox(_T("Nothing to write"), MB_OK | MB_ICONERROR, 0);
		return;
	}

	ldk.Write(atoi(Fileid), atoi(Offset), WriteBuf);
	Status.Format("%d", ldk.status);
	m_edit_status.SetWindowText(Status);
	m_edit_output.SetWindowText(WriteBuf);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnClickedButtonLoginScope()
{
	// TODO: Add your control notification handler code here
	m_edit_scope.GetWindowText(Scope);
	m_edit_feature.GetWindowText(Feature);
	//UpdateData(true);
	int f = atoi(Feature);
	ldk.LoginScope(f, Scope);
	Status.Format(_T("%d"), ldk.status);
	m_edit_status.SetWindowText(Status);
	if (!ldk.status) {
		Handle.Format(_T("%X"), ldk.hc->handle);
	}
	else {
		Handle.Format(_T("%X"), 0);
	}
	m_edit_handle.SetWindowText(Handle);
	Timer.Format("%.2f", ldk.LDKTimer);
	m_edit_timer.SetWindowText(Timer);
}


void CLDKEvaluationDlg::OnSelchangeComboFormat()
{
	// TODO: Add your control notification handler code here
	UINT f = m_cmb_format.GetCurSel();
	switch (f)
	{
	case 0:
		Format = format0;
		break;
	case 1:
		Format = format1;
		break;
	case 2:
		Format = format2;
		break;
	case 3:
		Format = format3;
		break;
	case 4:
		Format = format4;
		break;
	default:
		Format = format4;
		break;
	}
	m_edit_format.SetWindowText(Format);

}


void CLDKEvaluationDlg::OnSelchangeComboScope()
{
	// TODO: Add your control notification handler code here

	UINT s = m_cmb_scope.GetCurSel();
	switch (s)
	{
		case 0:
			Scope=scope0;
			break;
		case 1:
			Scope = scope1;
			break;
		case 2:
			Scope = scope2;
			break;
		case 3:
			Scope =scope3;
			break;
		case 4:
			Scope =scope4;
			break;
		default:
			Scope = scope_default;
			break;
	}
	m_edit_scope.SetWindowText(Scope);
}


void CLDKEvaluationDlg::OnClickedButtonStart()
{

	CString counts;
	CString sleeptime;
	m_edit_cyclecount.GetWindowText(counts);
	m_edit_sleeptime.GetWindowText(sleeptime);
	if (counts.IsEmpty() || sleeptime.IsEmpty())
	{
		AfxMessageBox("please input the counts and sleeptime", MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (threadIndex >= MAXTHREADNUM)
	{
		AfxMessageBox("can not create more threads");
		return;
	}

	//pParam =  ( struct myThreadParam*)malloc(sizeof(struct myThreadParam));
	//struct myThreadParam pParam = {0};
	//test the checkbox for each function is checked or not
	if (m_ck_1login.GetCheck())
		pParam[threadIndex].Flag[0] = 1;
	else
		pParam[threadIndex].Flag[0] = 0;
	if (m_ck_2loginscope.GetCheck())
		pParam[threadIndex].Flag[1] = 1;
	else
		pParam[threadIndex].Flag[1] = 0;
	if (m_ck_3getinfo.GetCheck())
		pParam[threadIndex].Flag[2] = 1;
	else
		pParam[threadIndex].Flag[2] = 0;
	if (m_ck_4read.GetCheck())
		pParam[threadIndex].Flag[3] = 1;
	else
		pParam[threadIndex].Flag[3] = 0;
	if (m_ck_5write.GetCheck())
		pParam[threadIndex].Flag[4] = 1;
	else
		pParam[threadIndex].Flag[4] = 0;
	if (m_ck_6encrypt.GetCheck())
		pParam[threadIndex].Flag[5] = 1;
	else
		pParam[threadIndex].Flag[5] = 0;
	if (m_ck_7decrypt.GetCheck())
		pParam[threadIndex].Flag[6] = 1;
	else
		pParam[threadIndex].Flag[6] = 0;
	if (m_ck_8logout.GetCheck())
		pParam[threadIndex].Flag[7] = 1;
	else
		pParam[threadIndex].Flag[7] = 0;
	//init the global variable
	m_edit_feature.GetWindowText(Feature);
	m_edit_scope.GetWindowText(Scope);
	m_edit_format.GetWindowText(Format);
	m_edit_fileid.GetWindowText(Fileid);
	m_edit_offset.GetWindowText(Offset);
	m_edit_length.GetWindowText(Length);
	m_edit_input.GetWindowText(Input);

	pParam[threadIndex].feature = atoi(Feature);
	pParam[threadIndex].scope = Scope;
	pParam[threadIndex].format = Format.GetBuffer();
	pParam[threadIndex].fileid = atoi(Fileid);
	pParam[threadIndex].offset = atoi(Offset);
	pParam[threadIndex].length = atoi(Length);
	pParam[threadIndex].input = Input.GetBuffer();

	pParam[threadIndex].counts = atoi(counts);
	pParam[threadIndex].sleeptime = atoi(sleeptime);
	
	
	pParam[threadIndex].pDlg = this; 

	/* create a thread to do the while cycle */
	pcycle[threadIndex++] = AfxBeginThread(DoCycle, (LPVOID)&pParam[threadIndex],THREAD_PRIORITY_NORMAL,0,0,NULL);
}

/* Terminate the thread by TerminateThread is very dangrous, so please DO NOT use this function */
void CLDKEvaluationDlg::OnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CString mesg1 = "ThreadTerminated:";
	CString mesg2 = "ThreadTerminate failed:";
	for (int k = threadIndex-1; k >= 0;k--)
	if (pcycle[k] != NULL)
	{
		if (TerminateThread(pcycle[k]->m_hThread, 0))
		{
			mesg1.AppendFormat("%d ", k);
			threadIndex--;
		}
		else
		{
			mesg2.AppendFormat("%d ", k);
		}
	}
	mesg1 += "\r\n";
	mesg1 += mesg2;
	
	AfxMessageBox(mesg1, MB_OK, 0);
	threadIndex = 0;
}


void CLDKEvaluationDlg::OnClickedCheckCycle()
{
	// TODO: Add your control notification handler code here
	if (m_ck_cycle.GetCheck())
	{
		m_ck_1login.ShowWindow(true);
		m_ck_2loginscope.ShowWindow(true);
		m_ck_3getinfo.ShowWindow(true);
		m_ck_4read.ShowWindow(true);
		m_ck_5write.ShowWindow(true);
		m_ck_6encrypt.ShowWindow(true);
		m_ck_7decrypt.ShowWindow(true);
		m_ck_8logout.ShowWindow(true);

		m_btn_start.EnableWindow(true);
		m_btn_stop.EnableWindow(true);

		m_edit_input.SetWindowText("30313233343536373839414243444546");
	}
	else {
		m_ck_1login.ShowWindow(false);
		m_ck_2loginscope.ShowWindow(false);
		m_ck_3getinfo.ShowWindow(false);
		m_ck_4read.ShowWindow(false);
		m_ck_5write.ShowWindow(false);
		m_ck_6encrypt.ShowWindow(false);
		m_ck_7decrypt.ShowWindow(false);
		m_ck_8logout.ShowWindow(false);

		m_btn_start.EnableWindow(false);
		m_btn_stop.EnableWindow(false);

		m_edit_input.SetWindowText("");
	}
}



UINT DoCycle(LPVOID pParam)
{
	LDK LDK4Cycle;
	struct myThreadParam *param = (struct myThreadParam*)pParam;
	//struct myThreadParam *param = (struct myThreadParam*)malloc(sizeof(struct myThreadParam));
	//memcpy(param,pParam,sizeof(struct myThreadParam));
	CString mesg;
	CString Handle;
	UINT c = 1;
	int clogin = 0, cloginscope = 0, cgetinfo = 0, cread = 0, cwrite = 0, cencrypt = 0, cdecrypt = 0, clogout = 0;
	
	while (c <= param->counts)
	{
		mesg.Empty();
		mesg.AppendFormat("%d/%d \r\n-----------------\r\n", c, param->counts);
		if (param->Flag[0] == 1) {
			LDK4Cycle.Login(param->feature);
			if (LDK4Cycle.status == 0) { 
				clogin++; 
				Handle.Format("%X",LDK4Cycle.handle);
				param->pDlg->m_edit_handle.SetWindowText(Handle); }
			mesg.AppendFormat("login(%d/%d): %d  --  %5.2fms\r\n", clogin, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[1] == 1) {
			LDK4Cycle.LoginScope(param->feature, param->scope);
			if (LDK4Cycle.status == 0) {
				cloginscope++;
				Handle.Format("%X", LDK4Cycle.handle);
				param->pDlg->m_edit_handle.SetWindowText(Handle);
			}
			mesg.AppendFormat("loginscope(%d/%d): %d  --  %5.2fms\r\n", cloginscope, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[2] == 1) {
			LDK4Cycle.GetInfo(param->scope, param->format);
			if (LDK4Cycle.status == 0) cgetinfo++;
			mesg.AppendFormat("getinfo(%d/%d): %d  --  %5.2fms\r\n", cgetinfo, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[3] == 1) {
			LDK4Cycle.Read(param->fileid, param->offset, param->length);
			if (LDK4Cycle.status == 0) cread++;
			mesg.AppendFormat("read(%d/%d): %d  --  %5.2fms\r\n", cread, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[4] == 1)
		{
			LDK4Cycle.Write(param->fileid, param->offset, param->input);
			if (LDK4Cycle.status == 0) cwrite++;
			mesg.AppendFormat("write(%d/%d): %d  --  %5.2fms\r\n", cwrite, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[5] == 1) {
			LDK4Cycle.Encrypt(Input);
			if (LDK4Cycle.status == 0) cencrypt++;
			mesg.AppendFormat("encrypt(%d/%d): %d  --  %5.2fms\r\n", cencrypt, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[6] == 1) {
			LDK4Cycle.Decrypt(Input);
			if (LDK4Cycle.status == 0) cdecrypt++;
			mesg.AppendFormat("decrypt(%d/%d): %d  --  %5.2fms\r\n", cdecrypt, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		if (param->Flag[7] == 1)
		{
			LDK4Cycle.Logout();
			if (LDK4Cycle.status == 0) { 
				clogout++; 
			}
			mesg.AppendFormat("logout(%d/%d): %d  --  %5.2fms\r\n", clogout, c, LDK4Cycle.status, LDK4Cycle.LDKTimer);
		}
		param->pDlg->m_edit_output.SetWindowText(mesg);
		c++;
		::Sleep(param->sleeptime);
	}
	Handle.Format("%X", 0);
	param->pDlg->m_edit_handle.SetWindowText(Handle);
	return 0;
}



//void CLDKEvaluationDlg::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//	LDK LDK4Cycle;
//	int count = 1000;
//
//	m_edit_feature.GetWindowText(Feature);
//	m_edit_scope.GetWindowText(Scope);
//	m_edit_format.GetWindowText(Format);
//	m_edit_fileid.GetWindowText(Fileid);
//	m_edit_offset.GetWindowText(Offset);
//	m_edit_length.GetWindowText(Length);
//	m_edit_input.GetWindowText(Input);
//	while(count--){
//
//
//	LDK4Cycle.Login(atoi(Feature));
//	LDK4Cycle.LoginScope(atoi(Feature), Scope);
//	LDK4Cycle.Read(atoi(Fileid), atoi(Offset), atoi(Length));
//	LDK4Cycle.Write(atoi(Fileid), atoi(Offset), Input);
//	LDK4Cycle.Encrypt(Input);
//	LDK4Cycle.Decrypt(Input);
//	LDK4Cycle.Logout();
//	}
//}
