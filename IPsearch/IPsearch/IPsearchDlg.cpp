
// IPsearchDlg.cpp: 实现文件
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "framework.h"
#include "IPsearch.h"
#include "IPsearchDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include<windows.h>
#include<winsock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CIPsearchDlg 对话框



CIPsearchDlg::CIPsearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IPSEARCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPsearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_SHOW, m_lst);
	DDX_Control(pDX, EDT_IP, m_domain);
	DDX_Control(pDX, LST_NAME, m_lstName);
}

BEGIN_MESSAGE_MAP(CIPsearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_SEARCH, &CIPsearchDlg::OnBnClickedSearch)
END_MESSAGE_MAP()


// CIPsearchDlg 消息处理程序

BOOL CIPsearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	m_lstName.InsertColumn(0, "host别名", LVCFMT_LEFT, 640);
	m_lst.InsertColumn(0, "域名对应IP地址", LVCFMT_LEFT, 640);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIPsearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPsearchDlg::OnPaint()
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
HCURSOR CIPsearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIPsearchDlg::OnBnClickedSearch()
{
	m_lst.DeleteAllItems();
	m_lstName.DeleteAllItems();

	CString DoMain;
	GetDlgItem(EDT_IP)->GetWindowText(DoMain);

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct hostent* host = gethostbyname(DoMain);

	if (!host)
	{
		AfxMessageBox("Get IpAddres error !!");
	}
	
	for (int i = 0; host->h_aliases[i]; i++) {
		//printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
		m_lstName.InsertItem(i, host->h_aliases[i]);
	}

	for (int i = 0; host->h_addr_list[i]; i++)
	{
		//cout<< inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) <<endl;
		m_lst.InsertItem(i,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	}


}
	
