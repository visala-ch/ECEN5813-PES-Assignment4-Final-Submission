/********************************************
 * Title		: log.h
 * Description	:Abstraction file for printf used for DEBUG and RUN
 * 				Log(....) replaces printf() function
 *
 * Author		: Visalakshmi Chemudupati
 *
 *
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#ifdef DEBUG
#  define LOG PRINTF //printf
#else
#  define LOG(...)
#endif

#endif /* LOG_H_ */

