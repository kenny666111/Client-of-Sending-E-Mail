// TONGXUN.cpp : implementation file
//

#include "stdafx.h"
#include "MySmtp.h"
#include "TONGXUN.h"
#include "allclass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TONGXUN dialog


TONGXUN::TONGXUN(CWnd* pParent /*=NULL*/)
	: CDialog(TONGXUN::IDD, pParent)
{
	//{{AFX_DATA_INIT(TONGXUN)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void TONGXUN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TONGXUN)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TONGXUN, CDialog)
	//{{AFX_MSG_MAP(TONGXUN)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelectUser)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TONGXUN message handlers

void TONGXUN::OnSelectUser() 
{
	// TODO: Add your control notification handler code here

                name=m_list.GetItemText(m_list.GetNextItem(-1,LVNI_SELECTED),1);
				email=m_list.GetItemText(m_list.GetNextItem(-1,LVNI_SELECTED),2);
        OnCancel();
		
}

void TONGXUN::BindGrid()//��ͨѶ¼����
{
CString strSql;
strSql = "select * from txl";//sql��ѯ���
CMyODBC db; //����CMyODBC���ʵ��
CODBCSet set;//����CODBCSet���ʵ��

/*�������ݿ⣬����access���ݿ�û���趨�û��Ϳ�//����������������ÿյ��ַ�������*/
db.ConnectDB("tx","", "");

db.PrepareSql(strSql, set);

int iRow = 0;
while(db.FetchData())/*ÿ��ȡ��һ����¼��*/
{
for(int i = 0; i < set.GetCols(); i++)
{
if(i == 0)
{
m_list.InsertItem(iRow, set.m_coldata[0].value);
}
else
{
m_list.SetItemText(iRow, i, set.m_coldata[i].value);
}
}
iRow++;
}
set.Empty();/*��ռ�¼��*/
db.DisConnect();/*�Ͽ�����*/



}



BOOL TONGXUN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.InsertColumn(0,"��ϵ�˱��",LVCFMT_CENTER,90);
	m_list.InsertColumn(1,"��ϵ������",LVCFMT_CENTER,90);
	m_list.InsertColumn(2,"��ϵ������",LVCFMT_CENTER,90);

	BindGrid();
	this->UpdateData(false);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TONGXUN::OnDelUser() //ɾ����ϵ��
{
	// TODO: Add your control notification handler code here
CString Sql;
CString id=m_list.GetItemText(m_list.GetNextItem(-1,LVNI_SELECTED),0);
Sql = "delete from txl where id=";//sql��ѯ���
Sql +=id;
CMyODBC db1; //����CMyODBC���ʵ��
db1.ConnectDB("tx","", "");
db1.ExeSqlDirect(Sql);
db1.DisConnect();/*�Ͽ�����*/
m_list.DeleteAllItems();
BindGrid();	
}
