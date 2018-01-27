#ifndef __CC_H__
#define __CC_H__

#include <stdio.h> //ʹ��printf�����������stdio.h
#include "includes.h"  //ʹ��UCOS Ҫ��Ӵ�ͷ�ļ���

#define BYTE_ORDER LITTLE_ENDIAN   //С��ģʽ
#define LWIP_PROVIDE_ERRNO 1       //ʹ��lwip/arch.hͷ�ļ���������Щ����

//LwIPʹ�õ��������Ͷ���D�Du8_t, s8_t, u16_t��s16_t��u32_t��s32_t��mem_ptr_t��
typedef unsigned   char    u8_t;
typedef signed     char    s8_t;
typedef unsigned   short   u16_t;
typedef signed     short   s16_t;
typedef unsigned   long    u32_t;
typedef signed     long    s32_t;
typedef u32_t mem_ptr_t;

//���������ص�LwIP�ṹ���
#if defined (__ICCARM__)

#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT 
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_USE_INCLUDES

#elif defined (__CC_ARM)

#define PACK_STRUCT_BEGIN __packed
#define PACK_STRUCT_STRUCT 
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

#elif defined (__GNUC__)

#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT __attribute__ ((__packed__))
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

#elif defined (__TASKING__)

#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

#endif


//  ��ƽ̨��صĵ����䣬ʹ��printf����
#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do { if(!(x)) while(1); } while(0)
#endif

#ifndef LWIP_PLATFORM_DIAG
#define LWIP_PLATFORM_DIAG(x) do {printf x;} while(0)
#endif

#if OS_CRITICAL_METHOD == 3  
#define SYS_ARCH_DECL_PROTECT(lev)	u32_t lev
#define SYS_ARCH_PROTECT(lev)		    lev = OS_CPU_SR_Save() 	//UCOS II�н����ٽ���,���ж�
#define SYS_ARCH_UNPROTECT(lev)		  OS_CPU_SR_Restore(lev)	//UCOS II���˳�A�ٽ��������ж� 
#endif

#endif /* __CC_H__ */
