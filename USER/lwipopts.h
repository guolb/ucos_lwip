#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define TCPIP_THREAD_STACKSIZE    4000//内核任务堆栈大小

#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO		  5   //定义内核任务的优先级为5
#endif
#undef  DEFAULT_THREAD_PRIO
#define DEFAULT_THREAD_PRIO		  2   //分配给其他线程的优先级


#define TCPIP_MBOX_SIZE           MBOX_MAX_SIZE   //邮箱尺寸 

#define LWIP_COMPAT_MUTEX        1                //不使用互斥信号量

#define SYS_LIGHTWEIGHT_PROT    1		//为1时使用实时操作系统的轻量级保护,保护关键代码不被中断打断

#define NO_SYS                  0  		//使用UCOS操作系统

#define CHECKSUM_GEN_ICMP       0       //关闭软件校验

#define LWIP_DHCP               1	    //使用DHCP

#undef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       MBOX_MAX_SIZE  

#undef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         MBOX_MAX_SIZE  

#endif /* __LWIPOPTS_H__ */

