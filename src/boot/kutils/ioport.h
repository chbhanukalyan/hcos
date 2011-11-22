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
 * This file contains the various Programmable IO helper functions
 */

#ifndef __KUTILS_IOPORT_H__
#define __KUTILS_IOPORT_H__

#include <stddefs.h>

static inline u8 inb(u16 ioport)
{
	u8 val;
	asm volatile("inb %1, %0"
			:"=a"(val):"aN"(ioport):"eax");
	return val;
}

static inline void outb(u16 ioport, u8 val)
{
	asm volatile("outb %1, %0"
			::"a"(val),"aN"(ioport):"eax");
}


#endif /* __KUTILS_IOPORT_H__ */

