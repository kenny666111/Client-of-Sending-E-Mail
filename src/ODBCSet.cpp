// ODBCSet.cpp: implementation of the CODBCSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ODBCSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODBCSet::CODBCSet()
{
	m_coldata = 0;
	m_cols = 0;
	m_coldatafmt = 0; 

}

CODBCSet::~CODBCSet()
{

}

BOOL CODBCSet::IsEmpty()
{
	return m_coldata == 0;
}

COL_DATAFMT_ODBC CODBCSet::GetColInfo(int i)
{
	 return m_coldatafmt[i];

}

void CODBCSet::Empty()
{
		if(m_coldata != 0 )
		{ 
			for(int i = 0; i < m_cols; i++ ) 
			{
				delete []m_coldata[i].valuelen;
				delete []m_coldata[i].value;
					
			}
			delete []m_coldata; m_coldata = 0; 
		}
		if( m_coldatafmt != 0 ) 
		{
			delete []m_coldatafmt; m_coldatafmt = 0; 
		}

		m_cols = 0;



}



int const CODBCSet::GetCols()
{
	return (int)m_cols;
}
