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
#include <fixeddefs.h>


#define	PAGE_DIR_SZ			PAGE_SIZE
#define	PAGE_DIR_BITSHIFT	22
#define	PAGE_DIR_OFFSET(p)	((p) >> PAGE_DIR_BITSHIFT)
#define	PAGE_TBL_SZ			PAGE_SIZE
#define	PAGE_TBL_BITSHIFT	12
#define	PAGE_TBL_OFFSET(p)	(((p) >> PAGE_TBL_BITSHIFT) & 0x3FF)

#define	PDE_ADDR	0x00C00000

/* 
 * Page Directory Entry Format
 *
 * From IA32 Manual
 *
 * 0 (P) Present; must be 1 to reference a page table
 * 1 (R/W) Read/write; if 0, writes may not be allowed to the 4-MByte region controlled by
 * this entry (depends on CPL and CR0.WP; see Section 4.6)
 * 2 (U/S) User/supervisor; if 0, accesses with CPL=3 are not allowed to the 4-MByte region
 * controlled by this entry (see Section 4.6)
 * 3 (PWT) Page-level write-through; indirectly determines the memory type used to access
 * the page table referenced by this entry (see Section 4.9)
 * 4 (PCD) Page-level cache disable; indirectly determines the memory type used to access
 * the page table referenced by this entry (see Section 4.9)
 * 5 (A) Accessed; indicates whether this entry has been used for linear-address
 * translation (see Section 4.8)
 * 6 Ignored
 * 7 (PS) If CR4.PSE = 1, must be 0 (otherwise, this entry maps a 4-MByte page; see
 * Table 4-4); otherwise, ignored
 * 11:8 Ignored
 * 31:12 Physical address of 4-KByte aligned page table referenced by this entry
 *
 */
#define    PDE_VAL_PRESENT     (0x1 <<  0)
#define    PDE_VAL_RW          (0x1 <<  1)
#define    PDE_VAL_USERSUPER   (0x1 <<  2)
#define    PDE_VAL_WRTTHRGH    (0x1 <<  3)
#define    PDE_VAL_CACHDISBL   (0x1 <<  4)
#define    PDE_VAL_ACCESSED    (0x1 <<  5)
#define    PDE_VAL_4MB_PAGE    (0x1 <<  7)

typedef struct {
	u32 pde[1024];
} PageDir;



/*
 * Format of a 32-Bit Page-Table Entry that Maps a 4-KByte Page
 *
 * From IA32 Manual
 *
 * 0 (P) Present; must be 1 to map a 4-KByte page
 * 1 (R/W) Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by
 * this entry (depends on CPL and CR0.WP; see Section 4.6)
 * 2 (U/S) User/supervisor; if 0, accesses with CPL=3 are not allowed to the 4-KByte page
 * referenced by this entry (see Section 4.6)
 * 3 (PWT) Page-level write-through; indirectly determines the memory type used to access
 * the 4-KByte page referenced by this entry (see Section 4.9)
 * 4 (PCD) Page-level cache disable; indirectly determines the memory type used to access
 * the 4-KByte page referenced by this entry (see Section 4.9)
 * 5 (A) Accessed; indicates whether software has accessed the 4-KByte page referenced
 * by this entry (see Section 4.8)
 * 6 (D) Dirty; indicates whether software has written to the 4-KByte page referenced by
 * this entry (see Section 4.8)
 * 7 (PAT) If the PAT is supported, indirectly determines the memory type used to access the
 * 4-KByte page referenced by this entry (see Section 4.9.2); otherwise, reserved
 * (must be 0)1
 * 8 (G) Global; if CR4.PGE = 1, determines whether the translation is global (see Section
 * 4.10); ignored otherwise
 * 11:9 Ignored
 * 31:12 Physical address of the 4-KByte page referenced by this entry
 */

#define PTE_VAL_PRESENT        (0x1 <<  0)
#define PTE_VAL_READWRITE      (0x1 <<  1)
#define PTE_VAL_USERSUPER      (0x1 <<  2)
#define PTE_VAL_PAGEWRITETHRGH (0x1 <<  3)
#define PTE_VAL_CACHEDISABLE   (0x1 <<  4)
#define PTE_VAL_ACCESSED       (0x1 <<  5)
#define PTE_VAL_DIRTY          (0x1 <<  6)
#define PTE_VAL_PAT            (0x1 <<  7)
#define PTE_VAL_GLOBAL         (0x1 <<  8)

typedef struct {
	u32 pte[1024];
} PageTable;

inline void set_pde4k(PageDir *pd, u32 actualaddr, u32 ptaddr)
{
	pd->pde[PAGE_DIR_OFFSET(actualaddr)] = ptaddr | PDE_VAL_PRESENT | PDE_VAL_RW;
}

inline void set_pde4m(PageDir *pd, u32 actualaddr, u32 physaddr)
{
	pd->pde[PAGE_DIR_OFFSET(actualaddr)] = physaddr | PDE_VAL_PRESENT | PDE_VAL_RW | PDE_VAL_4MB_PAGE;
}

inline void set_pte(PageTable *pt, u32 ptaddr)
{
	pt->pte[PAGE_TBL_OFFSET(ptaddr)] = ptaddr | PTE_VAL_PRESENT | PTE_VAL_READWRITE | PTE_VAL_GLOBAL;
}

/* Layout map
 *
 * 0x00A00000 -> code
 * 0x00B00000 -> Data
 * 0x00B80000 -> BSS
 * 0x02000000 -> Stack
 *
 * Use 4MB Pages
 */
void setup_pagetables(PageDir *pd)
{
	/* Text Segment */
	PageTable *pt = (void*)pd + PAGE_DIR_SZ;

	/* Have the first gig of RAM in the 3-4GB of the virtual address space */
	u32 i;
	for (i = 0; i < 0x100; i++) {
		set_pde4m(pd, (i << PAGE_DIR_BITSHIFT) + HCOS_KERNEL_ADDRSPLIT, (i << PAGE_DIR_BITSHIFT));
		set_pde4m(pd, (i << PAGE_DIR_BITSHIFT), (i << PAGE_DIR_BITSHIFT));
	}

	set_pde4k(pd, THIRD_STAGE_LOAD_ADDRESS, (u32)pt);

	set_pte(pt, THIRD_STAGE_LOAD_ADDRESS);
	set_pte(pt, THIRD_STAGE_DATA_ADDRESS);
	set_pte(pt, THIRD_STAGE_BSS_ADDRESS);

	/* Stack Segment - grows down */
	pt++;
	set_pde4k(pd, THIRD_STAGE_STACK_ADDRESS-PAGE_SIZE, (u32)pt);
	set_pte(pt, THIRD_STAGE_STACK_ADDRESS - PAGE_SIZE);
}

void enable_paging(void)
{
//	printf("Enabling Paging...\n");

	PageDir *pd = (PageDir*)PDE_ADDR;
	memset(pd, 0, PAGE_SIZE);

	setup_pagetables(pd);
	
	/* SET the PSE Bit (bit 4) to enable 4MB Pages */
	asm("movl %%cr4, %%eax\n\t"
			"orl $0x00000010, %%eax \n\t"
			"movl %%eax, %%cr4 \n\t"
			:
			: "r" (pd)
			:"eax");


	/* Load Page DIR address */
	asm("movl %%cr3, %%eax\n\t"
			"andl $0x00000FFF, %%eax \n\t"
			"orl %0, %%eax \n\t"
			"movl %%eax, %%cr3 \n\t"
			:
			: "r" (pd)
			:"eax");

//	printf("PDptr = %p", pd);


	/* Set Bit 31 of CR0 to enable Paging */
	asm volatile("movl %%cr0, %%eax\n\t"
			"orl $0x80000000, %%eax \n\t"
			"movl %%eax, %%cr0 \n\t"
			:
			:
			:"eax");

	printf("Virtual PDptr = %p", pd);
	printf("Virtual PDptr = %p", (void*)(((u32)pd) & HCOS_KERNEL_ADDRSPLIT));

	return;
}

