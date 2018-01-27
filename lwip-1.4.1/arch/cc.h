#ifndef __CC_H__
#define __CC_H__

#include <stdio.h> //使用printf函数，需包含stdio.h
#include "includes.h"  //使用UCOS 要添加此头文件！

#define BYTE_ORDER LITTLE_ENDIAN   //小端模式
#define LWIP_PROVIDE_ERRNO 1       //使用lwip/arch.h头文件来定义这些编码

//LwIP使用的数据类型定义――u8_t, s8_t, u16_t，s16_t，u32_t，s32_t，mem_ptr_t。
typedef unsigned   char    u8_t;
typedef signed     char    s8_t;
typedef unsigned   short   u16_t;
typedef signed     short   s16_t;
typedef unsigned   long    u32_t;
typedef signed     long    s32_t;
typedef u32_t mem_ptr_t;

//与编译器相关的LwIP结构体宏
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


//  与平台相关的调试输，使用printf函数
#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do { if(!(x)) while(1); } while(0)
#endif

#ifndef LWIP_PLATFORM_DIAG
#define LWIP_PLATFORM_DIAG(x) do {printf x;} while(0)
#endif

#if OS_CRITICAL_METHOD == 3  
#define SYS_ARCH_DECL_PROTECT(lev)	u32_t lev
#define SYS_ARCH_PROTECT(lev)		    lev = OS_CPU_SR_Save() 	//UCOS II中进入临界区,关中断
#define SYS_ARCH_UNPROTECT(lev)		  OS_CPU_SR_Restore(lev)	//UCOS II中退出A临界区，开中断 
#endif

#endif /* __CC_H__ */
