
// BUPTGYM_renshuDlg.cpp : 实现文件
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

CSocket _socket;/*************在stdsfx.h头文件中添加#include <afxsock.h>************/
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


// CBUPTGYM_renshuDlg 对话框



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


// CBUPTGYM_renshuDlg 消息处理程序

BOOL CBUPTGYM_renshuDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBUPTGYM_renshuDlg::OnPaint()
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
HCURSOR CBUPTGYM_renshuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}















/***********定时器函数**********************************/
void CBUPTGYM_renshuDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);

	if(1==nIDEvent)
	{
		CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);


		CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);

		CString strIPAddr;

		/******************当使用unicode字符集时候用上面这个函数，这是系统不能把LPCWSTR类型的字符串转换为LPCSTR类型，下面读取ip地址的时候需要的是LPCSTR类型，故需要转换，此方案不行，需要将项目的编码调整为混合编码，此时找不到上面的函数，需要调用下面的函数即可*/
		//pIPaddr->GetWindowTextW(strIPAddr);
		pIPaddr->GetWindowTextA(strIPAddr);

		//AfxBeginThread(QueryWSD, pEdit,&strIPAddr);
		CTime _time = CTime::GetCurrentTime();

		AppendTextToEditCtrl(*pEdit,_time.Format(_T("\r\n\r\n\r\n%Y-%m-%d %H:%M:%S\r\n")));
		QueryRenshu(*pEdit,strIPAddr);
		QueryWSD(*pEdit,strIPAddr,2012);
		
		QueryWSD(*pEdit,strIPAddr,2013);
		shuizhi(*pEdit,strIPAddr);
		/**********定时人数清零操作**************/
		int hour = _time.GetHour();//获取当前小时数，[0,23]
		int minute = _time.GetMinute();//获取当前分钟数，[0,59]
		switch(hour)
		{
		case 14://下午2点
			if(minute>55)//下午2点55到3点间，重复执行开馆清零操作
			{
				ResetRenShu(RENSHU_MAN,*pEdit,strIPAddr);
				ResetRenShu(RENSHU_WOMAN,*pEdit,strIPAddr);
			}
			break;
		case 22://晚上10点
			if(minute<5)//晚上10点到10点5分间，重复执行闭馆清零操作
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
		//WSACancelBlockingCall();//取消一次正在进行中的阻塞调用
		_socket.CancelBlockingCall();
		WSACancelBlockingCall();
		//WSACleanup();
		CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
		CString a;
		a.Format(_T("\r\n操作超时！！！") );
		AppendLineToMultilineEditCtrl(*pEdit,a);
	}
}



/******************开始按钮消息处理***********************/
void CBUPTGYM_renshuDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIPAddressCtrl * pIP = (CIPAddressCtrl *) GetDlgItem(IDC_IPADDRESS1);
	pIP -> EnableWindow(false);
	//获取Button句柄
	CButton * pButton1 =(CButton *) GetDlgItem(IDC_BUTTON1);
	//禁用Button控件
	pButton1->EnableWindow(false);
	//获取Button句柄
	CButton * pButton2 =(CButton *) GetDlgItem(IDC_BUTTON2);
	//禁用Button控件
	pButton2->EnableWindow(true);
	SetTimer(1,5000,NULL);         //定时器1，定时10s
}


/******************追加一行文本***********************/
void CBUPTGYM_renshuDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	//edit.SetSel(0,2);//选中文本
	edit.ReplaceSel(pszText);

}

/******************更新显示内容***********************/
void CBUPTGYM_renshuDlg::UpdateTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.SetSel(0,nLength);//选中文本
	edit.ReplaceSel(pszText);

}


/******************追加显示文本前后换行***********************/
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




/*******************停止按钮的相应处理****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CIPAddressCtrl * pIP = (CIPAddressCtrl *) GetDlgItem(IDC_IPADDRESS1);
	pIP -> EnableWindow(true);
	//获取Button句柄
	CButton * pButton1 =(CButton *) GetDlgItem(IDC_BUTTON1);
	//禁用Button控件
	pButton1->EnableWindow(true);
	//获取Button句柄
	CButton * pButton2 =(CButton *) GetDlgItem(IDC_BUTTON2);
	//禁用Button控件
	pButton2->EnableWindow(false);
	KillTimer(1);
}


/********************查询人数函数********************************/
int CBUPTGYM_renshuDlg::QueryRenshu(CEdit& rEdit,CString& strIPAddr)
{
	CString a;
	a.Format(_T("人数传感器连接中: %s:%d"), strIPAddr,50000);
	AppendLineToMultilineEditCtrl(rEdit,a);
	//AppendLineToMultilineEditCtrl(rEdit,strIPAddr);
	try
	{
		WSADATA			wsd;			//WSADATA变量
		SOCKET			sHost;			//服务器套接字
		SOCKADDR_IN		servAddr;		//服务器地址
		char			buf[BUF_SZIE];	//发送数据缓冲区
		int				retVal;			//返回值
		int countNumIn=0;//记录总的进出人数
		int countNumOut=0;
		int countNumNet=0;


		const byte query[2][8] ={ {0x24,0x30,0x30,0x31,0x33,0x39,0x21,0x23 }, {0x24,0x30,0x30,0x32,0x33,0x39,0x22,0x23 }}; 
		//byte query_woman[8] = {0x24,0x30,0x30,0x32,0x33,0x39,0x22,0x23 }; 


		//初始化套结字动态库
		AfxSocketInit();
		if(!_socket.Create())
		{
			char szMsg[1024] = {0};
			CString a;
			a.Format(_T("create faild: %d"), _socket.GetLastError());
			AppendLineToMultilineEditCtrl(rEdit,a);
			return -1;
		}

		//创建套接字
		SetTimer(2,500,NULL);
		if(_socket.Connect(strIPAddr,50000))
		{





			/******分别查询男女数据，查询两次**************************/
			for(int i=0;i<2;i++)
			{

				//向服务器发送数据
				SetTimer(2,500,NULL);
				_socket.Send(query[i], 8);
				KillTimer(2);

				//接收服务器数据
				byte			buf2[64];
				ZeroMemory(buf2, 14);

				SetTimer(2,500,NULL);
				_socket.Receive(buf2, 14);
				KillTimer(2);

				int inNum = ((buf2[6] << 16) + (buf2[7] << 8) + buf2[8]);
				int outNum = ((buf2[9] << 16) + (buf2[10] << 8) + buf2[11]);
				int netNum = inNum - outNum;
				if(netNum<0) netNum=0;//保证室内不出现负人数

				countNumIn=countNumIn+inNum;
				countNumOut=countNumOut+outNum;
				countNumNet=countNumNet+netNum;

				/******************************************
				* Author: zr.zz.alp@gmail.com
				* Time: 2014/06/03 23:01
				* TODO: 
				* 数据正常值的上界要重新确定，当一段时间不运行程序，导致未能按时清零数据时，很容易超过当前2000的上界
				******************************************/
				if(inNum<0||inNum>2000||outNum<0||outNum>2000)//加这句话，因为人数传感器会不定时发回数据，可能造成接受数据错误，因为先接收男宾错误则此时直接跳出循环,但是因为传感器命令已经发出，故现在还会有数据，要讲此时的数据接收到，否则会在下次循环时接收这个数据，导致传感器1和传感器2 的数据相混淆
				{	
					CString d;
					d.Format(_T("人数传感器查询错误"));
					AppendLineToMultilineEditCtrl(rEdit,d);
					//接收服务器数据
					byte			buf3[64];
					ZeroMemory(buf3, 64);

					SetTimer(2,500,NULL);
					//retVal = recv(sHost,(char*) buf3, 64, 0);
					KillTimer(2);

					return -1;
				}
				/**************写数据库***********************/
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



				/***************输出到界面************************/
				try
				{
					CString a,b,c;
					if(i==0)
					{
						a.Format(_T("男宾进门数%d,男宾出门数%d,剩余人数%d"), inNum,outNum,netNum);
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
						a.Format(_T("女宾进门数%d,女宾出门数%d,剩余人数%d"), inNum,outNum,netNum);
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
		/**************************循环结束*****************************************************/


		/**************************总人数写数据库**********************************/
		try  
		{  
			CString sql_str;  

			sql_str.Format(_T("insert into %s (_id,inNum,outNum,netNum) values(%d,%d,%d,%d) ON DUPLICATE KEY UPDATE _id = VALUES(_id),inNum = VALUES(inNum),outNum = VALUES(outNum),netNum = VALUES(netNum)"),"screenrenshu",99,countNumIn,countNumOut,countNumNet);  
			if(countNumIn>=0&&countNumIn<=4000&&countNumOut>=0&&countNumOut<=4000)//加这句话，因为人数传感器会不定时发回数据，可能造成接受数据错误，此时不写数据库
				m_db_opr.ExecuteSQL(sql_str);  
		}  
		catch(CDBException* pe)  
		{  
			// The error code is in pe->m_nRetCode   
			//pe->ReportError();  
			pe->Delete();  
		}  



		//退出
		//closesocket(sHost);	//关闭套接字
		//WSACleanup();		//释放套接字资源

		//	printf("执行成功!\n");
		return 0;
	}
	catch(...)
	{
		//KillTimer(1);
		KillTimer(2);
		return -1;
	}
}



/***********************************查询温湿度函数******************************************************************/

void CBUPTGYM_renshuDlg::QueryWSD(CEdit& rEdit,CString& strIPAddr,int portnum)
{
	CString a;
	a.Format(_T("温湿度传感器连接中: %s:%d"), strIPAddr,portnum);
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
			/*********如果端口号为2012即第一个传感器，则改写全局变量的值，不写数据库，如果不是2012则全局变量求平均，改写数据库***************************************/
			float temperature = ((float)(buffer[11] << 8) + buffer[12] - 27315)/100;
			float humid =  ((float)(buffer[9] << 8) + buffer[10])/100;
			if(portnum==2012)
			{
				roomt = temperature;
				roomr = humid;

			}
			else {

				/******************************此处保证如果2012端口的传感器出现问题，那么写数据库不会把温度和湿度的平均值写进去,如果不是2012传感器出问题则方法写在函数底部**********************************/
				/******************************************
				* Author: zr.zz.alp@gmail.com
				* Time: 2014/06/03 22:59
				* TODO: 
				* 2013 端口的传感器硬件读数暂时失常，现注释掉这一部分代码，取消2013数据的读取，应对校园安全检查
				* 要记得调试好传感器后调回来
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

				/**************写数据库***********************/
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
			/***************************显示到窗口*****************************/

			try
			{
				CString a,b,c;
				a.Format(_T("馆内室温%.2f℃，馆内湿度%.2f%%"), temperature,humid);
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
			a.Format(_T("温湿度传感器Socket连接失败: %s:%d"), strIPAddr,portnum);
			AppendLineToMultilineEditCtrl(rEdit,a);

			/**************如果端口号不为2012即上面求平均写数据库的指令无法执行则在此处写数据库***********************/
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




/***********************************查询水质函数******************************************************************/




/*****************
*	下面的内容是读取余氯模块的一个大致demo
*	使用到modebus,modbus-rtu,modbus-data等模块
******************/


//Input Registers相关宏，指定了相关数据在结果集中的位置
#define		INPUP_REGS_NUM			5
#define		INDEX_DISINFECTION		0
#define		INDEX_PH				1
#define		INDEX_TEMPERATURE		2
#define		INDEX_FLOW				3
#define		INDEX_HYPOCH			4


void CBUPTGYM_renshuDlg::shuizhi(CEdit& rEdit,CString& strIPAddr)
{


	CString a;
	a.Format(_T("水质监测装置连接中: %s:%d"), strIPAddr,50001);
	AppendLineToMultilineEditCtrl(rEdit,a);


	//余氯设备网络模块的IP端口
	int ipport = 50001;


	try
	{
		//准备使用CSocket实现网络连接
		AfxSocketInit();
		CSocket _socket;
		//初始化Socket
		if(!_socket.Create())
		{
			//Socket初始化失败
			CString d;
			d.Format(_T("Socket初始化失败"));
			AppendLineToMultilineEditCtrl(rEdit,d);
			//pEdit->SetWindowTextW(_T("Socket creation failed"));
			return ;
		}
		//连接到余氯设备的网络模块
		if(!_socket.Connect(strIPAddr,ipport))
		{
			//Socket连接失败
			CString d;
			d.Format(_T("Socket连接失败"));
			AppendLineToMultilineEditCtrl(rEdit,d);
			//pEdit->SetWindowTextW(_T("Socket connection failed"));
			return ;
		}
		//查询指令
		byte command[8] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x70, 0x0d};
		//接收缓冲区，按8位字节数据组织
		byte buffer[100];
		//接收缓冲区，按照16位数据组织
		uint16_t monitorRawData[100];
		//最终的浮点数据缓冲区
		float monitorFloatData[100];
		//发送查询指令
		_socket.Send(command,8);
		Sleep(200);
		//接收数据
		int recvLen = _socket.Receive(buffer,100);
		//记录数据结束位置
		buffer[recvLen]='\0';
		//偏移量是通信的Header长度，值为1
		int offset = 1;
		//按照modbus的规范调整高低位，将8位字节数据单元重新组成16位单元
		for (int i = 0; i < recvLen; i++) {
			/* shift reg hi_byte to temp OR with lo_byte */
			monitorRawData[i] = (buffer[offset + 2 + (i << 1)] << 8) |
				buffer[offset + 3 + (i << 1)];
		}
		//将按16位组织的缓冲区中的内容转换成浮点数
		for(int i=0;i<recvLen/2;i++)
		{
			//注意这里的modbus_get_float是modbus-data模块中的内容
			monitorFloatData[i]=modbus_get_float(monitorRawData+2*i);
		}

		//此时数据既已保存在monitorFloatData中

		//将数据转化为字符串

		CString q;
		q.Format(_T("disinfection: %f, PH: %f, temp: %f,flow: %f, hypo: %f"),monitorFloatData[INDEX_DISINFECTION],monitorFloatData[INDEX_PH],monitorFloatData[INDEX_TEMPERATURE],monitorFloatData[INDEX_FLOW],monitorFloatData[INDEX_HYPOCH]);




		if(monitorFloatData[INDEX_PH]>5&&monitorFloatData[INDEX_PH]<8&&monitorFloatData[INDEX_TEMPERATURE]>10&&monitorFloatData[INDEX_TEMPERATURE]<40){
			/***************************显示到窗口*****************************/


			CString a1,dis,ph,tem,flow,hcl;
			a1.Format(_T("消毒剂%.6f，PH值%.6f，水温%.6f℃，流量%.6f，次氯酸%.6f"), monitorFloatData[INDEX_DISINFECTION],monitorFloatData[INDEX_PH],monitorFloatData[INDEX_TEMPERATURE],monitorFloatData[INDEX_FLOW],monitorFloatData[INDEX_HYPOCH]);
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

			/**************写数据库***********************/
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
			d.Format(_T("水质监测模块数据错误"));
			AppendLineToMultilineEditCtrl(rEdit,d);

		}

		_socket.Close();
		//结束
		return;
	}
	catch(...)
	{
	}
}

/************取自modbus.cpp模块，在上面函数中使用到的，用来得到浮点数***********************************/
/* Get a float from 4 bytes in Modbus format */
float modbus_get_float(const uint16_t *src)
{
	float f = 0.0f;
	uint32_t i;

	i = (((uint32_t)src[0]) << 16) + src[1];
	memcpy(&f, &i, sizeof(float));

	return f;
}


/*******************人数复位功能封装****************************/
void CBUPTGYM_renshuDlg::ResetRenShu(int sensorID,CEdit& rEdit,CString& strIPAddr)
{
	int port = 50000;
	CString a;
	a.Format(_T("\r\n重置人数传感器 %d \r\n 人数传感器连接中: %s:%d"),sensorID ,strIPAddr,port);
	AppendLineToMultilineEditCtrl(rEdit,a);
	try
	{
		AfxSocketInit();
		if(!_socket.Create())
		{
			char szMsg[1024] = {0};
			CString a;
			a.Format(_T("套接字建立失败: %d"), _socket.GetLastError());
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
			a.Format(_T("人数传感器Socket连接失败: %s:%d"), strIPAddr,port);
			AppendLineToMultilineEditCtrl(rEdit,a);
		}
		_socket.Close();
	}
	catch(...)
	{
		KillTimer(2);
	}
}

/*******************男宾复位按钮的相应处理****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton3()
{
	CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
	CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);
	CString strIPAddr;
	/******************当使用unicode字符集时候用上面这个函数，这是系统不能把LPCWSTR类型的字符串转换为LPCSTR类型，下面读取ip地址的时候需要的是LPCSTR类型，故需要转换，此方案不行，需要将项目的编码调整为混合编码，此时找不到上面的函数，需要调用下面的函数即可*/
	//pIPaddr->GetWindowTextW(strIPAddr);
	pIPaddr->GetWindowTextA(strIPAddr);
	//KillTimer(1);									//终止定时器1
	ResetRenShu(RENSHU_MAN,*pEdit,strIPAddr);
	//SetTimer(1,5000,NULL);							//恢复定时器1
}

/*******************女宾复位按钮的相应处理****************************/
void CBUPTGYM_renshuDlg::OnBnClickedButton4()
{
	CEdit * pEdit =(CEdit *) GetDlgItem(IDC_EDIT2);
	CIPAddressCtrl * pIPaddr = (CIPAddressCtrl*) GetDlgItem(IDC_IPADDRESS1);
	CString strIPAddr;
	/******************当使用unicode字符集时候用上面这个函数，这是系统不能把LPCWSTR类型的字符串转换为LPCSTR类型，下面读取ip地址的时候需要的是LPCSTR类型，故需要转换，此方案不行，需要将项目的编码调整为混合编码，此时找不到上面的函数，需要调用下面的函数即可*/
	//pIPaddr->GetWindowTextW(strIPAddr);
	pIPaddr->GetWindowTextA(strIPAddr);
	//KillTimer(1);									//终止定时器1
	ResetRenShu(RENSHU_WOMAN,*pEdit,strIPAddr);
	//SetTimer(1,5000,NULL);							//恢复定时器1
}


