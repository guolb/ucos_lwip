#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define TCPIP_THREAD_STACKSIZE    4000//�ں������ջ��С

#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO		  5   //�����ں���������ȼ�Ϊ5
#endif
#undef  DEFAULT_THREAD_PRIO
#define DEFAULT_THREAD_PRIO		  2   //����������̵߳����ȼ�



#define LWIP_COMPAT_MUTEX        1                //��ʹ�û����ź���

#define TCPIP_MBOX_SIZE           MBOX_MAX_SIZE   //����ߴ�  

#define SYS_LIGHTWEIGHT_PROT    1		//Ϊ1ʱʹ��ʵʱ����ϵͳ������������,�����ؼ����벻���жϴ��

#define NO_SYS                  0  		//ʹ��UCOS����ϵͳ

#define CHECKSUM_GEN_ICMP       0       //�ر����У��

#define LWIP_DHCP               1	    //ʹ��DHCP

#undef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       MBOX_MAX_SIZE  

#undef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         MBOX_MAX_SIZE  


//ͨ��Ӳ��ʶ��ͼ���IP,UDP��ICMP��֡У���
#if  !CHECKSUM_GEN_ICMP    //�ж��Ƿ���Ӳ��У��,�ر����У��
  //CHECKSUM_GEN_IP==0: Ӳ������IP���ݰ���֡У���
  #define CHECKSUM_GEN_IP                 0
  //CHECKSUM_GEN_UDP==0: Ӳ������UDP���ݰ���֡У���
  #define CHECKSUM_GEN_UDP                0
  //CHECKSUM_GEN_TCP==0: Ӳ������TCP���ݰ���֡У���
  #define CHECKSUM_GEN_TCP                0 
  //CHECKSUM_CHECK_IP==0: Ӳ����������IP���ݰ�֡У���
  #define CHECKSUM_CHECK_IP               0
  //CHECKSUM_CHECK_UDP==0: Ӳ����������UDP���ݰ�֡У���
  #define CHECKSUM_CHECK_UDP              0
  //CHECKSUM_CHECK_TCP==0: Ӳ����������TCP���ݰ�֡У���
  #define CHECKSUM_CHECK_TCP              0
#else
  //CHECKSUM_GEN_IP==1: �������IP���ݰ�֡У���
  #define CHECKSUM_GEN_IP                 1
  // CHECKSUM_GEN_UDP==1: �������UDOP���ݰ�֡У���
  #define CHECKSUM_GEN_UDP                1
  //CHECKSUM_GEN_TCP==1: �������TCP���ݰ�֡У���
  #define CHECKSUM_GEN_TCP                1
  // CHECKSUM_CHECK_IP==1: �����������IP���ݰ�֡У���
  #define CHECKSUM_CHECK_IP               1
  // CHECKSUM_CHECK_UDP==1: �����������UDP���ݰ�֡У���
  #define CHECKSUM_CHECK_UDP              1
  //CHECKSUM_CHECK_TCP==1: �����������TCP���ݰ�֡У���
  #define CHECKSUM_CHECK_TCP              1
#endif



#endif /* __LWIPOPTS_H__ */

