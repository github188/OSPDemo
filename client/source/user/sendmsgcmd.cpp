/*==========================================================
函数名：SendMsgCmd
功能：向Daemon发送发消息命令
算法实现：
参数说明：chatto 保存要联系人对应的InstanceId  ； msgcontent 保存用户发送的消息
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../../include/interface.h"

using namespace std;

extern UCinfo tInterfaceInfo;	//保存界面输入信息

void SendMsgCMD()
{
	cout << "请输入聊天对象（0为广播）和消息（以,分隔）" << endl;
	s8 achConetent[BIGSIZE] = {0};
	
	cin.get(achConetent,BIGSIZE);

	if (FALSE == UserInputCheck(MSGCONTCHECK,achConetent))
	{
		cout << "请按照格式输入~~~"<<endl;
		return;
	}

	memcpy(tInterfaceInfo.achChatMsg,achConetent,sizeof(achConetent));

    u32 dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_SENDMSG_CMD,(u8 *)&achConetent,sizeof(achConetent));//给Daemon发送发消息命令
/*    if (0 == dwRetVal)  //是否发送成功
    {
		cout << "post to client send msg Cmd succeed." << endl;
    }
    else
    {
		cout <<"post to client send msg Cmd failed." << endl;
    }
*/}