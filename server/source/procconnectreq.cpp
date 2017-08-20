/*==========================================================
函数名：ProcConnectReq
功能：服务器收到连接消息操作
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::ProcConnectReq(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		CSDateInstanceClear();//初始化
		memset(m_achClientName,0,sizeof(m_achClientName)); //清空---
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
		
			//设置Instance别名
			SetAlias(m_achClientName,sizeof(m_achClientName));
			
			logprintf(LOG_LVL_KEYSTATUS,"Instance: server recv connect req.\n");
			cbShowNumToConsole(m_dwClientNode,"收到连接服务器请求. node = ",OutPutMsg);
			
			//反馈连接ACK消息
			post(pMsg->srcid,S_C_CONNECTSERVER_ACK,NULL,0,pMsg->srcnode);
			
			//设置断链检测
			OspSetHBParam(m_dwClientNode,SERVER_HBTIME,SERVER_HBNUM);
            OspNodeDiscCBRegQ(m_dwClientNode,SERVER_MSGAPP_NO,GetInsID());
		}

	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到连接服务器请求",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到连接服务器请求.\n");
	} 
	
}
void CSDateInstance::ProcDisConnect(CMessage *const pMsg) //断链操作---数据清除clear
{
	if (IDLE_STATE != CurState())
	{
		DeleteAlias();	//删除instance别名
		//cbShowMsgtoConsole(m_dwClientNode,OutputMsgtoUser);
		cbShowMsgtoConsole("断开连接",OutputMsgtoUser);			
		if (FILE_STATE == CurState())
		{
			post(m_dwServerId,OSP_DISCONNECT,NULL,0,0);//通知fileapp断开连接
		}		
		NextState(IDLE_STATE);
		CSDateInstanceClear();
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到断链通知",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到断链错通知.\n");		
    }
}

void CSDateInstance::ProcOverFlow(CMessage *const pMsg)
{
	if (CONNECT_STATE == CurState())
	{
		post(m_dwClientFileId,S_C_SENDFILEMSG_NACK,NULL,0,pMsg->srcnode);
		cbShowMsgtoConsole("写文件app没有空闲的instance",OutputMsgtoUser);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到overflow消息",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp:  收到overflow消息.\n");	
	}
}

