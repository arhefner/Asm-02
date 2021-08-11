/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/
#define MAIN

#include "header.h"

typedef struct {
  char opcode[5];
  byte typ;
  byte byte1;
  } OPCODE;

#define OT_0ARG    0
#define OT_1ARG    1
#define OT_LBR     2
#define OT_DB      3
#define OT_DS      4
#define OT_NARG    5
#define OT_EQU     6
#define OT_ORG     7
#define OT_680ARG  8
#define OT_681ARG  9
#define OT_68NARG 10
#define OT_682ARG 11
#define OT_END    12
#define OT_SBR    13
#define OT_PUSH   14
#define OT_POP    15
#define OT_MOV    16

#define OP_LOW    0x62
#define OP_HIGH   0x61
#define OP_DOT    0x51
#define OP_MOD    0x43
#define OP_MUL    0x42
#define OP_DIV    0x41
#define OP_ADD    0x32
#define OP_SUB    0x31
#define OP_GT     0x26
#define OP_LT     0x25
#define OP_GTE    0x24
#define OP_LTE    0x23
#define OP_EQ     0x22
#define OP_NE     0x21
#define OP_AND    0x13
#define OP_OR     0x12
#define OP_XOR    0x11
#define OP_OP     0x08
#define OP_CP     0x09
#define OP_NUM    0x00

OPCODE opcodes[] = {
  { "adc",   OT_0ARG,   ADC   },
  { "adci",  OT_1ARG,   ADCI  },
  { "add",   OT_0ARG,   ADD   },
  { "adi",   OT_1ARG,   ADI   },
  { "and",   OT_0ARG,   AND   },
  { "ani",   OT_1ARG,   ANI   },
  { "b1",    OT_SBR,    B1    },
  { "b2",    OT_SBR,    B2    },
  { "b3",    OT_SBR,    B3    },
  { "b4",    OT_SBR,    B4    },
  { "bdf",   OT_SBR,    BDF   },
  { "bn1",   OT_SBR,    BN1   },
  { "bn2",   OT_SBR,    BN2   },
  { "bn3",   OT_SBR,    BN3   },
  { "bn4",   OT_SBR,    BN4   },
  { "bnf",   OT_SBR,    BNF   },
  { "bnq",   OT_SBR,    BNQ   },
  { "bnz",   OT_SBR,    BNZ   },
  { "bq",    OT_SBR,    BQ    },
  { "br",    OT_SBR,    BR    },
  { "bz",    OT_SBR,    BZ    },
  { "db",    OT_DB,     'B'   },
  { "dw",    OT_DB,     'W'   },
  { "dd",    OT_DB,     'D'   },
  { "ds",    OT_DS,     0     },
  { "dec",   OT_NARG,   DEC   },
  { "dis",   OT_0ARG,   DIS   },
  { "equ",   OT_EQU,    0     },
  { "ghi",   OT_NARG,   GHI   },
  { "glo",   OT_NARG,   GLO   },
  { "idl",   OT_0ARG,   IDL   },
  { "inc",   OT_NARG,   INC   },
  { "inp",   OT_NARG,   INP   },
  { "irx",   OT_0ARG,   IRX   },
  { "lda",   OT_NARG,   LDA   },
  { "lbdf",  OT_LBR,    LBDF  },
  { "lbnf",  OT_LBR,    LBNF  },
  { "lbnq",  OT_LBR,    LBNQ  },
  { "lbnz",  OT_LBR,    LBNZ  },
  { "lbq",   OT_LBR,    LBQ   },
  { "lbr",   OT_LBR,    LBR   },
  { "lbz",   OT_LBR,    LBZ   },
  { "ldi",   OT_1ARG,   LDI   },
  { "ldn",   OT_NARG,   LDN   },
  { "ldx",   OT_0ARG,   LDX   },
  { "ldxa",  OT_0ARG,   LDXA  },
  { "lsdf",  OT_0ARG,   LSDF  },
  { "lsie",  OT_0ARG,   LSIE  },
  { "lskp",  OT_0ARG,   NLBR  },
  { "lsnf",  OT_0ARG,   LSNF  },
  { "lsnq",  OT_0ARG,   LSNQ  },
  { "lsnz",  OT_0ARG,   LSNZ  },
  { "lsq",   OT_0ARG,   LSQ   },
  { "lsz",   OT_0ARG,   LSZ   },
  { "mark",  OT_0ARG,   MARK  },
  { "nbr",   OT_0ARG,   NBR   },
  { "nlbr",  OT_0ARG,   NLBR  },
  { "nop",   OT_0ARG,   NOP   },
  { "or",    OT_0ARG,   OR    },
  { "ori",   OT_1ARG,   ORI   },
  { "out",   OT_NARG,   OUT   },
  { "phi",   OT_NARG,   PHI   },
  { "plo",   OT_NARG,   PLO   },
  { "req",   OT_0ARG,   REQ   },
  { "ret",   OT_0ARG,   RET   },
  { "sav",   OT_0ARG,   SAV   },
  { "sd",    OT_0ARG,   SD    },
  { "sdb",   OT_0ARG,   SDB   },
  { "sdi",   OT_1ARG,   SDI   },
  { "sdbi",  OT_1ARG,   SDBI  },
  { "sep",   OT_NARG,   SEP   },
  { "seq",   OT_0ARG,   SEQ   },
  { "sex",   OT_NARG,   SEX   },
  { "shl",   OT_0ARG,   SHL   },
  { "shlc",  OT_0ARG,   SHLC  },
  { "shr",   OT_0ARG,   SHR   },
  { "shrc",  OT_0ARG,   SHRC  },
  { "skp",   OT_0ARG,   NBR   },
  { "sm",    OT_0ARG,   SM    },
  { "smb",   OT_0ARG,   SMB   },
  { "smbi",  OT_1ARG,   SMBI  },
  { "smi",   OT_1ARG,   SMI   },
  { "str",   OT_NARG,   STR   },
  { "stxd",  OT_0ARG,   STXD  },
  { "xor",   OT_0ARG,   XOR   },
  { "xri",   OT_1ARG,   XRI   },
  { "org",   OT_ORG,    0     },
  { "rldi",  OT_68NARG, 0xc0  },
  { "rlxa",  OT_68NARG, 0x60  },
  { "rsxd",  OT_68NARG, 0xa0  },
  { "dbnz",  OT_682ARG, 0x20  },
  { "rnx",   OT_68NARG, 0xb0  },
  { "dadd",  OT_680ARG, 0xf4  },
  { "dadi",  OT_681ARG, 0xfc  },
  { "dadc",  OT_680ARG, 0x74  },
  { "daci",  OT_681ARG, 0x7c  },
  { "dsm",   OT_680ARG, 0xf7  },
  { "dsmi",  OT_681ARG, 0xff  },
  { "dsmb",  OT_680ARG, 0x77  },
  { "dsbi",  OT_681ARG, 0x7f  },
  { "bci",   OT_681ARG, 0x3e  },
  { "bxi",   OT_681ARG, 0x3f  },
  { "ldc",   OT_680ARG, 0x06  },
  { "gec",   OT_680ARG, 0x08  },
  { "stpc",  OT_680ARG, 0x00  },
  { "dtc",   OT_680ARG, 0x01  },
  { "stm",   OT_680ARG, 0x07  },
  { "scm1",  OT_680ARG, 0x05  },
  { "scm2",  OT_680ARG, 0x03  },
  { "spm1",  OT_680ARG, 0x04  },
  { "spm2",  OT_680ARG, 0x02  },
  { "etq",   OT_680ARG, 0x09  },
  { "xie",   OT_680ARG, 0x0a  },
  { "xid",   OT_680ARG, 0x0b  },
  { "cie",   OT_680ARG, 0x0c  },
  { "cid",   OT_680ARG, 0x0d  },
  { "dsav",  OT_680ARG, 0x76  },
  { "scal",  OT_682ARG, 0x80  },
  { "sret",  OT_680ARG, 0x90  },
  { "end",   OT_END,    0x00  },
  { "push",  OT_PUSH,   0x00  },
  { "pop",   OT_POP,    0x00  },
  { "mov",   OT_MOV,    0x00  },
  { "",      0,         0     },
  };

dword asm_numStack[256];
word asm_nstackSize;
byte asm_tokens[64];
byte asm_numTokens;
char *sourceLine;
word lstCount;

char* trim(char* line) {
  while (*line == ' ' || *line == '\t') line++;
  return line;
  }

void addDefine(char* define, int value, int redefine) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      if (redefine) {
        defineValues[i] = value;
        return;
        }
      printf("***ERROR: Duplicate define: %s\n",define);
      errors++;
      return;
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (int*)malloc(sizeof(int));
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (int*)realloc(defineValues, sizeof(int) * numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(define) + 1);
  strcpy(defines[numDefines-1], define);
  defineValues[numDefines-1] = value;
  }

int getDefine(char* define) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      return defineValues[i];
      }
  return 0;
  }

void delDefine(char* define) {
  int pos;
  int i;
  pos = -1;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) pos = i;
  if (pos < 0) return;
  free(defines[pos]);
  for (i=pos; i<numDefines-1; i++) {
    defines[i] = defines[i+1];
    defineValues[i] = defineValues[i+1];
    }
  numDefines--;
  if (numDefines == 0) {
    free(defines);
    free(defineValues);
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (int*)realloc(defineValues, sizeof(int) * numDefines);
    }
  }

void addLabel(char* label, word value) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      printf("***ERROR: Duplicate label: %s\n",label);
      errors++;
      return;
      }
  numLabels++;
  if (numLabels == 1) {
    labels = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    }
  else {
    labels = (char**)realloc(labels, sizeof(char*) * numLabels);
    labelValues = (word*)realloc(labelValues, sizeof(word) * numLabels);
    }
  labels[numLabels-1] = (char*)malloc(strlen(label) + 1);
  strcpy(labels[numLabels-1], label);
  labelValues[numLabels-1] = value;
  }

word getLabel(char* label) {
  int i;
  if (passNumber == 1) {
    for (i=0; i<numDefines; i++)
      if (strcasecmp(label, defines[i]) == 0)
        return defineValues[i];
    return 0;
    }
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      return labelValues[i];
      }
  for (i=0; i<numDefines; i++)
    if (strcasecmp(label, defines[i]) == 0)
      return defineValues[i];
  printf("***ERROR: Label not found: %s\n",label);
  errors++;
  return 0;
  }

void setLabel(char* label, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      labelValues[i] = value;
      return;
      }
  printf("***ERROR: Label not found: %s\n",label);
  errors++;
  }

void writeOutput() {
  int i;
  byte checksum;
  char outLine[80];
  char temp[16];
  if (outMode == 'R') {
    sprintf(outLine,":%04x",outAddress);
    for (i=0; i<outCount; i++) {
      sprintf(temp," %02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'I') {
    checksum = outCount;
    sprintf(outLine,":%02x",outCount);
    checksum += (outAddress / 256);
    checksum += (outAddress & 0xff);
    sprintf(temp,"%04x00",outAddress);
    strcat(outLine,temp);
    for (i=0; i<outCount; i++) {
      checksum += outBuffer[i];
      sprintf(temp,"%02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    checksum = (checksum ^ 0xff) + 1;
    sprintf(temp,"%02x",checksum);
    strcat(outLine, temp);
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'B') {
//    write(outFile, outBuffer, outCount);
    }
  }

void output(byte value) {
  if (compMode == 'A' && (address < ramStart || address > ramEnd)) {
    printf("***ERROR: Address exceeded available RAM");
    errors++;
    }
  if (compMode == 'O' && (address < romStart || address > romEnd)) {
    printf("***ERROR: Address exceeded available ROM");
    errors++;
    }
  if (passNumber == 1) {
    if (address > highest) highest = address;
    }
  if (passNumber == 2) {
    codeGenerated++;
    if (outMode == 'B') {
      if (address < lowAddress) lowAddress = address;
      if (address > highAddress) highAddress = address;
      memory[address] = value;
      }
    else {
      outBuffer[outCount++] = value;
      if (outCount == 16) {
        writeOutput();
        outCount = 0;
        outAddress = address+1;
        }
      }
    if (createLst != 0 || showList != 0) {
      if (lstCount == 4) {
        if (createLst) {
          fprintf(lstFile,"%s\n",sourceLine);
          fprintf(lstFile,"      ");
          }
        if (showList) {
          printf("%s\n",sourceLine);
          printf("      ");
          }
        }
      else if (lstCount > 4 && (lstCount % 4) == 0) {
        if (createLst) {
          fprintf(lstFile,"\n");
          fprintf(lstFile,"      ");
          }
        if (showList) {
          printf("\n");
          printf("      ");
          }
        }
      if (createLst) fprintf(lstFile,"%02x ",value);
      if (showList) printf("%02x ",value);
      lstCount++;
      }
    }
  address++;
  }

char* asm_convertNumber(char* buffer, dword* value, byte* success) {
  byte ishex;
  dword val1,val2;
  ishex = 0;
  val1 = 0;
  val2 = 0;
  if (*buffer == '\'' && *(buffer+2) == '\'') {
    buffer++;
    *value = *buffer;
    buffer += 2;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '%') {
    buffer++;
    while (*buffer == '1' || *buffer == '0' || *buffer == '_') {
      if (*buffer != '_')
        val1 = (val1 << 1) | (*buffer - '0');
      buffer++;
      }
    *value = val1;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '$') {
    buffer++;
    if ((*buffer >= '0' && *buffer <= '9') ||
        (*buffer >= 'a' && *buffer <= 'f') ||
        (*buffer >= 'A' && *buffer <= 'F'))
      ishex = 0xff;
    else {
      *value = asmAddress;
      *success = 0xff;
      return buffer;
      }
    }
  if (ishex == 0 && (*buffer < '0' || *buffer > '9')) {
    *success = 0;
    return buffer;
    }
  while ((*buffer >= '0' && *buffer <= '9') ||
         (*buffer >= 'a' && *buffer <= 'f') ||
         (*buffer >= 'A' && *buffer <= 'F')) {
      if (*buffer >= '0' && *buffer <= '9') {
        val1 = (val1 * 10) + (*buffer - '0');
        val2 = (val2 << 4) | (*buffer - '0');
        }
      if (*buffer >= 'a' && *buffer <= 'f')
        val2 = (val2 << 4) | (*buffer - 87);
      if (*buffer >= 'A' && *buffer <= 'F')
        val2 = (val2 << 4) | (*buffer - 55);
      buffer++;
    }
  if (*buffer == 'h' || *buffer == 'H') {
    ishex = 0xff;
    buffer++;
    }
  *success = 0xff;
  *value = (ishex != 0) ? val2 : val1;
  return buffer;
  }


int asm_reduce(char last) {
  int op;
  int ret;
  if (asm_numTokens == 0) return 0;
  if (asm_tokens[asm_numTokens-1] != OP_NUM) return 0;
  if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] >= 0x60) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 3;
    ret = 0;
    if (last) ret = -1;
    }
  else if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] == OP_OP) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 3;
    ret = 0;
    if (asm_numTokens > 0 && asm_tokens[asm_numTokens-1] >= 0x60) ret = -1;
    if (last) ret = -1;
    }
  else if (asm_numTokens > 4 && asm_tokens[asm_numTokens-3] >= 0x10 &&
                            asm_tokens[asm_numTokens-4] == OP_NUM) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 5;
    ret = -1;
    }
  else {
    return 0;
    }
  switch (op) {
    case OP_HIGH:
         asm_numStack[asm_nstackSize-1] =
           (asm_numStack[asm_nstackSize-1] & 0xff00) >> 8;
         break;
    case OP_LOW:
         asm_numStack[asm_nstackSize-1] =
           (asm_numStack[asm_nstackSize-1] & 0x00ff);
         break;
    case OP_DOT:
         if (asm_numStack[asm_nstackSize-1] == 0)
           asm_numStack[asm_nstackSize-2] &= 0x00ff;
         else
           asm_numStack[asm_nstackSize-2] >>= 8;
         asm_nstackSize--;
         break;
    case OP_MUL:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] *
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_DIV:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] /
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
    case OP_MOD:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] %
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_ADD:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] +
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_SUB:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] -
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_GT :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] >
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_LT :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] <
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_GTE:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] >=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_LTE:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] <=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_EQ :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] ==
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_NE :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] !=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_AND:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] &
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_OR :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] |
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_XOR:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] ^
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    }
  asm_tokens[asm_numTokens++] = 0;
  asm_tokens[asm_numTokens++] = OP_NUM;
  return ret;
  }

void asm_add(int op) {
  if (asm_tokens[asm_numTokens-1] >= 0x10) {
    }
  while (asm_numTokens > 4 && (op & 0xf0) <= (asm_tokens[asm_numTokens-3] & 0xf0)) {
    asm_reduce(0);
    }
  asm_tokens[asm_numTokens++] = op;
  }

char* asm_evaluate(char* buffer,char useDefines) {
  char term;
  int p;
  char token[64];
  int flag;
  int func;
  int parens;
  byte success;
  dword number;
  char* origLine;
  origLine = buffer;
  parens = 0;
  asm_numTokens = 0;
  asm_nstackSize = 0;
  flag = 1;
  while (*buffer == ' ') buffer++;
  if (*buffer == '-' && (*(buffer+1) < '0' || *(buffer+1) > '9')) {
    asm_tokens[asm_numTokens++] = 0;
    asm_tokens[asm_numTokens++] = OP_NUM;
    asm_tokens[asm_numTokens++] = OP_SUB;
    asm_numStack[asm_nstackSize++] = 0;
    buffer++;
    }
  while (*buffer != 0 && flag) {

    while (*buffer == ' ') buffer++;

    func = -1;
    while (func) {
      func = 0;
      while (*buffer == '(') {
        asm_tokens[asm_numTokens++] = OP_OP;
        parens++;
        buffer++;
        func = -1;
        }
      if (strncasecmp(buffer,"high ",5) == 0) {
         asm_tokens[asm_numTokens++] = OP_HIGH;
         buffer+=5;
         func = -1;
         }
      if (strncasecmp(buffer,"low ",4) == 0) {
         asm_tokens[asm_numTokens++] = OP_LOW;
         buffer+=4;
         func = -1;
         }
      }

    term = 0;

    /* **************************** */
    /* ***** Process constant ***** */
    /* **************************** */
    buffer = asm_convertNumber(buffer, &number, &success);
    if (success != 0) {
      asm_numStack[asm_nstackSize++] = number;
      asm_tokens[asm_numTokens++] = 0;
      asm_tokens[asm_numTokens++] = OP_NUM;
      term = -1;
      }

    if (term == 0) {
      if ((*buffer >= 'a' && *buffer <= 'z') ||
          (*buffer >= 'A' && *buffer <= 'Z')) {
        p = 0;
        while ((*buffer >= 'a' && *buffer <= 'z') ||
               (*buffer >= 'A' && *buffer <= 'Z') ||
               (*buffer >= '0' && *buffer <= '9') ||
                *buffer == '_' || *buffer == '!') {
          token[p++] = *buffer++;
          }
        token[p] = 0;
        if (useDefines == 'Y')
          asm_numStack[asm_nstackSize++] = getDefine(token);
        else
          asm_numStack[asm_nstackSize++] = getLabel(token);
        asm_tokens[asm_numTokens++] = 0;
        asm_tokens[asm_numTokens++] = OP_NUM;
        term = -1;
        }
      }

    if (term == 0) {
      printf("***ERROR: Expression error, invalid term: %s",buffer);
      errors++;
      return buffer;
      }

    while (*buffer == ' ') buffer++;
    while (*buffer == ')' && parens > 0) {
      parens--;
      while (asm_reduce(0)) ;
      buffer++;
      }
    while (*buffer == ' ') buffer++;

    if (*buffer == '+') { asm_add(OP_ADD); buffer++; }
    else if (*buffer == '-') { asm_add(OP_SUB); buffer++; }
    else if (*buffer == '*') { asm_add(OP_MUL); buffer++; }
    else if (*buffer == '/') { asm_add(OP_DIV); buffer++; }
    else if (*buffer == '%') { asm_add(OP_MOD); buffer++; }
    else if (*buffer == '&') { asm_add(OP_AND); buffer++; }
    else if (*buffer == '|') { asm_add(OP_OR); buffer++; }
    else if (*buffer == '^') { asm_add(OP_XOR); buffer++; }
    else if (*buffer == '.') { asm_add(OP_DOT); buffer++; }
    else if (*buffer == '<' && *(buffer+1) == '=') { asm_add(OP_LTE); buffer+=2; }
    else if (*buffer == '>' && *(buffer+1) == '=') { asm_add(OP_GTE); buffer+=2; }
    else if (*buffer == '<' && *(buffer+1) == '>') { asm_add(OP_NE); buffer+=2; }
    else if (*buffer == '<') { asm_add(OP_LT); buffer++; }
    else if (*buffer == '>') { asm_add(OP_GT); buffer++; }
    else if (*buffer == '=' && *(buffer+1) == '=') { asm_add(OP_EQ); buffer+=2; }
    else if (*buffer == '=') { asm_add(OP_EQ); buffer++; }
    else flag = 0;
    }
  while (asm_reduce(-1));
  if (asm_numTokens != 2) {
    printf("***ERROR: Expression error, expression does not reduce to 1 value\n");
    printf(">>> %s\n",origLine);
    printf(">>> %s\n",sourceLine);
    errors++;
    }
  return buffer;
  }

dword processArgs(char* args) {
  args = asm_evaluate(args,'N');
  return asm_numStack[0];
  }

void processDb(char* args,char typ) {
  dword num;
  args = trim(args);
  while (*args != 0) {
    if (*args == '\'' && *(args+2) != '\'') {
      args++;
      while (*args != 0 && *args != '\'')
        output(*args++);
      if (*args == '\'') args++;
      }
    else {
      args = asm_evaluate(args,'N');
      num = asm_numStack[0];
      if (typ == 'B') output(num & 0xff);
      else if (typ == 'W') {
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      else {
        output(((num & 0xff000000) >> 24) & 0xff);
        output(((num & 0x00ff0000) >> 16) & 0xff);
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      }
    args = trim(args);
    if (*args == ',') {
      args++;
      args = trim(args);
      }
    }
  }

void processDs(word arg) {
  address += arg;
  if (passNumber == 2 && outCount > 0) writeOutput();
  outCount = 0;
  }

void processOrg(word arg) {
  if (passNumber == 2 && outCount > 0) writeOutput();
  outCount = 0;
  address = arg;
  outAddress = address;
  }

void Asm(char* line) {
  int   pos;
  char  qt;
  char *orig;
  char  label[32];
  char  opcode[32];
  char  args[128];
  char *pargs;
  char  buffer[256];
  dword  value;
  byte  reg;
  FILE* file;
  int   i;
  orig = line;
  sourceLine = line;
  if (*line == '.') {
    if (strncasecmp(line,".1805",5) == 0) { use1805 = 0xff; return; }
    if (strncasecmp(line,".list",5) == 0) { showList = 0xff; return; }
    if (strncasecmp(line,".sym",4) == 0) { showSymbols = 0xff; return; }
    }
  if (strncasecmp(line,"include ", 8) == 0) {
    sprintf(buffer,"#%s",line);
    strcpy(line,buffer);
    }
  if (numNests > 0) {
    if (strncasecmp(line,"#else",5) == 0 && nests[numNests-1] != 'I') {
      nests[numNests-1] = (nests[numNests-1] == 'Y') ? 'N' : 'Y';
      return;
      }
    if (nests[numNests-1] != 'Y' && strncasecmp(line,"#ifdef",6) == 0) {
      nests[numNests++] = 'I';
      return;
      }
    if (nests[numNests-1] != 'Y' && strncasecmp(line,"#ifndef",7) == 0) {
      nests[numNests++] = 'I';
      return;
      }
    if (nests[numNests-1] != 'Y' && strncasecmp(line,"#if ",4) == 0) {
      nests[numNests++] = 'I';
      return;
      }
    if (strncasecmp(line,"#endif",6) == 0) {
      numNests--;
      if (numNests < 0) {
        printf("***ERROR: #endif without #if");
        errors++;
        }
      return;
      }
    if (nests[numNests-1] != 'Y') return;
    }
  if (*line == '#') {
    if (strncasecmp(line,"#if ",4) == 0) {
      line += 4;
      asm_evaluate(line,'Y');
      if (asm_numStack[0] != 0) {
        nests[numNests++] = 'Y';
        }
      else {
        nests[numNests++] = 'N';
        }
      return;
      }
    if (strncasecmp(line,"#define",7) == 0) {
      line += 7;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      line = trim(line);
      if (*line != 0) i = processArgs(line);
        else i = 1;
      addDefine(label, i, 0);
      return;
      }
    if (strncasecmp(line,"#undef",6) == 0) {
      line += 6;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      line = trim(line);
      i = atoi(line);
      if (i == 0) i = 1;
      delDefine(label);
      return;
      }
    if (strncasecmp(line,"#ifdef",6) == 0) {
      line += 6;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      if (getDefine(label)) {
        nests[numNests++] = 'Y';
        }
      else {
        nests[numNests++] = 'N';
        }
      return;
      }
    if (strncasecmp(line,"#ifndef",7) == 0) {
      line += 7;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      if (getDefine(label)) {
        nests[numNests++] = 'N';
        }
      else {
        nests[numNests++] = 'Y';
        }
      return;
      }
    }

  if (strncasecmp(line, "#include",8) == 0) {
    line += 8;
    while (*line == ' ' || *line == 9) line++;
    file = fopen(line,"r");
    if (file == NULL) {
      printf("Could not open include file: %s\n",line);
      exit(1);
      }
    numLineCount++;
    lineCount[numLineCount] = 0;
    while (fgets(buffer, 256, file) != NULL) {
      while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < 32)
        buffer[strlen(buffer)-1] = 0;
      lineCount[numLineCount]++;
      Asm(buffer);
      }
    fclose(file);
    numLineCount--;
    return;
    }

  asmAddress = address;
  strcpy(label,"");
  strcpy(opcode,"");
  strcpy(args,"");
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_' || *line == '!') {
      label[pos++] = *line++;
      }
    label[pos] = 0;
    if (*line != ':') {
      printf("***ERROR: Invalid label");
      printf("%s\n",orig);
      errors++;
      return;
      }
    line++;
    }
  line = trim(line);
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9')) {
      opcode[pos++] = *line++;
      }
    opcode[pos] = 0;
    }
  line = trim(line);
  pos = 0;
  qt = 0;
  while (((qt == 0 && *line != ';') || qt) && *line != 0) {
    if (*line == '\'') qt = 1 - qt;
    args[pos++] = *line++;
    }
  args[pos] = 0;
  if (passNumber == 1 && strlen(label) > 0) {
    addLabel(label, address);
    }
  if (strlen(opcode) > 0) {
    if (passNumber == 2 && createLst != 0) fprintf(lstFile, "[%5d] %04x: ",lineCount[numLineCount],asmAddress);
    if (passNumber == 2 && showList != 0) printf("[%5d] %04x: ",lineCount[numLineCount],asmAddress);
    lstCount = 0;
    i = 0;
    pos = -1;
    while (pos < 0 && opcodes[i].opcode[0] != 0) {
      if (strcasecmp(opcode, opcodes[i].opcode) == 0) pos = i;
      i++;
      }
    if (pos < 0) {
      printf("***ERROR: Unknown opcode: %s\n",opcode);
      errors++;
      return;
      }
    linesAssembled++;
    switch (opcodes[pos].typ) {
      case OT_0ARG:
           output(opcodes[pos].byte1);
           break;
      case OT_1ARG:
           output(opcodes[pos].byte1);
           output(processArgs(args) & 0xff);
           break;
      case OT_SBR:
           output(opcodes[pos].byte1);
           value = processArgs(args);
           if (passNumber == 2 && (value & 0xff00) != (address & 0xff00)) {
             if (numLineCount == 0)
               printf("[%5d]: Short branch out of page\n",lineCount[numLineCount]);
             else
               printf("<%5d>: Short branch out of page\n",lineCount[numLineCount]);
             errors++;
             }
           output(value & 0xff);
           break;
      case OT_NARG:
           output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
           break;
      case OT_DB:
           processDb(args,opcodes[pos].byte1);
           break;
      case OT_DS:
           processDs(processArgs(args));
           break;
      case OT_ORG:
           value = processArgs(args);
           processOrg(processArgs(args));
           break;
      case OT_EQU:
           value = processArgs(args);
           setLabel(label, value);
           break;
      case OT_LBR:
           value = processArgs(args);
           output(opcodes[pos].byte1);
           output(value/256);
           output(value%256);
           break;
      case OT_680ARG:
           if (use1805 == 0) {
             printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
             errors++;
             }
           output(0x68);
           output(opcodes[pos].byte1);
           break;
      case OT_681ARG:
           if (use1805 == 0) {
             printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
             errors++;
             }
           output(0x68);
           output(opcodes[pos].byte1);
           output(processArgs(args) & 0xff);
           break;
      case OT_682ARG:
           if (use1805 == 0) {
             printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
             errors++;
             }
           output(0x68);
           pargs = asm_evaluate(args,'N');
           output(opcodes[pos].byte1 | (asm_numStack[0] & 0xf));
           pargs = trim(pargs);
           if (*pargs == ',') {
             pargs++;
             pargs = trim(pargs);
             pargs = asm_evaluate(pargs,'N');
             output((asm_numStack[0] & 0xff00) >> 8);
             output(asm_numStack[0] & 0xff);
             }
           else {
             printf("***ERROR: Missing argument\n");
             errors++;
             }
           break;
      case OT_68NARG:
           if (use1805 == 0) {
             printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
             errors++;
             }
           output(0x68);
           output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
           break;
      case OT_END:
           if (passNumber == 1) {
             execAddr = processArgs(args) & 0xffff;
             }
           break;
      case OT_PUSH:
           value = processArgs(args) & 0xf;
           output(GHI | value);
           output(STXD);
           output(GLO | value);
           output(STXD);
           break;
      case OT_POP:
           value = processArgs(args) & 0xf;
           output(IRX);
           output(LDXA);
           output(PLO | value);
           output(LDX);
           output(PHI | value);
           break;
      case OT_MOV:
           pargs = asm_evaluate(args,'N');
           reg = (asm_numStack[0] & 0xf);
           pargs = trim(pargs);
           if (*pargs == ',') {
             pargs++;
             asm_evaluate(pargs,'N');
             value = asm_numStack[0];
             output(LDI);
             output((value & 0xff00) >> 8);
             output(PHI | reg);
             output(LDI);
             output(value & 0x00ff);
             output(PLO | reg);
             }
           else {
             printf("Invalid arguments for MOV\n");
             errors++;
             }
           break;
      default:
           printf("***ERROR: Unknown instruction type: %d\n",opcodes[pos].typ);
           errors++;
           break;
      }
    if (passNumber == 2 && (createLst != 0 || showList != 0)) {
      if (lstCount <= 4) {
        while (lstCount < 4) {
          if (createLst) fprintf(lstFile,"   ");
          if (showList) printf("   ");
          lstCount++;
          }
        if (createLst) fprintf(lstFile,"%s",sourceLine);
        if (showList) printf("%s",sourceLine);
        }
      if (createLst) fprintf(lstFile, "\n");
      if (showList) printf("\n");
      }
    }
  }

word getHex(char* line) {
  word number;
  number = 0;
  while ((*line >= '0' && *line <= '9') ||
         (*line >= 'a' && *line <= 'f') ||
         (*line >= 'A' && *line <= 'F')) {
    if (*line >= '0' && *line <= '9') number = (number << 4) + (*line - '0');
    if (*line >= 'a' && *line <= 'f') number = (number << 4) + (*line - 'a') + 10;
    if (*line >= 'A' && *line <= 'F') number = (number << 4) + (*line - 'A') + 10;
    line++;
    }
  return number;
  }


void processRAM(char* buffer) {
  ramStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -ram\n");
    exit(1);
    }
  buffer++;
  ramEnd = getHex(buffer);
  }

void processROM(char* buffer) {
  romStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -rom\n");
    exit(1);
    }
  buffer++;
  romEnd = getHex(buffer);
  }

void processOption(char* option) {
    if (strcmp(option,"-1805") == 0) use1805 = -1;
    if (strcmp(option,"-b") == 0) outMode = 'B';
    if (strcmp(option,"-i") == 0) outMode = 'I';
    if (strcmp(option,"-r") == 0) outMode = 'R';
    if (strcmp(option,"-l") == 0) showList = -1;
    if (strcmp(option,"-L") == 0) createLst = -1;
    if (strcmp(option,"-s") == 0) showSymbols = -1;
    if (strcmp(option,"-e") == 0) useExtended = -1;
    if (strcmp(option,"-lf") == 0) strcpy(lineEnding,"\n");
    if (strcmp(option,"-cr") == 0) strcpy(lineEnding,"\r");
    if (strcmp(option,"-crlf") == 0) strcpy(lineEnding,"\r\n");
    if (strcmp(option,"-lfcr") == 0) strcpy(lineEnding,"\n\r");
    if (strcmp(option,"-melf") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-pev") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-pev2") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-elf2k") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-mclo") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-mchi") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strcmp(option,"-mchip") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strncmp(option,"-ram=",5) == 0) processRAM(option+5);
    if (strncmp(option,"-rom=",5) == 0) processROM(option+5);
  }

int pass(int p) {
  int i;
  char buffer[256];
  FILE* inFile;
  passNumber = p;
  address = 0;
  outCount = 0;
  outAddress = 0;
  linesAssembled = 0;
  lineCount[0] = 0;
  numLineCount = 0;
  lowAddress = 0xffff;
  highAddress = 0x0000;
  inFile = fopen(sourceFile,"r");
  if (passNumber == 2) {
      if (outMode != 'B') {
      outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
      if (outFile < 0) {
        printf("Could not open output file: %s\n",outName);
        exit(1);
        }
      }
    if (createLst) lstFile = fopen(lstName,"w");
    }
  while (fgets(buffer, 255, inFile) != NULL) {
    for (i=0; i<strlen(buffer); i++)
      if (buffer[i] < 32) buffer[i] = 0;
    lineCount[numLineCount]++;
    Asm(buffer);
    }
  if (passNumber == 2 && outCount > 0) writeOutput();
  if (passNumber == 2 && outMode != 'B') close(outFile);
  if (createLst) fclose(lstFile);
  if (numNests > 0) printf("#ifdef without #endif\n");
  for (i=0; i<numDefines; i++)
    free(defines[i]);
  if (numDefines > 0) {
    free(defines);
    free(defineValues);
    }
  return 0;
  }

int main(int argc, char** argv) {
  int i;
  createLst = 0;
  outMode = 'R';
  ramStart = 0x0000;
  ramEnd = 0xffff;
  romStart = 0xffff;
  romEnd = 0xffff;
  showList = 0;
  showSymbols = 0;
  use1805 = 0;
  useExtended = 0;
  numDefines = 0;
  numLabels = 0;
  errors = 0;
  strcpy(lineEnding,"\n");
  strcpy(sourceFile,"");
  i = 0;
  while (i < argc) {
    if (argv[i][0] != '-') {
      strcpy(sourceFile, argv[i]);
      }
    else processOption(argv[i]);
    i++;
    }
  strcpy(baseName, sourceFile);
  for (i=0; i<strlen(baseName); i++)
    if (baseName[i] == '.') baseName[i] = 0;
  strcpy(outName,baseName);
  switch (outMode) {
    case 'R': strcat(outName, ".prg"); break;
    case 'I': strcat(outName, ".hex"); break;
    case 'B': strcat(outName, ".bin"); break;
    }
  strcpy(lstName,baseName);
  strcat(lstName,".lst");
  addLabel("r0",0);
  addLabel("r1",1);
  addLabel("r2",2);
  addLabel("r3",3);
  addLabel("r4",4);
  addLabel("r5",5);
  addLabel("r6",6);
  addLabel("r7",7);
  addLabel("r8",8);
  addLabel("r9",9);
  addLabel("r10",10);
  addLabel("r11",11);
  addLabel("r12",12);
  addLabel("r13",13);
  addLabel("r14",14);
  addLabel("r15",15);
  addLabel("ra",10);
  addLabel("rb",11);
  addLabel("rc",12);
  addLabel("rd",13);
  addLabel("re",14);
  addLabel("rf",15);

  for (i=0; i<argc; i++) {
    if (strncmp(argv[i],"-D",2) == 0) {
      addDefine(argv[i]+2,1,0);
      }
    }
  i = pass(1);
  numDefines = 0;
  if (i == 0 && errors == 0) {
    for (i=0; i<argc; i++) {
      if (strncmp(argv[i],"-D",2) == 0) {
        addDefine(argv[i]+2,1,0);
        }
      }
    i = pass(2);
    if (outMode == 'B' && i == 0 && errors == 0) {
      outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
      if (outFile < 0) {
        printf("Could not open output file: %s\n",outName);
        exit(1);
        }
      write(outFile, memory+lowAddress, (highAddress-lowAddress) + 1);
      close(outFile);
      }
    }
  else printf("Errors during pass 1, aborting pass 2\n");

  printf("\n");
  printf("Lines Assembled   : %d\n",linesAssembled);
  printf("Code Generated    : %d\n",codeGenerated);
  printf("Errors            : %d\n",errors);
  printf("\n");

  if (showSymbols) {
    printf("Symbols:\n");
    for (i=22; i<numLabels; i++)
      printf("  %04x  %s\n",labelValues[i],labels[i]);
    }

  return 0;
  }

