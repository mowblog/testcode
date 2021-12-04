
// LDKEvaluationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LDKEvaluation.h"
#include "LDKEvaluationDlg.h"
#include "afxdialogex.h"
#include "vendor_code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//define global variable to store the edit info
CString feature;
CString handle;
CString input;
CString output;
CString status;
CString offset;
CString length;
CString scope;
CString format;
CString fileid;
UINT docycle(LPVOID pParam);
LDK ldk;

//parameter struct for thread
struct myThreadParam {
	char Flag[8];
	UINT counts;
	UINT sleeptime;
	CLDKEvaluationDlg *pDlg;
} *pParam;
BOOL myThreadFlag=true;
//handle of thread
CWinThread *pcycle;
//Edit Control support Ctrl+A

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


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
	//  DDX_Control(pDX, IDC_BUTTON_START, m_btn_start);
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
//	ON_CBN_EDITCHANGE(IDC_COMBO_SCOPE, &CLDKEvaluationDlg::OnEditchangeComboScope)
//	ON_CBN_EDITCHANGE(IDC_COMBO_FORMAT, &CLDKEvaluationDlg::OnEditchangeComboFormat)
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
	ldk = LDK((char*)vendor_Code);
	m_edit_feature.SetWindowText(L"0");
	m_edit_fileid.SetWindowText(L"65524");
	m_edit_offset.SetWindowText(L"0");
	m_edit_length.SetWindowText(L"16");

	m_cmb_scope.InsertString(0,_T("specify host"));
	m_cmb_scope.InsertString(1,_T("specify ip"));
	m_cmb_scope.InsertString(2,_T("specify keyid"));
	m_cmb_scope.InsertString(3,_T("specify product"));
	m_cmb_scope.InsertString(4,_T("HL only"));
	m_cmb_scope.InsertString(5, L"unfiltered");
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

	m_btn_start.EnableWindow(false);
	m_btn_stop.EnableWindow(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLDKEvaluationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
	CString buf;
	m_edit_length.GetWindowText(length);
	m_edit_input.GetWindowText(buf);
	if (buf.IsEmpty())
	{
		AfxMessageBox(L"empty input", MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (buf.GetLength() / 2 != _tstoi(length))
	{
		AfxMessageBox(L"the length is different from real length of input", MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString de = ldk.Decrypt(buf, _tstoi(length));
	status.Format(L"%d", ldk.status);
	m_edit_output.SetWindowText(de);
}


void CLDKEvaluationDlg::OnClickedButtonEncrypt()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString buf;
	m_edit_input.GetWindowText(buf);
	m_edit_length.GetWindowText(length);
	if (buf.IsEmpty())
	{
		AfxMessageBox(L"empty input", MB_OK | MB_ICONERROR, 0);
		return;
	}
	if (buf.GetLength()/2 != _tstoi(length))
	{
		AfxMessageBox(L"the length is different from real length of input", MB_OK | MB_ICONERROR, 0);
		return;
	}
	CString en=ldk.Encrypt(buf,_tstoi(length));
	status.Format(L"%d", ldk.status);
	m_edit_status.SetWindowText(status);
	m_edit_output.SetWindowText(en);
}


void CLDKEvaluationDlg::OnClickedButtonGetinfo()
{
	// TODO: Add your control notification handler code here
	CString info;
	m_edit_scope.GetWindowText(scope);
	m_edit_format.GetWindowText(format);

	output = ldk.GetInfo(scope, format);
	status.Format(L"%d", ldk.status);
	m_edit_status.SetWindowText(status);
	m_edit_output.SetWindowText(output);
}


void CLDKEvaluationDlg::OnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox(L"this is a test", MB_OK | MB_ICONINFORMATION, 0);
	//ChaspFeature feature = ChaspFeature::fromFeature(1);
	m_edit_feature.GetWindowText(feature);
	//ldk.Login(_tstoi(feature));
	UpdateData(true);
	int f = m_edit_value_feature;
	ldk.Login(f);

	status.Format(_T("%d"), ldk.status);
	m_edit_status.SetWindowText(status);
	if (!ldk.status) {
		handle.Format(L"%X", ldk.hc->handle);
	}
	else {
		handle.Format(L"%X", 0);
	}
	m_edit_handle.SetWindowText(handle);
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
			status.Format(L"%d", ldk.status);
			handle.Format(L"%X", ldk.hc->handle);
			m_edit_status.SetWindowText(status);
			m_edit_handle.SetWindowText(handle);
		}
		else {
			status.Format(L"%d", 0);
			handle.Format(L"%X", 0);
			m_edit_status.SetWindowText(status);
			m_edit_handle.SetWindowText(handle);
		}
	}
}


void CLDKEvaluationDlg::OnClickedButtonRead()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	
	m_edit_length.GetWindowText(length);
	m_edit_offset.GetWindowText(offset);
	m_edit_fileid.GetWindowText(fileid);
	CString buf;
	//buf.GetBufferSetLength(_tstoi(length));
	buf = ldk.Read(_tstoi(fileid), _tstoi(offset), _tstoi(length));
	
	status.Format(L"%d", ldk.status);
	m_edit_status.SetWindowText(status);
	m_edit_output.SetWindowText(buf);
}


void CLDKEvaluationDlg::OnClickedButtonWrite()
{
	// TODO: Add your control notification handler code here
	if (ldk.hc == NULL)
	{
		AfxMessageBox(_T("please login first"), MB_OK | MB_ICONERROR, 0);
		return;
	}
	m_edit_length.GetWindowText(length);
	m_edit_offset.GetWindowText(offset);
	m_edit_fileid.GetWindowText(fileid);
	CString buf;
	m_edit_input.GetWindowText(buf);
	//buf.GetBufferSetLength(_tstoi(length));
	ldk.Write(_tstoi(fileid), _tstoi(offset), _tstoi(length), buf);
	status.Format(L"%d", ldk.status);
	m_edit_status.SetWindowText(status);
	m_edit_output.SetWindowText(buf);
}


void CLDKEvaluationDlg::OnClickedButtonLoginScope()
{
	// TODO: Add your control notification handler code here
	m_edit_scope.GetWindowText(scope);
	UpdateData(true);
	int f = m_edit_value_feature;
	ldk.LoginScope(f, scope);
	status.Format(_T("%d"), ldk.status);
	m_edit_status.SetWindowText(status);
	if (!ldk.status) {
		handle.Format(_T("%X"), ldk.hc->handle);
	}
	else {
		handle.Format(_T("%X"), 0);
	}
	m_edit_handle.SetWindowText(handle);
}


void CLDKEvaluationDlg::OnSelchangeComboFormat()
{
	// TODO: Add your control notification handler code here
	UINT f = m_cmb_format.GetCurSel();
	switch (f)
	{
	case 0:
		format = format0;
		break;
	case 1:
		format = format1;
		break;
	case 2:
		format = format2;
		break;
	case 3:
		format = format3;
		break;
	case 4:
		format = format4;
		break;
	default:
		format = format4;
		break;
	}
	m_edit_format.SetWindowText(format);

}


void CLDKEvaluationDlg::OnSelchangeComboScope()
{
	// TODO: Add your control notification handler code here

	UINT s = m_cmb_scope.GetCurSel();
	switch (s)
	{
		case 0:
			scope=scope0;
			break;
		case 1:
			scope= scope1;
			break;
		case 2:
			scope=scope2;
			break;
		case 3:
			scope=scope3;
			break;
		case 4:
			scope=scope4;
			break;
		default:
			scope = scope_default;
			break;
	}
	m_edit_scope.SetWindowText(scope);
}


void CLDKEvaluationDlg::OnClickedButtonStart()
{
	CString counts;
	CString sleeptime;
	m_edit_cyclecount.GetWindowText(counts);
	m_edit_sleeptime.GetWindowTextW(sleeptime);
	if (counts.IsEmpty() || sleeptime.IsEmpty())
	{
		AfxMessageBox(L"please input the counts and sleeptime", MB_OK | MB_ICONERROR, 0);
		return;
	}

	pParam = (struct myThreadParam*)calloc(1, sizeof(struct myThreadParam));
	//test the checkbox for each function is checked or not
	if (m_ck_1login.GetCheck())
		pParam->Flag[0] = 1;
	else
		pParam->Flag[0] = 0;
	if (m_ck_2loginscope.GetCheck())
		pParam->Flag[1] = 1;
	else
		pParam->Flag[1] = 0;
	if (m_ck_3getinfo.GetCheck())
		pParam->Flag[2] = 1;
	else
		pParam->Flag[2] = 0;
	if (m_ck_4read.GetCheck())
		pParam->Flag[3] = 1;
	else
		pParam->Flag[3] = 0;
	if (m_ck_5write.GetCheck())
		pParam->Flag[4] = 1;
	else
		pParam->Flag[4] = 0;
	if (m_ck_6encrypt.GetCheck())
		pParam->Flag[5] = 1;
	else
		pParam->Flag[5] = 0;
	if (m_ck_7decrypt.GetCheck())
		pParam->Flag[6] = 1;
	else
		pParam->Flag[6] = 0;
	if (m_ck_8logout.GetCheck())
		pParam->Flag[7] = 1;
	else
		pParam->Flag[7] = 0;
	//init the global variable
	m_edit_feature.GetWindowText(feature);
	m_edit_scope.GetWindowText(scope);
	m_edit_format.GetWindowText(format);
	m_edit_fileid.GetWindowText(fileid);
	m_edit_offset.GetWindowTextW(offset);
	m_edit_length.GetWindowTextW(length);
	m_edit_input.GetWindowTextW(input);


	pParam->counts = _tstoi(counts);
	pParam->sleeptime = _tstoi(sleeptime);
	
	pParam->pDlg = this;
	//create a thread to do the cycle
	
	pcycle = AfxBeginThread(docycle, (LPVOID)pParam,THREAD_PRIORITY_NORMAL,0,0,NULL);

}


void CLDKEvaluationDlg::OnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CString mesg;
	if (TerminateThread(pcycle->m_hThread, 0))
	{
		mesg = "thread timinated";
	}
	else
	{
		mesg.Format(L"thread timinate failed: %d,please close the program", GetLastError());
	}
	AfxMessageBox(mesg, MB_OK, 0);

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

		m_edit_input.SetWindowText(L"30313233343536373839414243444546");
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

		m_edit_input.SetWindowText(L"");
	}
}



UINT docycle(LPVOID pParam)
{

	struct myThreadParam *param = (struct myThreadParam*)pParam;
	CString mesg;
	UINT c = 1;
	int clogin = 0, cloginscope = 0, cgetinfo = 0, cread = 0, cwrite = 0, cencrypt = 0, cdecrypt = 0, clogout = 0;
	while (c <= param->counts)
	{
		//if (!myThreadFlag)
		//	return 0;
		mesg = "";
		mesg.AppendFormat(L"%d/%d \r\n-----------------\r\n", c, param->counts);
		if (param->Flag[0] == 1) {
			ldk.Login(_tstoi(feature));
			if (ldk.status == 0)
			{
				clogin++;
			}
			mesg.AppendFormat(L"login(%d/%d): %d  --  %5.2fms\r\n", clogin, c, ldk.status,ldk.LDKTimer*1000);
		}
		if (param->Flag[1] == 1) {
			ldk.LoginScope(_tstoi(feature), scope);
			if (ldk.status == 0)
			{
				cloginscope++;
			}
			mesg.AppendFormat(L"loginscope(%d/%d): %d  --  %5.2fms\r\n", cloginscope, c, ldk.status,ldk.LDKTimer*1000);
		}
		if (param->Flag[2] == 1) {
			ldk.GetInfo(scope, format);
			if (ldk.status == 0) cgetinfo++;
			mesg.AppendFormat(L"getinfo(%d/%d): %d  --  %5.2fms\r\n", cgetinfo, c, ldk.status,ldk.LDKTimer*1000);
		}
		if (param->Flag[3] == 1) {
			ldk.Read(_tstoi(fileid), _tstoi(offset), _tstoi(length));
			if (ldk.status == 0) cread++;
			mesg.AppendFormat(L"read(%d/%d): %d  --  %5.2fms\r\n", cread, c, ldk.status, ldk.LDKTimer*1000);
		}
		if (param->Flag[4] == 1)
		{
			ldk.Write(_tstoi(fileid), _tstoi(offset), _tstoi(length), input);
			if (ldk.status == 0) cwrite++;
			mesg.AppendFormat(L"write(%d/%d): %d  --  %5.2fms\r\n", cwrite, c, ldk.status, ldk.LDKTimer*1000);
		}
		if (param->Flag[5] == 1) {
			ldk.Encrypt(input, _tstoi(length));
			if (ldk.status == 0) cencrypt++;
			mesg.AppendFormat(L"encrypt(%d/%d): %d  --  %5.2fms\r\n", cencrypt, c, ldk.status, ldk.LDKTimer*1000);
		}
		if (param->Flag[6] == 1) {
			ldk.Decrypt(input, _tstoi(length));
			if (ldk.status == 0) cdecrypt++;
			mesg.AppendFormat(L"decrypt(%d/%d): %d  --  %5.2fms\r\n", cdecrypt, c, ldk.status, ldk.LDKTimer*1000);
		}
		if (param->Flag[7] == 1)
		{
			ldk.Logout();
			if (ldk.status == 0) clogout++;
			mesg.AppendFormat(L"logout(%d/%d): %d  --  %5.2fms\r\n", clogout, c, ldk.status, ldk.LDKTimer*1000);
		}
		param->pDlg->m_edit_output.SetWindowText(mesg);

		c++;
		Sleep(param->sleeptime);
	}

	return 0;
}

class MyThreadClass : public CLDKEvaluationDlg
{
	BOOL InitInstance()
	{

	}
};