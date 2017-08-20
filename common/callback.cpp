/*==========================================================
函数名：cbShowMsgtoConsole
功能：回调函数
算法实现：
参数说明：lpstrShowMsg保存需要反馈的消息  *ptr为调用的函数
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/
#include "../include/cscommon.h"
#include "iostream"

//直接打印字符串---打印第一个参数
void cbShowMsgtoConsole(LPSTR lpstrShowMsg,void (*ptr)(LPSTR lpstrShowMsg))
{
	(*ptr)(lpstrShowMsg);
}

//传入u32整形和字符串，打印出来
void cbShowNumToConsole(u32 dwNum,LPSTR lpstrShowMsg,void (*ptr)(u32 dwNum, LPSTR lpstrShowMsg))
{
	(*ptr)(dwNum,lpstrShowMsg);
}

//传入loglevel 判断等级然后确定是否输出
void cbShowMsgtoConsole2(u8 byloglevel,LPSTR lpstrShowMsg,void (*ptr)(u8 byloglevel,LPSTR lpstrShowMsg))
{
	(*ptr)(byloglevel,lpstrShowMsg);
}

