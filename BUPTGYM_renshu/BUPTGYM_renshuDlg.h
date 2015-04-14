
// BUPTGYM_renshuDlg.h : 头文件
//

#pragma once
#include "afxdb.h"

//人数传感器编号及人数清零指令
#define RENSHU_MAN 0
#define RENSHU_WOMAN 1
const byte reshu_reset[2][8] = { 
	{0x24,0x30,0x30,0x31,0x34,0x33,0x1c,0x23 }, //男宾人数清零指令
	{0x24,0x30,0x30,0x32,0x34,0x33,0x1d,0x23 }  //女宾人数清零指令
};

// CBUPTGYM_renshuDlg 对话框
class CBUPTGYM_renshuDlg : public CDialogEx
{
// 构造
public:
	CBUPTGYM_renshuDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BUPTGYM_RENSHU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	private:  
		 CDatabase m_db_opr;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);/********插入声明语句***********/
	void UpdateTextToEditCtrl(CEdit& edit, LPCTSTR pszText);/********插入声明语句***********/
	void AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText);/********插入声明语句***********/
	int QueryRenshu(CEdit& pEdit,CString& strIPAddr);/********插入声明语句***********/
	void QueryWSD(CEdit& pEdit,CString& strIPAddr,int portnum);/********插入声明语句***********/
	void CBUPTGYM_renshuDlg::shuizhi(CEdit& rEdit,CString& strIPAddr);/********插入声明语句***********/
	void CBUPTGYM_renshuDlg::ResetRenShu(int sensorID,CEdit& rEdit,CString& strIPAddr);/********插入声明语句***********/

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
