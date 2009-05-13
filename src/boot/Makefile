# Makefile
# ========
#
# Copyright (C) 2009  Bhanu Chetlapalli
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# =========================================================================
#
# Used to build the bootloader part of the OS
#

# Assembler used is NASM
NASM		=	nasm
GCC			=	gcc -m32
LD			=	ld -melf_i386
OBJCOPY		=	objcopy
BOCHSIMAGE	=	bximage

FIRSTSTAGE	=	firststage
SECONDSTAGE	=	secondstage
THIRDSTAGE	=	thirdstage
DISKIMG		=	disk.img

THIRDSTAGE_LOAD_ADDRESS	=	0x00E00000
THIRDSTAGE_DATA_ADDRESS	=	0x00F00000
THIRDSTAGE_BSS_ADDRESS	=	0x00F80000

all: $(DISKIMG)

$(FIRSTSTAGE): $(FIRSTSTAGE).s defs12.hs
	$(NASM) -o $(FIRSTSTAGE) $(FIRSTSTAGE).s

$(SECONDSTAGE): $(SECONDSTAGE).s defs12.hs harddisk.hs
	$(NASM) -o $(SECONDSTAGE) $(SECONDSTAGE).s

$(THIRDSTAGE): $(THIRDSTAGE).c
	$(GCC) -o $(THIRDSTAGE).o -c $(THIRDSTAGE).c
	$(LD) -o $(THIRDSTAGE).out -Ttext $(THIRDSTAGE_LOAD_ADDRESS) -Tdata $(THIRDSTAGE_DATA_ADDRESS) -Tbss $(THIRDSTAGE_BSS_ADDRESS) -e main $(THIRDSTAGE).o
	$(OBJCOPY) -R .note -R .comment -S -O binary $(THIRDSTAGE).out $(THIRDSTAGE)

$(DISKIMG):	$(FIRSTSTAGE) $(SECONDSTAGE) $(THIRDSTAGE)
	# If u you change this line, make sure to change bochsrc.txt too
	-rm -f $(DISKIMG)
	$(BOCHSIMAGE) -q -hd -mode=flat -size=10240 $(DISKIMG)
	#dd if=/dev/zero of=$(DISKIMG) bs=1024 count=10240
	dd if=$(FIRSTSTAGE) of=$(DISKIMG) bs=512 count=1 conv=notrunc
	dd if=$(SECONDSTAGE) of=$(DISKIMG) bs=512 count=2 seek=1 conv=notrunc
	dd if=$(THIRDSTAGE) of=$(DISKIMG) bs=512 count=2 seek=4 conv=notrunc

clean:
	-rm -f $(FIRSTSTAGE)
	-rm -f $(SECONDSTAGE)
	-rm -f $(THIRDSTAGE) $(THIRDSTAGE).out $(THIRDSTAGE).o
	-rm -f $(DISKIMG)

