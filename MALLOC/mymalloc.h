#ifndef _MY_MALLOC_
#define _MY_MALLOC_

typedef struct           //����һ���ڴ�����ṹ��
{
	uint8_t  mem_state;  //��ǰ��Ӧ�ڴ濨��״̬  0 ����  1��ռ��
	uint8_t  num;        //����ռ�õ��ڴ������ 
}MEM_BCT;

void mymen_Init(void);
void *mymalloc(uint32_t size);
void *myfree(void *p);

#endif
