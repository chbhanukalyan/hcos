## Processor Name Terminology ##

With respect to the different types of processors/models in the market, some form of terminology clarification is required I believe. I will now discuss the terms you will come across, so that you wont be confused. Consider this a very brief history lesson too :) Once you go through this document, you will hopefully understand what people are talking about when they mention i386, x86\_64 etc.

I oversimplified some product lines, so that clarity is maintained.

### 8088: ###
An 8 bit processor from Intel, one of the first ones. You wont find this anywhere on PCs

### 8086: ###
A 16 bit processor from Intel. Code written for this processor will STILL execute on even the latest Xeon multi-core processors! Such is the level of backwards compatibility provided

### 80x86: ###
This is used to indicate the processors after 8086 like 80186, 80286, 80386 etc. This has been shortened to "x86".

### x86: ###
See 80x86

### 286 ###
This processor had some basic support for segmentation etc

### 386 ###
This was the first 32 bit processor in the Intel line and had a fully supported protected mode (along with an MMU), paging etc, which enabled development of complicated operating systems like Windows, Linux etc which provide features like Virtual Memory, protection between processors etc.

### 486, 586, 686 ###
Subsequently improved versions of 386

### Pentium ###
For All processors mentioned before, other companies like AMD etc could make similar clones, AND use the same name. Essentially denying branding of Intel's products. Intel's efforts to trademark 386 were denied by the US Govt on the grounds that a number cannot be trademarked. So Intel released the Pentium Line of processors to overcome these trademark issues. It was now able to prevent other companies from using the same names as itself.

### Athlon ###
After Intel trademarked Pentium name, AMD was forced to use a new name for its processor line. It chose Athlon.

### Itanium ###
Itanium was a 64 bit processor from Intel which was NOT backwards compatible with the x86 line. It was also fundamentally different at the ISA level using a VLIW architecture instead of the standard CISC of the x86 line. This was a major disaster for Intel, since AMD undercut it by releasing a x86-backwards compatible 64 bit processor. Barring a few HP machines, this did not sell much.

### Athlon64 ###
After Itanium, which required special OS and application development was faltering in the market, AMD released the AMD64 ISA which was backwards compatible. The corresponding 64 bit processor was Athlon64.

### Opteron ###
Opteron is the AMD's Server class processor

### Xeon ###
Xeon was a newer x86 64 bit processor which was compatible with the AMD64 ISA. (Intel actually chose to call it EM64t instead of AMD64)

### IA32 ###
This is the processor Instruction Set Architecture (ISA) of the i386 and above, 32 bit processors. Although this used to be called the x86 ISA, it was retroactively named as IA32 by Intel after the release of the IA64 line

### IA64 ###
See Itanium

### AMD64/EM64T ###
See Xeon. Linux takes a neutral approach and calls it x86\_64 architecture.