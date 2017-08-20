/*==========================================================
函数名：ProcReadFileCmd
功能：客户端文件app读取文件
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/

#include "../../include/client.h"
#include "../../../include/cscommon.h"
extern Buffer BufOne;

//读取文件信息操作
void CCFileInstance::ProcReadFileCmd(CMessage *const pMsg) 
{
	if (FILE_IDLE_STATE == CurState())
	{
		//状态切换
		NextState(FILE_READ_STATE);
		
		memcpy(m_achFileName,pMsg->content,pMsg->length);
		
		//cout << "file instance : recv read file cmd.\n start to send file::" << m_achFileName << endl;
		logprintf(LOG_LVL_KEYSTATUS,"File: recv cmd ,start to send file.\n");
		
		BufOne.dwBufferState = BUFFER_IDLE;
		memset(BufOne.achFileBuffer,0,CLIENT_FILE_BUFF_SIZE*sizeof(s8));
		

		//文件打开读取存到缓存区
		m_pFileRead = fopen(m_achFileName,"rb"); 
		if (m_pFileRead==NULL)
		{
			perror ("Error opening file");
			NextState(FILE_IDLE_STATE);
			fclose(m_pFileRead);
			m_pFileRead = NULL;
		}
		else
		{   //文件大小
			struct stat info;
			stat(m_achFileName,&info);
	        m_dwFilesize = info.st_size;
			//fseek (m_pFileRead, 0, SEEK_END);   ///将文件指针移动文件结尾
			//m_dwFilesize =ftell (m_pFileRead); ///求出当前文件指针距离文件开始的字节数
			//fseek(m_pFileRead,0,SEEK_SET);
		}		
		//根据filesize实现判断发送逻辑
		if (m_dwFilesize <= CLIENT_FILE_BUFF_SIZE )//小于buff值，则直接发送通知
		{
			fread(BufOne.achFileBuffer,sizeof(s8),m_dwFilesize,m_pFileRead);
			BufOne.dwBufferState = BUFFER_FULL;
			post(pMsg->srcid,C_C_BUFFULL_NOTIFY,NULL,0);
		} 
		else    //大于Buff值，根据状态来写入缓存区;最后文件大小也许并不能填满缓存区--最后一个单独运算
		{
			m_dwFileNum = m_dwFilesize / CLIENT_FILE_BUFF_SIZE + 1; 
			if (BufOne.dwBufferState == BUFFER_IDLE && m_dwFileNum != 1)
			{
				m_dwFilePlace = fread(BufOne.achFileBuffer,sizeof(s8),CLIENT_FILE_BUFF_SIZE,m_pFileRead);
				BufOne.dwBufferState = BUFFER_FULL;
				m_dwFileNum--;
				post(pMsg->srcid,C_C_BUFFULL_NOTIFY,NULL,0);
			}
			else
			{
				Sleep(100);
			}        
		}
		if (fclose(m_pFileRead))//关闭文件流
		{
			perror("fclose");
		}
	    m_pFileRead = NULL;
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"fileinst:ERROR 收到读文件cmd");
		cbShowMsgtoConsole("fileinst:ERROR 收到读文件cmd.",OutputMsgtoUser);
	}
	
}