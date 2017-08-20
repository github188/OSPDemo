/*==========================================================
函数名：DaemonProcMsgSendCmd
功能：客户端daemon发送消息命令
算法实现：用到了strtok 
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../../include/client.h"
#include "../../../include/cscommon.h"

extern UCinfo tClientInfo;		//保存客户端信息

void CCDateInstance::DaemonProcMsgSendCmd(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		cbShowMsgtoConsole("请先连接服务器!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_KEYSTATUS,"Daemon: recv send msg cmd.\n");
	    //发送消息
		s8 achContent[CSMIDDLESIZE] = {0};		   //保存消息内容
		s8 achMsgContent[CSMIDDLESIZE] = {0};	   //组合广播消息
		s8 achMsgSingleContent[CSMIDDLESIZE] = {0}; //组合单发消息---直接发送消息内容
		
		memcpy(achContent,pMsg->content,pMsg->length);
		memcpy(achMsgSingleContent,pMsg->content,pMsg->length);
		
		u16 w_InsNum = atoi(strtok(achContent,","));//强制转换判断发送对象
		
		//组合消息，让广播消息有消息来源显示
		strcpy(achMsgContent,m_achusername);
		strcat(achMsgContent," said to you:");
		strcat(achMsgContent,strtok(NULL,"\0"));
		
		if (0 == w_InsNum) //广播消息发到服务器Daemon
		{
			post(MAKEIID(SERVER_MSGAPP_NO,CInstance::DAEMON),C_S_SENDMSG_REQ,achMsgContent,sizeof(achMsgContent),m_dwServerNode);
		} 
		else        //单发消息发到对应Instance
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
		cbShowMsgtoConsole("消息发送成功!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR 收到发送消息ack");
		cbShowMsgtoConsole("Daemon:ERROR 收到发送消息ack.",OutputMsgtoUser);
	}		
}


void CCDateInstance::DaemonProcSendMsgNack(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		logprintf(LOG_LVL_DETAIL,"Daemon: post msg to man fail.\n ");
		cbShowMsgtoConsole("消息发送失败!",OutputMsgtoUser);
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR 收到发送消息nack");
		cbShowMsgtoConsole("Daemon:ERROR 收到发送消息nack.",OutputMsgtoUser);
	}		
}


void CCDateInstance::DaemonProcSendMsgNoti(CMessage *const pMsg)
{
	if (IDLE_STATE != CurState())
	{
		s8 achMsgContent[CSMIDDLESIZE] = {0};
		cbShowMsgtoConsole("收到消息：",OutputMsgtoUser);         
		memcpy(achMsgContent,pMsg->content,pMsg->length);
		cbShowMsgtoConsole(achMsgContent,OutputMsgtoUser);
		logprintf(LOG_LVL_DETAIL,"Daemon: recv msg from server.\n");
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR 收到消息notify");
		cbShowMsgtoConsole("Daemon:ERROR 收到消息notify.",OutputMsgtoUser);
	}       
}

void CCDateInstance::DaemonProcSendFileCmd(CMessage *const pMsg)
{
	if (IDLE_STATE == CurState())
	{
		cbShowMsgtoConsole("请先连接服务器!",OutputMsgtoUser);
	}
	else
	{
		NextState(FILE_STATE);
		logprintf(LOG_LVL_DETAIL,"Daemon: recv send file cmd.\n ");
		//文件信息
		memcpy(&tClientInfo.achFilePath,pMsg->content,pMsg->length);
		//实现遍历Instance 方法----7.18更改使用pending
		//!!!注意：此处使用osppost带上了服务端的id号，将导致同一客户端不能同时上传文件---8.11pending更改固定，仅可上传一个文件
		OspPost(MAKEIID(CLIENT_MSGAPP_NO,1),C_C_SENDFILE_CMD,tClientInfo.achFilePath,sizeof(tClientInfo.achFilePath),0,m_dwServerId,m_dwServerNode);
    }      
}
