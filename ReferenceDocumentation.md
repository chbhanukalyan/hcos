## Fundamental Docs ##

The most fundamental part of the documentation is the AMD64/EM64t Manuals released by AMD/Intel. These manuals clearly define how the processor works. You can download the manuals from these links

  * http://www.intel.com/products/processor/manuals/
  * http://www.amd.com/us-en/Processors/DevelopWithAMD/0,,30_2252_875_7044,00.html

It is nearly impossible to write any kind of OS without the ISA documentation, so download them right now!

For basic OS writing, both Intel and AMD manuals are essentially same. For advanced programming, optimizations etc it pays to know the minor differences in HOW the ISA is implemented.

The only fundamental difference in the ISAs occur with the Multimedia Extensions with Intel having MMX, SSE, SSE2 etc and AMD having 3DNow! etc extensions. Even these are compatible until SSE2 on both company's chips.