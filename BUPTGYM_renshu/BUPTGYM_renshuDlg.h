
// BUPTGYM_renshuDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdb.h"

//������������ż���������ָ��
#define RENSHU_MAN 0
#define RENSHU_WOMAN 1
const byte reshu_reset[2][8] = { 
	{0x24,0x30,0x30,0x31,0x34,0x33,0x1c,0x23 }, //�б���������ָ��
	{0x24,0x30,0x30,0x32,0x34,0x33,0x1d,0x23 }  //Ů����������ָ��
};

// CBUPTGYM_renshuDlg �Ի���
class CBUPTGYM_renshuDlg : public CDialogEx
{
// ����
public:
	CBUPTGYM_renshuDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BUPTGYM_RENSHU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	private:  
		 CDatabase m_db_opr;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);/********�����������***********/
	void UpdateTextToEditCtrl(CEdit& edit, LPCTSTR pszText);/********�����������***********/
	void AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText);/********�����������***********/
	int QueryRenshu(CEdit& pEdit,CString& strIPAddr);/********�����������***********/
	void QueryWSD(CEdit& pEdit,CString& strIPAddr,int portnum);/********�����������***********/
	void CBUPTGYM_renshuDlg::shuizhi(CEdit& rEdit,CString& strIPAddr);/********�����������***********/
	void CBUPTGYM_renshuDlg::ResetRenShu(int sensorID,CEdit& rEdit,CString& strIPAddr);/********�����������***********/

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
