/*==========================================================
ģ�������������                           
�ļ�����logprintf.cpp
����ļ���client.h  
ʵ�ֹ��ܣ��ֲ㼶�������
���ߣ�suzhibin
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/
#include "../include/cscommon.h"
using namespace std;

extern u8 g_byLogLevel;

void OutputMsgtoUser2(u8 byloglevel,LPSTR lpstrReplayMsg)
{
	if (byloglevel <= g_byLogLevel)
	{
		cout << "msg : " << lpstrReplayMsg << endl;
	}
}

void OutPutMsg(u32 dwNum,LPSTR lpstrShowMsg)
{
	cout << "msg : " << lpstrShowMsg << " " << dwNum << endl;

}

void OutputMsgtoUser(LPSTR lpstrReplayMsg)
{
	cout << "msg : " << lpstrReplayMsg << endl;
}