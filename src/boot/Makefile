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

BASE := $(shell pwd)

include defs.mk

all: $(DISKIMG)

$(FIRSTSTAGE): $(FIRSTSTAGE).s defs12.hs
	$(NASM) -o $(FIRSTSTAGE) $(FIRSTSTAGE).s

$(SECONDSTAGE): $(SECONDSTAGE).s defs12.hs harddisk.hs
	$(NASM) -D NUM_THIRDSTAGE_SECTORS=$(NUM_THIRDSTAGE_SECTORS) -o $(SECONDSTAGE) $(SECONDSTAGE).s

SUBDIRS	:=	libc	\
			kutils	\

LIBS	:=	libc/libc.a		\
			kutils/libkutils.a	\

OBJS	:=	thirdstage.o	\
			interrupts.o	\
			8259.o			\
			paging.o		\

$(THIRDSTAGE): $(OBJS) subdirs
	$(LD) $(LD_FLAGS) -o $(THIRDSTAGE).out -Ttext $(THIRDSTAGE_LOAD_ADDRESS) -Tdata $(THIRDSTAGE_DATA_ADDRESS) -Tbss $(THIRDSTAGE_BSS_ADDRESS)  -e $(THIRD_STAGE_ENTRYPOINT) $(OBJS) $(LIBS)
	$(OBJCOPY) -R .note -R .comment -S -O binary $(THIRDSTAGE).out $(THIRDSTAGE)

# Generic suffix rule to compile C files					
.c.o:
	$(CC) -o $@ $(CC_FLAGS) -c $<

$(DISKIMG):	$(FIRSTSTAGE) $(SECONDSTAGE) $(THIRDSTAGE)
	# If u you change this line, make sure to change bochsrc.txt too
	-rm -f $(DISKIMG)
	$(BOCHSIMAGE) -q -hd -mode=flat -size=10240 $(DISKIMG)
	#dd if=/dev/zero of=$(DISKIMG) bs=1024 count=10240
	dd if=$(FIRSTSTAGE) of=$(DISKIMG) bs=512 count=1 conv=notrunc
	dd if=$(SECONDSTAGE) of=$(DISKIMG) bs=512 count=2 seek=1 conv=notrunc
	dd if=$(THIRDSTAGE) of=$(DISKIMG) bs=512 count=$(NUM_THIRDSTAGE_SECTORS) seek=4 conv=notrunc

# Libraries
subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	-rm -f $(FIRSTSTAGE)
	-rm -f $(SECONDSTAGE)
	-rm -f $(THIRDSTAGE) $(THIRDSTAGE).out
	-rm -f $(OBJS)
	-rm -f $(DISKIMG)
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

