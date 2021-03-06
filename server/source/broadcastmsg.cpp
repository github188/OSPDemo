/*==========================================================
函数名：DaemonProcBroadcastReq
功能：服务器广播消息
算法实现：
参数说明：pMsg : OSP传递的消息体  pcApp ： Osp Appdate
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::DaemonProcBroadcastReq(CMessage *const pMsg, CApp* pcApp)
{
	s8 achMsgConetent[CSMIDDLESIZE] = {0};
	memcpy(achMsgConetent,pMsg->content,pMsg->length);

	cbShowNumToConsole(pMsg->srcnode,"收到广播消息指令.来自--",OutPutMsg);
	logprintf(LOG_LVL_KEYSTATUS,"DaemonProcBroadcastReq: recv 0 from client.\n");
	
	u16 wInsNum = FIRSTNUM;        //instance 编号
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