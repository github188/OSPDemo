/*==========================================================
函数名：ProcReadFileNextNotify
功能：客户端文件app读取文件缓存区
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
using namespace std;
//读取文件信息操作
void CCFileInstance::ProcReadFileNextNotify(CMessage *const pMsg) 
{
	if (FILE_READ_STATE == CurState())
	{
		m_pFileRead = fopen(m_achFileName,"rb"); //打开文件
		if (m_pFileRead == NULL)
		{
			perror ("Error opening file");
		}
		fseek(m_pFileRead,m_dwFilePlace,SEEK_SET);//移动文件流指针
		
		memset(BufOne.achFileBuffer,0,CLIENT_FILE_BUFF_SIZE*sizeof(s8));	//清空缓存
		if (BufOne.dwBufferState == BUFFER_IDLE && m_dwFileNum != 1)
		{	
			s32 dwRetVal = fread(BufOne.achFileBuffer,sizeof(s8),CLIENT_FILE_BUFF_SIZE,m_pFileRead);
			//cout << "file app instance: start to read file.RetVal = " << dwRetVal << endl;
			m_dwFilePlace = m_dwFilePlace + dwRetVal;
			BufOne.dwBufferState = BUFFER_FULL;
			m_dwFileNum--;
			post(pMsg->srcid,C_C_BUFFULL_NOTIFY,NULL,0);
		}
		else //if (BufOne.dwBufferState == BUFFER_IDLE && m_dwFileNum == 1) //最后一次拷贝数据-相差
		{	
			u32 dwRetVal = fread(BufOne.achFileBuffer,sizeof(s8),m_dwFilesize - m_dwFilesize / CLIENT_FILE_BUFF_SIZE * CLIENT_FILE_BUFF_SIZE,m_pFileRead);
			//cout << "file app instance: start to read file.RetVal = " << dwRetVal << endl;
			
			BufOne.dwBufferState = BUFFER_FULL;
			post(pMsg->srcid,C_C_BUFFULL_NOTIFY,NULL,0);
		}
	
		if (fclose(m_pFileRead))//关闭文件流
		{
			perror("fclose");
		}
	    m_pFileRead = NULL;
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"fileinst:ERROR 收到读缓存notify");
		cbShowMsgtoConsole("fileinst:ERROR 收到读缓存notify.",OutputMsgtoUser);
	}		
}

void CCFileInstance::ProcWriteDoneNoti(CMessage *const pMsg) //写完成通知 
{
	if (FILE_READ_STATE == CurState())
	{
		NextState(FILE_IDLE_STATE);
		logprintf(LOG_LVL_KEYSTATUS,"File:recv write done.\n");
		CCFileInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"fileinst:ERROR 收到写完成notify");
		cbShowMsgtoConsole("fileinst:ERROR 收到写完成notify.",OutputMsgtoUser);		
	}
}


void CCFileInstance::ProcDisConnectNoti(CMessage *const pMsg) //断链通知
{
	if (FILE_READ_STATE == CurState())
	{
		NextState(FILE_IDLE_STATE);
		if (m_pFileRead != NULL)	//判断指针是否关闭
		{
			if (fclose(m_pFileRead))
			{
				perror("fclose");
			}
			m_pFileRead = NULL;
		}
		//清除数据clear
		CCFileInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"fileinst:ERROR 收到断链消息notify");
		cbShowMsgtoConsole("fileinst:ERROR 收到断链消息notify.",OutputMsgtoUser);		
	}
}