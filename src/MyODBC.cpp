// Odbc1.cpp: implementation of the CMyODBC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyODBC.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma comment(lib, "ODBC32")

CMyODBC::CMyODBC()
{
	this->m_hdbc = NULL;
	this->m_henv = NULL;
	this->m_hstmt = NULL;
	this->m_retcode = 0;
	m_pSet = NULL;

}

CMyODBC::~CMyODBC()
{
	DisConnect();
	
}

BOOL CMyODBC::ConnectDB(const char *cpServerName,const char *cpUserName,const char *cpPassword)
{
	//���价�����
	m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		AfxMessageBox("���价�����ʧ��!");
		return FALSE;
	}
		/* Set the ODBC version environment attribute */
	m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_henv, SQL_HANDLE_ENV, "����odbc�汾��ʱʧ��!");
		return FALSE;
	}	
	/*�������Ӿ�� */
	m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc); 
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_henv, SQL_HANDLE_ENV,"�������Ӿ��ʧ��!");
		return FALSE;
	}

	/* �������ݿ� */
	m_retcode = SQLConnect(m_hdbc, (SQLCHAR*) cpServerName, SQL_NTS, (SQLCHAR*) cpUserName, SQL_NTS, (SQLCHAR*) cpPassword, SQL_NTS);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"�������ݿ�ʧ��!");
		return FALSE;
	}
	return TRUE;
}

			

BOOL CMyODBC::ExeSqlDirect(const char *cpSqlStmt)
{
	SQLHSTMT hStmt;
	if(this->m_hdbc == NULL)
	{
		AfxMessageBox("û���������ݿ⣬���Ƚ�������!");
		return FALSE;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &hStmt); 
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"���������ʧ��,����ִ��");
		return FALSE;
	}

	m_retcode = SQLExecDirect(hStmt, (unsigned char *)cpSqlStmt, SQL_NTS);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO) && (m_retcode != SQL_NO_DATA))
	{
		ReportError(hStmt, SQL_HANDLE_STMT, "ִ��sql���ʧ��,����ִ��");
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		hStmt = NULL;
		return FALSE;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	hStmt = NULL;
	return TRUE;
}

BOOL CMyODBC::DisConnect()
{
	if(m_hstmt != NULL)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		m_hstmt = NULL;
	}

	if(this->m_hdbc != NULL)
	{
		SQLDisconnect(m_hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
		m_hdbc = NULL;
	}
	
	if(this->m_henv != NULL)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
		m_henv = NULL;
	}

	if(this->m_pSet != NULL)
	{
		m_pSet = NULL;
	}
	return TRUE;

}

BOOL CMyODBC::PrepareSql(const char *cpSql, CODBCSet &rset)
{
	CString strWarn,  strError;;
	if(this->m_hstmt != NULL)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		m_hstmt = NULL;
	}

	if(this->m_hdbc == NULL)
	{
		AfxMessageBox("û���������ݿ⣬���Ƚ�������!");
		return FALSE;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt); 
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"���������ʧ��,����ִ��");
		return FALSE;
	}

	this->m_pSet = &rset;
	if(!m_pSet->IsEmpty())
	{
		m_pSet->Empty();
	}

	m_retcode = SQLExecDirect(m_hstmt, (unsigned char *)cpSql, SQL_NTS);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt,SQL_HANDLE_STMT, "ִ��sql���ʧ��");
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		m_hstmt = NULL;
		return FALSE;
	}
	
	SQLSMALLINT iNumCols = 0;
	m_retcode = SQLNumResultCols(m_hstmt, &iNumCols); 
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt,SQL_HANDLE_STMT,  "ȡ����ʧ��,����ִ��");
		return FALSE;
	}
	m_pSet->m_cols = iNumCols;
	m_pSet->m_coldata = new COL_DATA_ODBC[iNumCols];
	if (m_pSet->m_coldata == NULL) 
	{
		AfxMessageBox("����ÿ�����ڴ�ռ�ʧ��\n");
		return FALSE;
	}

	m_pSet->m_coldatafmt  = new COL_DATAFMT_ODBC[iNumCols];
	if(m_pSet->m_coldatafmt == NULL)
	{
		AfxMessageBox("����ÿ������Ϣ���ڴ�ռ�ʧ��\n");
		delete []m_pSet->m_coldata;
		m_pSet->m_coldata = 0;
		return FALSE;
	}

	SQLINTEGER    dataLen;
	SQLSMALLINT  SqlType, cType;   
	char   SqlColName[100];
	SQLSMALLINT StringLeng;
	SqlType = SQL_INTEGER ;

	for(int iCount = 0; iCount <iNumCols; iCount++)
	{
		m_retcode = SQLColAttribute(m_hstmt, ((SQLUSMALLINT)iCount) + 1, SQL_DESC_NAME, (SQLPOINTER)SqlColName, 100, &StringLeng, 0);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			ReportError(m_hstmt,SQL_HANDLE_STMT,"ȡ����ʱʧ��");
			return FALSE;
		}
		strncpy(m_pSet->m_coldatafmt[iCount].name, SqlColName, StringLeng);
		m_pSet->m_coldatafmt[iCount].name[StringLeng] = 0;

		m_retcode = SQLColAttribute(m_hstmt, ((SQLUSMALLINT)iCount) + 1, SQL_DESC_TYPE, NULL, 0, NULL, (SQLPOINTER)&SqlType);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			ReportError(m_hstmt,SQL_HANDLE_STMT,"ȡ���ʹ���ʱʧ��");
			return FALSE;
		}
		cType = GetDefaultCType(SqlType);
		m_pSet->m_coldatafmt[iCount].datatype = cType;
		dataLen = GetColLength(m_hstmt, SqlType,iCount+1)  ;
		m_pSet->m_coldatafmt[iCount].maxlength = dataLen + 1;
		
		m_pSet->m_coldata[iCount].valuelen = new long;
		m_pSet->m_coldata[iCount].value = new char[dataLen+1];

		if( m_pSet->m_coldata[iCount].value == NULL ||  m_pSet->m_coldata[iCount].valuelen == NULL) 
		{
			AfxMessageBox("fail: new char[]");
			delete m_pSet->m_coldata[iCount].value;
			delete m_pSet->m_coldata[iCount].valuelen;
			delete m_pSet->m_coldata;
			delete m_pSet->m_coldatafmt;
			m_pSet->m_coldata = 0;
			m_pSet->m_coldatafmt = 0;
			return FALSE;
		}
		memset(m_pSet->m_coldata[iCount].value, 0, dataLen+1);
	}
		//bind
	// 
	for(int i = 0; i < iNumCols; i++)
	{
		m_retcode = SQLBindCol(m_hstmt, ((SQLUSMALLINT)i)+1,(SQLSMALLINT)m_pSet->m_coldatafmt[i].datatype ,m_pSet->m_coldata[i].value, m_pSet->m_coldatafmt[i].maxlength, (long *)m_pSet->m_coldata[i].valuelen);

		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			strError.Format("�� %d �а�ʧ��,��ָ����������%d",i + 1, m_pSet->m_coldatafmt[i].datatype);
			ReportError(m_hstmt,SQL_HANDLE_STMT, strError);
			return FALSE;
		}
	}

	return TRUE;
}





BOOL CMyODBC::FetchData()
{
	if((m_retcode = SQLFetch(m_hstmt)) != SQL_NO_DATA)
	{
		ConvertDataToChar();
		return TRUE;
		
	}
	else
	{
		if(m_hstmt != NULL)
		{
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
			m_hstmt = NULL;
		}
		return FALSE;
	}

}

//iColumnIndex������ʾ�е���ţ���1��ʼ����
SQLSMALLINT   CMyODBC::GetDefaultCType(long iODBCType)
{
	CString strWarn;
	SQLSMALLINT      iResult;
	switch(iODBCType)
	{
	case SQL_VARCHAR:
	case SQL_CHAR:
	case SQL_DECIMAL:
	case SQL_NUMERIC:
	case SQL_DOUBLE:
	case SQL_SMALLINT:
	case SQL_INTEGER:
	case SQL_FLOAT:
	case SQL_REAL:     
		iResult = SQL_C_CHAR; 
		break;
	case SQL_DATETIME:
		iResult = SQL_C_TYPE_TIMESTAMP;
		break;
	default:
		strWarn.Format("��֧������ת��--%d", iODBCType);
		AfxMessageBox(strWarn);
		iResult = -1;
		break;
	}
	return iResult;

}

long CMyODBC::GetColLength(SQLHSTMT &hstmt,int iDataType, int iCol)
{
	long lTemp = 0, lResult = -1;
	switch(iDataType)
	{

	case SQL_CHAR:
	case SQL_VARCHAR:
		m_retcode = SQLColAttribute(hstmt, (SQLUSMALLINT)iCol, SQL_DESC_OCTET_LENGTH, NULL, 0, NULL, (SQLPOINTER)&lResult);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			AfxMessageBox("ȡ�г���ʱʧ��");
			return FALSE;
		}
		break;
	case SQL_NUMERIC:
	case SQL_DECIMAL:
	case SQL_DOUBLE:
	case SQL_SMALLINT:
	case SQL_INTEGER:
	case SQL_FLOAT:
	case SQL_REAL:    
		m_retcode = SQLColAttribute(hstmt, (SQLUSMALLINT)iCol, SQL_DESC_PRECISION, NULL, 0, NULL, (SQLPOINTER)&lResult);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			AfxMessageBox("ȡ���������ֵĳ���ʱʧ��");
			return FALSE;
		}

		m_retcode = SQLColAttribute(hstmt, (SQLUSMALLINT)iCol, SQL_DESC_SCALE, NULL, 0, NULL, (SQLPOINTER)&lTemp);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			AfxMessageBox("ȡ��С������ʱʧ��");
			return FALSE;
		}
		lResult += lTemp ;
		break;

	case SQL_DATETIME:
		m_retcode = SQLColAttribute(hstmt, (SQLUSMALLINT)iCol, SQL_DESC_PRECISION, NULL, 0, NULL, (SQLPOINTER)&lResult);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			AfxMessageBox("ȡ���������ֵĳ���ʱʧ��");
			return FALSE;
		}

		m_retcode = SQLColAttribute(hstmt, (SQLUSMALLINT)iCol, SQL_DESC_SCALE, NULL, 0, NULL, (SQLPOINTER)&lTemp);
		if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
		{
			AfxMessageBox("ȡ��С������ʱʧ��");
			return FALSE;
		}
		lResult += lTemp + 1;
		break;

		default:
			AfxMessageBox("��֧����������");
			break;
	}

	return lResult ;

}

void CMyODBC::ReportError(SQLHSTMT &hstmt, int iHandleType ,CString strAlert)
{
	
	unsigned char *SQLState = new unsigned char[6];
	if(SQLState == NULL)
	{
		AfxMessageBox("���淢�������ԭ��ʱ������sqlstat�ڴ�ʧ��");
		return;
	}
	char Message[500] = "\0";
	short iMesLen;
	CString strError;
	SQLGetDiagRec(iHandleType, hstmt, 1, SQLState, NULL, (unsigned char  *)Message, 500, &iMesLen);
	strError.Format("%s,%s" , strAlert, Message);
	AfxMessageBox(strError);
	delete SQLState; SQLState= NULL;
}



int CMyODBC::ConvertDataToChar()
{
	int i;
	TIMESTAMP_STRUCT timeStamp;

	for(i = 0; i < m_pSet->GetCols(); i++)
	{
		if(*(m_pSet->m_coldata[i].valuelen) == -1)//�����ֵΪ��
		{
			memset(m_pSet->m_coldata[i].value, 0, m_pSet->m_coldatafmt[i].maxlength);
			*(m_pSet->m_coldata[i].valuelen) = m_pSet->m_coldatafmt[i].maxlength - 1;
			continue;
		}
		
		switch (m_pSet->m_coldatafmt[i].datatype)
		{
		case SQL_C_CHAR:
			break;

		case SQL_C_TYPE_TIMESTAMP:
			timeStamp.year = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->year;
			timeStamp.month = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->month;
			timeStamp.day = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->day;
			timeStamp.hour = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->hour;
			timeStamp.minute = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->minute;
			timeStamp.second = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->second;
			timeStamp.fraction = ((TIMESTAMP_STRUCT *)m_pSet->m_coldata[i].value)->fraction;
			sprintf(m_pSet->m_coldata[i].value, "%4u-%2u-%2u %2u:%2u:%2u", timeStamp.year, timeStamp.month, timeStamp.day, timeStamp.hour, timeStamp.minute, timeStamp.second);
			*(m_pSet->m_coldata[i].valuelen) = 19;
			break;
		default:
			AfxMessageBox("��û��֧�������������͵�ת��");
			return -1;
		}
	}
	return 0;
		

}

int CMyODBC::ExecTrans(CStringList &strSqlList)
{
	POSITION pos;
	CString strSql;
	BOOL bStatus;
	int iReturn = 0;
	if(m_hdbc == NULL)
	{
		AfxMessageBox("���Ӿ��Ϊ�գ�����ִ��");
		return -1;
	}
	//�����ύ��ʽΪ�ֶ�
	m_retcode = ::SQLSetConnectOption(m_hdbc, SQL_AUTOCOMMIT,	SQL_AUTOCOMMIT_OFF);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"�����ֶ��ύ��ʽʧ��");
		return -1;
	}
	
	//ִ��sql
	for(pos = strSqlList.GetHeadPosition(); pos != NULL;)
	{
		strSql = strSqlList.GetNext(pos);
		bStatus = this->ExeSqlDirect(strSql); 
		if(bStatus == FALSE)//ִ��ʧ�ܣ��ع�
		{
			m_retcode = ::SQLEndTran(SQL_HANDLE_DBC, m_hdbc, SQL_ROLLBACK);
			if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
			{
				ReportError(m_hdbc, SQL_HANDLE_DBC,"ִ������ʧ�ܣ����һع�ʧ��");
			}
			iReturn = -1;
			goto RESET_AUTO_COMMIT;
		}
	}
	//�ύ
	m_retcode = ::SQLEndTran(SQL_HANDLE_DBC, m_hdbc, SQL_COMMIT);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"ִ��������ɺ��ύʧ��");
		iReturn = -1;
	}
	//�ٰ��ύ��ʽ��Ϊ�Զ�
RESET_AUTO_COMMIT:
	m_retcode = ::SQLSetConnectOption(m_hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
	if ((m_retcode != SQL_SUCCESS) && (m_retcode != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hdbc, SQL_HANDLE_DBC,"�����Զ��ύ��ʽʧ��");
		iReturn = -1;
	}

	return iReturn;

}

//�����������ܼ�鵽���ݿ��Ƿ��Ѿ����ˡ�

BOOL CMyODBC::IsOpen()
{
	if(this->m_henv == NULL)
	{
		return FALSE;
	}

	if(this->m_hdbc == NULL)
	{
		return FALSE;
	}
	return TRUE;

}
