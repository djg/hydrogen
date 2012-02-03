// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4 -*- ///////////////
//
// File:	common.h
// Author:	Daniel Glastonbury
//
// Summary: Common definitions and constants
//
// © Copyright 2001 Daniel Glastonbury.  All rights reserved.
//
//----------------------------------------------------------------------------
// $Revision: 1.2 $    $Author: dan $    $Date: 2002/03/09 10:46:42 $
//----------------------------------------------------------------------------
// $Log: common.h,v $
// Revision 1.2  2002/03/09 10:46:42  dan
// - Added DBG_NEW macro.  This macro should be used instead of new.
// - Added ZeroStruct function.  Zeros memory for any struct passed as a parameter.
//
// Revision 1.1  2002/02/13 11:57:17  dan
// Initial Revision
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef __HYDROGEN_COMMON_H
#define __HYDROGEN_COMMON_H

#include <memory.h>
#include <string.h>

// Namespace
#define BEGIN_NAMESPACE(x)      namespace x {
#define END_NAMESPACE           };

#ifdef __linux__
#define PLATFORM_LINUX
#endif 

#ifdef WIN32
#define PLATFORM_WIN32
#endif

//////////////////////////////////////////////////////////////////////////////
// Kill Warnings under Windows
#ifdef PLATFORM_WIN32
#pragma warning ( disable : 4786 )
#endif

//////////////////////////////////////////////////////////////////////////////
// Common typedefs

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

//////////////////////////////////////////////////////////////////////////////
// Types for WIN32

#ifdef PLATFORM_WIN32

typedef char            int8;
typedef uchar           uint8;

typedef short           int16;
typedef ushort          uint16;

typedef int             int32;
typedef uint            uint32;

typedef float           float32;
typedef double          float64;

//////////////////////////////////////////////////////////////////////////////
// Types for Linux
#elif PLATFORM_LINUX

typedef char            int8;
typedef uchar           uint8;

typedef short           int16;
typedef ushort          uint16;

typedef int             int32;
typedef uint            uint32;

typedef float           float32;
typedef double          float64;

#else
#error Platform Unknown
#endif

/////////////////////////////////////////////////////////////////////////////
// No copying of class
#define NO_COPYING(class) \
    private: \
        class(const class&); \
        class& operator =(const class&)

//////////////////////////////////////////////////////////////////////////////
// NULL
#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////////////
// new/delete tracking
// #ifdef  _DEBUG
// #define  new new(__FILE__, __LINE__);
// #endif
#ifdef _DEBUG
#include "hydrogen/memdebugstats.h"
#else
#define DBG_NEW new
#endif

//////////////////////////////////////////////////////////////////////////////
// Assert
#ifndef _DEBUG
#define PREC(expr)
#define PRECM(expr, msg)
#else
void AssertFailure(const char* Expr, const char* File, uint32 Line);
void AssertFailure(const char* Expr, const char* Msg, const char* File, 
                   uint32 Line);
#define PREC(expr)        (void)((expr) || (AssertFailure(#expr, __FILE__,  __LINE__), 0))
#define PRECM(expr, msg)  (void)((expr) || (AssertFailure(#expr, msg, __FILE__, __LINE__), 0))
#endif

//////////////////////////////////////////////////////////////////////////////
// Log
#ifdef RELEASE
#define LOG(a)  ((void)0)
#else
void CommonLog(const char *fmt, ...);
#define LOG(a)  (CommonLog a)
#endif

//////////////////////////////////////////////////////////////////////////////
// Macros for managing arrays
#define ARRAY_SIZE(a)       (sizeof(a)/sizeof(*(a)))

//////////////////////////////////////////////////////////////////////////////
// Memory
inline void 
CopyMem(void* Dest, void* Src, uint32 NumBytes)
{
    ::memcpy(Dest, Src, NumBytes);
}

inline void
MoveMem(void* Dest, void* Src, uint32 NumBytes)
{
    ::memmove(Dest, Src, NumBytes);
}

inline void
SetMem(void* Dest, uint8 Value, uint32 NumBytes)
{
    ::memset(Dest, Value, NumBytes);
}

inline void
ZeroMem(void* Dest, uint32 NumBytes)
{
    ::memset(Dest, 0, NumBytes);
}

template <typename T>
inline void
ZeroStruct(T* Ptr)
{
    ::memset(Ptr, 0, sizeof(T));
}

#endif // __HYDROGEN_COMMON_H
