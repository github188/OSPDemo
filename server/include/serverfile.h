/*==========================================================
模块名：服务器文件存储模块
文件名：serverfile.h
相关文件：osp.h, kdvtype.h
实现功能：配置服务器
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
--------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录
   
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
类名 ：CSFileInstance
功能 ：继承CInstance，实现服务器自定义的InstanceEntry
主要接口：void DaemonInstanceEntry：必须重载以实现与客户端的连接，无返回值
          void InstanceEntry: 重载以实现与客户端的信息传输
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CSFileInstance : public CInstance{
private:
    s8  m_achFileName[CSBIGSIZE];
    u32 m_dwFileSize;
    u32 m_dwInsState;

	//记录文件信息
    FILE * m_pFileWrite;	//文件写指针	

    u32  m_dwFileNum;		//文件写--计数
	
	//定义服务器缓存区
	struct Buffer{
		u32 dwBufferState;                              //Buff状态
		s8  achFileBuffer[SERVER_STOREFILE_BUFF_SIZE];	//Buff大小
	};

    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry( CMessage *const, CApp* pCApp){};

	void ProcFileMsgReq(CMessage *const pMsg);	        //收到文件信息
	void ProcFileContentCmd(CMessage *const pMsg);      //开始写文件内容

	void ProcDisConnect(CMessage *const pMsg);

public:  
    void CSFileInstanceClear()
    {
       memset(m_achFileName,0,CSBIGSIZE);
	   m_dwFileSize = 0;
	   m_dwInsState = 0;
	   
	   //记录文件信息
	   m_pFileWrite = NULL;	//文件写指针	
	   
       m_dwFileNum = 0; //文件写--计数
    }
};
/*====================================================================
类名 ：CServerFileApp
功能 ：继承CAppNoData 文件存储空间大小
主要接口：
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CServerFileData : public CAppNoData{


};

//产生服务器FileApp的模板
typedef zTemplate<CSFileInstance,FILE_MAX_INSTANCE,CServerFileData,255>CSFileApp;
 
#endif

