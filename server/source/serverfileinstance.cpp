/*==========================================================
函数名：ServerFileInstance
功能：实现服务器FileInstance相关处理
算法实现：
参数说明：[I/O/IO]参数：含义（说明：按照参数的顺序排序）
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/server.h"
#include "../include/serverfile.h"
#include "../../include/cscommon.h"
#include "fstream"
#include "string.h"

using namespace std;

extern CSFileApp g_CSFileApp;

void CSFileInstance ::InstanceEntry(CMessage *const pMsg)
{
    if (NULL == pMsg) 
    {
		logprintf(LOG_LVL_ERROR,"File: instance pMsg is Null.\n");
        OspQuit();
        return ;
    }

    u16 wCurEvent = pMsg->event;
    OspEventDescShow(wCurEvent);	//Telnet上的OspEventDescShow命令,显示消息的描述
    switch(wCurEvent)
    {
    case S_S_FILEMSG_REQ: //收到写文件通知--准备
	    ProcFileMsgReq(pMsg);
        break; 

    case S_S_WRITEFILE_CMD:         //收到服务端写文件命令 -- 开始执行	
		ProcFileContentCmd(pMsg);
        break;

	case OSP_DISCONNECT:	//收到断链消息
		ProcDisConnect(pMsg);
		break;

    default:
        cbShowMsgtoConsole("写文件app收到未知消息",OutputMsgtoUser);
        break;
    }

}

