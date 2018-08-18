
// JAVAEnivronmentToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JAVAEnivronmentTools.h"
#include "JAVAEnivronmentToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define JAVA_KEYNAME_CLASSPATH "CLASSPATH"
#define JAVA_KEYNAME_HOME "JAVA_HOME"
#define JAVA_KEYNAME_PATH "Path"
#define REGEDIT_COMM_PATH "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"

#define INIT_TOTALBYTES 4096
#define BYTEINCREMENT	2048


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


// CJAVAEnivronmentToolsDlg dialog



CJAVAEnivronmentToolsDlg::CJAVAEnivronmentToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJAVAEnivronmentToolsDlg::IDD, pParent)
	, m_strJavaHome(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_NAIN_ICON);
}

void CJAVAEnivronmentToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_JDKPATH_EDIT, m_strJavaHome);
}

BEGIN_MESSAGE_MAP(CJAVAEnivronmentToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CJAVAEnivronmentToolsDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_JDKPATH_BUTTON, &CJAVAEnivronmentToolsDlg::OnBnClickedJdkpathButton)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CJAVAEnivronmentToolsDlg message handlers

BOOL CJAVAEnivronmentToolsDlg::OnInitDialog()
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
	//SetDlgItemText(IDC_JDKPATH_EDIT, "Please choose JDK Path...");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJAVAEnivronmentToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJAVAEnivronmentToolsDlg::OnPaint()
{
	CRect   rc;
	GetClientRect(&rc);// 获取客户区
	CPaintDC dc(this);
	dc.FillSolidRect(&rc, RGB(255, 255, 255));   // 填充客户区颜色
	CDialog::OnPaint();
// 	if (IsIconic())
// 	{
// 		CPaintDC dc(this); // device context for painting
// 
// 		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
// 
// 		// Center icon in client rectangle
// 		int cxIcon = GetSystemMetrics(SM_CXICON);
// 		int cyIcon = GetSystemMetrics(SM_CYICON);
// 		CRect rect;
// 		GetClientRect(&rect);
// 		int x = (rect.Width() - cxIcon + 1) / 2;
// 		int y = (rect.Height() - cyIcon + 1) / 2;
// 
// 		// Draw the icon
// 		dc.DrawIcon(x, y, m_hIcon);
// 	}
// 	else
// 	{
// 		CRect   rc;
// 		GetClientRect(&rc);// 获取客户区
// 		CPaintDC dc(this);
// 		dc.FillSolidRect(&rc, RGB(255, 255, 255));   // 填充客户区颜色
// 		CDialog::OnPaint();
// 	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJAVAEnivronmentToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJAVAEnivronmentToolsDlg::OnBnClickedSaveButton()
{
	//保存变量路径
	GetDlgItemText(IDC_JDKPATH_EDIT, m_strJavaHome);
	if (m_strJavaHome.IsEmpty())
	{
		MessageBox("Please choose the JDK path first");
		return;
	}
	m_strJavaClassPath = ".;%JAVA_HOME%\\lib\\dt.jar;%JAVA_HOME%\\lib\\tools.jar";
	m_strJavaPath = "%JAVA_HOME%\\bin;%JAVA_HOME%\\jre\\bin";
	
	
	std::string strAllFile = m_strJavaHome + "\\bin\\java.exe";
 	WIN32_FIND_DATA wfd;
 	HANDLE hFile = FindFirstFile(strAllFile.c_str(), &wfd);
	
 	if (hFile == INVALID_HANDLE_VALUE)
 	{
		DWORD dwError = GetLastError();
 		MessageBox("Please choose the right JDK path");
 		return;
 	}
	if (m_strJavaHome.IsEmpty())
	{
		MessageBox("Please choose the path of JDK installed...");
		return;
	}
	if (!WriteEnvironmentPathToOS(kJAVA_HOME) || !WriteEnvironmentPathToOS(kJAVA_PATH)
		|| !WriteEnvironmentPathToOS(kJAVA_CLASS_PATH))
	{
		MessageBox("Save Java Environment Error...");
		return;
	}
	else
	{
		MessageBox("Save Java Environment Successful...");
		return;
	}
}


void CJAVAEnivronmentToolsDlg::OnBnClickedJdkpathButton()
{
	//选择JDK安装目录
	char szDir[MAX_PATH] = {0};
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.iImage = 0;
	bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST lpi = SHBrowseForFolder(&bi);
	if (NULL == lpi)
	{
		//MessageBox("Choose a Folder");
		return;
	}
	CString strPath;
	SHGetPathFromIDList(lpi, strPath.GetBuffer(MAX_PATH));
	strPath.ReleaseBuffer();

	SetDlgItemText(IDC_JDKPATH_EDIT, strPath);
}


bool CJAVAEnivronmentToolsDlg::WriteEnvironmentPathToOS(int nType)
{
	bool bRet = true;
	std::string strKeyValueName("");
	CString strKeyValue("");
	DWORD dwRegType = 0;
	switch (nType)
	{
	case kJAVA_HOME:
		strKeyValueName = JAVA_KEYNAME_HOME;
		strKeyValue = m_strJavaHome;
		dwRegType = REG_SZ;
		break;
	case kJAVA_CLASS_PATH:
		strKeyValueName = JAVA_KEYNAME_CLASSPATH;
		strKeyValue = m_strJavaClassPath;
		dwRegType = REG_EXPAND_SZ;
		break;
	case kJAVA_PATH:
		strKeyValueName = JAVA_KEYNAME_PATH;
		strKeyValue = m_strJavaPath;
		dwRegType = REG_EXPAND_SZ;
		break;
	default:
		break;
	}
	HKEY hkey;
	DWORD dwType;
	DWORD cbData = INIT_TOTALBYTES;	
	DWORD dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		REGEDIT_COMM_PATH,
		NULL, KEY_ALL_ACCESS, &hkey);
	if (ERROR_SUCCESS == dwRet)
	{
		//打开注册表成功
		char szKeyValue[INIT_TOTALBYTES] = { 0 };
		
		DWORD dwQueryRet = RegQueryValueEx(hkey, strKeyValueName.c_str(), NULL, &dwType, 
			(LPBYTE)szKeyValue, &cbData);
		if (ERROR_FILE_NOT_FOUND == dwQueryRet)
		{
			//不存在键，创建注册表
			DWORD dwSetValue = RegSetValueEx(hkey, strKeyValueName.c_str(), 0, dwRegType, (BYTE *)(LPCTSTR)strKeyValue,
				strKeyValue.GetLength());
			//WriteLog("RegSetValueEx 01 ...%d", dwSetValue);
		}
		else if (dwQueryRet == ERROR_SUCCESS)
		{
			while (dwQueryRet == ERROR_MORE_DATA)
			{
				cbData += BYTEINCREMENT;
				dwQueryRet = RegQueryValueEx(hkey, strKeyValueName.c_str(), NULL, &dwType,
					(LPBYTE)szKeyValue, &cbData);
			}
			std::string strQueryKeyValue = szKeyValue;
		
			//判断是否已经包含环境变量，
			auto iter = strQueryKeyValue.find(strKeyValue);
			if (iter == std::string::npos)
			{
				//添加
				CString strValue = szKeyValue;
				strValue += ";" + strKeyValue;
				DWORD dwSetValue = RegSetValueEx(hkey, strKeyValueName.c_str(), 0, dwRegType, (BYTE *)(LPCTSTR)strValue,
					strValue.GetLength());
				//WriteLog("RegSetValueEx 02 ...%d", dwSetValue);
			}
		}
		else
		{
			//WriteLog("RegOpenKeyEx Errod Info %d", dwRet);
			std::string strErrMsg = "RegOpenKeyEx Errod Info ";
			strErrMsg += std::to_string(dwRet);
			OutputDebugString(strErrMsg.c_str());
			MessageBox("Unknow Error...");
			bRet = false;
		}
		RegCloseKey(hkey);

		DWORD dwResult = 0;
		int nRet = SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (LPARAM)"Environment", SMTO_NOTIMEOUTIFNOTHUNG, 1000, &dwResult);
		if (0 == nRet)
		{
			std::string strErrMsg = "SendMessageTimeout" + std::to_string(nRet);
			MessageBox(strErrMsg.c_str());
			bRet = false;
		}

	}
	else
	{
		std::string strErrMsg = "RegOpenKeyEx Errod Info ";
		strErrMsg += std::to_string(dwRet);
		OutputDebugString(strErrMsg.c_str());
		bRet = false;
	}
	return bRet;
}

HBRUSH CJAVAEnivronmentToolsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	int nChangedCtrlID = pWnd->GetDlgCtrlID();
	if (nChangedCtrlID == IDC_STATIC_JDKPATH || nChangedCtrlID == IDC_STATIC
		|| nChangedCtrlID == IDC_JDKPATH_EDIT)
	{
		pDC->SetBkColor(RGB(255,255,255));
		hbr = CreateSolidBrush(RGB(255, 255, 255));
		return hbr;
	}
	
	return hbr;
}


BOOL CJAVAEnivronmentToolsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
