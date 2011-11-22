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
 * This file contains the various functions required to handle Interrupts
 */

#include <stddefs.h>
#include <fixeddefs.h>
#include <interrupts.h>

/* TODO move this to a proper file */
extern void intr_hndlr(void);
asm(
	".text\n\t"
	".globl intr_hndlr\n\t"
	".type intr_hndlr, @function\n\t"
    ".align 4\n\t"
    "intr_hndlr:\n\t"
	"mov $0x1111FADD, %eax\n\t"
	"iret\n\t");


void setup_idt(void)
{
	int i;
	u32 *idt_base = (u32*)IDTR_BASE_ADDRESS;
	u8 idtr_segment_selector_loc[8];
	*(u16*)(idtr_segment_selector_loc+2) = (TOTAL_X86_INTERRUPT_VECTORS << 3);
	*(u32*)(idtr_segment_selector_loc+4) = IDTR_BASE_ADDRESS;

	u32 intrrupt_handler = (u32)intr_hndlr;

	for (i = 0; i < 2*TOTAL_X86_INTERRUPT_VECTORS; i += 2) {
		idt_base[i] = IDT_ENT0_CODE_SEG_SEL | IDT_ENT0_CODE_PTR_LO(intrrupt_handler);
		idt_base[i+1] = IDT_ENT1_DPL(0x3) | IDT_ENT1_TYPE_INTGATE | IDT_ENT1_PRESENT |
			IDT_ENT1_CODE_PTR_HI(intrrupt_handler);
	}

	asm volatile ("lidt (%0)"
			::"p"(idtr_segment_selector_loc+2):);
	asm volatile ("sti");
}

