/*==========================================================
��������ProcSendMsgReq
���ܣ�������������Ϣ����
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::ProcSendMsgReq(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		//������Ϣ����ȡĿ��Instance��
		s8 achContent[CSMIDDLESIZE] = {0};   
		s8 achMsgContent[CSMIDDLESIZE] = {0};    //������Ϣ
		
		memcpy(achContent,pMsg->content,pMsg->length);
		cbShowNumToConsole(m_dwClientNode,"�յ�������Ϣָ�����node=",OutPutMsg);
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv !0 from client.\n");
		
		u16 wInsNum = atoi(strtok(achContent,","));//�õ�Ŀ��Instance��
		strcpy(achMsgContent,m_achClientName);
		strcat(achMsgContent," said to you :");
		strcat(achMsgContent,strtok(NULL,"\0"));
		
		//���ö�ʱ���ж��Ƿ���ڶԶ�
		//SetTimer(S_S_SENDMSGFAIL_NOTIFY,WAITED_TIME);---8.11�޸��ж���instance���ֵ�ıȽ� ��ȷ��
		//����Ŀ��Instance
		if (wInsNum > SERVER_MAX_INSTANCE)
		{
			post(m_dwClientId,S_C_SENDMSG_NACK,NULL,0,m_dwClientNode);
		}
		else
		{
			post(MAKEIID(SERVER_MSGAPP_NO,wInsNum),S_S_SENDMSG_NOTIFY,achMsgContent,strlen(achMsgContent),0);	
		}
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ�������Ϣ����",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ�������Ϣ����.\n");
    }      
	
}

void CSDateInstance::ProcSendMsgOkNoti(CMessage *const pMsg)	//������Ϣ�ɹ�
{
	if (IDLE_STATE != CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv server msg ok notify.\n");
		post(m_dwClientId,S_C_SENDMSG_ACK,NULL,0,m_dwClientNode);
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ�������Ϣok֪ͨ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ�������Ϣok֪ͨ.\n");
	}	
}

void CSDateInstance::ProcSendMsgFailNoti(CMessage *const pMsg)	//������Ϣʧ��
{
	if (IDLE_STATE != CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv server msg fail notify.\n");
		post(m_dwClientId,S_C_SENDMSG_NACK,NULL,0,m_dwClientNode);
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ�������Ϣfail֪ͨ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ�������Ϣfail֪ͨ.\n");
	}
}