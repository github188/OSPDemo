/*==========================================================
ģ�������������ļ��洢ģ��
�ļ�����serverfile.h
����ļ���osp.h, kdvtype.h
ʵ�ֹ��ܣ����÷�����
���ߣ���־��
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
--------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼
   
==========================================================*/
#ifndef _SERVERFILE_H_
#define _SERVERFILE_H_

#include "../../include/osp.h"
#include "../../include/kdvtype.h"

//file app info
#define FILE_MAX_INSTANCE       3
#define FILE_APP_QUE_SIZE       1000

//instance state
#define FILE_IDLE_STATE         (u32)0
#define FILE_WRITE_STATE        (u32)1

/*====================================================================
���� ��CSFileInstance
���� ���̳�CInstance��ʵ�ַ������Զ����InstanceEntry
��Ҫ�ӿڣ�void DaemonInstanceEntry������������ʵ����ͻ��˵����ӣ��޷���ֵ
          void InstanceEntry: ������ʵ����ͻ��˵���Ϣ����
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��		�汾		�޸���		�߶���		�޸ļ�¼
	  
====================================================================*/
class CSFileInstance : public CInstance{
private:
    s8  m_achFileName[CSBIGSIZE];
    u32 m_dwFileSize;
    u32 m_dwInsState;

	//��¼�ļ���Ϣ
    FILE * m_pFileWrite;	//�ļ�дָ��	

    u32  m_dwFileNum;		//�ļ�д--����
	
	//���������������
	struct Buffer{
		u32 dwBufferState;                              //Buff״̬
		s8  achFileBuffer[SERVER_STOREFILE_BUFF_SIZE];	//Buff��С
	};

    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry( CMessage *const, CApp* pCApp){};

	void ProcFileMsgReq(CMessage *const pMsg);	        //�յ��ļ���Ϣ
	void ProcFileContentCmd(CMessage *const pMsg);      //��ʼд�ļ�����

	void ProcDisConnect(CMessage *const pMsg);

public:  
    void CSFileInstanceClear()
    {
       memset(m_achFileName,0,CSBIGSIZE);
	   m_dwFileSize = 0;
	   m_dwInsState = 0;
	   
	   //��¼�ļ���Ϣ
	   m_pFileWrite = NULL;	//�ļ�дָ��	
	   
       m_dwFileNum = 0; //�ļ�д--����
    }
};
/*====================================================================
���� ��CServerFileApp
���� ���̳�CAppNoData �ļ��洢�ռ��С
��Ҫ�ӿڣ�
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��		�汾		�޸���		�߶���		�޸ļ�¼
	  
====================================================================*/
class CServerFileData : public CAppNoData{


};

//����������FileApp��ģ��
typedef zTemplate<CSFileInstance,FILE_MAX_INSTANCE,CServerFileData,255>CSFileApp;
 
#endif

