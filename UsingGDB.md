Since developing the kernel without debugging infrastructure can be impossible, the following instructions can help leverage the GDB support in bochs to debug the programs

I have added a '-d' option to the run.sh script to start in debugger mode. Even if not you need to add a line similar to below to the bochsrc

```
gdbstub:enabled=1, port=1234, text_base=0, data_base=0, bss_base=0
```

This will make bochs listen on the port 1234. (Use bochs-gdb or similar to start bochs with GDB support built in)

Then you can use gdb on thirdstage.out (the EFL output before stripping by objcopy) to connect using the below GDB command and you are set. I have added a .gdbinit which does this

```
target remote 127.0.0.1:1234
```

To get started, I generally put a breakpoint at the Third stage address - 0x00A00000 and continue - so that I dont have to step through the initial startup instructions.

```
# gdb thirdstage.out 
GNU gdb (GDB) Fedora (7.1-30.fc13)
Copyright (C) 2010 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /root/hcos/src/boot/thirdstage.out...done.
warning: Remote failure reply: Eff
0x0000fff0 in ?? ()
(gdb) b *0x00A00000
Breakpoint 1 at 0xa00000: file thirdstage.c, line 34.
(gdb) c
Continuing.

Breakpoint 1, hcos_entry () at thirdstage.c:34
34      {
1: x/i $eip
=> 0xa00000 <hcos_entry>:       push   %ebp
(gdb) si
0x00a00001      34      {
1: x/i $eip
=> 0xa00001 <hcos_entry+1>:     mov    %esp,%ebp
(gdb) 
0x00a00003      34      {
1: x/i $eip
=> 0xa00003 <hcos_entry+3>:     sub    $0x78,%esp
(gdb) 
```