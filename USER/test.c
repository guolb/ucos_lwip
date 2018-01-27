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


err_t ethernetif_init(struct netif *netif); //�����ļ��ں�������
err_t ethernetif_input(struct netif *netif);//�����ļ��ں�������

u8_t MACaddr[6]={0,0,0,0,0,1};              //MAC��ַ������Ψһ��

struct netif netif;                          //����һ��ȫ�ֵ�����ӿڣ�ע����������Ҫ�õ�  



void LWIP_Init(void)
{
  struct ip_addr ipaddr;     //����IP��ַ�ṹ��
  struct ip_addr netmask;    //������������ṹ��
  struct ip_addr gw;         //�������ؽṹ��

  mem_init();  //��ʼ����̬�ڴ��

  memp_init(); //��ʼ���ڴ��

  tcpip_init(NULL,NULL); //��ʼ��LWIP�ں�
	
#if LWIP_DHCP     //�������DHCP���Զ���ȡIP
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#else            //������DHCP��ʹ�þ�̬IP
  IP4_ADDR(&ipaddr, 192, 168, 0, 30);      //����IP��ַ
  IP4_ADDR(&netmask, 255, 255, 255, 0);   //������������
  IP4_ADDR(&gw, 192, 168, 0, 1);          //��������
#endif

  ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //����MAC��ַ

  //ע����������   ethernetif_init��������Ҫ�Լ�ʵ�֣���������netif����ֶΣ��Լ���ʼ���ײ�Ӳ����
  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

  //��ע����������ע�����������ΪĬ������
  netif_set_default(&netif);


#if LWIP_DHCP           //���������DHCP��λ
  dhcp_start(&netif);   //����DHCP
#endif

  //������
  netif_set_up(&netif);
}

//�������ݺ���
void LwIP_Pkt_Handle(void)
{
  //�����绺�����ж�ȡ���յ������ݰ������䷢�͸�LWIP���� 
  ethernetif_input(&netif);
}
