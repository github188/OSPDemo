/*==========================================================
模块名：telnet api                           
文件名：osphelp.cpp
相关文件：client.h  
实现功能：telnet窗口帮助命令
作者：suzhibin
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/
#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "WINVER.h"

//输出log等级
u8 byLogLevel = 5;
void GetVersionshow();


API void help(void)
{	
	OspPrintf(TRUE,FALSE,"\n\nversion:\n");
	OspPrintf(TRUE,FALSE,"说明:显示工程的版本信息 \n\n");

	OspPrintf(TRUE,FALSE,"logshow:\n");
	OspPrintf(TRUE,FALSE,"说明:显示当前信息输出等级.\n\n");

	OspPrintf(TRUE,FALSE,"logset [level]:\n");
	OspPrintf(TRUE,FALSE,"说明:设置信息输出等级(1 -- 5).\n\t1.程序运行错误（逻辑或业务出错），必须输出.\n\t2.告警信息，可能正确，可能出错。\n\t3.程序运行到一个关键状态时的信息输出\n\t4.普通信息，最好不要写进log文件中\n\t5.更高级别的打印\n\n");

	OspPrintf(TRUE,FALSE,"logstop:\n");
	OspPrintf(TRUE,FALSE,"说明:暂停屏幕日志输出.\n");

	OspPrintf(TRUE,FALSE,"logresume:\n");
	OspPrintf(TRUE,FALSE,"说明:恢复屏幕日志输出.\n");

	OspPrintf(TRUE,FALSE,"showinstate [id]:\n");
	OspPrintf(TRUE,FALSE,"说明:显示对应APP下所有instance状态.\tu16 aid:App id号 \n");
	
	OspPrintf(TRUE,FALSE,"showapp:\n");
	OspPrintf(TRUE,FALSE,"说明:显示所有APP的状态信息. \n");

}

API void version(void)
{
	GetVersionshow();
	OspPrintf(TRUE,FALSE,"Comments:        OSP Demo / C-S\nCompanyName:     苏州科达科技有限公司\nFileDescription: OSP-客户端\nFileVersion:     4, 0, 0, 1\nInternalName:    client\nLegalCopyright:  版权所有(C)2017.03-2017.08 苏州科达科技有限公司\nLegalTrademarks: KEDACOM\nOriginalFilename:client.exe\nProductName:     OSP—client应用程序\nProductVersion:  2, 0, 0, 1\n");
}

API void logshow()
{
	OspPrintf(TRUE,FALSE,"Now level is : %d",byLogLevel);
}

API void logset(u8 sRet)
{
	byLogLevel = sRet;
	OspPrintf(TRUE,FALSE,"Set level success,\nlevel = %d",byLogLevel);
}

API void logstop(void)
{
	OspPrintf(TRUE,FALSE,"DONE\n");
	OspStopScrnLog();
}

API void logresume(void)
{
	OspResumeScrnLog();
	OspPrintf(TRUE,FALSE,"Done.\n");
}

API void showinstate(u16 aid)
{
	OspInstShow(aid);
}

API void showapp(void)
{
	OspAppShow();
}

//获取编译时间信息
void GetVersionshow()
{
	GetVersion();
	FILETIME ftLocal;
	WIN32_FILE_ATTRIBUTE_DATA attr;
	SYSTEMTIME creation;//创建

	if (!GetFileAttributesEx("..\\..\\version\\debug\\client.exe",GetFileExInfoStandard,&attr))
	{
		logprintf(LOG_LVL_KEYSTATUS,"获取文件失败。 error:%d \n",GetLastError());
	}
	
	FileTimeToLocalFileTime(&attr.ftLastWriteTime,&ftLocal);//将世界文件时间转换成本地文件时间
	FileTimeToSystemTime(&ftLocal,&creation);//将本地文件时间转换成本地系统时间
    
	logprintf(LOG_LVL_KEYSTATUS,"编译时间:        %04d-%02d-%02d%  02d:%02d:%02d\n",creation.wYear,creation.wMonth,
	creation.wDay,creation.wHour,creation.wMinute,creation.wSecond);
}

//其他尝试
/*
void GetAppVersion()//获取版本号---未实现
{
/*	TCHAR szFullPath[CSBIGSIZE];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO *pFileInfo;

	GetModuleFileName(NULL,szFullPath,sizeof(szFullPath));
	dwVerInfoSize = GetFileVersionInfoSize(szFullPath,&dwVerHnd);

	if (dwVerInfoSize)
	{
		HANDLE hMem;
		LPVOID lpvMem;
		unsigned int dwInfoSzie = 0;

		hMem = GlobalAlloc(GMEM_MOVEABLE,dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath,dwVerHnd,dwVerInfoSize,lpvMem);

		::VerQueryValue(lpvMem,(LPSTR)_T("\\"),(void **)&pFileInfo,&dwInfoSzie);

		u32 ret = GetLastError();
		WORD m_nProdVersion[4];

		m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
        m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
        m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
        m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 
/************************************************************************/
/*    b不一样的                                                                  */
/************************************************************************//*
	int   iVerInfoSize;  
    char   *pBuf;  
    CString   asVer="";  
    VS_FIXEDFILEINFO   *pVsInfo;  
    unsigned   int   iFileInfoSize   =   sizeof(   VS_FIXEDFILEINFO   );  
	
	
    iVerInfoSize   =   GetFileVersionInfoSizeA("..\\version\\debug\\client.exe",NULL);   
	
    if(iVerInfoSize!= 0)  
    {     
        pBuf   =   new   char[iVerInfoSize];  
        if(GetFileVersionInfo("..\\version\\debug\\client.exe",0,   iVerInfoSize,   pBuf   )   )     
        {     
            if(VerQueryValue(pBuf,   "//",(void   **)&pVsInfo,&iFileInfoSize))     
            {     
                //asVer.Format("%d.%d.%d.%d",HIWORD(pVsInfo->dwFileVersionMS),LOWORD(pVsInfo->dwFileVersionMS),HIWORD(pVsInfo->dwFileVersionLS),LOWORD(pVsInfo->dwFileVersionLS));  
				logprintf(LOG_LVL_KEYSTATUS,"The file's version : %d.%d.%d.%d",HIWORD(pVsInfo->dwFileVersionMS),LOWORD(pVsInfo->dwFileVersionMS),HIWORD(pVsInfo->dwFileVersionLS),LOWORD(pVsInfo->dwFileVersionLS));
			}     
        } 
		else
		{
			logprintf(LOG_LVL_KEYSTATUS,"获取文件失败。 error:%d \n",GetLastError());
		}
        delete   pBuf;     
    }     
    //return   asVer;  
			
}*/