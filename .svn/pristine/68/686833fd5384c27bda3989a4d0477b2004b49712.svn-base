/*==========================================================
函数名：ClientInstance
功能：客户端Instance相关处理
算法实现：
参数说明：[I/O/IO]参数：含义（说明：按照参数的顺序排序）
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../../include/client.h"
#include "../../include/uccommand.h"
#include "../../../include/cscommon.h"

#include "fstream"

using namespace std;

CClientMsgApp g_CClientApp;
CClientFileApp  g_CClientFileApp;

struct Buffer BufOne;	//缓存区
struct Buffer Buftwo;

u32 g_dwFileNumTemp ;	//存储文件发送次数--判定条件和偏移量
u32 g_dwFileNumShang ;	//文件大小和每包大小之差--用来判定偏移量

UCinfo tClientInfo;		//保存客户端信息

//DaemonInstanceEntry入口函数设置
void CCDateInstance::DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp)
{
    if ((NULL == pMsg) || (NULL == pcApp))
    {
		logprintf(LOG_LVL_ERROR,"client pMsg or pcApp is NULL.\n");
        OspQuit();
        return;
    }
    //处理收到的消息
    u16 wCurEvent = pMsg->event;    
  	OspEventDescShow(wCurEvent);	//Telnet上的OspEventDescShow命令,显示消息的描述
    switch(wCurEvent)
    {	
	case U_C_CONNECTSERVER_CMD:     //连接服务器 
        DaemonProcConnectCmd(pMsg);    //连接服务器  
        break;

    case S_C_CONNECTSERVER_ACK:     //连接成功反馈--状态切换
		DaemonProcConnectAck(pMsg);
		break;

	case S_C_CONNECTSERVER_NACK: //连接失败反馈---用户名为空
	    DaemonProcConnectNack(pMsg);
		break;
    
    case U_C_REQUSERLIST_CMD:       //请求用户列表
		DaemonProcReqListCmd(pMsg);
        break;

    case S_C_REQUSERLIST_ACK:       //用户列表反馈
		DaemonProcReqListAck(pMsg);	
        break;

    case S_C_REQUSERLIST_NACK:      //无用户反馈
		DaemonProcReqListNack(pMsg);
        break;

    case U_C_SENDMSG_CMD:   //发消息
		DaemonProcMsgSendCmd(pMsg);            
        break;

	case S_C_SENDMSG_ACK:   //消息发送ack反馈
		DaemonProcSendMsgAck(pMsg);
		break;

	case S_C_SENDMSG_NACK:    //消息发送nack反馈
		DaemonProcSendMsgNack(pMsg);		
		break;

    case S_C_SENDMSG_NOTIFY:    //收到消息通知
		DaemonProcSendMsgNoti(pMsg);
        break;

    case U_C_SENDFILE_CMD:      //发文件命令
		DaemonProcSendFileCmd(pMsg); 
        break;
 
    case OSP_OVERFLOW:  //无空闲实例
		DaemonOverFlow(pMsg);		
        break;

    case OSP_DISCONNECT:    //断链---切换状态
		DaemonDisConnect(pMsg);
        break;

    case CONNECT_TIMEOUT:   //连接服务器超时
		DaemonConnectTimeOut(pMsg);
        break;

	case U_C_INTERCONNECT_CMD:	//断开连接
		DaemonProcInterCmd(pMsg);	
		break;

    default:
		logprintf(LOG_LVL_ERROR,"Daemon:ERROR 收到未定义消息");
		cbShowMsgtoConsole("Daemon:ERROR 收到未定义消息",OutputMsgtoUser);
        break;
    }
}

//文件传输部分InstanceEntry入口实现
void CCDateInstance::InstanceEntry(CMessage *const pMsg)
{
    if (NULL == pMsg) 
    {
		logprintf(LOG_LVL_ERROR,"Instance: client pMsg is NUll.\n");
        OspQuit();	//退出osp
        return ;	//程序结束
    }
    //处理收到的消息
    u16 wCurEvent = pMsg->event;
//	OspEventDescShow(wCurEvent);	//Telnet上的OspEventDescShow命令,显示消息的描述
    switch(wCurEvent)
    {
    case C_C_SENDFILE_CMD:      //发文件指令----发送文件名和大小到服务器
       	ProcSendFileInfoCmd(pMsg);	//发送文件信息    
        break;

    case S_C_SENDFILEMSG_ACK:   //文件ack反馈消息，发送cmd通知读文件app
		ProcSendFileInfoAck(pMsg);		
        break;

    case S_C_SENDFILEMSG_NACK:   //文件NACK消息，无法发送文件
        ProcSendFileInfoNack(pMsg);
		break;

    case C_C_BUFFULL_NOTIFY:    //收到file app读完成通知，开始发送数据包；每收到此消息走一个循环、最后一个依据大小；
		ProcBuffNotify(pMsg);
        break;

    case S_C_SENDFILECONTENT_ACK:   //服务器返回ack，发送下一包数据	
		ProcSendFileContentReq(pMsg);
        break;

    case S_C_SENDFILECONTENT_NACK:  //服务器返回nack，发送同一包数据  ！！待完成---暂时为服务器写完成判断总大小
        ProcSendFileNack(pMsg);
		break;

    case S_C_SENDFILEDONE_NOTIFY:      //收到写完成通知，切换状态，通知fileApp
        ProcSendFileDoneNoti(pMsg);
		break;

    case OSP_OVERFLOW:      //读文件app无空闲Instance
		ProcOverFlow(pMsg);
        break;

	case OSP_DISCONNECT:    //断链---切换状态
		ProcDisConnect(pMsg);	
        break;

    default:
		logprintf(LOG_LVL_ERROR,"Msg: can't read pMsg.\n");
		cbShowMsgtoConsole("instance收到未知消息",OutputMsgtoUser);
        break;
    }
}
