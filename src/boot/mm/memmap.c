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
 * This file contains the memory map init functions
 */

#include <memmgr.h>

void init_memmap(void)
{
	/* initialize memory map - 1 bit per PAGE */
	int num_map_pgs = (MAX_PHYS_RAM_PAGES >> 3) + ((MAX_PHYS_RAM_PAGES & 0x7) ? 1 : 0);

	u8 *map = MEMORY_MAP_PHYS_ADDR;

	/* First mark all areas as unused */
	memset(map, 0, num_map_pgs << PAGE_SIZE_BITS);

	/* Now Mark Reserved no-go/already assigned Areas */
	
}

