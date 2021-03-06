/*==========================================================
函数名：ProcSendMsgNotify
功能：服务器收到消息通知操作
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

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
			post(pMsg->srcid,S_S_SENDMSGOK_NOTIFY,NULL,0,0);	//反馈消息发送成功
			post(m_dwClientId,S_C_SENDMSG_NOTIFY,achContent,strlen(achContent),m_dwClientNode);//转发消息到目的地
		}
		else
		{
			post(pMsg->srcid,S_S_SENDMSGFAIL_NOTIFY,NULL,0,0);
		}
	}
	else
	{
		post(pMsg->srcid,S_S_SENDMSGFAIL_NOTIFY,NULL,0,0);
		cbShowMsgtoConsole("Warning: 收到发送消息notify通知",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到发送消息notify通知.\n");
    }
	
}