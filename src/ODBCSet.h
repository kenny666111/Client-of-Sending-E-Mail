// ODBCSet.h: interface for the CODBCSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODBCSET_H__B87857A0_A997_48BD_9142_AD86790D7426__INCLUDED_)
#define AFX_ODBCSET_H__B87857A0_A997_48BD_9142_AD86790D7426__INCLUDED_

#include "MyODBC.h"	// Added by ClassView

#include <sql.h>
#include "sqltypes.h"
#include "sqlext.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
	char	name[256];
	short	datatype;
	int	maxlength;
} COL_DATAFMT_ODBC;//ÿһ�ֶε����������ƣ����ͣ�����

typedef struct
{
	char*	value;
	long *	valuelen;
}COL_DATA_ODBC;	//ÿһ�е�����,һ���ṹ������һ�е���������

typedef struct  
{
	char* value;
	long length;
}CELL_DATA_ODBC;//ÿ����Ԫ�������

class CODBCSet  
{
	public:
	int m_cols;			//��ѯ��������
	COL_DATAFMT_ODBC *m_coldatafmt;
	COL_DATA_ODBC* m_coldata;
public:
	CODBCSet();
	virtual ~CODBCSet();
	int const GetCols();
	void Empty();
	COL_DATAFMT_ODBC GetColInfo(int i);
	BOOL IsEmpty();
	class Row 
	{
		CODBCSet& m_recordset;
		int m_iRow;
	public:
		inline Row(CODBCSet& recordset, int iRow):m_recordset(recordset), m_iRow(iRow){}
	
		inline const CELL_DATA_ODBC operator[](int iCol)const 
		{ return m_recordset( iCol, m_iRow);}
		
		inline const CELL_DATA_ODBC operator[](LPCSTR strColName)const 
		{ return m_recordset(strColName, m_iRow);}
		
	};//��Row����ʾCRecordSet�е�ÿһ�У�

	inline const Row operator[](int iRow)
	{ return Row(*this, iRow); }//�õ���������

	inline const CELL_DATA_ODBC operator ()(int iCol, int iRow = 0)const//�õ�ָ���к��е�ֵ
	{
		CELL_DATA_ODBC celldata;
		celldata.value = m_coldata[iCol].value + iRow*m_coldatafmt[iCol].maxlength;
		// oracle:
		//              indicator == -1, The selected value is null, and the value of 
		//                                         the output variable is unchanged.
		//              indicator  == 0, Oracle assigned an intact value to the host variable.
		//              indicator  > 0 ,    The length of the item is greater than the length of 
		//                                         the output variable; the item has been truncated. The positive value 
		//                                         returned in the indicator variable is the actual length before truncation.
		
		celldata.length = m_coldata[iCol].valuelen[iRow];
		celldata.value[celldata.length] = 0;
		return celldata;
	}

	inline const CELL_DATA_ODBC operator ()(LPCSTR strColName, int iRow = 0)const 
	{
		CELL_DATA_ODBC celldata;
		int iCol;
		for( iCol = 0; iCol < m_cols; iCol++  )
		{
			if( strcmp(m_coldatafmt[iCol].name, strColName)== 0 )
			{
				break;
			}
		}

		if( iCol >= m_cols )
		{ // not found column according its name
			celldata.value = 0;  celldata.length = 0;
		}
		else 
		{			
			celldata.value = m_coldata[iCol].value + iRow*m_coldatafmt[iCol].maxlength;

			celldata.length = m_coldata[iCol].valuelen[iRow];

			celldata.value[celldata.length] = 0;
		}
		return celldata;
	}

	

};

#endif // !defined(AFX_ODBCSET_H__B87857A0_A997_48BD_9142_AD86790D7426__INCLUDED_)
