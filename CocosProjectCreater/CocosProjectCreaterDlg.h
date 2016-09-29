
// CocosProjectCreaterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>


// CCocosProjectCreaterDlg 对话框
class CCocosProjectCreaterDlg : public CDialogEx
{
// 构造
public:
	CCocosProjectCreaterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COCOSPROJECTCREATER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CString GetPath();
	CString GetLogInfo(CString fileContext, CString key);
	std::string CStringToGString(CString str);
	void CreateProgress(CString cmd);

private:
	// 源代码目录
	CString m_strSourcePath;
	// 项目生成目录
	CString m_strTargetPath;
	// 开发语言类型
	CString m_strDevelopeLanguage;
	// 开发语言控制
	CComboBox m_ctrDevelopeLanguage;
	// 项目名称
	CString m_strTargetName;
	// 包名称
	CString m_strPackdgeName;

public:
	afx_msg void OnBnClickedButtonCreateProject();
	afx_msg void OnBnClickedButtonBrowseSourcePath();
	afx_msg void OnBnClickedButtonBrowseTargetPath();
	afx_msg void OnBnClickedCancel();
};
