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
 * This file contains the various printf function definitions
 */

#include "stddefs.h"

static int int_to_str_hex(unsigned int *pval, char *s)
{
	unsigned int v = *pval;

	int i;
	s[0] = '0';
	s[1] = 'x';
	for (i = 0; i < 8; i++) {
		int n = (v & 0xF0000000) >> 28;
		s[i+2] = n + ((n < 10) ? '0' : 'A' - 10);
		v <<= 4;
	}
	return i + 2;
}

static int int_to_str_base(unsigned int *pval, char *s, int base)
{
	unsigned int v = *pval;
	int i, digits = 0;

	while (v) {
		v /= base;
		digits++;
	}

	v = *pval;
	for (i = 0; i < digits; i++) {
		s[digits - i - 1] = '0' + v % base;
		v /= base;
	}
	return digits;
}

#define	TMP_BUF_SZ	256
int printf(const char *s, ...)
{
	int i, j;
	char b[TMP_BUF_SZ];

	/* Access other variables from stack */
	unsigned int *stackptr = (void*)&s;

	for (i = 0, j = 0; s[i];) {
		if (s[i] == '%') {
			i++;
			switch (s[i]) {
				/* TODO make sure we dont overflow the temp buffer */
				case 'x':
				case 'p':
					j += int_to_str_hex(++stackptr, &b[j]);
					i++;
					break;

				case 'd':
					j += int_to_str_base(++stackptr, &b[j], 10);
					i++;
					break;

				case 's': {
					const char **sp = (const char**)++stackptr;
					strncpy(&b[j], *sp, TMP_BUF_SZ - j);
					j += strlen(*sp);
					i++;
					break;
				}

				case '%':
					b[j++] = '%';
					break;

				default:
					break;
			}
		} else {
			b[j++] = s[i++];
		}
	}
	b[j] = '\0';

	print_msg(b);

	return 0;
}

