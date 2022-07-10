#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define localtime_r(X,Y) (localtime_s(Y,X))
#else
#include <unistd.h>
#include <sys/time.h>
#define O_BINARY 0
#endif

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#define IDL      0x00
#define LDN      0x00
#define INC      0x10
#define DEC      0x20
#define BR       0x30
#define BQ       0x31
#define BZ       0x32
#define BDF      0x33
#define B1       0x34
#define B2       0x35
#define B3       0x36
#define B4       0x37
#define NBR      0x38
#define BNQ      0x39
#define BNZ      0x3a
#define BNF      0x3b
#define BN1      0x3c
#define BN2      0x3d
#define BN3      0x3e
#define BN4      0x3f
#define LDA      0x40
#define STR      0x50
#define IRX      0x60
#define OUT      0x60
#define INP      0x68
#define RET      0x70
#define DIS      0x71
#define LDXA     0x72
#define STXD     0x73
#define ADC      0x74
#define SDB      0x75
#define SHRC     0x76
#define SMB      0x77
#define SAV      0x78
#define MARK     0x79
#define REQ      0x7a
#define SEQ      0x7b
#define ADCI     0x7c
#define SDBI     0x7d
#define SHLC     0x7e
#define SMBI     0x7f
#define GLO      0x80
#define GHI      0x90
#define PLO      0xa0
#define PHI      0xb0
#define LBR      0xc0
#define LBQ      0xc1
#define LBZ      0xc2
#define LBDF     0xc3
#define NOP      0xc4
#define LSNQ     0xc5
#define LSNZ     0xc6
#define LSNF     0xc7
#define NLBR     0xc8
#define LSKP     0xc8
#define LBNQ     0xc9
#define LBNZ     0xca
#define LBNF     0xcb
#define LSIE     0xcc
#define LSQ      0xcd
#define LSZ      0xce
#define LSDF     0xcf
#define SEP      0xd0
#define SEX      0xe0
#define LDX      0xf0
#define OR       0xf1
#define AND      0xf2
#define XOR      0xf3
#define ADD      0xf4
#define SD       0xf5
#define SHR      0xf6
#define SM       0xf7
#define LDI      0xf8
#define ORI      0xf9
#define ANI      0xfa
#define XRI      0xfb
#define ADI      0xfc
#define SDI      0xfd
#define SHL      0xfe
#define SMI      0xff
#define R0       0x00
#define R1       0x01
#define R2       0x02
#define R3       0x03
#define R4       0x04
#define R5       0x05
#define R6       0x06
#define R7       0x07
#define R8       0x08
#define R9       0x09
#define RA       0x0a
#define RB       0x0b
#define RC       0x0c
#define RD       0x0d
#define RE       0x0e
#define RF       0x0f

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int   dword;

typedef union {
  float f;
  dword i;
  } FTOI;

LINK char** defines;
LINK char** defineValues;
LINK int    numDefines;
LINK char** clDefines;
LINK char** clDefineValues;
LINK int    numClDefines;
LINK char** labels;
LINK char** labelProcs;
LINK word*  labelValues;
LINK char   module[128];
LINK int    numLabels;
LINK word   asmAddress;
LINK char   nests[10];
LINK int    numNests;
LINK char** ops;
LINK char** arglist;
LINK char** translation;
LINK int    numOps;
LINK int   *externals;
LINK int    numExternals;
LINK int    usedReference;
LINK char   referenceType;
LINK byte   referenceLowOffset;
LINK word   fixups[10000];
LINK char   fixupTypes[10000];
LINK byte   fixupLowOffset[10000];
LINK int    numFixups;
LINK int    usedLocal;

LINK word   address;
LINK int    asmFile;
LINK char   asmName[64];
LINK char   baseName[64];
LINK char   buffer[2048];
LINK int    buildMonth;
LINK int    buildDay;
LINK int    buildYear;
LINK int    buildHour;
LINK int    buildMinute;
LINK int    buildSecond;
LINK int    buildNumber;
LINK word   codeGenerated;
LINK char   compMode;
LINK char   createLst;
LINK int    errors;
LINK word   execAddr;
LINK word   highest;
LINK word   highAddress;
LINK char **incPath;
LINK int    numIncPath;
LINK int    inProc;
LINK char   lineEnding[3];
LINK int    linesAssembled;
LINK char   listLine[256];
LINK word   lowAddress;
LINK FILE  *lstFile;
LINK char   lstName[64];
LINK byte   memory[65536];
LINK word   outAddress;
LINK byte   outBuffer[16];
LINK byte   outCount;
LINK int    outFile;
LINK char   outMode;
LINK char   outName[64];
LINK int    passNumber;
LINK word   ramEnd;
LINK word   ramStart;
LINK word   romEnd;
LINK word   romStart;
LINK char   showAsm;
LINK char   showList;
LINK char   showSymbols;
LINK char **sourceFiles;
LINK int    suppression;
LINK int    numSourceFiles;
LINK char   use1805;
LINK byte   useAsm;
LINK byte   useExtended;

LINK FILE  *sourceFile[100];
LINK int    lineNumber[100];
LINK int    fileNumber;



#endif
