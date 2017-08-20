/*==========================================================
��������ProcSendFileContentReq
���ܣ��ͻ��˷����ļ����ݵ�������
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

extern u32 g_dwFileNumTemp;	    //�洢�ļ����ʹ���--�ж�������ƫ����
extern u32 g_dwFileNumShang;	//�ļ���С��ÿ����С֮��--�����ж�ƫ����
extern Buffer BufOne;
//�����ļ����ݲ���
void CCDateInstance::ProcSendFileContentReq(CMessage *const pMsg) 
{
	if (FILE_STATE == CurState())
	{
		if (m_dwFileNum == 0)	//�ж�Ϊ���һ�����ͳɹ�
		{
			cbShowMsgtoConsole("�ļ�������ϡ�",OutputMsgtoUser);
			BufOne.dwBufferState = BUFFER_IDLE;
		}
		else if(m_dwFileNum != 0 && BufOne.dwBufferState == BUFFER_IDLE)	//������ȡ��һ��������
		{
			post(m_dwClientId,C_C_READFILENEXT_NOTIFY,NULL,0);//������ȡ
		}
		else if(BufOne.dwBufferState == BUFFER_BUSY)	//���ͻ���������
		{
			s8 achFileContent[CLIENT_SEND_FILE_SIZE] = {0};
			
			if (1 == m_dwFileNum) //�������һ��
			{   
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),(m_dwFileSize - (g_dwFileNumShang * CLIENT_SEND_FILE_SIZE ))*sizeof(s8));
				m_dwFileNum -- ;
				BufOne.dwBufferState = BUFFER_IDLE;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,(m_dwFileSize - g_dwFileNumShang * CLIENT_SEND_FILE_SIZE),m_dwServerNode);
				//cout << "instance :�������һ��. Tick Get ****" << OspTickGet() << endl;
			} 
			else if ((g_dwFileNumTemp - m_dwFileNum)%CLIENT_SEND_NUM == (CLIENT_SEND_NUM-1)) //����һ��������
			{
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),CLIENT_SEND_FILE_SIZE*sizeof(s8));
				m_dwFileNum -- ;
				BufOne.dwBufferState = BUFFER_IDLE;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
				//cout << "instance : ����һ�������� . Tick Get ****" << OspTickGet()<< endl;
			}
			else
			{                                                                        //ƫ��������
				memcpy(achFileContent,BufOne.achFileBuffer+CLIENT_SEND_FILE_SIZE*sizeof(s8)*((g_dwFileNumTemp- m_dwFileNum)%CLIENT_SEND_NUM),CLIENT_SEND_FILE_SIZE*sizeof(s8));
				m_dwFileNum -- ;
				post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
				//	cout << "instance :������һ����post֮�� . Tick Get ****" << OspTickGet() << endl; 
			}
			
			//�ͻ��˽�����ʾ��������ʾ    ������telnet������ʾ������������ȼ�Ӧ�ô���һ
		
			logprintf(LOG_LVL_WARNING,"�����ļ�����: %d%%\r",(CSMIDDLESIZE*(g_dwFileNumTemp - m_dwFileNum)/g_dwFileNumTemp));
		}
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ������ļ�ack");
		cbShowMsgtoConsole("instance:ERROR �յ������ļ�ack",OutputMsgtoUser);
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
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ������ļ�nack");
		cbShowMsgtoConsole("instance:ERROR �յ������ļ�nack",OutputMsgtoUser);
	}	
}

void CCDateInstance::ProcSendFileDoneNoti(CMessage *const pMsg) //�������֪ͨ
{
	if (FILE_STATE == CurState())
	{
		post(m_dwClientId,C_C_WRITEDONE_NOTIFY,NULL,0);
		logprintf(LOG_LVL_KEYSTATUS,"Msg: recv server write done notify.\n");
		cbShowMsgtoConsole("�յ�д���֪ͨ",OutputMsgtoUser);
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ������ļ����֪ͨ");
		cbShowMsgtoConsole("instance:ERROR �յ������ļ����֪ͨ",OutputMsgtoUser);		
	}
}


void CCDateInstance::ProcOverFlow(CMessage *const pMsg) //�޿���ʵ��
{
	if (CONNECT_STATE == CurState())
	{
		cbShowMsgtoConsole("д�ļ�app��æ",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"Msg: client file instance is busy.\n");
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ������ļ����֪ͨ");
		cbShowMsgtoConsole("instance:ERROR �յ������ļ����֪ͨ",OutputMsgtoUser);	
	}     
}


void CCDateInstance::ProcDisConnect(CMessage *const pMsg)  //�Ͽ�����---�������
{
	if (IDLE_STATE != CurState())
	{
		cbShowMsgtoConsole("osp���ӶϿ�",OutputMsgtoUser);
		logprintf(LOG_LVL_ERROR,"Msg: osp disconnect.\n");
		if (CurState() == FILE_STATE) //��fileapp��������Ϣ���ı�״̬
		{
			post(m_dwClientId,C_C_DISCONNECT_NOTIFY,NULL,0);
		}
		NextState(IDLE_STATE);
		DateInstanceClear();
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:�յ�OSP������Ϣ");
		cbShowMsgtoConsole("instance: �յ�OSP������Ϣ",OutputMsgtoUser);
	}
}
