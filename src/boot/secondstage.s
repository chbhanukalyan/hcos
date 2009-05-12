; secondstage.s
; =============
; Copyright (C) 2009  Bhanu Chetlapalli
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
; =========================================================================
;
; This File is a part of the Holy Cow Operating System, which is written and
; maintained by Bhanu Kalyan Chetlapalli <chbhanukalyan@gmail.com>.
; 
; Function:
; It reads the harddisk using PIO mode and loads the third stage of 
; the OS.

%include "defs12.hs"
%include "harddisk.hs"

[BITS 16]
[ORG SECOND_STAGE_LOAD_SEGMENT * 0x10]
start:
	; Fill in the DS, ES, SS registers
	xor eax, eax
	mov ds, ax
	mov es, ax
	mov ss, ax

	; mov on to more imp work
	cli

	; Enable the A20 Address line
	; A20 is a vestige from the DOS era, where ppl though that 1MB is all
	; the main memory you will *ever* need. So to enable the higher memory
	; locations the A20 (the 21st address line to the memory needs to be
	; enabled. If not more than 1MB cannot be accessed or it might loop
	; around to lower addresses based on the hardware). Controlling this 
	; line was traditionally done through the Keyboard controller which is
	; stupid. So newer systems will have a fast A20 gate option, which will
	; directly enable it from the chipset. I am implementing only the 
	; Fast A20 switch only here, which is pretty simple
	in al, 0x92
	or al, 2
	out 0x92, al

	; Load the GDT register with the location of the GDT table in memory
	lgdt [gdtreg]

	; This is the standard way of enabling protected mode (other way is to
	; use the lmsw instruction). Basically set the bit '0' of the CR0 
	; control register of the processor to make it move to protected mode.
	mov eax, cr0
	or  eax, 1
	mov cr0, eax

	; Long jump into a 32 bit mode. This is required to be a long jump as
	; the x86 ISA documentation clearly mentions that the instruction prefetch
	; queue must be flushed (to remove 16 bit instructions)
	; Here 08h indicates that we are loading the Code entry of the GDT table 
	; into the CS register to indicate the selector.
	jmp 08h:mode32


; This is the 32 bit code section
[BITS 32]
mode32:
	; First - make sure that the old values of DS etc which corresponds to the
	; 16 bit real mode, is overwritten with valid segment selectors.
	; Otherwise this will easily result in Triple Faults
	mov ax, GDT_DATA_SELECTOR
	mov ds, ax
	mov es, ax
	mov ss, ax

	; Clear the screen
	call clearscreen

; OK The third stage can be anywhere on the disk, we do not have to rely on
; the BIOS interrupts which can load only upto 1023 cylinders to get it for
; us. 

	mov eax, THIRD_STAGE_LOAD_ADDRESS
	mov ebx, 0x200
	call memset

	mov byte [0x000B8000], 'a'

	mov eax, 4
	mov bl, 1
	mov edi, THIRD_STAGE_LOAD_ADDRESS
	call read_sectors

	; see whether they actually loaded something
	mov al, [THIRD_STAGE_LOAD_ADDRESS]
	mov [0x000B8020], al
	mov al, [THIRD_STAGE_LOAD_ADDRESS + 1]
	mov [0x000B8022], al
	mov al, [THIRD_STAGE_LOAD_ADDRESS + 2]
	mov [0x000B8024], al

		mov byte [0x000B800E], 'Z'

; Start loading Stage 3 here - for now just stop
	jmp $


;=========================================================================
; clearscreen - clears the screen
; Screen typically has alternating color and character bytes. So color
; bytes must be set to sane values, not zero.
clearscreen:
	mov eax, 0x000B8000
	mov ebx, 0xF00
	call memset

	; Set color bytes to sane values
	mov eax, 0x000B8001
next_color_byte:
	add eax, 0x2
	mov byte [eax], 0x0F
	cmp eax, ebx
	jle next_color_byte

	ret

;=========================================================================
; memset - basically zeros out the memory location specified in eax, upto
; the count specified in ebx

memset:
	add ebx, eax
next_byte:
	cmp eax, ebx
	jz memset_over
	mov byte [eax], 0
	inc eax
	jmp next_byte
memset_over:
	ret


;==========================================================================
; This routine simply reads the data from the Disk and loads it into 
; the memory location specified.
;
; Reads the sector number (LBA) given in EAX
; Memory Location EDI
; number of sectos - BL

read_sectors:
	; Set Registers one by one

	; Set Sector Count
	mov al, bl
	mov dx, HDPC_SECTOR_BYTE
	out dx, al

mov byte [0x000B8002], 'B'

	; Set 24 bit LBA
	mov dx, HDPC_LBA_LOW_BYTE
	out dx , al
	mov byte [0x000B8004], 'C'

	shr eax, 8
	mov dx, HDPC_LBA_MID_BYTE
	out dx, al
	mov byte [0x000B8000], 'D'
	
	shr eax, 8
	mov dx, HDPC_LBA_HIGH_BYTE
	out dx, al
	
	mov byte [0x000B8006], 'E'
	shr eax, 8

	; Set the Device number etc
	; TODO only first disk for now (0xA0 is 1st disk, 0xB0 is 2nd disk)
	mov al, 0xA0
	mov dx, HDPC_DEVICE_BYTE
	out dx, al

	mov byte [0x000B8008], 'F'

	; Send Command
	mov al, HD_CTRLR_READ_SECTORS
	mov dx, HDPC_COMMAND_BYTE
	out dx, al
	mov byte [0x000B800A], 'G'

	; Read all 512 bytes into memory
	mov ecx, 256	; read upto 512 (256 words) bytes from port
	mov dx, HDPC_DATA_WORD
	cld ; set the direction bit
	rep insw
	
	mov byte [0x000B800C], 'H'

	ret

;==============================================================================================

[BITS 16]
; GDT Ptr - Pointer to the GDT Table to be loaded into the GDT Register
gdtreg:
	dw gdt_end-gdtable-1
	dd gdtable

; Create GDT table
gdtable:
	; NULL Selector
	dw 0	; Limit 15:0
	dw 0	; base 15:0
	db 0	; base 23:16
	db 0	; type
	db 0	; limit 19:16, flags
	db 0	; base 31:24

	; Code Selector
gdtentry2:
	GDT_CODE_SELECTOR equ $-gdtable
	dw 0xFFFF	; Limit 15:0
	dw 0	; base 15:0
	db 0	; base 23:16
	db 0x9A	; type
	db 0xCF	; limit 19:16, flags
	db 0	; base 31:24

gdtentry3:
	; Data Selector
	GDT_DATA_SELECTOR equ $-gdtable
	dw 0xFFFF	; Limit 15:0
	dw 0	; base 15:0
	db 0	; base 23:16
	db 0x92	; type
	db 0xCF	; limit 19:16, flags
	db 0	; base 31:24
gdt_end:


