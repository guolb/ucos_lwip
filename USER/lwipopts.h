#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define TCPIP_THREAD_STACKSIZE    4000//�ں������ջ��С

#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO		  5   //�����ں���������ȼ�Ϊ5
#endif
#undef  DEFAULT_THREAD_PRIO
#define DEFAULT_THREAD_PRIO		  2   //����������̵߳����ȼ�


#define TCPIP_MBOX_SIZE           MBOX_MAX_SIZE   //����ߴ� 

#define LWIP_COMPAT_MUTEX        1                //��ʹ�û����ź���

#define SYS_LIGHTWEIGHT_PROT    1		//Ϊ1ʱʹ��ʵʱ����ϵͳ������������,�����ؼ����벻���жϴ��

#define NO_SYS                  0  		//ʹ��UCOS����ϵͳ

#define CHECKSUM_GEN_ICMP       0       //�ر����У��

#define LWIP_DHCP               1	    //ʹ��DHCP

#undef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       MBOX_MAX_SIZE  

#undef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         MBOX_MAX_SIZE  

#endif /* __LWIPOPTS_H__ */

