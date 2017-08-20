/*==========================================================
��������DaemonProcBroadcastReq
���ܣ��������㲥��Ϣ
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��  pcApp �� Osp Appdate
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::DaemonProcBroadcastReq(CMessage *const pMsg, CApp* pcApp)
{
	s8 achMsgConetent[CSMIDDLESIZE] = {0};
	memcpy(achMsgConetent,pMsg->content,pMsg->length);

	cbShowNumToConsole(pMsg->srcnode,"�յ��㲥��Ϣָ��.����--",OutPutMsg);
	logprintf(LOG_LVL_KEYSTATUS,"DaemonProcBroadcastReq: recv 0 from client.\n");
	
	u16 wInsNum = FIRSTNUM;        //instance ���
	while(wInsNum <= SERVER_MAX_INSTANCE)
	{
		CInstance* pTemp = pcApp->GetInstance(wInsNum);
		if (IDLE_STATE != pTemp->m_curState )
		{		
			post(MAKEIID(SERVER_MSGAPP_NO,wInsNum),S_S_SENDMSG_NOTIFY,achMsgConetent,strlen(achMsgConetent),0);
		}
		wInsNum++;
	}
	logprintf(LOG_LVL_KEYSTATUS,"DaemonProcBroadcastReq:post msg to everyone.\n");
}