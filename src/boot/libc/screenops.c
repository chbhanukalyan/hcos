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
 * This file contains the various generic function definitions
 */

#include "stddefs.h"

#define	VID_MEM_ADDR	((void*)0x000B8000)
#define	VID_MEM_LEN		0xF00

int loc = 0;

void clearscreen(void)
{
	int i;
	char *ptr = VID_MEM_ADDR;
	for (i = 0; i < VID_MEM_LEN; i += 2) {
		/* Zero out the character */
		*(ptr + i) = 0x0;
		/* Print a sane value for screen color though */
		*(ptr + i + 1) = 0x0F;
	}
	loc = 0;
}

#define		SCREEN_WIDTH	80
#define		SCREEN_HEIGHT	24
#define		LINE_WIDTH		(SCREEN_WIDTH)

void print_msg(const char *msg)
{
	int i, j;
	int len = strlen(msg);
	char *ptr = VID_MEM_ADDR + 2*loc;

	for (i = 0, j = 0; j < len; j++) {
		switch (msg[j]) {
			case '\n':
				i = ((i + LINE_WIDTH) / LINE_WIDTH) * LINE_WIDTH;
				break;
			default:
				*(ptr + i) = msg[j];
				i += 2;
				break;
		}
	}

	loc += i;
}

