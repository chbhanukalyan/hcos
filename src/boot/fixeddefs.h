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
 * This file contains the various FIXED addresses macros etc
 */

#ifndef __FIXEDDEFS_H__
#define __FIXEDDEFS_H__

#include <types.h>

#define	THIRD_STAGE_LOAD_ADDRESS	0x00A00000
#define	THIRD_STAGE_DATA_ADDRESS	0x00B00000
#define	THIRD_STAGE_BSS_ADDRESS		0x00B80000
#define	THIRD_STAGE_STACK_ADDRESS	0x02000000
#define	HCOS_KERNEL_ADDRSPLIT		0xC0000000

#define	IDTR_BASE_ADDRESS			0x00900000

#define	PAGE_BITS	12
#define	PAGE_SIZE	(0x1 << PAGE_BITS)
#define	PAGE_MASK	(PAGE_SIZE-1)

/* TODO Make these defs runtime */
#define	MAX_PHYS_RAM_PAGES			((256<<10)>>(PAGE_BITS - 10))
#define	MEMORY_MAP_PHYS_ADDR		0x00900000

#endif /* __FIXEDDEFS_H__ */

