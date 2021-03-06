/*==========================================================
模块名：服务器数据传输模块
文件名：server.h
相关文件：osp.h, kdvtype.h
实现功能：配置服务器
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
--------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录
   
==========================================================*/
#ifndef _SERVER_H_
#define _SERVER_H_

#include "../../include/osp.h"
#include "../../include/kdvtype.h"
#include "../../Include/cscommon.h"


#define SERVER_APP_PRIO         100				//app优先级
#define SERVER_MSGAPP_NAME      "MSGSERVER"		//服务器msgapp名
#define SERVER_FILEAPP_NAME     "FILESERVER"	//服务器fileapp名

//server msg app      
#define SERVER_MAX_INSTANCE     3				//最大instance数量
#define SERVER_APP_QUE_SIZE     1000

#define SERVER_TELENT_PORT      2667

#define SERVER_DEFAULT_SIZE			 (u32)20000000000  //文件存储空间大小

#define SERVER_FILE_BUFF_SIZE		 (u32)28672	       //单次包的大小
#define SERVER_STOREFILE_BUFF_SIZE   (u32)7340032      //缓存区大小

//消息类型 --- 服务器间的交互
#define S_S_CONNECTSERVER_NOTIFY    (u16)(OSP_USEREVENT_BASE+0x0006)   //连接通知--没用到？
#define S_S_SENDMSG_NOTIFY          (u16)(OSP_USEREVENT_BASE+0x000F)   //发送消息通知
#define S_S_WRITEFILE_CMD           (u16)(OSP_USEREVENT_BASE+0x001D)   //写文件命令
#define S_S_WRITEDONE_NOTIFY        (u16)(OSP_USEREVENT_BASE+0x001E)   //写完成通知
#define S_S_WRITEWRONG_NOTIFY		(u16)(OSP_USEREVENT_BASE+0x0028)   //2017.07.19增加文件上传失败消息

#define S_S_FILEMSG_NOTIFY          (u16)(OSP_USEREVENT_BASE+0x0025)   //发送文件信息
/************************************************************************/
/* 2017.07.18 修改增加服务端的消息请求和反馈                            */
/************************************************************************/
#define S_S_FILEMSG_REQ				(u16)(OSP_USEREVENT_BASE+0x0026)
#define S_S_FILEMSG_ACK				(u16)(OSP_USEREVENT_BASE+0x0027)
#define S_S_FILEMSG_NACK            (u16)(OSP_USEREVENT_BASE+0x002D)
/************************************************************************/
/* 2017.07.21 修改增加服务端的定时反馈无联系人消息                                                                     */
/************************************************************************/	
#define S_S_SENDMSGFAIL_NOTIFY		(u16)(OSP_USEREVENT_BASE+0x0029)
#define S_S_SENDMSGOK_NOTIFY		(u16)(OSP_USEREVENT_BASE+0x002A)
/************************************************************************/
/* 2017.07.27 修改增加服务端的写一包数据确认消息                                                                     */
/************************************************************************/	
#define S_S_WRITEFILE_NOTIFY		(u16)(OSP_USEREVENT_BASE+0x002C)

//instance状态
#define IDLE_STATE             (u32)0           //instance状态：空闲状态
#define CONNECT_STATE          (u32)1           //instance状态：连接状态
#define FILE_STATE             (u32)2           //instance状态：传文件状态

#define SERVER_HBTIME          (u16)10          //链路检测周期(以秒为单位)
#define SERVER_HBNUM           (u8)5            //如果连续ping了u4HbNum次没有应答, 主动断开

#define WAITED_TIME				10000			//定时器时长


/*====================================================================
类名 ：CSDateInstance
功能 ：继承CInstance，实现服务器自定义的InstanceEntry
主要接口：void DaemonInstanceEntry：必须重载以实现与客户端的连接，无返回值
          void InstanceEntry: 重载以实现与客户端的信息传输
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CSDateInstance : public CInstance{
private:
     u32 m_dwClientNode;     //客户端信息
     u32 m_dwInsState;
	
	 u32 m_dwServerId;		//保存写文件AppId号
    
     u32 m_dwClientId;		//保存消息传输id号
	 u32 m_dwClientFileId;	//保存文件传输id号
     s8  m_achClientName[40];

     u32 m_dwFileSize;
     s8  m_achFileName[220];
	 u32 m_dwFileNum;		//文件传输次数
	 u32 m_dwNumCount;		//文件传输计数

     void InstanceEntry(CMessage *const pMsg);
     void DaemonInstanceEntry( CMessage *const pMsg, CApp* pcApp);

	 void DaemonProcUserlistReq(CMessage *const pMsg, CApp* pcApp);    //拉取用户列表

	 void DaemonProcBroadcastReq(CMessage *const pMsg, CApp* pcApp);   //广播消息
	 void ProcConnectReq(CMessage *const pMsg);					       //连接操作
	 void ProcDisConnect(CMessage *const pMsg);						   //断链操作
	 void ProcOverFlow(CMessage *const pMsg);						   //无空闲实例


	 void ProcSendMsgReq(CMessage *const pMsg);                        //发送消息操作
	 void ProcSendMsgOkNoti(CMessage *const pMsg);					   //消息反馈
	 void ProcSendMsgFailNoti(CMessage *const pMsg);
	 void ProcSendMsgNotify(CMessage *const pMsg);                     //收到消息通知操作

	 void ProcSendFileMsgReq(CMessage *const pMsg);                    //收到发送文件信息请求
	 void ProcSendFileMsgAck(CMessage *const pMsg);  
	 void ProcSendFileMsgNack(CMessage *const pMsg);

	 void ProcSendFileReq(CMessage *const pMsg);					   //文件内容请求
     void ProcWriteFileNoti(CMessage *const pMsg);
	 void ProcWriteDoneNoti(CMessage *const pMsg);
	 void ProcWriteWrongNoti(CMessage *const pMsg);


		
public:  
    void CSDateInstanceClear()
    {
        m_dwClientNode = 0;     //客户端信息
		m_dwInsState = IDLE_STATE;
		
		m_dwServerId = 0;		//保存写文件AppId号
		m_dwClientId = 0;		//保存消息传输id号
	    m_dwClientFileId = 0;	//保存文件传输id号
		memset(m_achClientName,0,CSLITTLESIZE);
		
		m_dwFileSize = 0;
		memset(m_achFileName,0,CSBIGSIZE);
		m_dwFileNum = 0;		//文件传输次数
	    m_dwNumCount = 0;		//文件传输计数
    }
};

/*====================================================================
类名 ：CServerMsgApp
功能 ：继承CAppNoData 文件存储空间大小
主要接口：
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CServerMsgData : public CAppNoData{
private:
    u32 m_dwFileLeftStore;

public:
    void SetFileLeftStore(u32 size)
    {
        m_dwFileLeftStore = size;
    }
    u32 GetFileLeftStore()
    {
        return m_dwFileLeftStore;
    }

	void CServerAppClear()
	{
		m_dwFileLeftStore = 0;
	}
};



//产生服务器App的模板
typedef zTemplate<CSDateInstance,SERVER_MAX_INSTANCE,CServerMsgData,255>CServerApp;

//获取文件夹大小
u32 GetFolderSize(LPSTR lpstrFilePath);

#endif



