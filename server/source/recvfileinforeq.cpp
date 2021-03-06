/*==========================================================
函数名：ProcFileMsgReq
功能：服务器写文件app收到文件信息操作
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../include/serverfile.h"
#include "../../include/cscommon.h"
#include "direct.h"
#define FILETEMPSIZE 10

using namespace std;
void CSFileInstance::ProcFileMsgReq(CMessage *const pMsg)
{
	if (FILE_IDLE_STATE == CurState())
	{
	    //状态切换
		CSFileInstanceClear();
	    NextState(FILE_WRITE_STATE);	

	    logprintf(LOG_LVL_KEYSTATUS,"File: recv file msg req.\n");  
	    cbShowMsgtoConsole("写文件app收到文件信息",OutputMsgtoUser);

	    s8 achFileMsg[CSMIDDLESIZE] = {0};
	
	    memcpy(achFileMsg,pMsg->content,pMsg->length);

	    //保存文件信息
	    s8 achFileTemp[FILETEMPSIZE] = {0};
	    memcpy(achFileTemp,achFileMsg,sizeof(achFileTemp));
	    m_dwFileSize = atoi(achFileTemp);
	    memcpy(m_achFileName,achFileMsg+sizeof(achFileTemp),sizeof(m_achFileName));
	
	    m_dwFileNum = m_dwFileSize/SERVER_FILE_BUFF_SIZE + 1;//文件传输次数
	    //上传到指定目录--可修改文件路径
	    s8 achFilePath[CSBIGSIZE] = {0};
	    sprintf(achFilePath,"%s","../uploadfile/"); //设置当前路径

/*	//判断文件路径是否存在，不存在则创建----已判断过
	if (!CreateDirectory(achFilePath,NULL))
	{
		DWORD dwError = GetLastError();

		if (ERROR_PATH_NOT_FOUND == dwError)
		{
			AfxMessageBox(_T("目录创建不成功。"));
			return;
		}
	}
*/
	    strcat(achFilePath,m_achFileName); //组合文件名
	    memset(m_achFileName,0,sizeof(m_achFileName)); //清空文件名
	    memcpy(m_achFileName,achFilePath,sizeof(achFilePath));

	    //文件指针打开文件
	    m_pFileWrite = fopen(m_achFileName,"wb");
	    if (m_pFileWrite == NULL)
		{
	    	perror ("Error opening file"); 
		    NextState(FILE_IDLE_STATE);
		    post(pMsg->srcid,S_S_FILEMSG_NACK,NULL,0); //反馈nack消息
		}
	    else
		{          
	    	post(pMsg->srcid,S_S_FILEMSG_ACK,NULL,0);	//反馈确认消息
		}
	    fclose(m_pFileWrite);
	    m_pFileWrite = NULL;
	}
	else
	{  
		cbShowMsgtoConsole("Warning: 收到写文件通知",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"fileapp: 收到写文件通知.\n");				
    }
	
}


//断链操作
void CSFileInstance::ProcDisConnect(CMessage *const pMsg)
{
	if (FILE_WRITE_STATE == CurState())
	{
		cbShowMsgtoConsole("file: 收到断链消息，删除未完成文件",OutputMsgtoUser);
		logprintf(LOG_LVL_KEYSTATUS,"File: recv disconnect.\n");
		
		NextState(FILE_IDLE_STATE);
		
		s8 achFile[CSLITTLESIZE] = {0};	
		sprintf(achFile,"%s",m_achFileName); //设置当前路径
		if (0 == remove(achFile))
		{
			cbShowMsgtoConsole("file: 删除文件成功",OutputMsgtoUser);
		}
		else
		{
			cbShowMsgtoConsole("file: 删除文件失败",OutputMsgtoUser);
		}
		CSFileInstanceClear();
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到断链消息",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到断链消息.\n");
	}
}
