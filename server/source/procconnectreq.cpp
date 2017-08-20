/*==========================================================
��������ProcConnectReq
���ܣ��������յ�������Ϣ����
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::ProcConnectReq(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		CSDateInstanceClear();//��ʼ��
		memset(m_achClientName,0,sizeof(m_achClientName)); //���---
		memcpy(m_achClientName,pMsg ->content,pMsg->length);
		if (strlen(m_achClientName) == 0)
		{
			post(pMsg->srcid,S_C_CONNECTSERVER_NACK,NULL,0,pMsg->srcnode);
		}
		
		else
		{			
			NextState(CONNECT_STATE); 
			m_dwInsState = CONNECT_STATE;
			m_dwClientNode = pMsg->srcnode;
			m_dwClientId = pMsg->srcid;
		
			//����Instance����
			SetAlias(m_achClientName,sizeof(m_achClientName));
			
			logprintf(LOG_LVL_KEYSTATUS,"Instance: server recv connect req.\n");
			cbShowNumToConsole(m_dwClientNode,"�յ����ӷ���������. node = ",OutPutMsg);
			
			//��������ACK��Ϣ
			post(pMsg->srcid,S_C_CONNECTSERVER_ACK,NULL,0,pMsg->srcnode);
			
			//���ö������
			OspSetHBParam(m_dwClientNode,SERVER_HBTIME,SERVER_HBNUM);
            OspNodeDiscCBRegQ(m_dwClientNode,SERVER_MSGAPP_NO,GetInsID());
		}

	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ����ӷ���������",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ����ӷ���������.\n");
	} 
	
}
void CSDateInstance::ProcDisConnect(CMessage *const pMsg) //��������---�������clear
{
	if (IDLE_STATE != CurState())
	{
		DeleteAlias();	//ɾ��instance����
		//cbShowMsgtoConsole(m_dwClientNode,OutputMsgtoUser);
		cbShowMsgtoConsole("�Ͽ�����",OutputMsgtoUser);			
		if (FILE_STATE == CurState())
		{
			post(m_dwServerId,OSP_DISCONNECT,NULL,0,0);//֪ͨfileapp�Ͽ�����
		}		
		NextState(IDLE_STATE);
		CSDateInstanceClear();
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ�����֪ͨ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ�������֪ͨ.\n");		
    }
}

void CSDateInstance::ProcOverFlow(CMessage *const pMsg)
{
	if (CONNECT_STATE == CurState())
	{
		post(m_dwClientFileId,S_C_SENDFILEMSG_NACK,NULL,0,pMsg->srcnode);
		cbShowMsgtoConsole("д�ļ�appû�п��е�instance",OutputMsgtoUser);
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ�overflow��Ϣ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp:  �յ�overflow��Ϣ.\n");	
	}
}
