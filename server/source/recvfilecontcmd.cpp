/*==========================================================
��������ProcFileContentCmd
���ܣ�������д�ļ�app�յ��ļ����ݲ���
�㷨ʵ�֣�
����˵����pMsg : OSP���ݵ���Ϣ��
����ֵ˵������
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../include/serverfile.h"
#include "../../include/cscommon.h"
//using namespace std; //����cout���Ϊ�˷���鿴����
void CSFileInstance::ProcFileContentCmd(CMessage *const pMsg)
{
	if (FILE_WRITE_STATE == CurState())
	{
		logprintf(LOG_LVL_KEYSTATUS,"File: recv write file cmd.\n");
	    //cbShowMsgtoConsole("д�ļ�app�յ�д����",OutputMsgtoUser);
	
	//�ϴ���ָ��Ŀ¼--���޸��ļ�·��
//	s8 achFilePath[256] = {0};
//	sprintf(achFilePath,"%s",m_achFileName); //���õ�ǰ·��
	//�ļ�ָ����ļ�
	m_pFileWrite = fopen(m_achFileName,"ab");
	/*if (m_pFileWrite == NULL)
	{
		perror ("Error opening file"); 
		NextState(FILE_IDLE_STATE);
		post(pMsg->srcid,S_S_FILEMSG_NACK,NULL,0); //����nack��Ϣ
	}*/

	//�˴�Ӧ��ʵ���ж�д��ɵ�����--
	//fseek(m_pFileWrite,0,SEEK_END);----����������ԣ��������ļ���С��С��������
	u32 dwRetVal = fwrite(pMsg->content,sizeof(u8),pMsg->length,m_pFileWrite);
	//m_dwFilePlace = m_dwFilePlace + dwRetVal;
	m_dwFileNum--;
//	cout << "д���--����" << m_dwFileNum << " д���ļ���С :" << dwRetVal << " . Tick Get****" << OspTickGet() << endl;//������ʾ
	post(pMsg->srcid,S_S_WRITEFILE_NOTIFY,NULL,0,0);	//���ط�����һ��ȷ�ϡ�
	
	if (0 == m_dwFileNum)
	{
		logprintf(LOG_LVL_KEYSTATUS,"File: write file done.\n");
		cbShowMsgtoConsole("д�ļ�appȷ��д���",OutputMsgtoUser);
		fseek (m_pFileWrite, 0, SEEK_END);   ///���ļ�ָ���ƶ��ļ���β
		if(m_dwFileSize == ftell (m_pFileWrite)) ///�����ǰ�ļ�ָ������ļ���ʼ���ֽ���
		{
			logprintf(LOG_LVL_KEYSTATUS,"File: write file size is same.\n");
			cbShowMsgtoConsole("д�ļ���Сһ��",OutputMsgtoUser);
			post(pMsg->srcid,S_S_WRITEDONE_NOTIFY,NULL,0);
		}else{
			cbShowMsgtoConsole("д�ļ���С��һ��",OutputMsgtoUser);
			post(pMsg->srcid,S_S_WRITEWRONG_NOTIFY,NULL,0);	//2017.07.19���Ӵ���Ϣ---�ļ�����ʧ��
		}
		NextState(FILE_IDLE_STATE);
	} 
	fclose(m_pFileWrite);
	m_pFileWrite = NULL;
	}
	else
	{
		cbShowMsgtoConsole("Warning: �յ������д�ļ�����",OutputMsgtoUser);
		logprintf(LOG_LVL_WARNING,"msgapp: �յ������д�ļ�����.\n");
	}
	
}