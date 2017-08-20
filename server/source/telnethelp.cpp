/*==========================================================
ģ������telnet api                           
�ļ�����telnethelp.cpp
����ļ���server.h  
ʵ�ֹ��ܣ�telnet���ڰ�������
���ߣ�suzhibin
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

//���log�ȼ�
u8 byLogLevel = LOG_LVL_REPEAT;
void GetVersionshow();

API void help(void)
{
	OspPrintf(TRUE,FALSE,"\n\nversion:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ���̵İ汾��Ϣ \n\n");

	OspPrintf(TRUE,FALSE,"\n\nversion:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ���̵İ汾��Ϣ \n\n");

	OspPrintf(TRUE,FALSE,"logshow:\n");
	OspPrintf(TRUE,FALSE,"˵��:��ʾ��ǰ��Ϣ����ȼ�.\n\n");

	OspPrintf(TRUE,FALSE,"logset [level]:\n");
	OspPrintf(TRUE,FALSE,"˵��:������Ϣ����ȼ�(1 -- 5).\n\t1.�������д����߼���ҵ����������������.\n\t2.�澯��Ϣ��������ȷ�����ܳ�����\n\t3.�������е�һ���ؼ�״̬ʱ����Ϣ���\n\t4.��ͨ��Ϣ����ò�Ҫд��log�ļ���\n\t5.���߼���Ĵ�ӡ\n\n");

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
	OspPrintf(TRUE,FALSE,"Comments:        OSP Demo / C-S\nCompanyName:     ���ݿƴ�Ƽ����޹�˾\nFileDescription: OSP-������\nFileVersion:     4, 0, 0, 1\nInternalName:    server\nLegalCopyright:  ��Ȩ����(C)2017.03-2017.08 ���ݿƴ�Ƽ����޹�˾\nLegalTrademarks: KEDACOM\nOriginalFilename:server.exe\nProductName:     OSP��serverӦ�ó���\nProductVersion:  2, 0, 0, 1\n");
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
	GetVersion();//��������----���õ����Ʋ��ԣ�
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