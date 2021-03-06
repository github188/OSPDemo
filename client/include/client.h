/*==========================================================
模块名：客户端数据传输模块
文件名：client.h
相关文件：osp.h, kdvtype.h  kdvdef.h
实现功能：配置客户端
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录
   
==========================================================*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "iostream"
#include "../../include/osp.h"
#include "../../include/kdvtype.h"
#include "../../include/kdvdef.h"
#include "../include/uccommand.h"
#include <sys/stat.h>       //获取文件信息


#define CLIENT_APP_PRIO            100              //app优先级
#define CLIENT_APP_NAME            "CLIENT"         //客户端app名称
#define CLIENT_FILEAPP_NAME        "CFILE"          //客户端读文件app

//App
#define CLIENT_MAX_INSTANCE        1                //客户端最大instance数量
#define CLIENT_APP_QUE_SIZE        100              //客户端消息等待队列

#define CLIENT_TELENT_PORT         2673             //客户端telent端口号
#define CLIENT_LISTEN_PORT         6682             //客户端监听端口号


//FILEApp
#define CLIENT_FILEMAX_INSTANCE    1                //客户端File App最大instance数量
#define CLIENT_FILEAPP_QUE_SIZE    100              //客户端File App消息等待队列

#define CLIENT_FILE_BUFF_SIZE       (u32)7340032    //缓存大小
#define CLIENT_SEND_FILE_SIZE       (u32)28672      //每次发送文件大小

#define CLIENT_SEND_NUM             (u32)(CLIENT_FILE_BUFF_SIZE/CLIENT_SEND_FILE_SIZE)	//一个缓存的包数

//消息类型---客户端msg - file instance的交互
#define C_C_SENDFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0012)	//msgapp发送文件命令（带上文件名）fileapp--准备
#define C_C_READFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0016)	//读取文件命令
#define C_C_BUFFULL_NOTIFY          (u16)(OSP_USEREVENT_BASE+0x0017)    //msgapp 收到缓存区满的通知
#define C_C_WRITEDONE_NOTIFY        (u16)(OSP_USEREVENT_BASE+0x0021)	//fileapp收到写完成的通知

#define C_C_READFILENEXT_NOTIFY		(u16)(OSP_USEREVENT_BASE+0x0023)	//fileapp收到读取下一个缓存区的通知

#define CONNECT_TIMEOUT             (u16)(OSP_USEREVENT_BASE+0x0020)	//fileapp收到连接超时的消息

/************************************************************************/
/* 2017-8-3添加断链检测通知fileapp消息                                */
/************************************************************************/
#define C_C_DISCONNECT_NOTIFY       (u16)(OSP_USEREVENT_BASE+0x002D)	//fileapp收到断链通知

//msg app instance状态
#define IDLE_STATE             (u32)0           //instance状态：空闲状态
#define CONNECT_STATE          (u32)1           //instance状态：连接状态
#define FILE_STATE             (u32)2           //instance状态：传文件状态

//file app instance状态
#define FILE_IDLE_STATE        (u32)0           //空闲状态
#define FILE_READ_STATE        (u32)4           //读文件状态

//buffer状态
#define BUFFER_IDLE            (u32)5           //buffer状态：空闲
#define BUFFER_BUSY            (u32)6           //buffer状态：写入
#define BUFFER_FULL            (u32)7           //buffer状态：写满

#define CLIENT_HBTIME          (u16)10          //链路检测周期(以秒为单位)
#define CLIENT_HBNUM           (u8)5            //如果连续ping了u4HbNum次没有应答, 主动断开
#define CONNECT_TIME           10000            //定时器时长


/*====================================================================
类名 ：CCDateInstance
功能 ：继承CInstance，实现客户端自定义的InstanceEntry
主要接口：void DaemonInstanceEntry：必须重载以实现与服务器的连接，无返回值
          void InstanceEntry: 重载以实现与服务器的信息传输
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/

class CCDateInstance : public CInstance{
private:
    u32 m_dwServerNode;		//保存服务器信息
    u32 m_dwServerId;
    u32 m_dwClientId;	    //保存对应写文件id
	
	//ip地址和用户名
    s8  m_achIpAddr[LITTLESIZE] ;	
    s8  m_achusername[LITTLESIZE];
	//文件信息
    u32 m_dwFileSize;
    s8  m_achFilename[BIGSIZE];
	s8  m_achFilePath[BIGSIZE];
    u32 m_dwFileNum;		//文件发送次数

	u32 * m_pdwLocalIP;		//保存本地ip地址，用于组合用户名

private:
    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
    void DaemonProcConnectCmd(CMessage *const pMsg);	    //连接服务器命令
	void DaemonProcConnectAgainCmd(CMessage *const pMsg);   //重连服务器
	void DaemonProcConnectAck(CMessage *const pMsg);		//连接确认
	void DaemonProcConnectNack(CMessage *const pMsg);		//连接失败
	void DaemonOverFlow(CMessage *const pMsg);				//无空闲
	void DaemonDisConnect(CMessage *const pMsg);			//断链
	void DaemonConnectTimeOut(CMessage *const pMsg);        //连接超时
	void DaemonProcInterCmd(CMessage *const pMsg);          //断开连接

	void DaemonProcReqListCmd(CMessage *const pMsg);		//请求列表
	void DaemonProcReqListAck(CMessage *const pMsg);		//列表反馈
	void DaemonProcReqListNack(CMessage *const pMsg);

	void DaemonProcMsgSendCmd(CMessage *const pMsg);        //消息发送
    void DaemonProcSendMsgAck(CMessage *const pMsg);  
	void DaemonProcSendMsgNack(CMessage *const pMsg); 
	void DaemonProcSendMsgNoti(CMessage *const pMsg);
	void DaemonProcSendFileCmd(CMessage *const pMsg);

    void ProcSendFileInfoCmd(CMessage *const pMsg);		    //发送文件信息
    void ProcSendFileInfoAck(CMessage *const pMsg);	
	void ProcSendFileInfoNack(CMessage *const pMsg);

	void ProcBuffNotify(CMessage *const pMsg);				//读取缓存区
	void ProcSendFileContentReq(CMessage *const pMsg);	    //发送文件内容
	void ProcSendFileNack(CMessage *const pMsg);
	void ProcSendFileDoneNoti(CMessage *const pMsg);

	void ProcOverFlow(CMessage *const pMsg);
	void ProcDisConnect(CMessage *const pMsg);


public:  
	
	void DateInstanceClear()
	{  
	    m_dwServerNode=0;		//保存服务器信息
        m_dwServerId = 0;
        m_dwClientId = 0;	    //保存对应写文件id
	    m_dwFileSize = 0;
		m_dwFileNum  = 0;
		m_pdwLocalIP = NULL;
		memset(m_achIpAddr,0,LITTLESIZE) ;	
        memset(m_achusername,0,LITTLESIZE);
		memset(m_achFilename,0,BIGSIZE);
	    memset(m_achFilePath,0,BIGSIZE);
	}
};

/*====================================================================
类名 ：CCFileInstance
功能 ：继承CInstance，实现客户端文件自定义的InstanceEntry
主要接口：void DaemonInstanceEntry：必须重载以实现与服务器的连接，无返回值
          void InstanceEntry: 重载以实现与服务器的信息传输
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CCFileInstance:public CInstance{
private:
    s8 m_achFileName[BIGSIZE];   //文件信息
    u32 m_dwFilesize;
	u32 m_dwFileNum;

    FILE *m_pFileRead;		//文件指针
    s32  m_dwFilePlace;		//文件读取记录

    u32 m_dwInsState;       //instance状态   

    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp){};

	void ProcReadFileCmd(CMessage *const pMsg);		    //读取文件
	void ProcReadFileNextNotify(CMessage *const pMsg);  //读取下一个缓存区

	void ProcWriteDoneNoti(CMessage *const pMsg);       //写完成
	void ProcDisConnectNoti(CMessage *const pMsg);

public:  
    void CCFileInstanceClear()
    {
		memset(m_achFileName,0,BIGSIZE);   //文件信息
		m_dwFilesize = 0;
		m_dwFileNum = 0;	
		m_pFileRead = NULL;		//文件指针
		m_dwFilePlace = 0;		//文件读取记录	
        m_dwInsState = FILE_IDLE_STATE;       //instance状态 
    }
};

/*====================================================================
类名 ：CClientMsgData

功能 ：继承CAppNoData，保存服务器反馈的信息
  
主要接口：
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CClientMsgData:public CAppNoData{


	
};

/*====================================================================
类名 ：CClientMsgData
功能 ：继承CAppNoData，保存服务器反馈的信息
主要接口：
----------------------------------------------------------------------
修改记录 ：
日 期		版本		修改人		走读人		修改记录
	  
====================================================================*/
class CClientFileData:public CAppNoData{

};


//产生客户端App的模板
typedef zTemplate<CCDateInstance,CLIENT_MAX_INSTANCE,CClientMsgData>CClientMsgApp;
typedef zTemplate<CCFileInstance,CLIENT_FILEMAX_INSTANCE,CClientFileData>CClientFileApp;


//定义客户端全局缓存区-------
struct Buffer{
    u32 dwBufferState;      //Buff状态
    s8  achFileBuffer[CLIENT_FILE_BUFF_SIZE];
};


//用户界面函数
void Interface(void);

#endif