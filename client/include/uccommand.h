/*==========================================================
模块名：界面/客户端交互
文件名：uccommand.h
相关文件：
实现功能：定义交互消息类型和基本属性
作者：苏志斌
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/

#ifndef _UCCOMMAND_H_
#define _UCCOMMAND_H_


#define CLIENT_MSGAPP_NO              1		        //客户端msgAPP  id号
#define CLIENT_FILEAPP_NO             2				//客户端fileAPP id号
//消息类型
//连接/断开服务器 内容：
#define U_C_CONNECTSERVER_CMD       (u16)(OSP_USEREVENT_BASE+0x0001)
#define U_C_INTERCONNECT_CMD        (u16)(OSP_USEREVENT_BASE+0x0002)
//拉取用户列表
#define U_C_REQUSERLIST_CMD         (u16)(OSP_USEREVENT_BASE+0x0007)
//发消息
#define U_C_SENDMSG_CMD             (u16)(OSP_USEREVENT_BASE+0x000B)
//发文件
#define U_C_SENDFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0011)
//帮助
#define U_C_HELPCOMMAND_CMD         (u16)(OSP_USEREVENT_BASE+0x001F)

//局部变量大小---数组定义
#define LITTLESIZE      40
#define MIDDLESIZE      100
#define BIGSIZE         200

//定义一个结构体保存用户输入连接信息
typedef struct UserCInput
{
	s8 achIpaddr[LITTLESIZE];	  //服务器ip地址
	s8 achusername[LITTLESIZE];   //用户名
	s8 achChatMsg[BIGSIZE];		  //聊天内容
	s8 achFilePath[BIGSIZE];	  //文件路径   
}UCinfo;


#endif