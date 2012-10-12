; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySmtpDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MySmtp.h"

ClassCount=6
Class1=CMySmtpApp
Class2=CMySmtpDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CScrollBarEx
Resource3=IDD_MYSMTP_DIALOG
Class5=TONGXUN
Class6=CSplashWnd
Resource4=IDD_TONGXUN_DIALOG

[CLS:CMySmtpApp]
Type=0
HeaderFile=MySmtp.h
ImplementationFile=MySmtp.cpp
Filter=N
LastObject=CMySmtpApp

[CLS:CMySmtpDlg]
Type=0
HeaderFile=MySmtpDlg.h
ImplementationFile=MySmtpDlg.cpp
Filter=T
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMySmtpDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=MySmtpDlg.h
ImplementationFile=MySmtpDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_MYSMTP_DIALOG]
Type=1
Class=CMySmtpDlg
ControlCount=30
Control1=IDC_EDIT_CONTENT,edit,1353781380
Control2=IDC_EDIT_PORT,edit,1350639744
Control3=IDC_EDIT_ACCOUNT,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1350631584
Control5=IDC_EDIT_SENDERNAME,edit,1350631552
Control6=IDC_EDIT_SENDFROM,edit,1350631552
Control7=IDC_EDIT_RECEIVERNAME,edit,1350631552
Control8=IDC_EDIT_SENDTO,edit,1350631552
Control9=IDC_EDIT_SUBJECT,edit,1350631552
Control10=IDC_BTN_BROWSER,button,1342242816
Control11=IDC_BTN_DELFILE,button,1342242816
Control12=IDC_CHECK_HTML,button,1073807363
Control13=IDC_BTN_SEND,button,1342242816
Control14=IDC_BTN_ABOUT,button,1342242816
Control15=IDOK,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_COMBO_FILELIST,combobox,1344339971
Control28=IDC_COMBO_SMTP,combobox,1344339970
Control29=IDC_BUTTON1,button,1342242816
Control30=IDC_BUTTON2,button,1342242816

[CLS:CScrollBarEx]
Type=0
HeaderFile=ScrollBarEx.h
ImplementationFile=ScrollBarEx.cpp
BaseClass=CScrollBar
Filter=W

[DLG:IDD_TONGXUN_DIALOG]
Type=1
Class=TONGXUN
ControlCount=4
Control1=IDC_LIST1,SysListView32,1350631445
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUTTON2,button,1342242816

[CLS:TONGXUN]
Type=0
HeaderFile=TONGXUN.h
ImplementationFile=TONGXUN.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

