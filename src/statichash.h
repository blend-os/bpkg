/* statichash.h
 *
 * Copyright (c) 2015 by Lukas S. van der Heeden
 * All rights reserved.
 *
 * Modified by Erik Jakin on 6.7.2022.
 *
 * Modified by Sven Kovač on 8/13/2022.
 *
 * Use license: Modified from standard BSD license.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation, advertising
 * materials, Web server pages, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Lukas S. van der Heeden. The name "Lukas S. van der Heeden" may
 * not be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
#ifndef STATICHASH_H
#define STATICHASH_H


#ifdef __cplusplus
extern "C" {
#endif



/*
 *	Static HASH algorithm implementation.
 *
 *	C does not allow strings to be used in switch/case constructions. One logical solution is to use an if else if construction with string compares. But 
 *	that are very slow and in my application (an embedded system that parse XML data) this overhead was a problem.
 *
 *	I searched for a static HASH algorithm, but could not found an algorithm that could be used in a switch case construction. Basically because C expect
 *	a constant value behind a case, not a function call. On one site I found an almost static HASH algorithm, and the inspiration how to solve the issue.
 *
 *	The static HASH function defined here could only be used with character strings in its call. For example: HASH_S16(�test�) the value could not be a
 *	pointer to an array, or just a plain pointer. When the hash value from a generic C string is required, a separate function is available to calculate
 *	the HASH.
 */

#define HASH_INT_LEN(s)			((sizeof(s)/sizeof(s[0])) - 1)
#define HASH_INT_1(s,i,x)		(x*65599u+(unsigned char)s[(i)<HASH_INT_LEN(s)?HASH_INT_LEN(s)-1-(i):HASH_INT_LEN(s)])
#define HASH_INT_4(s,i,x)		HASH_INT_1(s,i,HASH_INT_1(s,i+1,HASH_INT_1(s,i+2,HASH_INT_1(s,i+3,x))))
#define HASH_INT_16(s,i,x)		HASH_INT_4(s,i,HASH_INT_4(s,i+4,HASH_INT_4(s,i+8,HASH_INT_4(s,i+12,x))))
#define HASH_INT_64(s,i,x)		HASH_INT_16(s,i,HASH_INT_16(s,i+16,HASH_INT_16(s,i+32,HASH_INT_16(s,i+48,x))))
#define HASH_INT_256(s,i,x)		HASH_INT_64(s,i,HASH_INT_64(s,i+64,HASH_INT_64(s,i+128,HASH_INT_64(s,i+192,x))))

#define assertStatic(e) \
	do { \
		enum { assert_static__ = 1/(e) }; \
	} while (0)

#define HASH_S256(s)			((unsigned int)(HASH_INT_256(s,0,0)^(HASH_INT_256(s,0,0)>>16)))	///< Hash value from string with a max length of 256 bytes.
#define HASH_S64(s)				((unsigned int)(HASH_INT_64(s,0,0)^(HASH_INT_64(s,0,0)>>16)))	///< Hash value from string with a max length of 64 bytes.
#define HASH_S16(s)				((unsigned int)(HASH_INT_16(s,0,0)^(HASH_INT_16(s,0,0)>>16)))	///< Hash value from string with a max length of 16 bytes.
#define HASH_S4(s)				((unsigned int)(HASH_INT_4(s,0,0)^(HASH_INT_4(s,0,0)>>16)))		///< Hash value from string with a max length of 4 bytes.

inline unsigned int hashString (const char *string) {
    unsigned int hash = 0, i;
	assertStatic(sizeof(unsigned int) == 4);
	assertStatic(sizeof(unsigned char) == 1);
	
    for(i = 0; string[i]; ++i)
        hash = 65599 * hash + string[i];
    return hash ^ (hash >> 16);
}


#ifdef __cplusplus
}
#endif

#endif
