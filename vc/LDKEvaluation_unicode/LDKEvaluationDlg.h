
// LDKEvaluationDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "LDK.h"


// CLDKEvaluationDlg dialog
class CLDKEvaluationDlg : public CDialogEx
{
// Construction
public:
	CLDKEvaluationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LDKEVALUATION_DIALOG };
#endif

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
	afx_msg void OnClickedButtonDecrypt();
	afx_msg void OnClickedButtonEncrypt();
	afx_msg void OnClickedButtonGetinfo();
	afx_msg void OnClickedButtonLogin();
	afx_msg void OnClickedButtonLogout();
	afx_msg void OnClickedButtonRead();
	afx_msg void OnClickedButtonWrite();
	CComboBox m_cmb_format;
	CComboBox m_cmb_scope;
	CEdit m_edit_feature;
	CEdit m_edit_format;
	CEdit m_edit_handle;
	CEdit m_edit_input;
	CEdit m_edit_length;
	CEdit m_edit_offset;
	CEdit m_edit_output;
	CEdit m_edit_scope;
	CEdit m_edit_status;

	afx_msg void OnClickedButtonLoginScope();
	afx_msg void OnSelchangeComboFormat();
	afx_msg void OnSelchangeComboScope();
	CEdit m_edit_fileid;
//	afx_msg void OnEditchangeComboScope();
//	afx_msg void OnEditchangeComboFormat();
	int m_edit_value_feature;
	CButton m_ck_1login;
	CButton m_ck_2loginscope;
	CButton m_ck_cycle;
//	CButton m_btn_start;
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonStop();
	afx_msg void OnClickedCheckCycle();
	CButton m_ck_3getinfo;
	CButton m_ck_4read;
	CButton m_ck_5write;
	CButton m_ck_6encrypt;
	CButton m_ck_7decrypt;
	CButton m_ck_8logout;
	CButton m_btn_start;
	CButton m_btn_stop;
	CEdit m_edit_cyclecount;
	CEdit m_edit_sleeptime;
};
