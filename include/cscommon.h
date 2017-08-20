/*==========================================================
ģ�������ͻ���/������ͬ
�ļ�����cscommom.h
����ļ���
ʵ�ֹ��ܣ����彻����Ϣ���ͺͻ�������
���ߣ���־��
��Ȩ��MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

==========================================================*/

#ifndef _CSCOMMOND_H_
#define _CSCOMMOND_H_

#include "iostream"
#include "../include/osp.h"
#include "../include/kdvtype.h"
#include "../include/kdvdef.h"

//#define CLIENT_MSGAPP_NO              1		        //�ͻ���msgAPP  id��
//#define CLIENT_FILEAPP_NO             2				//�ͻ���fileAPP id��
#define SERVER_MSGAPP_NO              3             //������msgAPP  id��
#define SERVER_FILEAPP_NO             4             //������fileAPP id��

#define SERVER_LISTEN_PORT            6688          //�����������˿ں�

//�ͻ���(C)�������(S)�Ľ�����Ϣ
//����/�Ͽ�������
#define C_S_CONNECTSERVER_REQ       (u16)(OSP_USEREVENT_BASE+0x0003)		//���ӷ���������
#define S_C_CONNECTSERVER_ACK       (u16)(OSP_USEREVENT_BASE+0x0004)		//���ӷ�����ack����
#define S_C_CONNECTSERVER_NACK      (u16)(OSP_USEREVENT_BASE+0x0005)		//���ӷ�����nack����
//��ȡ�û��б�
#define C_S_REQUSERLIST_REQ         (u16)(OSP_USEREVENT_BASE+0x0008)		//�����û��б�
#define S_C_REQUSERLIST_ACK         (u16)(OSP_USEREVENT_BASE+0x0009)		//�û��б���ack
#define S_C_REQUSERLIST_NACK        (u16)(OSP_USEREVENT_BASE+0x000A)		//�û��б���nack
//����Ϣ
#define C_S_SENDMSG_REQ             (u16)(OSP_USEREVENT_BASE+0x000C)		//������Ϣ����
#define S_C_SENDMSG_ACK             (u16)(OSP_USEREVENT_BASE+0x000D)		//��Ϣ����״̬����ack
#define S_C_SENDMSG_NACK            (u16)(OSP_USEREVENT_BASE+0x000E)		//��Ϣ����״̬����nack
#define S_C_SENDMSG_NOTIFY          (u16)(OSP_USEREVENT_BASE+0x0022)		//������Ϣ֪ͨ

//���ļ�
#define C_S_SENDFILEMSG_REQ         (u16)(OSP_USEREVENT_BASE+0x0013)		//�����ļ���Ϣ����
#define S_C_SENDFILEMSG_ACK         (u16)(OSP_USEREVENT_BASE+0x0014)		//�ļ����ͷ���ack
#define S_C_SENDFILEMSG_NACK        (u16)(OSP_USEREVENT_BASE+0x0015)		//�ļ����ͷ���nack

#define C_S_SENDFILECONTENT_REQ     (u16)(OSP_USEREVENT_BASE+0x0018)		//�����ļ���������
#define S_C_SENDFILECONTENT_ACK     (u16)(OSP_USEREVENT_BASE+0x0019)		//�ļ����ݷ���ack
#define S_C_SENDFILECONTENT_NACK    (u16)(OSP_USEREVENT_BASE+0x001A)		//�ļ����ݷ���nack
#define S_C_SENDFILEDONE_NOTIFY     (u16)(OSP_USEREVENT_BASE+0x001B)		//�ļ��������֪ͨ
#define S_C_SENDFILEWRONG_NOTIFY    (u16)(OSP_USEREVENT_BASE+0x002E)		//�ļ�����ʧ��֪ͨ



// log�ȼ�����
#define		LOG_LVL_ERROR					(u8)1				// �������д���(�߼���ҵ�����),�������
#define		LOG_LVL_WARNING					(u8)2				// �澯��Ϣ, ������ȷ, Ҳ���ܴ���
#define		LOG_LVL_KEYSTATUS				(u8)3				// �������е�һ���ؼ�״̬ʱ����Ϣ���
#define		LOG_LVL_DETAIL					(u8)4				// ��ͨ��Ϣ, ��ò�Ҫд��log�ļ���
#define		LOG_LVL_REPEAT					(u8)5      			// ���߼����ӡ


//�ֲ�������С---���鶨������Լ�����sleep����������
#define CSLITTLESIZE      40
#define CSMIDDLESIZE      100
#define CSBIGSIZE         200

#define ZERONUM			  0
#define FIRSTNUM		  1

//telnet�����������
void logprintf(u8 sLevel,LPSTR lpstrFormat,...);

//�ص���������---����һΪҪ��ʾ���ն˵��ַ����������Ǻ���ָ�����OutputMsgtoUser(Ĭ��ֵ)��
void cbShowMsgtoConsole(LPSTR lpstrShowMsg,void (*ptr)(LPSTR lpstrMsgtemp));
extern void OutputMsgtoUser(LPSTR lpstrReplayMsg);

void cbShowMsgtoConsole2(u8 byloglevel,LPSTR lpstrShowMsg,void (*ptr)(u8 byRetVal,LPSTR lpstrMsgtemp));
extern void OutputMsgtoUser2(u8 byloglevel,LPSTR lpstrReplayMsg);

void cbShowNumToConsole(u32 dwNum,LPSTR lpstrShowMsg,void (*ptr)(u32 dwNum, LPSTR lpstrShowMsg));
extern void  OutPutMsg(u32 dwNum,LPSTR lpstrShowMsg);


#endif