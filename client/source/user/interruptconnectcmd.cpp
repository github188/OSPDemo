/*==========================================================
��������InterruptConnectCmd
���ܣ���Daemon���ͶϿ�����������
�㷨ʵ�֣�
����˵����arr1 ����ip��ַ��ָ��  arr2 �����û���
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../../include/interface.h"

using namespace std;

void InterruptConnectCMD()
{
    u32 dwRetVal;                //OspPost����ֵ
    
    dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_INTERCONNECT_CMD,NULL,0);//��Daemon����������Ϣ
/*    if (0 == dwRetVal)  //�Ƿ��ͳɹ�
    {
		cout << "post to client daemon InterConnect Cmd succeed." << endl;
    }
    else
    {
		cout << "post to client daemon InterConnect Cmd failed." <<endl;
    }
  */ 
}