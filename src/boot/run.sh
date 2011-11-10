#!/bin/sh
# Run the BOCHS simulator

set -e

BOCHS=bochs-gdb
make clean
make

DEBUG_OPT=

if [ "$1" = "-d" ]; then
	DEBUG_OPT='gdbstub:enabled=1, port=1234, text_base=0, data_base=0, bss_base=0'
	DEBUG_OPT='gdbstub:enabled=1, port=1234, text_base=0x00A00000, data_base=0x00F00000, bss_base=0x00F800000'
fi

$BOCHS -q -f ../../env/bochsrc_pc_with_nic.cfg "$DEBUG_OPT"

