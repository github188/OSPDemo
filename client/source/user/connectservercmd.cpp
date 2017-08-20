/*==========================================================
函数名：CconnectServercCmd
功能：向Daemon发送连接服务器命令
算法实现：
参数说明：arr1 保存ip地址的指针  arr2 保存用户名
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/

#include "../../include/interface.h"

using namespace std;
extern UCinfo tInterfaceInfo;	//保存界面输入信息

void ConnectServerCMD()
{
	s8 achipaddr[LITTLESIZE] = {0};   //服务器ip
	s8 achusername[LITTLESIZE] = {0}; //用户名
				
	cout << "输入服务器IP："<<endl;
	cin.get(achipaddr,LITTLESIZE);
	if (FALSE == UserInputCheck(IPCHECK,achipaddr))
	{
		cout << "ip地址不合法，重新来过---】"<<endl;
        return;
	}
    getchar();
				
	cout <<"输入用户名："<<endl;
	cin.get(achusername,LITTLESIZE);
	if (FALSE == UserInputCheck(USERNAMECHECK,achusername))
	{
		cout << "用户名不符合规则，重新来过---】"<<endl;
		return;
	}
	
	memset(&tInterfaceInfo,0,sizeof(tInterfaceInfo));//使用之前初始化结构体
	memcpy(tInterfaceInfo.achIpaddr,achipaddr,sizeof(achipaddr));
	memcpy(tInterfaceInfo.achusername,achusername,sizeof(achusername));

    u32 dwRetVal;                //OspPost返回值
   
    dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_CONNECTSERVER_CMD,(u8*)&tInterfaceInfo,sizeof(tInterfaceInfo));//给Daemon发送连接消息

/*	if (0 == dwRetVal)  //是否发送成功
    {
		cout << "post to daemon Msg Cmd succeed.\n" <<endl;
    }
    else
    {
		cout << "post to daemon Msg Cmd failed.\n" << endl;
    } 
*/}
