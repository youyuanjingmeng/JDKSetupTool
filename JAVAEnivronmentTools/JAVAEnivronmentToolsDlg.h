
// JAVAEnivronmentToolsDlg.h : header file
//

#pragma once
#include "stdafx.h"
#include <string>
enum CLASS_PATH_TYPE
{
	kJAVA_HOME,
	kJAVA_CLASS_PATH,
	kJAVA_PATH,
};

// CJAVAEnivronmentToolsDlg dialog
class CJAVAEnivronmentToolsDlg : public CDialogEx
{
// Construction
public:
	CJAVAEnivronmentToolsDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedJdkpathButton();

	bool WriteEnvironmentPathToOS(int nType);

// Dialog Data
	enum { IDD = IDD_JAVAENIVRONMENTTOOLS_DIALOG };

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
	CString m_strJavaHome;
	CString m_strJavaClassPath;
	CString m_strJavaPath;
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
