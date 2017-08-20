/*==========================================================
函数名：ProcFileContentCmd
功能：服务器写文件app收到文件内容操作
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
//using namespace std; //增加cout输出为了方便查看进度
void CSFileInstance::ProcFileContentCmd(CMessage *const pMsg)
{
	if (FILE_WRITE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"File: recv write file cmd.\n");
	    //cbShowMsgtoConsole("写文件app收到写命令",OutputMsgtoUser);
	
	//上传到指定目录--可修改文件路径
//	s8 achFilePath[256] = {0};
//	sprintf(achFilePath,"%s",m_achFileName); //设置当前路径
	//文件指针打开文件
	m_pFileWrite = fopen(m_achFileName,"ab");
	/*if (m_pFileWrite == NULL)
	{
		perror ("Error opening file"); 
		NextState(FILE_IDLE_STATE);
		post(pMsg->srcid,S_S_FILEMSG_NACK,NULL,0); //反馈nack消息
	}*/

	//此处应该实现判断写完成的条件--
	//fseek(m_pFileWrite,0,SEEK_END);----这个方法不对，将导致文件大小变小。。待查
	u32 dwRetVal = fwrite(pMsg->content,sizeof(u8),pMsg->length,m_pFileWrite);
	//m_dwFilePlace = m_dwFilePlace + dwRetVal;
	m_dwFileNum--;
//	cout << "写完成--进度" << m_dwFileNum << " 写入文件大小 :" << dwRetVal << " . Tick Get****" << OspTickGet() << endl;//进度显示
	post(pMsg->srcid,S_S_WRITEFILE_NOTIFY,NULL,0,0);	//返回发送下一包确认。
	
	if (0 == m_dwFileNum)
	{
		logprintf(LOG_LVL_KEYSTATUS,"File: write file done.\n");
		cbShowMsgtoConsole("写文件app确认写完成",OutputMsgtoUser);
		fseek (m_pFileWrite, 0, SEEK_END);   ///将文件指针移动文件结尾
		if(m_dwFileSize == ftell (m_pFileWrite)) ///求出当前文件指针距离文件开始的字节数
		{
			logprintf(LOG_LVL_KEYSTATUS,"File: write file size is same.\n");
			cbShowMsgtoConsole("写文件大小一致",OutputMsgtoUser);
			post(pMsg->srcid,S_S_WRITEDONE_NOTIFY,NULL,0);
		}else{
			cbShowMsgtoConsole("写文件大小不一致",OutputMsgtoUser);
			post(pMsg->srcid,S_S_WRITEWRONG_NOTIFY,NULL,0);	//2017.07.19增加此消息---文件发送失败
		}
		NextState(FILE_IDLE_STATE);
	} 
	fclose(m_pFileWrite);
	m_pFileWrite = NULL;
	}
	else
	{
		cbShowMsgtoConsole("Warning: 收到服务端写文件命令",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: 收到服务端写文件命令.\n");
	}
	
}