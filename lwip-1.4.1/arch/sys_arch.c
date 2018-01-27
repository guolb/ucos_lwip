#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "arch/sys_arch.h"
#include "mymalloc.h"

OS_STK  TCPIP_THREAD_TASK_STK[TCPIP_THREAD_STACKSIZE];//�ں������ջ

//����һ����Ϣ����
//*mbox:��Ϣ����
//size:�����С
//����ֵ:ERR_OK,�����ɹ�
//         ����,����ʧ��
err_t sys_mbox_new( sys_mbox_t *mbox, int size)
{
	(*mbox)=mymalloc(sizeof(LWip_MBOX));	//Ϊ��Ϣ���������ڴ�
	memset((*mbox),0,sizeof(LWip_MBOX));  //���mbox���ڴ�
	if(*mbox)//�ڴ����ɹ�
	{
		if(size>MBOX_MAX_SIZE)size=MBOX_MAX_SIZE;		             //��Ϣ�����������MAX_QUEUE_ENTRIES��Ϣ��Ŀ 
 		(*mbox)->pst=OSQCreate(&((*mbox)->pvQEntries[0]),size);  //ʹ��UCOS����һ����Ϣ����
		if((*mbox)->pst!=NULL)return ERR_OK;                     //����ERR_OK,��ʾ��Ϣ���д����ɹ� ERR_OK=0
		else
		{ 
			myfree((*mbox));
			return ERR_MEM;  		//��Ϣ���д�������
		}
	}else return ERR_MEM; 			//��Ϣ���д������� 
} 

//�ͷŲ�ɾ��һ����Ϣ����
//*mbox:Ҫɾ������Ϣ����
void sys_mbox_free(sys_mbox_t * mbox)
{
	u8_t ucErr;
	sys_mbox_t m_box=*mbox;   
	OSQDel(m_box->pst,OS_DEL_ALWAYS,&ucErr);
	(*mbox)=myfree(*mbox);
}

//����Ϣ�����з���һ����Ϣ(��������ֱ�����ͳɹ�)
//*mbox:��Ϣ����
//*msg:Ҫ���͵���Ϣ
void sys_mbox_post(sys_mbox_t *mbox,void *msg)
{     
	while(OSQPost((*mbox)->pst,msg)!=OS_ERR_NONE);//��ѭ���ȴ���Ϣ���ͳɹ� 
}

//��һ����Ϣ���䷢����Ϣ(����һ�Σ��ɹ���񶼲���������)
//*mbox:��Ϣ����
//*msg:Ҫ���͵���Ϣ
//����ֵ:ERR_OK,����OK
// 	     ERR_MEM,����ʧ��
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{ 
	if((OSQPost((*mbox)->pst, msg))!=OS_ERR_NONE)return ERR_MEM;
	return ERR_OK;
}
//�ȴ������е���Ϣ
//*mbox:��Ϣ����
//*msg:��Ϣ
//timeout:��ʱʱ�䣬���timeoutΪ0�Ļ�,��һֱ�ȴ�
//����ֵ:��timeout��Ϊ0ʱ����ɹ��Ļ��ͷ��صȴ���ʱ�䣬
//		ʧ�ܵĻ��ͷ��س�ʱSYS_ARCH_TIMEOUT
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{ 
	u8_t ucErr;
	u32_t ucos_timeout,timeout_new;
	void *temp;
	sys_mbox_t m_box=*mbox;
	if(timeout!=0)
	{
		ucos_timeout=(timeout*OS_TICKS_PER_SEC)/1000; //ת��Ϊ������,��ΪUCOS��ʱʹ�õ��ǽ�����,��LWIP����ms
		if(ucos_timeout<1)ucos_timeout=1;//����1������
	}else ucos_timeout = 0; 
	timeout = OSTimeGet(); //��ȡϵͳʱ�� 
	temp=OSQPend(m_box->pst,(u16_t)ucos_timeout,&ucErr); //������Ϣ����,�ȴ�ʱ��Ϊucos_timeout
	if(msg!=NULL)
	{	
		*msg=temp;									    
	}    
	if(ucErr==OS_ERR_TIMEOUT)timeout=SYS_ARCH_TIMEOUT;  //����ʱ
	else
	{ 
		timeout_new=OSTimeGet();
		if (timeout_new>timeout) timeout_new = timeout_new - timeout;//���������Ϣ��ʹ�õ�ʱ��
		else timeout_new = 0xffffffff - timeout + timeout_new; 
		timeout=timeout_new*1000/OS_TICKS_PER_SEC + 1; 
	}
	return timeout; 
}
//���Ի�ȡ��Ϣ������������
//*mbox:��Ϣ����
//*msg:��Ϣ
//����ֵ:�ȴ���Ϣ���õ�ʱ��/SYS_ARCH_TIMEOUT
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	return sys_arch_mbox_fetch(mbox,msg,1);//���Ի�ȡһ����Ϣ
}

//���һ����Ϣ�����Ƿ���Ч
//*mbox:��Ϣ����
//����ֵ:1,��Ч.
//      0,��Ч
int sys_mbox_valid(sys_mbox_t *mbox)
{  
	sys_mbox_t m_box=*mbox;
	u8_t ucErr;
	int ret;
	OS_Q_DATA q_data;
	memset(&q_data,0,sizeof(OS_Q_DATA));
	ucErr=OSQQuery (m_box->pst,&q_data);
	ret=(ucErr<2&&(q_data.OSNMsgs<q_data.OSQSize))?1:0;
	return ret;
} 

//����һ����Ϣ����Ϊ��Ч
//*mbox:��Ϣ����
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
	*mbox=(void *)0;
}

//����һ���ź���
//*sem:�������ź���
//count:�ź���ֵ
//����ֵ:ERR_OK,����OK
// 	     ERR_MEM,����ʧ��
err_t sys_sem_new(sys_sem_t * sem, u8_t count)
{  
	*sem=OSSemCreate((u16_t)count);
	if(*sem==NULL)return ERR_MEM; 
	return ERR_OK;
} 

//�ȴ�һ���ź���
//*sem:Ҫ�ȴ����ź���
//timeout:��ʱʱ��
//����ֵ:��timeout��Ϊ0ʱ����ɹ��Ļ��ͷ��صȴ���ʱ�䣬
//		ʧ�ܵĻ��ͷ��س�ʱSYS_ARCH_TIMEOUT
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{ 
	u8_t ucErr;
	u32_t ucos_timeout, timeout_new; 
	if(	timeout!=0) 
	{
		ucos_timeout = (timeout * OS_TICKS_PER_SEC) / 1000;//ת��Ϊ������,��ΪUCOS��ʱʹ�õ��ǽ�����,��LWIP����ms
		if(ucos_timeout < 1)
		ucos_timeout = 1;
	}else ucos_timeout = 0; 
	timeout = OSTimeGet();  
	OSSemPend (*sem,(u16_t)ucos_timeout, (u8_t *)&ucErr);
 	if(ucErr == OS_ERR_TIMEOUT)timeout=SYS_ARCH_TIMEOUT;//����ʱ	
	else
	{     
 		timeout_new = OSTimeGet(); 
		if (timeout_new>=timeout) timeout_new = timeout_new - timeout;
		else timeout_new = 0xffffffff - timeout + timeout_new;
 		timeout = (timeout_new*1000/OS_TICKS_PER_SEC + 1);//���������Ϣ��ʹ�õ�ʱ��(ms)
	}
	return timeout;
}

//����һ���ź���
//sem:�ź���ָ��
void sys_sem_signal(sys_sem_t *sem)
{
	OSSemPost(*sem);//����UCOS��OSSemPost����
}

//�ͷŲ�ɾ��һ���ź���
//sem:�ź���ָ��
void sys_sem_free(sys_sem_t *sem)
{
	u8_t ucErr;//����һ����������Ŵ������
	OSSemDel(*sem,OS_DEL_ALWAYS,&ucErr );//����UCOS��OSSemDel������ɾ��һ���ź���
	if(ucErr!=OS_ERR_NONE)LWIP_ASSERT("OSSemDel ",ucErr==OS_ERR_NONE);
	*sem = (void *)0;
} 

//��ѯһ���ź�����״̬,��Ч����Ч
//sem:�ź���ָ��
//����ֵ:1,��Ч.
//      0,��Ч
int sys_sem_valid(sys_sem_t *sem)
{
 	OS_SEM_DATA  sem_data;                                       //����һ��UCOS�ź����ṹ
	return (OSSemQuery (*sem,&sem_data) == OS_ERR_NONE )? 1:0;   //����UCOS���� OSSemQuery����ѯ�ź���״̬ 
} 

//����һ���ź�����Ч
//sem:�ź���ָ��
void sys_sem_set_invalid(sys_sem_t *sem)
{
	*sem=(void *)0; //ָ���ָ��
} 

//arch��ʼ��
void sys_init(void)
{ 
    //����,�����ڸú���,�����κ�����
} 


//����һ���½���
//*name:��������
//thred:����������
//*arg:�����������Ĳ���
//stacksize:��������Ķ�ջ��С
//prio:������������ȼ�
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
	OS_CPU_SR cpu_sr;
	if(strcmp(name,TCPIP_THREAD_NAME)==0)//����TCP IP�ں�����
	{
		OS_ENTER_CRITICAL();  //�����ٽ��� 
		OSTaskCreate(thread,arg,(OS_STK*)&TCPIP_THREAD_TASK_STK[stacksize-1],prio);//����TCP IP�ں����� 
		OS_EXIT_CRITICAL();  //�˳��ٽ���
	} 
	return 0;
} 

//��ȡϵͳʱ��
//����ֵ:��ǰϵͳʱ��(��λ:����)
u32_t sys_now(void)
{
	u32_t ucos_time, lwip_time;
	ucos_time=OSTimeGet();	                      //��ȡ��ǰϵͳʱ�� �õ�����UCSO�Ľ�����
	lwip_time=(ucos_time*1000/OS_TICKS_PER_SEC+1);//��������ת��ΪLWIP��ʱ��MS
	return lwip_time; 		                      //����lwip_time;
}
