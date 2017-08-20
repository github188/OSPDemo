/*==========================================================
��������ProcSendMsgNotify
���ܣ��������յ���Ϣ֪ͨ����
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::ProcSendMsgNotify(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		s8 achContent[CSMIDDLESIZE] = {0};
		memcpy(achContent,pMsg->content,pMsg->length);
		
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv transfer msg.\n");
		if (IDLE_STATE != CurState()) 
		{
			post(pMsg->srcid,S_S_SENDMSGOK_NOTIFY,NULL,0,0);	//������Ϣ���ͳɹ�
			post(m_dwClientId,S_C_SENDMSG_NOTIFY,achContent,strlen(achContent),m_dwClientNode);//ת����Ϣ��Ŀ�ĵ�
		}
		else
		{
			post(pMsg->srcid,S_S_SENDMSGFAIL_NOTIFY,NULL,0,0);
		}
	}
	else
	{
		post(pMsg->srcid,S_S_SENDMSGFAIL_NOTIFY,NULL,0,0);
		cbShowMsgtoConsole("Warning: �յ�������Ϣnotify֪ͨ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ�������Ϣnotify֪ͨ.\n");
    }
	
}