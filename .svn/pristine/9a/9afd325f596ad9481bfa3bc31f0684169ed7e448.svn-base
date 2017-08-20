/*==========================================================
模块名：界面头文件
文件名：interface.h
相关文件：
实现功能：定义界面相关数据
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "../../include/osp.h"

#include "iostream"
#include "../include/uccommand.h"


//标志位，用于判断程序是否退出
#define START           0
#define END             8


//用户选项
#define CONNECT         '1'
#define REQLIST         '2'
#define SENDMSG         '3'
#define SENDFILE        '4'
#define INTERRUPT       '5'
#define HELP            '6'
#define QUIT            '7'

//输入检测
#define IPCHECK			8
#define USERNAMECHECK   9
#define MSGCONTCHECK    10
#define FILENAMECONTENT 11



//函数原型---（命名差错-不是发送这样命名，而应该是接收消息的函数这样命名--修改）
void ConnectServerCMD(void);        //连接服务器
void ReqUserListCMD(void);						        //拉用户列表
void SendMsgCMD(void);						//发消息
void SendFileCMD(void);						//发文件
void InterruptConnectCMD(void);						    //断开连接

//消息格式检测下标
enum em_MsgCont
{
	list_0_Num = 0,
	list_1_Comma,
	list_2_Comma,
	list_2_Null = 2,
	list_3_Null = 3,
	list_19_End = 19

};

//用户输入值检测
BOOL32 UserInputCheck(u32 dwRetVal,s8 *pchContent);


#endif

