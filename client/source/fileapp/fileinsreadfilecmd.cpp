/*==========================================================
��������ProcReadFileCmd
���ܣ��ͻ����ļ�app��ȡ�ļ�
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/

#include "../../include/client.h"
#include "../../../include/cscommon.h"
extern Buffer BufOne;

//��ȡ�ļ���Ϣ����
void CCFileInstance::ProcReadFileCmd(CMessage *const pMsg) 
{
	if (FILE_IDLE_STATE == CurState())
	{
		//״̬�л�
		NextState(FILE_READ_STATE);
		
		memcpy(m_achFileName,pMsg->content,pMsg->length);
		
		//cout << "file instance : recv read file cmd.\n start to send file::" << m_achFileName << endl;
		logprintf(LOG_LVL_KEYSTATUS,"File: recv cmd ,start to send file.\n");
		
		BufOne.dwBufferState = BUFFER_IDLE;
		memset(BufOne.achFileBuffer,0,CLIENT_FILE_BUFF_SIZE*sizeof(s8));
		

		//�ļ��򿪶�ȡ�浽������
		m_pFileRead = fopen(m_achFileName,"rb"); 
		if (m_pFileRead==NULL)
		{
			perror ("Error opening file");
			NextState(FILE_IDLE_STATE);
			fclose(m_pFileRead);
			m_pFileRead = NULL;
		}
		else
		{   //�ļ���С
			struct stat info;
			stat(m_achFileName,&info);
	        m_dwFilesize = info.st_size;
			//fseek (m_pFileRead, 0, SEEK_END);   ///���ļ�ָ���ƶ��ļ���β
			//m_dwFilesize =ftell (m_pFileRead); ///�����ǰ�ļ�ָ������ļ���ʼ���ֽ���
			//fseek(m_pFileRead,0,SEEK_SET);
		}		
		//����filesizeʵ���жϷ����߼�
		if (m_dwFilesize <= CLIENT_FILE_BUFF_SIZE )//С��buffֵ����ֱ�ӷ���֪ͨ
		{
			fread(BufOne.achFileBuffer,sizeof(s8),m_dwFilesize,m_pFileRead);
			BufOne.dwBufferState = BUFFER_FULL;
			post(pMsg->srcid,C_C_BUFFULL_NOTIFY,NULL,0);
		} 
		else    //����Buffֵ������״̬��д�뻺����;����ļ���СҲ������������������--���һ����������
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
		if (fclose(m_pFileRead))//�ر��ļ���
		{
			perror("fclose");
		}
	    m_pFileRead = NULL;
	}
	else
	{
		logprintf(LOG_LVL_ERROR,"fileinst:ERROR �յ����ļ�cmd");
		cbShowMsgtoConsole("fileinst:ERROR �յ����ļ�cmd.",OutputMsgtoUser);
	}
	
}