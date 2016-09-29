
// CocosProjectCreaterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CocosProjectCreater.h"
#include "CocosProjectCreaterDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString gstrDevelopLanguageKey = _T("Develope Language");
CString gstrPackdgeNameKey = _T("Packdge Name");
CString gstrSourcePath = _T("Source Path");
CString gstrTargetPath = _T("Project Path");
CString gstrLogFileName = _T("./runlog.log");
//m_strDevelopeLanguage = GetLogInfo(fileContext, _T("Develope Language"));
//m_strPackdgeName = GetLogInfo(fileContext, _T("Packdge Name"));
//m_strSourcePath = GetLogInfo(fileContext, _T("Source Path"));
////m_strTargetName = GetLogInfo(fileContext, _T("Project Name"));
//m_strTargetPath = GetLogInfo(fileContext, _T("Project Path"));

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCocosProjectCreaterDlg 对话框



CCocosProjectCreaterDlg::CCocosProjectCreaterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocosProjectCreaterDlg::IDD, pParent)
	, m_strSourcePath(_T(""))
	, m_strTargetPath(_T(""))
	, m_strDevelopeLanguage(_T(""))
	, m_strTargetName(_T(""))
	, m_strPackdgeName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCocosProjectCreaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SOURCE_PATH, m_strSourcePath);
	DDX_Text(pDX, IDC_EDIT_TARGET_PATH, m_strTargetPath);
	DDX_CBString(pDX, IDC_COMBO_DEVELOPE_LANGUAGE, m_strDevelopeLanguage);
	DDX_Control(pDX, IDC_COMBO_DEVELOPE_LANGUAGE, m_ctrDevelopeLanguage);
	DDX_Text(pDX, IDC_EDIT_TARGET_NAME, m_strTargetName);
	DDX_Text(pDX, IDC_EDIT_PACKDGE_NAME, m_strPackdgeName);
}

BEGIN_MESSAGE_MAP(CCocosProjectCreaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_PROJECT, &CCocosProjectCreaterDlg::OnBnClickedButtonCreateProject)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_SOURCE_PATH, &CCocosProjectCreaterDlg::OnBnClickedButtonBrowseSourcePath)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_TARGET_PATH, &CCocosProjectCreaterDlg::OnBnClickedButtonBrowseTargetPath)
	ON_BN_CLICKED(IDCANCEL, &CCocosProjectCreaterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCocosProjectCreaterDlg 消息处理程序

BOOL CCocosProjectCreaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	UpdateData(TRUE);
	m_strDevelopeLanguage = "cpp";
	m_strPackdgeName = "com.freesoft.org";
	CStdioFile file;
	if (file.Open(gstrLogFileName, CFile::modeRead))
	{
		//CString fileContext;
		//int ret = file.ReadString(fileContext);
		char *buff = new char[file.GetLength() + 1];
		memset(buff, 0, file.GetLength() + 1);
		int ret = file.Read(buff, file.GetLength());
		CString fileContext(buff);
		if (ret)
		{
			m_strDevelopeLanguage = GetLogInfo(fileContext, gstrDevelopLanguageKey);
			m_strPackdgeName = GetLogInfo(fileContext, gstrPackdgeNameKey);
			m_strSourcePath = GetLogInfo(fileContext, gstrSourcePath);
			m_strTargetPath = GetLogInfo(fileContext, gstrTargetPath);
		}
		file.Close();
	}

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCocosProjectCreaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCocosProjectCreaterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCocosProjectCreaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCocosProjectCreaterDlg::OnBnClickedButtonCreateProject()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strCocos_py = CString("tools\\cocos2d-console\\bin\\cocos.py");
	
	UpdateData(TRUE);
	UpdateData(FALSE);
	if (m_strDevelopeLanguage.IsEmpty() 
		|| m_strPackdgeName.IsEmpty() 
		|| m_strSourcePath.IsEmpty() 
		|| m_strTargetName.IsEmpty()
		|| m_strTargetPath.IsEmpty())
	{
		return;
	}
	CString strCmd = CString("python ");
	strCmd.Append(m_strSourcePath + strCocos_py + " new " + m_strTargetName);
	strCmd.Append(CString(" -p ") + m_strPackdgeName);
	strCmd.Append(CString(" -l ") + m_strDevelopeLanguage);
	strCmd.Append(CString(" -d ") + m_strTargetPath);
	
	CString cmdFile = _T("create.bat");
	CStdioFile file;
	file.Open(cmdFile, CFile::modeCreate|CFile::modeWrite);
	file.WriteString(strCmd);
	file.Close();

	// 执行脚本文件
	CreateProgress(cmdFile);

	// 执行完之后删除生成的文件
	remove(CStringToGString(cmdFile).c_str());
}


void CCocosProjectCreaterDlg::OnBnClickedButtonBrowseSourcePath()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath = GetPath();
	if (!strPath.IsEmpty())
	{
		m_strSourcePath = strPath;
	}
	UpdateData(FALSE);
	
}


void CCocosProjectCreaterDlg::OnBnClickedButtonBrowseTargetPath()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath = GetPath();
	if (!strPath.IsEmpty())
	{
		m_strTargetPath = strPath;
	}
	UpdateData(FALSE);
}

CString CCocosProjectCreaterDlg::GetPath()
{
	static TCHAR strDirName[MAX_PATH];

	BROWSEINFO bi;
	CString szString = TEXT("选择文件夹");
	bi.hwndOwner = ::GetFocus();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = strDirName;
	bi.lpszTitle = szString;
	bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&bi);
	if (pItemIDList == NULL)
	{
		return CString("");
	}

	::SHGetPathFromIDList(pItemIDList, strDirName);

	CString str = strDirName;
	if (str != "" && str.Right(1) != '\\')
		str += '\\';
	return str;
}

CString CCocosProjectCreaterDlg::GetLogInfo(CString fileContext, CString key)
{
	CString findResult;
	size_t posOfKey = fileContext.Find(key);
	if (posOfKey != -1)
	{
		size_t posOfEnd = fileContext.Find(';', posOfKey);
		findResult = fileContext.Mid(posOfKey + key.GetLength() + 1, posOfEnd - posOfKey - key.GetLength() - 1);
	}

	return findResult;
}


void CCocosProjectCreaterDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CStdioFile file;
	if (file.Open(gstrLogFileName, CFile::modeCreate | CFile::modeWrite))
	{
		file.WriteString(gstrDevelopLanguageKey + _T("=") + m_strDevelopeLanguage + _T(";\n"));
		file.WriteString(gstrPackdgeNameKey + _T("=") + m_strPackdgeName + _T(";\n"));
		file.WriteString(gstrSourcePath + _T("=") + m_strSourcePath + _T(";\n"));
		file.WriteString(gstrTargetPath + _T("=") + m_strTargetPath + _T(";\n"));
		file.Close();
	}
	UpdateData(FALSE);


	CDialogEx::OnCancel();
}
std::string CCocosProjectCreaterDlg::CStringToGString(CString str)
{
	std::string convertStr;
	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		convertStr += ((char)str.GetAt(i));
	}
	return convertStr;
}

void CCocosProjectCreaterDlg::CreateProgress(CString cmd)
{
	LPWSTR szCmdLine = (LPWSTR)(LPCTSTR)cmd;
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));

	si.cb = sizeof(si);
	si.wShowWindow = FALSE;
	si.dwFlags = STARTF_USESHOWWINDOW;

	BOOL ret = ::CreateProcess(
		NULL,
		szCmdLine,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);

	//释放句柄，否则新进程将无法退出
	if (ret)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		::CloseHandle(pi.hProcess);
		::CloseHandle(pi.hThread);
	}
}