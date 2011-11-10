/*
 * Copyright (C) 2009  Bhanu Chetlapalli
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
 * This file contains the various functions require to enable paging
 */

#include <stddefs.h>

#define	PAGE_SIZE	0x00001000

#define	PDE_ADDR	0x00B00000

/* Page Directory */
typedef struct {
	unsigned int pde[1024];
} PageDir;

typedef struct {
	unsigned int pte[1024];
} PageTable;

void enable_paging(void)
{
	printf("Enabling Paging...\n");

	PageDir *pd = (PageDir*)PDE_ADDR;
	memset(pd, 0, PAGE_SIZE);

	printf("PDptr = %p", pd);

	return;


	/* Set Bit 31 of CR0 to enable Paging */
	asm volatile("movl %cr0, %eax\n\t"
			"orl $0x80000000, %eax \n\t"
			"movl %eax, %cr0 \n\t");
}

