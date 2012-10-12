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
	SetDlgItemText(IDC_EDIT_SENDTO,"�緢�Ͷ���ʼ�,��ַ�Զ���(\",\")�ָ�");

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
	
	CSplashWnd::ShowSplashScreen(this); //��ʾ��������
	
	HWND hwnd=::FindWindow(NULL,"VC++��ҵ��Ƴ���(�����ʼ��ͻ��˷������)");
	::ShowWindow(hwnd,SW_HIDE); //����ҵ����Ͱ������������
	Sleep(2200); //ͣ��2.2��


	::ShowWindow(hwnd,SW_SHOWNA); //2.2�����ʾ������
	
	
	
	
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

void CMySmtpDlg::OnBtnBrowser() //�򿪸�������
{
	ZFileDialog FileDlg;
	deque<string> dqTmp=FileDlg.GetOpenFileName(m_hWnd,false,"�����ļ� (*.*)\0*.*\0\0");
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

void CMySmtpDlg::OnBtnDelfile() //ɾ�����ӷ���
{
	if(m_dqFiles.size()>0)
		m_dqFiles.erase(m_dqFiles.begin()+pCombo->GetCurSel());
	pCombo->ResetContent();
	for(int j=0;j<m_dqFiles.size();j++)
		pCombo->AddString(m_dqFiles[j].substr(m_dqFiles[j].find_last_of("\\")+1).c_str());
	pCombo->SetCurSel(m_dqFiles.size()-1);
}

void CMySmtpDlg::OnBtnSend() //���͵����ʼ��¼�����
{
	UpdateData();

	ZSmtp smtp;				// smtp����
	CString strSmtpAddr;	// smtp��������ַ
	CString strAccount;		// �ʺ�
	CString strPassword;	// ����
	CString strSendfrom;	// ����Դ��ַ
	CString strSendto;		// Ŀ�ص�ַ
	CString strSenderName;	// ����������
	CString strReceiverName;// ����������
	CString strSubject;		// �ʼ�����
	CString strContent;		// �ʼ�����

	//�ռ���Ϣ

	GetDlgItemText(IDC_COMBO_SMTP       , strSmtpAddr);
	GetDlgItemText(IDC_EDIT_ACCOUNT     , strAccount);
	GetDlgItemText(IDC_EDIT_PASSWORD    , strPassword);
	GetDlgItemText(IDC_EDIT_SENDERNAME  , strSenderName);
	GetDlgItemText(IDC_EDIT_SENDFROM    , strSendfrom);
	GetDlgItemText(IDC_EDIT_RECEIVERNAME, strReceiverName);
	GetDlgItemText(IDC_EDIT_SENDTO      , strSendto);
	GetDlgItemText(IDC_EDIT_SUBJECT     , strSubject);
	GetDlgItemText(IDC_EDIT_CONTENT     , strContent);

	//��֤��Ϣ

	if(strSmtpAddr.IsEmpty())
	{
		AfxMessageBox("����дsmtp��������ַ!"); 
		return ;
	}
	if(GetDlgItemInt(IDC_EDIT_PORT)==0)
	{
		AfxMessageBox("����дsmtp�������˿ں�!"); 
		return ;	
	}
	if(strAccount.IsEmpty())
	{
		AfxMessageBox("����д�ʺ�!"); 
		return ;
	}
	if(strPassword.IsEmpty())
	{
		AfxMessageBox("����д����"); 
		return ;
	}
	if(strSenderName.IsEmpty())
	{
		AfxMessageBox("����д����������!"); 
		return ;
	}
	if(strSendfrom.IsEmpty())
	{
		AfxMessageBox("����д���͵�ַ!"); 
		return ;
	}
	if(strReceiverName.IsEmpty())
	{
		AfxMessageBox("����д����������!"); 
		return ;
	}
	if(strSendto.Find('@')==-1)
	{
		AfxMessageBox("��������ȷ�������˵�ַ!"); 
		return ;
	}
	if(strSendto.IsEmpty())
	{
		AfxMessageBox("����д�����˵�ַ!"); 
		return ;
	}
	if(strSubject.IsEmpty())
	{
		AfxMessageBox("����д�ʼ�����!"); 
		return ;
	}
	if(strContent.IsEmpty())
	{
		AfxMessageBox("����д�ʼ�����!"); 
		return ;
	}

	//���ӷ�����
	if(!smtp.Connect((LPSTR)(LPCTSTR)strSmtpAddr,GetDlgItemInt(IDC_EDIT_PORT))){
		AfxMessageBox("���ӷ�����ʧ��!"); return ;	
	}

	//��֤�ʼ��û�������
	if(!smtp.Validate((LPSTR)(LPCTSTR)strAccount,(LPSTR)(LPCTSTR)strPassword)){
		AfxMessageBox("�û���������ʧ��!"); return ;	
	}

	//׼��Ŀ�ص�ַ�б�
	ZString zstr;
	deque<string> strMails=zstr.Splitter((LPSTR)(LPCTSTR)strSendto,",");
//	CString str;
//	str.Format("%d",strMails.size());
//	AfxMessageBox(str);
//		
//	return ;
	//����
	if(!smtp.SendData((LPSTR)(LPCTSTR)strSendfrom,
				  strMails,
				  (LPSTR)(LPCTSTR)strSenderName,
				  (LPSTR)(LPCTSTR)strReceiverName,
				  (LPSTR)(LPCTSTR)strSubject,
				  (LPSTR)(LPCTSTR)strContent,
				  m_dqFiles,
				  m_IsHtml))
	{
		AfxMessageBox("�ʼ�����ʧ��!"); return ;
	}	AfxMessageBox("�ʼ����ͳɹ�!");
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

void CMySmtpDlg::OnAddUser() //�����ϵ�� 

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
db.ConnectDB("tx","", "");//�������ݿ�
if(db.ExeSqlDirect(strSql)>0)
{
MessageBox("��ӳɹ�");

}//ִ��sql���
db.DisConnect();//�Ͽ�����


}

//DEL BOOL CMySmtpDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	
//DEL 	return CDialog::Create(IDD, pParentWnd);
//DEL }


