/*==========================================================
模块名：主程序                           
文件名：main.cpp
相关文件：iostream.h  client.h  cscommon.h
实现功能：创建app
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/

#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "shellapi.h"
extern CClientMsgApp  g_CClientApp;		//模板类实例化
extern CClientFileApp g_CClientFileApp;

extern struct Buffer BufOne;			//文件读取缓存区
extern struct Buffer Buftwo;

using namespace std;

int main()
{

    s8* pchModuleName = "ClientDate";   //模块名
    cbShowMsgtoConsole("****开始初始化****",OutputMsgtoUser); 

    BOOL32 bOpenTel = FALSE;
#ifdef _DEBUG
	bOpenTel = TRUE;
//	HWND handle = GetDesktopWindow();

//	system("cd C:\\Users\\灼灼\\");
//	system("telnet 127.0.0.1 2673");
//	WinExec("cmd.exe",SW_SHOW);
//	WinExec("cd \\",SW_NORMAL);
//	WinExec("telnet 127.0.0.1 2673",SW_NORMAL);
	//ShellExecute(handle,NULL,"cmd.exe","telnet 127.0.0.1 2673",NULL,SW_SHOWNORMAL);
//	CreateProcess("C:\\Users\\灼灼\\", "telnet 127.0.0.1 2673", NULL, NULL, NULL, 
//                                    CREATE_NEW_CONSOLE | CREATE_NO_WINDOW, NULL, "C:\\WINDOWS\\system32\\telnet.exe",NULL, NULL);
#endif


	if(FALSE == IsOspInitd())
	{
		 OspInit(bOpenTel,CLIENT_TELENT_PORT);    //初始化osp，在端口2673启动telnet 
		 OspRegistModule(pchModuleName);
	}

    g_CClientApp.CreateApp(CLIENT_APP_NAME,CLIENT_MSGAPP_NO,CLIENT_APP_PRIO,CLIENT_APP_QUE_SIZE);
    g_CClientFileApp.CreateApp(CLIENT_FILEAPP_NAME,CLIENT_FILEAPP_NO,CLIENT_APP_PRIO,CLIENT_FILEAPP_QUE_SIZE);
	
	OspCreateTcpNode(0,CLIENT_LISTEN_PORT);            //在6682端口创建本地监听结点
	if(TRUE == OspSetPrompt("SuShareClient"))		   //设置telnet终端提示符
	{ 
		cbShowMsgtoConsole("****set osp telnet string succeed****",OutputMsgtoUser); 
	}
	else
	{
		cbShowMsgtoConsole("****set osp telnet string failed****",OutputMsgtoUser); 
	}

//	s8 ach[20] = "telnet.exe";
//	CreateProcess(ach);

    Interface();	//界面
    return 0;
}

