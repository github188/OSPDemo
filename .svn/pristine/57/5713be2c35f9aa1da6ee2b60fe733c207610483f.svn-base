/*==========================================================
函数名：ReqUserListCmd
功能：向Daemon发送请求用户列表命令
算法实现：
参数说明：
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../../include/interface.h"

using namespace std;

void ReqUserListCMD()
{
    u32 dwRetVal;
    dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_REQUSERLIST_CMD,NULL,0);//给Daemon发送消息
/*    if (0 == dwRetVal)  //是否发送成功
    {
		cout << "post to client daemon ReqUserList Cmd succeed."<< endl;
    }
    else
    {
		cout << "post to client daemon ReqUserList Cmd failed. " << endl;
    }
 */  
}
