/*==========================================================
ģ����������/�ͻ��˽���
�ļ�����uccommand.h
����ļ���
ʵ�ֹ��ܣ����彻����Ϣ���ͺͻ�������
���ߣ���־��
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/

#ifndef _UCCOMMAND_H_
#define _UCCOMMAND_H_


#define CLIENT_MSGAPP_NO              1		        //�ͻ���msgAPP  id��
#define CLIENT_FILEAPP_NO             2				//�ͻ���fileAPP id��
//��Ϣ����
//����/�Ͽ������� ���ݣ�
#define U_C_CONNECTSERVER_CMD       (u16)(OSP_USEREVENT_BASE+0x0001)
#define U_C_INTERCONNECT_CMD        (u16)(OSP_USEREVENT_BASE+0x0002)
//��ȡ�û��б�
#define U_C_REQUSERLIST_CMD         (u16)(OSP_USEREVENT_BASE+0x0007)
//����Ϣ
#define U_C_SENDMSG_CMD             (u16)(OSP_USEREVENT_BASE+0x000B)
//���ļ�
#define U_C_SENDFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0011)
//����
#define U_C_HELPCOMMAND_CMD         (u16)(OSP_USEREVENT_BASE+0x001F)

//�ֲ�������С---���鶨��
#define LITTLESIZE      40
#define MIDDLESIZE      100
#define BIGSIZE         200

//����һ���ṹ�屣���û�����������Ϣ
typedef struct UserCInput
{
	s8 achIpaddr[LITTLESIZE];	  //������ip��ַ
	s8 achusername[LITTLESIZE];   //�û���
	s8 achChatMsg[BIGSIZE];		  //��������
	s8 achFilePath[BIGSIZE];	  //�ļ�·��   
}UCinfo;


#endif