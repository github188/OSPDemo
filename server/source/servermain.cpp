/*==========================================================
ģ������������������                           
�ļ�����mainserver.cpp
����ļ���iostream.h  server.h  cscommon.h
ʵ�ֹ��ܣ�����server
���ߣ���־��
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/
#include "../include/server.h"
#include "../include/serverfile.h"
#include "../../include/cscommon.h"
#include "iostream"
#include "conio.h" //kbhit()���ڵĿ⺯��
#include "math.h"	//pow���ڿ⺯��

using namespace std;

CServerApp g_CServerApp;//ʵ����ģ����
CSFileApp g_CSFileApp;


void main(int argc,char argv[])
{
    u32 dwRetVal;						//osp�������ӷ���ֵ
    s8* pchModulName = "ServerDate";	//ģ����
	
	cbShowMsgtoConsole("server app.Init__",OutputMsgtoUser);
	cbShowMsgtoConsole("telnet port__2667",OutputMsgtoUser);

	if (FALSE == IsOspInitd())			//�ж�osp�Ƿ��ʼ��
	{
		OspInit(TRUE,SERVER_TELENT_PORT,pchModulName);     //��ʼ��OSP���ڶ˿�2606����telnet
	}
       
	cbShowMsgtoConsole("server CreateApp__",OutputMsgtoUser);

    g_CServerApp.CreateApp(SERVER_MSGAPP_NAME,SERVER_MSGAPP_NO,SERVER_APP_PRIO,SERVER_APP_QUE_SIZE,200<<10);
    g_CSFileApp.CreateApp(SERVER_FILEAPP_NAME,SERVER_FILEAPP_NO,SERVER_APP_PRIO,FILE_APP_QUE_SIZE,200<<15);

	if(TRUE == OspSetPrompt("SuShareServer"))	//�����ն���ʾ��
	{
		cbShowMsgtoConsole("****set osp telnet string succeed****",OutputMsgtoUser);
	}
	else
	{
		cbShowMsgtoConsole("****set osp telnet string failed****",OutputMsgtoUser);
	}

	//���ô洢�ռ��С
    cbShowMsgtoConsole("�����ô洢�ļ��ռ��С. ",OutputMsgtoUser);
    u32 dwFileStore;
	g_CServerApp.CServerAppClear(); //��ʼ���ռ��С
	while(TRUE)	//�ļ���С����---�����ⲻ����
	{
		if (kbhit())		//���������롣��
		{
			//�������룬����
			scanf("%d",&dwFileStore);
			float Temp = pow(10,-6.0);		//��ʹ�ú궨�����----����
			if ((dwFileStore - (u32)dwFileStore < Temp) && (dwFileStore- (u32)dwFileStore > -Temp))
			{
				cbShowNumToConsole(dwFileStore," ������ȷ,size = ",OutPutMsg);
				g_CServerApp.SetFileLeftStore(dwFileStore);
				break;
			}
			else
			{
				cbShowMsgtoConsole("�������",OutputMsgtoUser);
			}
		}
		else
		{
			//Sleep(WAITED_TIME);
			cbShowNumToConsole(SERVER_DEFAULT_SIZE," ����ΪĬ��ֵ,size = ",OutPutMsg);
			g_CServerApp.SetFileLeftStore(SERVER_DEFAULT_SIZE);
			break;
		}
	}
	
    cbShowMsgtoConsole("set file store size success. ",OutputMsgtoUser);
	
	//�����ļ��ӿ�---�жϹ̶��ļ��еô�С
	u32 dwFolderSize = GetFolderSize("../uploadfile");

	cout << "��ǰ�ļ��д�С��" << dwFolderSize << endl;
	cout << "��ǰ�ļ���ʣ���С��" << (g_CServerApp.GetFileLeftStore() - dwFolderSize)<< endl;



    dwRetVal = OspCreateTcpNode(0,SERVER_LISTEN_PORT);          //��6688�˿ڽ����������;
    //�ɹ����ش�����Socket��������ʧ�ܷ���INVALID_SOCKET
    if (INVALID_SOCKET == dwRetVal)
    {
		cbShowMsgtoConsole("server Create Node Failed",OutputMsgtoUser);
		logprintf(LOG_LVL_ERROR,"Server Create Node Failed!\n");
        OspQuit();
        return;
    }
    else
    {
		cbShowMsgtoConsole("server Create Node succeed",OutputMsgtoUser);
		logprintf(LOG_LVL_KEYSTATUS,"Server Create Node succeed!\n");
    }

    while(TRUE)
    {
        Sleep(CSLITTLESIZE);
    }
}




