#include "stm32f10x.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/init.h"
#include "lwip/timers.h"
#include "lwip/tcp_impl.h"
#include "lwip/ip_frag.h"
#include "lwip/tcpip.h"
#include "stm32_eth.h"
#include <stdio.h>


err_t ethernetif_init(struct netif *netif); //其他文件内函数声明
err_t ethernetif_input(struct netif *netif);//其他文件内函数声明

u8_t MACaddr[6]={0,0,0,0,0,1};              //MAC地址，具有唯一性

struct netif netif;                          //定义一个全局的网络接口，注册网卡函数要用到  



void LWIP_Init(void)
{
  struct ip_addr ipaddr;     //定义IP地址结构体
  struct ip_addr netmask;    //定义子网掩码结构体
  struct ip_addr gw;         //定义网关结构体

  mem_init();  //初始化动态内存堆

  memp_init(); //初始化内存池

  tcpip_init(NULL,NULL); //初始化LWIP内核
	
#if LWIP_DHCP     //如果开启DHCP，自动获取IP
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#else            //不开启DHCP，使用静态IP
  IP4_ADDR(&ipaddr, 192, 168, 0, 30);      //设置IP地址
  IP4_ADDR(&netmask, 255, 255, 255, 0);   //设置子网掩码
  IP4_ADDR(&gw, 192, 168, 0, 1);          //设置网关
#endif

  ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //配置MAC地址

  //注册网卡函数   ethernetif_init函数，需要自己实现，用于配置netif相关字段，以及初始化底层硬件。
  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

  //将注册网卡函数注册的网卡设置为默认网卡
  netif_set_default(&netif);


#if LWIP_DHCP           //如果开启了DHCP复位
  dhcp_start(&netif);   //开启DHCP
#endif

  //打开网卡
  netif_set_up(&netif);
}

//接收数据函数
void LwIP_Pkt_Handle(void)
{
  //从网络缓冲区中读取接收到的数据包并将其发送给LWIP处理 
  ethernetif_input(&netif);
}
