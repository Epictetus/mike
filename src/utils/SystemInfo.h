#ifndef _MIKE_SYSTEM_INFO_H_
#define _MIKE_SYSTEM_INFO_H_

#include <stdlib.h>

// Mike's settings
#define MIKE_VERSION "0.0.1"

// Detecting CPU architecture
#if defined(__amd64__)
#define CPU_ARCH "x86_64"
#elif defined(__i386__)
#define CPU_ARCH "i386"
#elif defined(__i486__)
#define CPU_ARCH "i486"
#elif defined(__i486__)
#define CPU_ARCH "i586"
#elif defined(__i486__)
#define CPU_ARCH "i686"
#elif defined(__ia64__)
#define CPU_ARCH "x64"
#elif defined(__powerpc__)
#define CPU_ARCH "powerpc"
#else
#define CPU_ARCH "unknown"
#endif

// Detecting operating system
#if defined(__WIN32__) || defined(__MINGW32__) || defined(__CYGWIN__)
#define OS_TYPE "Windows"
#elif defined(__linux__)
#define OS_TYPE "Linux"
#elif defined(__APPLE__)
#define OS_TYPE "Apple"
#endif

#endif /* _MIKE_SYSTEM_INFO_H_ */
