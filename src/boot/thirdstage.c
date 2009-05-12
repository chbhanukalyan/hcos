/*
 * Copyright (C) 2003  Bhanu Chetlapalli, Vamsi Krishna, Swamy Suman
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

void clearscreen(void);
int main(void)
{
	clearscreen();
	__asm__("movl $0xDEADBEAF, %eax");
	__asm__("movl $0xB1DBADBD, %eax");

	/* Do stuff here */

	/* OK halt the system here */
	while (1);
}

#define	VID_MEM_ADDR	0x000B8000
#define	VID_MEM_LEN		0xF00

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
}


