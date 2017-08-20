/*==========================================================
模块名：输出命令                           
文件名：logprintf.cpp
相关文件：client.h  
实现功能：分层级输出命令
作者：suzhibin
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/
#include "../include/cscommon.h"
using namespace std;

extern u8 g_byLogLevel;

void OutputMsgtoUser2(u8 byloglevel,LPSTR lpstrReplayMsg)
{
	if (byloglevel <= g_byLogLevel)
	{
		cout << "msg : " << lpstrReplayMsg << endl;
	}
}

void OutPutMsg(u32 dwNum,LPSTR lpstrShowMsg)
{
	cout << "msg : " << lpstrShowMsg << " " << dwNum << endl;

}

void OutputMsgtoUser(LPSTR lpstrReplayMsg)
{
	cout << "msg : " << lpstrReplayMsg << endl;
}