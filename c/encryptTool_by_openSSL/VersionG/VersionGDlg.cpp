
// VersionGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VersionG.h"
#include "VersionGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CVersionGDlg dialog




CVersionGDlg::CVersionGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVersionGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVersionGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_DECRYPT, m_edit_encrypt);
	DDX_Control(pDX, IDC_EDIT_DECRYPT, m_edit_decrypt);
	DDX_Control(pDX, IDC_EDIT_ENCRYPT, m_edit_encrypt);
	DDX_Control(pDX, IDC_EDIT_KEY, m_edit_key);
}

BEGIN_MESSAGE_MAP(CVersionGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_EN_CHANGE(IDC_EDIT_ENCRYPT, &CVersionGDlg::OnChangeEditEncrypt)
//	ON_EN_CHANGE(IDC_EDIT_DECRYPT, &CVersionGDlg::OnChangeEditDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CVersionGDlg::OnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CVersionGDlg::OnClickedButtonEncrypt)
END_MESSAGE_MAP()


// CVersionGDlg message handlers

BOOL CVersionGDlg::OnInitDialog()
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
	m_edit_key.SetLimitText(8);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVersionGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVersionGDlg::OnPaint()
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
HCURSOR CVersionGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CVersionGDlg::OnChangeEditEncrypt()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//
//}


//void CVersionGDlg::OnChangeEditDecrypt()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//	
//}


void CVersionGDlg::OnClickedButtonDecrypt()
{
	// TODO: Add your control notification handler code here
	CString src, dst, cs_key;
	char *aes_s, *aes_d;
	m_edit_decrypt.GetWindowText(src);
	m_edit_key.GetWindowText(cs_key);
	char * c_key=cs_key.GetBuffer(0);
	if(strlen(c_key)!=8)
	{
		MessageBox("please input 8 characters key");
		return;
	}
	else
	{
		for(int i=0;i<8;i++)
		{
			key[i]=c_key[i];
		}
	}
	//aes_s = (char*)calloc(src.GetLength(), 1);
	//USES_CONVERSION;
	//char* base64_d = W2A(src);
	int len_s = src.GetLength();
	char* base64_d1=src.GetBuffer(0);
	char* base64_d = base64_d1+1;
	char* base64_s = base64_decode((unsigned char*)base64_d, len_s-1);

	//char* aes_debuf = dst2.c_str();
	char* aes_inbuf = base64_s;
	aes_d = (char*)calloc(len_s - 1, 1);
	openssl_aes_ecb_decrypt(aes_inbuf, len_s-1, aes_d);
	dst.Format("%s", aes_d);
	m_edit_encrypt.SetWindowText(dst);
}


void CVersionGDlg::OnClickedButtonEncrypt()
{
	// TODO: Add your control notification handler code here
	CString src,dst,cs_key;
	char *aes_s,*aes_d;
	m_edit_encrypt.GetWindowText(src);
	m_edit_key.GetWindowText(cs_key);
	
	char * c_key=cs_key.GetBuffer(0);
	if(strlen(c_key)!=8)
	{
		MessageBox("please input 8 characters key");
		return;
	}
	else
	{
		for(int i=0;i<8;i++)
		{
			key[i]=c_key[i];
		}
	}
	//s = (char*)calloc(src.GetLength(), 1);
	//USES_CONVERSION;
	//aes_s = W2A(src);
	int len_s = src.GetLength();
	aes_s=src.GetBuffer();
	//aes encrypt
	//aes_d = (char*)calloc((strlen(aes_s)/16+1)*16 ,1);
	aes_d = (char*)calloc((len_s / 16 + 1) * 16, 1);
	int size = openssl_aes_ecb_encrypt(aes_s, len_s, aes_d);
	char* dst2 = base64_encode((unsigned char*)aes_d, (len_s / 16 + 1) * 16);
	//dst = dst2.c_str();
	dst.Format("%X%s", size-strlen(aes_s), dst2);

	m_edit_decrypt.SetWindowText(dst);
}
