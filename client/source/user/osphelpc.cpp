/*==========================================================
ģ������telnet api                           
�ļ�����osphelp.cpp
����ļ���client.h  
ʵ�ֹ��ܣ�telnet���ڰ�������
���ߣ�suzhibin
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/
#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "WINVER.h"

//���log�ȼ�
u8 byLogLevel = 5;
void GetVersionshow();


API void help(void)
{	
	OspPrintf(TRUE,FALSE,"\n\nversion:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ���̵İ汾��Ϣ \n\n");

	OspPrintf(TRUE,FALSE,"logshow:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ��ǰ��Ϣ����ȼ�.\n\n");

	OspPrintf(TRUE,FALSE,"logset [level]:\n");
	OspPrintf(TRUE,FALSE,"˵��:������Ϣ����ȼ�(1 -- 5).\n\t1.�������д����߼���ҵ��������������.\n\t2.�澯��Ϣ��������ȷ�����ܳ���\n\t3.�������е�һ���ؼ�״̬ʱ����Ϣ���\n\t4.��ͨ��Ϣ����ò�Ҫд��log�ļ���\n\t5.���߼���Ĵ�ӡ\n\n");

	OspPrintf(TRUE,FALSE,"logstop:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ͣ��Ļ��־���.\n");

	OspPrintf(TRUE,FALSE,"logresume:\n");
	OspPrintf(TRUE,FALSE,"˵��:�ָ���Ļ��־���.\n");

	OspPrintf(TRUE,FALSE,"showinstate [id]:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ��ӦAPP������instance״̬.\tu16 aid:App id�� \n");
	
	OspPrintf(TRUE,FALSE,"showapp:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ����APP��״̬��Ϣ. \n");

}

API void version(void)
{
	GetVersionshow();
	OspPrintf(TRUE,FALSE,"Comments:        OSP Demo / C-S\nCompanyName:     ���ݿƴ�Ƽ����޹�˾\nFileDescription: OSP-�ͻ���\nFileVersion:     4, 0, 0, 1\nInternalName:    client\nLegalCopyright:  ��Ȩ����(C)2017.03-2017.08 ���ݿƴ�Ƽ����޹�˾\nLegalTrademarks: KEDACOM\nOriginalFilename:client.exe\nProductName:     OSP��clientӦ�ó���\nProductVersion:  2, 0, 0, 1\n");
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

//��ȡ����ʱ����Ϣ
void GetVersionshow()
{
	GetVersion();
	FILETIME ftLocal;
	WIN32_FILE_ATTRIBUTE_DATA attr;
	SYSTEMTIME creation;//����

	if (!GetFileAttributesEx("..\\..\\version\\debug\\client.exe",GetFileExInfoStandard,&attr))
	{
		logprintf(LOG_LVL_KEYSTATUS,"��ȡ�ļ�ʧ�ܡ� error:%d \n",GetLastError());
	}
	
	FileTimeToLocalFileTime(&attr.ftLastWriteTime,&ftLocal);//�������ļ�ʱ��ת���ɱ����ļ�ʱ��
	FileTimeToSystemTime(&ftLocal,&creation);//�������ļ�ʱ��ת���ɱ���ϵͳʱ��
    
	logprintf(LOG_LVL_KEYSTATUS,"����ʱ��:        %04d-%02d-%02d%  02d:%02d:%02d\n",creation.wYear,creation.wMonth,
	creation.wDay,creation.wHour,creation.wMinute,creation.wSecond);
}

//��������
/*
void GetAppVersion()//��ȡ�汾��---δʵ��
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
/*    b��һ����                                                                  */
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
			logprintf(LOG_LVL_KEYSTATUS,"��ȡ�ļ�ʧ�ܡ� error:%d \n",GetLastError());
		}
        delete   pBuf;     
    }     
    //return   asVer;  
			
}*/