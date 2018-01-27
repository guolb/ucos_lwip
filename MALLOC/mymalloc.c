#include "stm32f10x_it.h"
#include "mymalloc.h"

#define   MEM_BLOCK_NUM   200         //�ڴ������
#define   MEM_BLOCK_SIZE  32          //�ڴ���С
 
uint8_t   MEM_BUFF[MEM_BLOCK_NUM][MEM_BLOCK_SIZE]; //�����ڴ��
MEM_BCT   MEM_BCT_TAB[MEM_BLOCK_NUM];              //�ڴ������һ������

//��ʼ���ڴ���������
void mymen_Init(void)                 
{
  uint32_t i;
	for(i=0;i<MEM_BLOCK_NUM;i++)         //���������ڴ�����
	{
		MEM_BCT_TAB[i].mem_state=0;        //�ڴ��״̬����=0����ʾ����
		MEM_BCT_TAB[i].num=0;              //ռ�������ڴ��Ϊ0
	}
}
 void *mymalloc(uint32_t size)
{
	uint32_t num;                            //num�����Ҫ������ڴ����Ŀ
	uint32_t i;                              //forѭ��ʹ��
	uint32_t start_N0=MEM_BLOCK_NUM;         //�ҵ��Ŀ��е��ڴ�����
	uint32_t start_flag=0;                   //�ҵ��������ڴ�������
	
	if((size%MEM_BLOCK_SIZE)!=0)          
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE)+1); //������Ҫ�����ڴ��
	}
	else
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE));   //������Ҫ�����ڴ��
	}
	
	for(i=0;i<MEM_BLOCK_NUM;i++)             //���������ڴ�����
	{
		if(MEM_BCT_TAB[i].mem_state==0)        //�鿴��ǰ�ڴ���Ƿ���ã����õĻ�if����
		{   //if��������ʾ��ǰ�ڴ濨����
			start_N0=i;                          //��¼�µ�ǰ���õ��ڴ����
			start_flag++;                        //�ҵ������ڴ�������+1              
		}
		else                                   //�鿴��ǰ�ڴ���Ƿ���ã������õĻ�else����
		{
			start_N0=MEM_BLOCK_NUM;              //�����ǰ���õ��ڴ���
			start_flag=0;                        //����ҵ������ڴ�������
		}
		if(start_flag==num)                    //�жϣ�һ���ҵ���������Ҫ��������ڴ�飬������forѭ��
		{
			break;
		}
	}
	
	if(start_flag!=num)                      //�ж�forѭ������ν�����
	{
		return (void*)0;                       //����ҵ������ڴ���������=num��Ҳ����û���㹻�������ڴ��ɹ������ˣ����ؿ�ָ��
  }
	else                                     //���start_flag==num��Ҳ����˵�ҵ����㹻�������ڴ��
	{
		for(i=(start_N0+1);i>(start_N0+1-num);i--)   //�����ҵ��������ڴ��
		{
			MEM_BCT_TAB[i-1].mem_state=1;              //����Щ�ڴ��״̬��1����ʾ��ռ����
		}
		MEM_BCT_TAB[start_N0+1-num].num=num;         //�������ڴ��ĵ�һ���ڴ���б�ǣ�����ռ���˼����ڴ��
		return (void *)(MEM_BUFF[start_N0+1-num]);   //���ص�һ���ڴ���ַ
	}
}

//�ͷ�������ڴ��
//���ؿ�ָ�룬��ֹ������������ڴ���ͷţ���Ҫ����Ź��ڴ���ָ��ָ��գ���ֹ����ʹ�ø�ָ��
void *myfree(void *p)
{
	uint32_t number;   
	uint32_t i;
	u8 *q = p;
	
	number=(uint32_t)((q-MEM_BUFF[0])/MEM_BLOCK_SIZE);    //����ָ����Ҫ�ͷŵ��ڴ���ָ���ַ��������ڴ�����ڴ���е�ƫ��λ�ã��Ա��ҵ��ڴ�������е�λ��
	for(i=number;i<(MEM_BCT_TAB[number].num+number);i++)  //�ҵ��ڴ���Ӧ�Ĺ���ģ��
	{
		MEM_BCT_TAB[i].mem_state=0;                         //��ģ��״̬=0����ʾ�ɹ�����
	} 
	MEM_BCT_TAB[number].num=0;                            //��ռ�������ڴ�ģ����Ϊ0
	
	return (void *)0;	                                    //���ؿ�ָ�룬
}
