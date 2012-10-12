
#ifndef _ZTHUNK
#define _ZTHUNK

class ZThunk  
{
private:
	unsigned char m_ThiscallCode[10];
	unsigned char m_StdcallCode[16];
public:
	enum CALLINGCONVENTIONS
	{
		STDCALL = 1,
		THISCALL= 2
	};
public:
	template <class T>
	void* Callback(void* pThis,T MemberOffset,CALLINGCONVENTIONS CallingConvention = STDCALL)
	{
		// these codes only use in stdcall
		if(CallingConvention == STDCALL)
		{
			// Encoded machine instruction   Equivalent assembly languate notation
			// ---------------------------   -------------------------------------
			// FF 34 24                      push  dword ptr [esp]          ; Save (or duplicate)                                                                    ; the Return Addr into stack
			// C7 44 24 04 ?? ?? ?? ??       mov   dword ptr [esp+4], pThis ; Overwite the old                                                                    ; Return Addr with 'this pointer'
			// E9 ?? ?? ?? ??                jmp   target addr              ; Jump to target message handler

			char Buf[33]={0};
			sprintf(Buf,"%d",MemberOffset);
			unsigned long JmpAddr = (unsigned long) atol(Buf) - (unsigned long) &m_StdcallCode[0] - 16;

			m_StdcallCode[11] = 0xE9; 
			*((unsigned long *)  &m_StdcallCode[ 0]) = 0x002434FF;
			*((unsigned long *)  &m_StdcallCode[ 3]) = 0x042444C7;
			*((unsigned long *)  &m_StdcallCode[ 7]) = (unsigned long) pThis;
			*((unsigned long *)  &m_StdcallCode[12]) = JmpAddr;

			return (void*)m_StdcallCode;
		}
		// these codes only use in thiscall
		else if(CallingConvention == THISCALL)
		{
			// Encoded machine instruction   Equivalent assembly languate notation
			// ---------------------------   -------------------------------------
			// B9 ?? ?? ?? ??                mov    ecx, pThis  ; Load ecx with this pointer
			// E9 ?? ?? ?? ??                jmp    target addr ; Jump to target message handler

			char Buf[33]={0};
			sprintf(Buf,"%d",MemberOffset);
			unsigned long JmpAddr = (unsigned long) atol(Buf) - (unsigned long) &m_ThiscallCode[0] - 10;

			m_ThiscallCode[0] = 0xB9;
			m_ThiscallCode[5] = 0xE9;
			*((unsigned long *) &m_ThiscallCode[1]) = (unsigned long) pThis;
			*((unsigned long *) &m_ThiscallCode[6]) = JmpAddr;

			return (void*)m_ThiscallCode;
		}return 0;
	}
};

#endif
