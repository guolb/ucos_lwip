#ifndef __ARCH_SYS_ARCH_H__
#define __ARCH_SYS_ARCH_H__ 
#include "arch/cc.h"

 
#define MBOX_NUM        		  10	// ��Ϣ���������
#define MBOX_MAX_SIZE         20  //ÿ����Ϣ����Ĵ�С


//LWIP��Ϣ����ṹ��
typedef struct 
{
    OS_EVENT*   pst;                          //UCOS��ָ���¼����ƿ��ָ��
    void*       pvQEntries[MBOX_MAX_SIZE];    //UCOS��Ϣ���� 
} LWip_MBOX,*pstMBOX;

typedef OS_EVENT  *sys_sem_t;      //LWIPʹ�õ��ź���
typedef pstMBOX    sys_mbox_t;     //LWIPʹ�õ���Ϣ����,��ʵ����UCOS�е���Ϣ����
typedef INT8U      sys_thread_t;   //�߳�ID,Ҳ�����������ȼ�

#endif 





































