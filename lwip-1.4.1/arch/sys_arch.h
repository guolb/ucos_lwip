#ifndef __ARCH_SYS_ARCH_H__
#define __ARCH_SYS_ARCH_H__ 
#include "arch/cc.h"

 
#define MBOX_NUM        		  10	// 消息邮箱的数量
#define MBOX_MAX_SIZE         20  //每个消息邮箱的大小


//LWIP消息邮箱结构体
typedef struct 
{
    OS_EVENT*   pst;                          //UCOS中指向事件控制块的指针
    void*       pvQEntries[MBOX_MAX_SIZE];    //UCOS消息队列 
} LWip_MBOX,*pstMBOX;

typedef OS_EVENT  *sys_sem_t;      //LWIP使用的信号量
typedef pstMBOX    sys_mbox_t;     //LWIP使用的消息邮箱,其实就是UCOS中的消息队列
typedef INT8U      sys_thread_t;   //线程ID,也就是任务优先级

#endif 





































