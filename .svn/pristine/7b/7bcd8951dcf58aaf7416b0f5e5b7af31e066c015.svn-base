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

#define MAXNUM_BUFFER  512   //buffer大小
//u8  g_byClientLog ;可分层级打印调试信息，但是这种方法不起效果。。。。如何区分Debug和Release版本？---debug需要加下划线！！
#ifdef _DEBUG
u8 g_byLogLevel = LOG_LVL_REPEAT;	//debug模式启动最高级别的打印5
#else
u8 g_byLogLevel = LOG_LVL_ERROR;
#endif


void logprintf(u8 byLevel,LPSTR lpstrFormat,...)
{
	if (NULL == lpstrFormat)
	{
		return;
	}
	if (byLevel <= g_byLogLevel)
	{
		s8 achBuf[MAXNUM_BUFFER] = {0};

		va_list args;
	    va_start(args,lpstrFormat);

		if (_vsnprintf(achBuf,sizeof(achBuf),lpstrFormat,args) > 0)
		{
			achBuf[sizeof(achBuf) - 1] = '\0';
			OspPrintf(TRUE,FALSE,"%s",achBuf);
		}

		va_end(args);
	}	
}

