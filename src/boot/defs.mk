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
# Contains basic variable defs
#

# Assembler used is NASM
NASM		=	nasm
CC			=	x86_64-redhat-linux-gcc
CC_FLAGS	=	-Ilibc -g3 -Wall -Werror -m32 -nostdinc -nodefaultlibs -nostartfiles -nostdlib -fno-builtin
LD			=	ld
LD_FLAGS	=	-melf_i386 -nostdlib -nodefaultlibs -nostartfiles
AR			=	ar
AR_FLAGS	=	rcs
OBJCOPY		=	objcopy
BOCHSIMAGE	=	bximage

FIRSTSTAGE	=	firststage
SECONDSTAGE	=	secondstage
THIRDSTAGE	=	thirdstage
DISKIMG		=	disk.img

THIRDSTAGE_LOAD_ADDRESS	=	0x00A00000
THIRDSTAGE_DATA_ADDRESS =   0x00F00000
THIRDSTAGE_BSS_ADDRESS  =   0x00F80000
THIRD_STAGE_ENTRYPOINT	=	hcos_entry

