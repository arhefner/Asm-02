
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

## Building the Assembler

### Linux

This code can use ya_getopt (https://github.com/kubo/ya_getopt), which is provided under a 2-clause BSD-style license.
If you are compiling under Linux using the included Makefile, you can set the GETOPT variable to 'ya_getopt' to use this instead of the standard getopt library, like so:

```shell
make GETOPT=ya_getopt
```

### Windows

This code should be able to be compiled with any reasonable C compiler.
All that is needed is to compile and link all the "C" files in this repository to produce the assembler executable.
There are no compiler options or settings that are strictly required.

The assembler can be built with Microsoft Visual Studio without using its IDE.
Any recent version of the free "Community Edition" of Visual Studio should work.
Start a "Developer Command Prompt" from the Windows Start Menu and change the current directory to the one containing the source code. 

An nmake file is provided to build all the sources:

```
nmake -f MakeAsm
```

Of course the Visual Studio IDE can be used to easily create a Solution/Project to build the "C" files in this repository.

## Special Features and Usage Notes
The assembler can produce binary, Intel hex, or a relocatable format for use with [Link/02](https://github.com/fourstix/Link-02).
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
* `mov reg, symbol+N`-style compound expressions (a relocatable label plus/minus a constant, used directly as an instruction operand) resolve correctly, including `N` written as a named `equ` constant rather than a bare numeral (`symbol+FIELD_OFFSET`, and chains like `symbol+FIELD_A+FIELD_B`), and including offsets that cross a byte boundary and need carry propagation into the address's high byte — confirmed by isolated testing against real relocatable (cross-file, link-time-resolved) labels, not just absolute `equ` constants.
* **Fixed in v1.6 (2026-07-15): `mov reg, symbol+NAME`, where `NAME` is itself a named `equ` constant, used to silently drop `symbol`'s own relocation and resolve to just `NAME`'s value — found via direct byte-decode of a real build that hit this in practice (a struct-field-offset idiom, `mov rf, some_struct+FIELD_OFFSET`, is about as common as this gets).** Cause: evaluating a `+` expression parses each operand through the same identifier-token path, and *every* label token — not just the first — unconditionally overwrote the evaluator's internal "this expression references an external/relocatable symbol" tracking based on whether *that* token was itself external. So `symbol+NAME` recorded a valid reference while parsing `symbol`, then immediately lost it while parsing `NAME` (a plain, non-relocatable `equ` label isn't a reference itself, so the tracking got reset to "no reference" even though `symbol` genuinely was one) — the instruction silently emitted with no relocation fixup at all, just `NAME`'s bare numeric value, no warning or error at any point. A bare-numeral offset never hit this (numbers are parsed by a separate code path that doesn't touch this tracking), which is why isolated testing of `symbol+300`-style cases alone didn't catch it. Fix: the tracking is now only updated when the *current* token is itself a genuine reference, so a later plain-constant token can no longer clobber one recorded earlier in the same expression. `high`/`low`/`.` applied to a `symbol+NAME` expression share the same fix (they depend on the same tracking).
* **Fixed in v1.12 (2026-09-25): `mov reg, label+N`, where `label` is defined in the same `proc`, used to lose the offset's low byte.** A local high-byte fixup stores a companion low byte that the linker uses to rebuild the full value; for macro operands (`mov`, via `.op` `H`/`L` bytes) it stored the bare label's low byte instead of the whole expression's, so `mov rf, buf+510` linked to `buf+512` and `buf+1` linked to `buf`. The high byte was right, which made it easy to miss. References to labels in another proc or file were never affected (their `/` line already carries the expression's low byte), nor was code outside any `proc` (no local fixups at all). Rebuilding the whole ELF-DOS tree with the fix is byte-identical to the v1.10 build: no existing code there depended on the bug.
* **`equ alias: equ relocatable_label+CONST` remains broken, for a different reason — NOT fixed by the above** — `equ`'s handler (`OT_EQU` in `asm.c`) just evaluates the expression and calls `setLabel()`, with no participation in the reference/fixup mechanism at all (so even a bare-numeral offset doesn't save it here, unlike the `mov` case above, which was always fine with a numeral). The result silently resolves to an unrelated, wrong link-time value with no assembler warning or error — confirmed via an isolated test (`alias0: equ real_block`, `alias1: equ real_block+1`, `alias5: equ real_block+5`, where `real_block` is a genuine `ds`-declared label inside a `proc`): all three aliases collapsed to the *same* wrong address regardless of the offset used, instead of `real_block+0/1/5`. Only alias an absolute constant this way (`equ`-ing another `equ`-defined literal, or a fixed `org`-style address) — never a `ds`/`dw`/`db` label that lives inside a `proc`.

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
* .norelax     - Long branches (lbr/lbq/lbz/lbdf/lbnq/lbnz/lbnf) assembled
                  from here on emit old-style fixups, exactly like a plain
                  word reference -- a linker's short-branch relaxation pass
                  (e.g. link02 -r) will never touch them. This is already
                  the default for a whole file assembled without -r (see
                  below); .norelax is for forcing it on one section of a
                  file that otherwise has -r's relax-aware default. Resets
                  to the file's own default at the start of every pass, so
                  it only affects code between here and the next .relax
                  (or end of file).
* .relax       - Long branches assembled from here on emit relax-aware
                  fixups, so a linker's -r pass can consider shrinking
                  them. This is already the default for a whole file
                  assembled with -r; .relax is for forcing it on one
                  section of a file that otherwise has -r's own default
                  turned off (i.e. no -r was passed at all). Safe even
                  with no -r anywhere: the fixups still resolve correctly,
                  just nothing gets shrunk.
* .endian=big     - Set byte order to big-endian
* .endian=little  - Set byte order to little-endian
* .endian=default - Set byte order to default
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
* -reloc        - Output in RCS hex (already the default)
* -r            - Long branches emit relax-aware fixups by default (see
                   .relax/.norelax above), so a linker's short-branch
                   relaxation pass (e.g. link02 -r) can shrink them.
                   Without -r, long branches always emit old-style
                   fixups, byte-for-byte matching a pre-relaxation
                   Asm/02 and safe for any linker that doesn't know
                   about the newer marker format. Pass the same -r to
                   both Asm/02 and link02 to get real branch shrinking;
                   -r on only one of the two tools is a harmless no-op
                   on the other.
* -i, -intel    - Output in Intel hex
* -Ipath        - Add path to search list for #include files
* -l, -showlist - Show assembly list
* -L, -list     - Create .lst file
* -q, -quiet    - Show minimal output
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
* -version, -v  - Display the version number
* -C, -case     - Treat labels as case sensitive
* -be           - Set default byte order to big-endian
* -le           - Set default byte order to little-endian
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
* #elif expr
* #endif
* #error text
* defined(symbol)

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
* end expr      - Set the program's exec/start address (recorded in the output header; has no effect on assembly itself)

## Expressions

Expression evaluation is available anywhere a numeric value is expected (instruction operands, `equ`, `db`/`dw`/`ds` arguments, `#if`, etc. — including the `[month]`/`[day]`/... build-time variables listed above). Standard C-like precedence applies (unary operators and `abs()`/`sgn()`/`high`/`low` bind tightest, then `* / %`, then `+ -`, then `<< >>`, then `& | ^`, then the comparisons, then `&& ||`).

* Values are 32-bit signed: `-1`, `0-1` and `~0` are all `0xffffffff`, and a label or `equ` constant holds exactly the 32-bit value its expression produced (so `M1: equ -1` makes `dd M1` emit `ff ff ff ff` and `M1 == -1` true). `db`/`dw`/instruction operands take the low byte/word, warning only if the value doesn't fit. Values exported to the linker (`public`) and shown in the symbol listing are the low 16 bits. Note that `0ffffh` and `-1` are different values in comparisons.
* Binary arithmetic: `+` `-` `*` `/` `%` (modulo)
* Binary bitwise: `&` (and) `|` (or) `^` (xor) `<<` (shift left) `>>` (shift right)
* Binary comparison: `==` (or bare `=`) `!=` `<` `>` `<=` `>=`
* Binary logical: `&&` `||`
* `expr . bit` — byte-select: if `bit`'s low bit is 1, take `expr`'s high byte; if 0, take its low byte (an older/alternate spelling of `high`/`low` below)
* Unary prefix: `!expr` (logical not), `~expr` (bitwise not / one's complement), `high expr` (high byte), `low expr` (low byte), `abs(expr)`, `sgn(expr)` (-1/0/1)
* `high`/`low` (and the `.` byte-select operator above) correctly extract a symbol's high/low byte at assemble time even for a relocatable, link-time-resolved label — including across a byte-boundary-crossing offset, e.g. `high (some_label+300)`.
* `relocatable_symbol + N` resolves correctly as of v1.6 whether `N` is a bare numeral or a named `equ` constant — see the "Special Features and Usage Notes" section above for the fix history and the one still-open, unrelated `equ`-aliasing limitation.

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
