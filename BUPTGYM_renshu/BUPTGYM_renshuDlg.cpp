
// BUPTGYM_renshuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BUPTGYM_renshu.h"
#include "BUPTGYM_renshuDlg.h"
#include "afxdialogex.h"
#include "winsock2.h"
#include <string>

#include "modbus.h"
#include "modbus-rtu.h"
#include "modbus-rtu-private.h"


using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define	BUF_SZIE	64

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

float roomt=0;
float roomr=0;

CSocket _socket;/*************��stdsfx.hͷ�ļ������#include <afxsock.h>************/
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CBUPTGYM_renshuDlg �Ի���



CBUPTGYM_renshuDlg::CBUPTGYM_renshuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBUPTGYM_renshuDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBUPTGYM_renshuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBUPTGYM_renshuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBUPTGYM_renshuDlg::OnBnClickedButton1)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CBUPTGYM_renshuDlg::OnIpnFieldchangedIpaddress1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBUPTGYM_renshuDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CBUPTGYM_renshuDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CBUPTGYM_renshuDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBUPTGYM_renshuDlg ��Ϣ�������

BOOL CBUPTGYM_renshuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CEdit * pEdit1 =(CEdit *) GetDlgItem(IDC_EDIT2);
	pEdit1->SetLimitText(UINT_MAX);


	m_db_opr.Open(NULL,   
		false,   
		false,   
		//_T("ODBC;server=10.108.38.89;DSN=buptgym_screen;UID=wuudann;PWD=123456")  
		_T("ODBC;server=localhost;DSN=buptgym_screen;UID=root;PWD=123456")  
		);  


	if(!m_db_opr.IsOpen())  
	{  
		//AfxMessageBox(_T("DB open failed!"));  
		return false;  
	}  

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBUPTGYM_renshuDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBUPTGYM_renshuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBUPTGYM_renshuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}















/***********��ʱ������**********************************/
void CBUPTGYM_renshuDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);

	if(1==nIDEvent)
	{
		CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);


		CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);

		CString strIPAddr;

		/******************��ʹ��unicode�ַ���ʱ���������������������ϵͳ���ܰ�LPCWSTR���͵��ַ���ת��ΪLPCSTR���ͣ������ȡip��ַ��ʱ����Ҫ����LPCSTR���ͣ�����Ҫת�����˷������У���Ҫ����Ŀ�ı������Ϊ��ϱ��룬��ʱ�Ҳ�������ĺ�������Ҫ��������ĺ�������*/
		//pIPaddr->GetWindowTextW(strIPAddr);
		pIPaddr->GetWindowTextA(strIPAddr);

		//AfxBeginThread(QueryWSD, pEdit,&strIPAddr);
		CTime _time = CTime::GetCurrentTime();

		AppendTextToEditCtrl(*pEdit,_time.Format(_T("\r\n\r\n\r\n%Y-%m-%d %H:%M:%S\r\n")));
		QueryRenshu(*pEdit,strIPAddr);
		QueryWSD(*pEdit,strIPAddr,2012);
		
		QueryWSD(*pEdit,strIPAddr,2013);
		shuizhi(*pEdit,strIPAddr);
		/**********��ʱ�����������**************/
		int hour = _time.GetHour();//��ȡ��ǰСʱ����[0,23]
		int minute = _time.GetMinute();//��ȡ��ǰ��������[0,59]
		switch(hour)
		{
		case 14://����2��
			if(minute>55)//����2��55��3��䣬�ظ�ִ�п����������
			{
				ResetRenShu(RENSHU_MAN,*pEdit,strIPAddr);
				ResetRenShu(RENSHU_WOMAN,*pEdit,strIPAddr);
			}
			break;
		case 22://����10��
			if(minute<5)//����10�㵽10��5�ּ䣬�ظ�ִ�бչ��������
			{
				ResetRenShu(RENSHU_MAN,*pEdit,strIPAddr);
				ResetRenShu(RENSHU_WOMAN,*pEdit,strIPAddr);
			}
			break;
		default:
			break;
		}

	}
	else if(2==nIDEvent)
	{
		//WSACancelBlockingCall();//ȡ��һ�����ڽ����е���������
		_socket.CancelBlockingCall();
		WSACancelBlockingCall();
		//WSACleanup();
		CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
		CString a;
		a.Format(_T("\r\n������ʱ������") );
		AppendLineToMultilineEditCtrl(*pEdit,a);
	}
}



/******************��ʼ��ť��Ϣ����***********************/
void CBUPTGYM_renshuDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIPAddressCtrl * pIP = (CIPAddressCtrl *) GetDlgItem(IDC_IPADDRESS1);
	pIP -> EnableWindow(false);
	//��ȡButton���
	CButton * pButton1 =(CButton *) GetDlgItem(IDC_BUTTON1);
	//����Button�ؼ�
	pButton1->EnableWindow(false);
	//��ȡButton���
	CButton * pButton2 =(CButton *) GetDlgItem(IDC_BUTTON2);
	//����Button�ؼ�
	pButton2->EnableWindow(true);
	SetTimer(1,5000,NULL);         //��ʱ��1����ʱ10s
}


/******************׷��һ���ı�***********************/
void CBUPTGYM_renshuDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	//edit.SetSel(0,2);//ѡ���ı�
	edit.ReplaceSel(pszText);

}

/******************������ʾ����***********************/
void CBUPTGYM_renshuDlg::UpdateTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.SetSel(0,nLength);//ѡ���ı�
	edit.ReplaceSel(pszText);

}


/******************׷����ʾ�ı�ǰ����***********************/
void CBUPTGYM_renshuDlg::AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	CString strLine;
	// add CR/LF to text
	strLine.Format(_T("\r\n%s\r\n"), pszText);
	AppendTextToEditCtrl(edit, strLine);
}





void CBUPTGYM_renshuDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}




/*******************ֹͣ��ť����Ӧ����****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIPAddressCtrl * pIP = (CIPAddressCtrl *) GetDlgItem(IDC_IPADDRESS1);
	pIP -> EnableWindow(true);
	//��ȡButton���
	CButton * pButton1 =(CButton *) GetDlgItem(IDC_BUTTON1);
	//����Button�ؼ�
	pButton1->EnableWindow(true);
	//��ȡButton���
	CButton * pButton2 =(CButton *) GetDlgItem(IDC_BUTTON2);
	//����Button�ؼ�
	pButton2->EnableWindow(false);
	KillTimer(1);
}


/********************��ѯ��������********************************/
int CBUPTGYM_renshuDlg::QueryRenshu(CEdit& rEdit,CString& strIPAddr)
{
	CString a;
	a.Format(_T("����������������: %s:%d"), strIPAddr,50000);
	AppendLineToMultilineEditCtrl(rEdit,a);
	//AppendLineToMultilineEditCtrl(rEdit,strIPAddr);
	try
	{
		WSADATA			wsd;			//WSADATA����
		SOCKET			sHost;			//�������׽���
		SOCKADDR_IN		servAddr;		//��������ַ
		char			buf[BUF_SZIE];	//�������ݻ�����
		int				retVal;			//����ֵ
		int countNumIn=0;//��¼�ܵĽ�������
		int countNumOut=0;
		int countNumNet=0;


		const byte query[2][8] ={ {0x24,0x30,0x30,0x31,0x33,0x39,0x21,0x23 }, {0x24,0x30,0x30,0x32,0x33,0x39,0x22,0x23 }}; 
		//byte query_woman[8] = {0x24,0x30,0x30,0x32,0x33,0x39,0x22,0x23 }; 


		//��ʼ���׽��ֶ�̬��
		AfxSocketInit();
		if(!_socket.Create())
		{
			char szMsg[1024] = {0};
			CString a;
			a.Format(_T("create faild: %d"), _socket.GetLastError());
			AppendLineToMultilineEditCtrl(rEdit,a);
			return -1;
		}

		//�����׽���
		SetTimer(2,500,NULL);
		if(_socket.Connect(strIPAddr,50000))
		{





			/******�ֱ��ѯ��Ů���ݣ���ѯ����**************************/
			for(int i=0;i<2;i++)
			{

				//���������������
				SetTimer(2,500,NULL);
				_socket.Send(query[i], 8);
				KillTimer(2);

				//���շ���������
				byte			buf2[64];
				ZeroMemory(buf2, 14);

				SetTimer(2,500,NULL);
				_socket.Receive(buf2, 14);
				KillTimer(2);

				int inNum = ((buf2[6] << 16) + (buf2[7] << 8) + buf2[8]);
				int outNum = ((buf2[9] << 16) + (buf2[10] << 8) + buf2[11]);
				int netNum = inNum - outNum;
				if(netNum<0) netNum=0;//��֤���ڲ����ָ�����

				countNumIn=countNumIn+inNum;
				countNumOut=countNumOut+outNum;
				countNumNet=countNumNet+netNum;

				/******************************************
				* Author: zr.zz.alp@gmail.com
				* Time: 2014/06/03 23:01
				* TODO: 
				* ��������ֵ���Ͻ�Ҫ����ȷ������һ��ʱ�䲻���г��򣬵���δ�ܰ�ʱ��������ʱ�������׳�����ǰ2000���Ͻ�
				******************************************/
				if(inNum<0||inNum>2000||outNum<0||outNum>2000)//����仰����Ϊ�����������᲻��ʱ�������ݣ�������ɽ������ݴ�����Ϊ�Ƚ����б��������ʱֱ������ѭ��,������Ϊ�����������Ѿ������������ڻ��������ݣ�Ҫ����ʱ�����ݽ��յ�����������´�ѭ��ʱ����������ݣ����´�����1�ʹ�����2 �����������
				{	
					CString d;
					d.Format(_T("������������ѯ����"));
					AppendLineToMultilineEditCtrl(rEdit,d);
					//���շ���������
					byte			buf3[64];
					ZeroMemory(buf3, 64);

					SetTimer(2,500,NULL);
					//retVal = recv(sHost,(char*) buf3, 64, 0);
					KillTimer(2);

					return -1;
				}
				/**************д���ݿ�***********************/
				try  
				{  
					CString sql_str;  

					sql_str.Format(_T("insert into %s (_id,inNum,outNum,netNum) values(%d,%d,%d,%d) ON DUPLICATE KEY UPDATE _id = VALUES(_id),inNum = VALUES(inNum),outNum = VALUES(outNum),netNum = VALUES(netNum)"),"screenrenshu",i+1,inNum,outNum,netNum);  

					m_db_opr.ExecuteSQL(sql_str);  
				}  
				catch(CDBException* pe)  
				{  
					// The error code is in pe->m_nRetCode   
					//pe->ReportError();  
					pe->Delete();  
				}  



				/***************���������************************/
				try
				{
					CString a,b,c;
					if(i==0)
					{
						a.Format(_T("�б�������%d,�б�������%d,ʣ������%d"), inNum,outNum,netNum);
						AppendLineToMultilineEditCtrl(rEdit,a);

						b.Format(_T("%d"),inNum);
						CEdit * pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT3);
						UpdateTextToEditCtrl(*pEdit3,b);

						c.Format(_T("%d"),outNum);
						pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT1);
						UpdateTextToEditCtrl(*pEdit3,c);
					}
					else
					{
						a.Format(_T("Ů��������%d,Ů��������%d,ʣ������%d"), inNum,outNum,netNum);
						AppendLineToMultilineEditCtrl(rEdit,a);

						b.Format(_T("%d"),inNum);
						CEdit * pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT4);
						UpdateTextToEditCtrl(*pEdit3,b);

						c.Format(_T("%d"),outNum);
						pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT6);
						UpdateTextToEditCtrl(*pEdit3,c);
					}

				}
				catch(...)
				{
					KillTimer(2);
				}

				//	printf("%d,%d,%d\n",inNum,outNum,netNum);
				//	printf("%d\n", retVal);		
			}
		}
		_socket.Close();
		/**************************ѭ������*****************************************************/


		/**************************������д���ݿ�**********************************/
		try  
		{  
			CString sql_str;  

			sql_str.Format(_T("insert into %s (_id,inNum,outNum,netNum) values(%d,%d,%d,%d) ON DUPLICATE KEY UPDATE _id = VALUES(_id),inNum = VALUES(inNum),outNum = VALUES(outNum),netNum = VALUES(netNum)"),"screenrenshu",99,countNumIn,countNumOut,countNumNet);  
			if(countNumIn>=0&&countNumIn<=4000&&countNumOut>=0&&countNumOut<=4000)//����仰����Ϊ�����������᲻��ʱ�������ݣ�������ɽ������ݴ��󣬴�ʱ��д���ݿ�
				m_db_opr.ExecuteSQL(sql_str);  
		}  
		catch(CDBException* pe)  
		{  
			// The error code is in pe->m_nRetCode   
			//pe->ReportError();  
			pe->Delete();  
		}  



		//�˳�
		//closesocket(sHost);	//�ر��׽���
		//WSACleanup();		//�ͷ��׽�����Դ

		//	printf("ִ�гɹ�!\n");
		return 0;
	}
	catch(...)
	{
		//KillTimer(1);
		KillTimer(2);
		return -1;
	}
}



/***********************************��ѯ��ʪ�Ⱥ���******************************************************************/

void CBUPTGYM_renshuDlg::QueryWSD(CEdit& rEdit,CString& strIPAddr,int portnum)
{
	CString a;
	a.Format(_T("��ʪ�ȴ�����������: %s:%d"), strIPAddr,portnum);
	AppendLineToMultilineEditCtrl(rEdit,a);
	try
	{
		AfxSocketInit();
		if(!_socket.Create())
		{
			char szMsg[1024] = {0};
			CString a;
			a.Format(_T("create faild: %d"), _socket.GetLastError());
			AppendLineToMultilineEditCtrl(rEdit,a);
			return;
		}

		SetTimer(2,500,NULL);
		if(_socket.Connect(strIPAddr,portnum))
		{
			KillTimer(2);
			const byte command[12]={0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0x00, 0x00, 0x02};

			SetTimer(2,500,NULL);
			_socket.Send(command,12);
			KillTimer(2);


			byte * buffer = new byte[13];

			SetTimer(2,500,NULL);
			_socket.Receive(buffer,13);
			KillTimer(2);
			//	CTime _time = CTime::GetCurrentTime();

			//	AppendTextToEditCtrl(rEdit,_time.Format(_T("%Y-%m-%d %H:%M:%S")));

			/*		for(int i=0;i<13;i++)
			{
			CString a;
			a.Format(_T(" %x "), buffer[i]);
			AppendTextToEditCtrl(rEdit,a);
			}

			*/
			/*********����˿ں�Ϊ2012����һ�������������дȫ�ֱ�����ֵ����д���ݿ⣬�������2012��ȫ�ֱ�����ƽ������д���ݿ�***************************************/
			float temperature = ((float)(buffer[11] << 8) + buffer[12] - 27315)/100;
			float humid =  ((float)(buffer[9] << 8) + buffer[10])/100;
			if(portnum==2012)
			{
				roomt = temperature;
				roomr = humid;

			}
			else {

				/******************************�˴���֤���2012�˿ڵĴ������������⣬��ôд���ݿⲻ����¶Ⱥ�ʪ�ȵ�ƽ��ֵд��ȥ,�������2012�������������򷽷�д�ں����ײ�**********************************/
				/******************************************
				* Author: zr.zz.alp@gmail.com
				* Time: 2014/06/03 22:59
				* TODO: 
				* 2013 �˿ڵĴ�����Ӳ��������ʱʧ������ע�͵���һ���ִ��룬ȡ��2013���ݵĶ�ȡ��Ӧ��У԰��ȫ���
				* Ҫ�ǵõ��Ժô������������
				******************************************/
				/*
				if(roomt>1&&roomr>1){
					roomt = (temperature+roomt)/2.0;
					roomr = (humid+roomr)/2.0;
				}
				else{
					roomt = temperature;
					roomr = humid;
				}
				*/

				/**************д���ݿ�***********************/
				try  
				{  
					CString sql_str;  
					sql_str.Format(_T("insert into %s (_id,roomt,roomr) values(%s,%.2f,%.2f) ON DUPLICATE KEY UPDATE _id = VALUES(_id),roomt = VALUES(roomt),roomr = VALUES(roomr)"),"screenpool","1",roomt,roomr);
					m_db_opr.ExecuteSQL(sql_str);  
				}  
				catch(CDBException* pe)  
				{  
					// The error code is in pe->m_nRetCode   
					//pe->ReportError();  
					pe->Delete();  
				}  
				roomt=0.0;roomr=0.0;
			}
			/***************************��ʾ������*****************************/

			try
			{
				CString a,b,c;
				a.Format(_T("��������%.2f�棬����ʪ��%.2f%%"), temperature,humid);
				AppendLineToMultilineEditCtrl(rEdit,a);

				b.Format(_T("%.2f"),temperature);
				if(portnum==2012){	
					CEdit * pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT5);
					UpdateTextToEditCtrl(*pEdit3,b);

					c.Format(_T("%.2f"),humid);
					pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT7);
					UpdateTextToEditCtrl(*pEdit3,c);
				}


				else{
					CEdit * pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT8);
					UpdateTextToEditCtrl(*pEdit3,b);

					c.Format(_T("%.2f"),humid);
					pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT9);
					UpdateTextToEditCtrl(*pEdit3,c);
				}
			}
			catch(...)
			{
				KillTimer(2);
			}
		}
		else
		{
			//KillTimer(1);
			KillTimer(2);
			CString a;
			a.Format(_T("��ʪ�ȴ�����Socket����ʧ��: %s:%d"), strIPAddr,portnum);
			AppendLineToMultilineEditCtrl(rEdit,a);

			/**************����˿ںŲ�Ϊ2012��������ƽ��д���ݿ��ָ���޷�ִ�����ڴ˴�д���ݿ�***********************/
			if(portnum!=2012)
			try  
			{  
				CString sql_str;  
				sql_str.Format(_T("insert into %s (_id,roomt,roomr) values(%s,%.2f,%.2f) ON DUPLICATE KEY UPDATE _id = VALUES(_id),roomt = VALUES(roomt),roomr = VALUES(roomr)"),"screenpool","1",roomt,roomr);
				m_db_opr.ExecuteSQL(sql_str);  
			}  
			catch(CDBException* pe)  
			{  
				// The error code is in pe->m_nRetCode   
				//pe->ReportError();  
				pe->Delete();  
			}  



		}
		_socket.Close();
	}
	catch(...)
	{
		//KillTimer(1);
		KillTimer(2);
	}
}




/***********************************��ѯˮ�ʺ���******************************************************************/




/*****************
*	����������Ƕ�ȡ����ģ���һ������demo
*	ʹ�õ�modebus,modbus-rtu,modbus-data��ģ��
******************/


//Input Registers��غָ꣬������������ڽ�����е�λ��
#define		INPUP_REGS_NUM			5
#define		INDEX_DISINFECTION		0
#define		INDEX_PH				1
#define		INDEX_TEMPERATURE		2
#define		INDEX_FLOW				3
#define		INDEX_HYPOCH			4


void CBUPTGYM_renshuDlg::shuizhi(CEdit& rEdit,CString& strIPAddr)
{


	CString a;
	a.Format(_T("ˮ�ʼ��װ��������: %s:%d"), strIPAddr,50001);
	AppendLineToMultilineEditCtrl(rEdit,a);


	//�����豸����ģ���IP�˿�
	int ipport = 50001;


	try
	{
		//׼��ʹ��CSocketʵ����������
		AfxSocketInit();
		CSocket _socket;
		//��ʼ��Socket
		if(!_socket.Create())
		{
			//Socket��ʼ��ʧ��
			CString d;
			d.Format(_T("Socket��ʼ��ʧ��"));
			AppendLineToMultilineEditCtrl(rEdit,d);
			//pEdit->SetWindowTextW(_T("Socket creation failed"));
			return ;
		}
		//���ӵ������豸������ģ��
		if(!_socket.Connect(strIPAddr,ipport))
		{
			//Socket����ʧ��
			CString d;
			d.Format(_T("Socket����ʧ��"));
			AppendLineToMultilineEditCtrl(rEdit,d);
			//pEdit->SetWindowTextW(_T("Socket connection failed"));
			return ;
		}
		//��ѯָ��
		byte command[8] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x70, 0x0d};
		//���ջ���������8λ�ֽ�������֯
		byte buffer[100];
		//���ջ�����������16λ������֯
		uint16_t monitorRawData[100];
		//���յĸ������ݻ�����
		float monitorFloatData[100];
		//���Ͳ�ѯָ��
		_socket.Send(command,8);
		Sleep(200);
		//��������
		int recvLen = _socket.Receive(buffer,100);
		//��¼���ݽ���λ��
		buffer[recvLen]='\0';
		//ƫ������ͨ�ŵ�Header���ȣ�ֵΪ1
		int offset = 1;
		//����modbus�Ĺ淶�����ߵ�λ����8λ�ֽ����ݵ�Ԫ�������16λ��Ԫ
		for (int i = 0; i < recvLen; i++) {
			/* shift reg hi_byte to temp OR with lo_byte */
			monitorRawData[i] = (buffer[offset + 2 + (i << 1)] << 8) |
				buffer[offset + 3 + (i << 1)];
		}
		//����16λ��֯�Ļ������е�����ת���ɸ�����
		for(int i=0;i<recvLen/2;i++)
		{
			//ע�������modbus_get_float��modbus-dataģ���е�����
			monitorFloatData[i]=modbus_get_float(monitorRawData+2*i);
		}

		//��ʱ���ݼ��ѱ�����monitorFloatData��

		//������ת��Ϊ�ַ���

		CString q;
		q.Format(_T("disinfection: %f, PH: %f, temp: %f,flow: %f, hypo: %f"),monitorFloatData[INDEX_DISINFECTION],monitorFloatData[INDEX_PH],monitorFloatData[INDEX_TEMPERATURE],monitorFloatData[INDEX_FLOW],monitorFloatData[INDEX_HYPOCH]);




		if(monitorFloatData[INDEX_PH]>5&&monitorFloatData[INDEX_PH]<8&&monitorFloatData[INDEX_TEMPERATURE]>10&&monitorFloatData[INDEX_TEMPERATURE]<40){
			/***************************��ʾ������*****************************/


			CString a1,dis,ph,tem,flow,hcl;
			a1.Format(_T("������%.6f��PHֵ%.6f��ˮ��%.6f�棬����%.6f��������%.6f"), monitorFloatData[INDEX_DISINFECTION],monitorFloatData[INDEX_PH],monitorFloatData[INDEX_TEMPERATURE],monitorFloatData[INDEX_FLOW],monitorFloatData[INDEX_HYPOCH]);
			AppendLineToMultilineEditCtrl(rEdit,a1);

			dis.Format(_T("%.6f"),monitorFloatData[INDEX_DISINFECTION]);
			ph.Format(_T("%.6f"),monitorFloatData[INDEX_PH]);
			tem.Format(_T("%.6f"),monitorFloatData[INDEX_TEMPERATURE]);
			flow.Format(_T("%.6f"),monitorFloatData[INDEX_FLOW]);
			hcl.Format(_T("%.6f"),monitorFloatData[INDEX_HYPOCH]);

			CEdit * pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT14);
			UpdateTextToEditCtrl(*pEdit3,tem);

			pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT12);
			UpdateTextToEditCtrl(*pEdit3,dis);

			pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT13);
			UpdateTextToEditCtrl(*pEdit3,ph);

			pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT10);
			UpdateTextToEditCtrl(*pEdit3,flow);

			pEdit3 =(CEdit *) GetDlgItem(IDC_EDIT11);
			UpdateTextToEditCtrl(*pEdit3,hcl);

			/**************д���ݿ�***********************/
			try  
			{  
				CString sql_str;  

				sql_str.Format(_T("insert into %s (_id,xdj,pH,temperature,hclo3) values(%d,%.2f,%.2f,%.2f,%.2f) ON DUPLICATE KEY UPDATE _id = VALUES(_id),xdj = VALUES(xdj),pH = VALUES(pH),temperature = VALUES(temperature),hclo3=VALUES(hclo3)"),"screenyl",1,monitorFloatData[INDEX_DISINFECTION],monitorFloatData[INDEX_PH],monitorFloatData[INDEX_TEMPERATURE],monitorFloatData[INDEX_HYPOCH]);  

				m_db_opr.ExecuteSQL(sql_str);  
			}  
			catch(CDBException* pe)  
			{  
				// The error code is in pe->m_nRetCode   
				//pe->ReportError();  
				pe->Delete();  
			}  

		}
		else{
			CString d;
			d.Format(_T("ˮ�ʼ��ģ�����ݴ���"));
			AppendLineToMultilineEditCtrl(rEdit,d);

		}

		_socket.Close();
		//����
		return;
	}
	catch(...)
	{
	}
}

/************ȡ��modbus.cppģ�飬�����溯����ʹ�õ��ģ������õ�������***********************************/
/* Get a float from 4 bytes in Modbus format */
float modbus_get_float(const uint16_t *src)
{
	float f = 0.0f;
	uint32_t i;

	i = (((uint32_t)src[0]) << 16) + src[1];
	memcpy(&f, &i, sizeof(float));

	return f;
}


/*******************������λ���ܷ�װ****************************/
void CBUPTGYM_renshuDlg::ResetRenShu(int sensorID,CEdit& rEdit,CString& strIPAddr)
{
	int port = 50000;
	CString a;
	a.Format(_T("\r\n�������������� %d \r\n ����������������: %s:%d"),sensorID ,strIPAddr,port);
	AppendLineToMultilineEditCtrl(rEdit,a);
	try
	{
		AfxSocketInit();
		if(!_socket.Create())
		{
			char szMsg[1024] = {0};
			CString a;
			a.Format(_T("�׽��ֽ���ʧ��: %d"), _socket.GetLastError());
			AppendLineToMultilineEditCtrl(rEdit,a);
			return;
		}

		SetTimer(2,500,NULL);
		if(_socket.Connect(strIPAddr,50000))
		{
			KillTimer(2);

			SetTimer(2,500,NULL);
			_socket.Send(reshu_reset[sensorID],8);
			KillTimer(2);
		}
		else
		{
			KillTimer(2);
			CString a;
			a.Format(_T("����������Socket����ʧ��: %s:%d"), strIPAddr,port);
			AppendLineToMultilineEditCtrl(rEdit,a);
		}
		_socket.Close();
	}
	catch(...)
	{
		KillTimer(2);
	}
}

/*******************�б���λ��ť����Ӧ����****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton3()
{
	CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
	CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);
	CString strIPAddr;
	/******************��ʹ��unicode�ַ���ʱ���������������������ϵͳ���ܰ�LPCWSTR���͵��ַ���ת��ΪLPCSTR���ͣ������ȡip��ַ��ʱ����Ҫ����LPCSTR���ͣ�����Ҫת�����˷������У���Ҫ����Ŀ�ı������Ϊ��ϱ��룬��ʱ�Ҳ�������ĺ�������Ҫ��������ĺ�������*/
	//pIPaddr->GetWindowTextW(strIPAddr);
	pIPaddr->GetWindowTextA(strIPAddr);
	//KillTimer(1);									//��ֹ��ʱ��1
	ResetRenShu(RENSHU_MAN,*pEdit,strIPAddr);
	//SetTimer(1,5000,NULL);							//�ָ���ʱ��1
}

/*******************Ů����λ��ť����Ӧ����****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton4()
{
	CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
	CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);
	CString strIPAddr;
	/******************��ʹ��unicode�ַ���ʱ���������������������ϵͳ���ܰ�LPCWSTR���͵��ַ���ת��ΪLPCSTR���ͣ������ȡip��ַ��ʱ����Ҫ����LPCSTR���ͣ�����Ҫת�����˷������У���Ҫ����Ŀ�ı������Ϊ��ϱ��룬��ʱ�Ҳ�������ĺ�������Ҫ��������ĺ�������*/
	//pIPaddr->GetWindowTextW(strIPAddr);
	pIPaddr->GetWindowTextA(strIPAddr);
	//KillTimer(1);									//��ֹ��ʱ��1
	ResetRenShu(RENSHU_WOMAN,*pEdit,strIPAddr);
	//SetTimer(1,5000,NULL);							//�ָ���ʱ��1
}


