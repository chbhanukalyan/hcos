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
 * This contains the Third stage of the bootloader, and essentially does
 * all important stuff like enabling paging, setting up IDTs etc.
 */

#include <stddefs.h>
#include <interrupts.h>

void enable_paging(void);
void hcos_entry(void) __attribute__ ((noreturn));

int data_var = 0xDEADBEEF;
static int bss_var;

void hcos_entry(void)
{
	char welcome_msg[] = "Welcome to HolyCow OS - Third Stage!!\n";

	clearscreen();

	printf(welcome_msg);
	int ptr;

	printf("Code Value = %p\n", &hcos_entry);
	printf("Stack Value = %p\n", &ptr);
	printf("Data Value = %p\n", &data_var);
	printf("BSS Value = %p\n", &bss_var);
	printf("Data actual Value = %x\n", data_var);

	/* Do stuff here */
	enable_paging();

	setup_idt();

	asm volatile("movl $0xB1DBADBD, %eax");


	/* OK halt the system here */
	while (1);
}


