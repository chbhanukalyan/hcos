/*
 * Copyright (C) 2011  Bhanu Chetlapalli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * =========================================================================
 *
 * This File is a part of the Holy Cow Operating System, which is written and
 * maintained by Bhanu Kalyan Chetlapalli <chbhanukalyan@gmail.com>.
 *
 * This file contains the various generic memory/string operations
 */

#include "stddefs.h"

int strlen(const char *str)
{
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

void *memset(void *s, int c, int n)
{
	int i;
	for (i = 0; i < n; i++)
		*(unsigned char*)(s+i) = (unsigned char)c;
	return s;
}

void *memcpy(void *d, const void *s, int n)
{
	int i;
	for (i = 0; i < n; i++)
		*(unsigned char*)(d+i) = *(const unsigned char*)(s+i);
	return d;
}

char* strncpy(char *d, const char *s, int n)
{
	int i;
	char *dst = d;
	for (i = 0; i < n; i++) {
		*d = *s;
		if (*s == '\0')
			break;
		s++, d++;
	}
	return dst;
}

