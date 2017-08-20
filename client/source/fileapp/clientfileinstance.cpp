/*==========================================================
��������ClientfileInstance
���ܣ��ͻ���fileInstance��ش���
�㷨ʵ�֣�
����˵����[I/O/IO]���������壨˵�������ղ�����˳������
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/
#include "../../include/client.h"
#include "../../../include/cscommon.h"
#include "fstream"
#include "io.h"

using namespace std;

extern struct Buffer BufOne;	//������
extern struct Buffer Buftwo;

//�ļ���ȡ����InstanceEntry���ʵ��
void CCFileInstance::InstanceEntry(CMessage *const pMsg)
{
    if (NULL == pMsg) 
    {
        OspPrintf(TRUE,FALSE,"File InstanceEntry: client pMsg is NULL.\n");
        OspQuit();
        return;
    }
    
    //�����յ�����Ϣ
    u16 wCurEvent = pMsg->event;
    switch(wCurEvent)
    {
    case C_C_READFILE_CMD:  //�յ����ļ�ָ��---��ȡ�ļ���������
		ProcReadFileCmd(pMsg);	//��ȡ�ļ�
		break;

	case C_C_READFILENEXT_NOTIFY:	//��ȡ��һ������������	�������ڵ�-->�����ɣ�����Ϣ������������������sleep(1000),������Ϣ�Ƿ���Ѿ����������ˣ�����sleep�ǻ�������ģ�
		ProcReadFileNextNotify(pMsg);	
		break;
        
    case C_C_WRITEDONE_NOTIFY: //�յ�д�����Ϣ
		ProcWriteDoneNoti(pMsg);
        break;
       
	case C_C_DISCONNECT_NOTIFY:	//�յ����������Ϣ
		ProcDisConnectNoti(pMsg);
		break;

    default:
        logprintf(LOG_LVL_ERROR,"Daemon:ERROR �յ�δ������Ϣ");
		cbShowMsgtoConsole("Daemon:ERROR �յ�δ������Ϣ",OutputMsgtoUser);
        break;
    } 
}