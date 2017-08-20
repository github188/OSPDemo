/*==========================================================
��������ProcBuffNotify
���ܣ�������������--��ʼ�����ļ�
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

void CCDateInstance::ProcBuffNotify(CMessage *const pMsg) 
{
	if (FILE_STATE == CurState())
	{
		//logprintf(LOG_LVL_KEYSTATUS,"Instance: recv client file buf full notify.\n");
		m_dwClientId = pMsg->srcid;//����fileApp��id
		
		BufOne.dwBufferState = BUFFER_BUSY;
		s8 achFileContent[CLIENT_SEND_FILE_SIZE] = {0};//��ʼ������
		
		if (m_dwFileNum == 1 ) //�������һ��
		{ 
			memcpy(achFileContent,BufOne.achFileBuffer,(m_dwFileSize - (g_dwFileNumShang * CLIENT_SEND_FILE_SIZE ))*sizeof(s8));               
			m_dwFileNum -- ;
			BufOne.dwBufferState = BUFFER_IDLE;
			post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,(m_dwFileSize - g_dwFileNumShang * CLIENT_SEND_FILE_SIZE),m_dwServerNode);		
		} 
		else
		{
			//instance: �յ�������������Ϣ�������ļ���������. Tick Get ****" << OspTickGet() << endl;
			memcpy(achFileContent,BufOne.achFileBuffer,CLIENT_SEND_FILE_SIZE);
			m_dwFileNum--;
			post(m_dwServerId,C_S_SENDFILECONTENT_REQ,achFileContent,CLIENT_SEND_FILE_SIZE,m_dwServerNode);
		}
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"instance:ERROR �յ�����֪ͨ");
		cbShowMsgtoConsole("instance:ERROR �յ�����֪ͨ��Ϣ",OutputMsgtoUser);
	}	
	
}