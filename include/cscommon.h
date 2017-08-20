/*==========================================================
模块名：客户端/服务器同
文件名：cscommom.h
相关文件：
实现功能：定义交互消息类型和基本属性
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/

#ifndef _CSCOMMOND_H_
#define _CSCOMMOND_H_

#include "iostream"
#include "../include/osp.h"
#include "../include/kdvtype.h"
#include "../include/kdvdef.h"

//#define CLIENT_MSGAPP_NO              1		        //客户端msgAPP  id号
//#define CLIENT_FILEAPP_NO             2				//客户端fileAPP id号
#define SERVER_MSGAPP_NO              3             //服务器msgAPP  id号
#define SERVER_FILEAPP_NO             4             //服务器fileAPP id号

#define SERVER_LISTEN_PORT            6688          //服务器监听端口号

//客户端(C)与服务器(S)的交互信息
//连接/断开服务器
#define C_S_CONNECTSERVER_REQ       (u16)(OSP_USEREVENT_BASE+0x0003)		//连接服务器请求
#define S_C_CONNECTSERVER_ACK       (u16)(OSP_USEREVENT_BASE+0x0004)		//连接服务器ack反馈
#define S_C_CONNECTSERVER_NACK      (u16)(OSP_USEREVENT_BASE+0x0005)		//连接服务器nack反馈
//拉取用户列表
#define C_S_REQUSERLIST_REQ         (u16)(OSP_USEREVENT_BASE+0x0008)		//请求用户列表
#define S_C_REQUSERLIST_ACK         (u16)(OSP_USEREVENT_BASE+0x0009)		//用户列表反馈ack
#define S_C_REQUSERLIST_NACK        (u16)(OSP_USEREVENT_BASE+0x000A)		//用户列表反馈nack
//发消息
#define C_S_SENDMSG_REQ             (u16)(OSP_USEREVENT_BASE+0x000C)		//发送消息请求
#define S_C_SENDMSG_ACK             (u16)(OSP_USEREVENT_BASE+0x000D)		//消息发送状态反馈ack
#define S_C_SENDMSG_NACK            (u16)(OSP_USEREVENT_BASE+0x000E)		//消息发送状态反馈nack
#define S_C_SENDMSG_NOTIFY          (u16)(OSP_USEREVENT_BASE+0x0022)		//接收消息通知

//发文件
#define C_S_SENDFILEMSG_REQ         (u16)(OSP_USEREVENT_BASE+0x0013)		//发送文件信息请求
#define S_C_SENDFILEMSG_ACK         (u16)(OSP_USEREVENT_BASE+0x0014)		//文件发送反馈ack
#define S_C_SENDFILEMSG_NACK        (u16)(OSP_USEREVENT_BASE+0x0015)		//文件发送反馈nack

#define C_S_SENDFILECONTENT_REQ     (u16)(OSP_USEREVENT_BASE+0x0018)		//发送文件内容请求
#define S_C_SENDFILECONTENT_ACK     (u16)(OSP_USEREVENT_BASE+0x0019)		//文件内容反馈ack
#define S_C_SENDFILECONTENT_NACK    (u16)(OSP_USEREVENT_BASE+0x001A)		//文件内容反馈nack
#define S_C_SENDFILEDONE_NOTIFY     (u16)(OSP_USEREVENT_BASE+0x001B)		//文件发送完成通知
#define S_C_SENDFILEWRONG_NOTIFY    (u16)(OSP_USEREVENT_BASE+0x002E)		//文件发送失败通知



// log等级定义
#define		LOG_LVL_ERROR					(u8)1				// 程序运行错误(逻辑或业务出错),必须输出
#define		LOG_LVL_WARNING					(u8)2				// 告警信息, 可能正确, 也可能错误
#define		LOG_LVL_KEYSTATUS				(u8)3				// 程序运行到一个关键状态时的信息输出
#define		LOG_LVL_DETAIL					(u8)4				// 普通信息, 最好不要写进log文件中
#define		LOG_LVL_REPEAT					(u8)5      			// 更高级别打印


//局部变量大小---数组定义相关以及部分sleep参数。。。
#define CSLITTLESIZE      40
#define CSMIDDLESIZE      100
#define CSBIGSIZE         200

#define ZERONUM			  0
#define FIRSTNUM		  1

//telnet窗口输出函数
void logprintf(u8 sLevel,LPSTR lpstrFormat,...);

//回调函数定义---参数一为要显示在终端的字符；参数二是函数指针调用OutputMsgtoUser(默认值)；
void cbShowMsgtoConsole(LPSTR lpstrShowMsg,void (*ptr)(LPSTR lpstrMsgtemp));
extern void OutputMsgtoUser(LPSTR lpstrReplayMsg);

void cbShowMsgtoConsole2(u8 byloglevel,LPSTR lpstrShowMsg,void (*ptr)(u8 byRetVal,LPSTR lpstrMsgtemp));
extern void OutputMsgtoUser2(u8 byloglevel,LPSTR lpstrReplayMsg);

void cbShowNumToConsole(u32 dwNum,LPSTR lpstrShowMsg,void (*ptr)(u32 dwNum, LPSTR lpstrShowMsg));
extern void  OutPutMsg(u32 dwNum,LPSTR lpstrShowMsg);


#endif