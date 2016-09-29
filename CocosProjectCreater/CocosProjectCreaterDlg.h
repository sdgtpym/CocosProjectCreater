
// CocosProjectCreaterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>


// CCocosProjectCreaterDlg �Ի���
class CCocosProjectCreaterDlg : public CDialogEx
{
// ����
public:
	CCocosProjectCreaterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COCOSPROJECTCREATER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// Դ����Ŀ¼
	CString m_strSourcePath;
	// ��Ŀ����Ŀ¼
	CString m_strTargetPath;
	// ������������
	CString m_strDevelopeLanguage;
	// �������Կ���
	CComboBox m_ctrDevelopeLanguage;
	// ��Ŀ����
	CString m_strTargetName;
	// ������
	CString m_strPackdgeName;

public:
	afx_msg void OnBnClickedButtonCreateProject();
	afx_msg void OnBnClickedButtonBrowseSourcePath();
	afx_msg void OnBnClickedButtonBrowseTargetPath();
	afx_msg void OnBnClickedCancel();
};
