
// TMCVDlg.h: 头文件
//

#pragma once

#include <string>
#include <vector>


// CTMCVDlg 对话框
class CTMCVDlg : public CDialogEx
{
// 构造
public:
	CTMCVDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TMCV_DIALOG };
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
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtoncv();
	afx_msg void OnEnChangeEdit3();
	void AppendText3(const CString&);
	void FileIO();
	void FileFlush();
	void InsertNote(std::string, int&, std::ostream&);
	void InsertNoteNf(std::string, int&, std::ostream&);
	void InsertNoteDdKk(std::string, int&, std::ostream&);
	void InsertNoteDdKkNf(std::string, int&, std::ostream&);
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox cb;
	CButton bcv;
	CButton rd1;
	CButton rd2;
	afx_msg void OnBnClickedButtonhr();
	CButton bhr;
	afx_msg void OnBnClickedButtonsr();
	CButton bsr;
	CButton brev;
	afx_msg void OnBnClickedButtonspawn();
	bool avoidGreenLine = false;
	bool avoidTiming = false;
	double basebpm;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck1();
	std::vector<std::pair<int, int>> BpmScaling;
	std::vector<double> BpmS;
	CButton ck1;
	CButton ck2;
	CButton ck4;
	afx_msg void OnBnClickedButtonrdm();
	CButton brdm;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonrev();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButtonhr2();
	CButton bhr2;
	CEdit ed;
};
