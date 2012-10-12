// MySmtpDlg.cpp : implementation file
//
#include "window.h"
#include "stdafx.h"
#include "MySmtp.h"
#include "MySmtpDlg.h"
#include "TONGXUN.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySmtpDlg dialog

CMySmtpDlg::CMySmtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySmtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySmtpDlg)
	m_IsHtml = FALSE;
	m_name = _T("");
	m_email = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySmtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySmtpDlg)
	DDX_Check(pDX, IDC_CHECK_HTML, m_IsHtml);
	DDX_Text(pDX, IDC_EDIT_RECEIVERNAME, m_name);
	DDX_Text(pDX, IDC_EDIT_SENDTO, m_email);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMySmtpDlg, CDialog)
	//{{AFX_MSG_MAP(CMySmtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_BROWSER, OnBtnBrowser)
	ON_BN_CLICKED(IDC_BTN_DELFILE, OnBtnDelfile)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnAddUser)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySmtpDlg message handlers

BOOL CMySmtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//SetDlgItemText(IDC_EDIT_SMTP,"smtp.163.com");

	CComboBox* pComSmtp=(CComboBox*)GetDlgItem(IDC_COMBO_SMTP);
	pComSmtp->AddString("smtp.163.com");
	pComSmtp->AddString("smtp.126.com");
	pComSmtp->SetCurSel(0);
	SetDlgItemText(IDC_EDIT_PORT,"25");
	SetDlgItemText(IDC_EDIT_SENDTO,"如发送多个邮件,地址以豆号(\",\")分隔");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMySmtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMySmtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
int CMySmtpDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CSplashWnd::ShowSplashScreen(this); //显示启动画面
	
	HWND hwnd=::FindWindow(NULL,"VC++毕业设计程序(电子邮件客户端发送软件)");
	::ShowWindow(hwnd,SW_HIDE); //如果找到，就把这个窗体隐藏
	Sleep(2200); //停留2.2秒


	::ShowWindow(hwnd,SW_SHOWNA); //2.2秒后显示主窗体
	
	
	
	
	return 0;
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMySmtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMySmtpDlg::OnBtnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMySmtpDlg::OnBtnBrowser() //打开附件方法
{
	ZFileDialog FileDlg;
	deque<string> dqTmp=FileDlg.GetOpenFileName(m_hWnd,false,"所有文件 (*.*)\0*.*\0\0");
	if(dqTmp.size()<=0) return ;

	bool IsRepeat=false;
	for(int i=0;i<m_dqFiles.size();i++)
	{
		if(m_dqFiles[i]==dqTmp[0])
		{
			IsRepeat=true;
			break;
		}
	}
	if(!IsRepeat) m_dqFiles.push_back(dqTmp[0]);

	pCombo=(CComboBox*)GetDlgItem(IDC_COMBO_FILELIST);
	pCombo->ResetContent();
	for(int j=0;j<m_dqFiles.size();j++)
		pCombo->AddString(m_dqFiles[j].substr(m_dqFiles[j].find_last_of("\\")+1).c_str());
	pCombo->SetCurSel(m_dqFiles.size()-1);
}

void CMySmtpDlg::OnBtnDelfile() //删除附加方法
{
	if(m_dqFiles.size()>0)
		m_dqFiles.erase(m_dqFiles.begin()+pCombo->GetCurSel());
	pCombo->ResetContent();
	for(int j=0;j<m_dqFiles.size();j++)
		pCombo->AddString(m_dqFiles[j].substr(m_dqFiles[j].find_last_of("\\")+1).c_str());
	pCombo->SetCurSel(m_dqFiles.size()-1);
}

void CMySmtpDlg::OnBtnSend() //发送电子邮件事件方法
{
	UpdateData();

	ZSmtp smtp;				// smtp对像
	CString strSmtpAddr;	// smtp服务器地址
	CString strAccount;		// 帐号
	CString strPassword;	// 密码
	CString strSendfrom;	// 发送源地址
	CString strSendto;		// 目地地址
	CString strSenderName;	// 发送者姓名
	CString strReceiverName;// 接收者姓名
	CString strSubject;		// 邮件主题
	CString strContent;		// 邮件正文

	//收集信息

	GetDlgItemText(IDC_COMBO_SMTP       , strSmtpAddr);
	GetDlgItemText(IDC_EDIT_ACCOUNT     , strAccount);
	GetDlgItemText(IDC_EDIT_PASSWORD    , strPassword);
	GetDlgItemText(IDC_EDIT_SENDERNAME  , strSenderName);
	GetDlgItemText(IDC_EDIT_SENDFROM    , strSendfrom);
	GetDlgItemText(IDC_EDIT_RECEIVERNAME, strReceiverName);
	GetDlgItemText(IDC_EDIT_SENDTO      , strSendto);
	GetDlgItemText(IDC_EDIT_SUBJECT     , strSubject);
	GetDlgItemText(IDC_EDIT_CONTENT     , strContent);

	//验证信息

	if(strSmtpAddr.IsEmpty())
	{
		AfxMessageBox("请填写smtp服务器地址!"); 
		return ;
	}
	if(GetDlgItemInt(IDC_EDIT_PORT)==0)
	{
		AfxMessageBox("请填写smtp服务器端口号!"); 
		return ;	
	}
	if(strAccount.IsEmpty())
	{
		AfxMessageBox("请填写帐号!"); 
		return ;
	}
	if(strPassword.IsEmpty())
	{
		AfxMessageBox("请填写密码"); 
		return ;
	}
	if(strSenderName.IsEmpty())
	{
		AfxMessageBox("请填写发送者姓名!"); 
		return ;
	}
	if(strSendfrom.IsEmpty())
	{
		AfxMessageBox("请填写发送地址!"); 
		return ;
	}
	if(strReceiverName.IsEmpty())
	{
		AfxMessageBox("请填写接收者姓名!"); 
		return ;
	}
	if(strSendto.Find('@')==-1)
	{
		AfxMessageBox("请输入正确的收信人地址!"); 
		return ;
	}
	if(strSendto.IsEmpty())
	{
		AfxMessageBox("请填写收信人地址!"); 
		return ;
	}
	if(strSubject.IsEmpty())
	{
		AfxMessageBox("请填写邮件主题!"); 
		return ;
	}
	if(strContent.IsEmpty())
	{
		AfxMessageBox("请填写邮件内容!"); 
		return ;
	}

	//连接服务器
	if(!smtp.Connect((LPSTR)(LPCTSTR)strSmtpAddr,GetDlgItemInt(IDC_EDIT_PORT))){
		AfxMessageBox("连接服务器失败!"); return ;	
	}

	//验证邮件用户名密码
	if(!smtp.Validate((LPSTR)(LPCTSTR)strAccount,(LPSTR)(LPCTSTR)strPassword)){
		AfxMessageBox("用户名或密码失败!"); return ;	
	}

	//准备目地地址列表
	ZString zstr;
	deque<string> strMails=zstr.Splitter((LPSTR)(LPCTSTR)strSendto,",");
//	CString str;
//	str.Format("%d",strMails.size());
//	AfxMessageBox(str);
//		
//	return ;
	//发送
	if(!smtp.SendData((LPSTR)(LPCTSTR)strSendfrom,
				  strMails,
				  (LPSTR)(LPCTSTR)strSenderName,
				  (LPSTR)(LPCTSTR)strReceiverName,
				  (LPSTR)(LPCTSTR)strSubject,
				  (LPSTR)(LPCTSTR)strContent,
				  m_dqFiles,
				  m_IsHtml))
	{
		AfxMessageBox("邮件发送失败!"); return ;
	}	AfxMessageBox("邮件发送成功!");
}


void CMySmtpDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	TONGXUN tx;
	int nret;
	nret=tx.DoModal();
	if(nret==IDCANCEL)
	{
	m_name=tx.name;
	m_email=tx.email;
	
	}
		this->UpdateData(false);
}

void CMySmtpDlg::OnAddUser() //添加联系人 

{
	// TODO: Add your control notification handler code here
UpdateData(TRUE);
CString strSql;
strSql="insert into txl (name,email) values ('";
strSql+=m_name;
strSql+="' ,'";
strSql+=m_email;
strSql+="')";
CMyODBC db;
db.ConnectDB("tx","", "");//连接数据库
if(db.ExeSqlDirect(strSql)>0)
{
MessageBox("添加成功");

}//执行sql语句
db.DisConnect();//断开连接


}

//DEL BOOL CMySmtpDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	
//DEL 	return CDialog::Create(IDD, pParentWnd);
//DEL }


