/*==========================================================
函数名：ProcSendFileContentReq
功能：客户端发送文件内容到服务器
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/

#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "io.h"

extern u32 g_dwFileNumTemp;	    //存储文件发送次数--判定条件和偏移量
extern u32 g_dwFileNumShang;	//文件大小和每包大小之差--用来判定偏移量
extern Buffer BufOne;
//发送文件内容操作
void CCDateInstance::ProcSendFileContentReq(CMessage *const pMsg) 
{
	if (FILE_STATE == CurState())
	{
		if (m_dwFileNum == 0)	//判断为最后一包发送成功
		{
			cbShowMsgtoConsole("文件发送完毕。",OutputMsgtoUser);
			BufOne.dwBufferState = BUFFER_IDLE;
		}
		else if(m_dwFileNum != 0 && BufOne.dwBufferState == BUFFER_IDLE)	//继续读取下一个缓存区
		{
			post(m_dwClientId,C_C_READFILENEXT_NOTIFY,NULL,0);//继续读取
		}
		else if(BufOne.dwBufferState == BUFFER_BUSY)	//发送缓存区内容
		{
			s8 achFileContent[CLIENT_SEND_FILE_SIZE] = {0};
			
			if (1 == m_dwFileNum) //发送最后一包
			{   
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),(m_dwFileSize - (g_dwFileNumShang * CLIENT_SEND_FILE_SIZE ))*sizeof(s8));
				m_dwFileNum -- ;
				BufOne.dwBufferState = BUFFER_IDLE;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,(m_dwFileSize - g_dwFileNumShang * CLIENT_SEND_FILE_SIZE),m_dwServerNode);
				//cout << "instance :发送最后一包. Tick Get ****" << OspTickGet() << endl;
			} 
			else if ((g_dwFileNumTemp - m_dwFileNum)%CLIENT_SEND_NUM == (CLIENT_SEND_NUM-1)) //发完一个缓存区
			{
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),CLIENT_SEND_FILE_SIZE*sizeof(s8));
				m_dwFileNum -- ;
				BufOne.dwBufferState = BUFFER_IDLE;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
				//cout << "instance : 发完一个缓存区 . Tick Get ****" << OspTickGet()<< endl;
			}
			else
			{                                                                        //偏移量设置
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),CLIENT_SEND_FILE_SIZE*sizeof(s8));
				m_dwFileNum -- ;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
				//	cout << "instance :发送下一包（post之后） . Tick Get ****" << OspTickGet() << endl; 
			}
			
			//客户端进度显示、内容显示    进度在telnet窗口显示不过设置输出等级应该大于一
		
			logprintf(LOG_LVL_WARNING,"发送文件进度: %d%%\r",(CSMIDDLESIZE*(g_dwFileNumTemp - m_dwFileNum)/g_dwFileNumTemp));
		}
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR 收到发送文件ack");
		cbShowMsgtoConsole("instance:ERROR 收到发送文件ack",OutputMsgtoUser);
	}  	
}

void CCDateInstance::ProcSendFileNack(CMessage *const pMsg)
{
	if (FILE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Msg: recv server send file nack.\n");
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR 收到发送文件nack");
		cbShowMsgtoConsole("instance:ERROR 收到发送文件nack",OutputMsgtoUser);
	}	
}

void CCDateInstance::ProcSendFileDoneNoti(CMessage *const pMsg) //发送完成通知
{
	if (FILE_STATE == CurState())
	{
		post(m_dwClientId,C_C_WRITEDONE_NOTIFY,NULL,0);
		logprintf(LOG_LVL_KEYSTATUS,"Msg: recv server write done notify.\n");
		cbShowMsgtoConsole("收到写完成通知",OutputMsgtoUser);
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR 收到发送文件完成通知");
		cbShowMsgtoConsole("instance:ERROR 收到发送文件完成通知",OutputMsgtoUser);		
	}
}


void CCDateInstance::ProcOverFlow(CMessage *const pMsg) //无空闲实例
{
	if (CONNECT_STATE == CurState())
	{
		cbShowMsgtoConsole("写文件app正忙",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"Msg: client file instance is busy.\n");
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR 收到发送文件完成通知");
		cbShowMsgtoConsole("instance:ERROR 收到发送文件完成通知",OutputMsgtoUser);	
	}     
}


void CCDateInstance::ProcDisConnect(CMessage *const pMsg)  //断开连接---清除数据
{
	if (IDLE_STATE != CurState())
	{
		cbShowMsgtoConsole("osp连接断开",OutputMsgtoUser);
		logprintf(LOG_LVL_ERROR,"Msg: osp disconnect.\n");
		if (CurState() == FILE_STATE) //给fileapp发断链消息，改变状态
		{
			post(m_dwClientId,C_C_DISCONNECT_NOTIFY,NULL,0);
		}
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:收到OSP断链消息");
		cbShowMsgtoConsole("instance: 收到OSP断链消息",OutputMsgtoUser);
	}
}
