; firststage.s
; ============
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
; The main function of this file is to load the second stage of the bootloader.
; It reads the harddisk using the interrupt 13h and loads the third stage of 
; the OS.
;
; We get the size of the Second Stage and location to load it in the
; given variables
;

%include  "defs12.hs"
 
%define SCREEN_WIDTH 80
%define SCREEN_HEIGHT 25

; This is the 0th offset (Directive to nasm)
[ORG 0]
	jmp 07C0h:start

; Declare some message strings
	welcome1  db 'Welcome to Holy Cow Operating System - By Bhanu Chetlapalli',13,0
	startstr1 db 'Starting the System....',13,0
	load2 db 'Loading Second Stage ',0
	pass db 'Succeded',13,0
	fail db 'Failed',13,0
	systemhalted db 13,'System Halted!',13,0
	exec2stage db 'Executing Second Stage',13,0

	curline dw 0x0000
	curoff  dw 0x0000
	screencolor db 0x8F

; Main function
start:
	; Disable all Interrupts
	cli

	; Load the ds, es segment registers
	mov ax, cs
	mov ds, ax
	mov es, ax

	; Initialize the screen coordinates and Clean up the screen
	mov word [curline],0
	mov word [curoff],0
	mov bl, 0x8F
	call clearscreen

	mov si, welcome1
	call printstr
	
	mov si, startstr1
	call printstr

	; Load sectors
	mov si, load2
	call printstr
	call loaddisk

	mov si,exec2stage
	call printstr
	
;	xor ebx, ebx
;myinc: inc ebx
;	cmp ebx,500000	; @ 800MHz it is 1 sec .. :)
;	jnz myinc	
;	jmp bck

	;Enable Interrupts
	cli

	; Jump to the second stage of the boot loader
	jmp SECOND_STAGE_LOAD_SEGMENT:0000

; ============================================================================
; Name		: loaddisk
; Input		: -
; Output	: -
; Function	: Loads the SECOND_STAGE_SIZE sectors starting from 2nd sector
;			  into SECOND_STAGE_LOAD_SEGMENT:0000 memory location
; ============================================================================
loaddisk:
	
	mov ax, SECOND_STAGE_LOAD_SEGMENT
	mov es, ax			; loads the segment register to copy data from HD
	mov bx, 0			; load offset
	mov al, SECOND_STAGE_SIZE	; loads the given sectors
	mov cl, 02h			; read starting from which sector?
	mov ah, 02h         ; const
	mov ch, 00h         ; track no
	mov dh, 00h         ; head no
	mov dl, 80h         ; disk no (00-7h floppy & 80-ff HardDisk)

	int 13h				; Call the 13h interrupt to load the disk sectors

	jnc loaddiskret

	mov si, fail
	call printstr

	jmp haltpc

loaddiskret:
	
	mov si, pass
	call printstr

	ret
	

; ============================================================================
; Name		: haltpc
; Input		: 
; Output	: -
; Function	: Halts the computer, until a h/w reset (generally on fatal errs)
; ============================================================================
haltpc:
	mov si, systemhalted
	call printstr
	jmp $

; ============================================================================
; Name		: clearscreen
; Input		: %BL color to clear
; Output	: -
; Function	: Clears the screen with the value defined in %BL
; ============================================================================
clearscreen:
	mov ax, 0xB800
	mov ds, ax
	mov si,0
clearscreen_clr: mov byte [DS:SI], 0
	inc si
	mov [DS:SI], bl
	mov [screencolor], bl	; Also save the byte color
	inc si
	cmp si,0xF00	; End
	jnz clearscreen_clr
	mov ax, cs
	mov ds, ax
	ret

; ============================================================================
; Name		: printstr
; Input		: ES:SI (contains string ptr)
; Output	: -
; Function	: Prints the string onto the screen
; ============================================================================
printstr:
	mov ax, cs
	mov es, ax			; Load the video segment
	mov ax, 0xB800
	mov ds, ax			; Load the video segment
printnextchar:
;	xor eax,eax
;	xor ebx,ebx
;	xor ecx,ecx
	mov byte al, [ES:SI]				; al contains the byte from ES:SI
	inc si
	cmp al, 0
	jz printret
	cmp al, 13
	jnz notnewline
	add word [ES:curline], 1
	mov word [ES:curoff], 0
	
	; Scroll Window....
	cmp word [ES:curline], SCREEN_HEIGHT
	jnz noscrollreq

	;To scroll, copy data & dec [curline] & zero last line
	mov word [ES:curline], SCREEN_HEIGHT-1
	mov bx,160
scrollcopy:
	mov byte DL, [DS:BX]
	sub bx, 160
	mov byte [DS:BX], DL
	add bx, 161
	cmp bx, SCREEN_HEIGHT*SCREEN_WIDTH*2
	jnz scrollcopy

	sub bx,160
scrollzerolast:
	mov byte [DS:BX], 0
	inc bx
	cmp bx, SCREEN_HEIGHT*SCREEN_WIDTH*2
	jnz scrollzerolast

noscrollreq:
	jmp printnextchar
notnewline:
	mov cx, ax
	mov ax, 0x50		; if 0, first line...
	mul word [ES:curline]
	add word ax, [ES:curoff] ; go to offset also
	mov bx, 2
	mul bx			; now we have the correct location of cursor offset
	mov bx, ax
	mov byte [DS:BX], cl
	; Setting color man
	add bx,1
	mov cl, [screencolor]
	mov byte [DS:BX], cl

	add word [ES:curoff], 1
	jmp printnextchar
	
printret: 
	mov ax, cs
	mov ds, ax
	ret

; Pad the remaining space, so that the size of the sector adds up to 512 bytes
; NOTE: On an actual hard disk this will end up overwriting the
; Partition table which resides from 400 byte offset. For initial stages
; this is fine
	times 510-($-$$) db 0
; Last 2 bytes are a magic number which indicates that this is a
; real bootable drive
	dw 0xaa55

;==========================================================================
; This is the second part of the boot loader....
	; DO NOT USE $ etc as this will be loaded away from the top 512 bytes
	xor eax,eax
	mov eax,0xABCDEF01
	jmp SECOND_STAGE_LOAD_SEGMENT:0
	times 2048-($-$$) db 0

