/*==========================================================
��������DaemonProcMsgSendCmd
���ܣ��ͻ���daemon������Ϣ����
�㷨ʵ�֣��õ���strtok 
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../../include/client.h"
#include "../../../include/cscommon.h"

extern UCinfo tClientInfo;		//����ͻ�����Ϣ

void CCDateInstance::DaemonProcMsgSendCmd(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		cbShowMsgtoConsole("�������ӷ�����!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_KEYSTATUS,"Daemon: recv send msg cmd.\n");
	    //������Ϣ
		s8 achContent[CSMIDDLESIZE] = {0};		   //������Ϣ����
		s8 achMsgContent[CSMIDDLESIZE] = {0};	   //��Ϲ㲥��Ϣ
		s8 achMsgSingleContent[CSMIDDLESIZE] = {0}; //��ϵ�����Ϣ---ֱ�ӷ�����Ϣ����
		
		memcpy(achContent,pMsg->content,pMsg->length);
		memcpy(achMsgSingleContent,pMsg->content,pMsg->length);
		
		u16 w_InsNum = atoi(strtok(achContent,","));//ǿ��ת���жϷ��Ͷ���
		
		//�����Ϣ���ù㲥��Ϣ����Ϣ��Դ��ʾ
		strcpy(achMsgContent,m_achusername);
		strcat(achMsgContent," said to you:");
		strcat(achMsgContent,strtok(NULL,"\0"));
		
		if (0 == w_InsNum) //�㲥��Ϣ����������Daemon
		{
			post(MAKEIID(SERVER_MSGAPP_NO,CInstance::DAEMON),C_S_SENDMSG_REQ,achMsgContent,sizeof(achMsgContent),m_dwServerNode);
		} 
		else        //������Ϣ������ӦInstance
		{
			post(m_dwServerId,C_S_SENDMSG_REQ,achMsgSingleContent,sizeof(achMsgSingleContent),m_dwServerNode);
		}
    }   	
}

void CCDateInstance::DaemonProcSendMsgAck(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		logprintf(LOG_LVL_DETAIL,"Daemon: post msg to man succeed.\n ");
		cbShowMsgtoConsole("��Ϣ���ͳɹ�!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR �յ�������Ϣack");
		cbShowMsgtoConsole("Daemon:ERROR �յ�������Ϣack.",OutputMsgtoUser);
	}		
}


void CCDateInstance::DaemonProcSendMsgNack(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		logprintf(LOG_LVL_DETAIL,"Daemon: post msg to man fail.\n ");
		cbShowMsgtoConsole("��Ϣ����ʧ��!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR �յ�������Ϣnack");
		cbShowMsgtoConsole("Daemon:ERROR �յ�������Ϣnack.",OutputMsgtoUser);
	}		
}


void CCDateInstance::DaemonProcSendMsgNoti(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		s8 achMsgContent[CSMIDDLESIZE] = {0};
		cbShowMsgtoConsole("�յ���Ϣ��",OutputMsgtoUser);         
		memcpy(achMsgContent,pMsg->content,pMsg->length);
		cbShowMsgtoConsole(achMsgContent,OutputMsgtoUser);
		logprintf(LOG_LVL_DETAIL,"Daemon: recv msg from server.\n");
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR �յ���Ϣnotify");
		cbShowMsgtoConsole("Daemon:ERROR �յ���Ϣnotify.",OutputMsgtoUser);
	}       
}

void CCDateInstance::DaemonProcSendFileCmd(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		cbShowMsgtoConsole("�������ӷ�����!",OutputMsgtoUser);
	}
	else
	{
		NextState(FILE_STATE);
		logprintf(LOG_LVL_DETAIL,"Daemon: recv send file cmd.\n ");
		//�ļ���Ϣ
		memcpy(&tClientInfo.achFilePath,pMsg->content,pMsg->length);
		//ʵ�ֱ���Instance ����----7.18����ʹ��pending
		//!!!ע�⣺�˴�ʹ��osppost�����˷���˵�id�ţ�������ͬһ�ͻ��˲���ͬʱ�ϴ��ļ�---8.11pending���Ĺ̶��������ϴ�һ���ļ�
		OspPost(MAKEIID(CLIENT_MSGAPP_NO,1),C_C_SENDFILE_CMD,tClientInfo.achFilePath,sizeof(tClientInfo.achFilePath),0,m_dwServerId,m_dwServerNode);
    }      
}
