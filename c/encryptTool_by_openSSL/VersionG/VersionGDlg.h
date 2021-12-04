
// VersionGDlg.h : header file
//



#pragma once

unsigned char key[];
char *base64_encode(const void *b64_encode_this, int encode_this_many_bytes);
char *base64_decode(const void  *b64_decode_this, int decode_this_many_bytes);
int openssl_aes_ecb_encrypt(char* in, size_t len, char* out);
int openssl_aes_ecb_decrypt(char* in,size_t len, char* out);

// CVersionGDlg dialog
class CVersionGDlg : public CDialogEx
{
// Construction
public:
	CVersionGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VERSIONG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
//	CEdit m_edit_encrypt;
	CEdit m_edit_decrypt;
	CEdit m_edit_encrypt;
//	afx_msg void OnChangeEditEncrypt();
//	afx_msg void OnChangeEditDecrypt();
	afx_msg void OnClickedButtonDecrypt();
	afx_msg void OnClickedButtonEncrypt();
	CEdit m_edit_key;
};
