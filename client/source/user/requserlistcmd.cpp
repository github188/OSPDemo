/*==========================================================
��������ReqUserListCmd
���ܣ���Daemon���������û��б�����
�㷨ʵ�֣�
����˵����
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../../include/interface.h"

using namespace std;

void ReqUserListCMD()
{
    u32 dwRetVal;
    dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_REQUSERLIST_CMD,NULL,0);//��Daemon������Ϣ
/*    if (0 == dwRetVal)  //�Ƿ��ͳɹ�
    {
		cout << "post to client daemon ReqUserList Cmd succeed."<< endl;
    }
    else
    {
		cout << "post to client daemon ReqUserList Cmd failed. " << endl;
    }
 */  
}
