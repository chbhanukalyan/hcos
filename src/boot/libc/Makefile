# Makefile
# ========
#
# Copyright (C) 2011  Bhanu Chetlapalli
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
# Used to build libc
#

include ../defs.mk

TARGET	:=	libc.a

OBJS	:=	string.o		\
			screenops.o		\
			stdio.o			\
			debug.o			\

$(TARGET): $(OBJS)
	$(AR) $(AR_FLAGS) $(TARGET) $(OBJS)

.c.o:
	$(CC) -o $@ $(CC_FLAGS) -c $<

clean:
	-rm -f $(TARGET)
	-rm -f $(OBJS)

