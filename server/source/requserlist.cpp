/*==========================================================
函数名：DaemonProcUserlistReq
功能：服务器查询用户列表操作
算法实现：
参数说明：pMsg : OSP传递的消息体  pcApp ： Osp Appdate
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"

void CSDateInstance::DaemonProcUserlistReq(CMessage *const pMsg, CApp* pcApp)
{
	u16 wInsNum = FIRSTNUM;                   //instance编号
	s8  chValue = ZERONUM;                   //存在上线用户标志位
	s8  achUserName[CSMIDDLESIZE] = {0};        //消息内容
	
	u8  wAliasLength = ZERONUM;              //实例别名长度
	s8  achbuff[CSLITTLESIZE];                   //存储实例号
	
	logprintf(LOG_LVL_KEYSTATUS,"Daemon: recv user list req.\n");
	while(wInsNum <= SERVER_MAX_INSTANCE)
	{
		s8 achName[CSBIGSIZE] = {0};          //存储实例别名  
		CInstance* pTemp = pcApp->GetInstance(wInsNum);

		if (IDLE_STATE != pTemp->m_curState )//需要加判断去掉自己的
		{ 
			chValue++;
			//获取实例别名
			pTemp->GetAlias(achName,CSBIGSIZE,&wAliasLength);

			//组合消息,所有在线用户
			sprintf(achbuff,"%d",wInsNum);
			strcat(achUserName,achbuff);
			strcat(achUserName,".");
			strcat(achUserName,pTemp->m_alias);
			strcat(achUserName,"\n\t");
			cbShowMsgtoConsole(achUserName,OutputMsgtoUser);
		}
		wInsNum++;		
	}
	if (!chValue)	//需要去掉自己（-1）  此判断才有效
	{
		logprintf(LOG_LVL_KEYSTATUS,"Daemon: post user list nack to client.\n");
		cbShowMsgtoConsole("post ReaUserList Nack to Client",OutputMsgtoUser);
		post(pMsg->srcid,S_C_REQUSERLIST_NACK,NULL,0,pMsg->srcnode);
	}
	else	//返回所有的用户
	{
		logprintf(LOG_LVL_KEYSTATUS,"Daemon: post user list ack to client.\n");
        cbShowNumToConsole(pMsg->srcnode,"post ReaUserList ack to Client" ,OutPutMsg);
		post(pMsg->srcid,S_C_REQUSERLIST_ACK,achUserName,strlen(achUserName),pMsg->srcnode);
	}	
}