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
BOCHSIMAGE	=	bximage

FIRSTSTAGE	=	firststage
DISKIMG		=	disk.img

all: $(DISKIMG)

$(FIRSTSTAGE): firststage.s
	$(NASM) -o $(FIRSTSTAGE) firststage.s

$(DISKIMG):	$(FIRSTSTAGE)
	# If u you change this line, make sure to change bochsrc.txt too
	$(BOCHSIMAGE) -q -hd -mode=flat -size=10240 $(DISKIMG)
	dd if=$(FIRSTSTAGE) of=$(DISKIMG) bs=512 count=1 conv=notrunc

clean:
	-rm -f $(FIRSTSTAGE)
	-rm -f $(DISKIMG)
