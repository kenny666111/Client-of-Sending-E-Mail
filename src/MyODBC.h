// Odbc1.h: interface for the CMyODBC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODBC1_H__DA87D10F_A7D7_4DC8_A463_B1B2B6A9A4D7__INCLUDED_)
#define AFX_ODBC1_H__DA87D10F_A7D7_4DC8_A463_B1B2B6A9A4D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ODBCSet.h"
#include <sql.h>
#include "sqltypes.h"
class CODBCSet;

class CMyODBC  
{
public:
	BOOL ConnectDB(const char *cpServerName, const char *cpUserName, const char *cpPassword);
	CMyODBC();
	virtual ~CMyODBC();

public:
	BOOL IsOpen();
	int ExecTrans(CStringList &strSqlList);
	int ConvertDataToChar();
	void ReportError(SQLHSTMT &hstmt, int iHandleType ,CString strAlert);
	long GetColLength(SQLHSTMT &hstmt,int iDataType, int iCol);
	SQLSMALLINT    GetDefaultCType(long  iODBCType);
	BOOL FetchData();
	BOOL PrepareSql(const char *cpSql, CODBCSet &rset);
	BOOL DisConnect();
	BOOL ExeSqlDirect(const char *cpSqlStmt);
	SQLHENV m_henv;
	SQLHDBC m_hdbc;
	SQLHSTMT m_hstmt;
	SQLRETURN m_retcode;
	CODBCSet *m_pSet;

};

#endif // !defined(AFX_ODBC1_H__DA87D10F_A7D7_4DC8_A463_B1B2B6A9A4D7__INCLUDED_)
