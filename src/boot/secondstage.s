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

	lgdt [gdtreg]

	xor eax,eax
	mov ax, 0x0001
	lmsw ax

; Long jump into a 32 bit mode. This is required to be a long jump as
; the x86 ISA documentation clearly mentions that the instruction prefect
; queue must be flushed (to remove 16 bit instructions)
; Here 08h indicates that we are loading the Code entry of the GDT table
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

;==============================================================================================

; Define the hard disk controler IDs
%define     HARD_DISK_PRIMARY_CONTROLER     0x01F0
%define     HARD_DISK_SECONDARY_CONTROLER   0x0170

; Note that this will read sectors without any limit (0x20 is a more basic version)
%define     CMD_READ_SECTORS                0x24
%define     CMD_WRITE_SECTORS               0x30

%define     HDPC_DATA_WORD              0x01F0

%define     HDPC_SECTOR_BYTE            0x01F2
%define     HDPC_LBA_LOW_BYTE           0x01F3
%define     HDPC_LBA_MID_BYTE           0x01F4
%define     HDPC_LBA_HIGH_BYTE          0x01F5
%define     HDPC_DEVICE_BYTE            0x01F6
%define     HDPC_COMMAND_BYTE           0x01F7



mov byte [0x000B8000], 'A'

    mov eax,0x000E0000
	bzo:
	    inc eax
		    mov byte [eax], 0
		    cmp eax, 0x000E0200
		    jnz bzo

		mov byte [0x000B8000], 'a'

		    mov eax, 4
		    mov edi, 0x000E0000
		   call read_sectors

		mov al, [0x000E0000]
		mov [0x000B8020], al
		mov al, [0x000E0001]
		mov [0x000B8022], al
		mov al, [0x000E0002]
		mov [0x000B8024], al

		mov byte [0x000B800E], 'Z'

; Start loading Stage 3 here - for now just stop
	jmp $

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

		    ; Set 25-28 bit etc
		    ; Set the Device number etc
		    and eax, 0x0000000F
		    or eax, 0xE0         ; i.e.E0 = 0x40|0xA0
		    mov dx, HDPC_DEVICE_BYTE
		    out dx, al
		mov byte [0x000B8008], 'F'

		    ; Send Command
		    mov al, CMD_READ_SECTORS
		    mov dx, HDPC_COMMAND_BYTE
		    out  dx, al
		mov byte [0x000B800A], 'G'

		    ; Read all 512 bytes into memory
		    mov ecx, 256    ; read upto 512 (256 words) bytes from port
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


