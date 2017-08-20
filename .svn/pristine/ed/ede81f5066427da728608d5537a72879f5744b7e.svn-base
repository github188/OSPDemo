

/*==========================================================
函数名：ServerInstance
功能：服务器Instance相关处理
算法实现：
参数说明：[I/O/IO]参数：含义（说明：按照参数的顺序排序）
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"
#include "../include/serverfile.h"
#include "io.h"
using namespace std;

extern CServerApp g_CServerApp;
extern CSFileApp g_CSFileApp;

void CSDateInstance::DaemonInstanceEntry(CMessage *const pMsg, CApp* pcApp)
{
    if ((NULL == pMsg) || (NULL == pcApp))
    {
		logprintf(LOG_LVL_ERROR,"Daemon: server pMsg or pcApp is NULL.\n"); 
        OspQuit();
        return ;
    }
   
    u16 wCurEvent = pMsg ->event;   //得到当前消息的类型
    OspEventDescShow(wCurEvent);	//Telnet上的OspEventDescShow命令,显示消息的描述
    switch (wCurEvent)
    {
    case C_S_REQUSERLIST_REQ:       //拉取列表，遍历instance 
		 DaemonProcUserlistReq(pMsg,pcApp);
         break;
          
    case C_S_SENDMSG_REQ:           //广播消息
		DaemonProcBroadcastReq(pMsg,pcApp);
        break; 

	case S_S_SENDMSGOK_NOTIFY:      //广播消息反馈
		cbShowMsgtoConsole("广播：一条消息发送成功",OutputMsgtoUser);
		break;

	case S_S_SENDMSGFAIL_NOTIFY:    //广播消息反馈
        cbShowMsgtoConsole("广播：一条消息发送失败",OutputMsgtoUser);
        break;

    default:
		cbShowMsgtoConsole("daemon can't read this msg ",OutputMsgtoUser);
        break;
    }
}

void CSDateInstance::InstanceEntry(CMessage *const pMsg)
{
    if (NULL == pMsg)
    {
		logprintf(LOG_LVL_ERROR,"Instance: server pMsg is null.\n");
        OspQuit();
    }

    u16 wCurEvent = pMsg ->event;   //得到当前消息的类型
	OspEventDescShow(wCurEvent);	//Telnet上的OspEventDescShow命令,显示消息的描述
    switch (wCurEvent)
    { 
    case C_S_CONNECTSERVER_REQ:     //连接请求--实现状态切换.消息存储.设置断链检测 
		ProcConnectReq(pMsg);
        break;

    case  C_S_SENDMSG_REQ:      //单发消息-------（7.20需要增加判断对应端是否存在）？ √ 
        ProcSendMsgReq(pMsg);     
        break;

	case S_S_SENDMSGOK_NOTIFY:   //成功发送消息
		ProcSendMsgOkNoti(pMsg);
		break;

	case S_S_SENDMSGFAIL_NOTIFY:	//发送消息失败
		ProcSendMsgFailNoti(pMsg);
		break;

    case S_S_SENDMSG_NOTIFY:    //转发消息
		ProcSendMsgNotify(pMsg);
        break;

    case C_S_SENDFILEMSG_REQ:   //收到发文件请求；实现判断文件名大小是否合适;切换状态，反馈信息；
	    ProcSendFileMsgReq(pMsg);
        break;

	case S_S_FILEMSG_ACK:	//保存写文件app对应instance号 ---2017-8-3客户端同时上传多个文件，如何处理？
		ProcSendFileMsgAck(pMsg);
		break;

	case S_S_FILEMSG_NACK:	//文件信息打开失败，返回客户端nack消息
		ProcSendFileMsgNack(pMsg);
		break;

    case C_S_SENDFILECONTENT_REQ:   //开始发送数据包;实现转发数据给写文件app，以及返回客户端消息
		ProcSendFileReq(pMsg);
        break;

	case S_S_WRITEFILE_NOTIFY:	//发送下一包通知
		ProcWriteFileNoti(pMsg);
		break;

    case S_S_WRITEDONE_NOTIFY:	//服务器收到写完成通知，切换状态，发到客户端
		ProcWriteDoneNoti(pMsg);
        break;

	case S_S_WRITEWRONG_NOTIFY:		//服务器收到写文件出错通知。(未区别)
		ProcWriteWrongNoti(pMsg);		
		break;

    case OSP_DISCONNECT:    //断链--状态切换-----是否传输文件状态--删除未完成的文件(发送消息到fileapp)
        ProcDisConnect(pMsg);	
		break;

	case OSP_OVERFLOW:		//无空闲实例
		ProcOverFlow(pMsg);
		
		break;

    default:
        cbShowMsgtoConsole("server can't read msg ",OutputMsgtoUser);
        break;
    }
}