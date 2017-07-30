/*
 * logger.h
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#ifndef LOGGER_H_
#define LOGGER_H_



#include <syslog.h>
#include <stdarg.h>

#define L_CON		1
#define L_LOG2		2
#define L_LOG3		4
#define L_LOG4		16
#define L_LOG5		32
#define L_LOG6      	64
#define L_LOG7		128
#define L_SYSLOG	256
static void Log( int tLevel , int moduleid , const char* filename , int linenumber , const char* tStr , ... ) {
	 char syslogprintbuf[ 512 ];
	 //if ( tLevel > debug_level )
		//return;

	 if ( ( tLevel & L_SYSLOG ) == L_SYSLOG ) {
			va_list v_args;
			va_start( v_args , tStr );
			vsprintf( syslogprintbuf , tStr , v_args );
			va_end( v_args );
			syslog ( LOG_INFO , " %s" , syslogprintbuf );
	 }

	 printf( "%s:%d:" , filename , linenumber );
	 va_list v_args;
     va_start( v_args , tStr );
	 vprintf( tStr , v_args );
     va_end( v_args );
  	 printf( "\n" );
}

#define PTRACE(l,o,...) \
Log( l , o , __FILE__ , __LINE__ , ##__VA_ARGS__)



#endif /* LOGGER_H_ */
