/*==========================================================
��������cbShowMsgtoConsole
���ܣ��ص�����
�㷨ʵ�֣�
����˵����lpstrShowMsg������Ҫ��������Ϣ  *ptrΪ���õĺ���
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/cscommon.h"
#include "iostream"

//ֱ�Ӵ�ӡ�ַ���---��ӡ��һ������
void cbShowMsgtoConsole(LPSTR lpstrShowMsg,void (*ptr)(LPSTR lpstrShowMsg))
{
	(*ptr)(lpstrShowMsg);
}

//����u32���κ��ַ�������ӡ����
void cbShowNumToConsole(u32 dwNum,LPSTR lpstrShowMsg,void (*ptr)(u32 dwNum, LPSTR lpstrShowMsg))
{
	(*ptr)(dwNum,lpstrShowMsg);
}

//����loglevel �жϵȼ�Ȼ��ȷ���Ƿ����
void cbShowMsgtoConsole2(u8 byloglevel,LPSTR lpstrShowMsg,void (*ptr)(u8 byloglevel,LPSTR lpstrShowMsg))
{
	(*ptr)(byloglevel,lpstrShowMsg);
}

