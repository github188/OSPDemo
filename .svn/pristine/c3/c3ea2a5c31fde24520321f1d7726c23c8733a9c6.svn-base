/*==========================================================
函数名：SendFileCmd
功能：向Daemon发送发文件命令
算法实现：
参数说明：
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../../include/interface.h"

using namespace std;

extern UCinfo tInterfaceInfo;	//保存界面输入信息

void SendFileCMD()
{
	s8 achFileInfo[BIGSIZE] = {0};//保存文件路径
    cout << "请输入需上传文件路径：" << endl;
    cin.get(achFileInfo,BIGSIZE);
	if (FALSE == UserInputCheck(FILENAMECONTENT,achFileInfo))
	{
		cout << "该文件不存在" <<endl;
		return;
	}

	memcpy(tInterfaceInfo.achFilePath,achFileInfo,sizeof(achFileInfo));
    //发文件命令---Daemon
    u32 dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_SENDFILE_CMD,tInterfaceInfo.achFilePath,sizeof(tInterfaceInfo.achFilePath));   
/*    if (0 == dwRetVal)
    {
		cout << "post send file cmd to client daemon succeed." << endl;
    } 
    else
    {
		cout << "post send file cmd to client daemon failed." << endl;
    }
*/
  } 