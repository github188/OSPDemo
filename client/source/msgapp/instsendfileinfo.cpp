/*==========================================================
��������ProcSendFileInfoCmd
���ܣ��ͻ��˷����ļ���Ϣ��������
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/

#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "io.h"
using namespace std;

extern u32 g_dwFileNumTemp;	    //�洢�ļ����ʹ���--�ж�������ƫ����
extern u32 g_dwFileNumShang;	//�ļ���С��ÿ����С֮��--�����ж�ƫ����

//�����ļ���Ϣ����
void CCDateInstance::ProcSendFileInfoCmd(CMessage *const pMsg) 
{
	if (IDLE_STATE == CurState())
	{
		DateInstanceClear();
		//�����ļ���Ϣ
		s8 achFileInfo[CSBIGSIZE] = {0};           
    memcpy(m_achFilename,pMsg->content,pMsg->length);

	logprintf(LOG_LVL_DETAIL,"Instance: recv file msg.\n");
	cbShowMsgtoConsole("�յ��ļ���Ϣ��",OutputMsgtoUser);
           
	//ʵ�ֻ�ȡ�ļ���Ϣ��С������������-----
    //ֱ�Ӵ���ǰ�ļ�Ŀ¼���ļ�   2017-7-27�ɴ�����·���ļ��������ļ���������������������������������������
/*		FILE *pFile = fopen(m_achFilename,"rb+");
		if (pFile==NULL)
		{
			logprintf(LOG_LVL_ERROR,"Instance: open file error.\n");
			perror("Error opening file");	
		}
		else
		{    
*/          //�޸�--��ȡ�ļ���С  
			//�Ѿ��ж��ļ�����
			struct stat info;

			//stat("../../include",&info);
		    //cout <<"file folder size : "<< info.st_size << endl;

			stat(m_achFilename,&info);
			m_dwFileSize = info.st_size;

		/*	fseek (pFile, 0, SEEK_END);   ///���ļ�ָ���ƶ��ļ���β
			m_dwFileSize =ftell (pFile); ///�����ǰ�ļ�ָ������ļ���ʼ���ֽ���
*/			m_dwFileNum = m_dwFileSize / CLIENT_SEND_FILE_SIZE + 1;//*****���Ǻ���Ҫ����ֵ--��Ҫ���͵Ĵ���
			g_dwFileNumTemp = m_dwFileNum;
			g_dwFileNumShang = g_dwFileNumTemp - 1;

			//07.31ȡ���ļ���----����Ҫ�����ļ�·��
			strcpy(m_achFilePath,m_achFilename);
			for (u32 dwTemp = sizeof(m_achFilePath) - 1;dwTemp > 0;dwTemp--)
			{
				if (m_achFilePath[dwTemp] == '\\')
				{
					memset(m_achFilename,0,sizeof(m_achFilename));
					strcpy(m_achFilename,m_achFilePath+dwTemp+1);
					break;
				}
			}
			//����ļ���С���ļ���
			sprintf(achFileInfo,"%10d%s",m_dwFileSize,m_achFilename);
			cbShowMsgtoConsole(achFileInfo,OutputMsgtoUser);
	
			NextState(CONNECT_STATE);//״̬�л�
			post(pMsg->srcid,C_S_SENDFILEMSG_REQ,achFileInfo,strlen(achFileInfo),pMsg->srcnode);//�������󵽷�����
					
			//���ö������---��֪instance
			OspSetHBParam(pMsg->srcnode,CLIENT_HBTIME,CLIENT_HBNUM);
			OspNodeDiscCBRegQ(pMsg->srcnode,CLIENT_MSGAPP_NO,GetInsID());
	//	}
		//fclose(pFile);
		//pFile = NULL;
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ����ļ���Ϣ");
		cbShowMsgtoConsole("instance:��ȴ��ļ��ϴ����",OutputMsgtoUser);
    }    
	
}   

void CCDateInstance::ProcSendFileInfoAck(CMessage *const pMsg) 
{
	if (CONNECT_STATE == CurState())
	{
		NextState(FILE_STATE);
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv server ack, post cmd to read file instance");
		cbShowMsgtoConsole("�յ��ļ�ack��Ϣ����ʼ�ϴ�~�ϴ����ȼ�telnet����",OutputMsgtoUser);
		
		//����Զ˷�������Ϣ--
		m_dwServerNode = pMsg->srcnode;
		m_dwServerId = pMsg->srcid;
		
		post(MAKEIID(CLIENT_FILEAPP_NO,CInstance::PENDING),C_C_READFILE_CMD,m_achFilePath,sizeof(m_achFilename));//���Ͷ��ļ����fileapp
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ����ļ�ack��Ϣ");
		cbShowMsgtoConsole("instance:ERROR �յ����ļ�ack��Ϣ",OutputMsgtoUser);			
    }
}

void CCDateInstance::ProcSendFileInfoNack(CMessage *const pMsg)
{
	if (CONNECT_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"Instance: recv server nack, can't send file" );
		cbShowMsgtoConsole("�������ܾ��ļ��ϴ�",OutputMsgtoUser);	
		NextState(IDLE_STATE);
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ����ļ�nack��Ϣ");
		cbShowMsgtoConsole("instance:ERROR �յ����ļ�nack��Ϣ",OutputMsgtoUser);		
	}
}