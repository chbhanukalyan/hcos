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
 * This file contains the various interrupt related macros & info
 */

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

/* 
 * List of Interrupts & vector info
 * Vector Exception/Interrupt Mnemonic Cause
 * 0 Divide-by-Zero-Error #DE DIV, IDIV, AAM instructions
 * 1 Debug #DB Instruction accesses and data accesses
 * 2 Non-Maskable-Interrupt #NMI External NMI signal
 * 3 Breakpoint #BP INT3 instruction
 * 4 Overflow #OF INTO instruction
 * 5 Bound-Range #BR BOUND instruction
 * 6 Invalid-Opcode #UD Invalid instructions
 * 7 Device-Not-Available #NM x87 instructions
 * 8 Double-Fault #DF Exception during the handling of another
 * exception or interrupt
 * 9 Coprocessor-Segment-Overrun — Unsupported (Reserved)
 * 10 Invalid-TSS #TS Task-state segment access and task switch
 * 11 Segment-Not-Present #NP Segment register loads
 * 12 Stack #SS SS register loads and stack references
 * 13 General-Protection #GP Memory accesses and protection checks
 * 14 Page-Fault #PF Memory accesses when paging enabled
 * 15 Reserved —
 * 16 x87 Floating-Point Exception-
 * Pending #MF x87 floating-point instructions
 * 17 Alignment-Check #AC Misaligned memory accesses
 * 18 Machine-Check #MC Model specific
 * 19 SIMD Floating-Point #XF SSE floating-point instructions
 * 20—29 Reserved —
 * 30 Security Exception #SX Security-sensitive event in host
 * 31 Reserved —
 * 0—255 External Interrupts (Maskable) #INTR External interrupts
 * 0—255 Software Interrupts — INTn instruction
 */
#define	TOTAL_X86_INTERRUPT_VECTORS	256

/* Interrupt gate Segment Descriptor
 *
 * BITS
 * Lower
 * 0-15  - Target Code Segment Offset (Lower 16 bits)
 * 16-31 - Target Code Segment Selector
 * Higher
 * 0-7   - reserved
 * 8-11  - Type
 * 12    - 0
 * 13-14 - DPL (Descriptor Privilege Level)
 * 15    - P
 * 16-31 - Target Code Segment Offset (Higher 16 bits)
 *
 * Gate Type descrtiptions
(Bits 11–8) Description
0 0000 Reserved (Illegal)
1 0001 Available 16-bit TSS
2 0010 LDT
3 0011 Busy 16-bit TSS
4 0100 16-bit Call Gate
5 0101 Task Gate
6 0110 16-bit Interrupt Gate
7 0111 16-bit Trap Gate
8 1000 Reserved (Illegal)
9 1001 Available 32-bit TSS
A 1010 Reserved (Illegal)
B 1011 Busy 32-bit TSS
C 1100 32-bit Call Gate
D 1101 Reserved (Illegal)
E 1110 32-bit Interrupt Gate
F 1111 32-bit Trap Gate
 * 
 */
#define	IDT_ENT0_CODE_SEG_SEL	(0x8 << 16)
#define	IDT_ENT0_CODE_PTR_LO(x)	((x) & 0xFFFF)
#define	IDT_ENT1_CODE_PTR_HI(x)	((x) & 0xFFFF0000)
#define	IDT_ENT1_DPL(x)			((x) << 13)
#define	IDT_ENT1_TYPE_INTGATE	(0xE << 8)
#define	IDT_ENT1_PRESENT		(0x1 << 15)


/* Page fault codes
 *
 * The information reported by the page-fault error code includes:
 * • P—Bit 0. If this bit is cleared to 0, the page fault was caused by a not-present page. If this bit is set
 * to 1, the page fault was caused by a page-protection violation.
 * • R/W—Bit 1. If this bit is cleared to 0, the access that caused the page fault is a memory read. If this
 * bit is set to 1, the memory access that caused the page fault was a write. This bit does not
 * necessarily indicate the cause of the page fault was a read or write violation.
 * • U/S—Bit 2. If this bit is cleared to 0, an access in supervisor mode (CPL=0, 1, or 2) caused the
 * page fault. If this bit is set to 1, an access in user mode (CPL=3) caused the page fault. This bit does
 * not necessarily indicate the cause of the page fault was a privilege violation.
 * • RSV—Bit 3. If this bit is set to 1, the page fault is a result of the processor reading a 1 from a
 * reserved field within a page-translation-table entry. This type of page fault occurs only when
 * CR4.PSE=1 or CR4.PAE=1. If this bit is cleared to 0, the page fault was not caused by the
 * processor reading a 1 from a reserved field.
 * • I/D—Bit 4. If this bit is set to 1, it indicates that the access that caused the page fault was an
 * instruction fetch. Otherwise, this bit is cleared to 0. This bit is only defined if no-execute feature is
 * enabled (EFER.NXE=1 && CR4.PAE=1).
 */

extern void setup_idt(void);

#endif /* __INTERRUPTS_H__ */

