/*==========================================================
��������SendMsgCmd
���ܣ���Daemon���ͷ���Ϣ����
�㷨ʵ�֣�
����˵����chatto ����Ҫ��ϵ�˶�Ӧ��InstanceId  �� msgcontent �����û����͵���Ϣ
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../../include/interface.h"

using namespace std;

extern UCinfo tInterfaceInfo;	//�������������Ϣ

void SendMsgCMD()
{
	cout << "�������������0Ϊ�㲥������Ϣ����,�ָ���" << endl;
	s8 achConetent[BIGSIZE] = {0};
	
	cin.get(achConetent,BIGSIZE);

	if (FALSE == UserInputCheck(MSGCONTCHECK,achConetent))
	{
		cout << "�밴�ո�ʽ����~~~"<<endl;
		return;
	}

	memcpy(tInterfaceInfo.achChatMsg,achConetent,sizeof(achConetent));

    u32 dwRetVal = OspPost(MAKEIID(CLIENT_MSGAPP_NO,CInstance::DAEMON),U_C_SENDMSG_CMD,(u8 *)&achConetent,sizeof(achConetent));//��Daemon���ͷ���Ϣ����
/*    if (0 == dwRetVal)  //�Ƿ��ͳɹ�
    {
		cout << "post to client send msg Cmd succeed." << endl;
    }
    else
    {
		cout <<"post to client send msg Cmd failed." << endl;
    }
*/}