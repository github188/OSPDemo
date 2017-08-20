/*==========================================================
模块名：界面                            
文件名：interface.cpp
相关文件：iostream.h  interface.h
实现功能：搭建界面，实现用户输入
作者：苏志斌）
版权：MyProject_chat_version2.0  Copyright(C)2017 KDC, All rights reserved
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

==========================================================*/

#include "../../include/interface.h"
#include "io.h"

using namespace std;

//用户输入相关常量
#define USERCHOISE_SIZE      (u32)100
#define USERCHOICE_FIR		 (u32)0
#define USERCHOICE_TWI		 (u32)1

#define INPUTCHECK_FLAG      (s32)-1
#define INPUTCHECK_LOW       (s32)0
#define INPUTCHECK_HIGH      (s32)255
#define IPTEMP_SIZE          (s32)200

UCinfo tInterfaceInfo;	//保存界面输入信息

void Interface()
{
    cout << "Hello SuShare" << endl;
	cout << "Telnet Port__2673" << endl;
    cout << "请输入指令:" << endl;
    cout <<"1.连接服务器  2.查看用户  3.发消息  4.发文件  5.断开连接  6.help  7.退出"<<endl;

    u32 g_dwflag = START;     //while 标志位，用于执行程序退出操作
   
    while (START == g_dwflag)
    {
        s8 achUserChoise[USERCHOISE_SIZE] = {0};	//用户输入指令
        cin.get(achUserChoise,USERCHOISE_SIZE);
     
        getchar();
		
		//判断是否输入为帮助请求
		if (!(strcmp(achUserChoise,"h"))||!(strcmp(achUserChoise,"help")) || !(strcmp(achUserChoise,"HELP")) || !(strcmp(achUserChoise,"H")))
		{
			cout <<"1.连接服务器  2.查看用户  3.发消息  4.发文件  5.断开连接  6.help  7.退出"<<endl;
		}
		//判断输入指令
        else if(achUserChoise[USERCHOICE_FIR] > '0' && achUserChoise[USERCHOICE_FIR] < '9'&& achUserChoise[USERCHOICE_TWI] == NULL)
        {
            switch (achUserChoise[USERCHOICE_FIR])
			{
			case CONNECT:   //  连接
				ConnectServerCMD();
				break;

            case REQLIST:   //拉列表         
                ReqUserListCMD();
                break;

            case SENDMSG:   // 发消息
				SendMsgCMD();	
                break;

            case  SENDFILE:  //发文件
                SendFileCMD();
                break;

            case INTERRUPT:   //断开连接
			    InterruptConnectCMD();
                break;

            case HELP:        //help命令
                cout <<"1.连接服务器  2.查看用户  3.发消息  4.发文件  5.断开连接  6.help  7.退出"<<endl;
                break;

            case QUIT:         //退出     
                cout << "正在退出……" << endl;
                g_dwflag = END;
                break;

            default:
                cout << "输入错误，请重新输入" <<endl;
                break;
			}
        }
		else
		{
			cout <<"input illegal" << endl;
		}
        cin.clear();
        cin.sync();
    }
    return;
}

BOOL32 UserInputCheck(u32 dwRetVal,s8 *pchContent)	//用户输入检测
{
	if (NULL == pchContent) //入口检查
	{
		return FALSE;
	}
	switch(dwRetVal)
	{
	case IPCHECK:  //ip地址检测合法性
		{
			s32 dwTempA = INPUTCHECK_FLAG,dwTempB = INPUTCHECK_FLAG,dwTempC = INPUTCHECK_FLAG,dwTempD = INPUTCHECK_FLAG;
			s8 achIpTemp[IPTEMP_SIZE] = {0};
			sscanf(pchContent,"%d.%d.%d.%d%s",&dwTempA,&dwTempB,&dwTempC,&dwTempD,achIpTemp);
			if (dwTempA > INPUTCHECK_HIGH || dwTempA < INPUTCHECK_LOW||dwTempB > INPUTCHECK_HIGH || dwTempB < INPUTCHECK_LOW||dwTempC > INPUTCHECK_HIGH || dwTempC < INPUTCHECK_LOW||dwTempD > INPUTCHECK_HIGH || dwTempD < INPUTCHECK_LOW)
			{
				return FALSE;
			}
			if (achIpTemp[0] != FALSE)
			{
				return FALSE;
			}
			return TRUE;
		}
		break;

	case USERNAMECHECK:		//用户名检测
		{	
			if (pchContent[LITTLESIZE - 1] == NULL && strlen(pchContent) != 0)
			{
				return TRUE;				
			} 
			return FALSE;
		}
		break;

	case MSGCONTCHECK:		//消息格式检测
		{
			u32 dwTemp ;
			for (dwTemp = 0;dwTemp < sizeof(pchContent);dwTemp++)
			{
				if (pchContent[list_1_Comma] == ',' || pchContent[list_2_Comma] == ',')
				{
					if ( pchContent[list_3_Null] != NULL || pchContent[list_2_Null] != NULL)
					{
						if (pchContent[list_0_Num] >= '0' && pchContent[list_0_Num] < '9')
						{
							return TRUE;
						}
						
					}					
				}
			}
			return FALSE;
		}
		break;

	case FILENAMECONTENT:	//文件存在检测
		{
			if (FALSE == access(pchContent,0))
			{
				return TRUE;
			}
			return FALSE;
		}
		break; 

	default:
		return FALSE;
		break;
	}
}

