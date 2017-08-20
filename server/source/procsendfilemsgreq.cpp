/*==========================================================
函数名：ProcSendFileMsgReq
功能：服务器收到发送文件信息请求
算法实现：
参数说明：pMsg : OSP传递的消息体
返回值说明：无
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"
#include "direct.h"
#include "io.h"

#define FILETEMPSIZE     10

extern CServerApp g_CServerApp;

void CSDateInstance::ProcSendFileMsgReq(CMessage *const pMsg)
{
	if (CONNECT_STATE == CurState())
	{
		//信息保存
	m_dwClientFileId = pMsg->srcid;
    s8 achFileMsg[CSMIDDLESIZE] = {0};
    memcpy(achFileMsg,pMsg->content,pMsg->length);

	logprintf(LOG_LVL_KEYSTATUS,"Instance: recv file info.\n");

    //这里先将文件信息发给写文件app
    //遍历找到写文件app的空闲InstanceId号 ---使用pending需要增加一条反馈信息-----应该确定，不能pending    
	/** 2017.07.18修改：使用pending，增加消息
	u16 wInsnum  = 1;
	m_dwServerId = MAKEIID(SERVER_FILEAPP_NO,wInsnum);	**/
	
	//获取路径的文件名……！！！ 
	s8 achFileTemp[FILETEMPSIZE] = {0};
	memcpy(achFileTemp,achFileMsg,sizeof(achFileTemp));
	m_dwFileSize = atoi(achFileTemp);		//强制转换保存文件大小

    if (m_dwFileSize <= g_CServerApp.GetFileLeftStore())	//判断文件大小，确认是否上传
	{
		g_CServerApp.SetFileLeftStore(g_CServerApp.GetFileLeftStore() - m_dwFileSize);

	    memcpy(m_achFileName,achFileMsg+sizeof(achFileTemp),sizeof(m_achFileName));
	    m_dwFileNum = m_dwFileSize / SERVER_FILE_BUFF_SIZE + 1; //文件需要传输的次数---对文件传输进行判定
			
	    s8 achFilePath[CSBIGSIZE] = {0};
//	sprintf(achFilePath,"%s",m_achFileName);	//固定保存路径  ！！增加文件夹路径判断
     
	    sprintf(achFilePath,"%s","../uploadfile/"); //设置当前路径
	
	    //判断文件路径是否存在，不存在则创建
	    if (!CreateDirectory(achFilePath,NULL))
		{
	    	DWORD dwError = GetLastError();
		
		    if (ERROR_PATH_NOT_FOUND == dwError)
			{
			    AfxMessageBox(_T("目录创建不成功。"));
			    post(pMsg->srcid,S_C_SENDFILEMSG_NACK,NULL,0,pMsg->srcnode);//返回nack消息（消息与大小不一相同，未添加特定的消息）
			    return;
			}
		}
		sprintf(achFilePath,"%s",m_achFileName);	//固定保存路径  ！！增加文件夹路径判断
	    //判断是否存在同名文件，更改文件名2017.07.20
	    if (0 == access(achFilePath,0))
		{
		    s8 achFiletemp[CSMIDDLESIZE] = {0};//文件名拷贝
		    u16 wFilenum = 0;  //增加后缀
		    s8 achFilenum[FIRSTNUM] = {0};//后缀字符串
		    s8 achFilename[CSBIGSIZE] = {0}; //文件名
		    s8 achFileInfo[CSLITTLESIZE] = {0}; //文件格式
				
		    //strtok  不安全
		    strcpy(achFiletemp,m_achFileName); //文件名拷贝
		    strcpy(achFilename,strtok(achFiletemp,"."));//将文件名前部分取出
		    strcpy(achFileInfo,strtok(NULL,"\0"));	//保存文件名后部分

		    while (0 == access(achFilePath,0))  //更改文件名
			{
			    cbShowMsgtoConsole("instance : This File Name is Exited. Now Change.",OutputMsgtoUser);
			    wFilenum++;
			    memset(m_achFileName,0,sizeof(m_achFileName));
			    memcpy(m_achFileName,achFilename,strlen(achFilename));
			
			    strcat(m_achFileName,itoa(wFilenum,achFilenum,10));
			    strcat(m_achFileName,".");
			    strcat(m_achFileName,achFileInfo);
			    sprintf(achFilePath,"%s",m_achFileName);
			}
		}
						
	    memset(achFileMsg,0,sizeof(achFileMsg));
	    //组合文件大小和文件名  0807---标准化消息格式
        sprintf(achFileMsg,"%10d%s",m_dwFileSize,m_achFileName);
    	cbShowMsgtoConsole(achFileMsg,OutputMsgtoUser);

    	post(MAKEIID(SERVER_FILEAPP_NO,PENDING),S_S_FILEMSG_REQ,achFileMsg,strlen(achFileMsg),0);		
    }
	else
	{
		logprintf(LOG_LVL_ERROR,"Instance: file store size left little.\n");
		cbShowMsgtoConsole("File Store Size is too small,please Contact We to UPDATE",OutputMsgtoUser);
        post(pMsg->srcid,S_C_SENDFILEMSG_NACK,NULL,0,pMsg->srcnode);
    }
	}
    else
	{
	    cbShowMsgtoConsole("Warning: 收到发送文件信息req",OutputMsgtoUser);
	    logprintf(LOG_LVL_WARNING,"msgapp: 收到发送文件信息req.\n");
	} 
}

void CSDateInstance::ProcSendFileMsgAck(CMessage *const pMsg) //收到fileapp的确认反馈
{
	if (CONNECT_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: msg instance recv file ack.\n");
		cbShowMsgtoConsole("收到fileapp的确认消息",OutputMsgtoUser);
		m_dwServerId = pMsg->srcid;
		NextState(FILE_STATE);			//状态切换
		post(m_dwClientFileId,S_C_SENDFILEMSG_ACK,NULL,0,m_dwClientNode);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到文件信息确认ack",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到文件信息确认ack.\n");	
	}
}

void CSDateInstance::ProcSendFileMsgNack(CMessage *const pMsg)
{
	if (CONNECT_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: msg instance recv file nack.\n");
		cbShowMsgtoConsole("收到fileapp的文件打开错误消息",OutputMsgtoUser);
		post(m_dwClientFileId,S_C_SENDFILEMSG_NACK,NULL,0,m_dwClientNode);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到文件信息nack",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到文件信息nack.\n");	
	}
}

void CSDateInstance::ProcSendFileReq(CMessage *const pMsg)	//收到文件req，转发给fileapp
{
	if (FILE_STATE == CurState())
	{
		s8 achFileContent[SERVER_FILE_BUFF_SIZE] = {0};
        memcpy(achFileContent,pMsg->content,pMsg->length);
			
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv send file req.\n");
		//cbShowMsgtoConsole("服务器收到文件请求",OutputMsgtoUser);
		post(m_dwServerId,S_S_WRITEFILE_CMD,achFileContent,pMsg->length,0);
	}
	else
	{	
		cbShowMsgtoConsole("Warning: 收到文件内容req",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到文件内容req.\n");
       /*   m_dwNumCount ++;
            if (m_dwNumCount == m_dwFileNum )  //判断文件发送存入缓存区---文件最后一包
			{
				memcpy(bufone.achFileBuffer + (m_dwNumCount-1) * SERVER_FILE_BUFF_SIZE * sizeof(s8),pMsg->content,pMsg->length);
				//发送cmd到写文件app
				for (u32 dwTemp = 0;dwTemp < (m_dwNumCount - 1);dwTemp++)
				{
					memcpy(achFileContent,bufone.achFileBuffer + dwTemp * SERVER_FILE_BUFF_SIZE * sizeof(s8),SERVER_FILE_BUFF_SIZE*sizeof(s8));
					post(m_dwServerId,S_S_WRITEFILE_CMD,achFileContent,pMsg->length,0);
				}
				//文件最后一包
				memcpy(achFileContent,bufone.achFileBuffer + (m_dwNumCount - 1) * SERVER_FILE_BUFF_SIZE* sizeof(s8),(m_dwFileSize-m_dwFileSize / SERVER_FILE_BUFF_SIZE * SERVER_FILE_BUFF_SIZE) * sizeof(s8));
				post(m_dwServerId,S_S_WRITEFILE_CMD,achFileContent,(m_dwFileSize-m_dwFileSize / SERVER_FILE_BUFF_SIZE * SERVER_FILE_BUFF_SIZE) * sizeof(s8),0);

			}
			else if (m_dwNumCount < 256)  //同一个缓存区
			{
				memcpy(bufone.achFileBuffer + (m_dwNumCount-1) * SERVER_FILE_BUFF_SIZE * sizeof(s8),pMsg->content,pMsg->length);
				post(m_dwClientFileId,S_C_SENDFILECONTENT_ACK,NULL,0,m_dwClientNode);
			}
			else if (m_dwNumCount == 256) //同一缓存区最后一包
			{
				memcpy(bufone.achFileBuffer + (m_dwNumCount-1) * SERVER_FILE_BUFF_SIZE * sizeof(s8),pMsg->content,pMsg->length);
				//发送cmd到写文件app
				for (u32 dwTemp = 0;dwTemp < m_dwNumCount ;dwTemp++)
				{
					memcpy(achFileContent,bufone.achFileBuffer + dwTemp * SERVER_FILE_BUFF_SIZE * sizeof(s8),SERVER_FILE_BUFF_SIZE*sizeof(s8));
					post(m_dwServerId,S_S_WRITEFILE_CMD,achFileContent,pMsg->length,0);
				}
				m_dwNumCount = 0;
				m_dwFileNum = m_dwFileNum - 256;
				post(m_dwClientFileId,S_C_SENDFILECONTENT_ACK,NULL,0,m_dwClientNode);
			}  */	
    }   

}


void CSDateInstance::ProcWriteFileNoti(CMessage *const pMsg)
{
	if (FILE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: server recv write file notify.\n");
		post(m_dwClientFileId,S_C_SENDFILECONTENT_ACK,NULL,0,m_dwClientNode);
		//cbShowMsgtoConsole("服务器ack反馈给客户端",OutputMsgtoUser);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到文件发送noyify",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到文件发送noyify.\n");
	}		
}

void CSDateInstance::ProcWriteDoneNoti(CMessage *const pMsg)//写完成
{
	if (FILE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: server recv write done notify.\n");
		cbShowMsgtoConsole("服务器收到写完成通知",OutputMsgtoUser);
		NextState(CONNECT_STATE);
		post(m_dwClientFileId,S_C_SENDFILEDONE_NOTIFY,NULL,0,m_dwClientNode);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到写完成通知",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到写完成通知.\n");
	}
}

void CSDateInstance::ProcWriteWrongNoti(CMessage *const pMsg)//写出错
{
	if (FILE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: srever recv file write wrong notify.\n");
		cbShowMsgtoConsole("服务器收到写文件出错通知",OutputMsgtoUser);
		post(m_dwClientFileId,S_C_SENDFILEDONE_NOTIFY,NULL,0,m_dwClientNode);
		NextState(CONNECT_STATE);
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到写文件出错通知",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到写文件出错通知.\n");
	}
	
}
