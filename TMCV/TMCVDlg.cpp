
// TMCVDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TMCV.h"
#include "TMCVDlg.h"
#include "afxdialogex.h"
#include "Circle.h"

#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
#include <vector>

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
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTMCVDlg 对话框



CTMCVDlg::CTMCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TMCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTMCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cb);
	DDX_Control(pDX, IDC_BUTTONCV, bcv);
	DDX_Control(pDX, IDC_BUTTONHR, bhr);
	DDX_Control(pDX, IDC_BUTTONSR, bsr);
	DDX_Control(pDX, IDC_BUTTONREV, brev);
	DDX_Control(pDX, IDC_CHECK1, ck1);
	DDX_Control(pDX, IDC_CHECK2, ck2);
	DDX_Control(pDX, IDC_CHECK4, ck4);
	DDX_Control(pDX, IDC_BUTTONRDM, brdm);
	DDX_Control(pDX, IDC_BUTTONHR2, bhr2);
	DDX_Control(pDX, IDC_EDIT3, ed);
}

BEGIN_MESSAGE_MAP(CTMCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CTMCVDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONCV, &CTMCVDlg::OnBnClickedButtoncv)
	ON_EN_CHANGE(IDC_EDIT3, &CTMCVDlg::OnEnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTMCVDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTONHR, &CTMCVDlg::OnBnClickedButtonhr)
	ON_BN_CLICKED(IDC_BUTTONSR, &CTMCVDlg::OnBnClickedButtonsr)
	ON_BN_CLICKED(IDC_BUTTONSPAWN, &CTMCVDlg::OnBnClickedButtonspawn)
	ON_BN_CLICKED(IDC_CHECK2, &CTMCVDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK1, &CTMCVDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTONRDM, &CTMCVDlg::OnBnClickedButtonrdm)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTONREV, &CTMCVDlg::OnBnClickedButtonrev)
	ON_EN_CHANGE(IDC_EDIT5, &CTMCVDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTONHR2, &CTMCVDlg::OnBnClickedButtonhr2)
END_MESSAGE_MAP()


// CTMCVDlg 消息处理程序

BOOL CTMCVDlg::OnInitDialog()
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

	cb.AddString(_T("kddk 全换"));
	cb.AddString(_T("ddkk 全换"));

	ck1.SetCheck(1);
	ck2.SetCheck(1);

	SetDlgItemText(IDC_COMBO1, _T("kddk 全换"));
	SetDlgItemText(IDC_EDIT5, _T("1.0"));

	AppendText3(_T("作者：Edward_Tsui, QQ: 1872561401"));
	AppendText3(_T("\"删除原图绿线\"和\"自动平衡流速\"选项在大随/小随/反色功能中没有效果"));
	AppendText3(_T("OSU太鼓交流群：257231308"));


	ShowWindow(SW_NORMAL);
//	ShowWindow(SW_MAXIMIZE);

//	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTMCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTMCVDlg::OnPaint()
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
HCURSOR CTMCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString GetFileTitleFromFileName(const CString& path)
{
	int nPos = path.ReverseFind('\\');
	CString tmpStr(path);
	if (nPos != -1) {
		tmpStr = tmpStr.Right(path.GetLength() - nPos - 1);
	}

	//tmpStr: 0015.dat
	nPos = tmpStr.ReverseFind('.');
	if (nPos != -1) {
		tmpStr = tmpStr.Left(nPos);//tmpStr: 0015
	}

	return tmpStr;
}

CString GetFileTitleExceptDiffName(const CString& path)
{
	int nPos = path.ReverseFind('[');
	CString tmpStr(path);
	if (nPos != -1) {
		tmpStr = tmpStr.Left(nPos);
	}
	return tmpStr;
}

CString GetFilePathExceptFileName(const CString& path)
{
	int nPos = path.ReverseFind('\\');
	CString tmpStr(path);
	if (nPos != -1) {
		tmpStr = tmpStr.Left(nPos + 1);
	}
	return tmpStr;
}

//void writeh(CFile& fp, CString& str)
//{
//	fp.Write(str.GetBuffer(), str.GetLength() << 1);
//}

bool isRedLine(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 7)
		{
			if (token == "1")
			{
				redline = true;
			}
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return redline;
}

std::string getNoteStamp(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 3)
		{
			return token;
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return std::string("");
}

int getTimeStamp(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 1)
		{
			return std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

int getHitType(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 4)
		{
			return std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

int getCircleStamp(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 3)
		{
			return std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

int getSliderEndStamp(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0, temp = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 3)
		{
			temp = std::stoi(token);
		}
		if (k == 8)
		{
			temp += std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return temp;
}

int getSpinnerEndStamp(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0, temp = 0;
	bool redline = false;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 6)
		{
			return std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

bool isNote(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 6)
		{
			return false;
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return true;
}

int getColor(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	std::string token;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 5)
		{
			return std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

bool cmp(const std::pair<int, int> a, const std::pair<int, int> b)
{
	return a.first > b.first;
}

double getAllRoundBPM(std::vector<std::pair<int, int>> a, std::vector<double> b)
{
	std::vector<std::pair<int, int>> c;
	for (size_t p = 0; p < a.size(); p++)
	{
		c.push_back(std::pair<int, double>(a[p].second - a[p].first, b[p]));
	}
	std::sort(c.begin(), c.end(), cmp);
	return c[0].second;
}

double getBPM(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	bool redline = false;
	std::string token;
	double tempbpm = 0.0;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 2)
		{
			tempbpm = std::stod(token);
			tempbpm = 1.0 / tempbpm;
			tempbpm *= 60000.0;
			return tempbpm;
		}
		parszline.erase(0, pos + delimiter.length());
	}
	return -1;
}

std::string getBalancedGreenLine(std::string parszline, std::vector<std::pair<int, int>> t, std::vector<double> b)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	std::string temp = parszline;
	double bpm = 0, cbpm = 0;
	double greens = 0;
	bool redline = false;
	std::string token, res;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		switch (k)
		{
		case 1:
			if (token[0] == '-')
			{
				res += "0,";
			}
			else
			{
				res += token;
				res += ",";
			}
			break;
		case 2:
			bpm = getAllRoundBPM(t, b);
			cbpm = getBPM(temp);
			greens = -1.0 * ((cbpm * 100.0) / bpm);
			res += std::to_string(greens);
			res += ",";
			break;
		case 4:
			res += std::string("2,");
			break;
		case 7:
			res += std::string("0,");
			break;
		case 8:
			res += token;
			break;
		default:
			res += token;
			res += ",";
			break;
		}

		parszline.erase(0, pos + delimiter.length());
	}
	res += parszline;
	return res;
}

double getCurrentBPM(std::string parszline, const std::vector<std::pair<int, int>> t, const std::vector<double> b)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	int ppos = 0;
	bool redline = false;
	std::string token;
	double tempbpm = 0.0;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		if (k == 1)
		{
			ppos = std::stoi(token);
		}
		parszline.erase(0, pos + delimiter.length());
	}
	for (int i = 0; i < t.size(); i++)
		if (t[i].first <= ppos && t[i].second > ppos)
			return b[i];
	return -1;
}

void CTMCVDlg::InsertNote(std::string parszline, int& lr, std::ostream& outF)
{
	lr ^= 1;
	std::string res, notestamp;
	notestamp = getNoteStamp(parszline);
	int noteColor = getColor(parszline);
	if (lr)
	{
		switch (noteColor)
		{
		case 0:
			outF << "320,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "320,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "64,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "448,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "64,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "64,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (noteColor)
		{
		case 0:
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "64,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "192,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			outF << "320,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			outF << "64,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "64,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "64,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			outF << "64,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "64,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
}

void CTMCVDlg::InsertNoteNf(std::string parszline, int& lr, std::ostream& outF)
{
	lr ^= 1;
	std::string res, notestamp;
	notestamp = getNoteStamp(parszline);
	int noteColor = getColor(parszline);
	if (lr)
	{
		switch (noteColor)
		{
		case 0:
			outF << "320,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "320,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "448,192," + notestamp + ",1,6,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "448,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "448,192," + notestamp + ",1,12,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "448,192," + notestamp + ",1,14,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (noteColor)
		{
		case 0:
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "64,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "192,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "64,192," + notestamp + ",1,6,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "64,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "64,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "64,192," + notestamp + ",1,12,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "64,192," + notestamp + ",1,14,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
}

void CTMCVDlg::InsertNoteDdKk(std::string parszline, int& lr, std::ostream& outF)
{
	lr ^= 1;
	std::string res, notestamp;
	notestamp = getNoteStamp(parszline);
	int noteColor = getColor(parszline);
	if (lr)
	{
		switch (noteColor)
		{
		case 0:
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "320,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "64,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "320,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "320,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "320,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "320,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "320,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (noteColor)
		{
		case 0:
			outF << "64,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "192,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			outF << "64,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			outF << "320,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "448,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			outF << "320,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "320,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
}

void CTMCVDlg::InsertNoteDdKkNf(std::string parszline, int& lr, std::ostream& outF)
{
	lr ^= 1;
	std::string res, notestamp;
	notestamp = getNoteStamp(parszline);
	int noteColor = getColor(parszline);
	if (lr)
	{
		switch (noteColor)
		{
		case 0:
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "320,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "192,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "320,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "320,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "320,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "320,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "320,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (noteColor)
		{
		case 0:
			outF << "64,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 2:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 4:
			outF << "64,192," + notestamp + ",1,0,0:0:0:0:" << std::endl;
			break;
		case 6:
			outF << "448,192," + notestamp + ",1,2,0:0:0:0:" << std::endl;
			break;
		case 8:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 10:
			outF << "448,192," + notestamp + ",1,10,0:0:0:0:" << std::endl;
			break;
		case 12:
			outF << "448,192," + notestamp + ",1,8,0:0:0:0:" << std::endl;
			break;
		case 14:
			outF << "448,192," + notestamp + ",1,4,0:0:0:0:" << std::endl;
			break;
		default:
			break;
		}
	}
}


void CTMCVDlg::FileIO()
{
//	Getting source file path to read and destination file path to write
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	AppendText3(_T("destpath is: ") + destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	AppendText3(CString("despath is: ") + CString(despath.c_str()));
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
//	CStdioFile outF(destpath + destname + _T(".osu"), CFile::modeWrite | CFile::modeCreate);
//	CStdioFile inF(sourcepath, CFile::modeRead | CFile::typeBinary);

//	Operation Log
	AppendText3(_T("Created and opened file \"") + destname + _T(".osu\""));
	AppendText3(_T("Converting..."));

	std::string szline, temp;
// ~ [TimingPoints]
	while (std::getline(inF, szline))
	{
//		AppendText3(CString(szline.c_str()));	// Just debug for what it read
		if (szline.find("Mode") != -1)
		{
			temp = "Mode:3";
			outF << temp << std::endl;
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("CircleSize") != -1)
		{
			temp = "CircleSize:4";
			outF << temp << std::endl;
		}
		else if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("TimingPoints") != -1)
		{
			break;
		}
	}
// [TimingPoints] ~ [HitObjects]
	while (std::getline(inF, szline))
	{
		if ((szline[0] >= '0' && szline[0] <= '9') || szline[0] == '-')
		{
			if (isRedLine(szline))
			{
				if (!ck2.GetCheck())
				{
					outF << szline << std::endl;
//					int t = avoidTiming;
//					CString st;
//					st.Format(_T("%d"), t);
//					AppendText3(_T("hahahahahahaha") + st);
				}
				else
				{
					outF << szline << std::endl
						<< getBalancedGreenLine(szline, BpmScaling, BpmS) << std::endl;
				}
			}
			else // green line
			{
				if (!ck1.GetCheck())
				{
					outF << szline << std::endl;
				}
				else
					continue;
			}
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
// [HitObjects] ~
	outF << std::endl << "[HitObjects]" << std::endl;
	int lr = 0; // 0 left 1 right
	while (std::getline(inF, szline))
	{
		if (isNote(szline))
		{
			CString PlayStyle, noFinishers;
			GetDlgItemText(IDC_COMBO1, PlayStyle);
			std::string playstyle = CW2A(PlayStyle.GetBuffer());
			if (playstyle == "kddk 全换" && !ck4.GetCheck())
			{
				InsertNote(szline, lr, outF);
			}
			else if (playstyle == "kddk 全换" && ck4.GetCheck())
			{
				InsertNoteNf(szline, lr, outF);
			}
			else if (playstyle == "ddkk 全换" && !ck4.GetCheck())
			{
				InsertNoteDdKk(szline, lr, outF);
			}
			else if (playstyle == "ddkk 全换" && ck4.GetCheck())
			{
				InsertNoteDdKkNf(szline, lr, outF);
			}
		}
		else // spinner, slider
		{
			continue;
		}
	}
	CString alerting, e2;
	alerting = _T("生成了一个mania谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	AppendText3(alerting);
}

void CTMCVDlg::OnBnClickedButtonopen()
{
	TCHAR szFilter[] = _T("OSU Files (*.osu) |*.osu||");
	CFileDialog filedlg(TRUE, _T("osu"), NULL, 0, szFilter, this);
	CString strFilePath, filename;
	int idx;
	if (IDOK == filedlg.DoModal())
	{
		strFilePath = filedlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
		
		filename = GetFileTitleFromFileName(strFilePath);
		idx = filename.GetLength();
		filename = filename.Left(idx - 1);
		filename += _T("_CV]");
		idx = filename.ReverseFind('[');
		filename = filename.Right(filename.GetLength() - idx - 1);
		idx = filename.Find(']');
		filename = filename.Left(idx);

		SetDlgItemText(IDC_EDIT2, filename);
		SetDlgItemText(IDC_EDIT5, _T("1"));
		AppendText3(CString("Read file: ") + strFilePath);

		FileFlush();
	}
}

void CTMCVDlg::FileFlush()
{
	CString sourcepath;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::ifstream inF;
	bool InvFile = false;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	std::string szline, temp;
//	int k = 0;
	// find original hp and od data
	while (std::getline(inF, szline))
	{
		if (szline.find("Mode") != -1)
		{
			temp = szline;
			int t = temp.length(), i = 0, j = 0;
			for (i = 0; i < t; i++)
				if (temp[i] >= '0' && temp[i] <= '9')
				{
					for (j = i + 1; j < t; j++)
					{
						if (temp[j] == '.' || (temp[j] >= '0' && temp[j] <= '9'))
						{
							continue;
						}
						else
						{
							break;
						}
					}
					break;
				}
			std::string st = temp.substr(i, j);
			if (st != "1")
			{
				InvFile = true;
				AppendText3(CString("Error: Please Select a *OSU TAIKO* map!"));
				break;
			}
			else
			{
				bcv.EnableWindow(TRUE);
				bhr.EnableWindow(TRUE);
				bsr.EnableWindow(TRUE);
				brev.EnableWindow(TRUE);
				brdm.EnableWindow(TRUE);
				bhr2.EnableWindow(TRUE);
			}
		}
		if (szline.find("HPDrainRate") != -1)
		{
			temp = szline;
			int t = temp.length(), i = 0, j = 0;
			for (i = 0; i < t; i++)
				if (temp[i] >= '0' && temp[i] <= '9')
				{
					for (j = i + 1; j < t; j++)
					{
						if (temp[j] == '.' || (temp[j] >= '0' && temp[j] <= '9'))
						{
							continue;
						}
						else
						{
							break;
						}
					}
					break;
				}
			std::string st = temp.substr(i, j);
			AppendText3(CString("Original HP: ") + CString(st.c_str()));
			SetDlgItemText(IDC_EDITHP, CString(st.c_str()));
	//		k++;
		}
		if (szline.find("OverallDifficulty") != -1)
		{
			temp = szline;
			int t = temp.length(), i = 0, j = 0;
			for (i = 0; i < t; i++)
				if (temp[i] >= '0' && temp[i] <= '9')
				{
					for (j = i + 1; j < t; j++)
					{
						if (temp[j] == '.' || (temp[j] >= '0' && temp[j] <= '9'))
						{
							continue;
						}
						else
						{
							break;
						}
					}
					break;
				}
			std::string st = temp.substr(i, j);
			AppendText3(CString("Original OD: ") + CString(st.c_str()));
			SetDlgItemText(IDC_EDITOD, CString(st.c_str()));
	//		k++;
		}
		if (szline.find("TimingPoints") != -1)
		{
			break;
		}
	}
	// find all red lines.
	std::vector<std::pair<int, int>> RedlineTimes;
	std::vector<double> bpms;
	bpms.push_back(0.0);
	int prevTimeStamp = 0;
	while (std::getline(inF, szline))
	{
		if (std::isalnum(szline[0]) || szline[0] == '-')
		{
	//		AppendText3(CString(szline.c_str()));
			if (isRedLine(szline))
			{
				RedlineTimes.push_back(std::pair<int, int>(prevTimeStamp, getTimeStamp(szline)));
				bpms.push_back(getBPM(szline));
				CString str;
				str.Format(CString("prevTimeStamp: %d , TimeStamp: %d "), prevTimeStamp, getTimeStamp(szline));
		//		AppendText3(str);
				prevTimeStamp = getTimeStamp(szline);
				str.Format(CString("bpm: %lf"), getBPM(szline));
		//		AppendText3(str);
			}
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	if (InvFile)
	{
		return;
	}
	// find the end note's timestamp
	while (std::getline(inF, szline))
	{
		if (szline[0])
			temp = szline;
	}
	int objectType = getHitType(temp), finalEndStamp = 0;
	switch (objectType)
	{
	case 1:
		finalEndStamp = getCircleStamp(temp);
		break;
	case 2:
		finalEndStamp = getCircleStamp(temp);
		break;
	case 8:
		finalEndStamp = getSpinnerEndStamp(temp);
		break;
	default:
		break;
	}
	int tmp1 = (*(RedlineTimes.end() - 1)).second;
	RedlineTimes.push_back(std::pair<int, int>(tmp1, finalEndStamp));
	CString cstmp;
	cstmp.Format(_T("BaseBPM: %lf"), getAllRoundBPM(RedlineTimes, bpms));
	AppendText3(cstmp);
	basebpm = getAllRoundBPM(RedlineTimes, bpms);
	for (int index = 0; index < RedlineTimes.size(); index++)
	{
		BpmScaling.push_back(RedlineTimes[index]);
		BpmS.push_back(bpms[index]);

	}
/*	Debug:
	for (auto p = RedlineTimes.begin(); p != RedlineTimes.end(); p++)
	{	
		CString cstmp;
		cstmp.Format(_T("Range: %d to %d"), p->first, p->second);
		AppendText3(cstmp);
	}
*/
}

void CTMCVDlg::AppendText3(const CString &str)
{
	CString strText = _T("");
	GetDlgItemText(IDC_EDIT3, strText);
	strText += str;
	strText += _T("\r\n");
	SetDlgItemText(IDC_EDIT3, strText);
	((CEdit*)(GetDlgItem(IDC_EDIT3)))->LineScroll(ed.GetLineCount());
}

void CTMCVDlg::OnBnClickedButtoncv()
{
	CString	filepath, filetitle, filename;
	GetDlgItemText(IDC_EDIT1, filetitle);
	GetDlgItemText(IDC_EDIT1, filepath);
	CFileFind finder;
	BOOL working = finder.FindFile(filetitle);
	while (working)
	{
		working = finder.FindNextFileW();
		filetitle = finder.GetFileTitle();
	}
	AppendText3(_T("Opened File: ") + filetitle);
	filepath = GetFilePathExceptFileName(filepath);
	GetDlgItemText(IDC_EDIT2, filename);
	FileIO();
//	writeh(outf, testStr);
}


void CTMCVDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTMCVDlg::OnCbnSelchangeCombo1()
{
}



void CTMCVDlg::OnBnClickedButtonhr()
{
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
	std::string szline, temp;
	while (std::getline(inF, szline))
	{
		if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else if (szline.find("Mode") != -1)
		{
			if (szline.find("1") == -1)
			{
				AppendText3(_T("Error: 请提供一张太鼓谱面！"));
				return;
			}
			else
			{
				temp = "Mode:1";
				outF << temp << std::endl;
			}
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("TimingPoints") != -1)
		{
			break;
		}
	}

	// [TimingPoints] ~ [HitObjects]
	while (std::getline(inF, szline))
	{
		if ((szline[0] >= '0' && szline[0] <= '9') || szline[0] == '-')
		{
			if (isRedLine(szline))
			{
				if (!ck2.GetCheck())
				{
					outF << szline << std::endl;
				}
				else
				{
					outF << szline << std::endl
						<< getBalancedGreenLine(szline, BpmScaling, BpmS) << std::endl;
				}
			}
			else // green line
			{
				if (!ck1.GetCheck())
				{
					outF << szline << std::endl;
				}
				else
					continue;
			}
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	// [HitObjects] ~
	outF << std::endl << "[HitObjects]" << std::endl;
	while (std::getline(inF, szline))
	{
		if (isNote(szline))
		{
			Circle cr(szline);
			if (cr.isFinisher() && ck4.GetCheck())
			{
				cr.unFinisher();
			}
			outF << cr.getString() << std::endl;
		}
		else
			continue;
	}

	CString alerting, e2;
	alerting = _T("生成了一个等速谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	alerting += _T("，请注意，所有的滑条和转盘均被删除。后续版本可能会更新滑条适配方案");
	AppendText3(alerting);
}


void CTMCVDlg::OnBnClickedButtonsr()
{
	CString seedcs;
	std::default_random_engine ee(std::time(0));
	std::uniform_int_distribution<unsigned> uu(1000000, 9999999);
	unsigned tt = uu(ee);
	CString st;
	st.Format(_T("%d"), tt);
	GetDlgItemText(IDC_EDITRD, seedcs);
	int countred = 0, countblue = 0;
	if (seedcs.IsEmpty())
	{
		seedcs = st;
		AppendText3(_T("随机种子未给定，自动生成随机种子：") + seedcs);
	}
	if (seedcs != seedcs.SpanIncluding(CString("0123456789")))
	{
		AppendText3(_T("Error: 请在那个框里输入数字！"));
		return;
	}
	if (seedcs.GetLength() > 9)
	{
		AppendText3(_T("Error: 你输入的种子太大了"));
		return;
	}
	std::string seedst = CW2A(seedcs.GetBuffer());
	int seed = std::stoi(seedst);
	std::default_random_engine e(seed);
	std::uniform_int_distribution<unsigned> u(0, 1);
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
	std::string szline, temp;
	while (std::getline(inF, szline))
	{
		if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else if (szline.find("Mode") != -1)
		{
			if (szline.find("1") == -1)
			{
				AppendText3(_T("Error: 请提供一张太鼓谱面！"));
				return;
			}
			else
			{
				temp = "Mode:1";
				outF << temp << std::endl;
			}
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	while (std::getline(inF, szline))
	{
		if (isNote(szline))
		{
			std::string st2 = "szline: " + szline;
			Circle cr(szline);
			int color = u(e);
			int change = u(e);
			if (change)
			{
				if (color)
				{
					if (cr.isFinisher())
					{
						bool smalldk = ck4.GetCheck();
						if (smalldk)
						{
							cr.setDon();
						}
						else
						{
							cr.setDon();
							cr.setFinisher();
						}
					}
					else
					{
						cr.setDon();
					}
					countred++;
				}
				else
				{
					if (cr.isFinisher())
					{
						bool smalldk = ck4.GetCheck();
						if (smalldk)
						{
							cr.setKat();
						}
						else
						{
							cr.setKat();
							cr.setFinisher();
						}
					}
					else
					{
						cr.setKat();
					}
					countblue++;
				} // if color
				outF << cr.getString() << std::endl;
			} // if change
			else
			{
				if (cr.isDon())
				{
					countred++;
				}
				else
				{
					countblue++;
				}
				outF << szline << std::endl;
			}
		}
		else
		{
			outF << szline << std::endl;
		}
	} // while
	CString alerting, e2;
	std::string CtR = std::to_string(countred);
	std::string CtB = std::to_string(countblue);
	alerting = _T("生成了一个大随机谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	alerting += _T(", (红蓝比：");
	alerting += CString(CtR.c_str());
	alerting += _T(" : ");
	alerting += CString(CtB.c_str());
	alerting += _T(")");
	AppendText3(alerting);
}


void CTMCVDlg::OnBnClickedButtonspawn()
{
	std::default_random_engine e(std::time(0));
	std::uniform_int_distribution<unsigned> u(1000000, 9999999);
	unsigned t = u(e);
	CString st;
	st.Format(_T("%d"), t);
	SetDlgItemText(IDC_EDITRD, st);
}



void CTMCVDlg::OnBnClickedCheck2()
{
	if (IsDlgButtonChecked(IDC_CHECK2))
		avoidTiming = true;
	else
		avoidTiming = false;
//	CString st;
//	st.Format(_T("%d"), avoidTiming);
//	AppendText3(st);
}


void CTMCVDlg::OnBnClickedCheck1()
{
	if (IsDlgButtonChecked(IDC_CHECK1))
		avoidGreenLine = true;
	else
		avoidGreenLine = false;
}


void CTMCVDlg::OnBnClickedButtonrdm()
{
	CString seedcs;
	std::default_random_engine ee(std::time(0));
	std::uniform_int_distribution<unsigned> uu(1000000, 9999999);
	unsigned tt = uu(ee);
	CString st;
	st.Format(_T("%d"), tt);
	GetDlgItemText(IDC_EDITRD, seedcs);
	int countred = 0, countblue = 0;
	if (seedcs.IsEmpty())
	{
		seedcs = st;
		AppendText3(_T("随机种子未给定，自动生成随机种子：") + seedcs);
	}
	if (seedcs != seedcs.SpanIncluding(CString("0123456789")))
	{
		AppendText3(_T("Error: 请在那个框里输入数字！"));
		return;
	}
	if (seedcs.GetLength() > 9)
	{
		AppendText3(_T("Error: 你输入的种子太大了"));
		return;
	}
	std::string seedst = CW2A(seedcs.GetBuffer());
	int seed = std::stoi(seedst);
	std::default_random_engine e(seed);
	std::uniform_int_distribution<unsigned> u(0, 1);
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
	std::string szline, temp;
	while (std::getline(inF, szline))
	{
		if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else if (szline.find("Mode") != -1)
		{
			if (szline.find("1") == -1)
			{
				AppendText3(_T("Error: 请提供一张太鼓谱面！"));
				return;
			}
			else
			{
				temp = "Mode:1";
				outF << temp << std::endl;
			}
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	while (std::getline(inF, szline))
	{
		if (isNote(szline))
		{
			std::string st2 = "szline: " + szline;
			Circle cr(szline);
			int color = u(e);
			if (color)
			{
				if (cr.isFinisher())
				{
					bool smalldk = ck4.GetCheck();
					if (smalldk)
					{
						cr.setDon();
					}
					else
					{
						cr.setDon();
						cr.setFinisher();
					}
				}
				else
				{
					cr.setDon();
				}
				countred++;
			}
			else
			{
				if (cr.isFinisher())
				{
					bool smalldk = ck4.GetCheck();
					if (smalldk)
					{
						cr.setKat();
					}
					else
					{
						cr.setKat();
						cr.setFinisher();
					}
				}
				else
				{
					cr.setKat();
				}
				countblue++;
			}
			outF << cr.getString() << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
	} // while
	CString alerting, e2;
	std::string CtR = std::to_string(countred);
	std::string CtB = std::to_string(countblue);
	alerting = _T("生成了一个大随机谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	alerting += _T(", (红蓝比：");
	alerting += CString(CtR.c_str());
	alerting += _T(" : ");
	alerting += CString(CtB.c_str());
	alerting += _T(")");
	AppendText3(alerting);
}


void CAboutDlg::OnDropFiles(HDROP hDropInfo)
{
	// fuckyou

	CDialogEx::OnDropFiles(hDropInfo);
}


void CTMCVDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT filecount;
	CString strtmp;
	filecount = DragQueryFile(hDropInfo, 0xffffffff, NULL, 0);
	TCHAR xx[2011] = { 0 };
	for (UINT i = 0; i < filecount; i++)
	{
		DragQueryFile(hDropInfo, i, xx, MAX_PATH - 1);
		CFile file(xx, CFile::modeRead);
		strtmp = file.GetFilePath();
		SetDlgItemText(IDC_EDIT1, file.GetFilePath());
	}
	int idx = 0;

	CString filename;

	filename = GetFileTitleFromFileName(strtmp);
	idx = filename.GetLength();
	filename = filename.Left(idx - 1);
	filename += _T("_CV]");
	idx = filename.ReverseFind('[');
	filename = filename.Right(filename.GetLength() - idx - 1);
	idx = filename.Find(']');
	filename = filename.Left(idx);

	SetDlgItemText(IDC_EDIT2, filename);
	AppendText3(CString("Read file: ") + strtmp);

	FileFlush();

	CDialogEx::OnDropFiles(hDropInfo);
}


void CTMCVDlg::OnBnClickedButtonrev()
{
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
	std::string szline, temp;
	while (std::getline(inF, szline))
	{
		if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else if (szline.find("Mode") != -1)
		{
			if (szline.find("1") == -1)
			{
				AppendText3(_T("Error: 请提供一张太鼓谱面！"));
				return;
			}
			else
			{
				temp = "Mode:1";
				outF << temp << std::endl;
			}
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	while (std::getline(inF, szline))
	{
		Circle cr(szline);
		bool smalldk = ck4.GetCheck();
		if (isNote(szline))
		{
			if (cr.isKat())
			{
				if (cr.isFinisher())
				{
					if (smalldk)
					{
						cr.setDon();
					}
					else
					{
						cr.setDon();
						cr.setFinisher();
					}
				}
				else
				{
					cr.setDon();
				}
			}
			else
			{
				if (cr.isFinisher())
				{
					if (smalldk)
					{
						cr.setKat();
					}
					else
					{
						cr.setKat();
						cr.setFinisher();
					}
				}
			}
			outF << cr.getString() << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
	} // while
	CString alerting, e2;
	alerting = _T("生成了一个反色谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	AppendText3(alerting);
}


void CTMCVDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTMCVDlg::OnBnClickedButtonhr2()
{
	CString seedcs;
	GetDlgItemText(IDC_EDIT5, seedcs);
	if (seedcs.IsEmpty())
	{
		AppendText3(_T("Error: 请输入sv倍率"));
		return;
	}
	if (seedcs != seedcs.SpanIncluding(CString("-.0123456789")))
	{
		AppendText3(_T("Error: 请在那个框里输入小数！"));
	}
	if (seedcs.GetLength() > 9)
	{
		AppendText3(_T("Error: 你输入的数太长了，算不过来"));
	}
	std::string seedst = CW2A(seedcs.GetBuffer());
	double rate = std::stod(seedst);
	CString	destpath, sourcepath, destname;
	GetDlgItemText(IDC_EDIT1, sourcepath);
	GetDlgItemText(IDC_EDIT1, destpath);
	GetDlgItemText(IDC_EDIT2, destname);
	destpath = GetFileTitleExceptDiffName(destpath);
	std::string srcpath = CT2A(sourcepath.GetBuffer());
	std::string des1 = CT2A(destpath.GetBuffer());
	std::string des2 = CT2A(destname.GetBuffer());
	std::string despath = des1 + "[" + des2 + "].osu";
	std::ifstream inF;
	std::ofstream outF;
	inF.open(srcpath, std::ios_base::in | std::ios_base::app);
	outF.open(despath, std::ios_base::out);
	std::string szline, temp;
	while (std::getline(inF, szline))
	{
		if (szline.find("Version") != -1)
		{
			CString cs;
			GetDlgItemText(IDC_EDIT2, cs);
			temp = CT2A(cs.GetBuffer());
			outF << "Version:" << temp << std::endl;
		}
		else if (szline.find("SampleSet") != -1)
		{
			temp = "Sampleset: Soft";
			outF << temp << std::endl;
		}
		else if (szline.find("BeatmapSetID") != -1)
		{
			temp = "BeatmapSetID:-1";
			outF << temp << std::endl;
		}
		else if (szline.find("HPDrainRate") != -1)
		{
			CString temphp;
			GetDlgItemText(IDC_EDITHP, temphp);
			temp = "HPDrainRate:";
			temp += CW2A(temphp.GetBuffer());
			outF << temp << std::endl;
		}
		else if (szline.find("OverallDifficulty") != -1)
		{
			CString tempod;
			GetDlgItemText(IDC_EDITOD, tempod);
			temp = "OverallDifficulty:";
			temp += CW2A(tempod.GetBuffer());
			outF << temp << std::endl;
		}
		else
		{
			outF << szline << std::endl;
		}
		if (szline.find("TimingPoints") != -1)
		{
			break;
		}
	}

	// [TimingPoints] ~ [HitObjects]
	while (std::getline(inF, szline))
	{
		if ((szline[0] >= '0' && szline[0] <= '9') || szline[0] == '-')
		{
			Line ln(szline);
			if (!ln.isRed())
			{
				ln.setRate(rate);
				outF << ln.getString() << std::endl;
			} // is green line
			else
			{
				Line newln(szline);
				newln.setBPM(-100);
				newln.setLineType(0);
				newln.setRate(rate);
				outF << ln.getString() << std::endl;
			}
		}// isline
		if (szline.find("HitObjects") != -1)
		{
			break;
		}
	}
	// [HitObjects] ~
	outF << std::endl << "[HitObjects]" << std::endl;
	while (std::getline(inF, szline))
	{
		if (isNote(szline))
		{
			Circle cr(szline);
			if (cr.isFinisher() && ck4.GetCheck())
			{
				cr.unFinisher();
			}
			outF << cr.getString() << std::endl;
		}
		else
			continue;
	}
	CString alerting, e2;
	alerting = _T("生成了一个流速加倍谱面差分：");
	GetDlgItemText(IDC_EDIT2, e2);
	alerting += e2;
	alerting += _T("，请注意，所有的滑条和转盘均被删除。后续版本可能会更新滑条转盘适配方案");
	AppendText3(alerting);
}
