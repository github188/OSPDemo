

/*==========================================================
��������ServerInstance
���ܣ�������Instance��ش���
�㷨ʵ�֣�
����˵����[I/O/IO]���������壨˵�������ղ�����˳������
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../include/server.h"
#include "../../include/cscommon.h"
#include "../include/serverfile.h"
#include "io.h"
using namespace std;

extern CServerApp g_CServerApp;
extern CSFileApp g_CSFileApp;

void CSDateInstance::DaemonInstanceEntry(CMessage *const pMsg, CApp* pcApp)
{
    if ((NULL == pMsg) || (NULL == pcApp))
    {
		logprintf(LOG_LVL_ERROR,"Daemon: server pMsg or pcApp is NULL.\n"); 
        OspQuit();
        return ;
    }
   
    u16 wCurEvent = pMsg ->event;   //�õ���ǰ��Ϣ������
    OspEventDescShow(wCurEvent);	//Telnet�ϵ�OspEventDescShow����,��ʾ��Ϣ������
    switch (wCurEvent)
    {
    case C_S_REQUSERLIST_REQ:       //��ȡ�б�����instance 
		 DaemonProcUserlistReq(pMsg,pcApp);
         break;
          
    case C_S_SENDMSG_REQ:           //�㲥��Ϣ
		DaemonProcBroadcastReq(pMsg,pcApp);
        break; 

	case S_S_SENDMSGOK_NOTIFY:      //�㲥��Ϣ����
		cbShowMsgtoConsole("�㲥��һ����Ϣ���ͳɹ�",OutputMsgtoUser);
		break;

	case S_S_SENDMSGFAIL_NOTIFY:    //�㲥��Ϣ����
        cbShowMsgtoConsole("�㲥��һ����Ϣ����ʧ��",OutputMsgtoUser);
        break;

    default:
		cbShowMsgtoConsole("daemon can't read this msg ",OutputMsgtoUser);
        break;
    }
}

void CSDateInstance::InstanceEntry(CMessage *const pMsg)
{
    if (NULL == pMsg)
    {
		logprintf(LOG_LVL_ERROR,"Instance: server pMsg is null.\n");
        OspQuit();
    }

    u16 wCurEvent = pMsg ->event;   //�õ���ǰ��Ϣ������
	OspEventDescShow(wCurEvent);	//Telnet�ϵ�OspEventDescShow����,��ʾ��Ϣ������
    switch (wCurEvent)
    { 
    case C_S_CONNECTSERVER_REQ:     //��������--ʵ��״̬�л�.��Ϣ�洢.���ö������ 
		ProcConnectReq(pMsg);
        break;

    case  C_S_SENDMSG_REQ:      //������Ϣ-------��7.20��Ҫ�����ж϶�Ӧ���Ƿ���ڣ��� �� 
        ProcSendMsgReq(pMsg);     
        break;

	case S_S_SENDMSGOK_NOTIFY:   //�ɹ�������Ϣ
		ProcSendMsgOkNoti(pMsg);
		break;

	case S_S_SENDMSGFAIL_NOTIFY:	//������Ϣʧ��
		ProcSendMsgFailNoti(pMsg);
		break;

    case S_S_SENDMSG_NOTIFY:    //ת����Ϣ
		ProcSendMsgNotify(pMsg);
        break;

    case C_S_SENDFILEMSG_REQ:   //�յ����ļ�����ʵ���ж��ļ�����С�Ƿ����;�л�״̬��������Ϣ��
	    ProcSendFileMsgReq(pMsg);
        break;

	case S_S_FILEMSG_ACK:	//����д�ļ�app��Ӧinstance�� ---2017-8-3�ͻ���ͬʱ�ϴ�����ļ�����δ���
		ProcSendFileMsgAck(pMsg);
		break;

	case S_S_FILEMSG_NACK:	//�ļ���Ϣ��ʧ�ܣ����ؿͻ���nack��Ϣ
		ProcSendFileMsgNack(pMsg);
		break;

    case C_S_SENDFILECONTENT_REQ:   //��ʼ�������ݰ�;ʵ��ת�����ݸ�д�ļ�app���Լ����ؿͻ�����Ϣ
		ProcSendFileReq(pMsg);
        break;

	case S_S_WRITEFILE_NOTIFY:	//������һ��֪ͨ
		ProcWriteFileNoti(pMsg);
		break;

    case S_S_WRITEDONE_NOTIFY:	//�������յ�д���֪ͨ���л�״̬�������ͻ���
		ProcWriteDoneNoti(pMsg);
        break;

	case S_S_WRITEWRONG_NOTIFY:		//�������յ�д�ļ�����֪ͨ��(δ����)
		ProcWriteWrongNoti(pMsg);		
		break;

    case OSP_DISCONNECT:    //����--״̬�л�-----�Ƿ����ļ�״̬--ɾ��δ��ɵ��ļ�(������Ϣ��fileapp)
        ProcDisConnect(pMsg);	
		break;

	case OSP_OVERFLOW:		//�޿���ʵ��
		ProcOverFlow(pMsg);
		
		break;

    default:
        cbShowMsgtoConsole("server can't read msg ",OutputMsgtoUser);
        break;
    }
}