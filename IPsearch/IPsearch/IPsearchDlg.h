
// IPsearchDlg.h: 头文件
//

#pragma once


// CIPsearchDlg 对话框
class CIPsearchDlg : public CDialogEx
{
// 构造
public:
	CIPsearchDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IPSEARCH_DIALOG };
#endif

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
public:
	afx_msg void OnBnClickedSearch();
	CListCtrl m_lst;
	CEdit m_domain;
	CListCtrl m_lstName;
};
