#ifndef __DEBUGTOOL_H__
#define __DEBUGTOOL_H__


#include <rtthread.h>
#include <rtdevice.h>

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdio.h>

// #define DEBUG_TOOL
#define ERR_DEBUG_TOOL
// #define NEEDDED_DEBUG_TOOL


#ifdef DEBUG_TOOL
// #define LOG_DEBUG(format,...) rt_kprintf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(format,...) printf("LOG: "format"\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(format,...)
#endif

#ifdef ERR_DEBUG_TOOL
#define ERR_DEBUG(format,...) rt_kprintf("ERR File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define ERR_DEBUG(format,...)
#endif


#ifdef NEEDDED_DEBUG_TOOL
// #define NEEDDED_DEBUG(format,...) rt_kprintf("NEEDDED File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define NEEDDED_DEBUG(format,...) rt_kprintf("NEEDDED: "format"\n", ##__VA_ARGS__)
#else
#define NEEDDED_DEBUG(format,...)
#endif

#endif


