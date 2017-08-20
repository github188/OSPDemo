/*==========================================================
函数名：ProcBuffNotify
功能：缓存区满操作--开始发送文件
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

void CCDateInstance::ProcBuffNotify(CMessage *const pMsg) 
{
	if (FILE_STATE == CurState())
	{
		//logprintf(LOG_LVL_KEYSTATUS,"Instance: recv client file buf full notify.\n");
		m_dwClientId = pMsg->srcid;//保存fileApp的id
		
		BufOne.dwBufferState = BUFFER_BUSY;
		s8 achFileContent[CLIENT_SEND_FILE_SIZE] = {0};//初始化缓存
		
		if (m_dwFileNum == 1 ) //发送最后一包
		{ 
			memcpy(achFileContent,BufOne.achFileBuffer,(m_dwFileSize - (g_dwFileNumShang * CLIENT_SEND_FILE_SIZE ))*sizeof(s8));               
			m_dwFileNum -- ;
			BufOne.dwBufferState = BUFFER_IDLE;
			post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,(m_dwFileSize - g_dwFileNumShang * CLIENT_SEND_FILE_SIZE),m_dwServerNode);		
		} 
		else
		{
			//instance: 收到缓存区满的消息，发送文件到服务器. Tick Get ****" << OspTickGet() << endl;
			memcpy(achFileContent,BufOne.achFileBuffer,CLIENT_SEND_FILE_SIZE);
			m_dwFileNum--;
			post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
		}
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR 收到缓存通知");
		cbShowMsgtoConsole("instance:ERROR 收到缓存通知消息",OutputMsgtoUser);
	}	
	
}
