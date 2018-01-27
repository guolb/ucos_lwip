#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define TCPIP_THREAD_STACKSIZE    4000//内核任务堆栈大小

#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO		  5   //定义内核任务的优先级为5
#endif
#undef  DEFAULT_THREAD_PRIO
#define DEFAULT_THREAD_PRIO		  2   //分配给其他线程的优先级



#define LWIP_COMPAT_MUTEX        1                //不使用互斥信号量

#define TCPIP_MBOX_SIZE           MBOX_MAX_SIZE   //邮箱尺寸  

#define SYS_LIGHTWEIGHT_PROT    1		//为1时使用实时操作系统的轻量级保护,保护关键代码不被中断打断

#define NO_SYS                  0  		//使用UCOS操作系统

#define CHECKSUM_GEN_ICMP       0       //关闭软件校验

#define LWIP_DHCP               1	    //使用DHCP

#undef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       MBOX_MAX_SIZE  

#undef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         MBOX_MAX_SIZE  


//通过硬件识别和计算IP,UDP和ICMP的帧校验和
#if  !CHECKSUM_GEN_ICMP    //判断是否开启硬件校验,关闭软件校验
  //CHECKSUM_GEN_IP==0: 硬件生成IP数据包的帧校验和
  #define CHECKSUM_GEN_IP                 0
  //CHECKSUM_GEN_UDP==0: 硬件生成UDP数据包的帧校验和
  #define CHECKSUM_GEN_UDP                0
  //CHECKSUM_GEN_TCP==0: 硬件生成TCP数据包的帧校验和
  #define CHECKSUM_GEN_TCP                0 
  //CHECKSUM_CHECK_IP==0: 硬件检查输入的IP数据包帧校验和
  #define CHECKSUM_CHECK_IP               0
  //CHECKSUM_CHECK_UDP==0: 硬件检查输入的UDP数据包帧校验和
  #define CHECKSUM_CHECK_UDP              0
  //CHECKSUM_CHECK_TCP==0: 硬件检查输入的TCP数据包帧校验和
  #define CHECKSUM_CHECK_TCP              0
#else
  //CHECKSUM_GEN_IP==1: 软件生成IP数据包帧校验和
  #define CHECKSUM_GEN_IP                 1
  // CHECKSUM_GEN_UDP==1: 软件生成UDOP数据包帧校验和
  #define CHECKSUM_GEN_UDP                1
  //CHECKSUM_GEN_TCP==1: 软件生成TCP数据包帧校验和
  #define CHECKSUM_GEN_TCP                1
  // CHECKSUM_CHECK_IP==1: 软件检查输入的IP数据包帧校验和
  #define CHECKSUM_CHECK_IP               1
  // CHECKSUM_CHECK_UDP==1: 软件检查输入的UDP数据包帧校验和
  #define CHECKSUM_CHECK_UDP              1
  //CHECKSUM_CHECK_TCP==1: 软件检查输入的TCP数据包帧校验和
  #define CHECKSUM_CHECK_TCP              1
#endif



#endif /* __LWIPOPTS_H__ */

