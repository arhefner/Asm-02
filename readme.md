
# ASM/02 - 1802 Cross Assembler

This is an update to Mike Riley's ASM/02 cross compiler for the 1802 running on Windows/Linux/etc.

## Original Repo
https://github.com/rileym65/Asm-02

## Options and License

The original ASM/02 license reads:
```
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
```
This code can use ya_getopt (https://github.com/kubo/ya_getopt), which is provided under a 2-clause BSD-style license.
If you are compiling under Linux, you can set the GETOPT variable to 'ya_getopt' to use this instead of the standard getopt library, like so:

```
make GETOPT=ya_getopt
```

## Special Features and Usage Notes
The assembler can produce binary, Intel hex, or a relocatable format for use with [Link/02](https://github.com/arhefner/Link-02).
It offers a preprocessor and conditional compilation. There is also a mechanism for defining new instructions
such as those found in opcodes.def.

* Labels must end with a colon
* Hex numbers may be specified with an 'h' suffix, or a '$' prefix. When using the 'h' suffix, the number must start with a digit from 0-9.  
Examples:
```
12h
$12
0f7h
$F7
```
* You can't use ORG to specify an absolute address within a PROC/ENDPROC.

## Directives

* .1805        - Enable 1805 mode
* .arch=elf2k  - Set Elf2000 memory model
* .arch=mchi   - Set Membership Card high-RAM memory model
* .arch=mchip  - Set MemberCHIP card memory model
* .arch=mclo   - Set Membership Card low-RAM memory model
* .arch=melf   - Set Micro/Elf memory model
* .arch=pev    - Set Pico/Elf memory model
* .arch=pev2   - Set Pico/Elf V2 memory model
* .arch=mini   - Set 1802/Mini memory model
* .arch=max    - Set 1802/MAX memory model
* .align word  - Align address on word boundary (2 bytes)
* .align dword - Align address on double word boundary (4 bytes)
* .align qword - Align address on quad word boundary (8 bytes)
* .align para  - Align address on paragraph boundary (16 bytes)
* .align 32    - Align address on 32-byte boundary
* .align 64    - Align address on 64-byte boundary
* .align 128   - Align address on 128-byte boundary
* .align page  - Align address on page boundary (256 bytes)
* .binary      - Output as binary
* .intel       - Output as Intel hex
* .list        - Enable show list
* .rcs         - Output as Rcs hex
* .sym         - Show symbols
* .link line   - Pass 'line' to linker
* .suppress    - Suppress further byte output
* .op "opcode","arglist","translation" (see examples, below)

### Arglist:

*  B - byte
*  N - nybble
*  W - word
*  R - R-register

### Translation:
*  0-9 - Nybble after 4-bit left shift
*  A-F - Nybble after 4-bit left shift
*  Hn  - High byte of argument n
*  Ln  - Low byte of argument n
*  Tn  - Low byte of argument n, error if not in current page
*  $n  - Or with argument n after 4-bit left shift
*  Wn  - Output the two bytes of word argument n

## Command line switches
* -1805         - Enable 1805 mode
* -b, -binary   - Output in binary
* -Dname        - Define name with value of "1"
* -Dname=value  - Define name with specified value
* -r, -reloc    - Output in RCS hex
* -i, -intel    - Output in Intel hex
* -Ipath        - Add path to search list for #include files
* -l, -showlist - Show assembly list
* -L, -list     - Create .lst file
* -s, -symbols  - Show symbols
* -m, -map      - Show memory map in binary/hex mode
* -melf         - Set Micro/Elf memory model
* -pev          - Set Pico/Elf memory model
* -pev2         - Set Pico/Elf V2 memory model
* -elf2k        - Set Elf2000 memory model
* -mclo         - Set Membership Card low RAM memory model
* -mchi         - Set Membership Card high RAM memory model
* -mchip        - Set MemberChip Card memory model
* -mini         - Set 1802/Mini memory model
* -max          - Set 1802/MAX memory model
* -ram=low-high - Set explicit RAM region
* -rom=how-high - Set explicit ROM region
* -cr           - Use CR as line ending
* -lf           - Use LF as line ending
* -crlf         - Use CRLF as line ending
* -lfcr         - Use LFCR as line ending
* -help, -h     - List of options

## Evaluator variables
* [month]         - Build month
* [day]           - Build day
* [year]          - Build year
* [hour]          - Build hour
* [minute]        - Build minute
* [second]        - Build second
* [build]         - Build number

## Preprocessor
* #include filename
* #define symbol value
* #undef symbol
* #if expr
* #ifdef symbol
* #ifndef symbol
* #else
* #endif
* #error text

## Pseudo ops
* extrn label   - Define external label
* public label  - Define label as public
* db  bb,bb,... - Define bytes
* dw  ww,ww,... - Define words
* dd  dd,dd,... - Define double words
* df  ff,ff,... - Define floating point data
* ds  ww        - Define storage
* equ expr      - Set label to value
* org expr      - Set assembly address
* proc label    - Begin relocatable procedure
* endp          - End of relocatable procedure
* ver           - Build standard Elf/OS VER header
* ever          - Build extended Elf/OS VER header
* eever         - Build enhanced Elf/OS VER header
  
## Sample opcode macros
```
.op "PUSH","N","9$1 73 8$1 73"
.op "POP","N","60 72 A$1 F0 B$1"
.op "CALL","W","D4 H1 L1"
.op "RTN","","D5"
.op "MOV","NR","9$2 B$1 8$2 A$1"
.op "MOV","NW","F8 H2 B$1 F8 L2 A$1"
.op "SUB16","NR","8$2 52 8$1 F7 A$1 9$2 52 9$1 77 B$1"
.op "SHL16","N","8$1 FE A$1 9$1 7E B$1"
.op "SHR16","N","9$1 F6 B$1 8$1 76 A$1"
.op "ADD16","NW","8$1 FC L2 A$1 9$1 7C H2 B$1"
.op "SUB16","NW","8$1 FF L2 A$1 9$1 7F H2 B$1"
.op "CLC","","fc 00"
.op "STC","","ff 00"
```
