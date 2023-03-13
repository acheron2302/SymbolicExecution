/* Copyright 2017 - 2023 R. Thomas
 * Copyright 2017 - 2023 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIEF_ELF_RELOCATION_SIZES_H_
#define LIEF_ELF_RELOCATION_SIZES_H_

#include <map>
#include <cstdint>
#include <map>

#include "LIEF/ELF/enums.hpp"
#define CONST_MAP(KEY, VAL, NUM) static const std::map<KEY, VAL>

namespace LIEF {
namespace ELF {

CONST_MAP(RELOC_x86_64, uint32_t, 43) relocation_x86_64_sizes {
  {RELOC_x86_64::R_X86_64_NONE,             0 },
  {RELOC_x86_64::R_X86_64_64,              64 },
  {RELOC_x86_64::R_X86_64_PC32,            32 },
  {RELOC_x86_64::R_X86_64_GOT32,           32 },
  {RELOC_x86_64::R_X86_64_PLT32,           32 },
  {RELOC_x86_64::R_X86_64_COPY,            32 },
  {RELOC_x86_64::R_X86_64_GLOB_DAT,        64 },
  {RELOC_x86_64::R_X86_64_JUMP_SLOT,       64 },
  {RELOC_x86_64::R_X86_64_RELATIVE,        64 },
  {RELOC_x86_64::R_X86_64_GOTPCREL,        32 },
  {RELOC_x86_64::R_X86_64_32,              32 },
  {RELOC_x86_64::R_X86_64_32S,             32 },
  {RELOC_x86_64::R_X86_64_16,              16 },
  {RELOC_x86_64::R_X86_64_PC16,            16 },
  {RELOC_x86_64::R_X86_64_8,                8 },
  {RELOC_x86_64::R_X86_64_PC8,              8 },
  {RELOC_x86_64::R_X86_64_DTPMOD64,        64 },
  {RELOC_x86_64::R_X86_64_DTPOFF64,        64 },
  {RELOC_x86_64::R_X86_64_TPOFF64,         64 },
  {RELOC_x86_64::R_X86_64_TLSGD,           32 },
  {RELOC_x86_64::R_X86_64_TLSLD,           32 },
  {RELOC_x86_64::R_X86_64_DTPOFF32,        32 },
  {RELOC_x86_64::R_X86_64_GOTTPOFF,        32 },
  {RELOC_x86_64::R_X86_64_TPOFF32,         32 },
  {RELOC_x86_64::R_X86_64_PC64,            64 },
  {RELOC_x86_64::R_X86_64_GOTOFF64,        64 },
  {RELOC_x86_64::R_X86_64_GOTPC32,         32 },
  {RELOC_x86_64::R_X86_64_GOT64,           64 },
  {RELOC_x86_64::R_X86_64_GOTPCREL64,      64 },
  {RELOC_x86_64::R_X86_64_GOTPC64,         64 },
  {RELOC_x86_64::R_X86_64_GOTPLT64,        64 },
  {RELOC_x86_64::R_X86_64_PLTOFF64,        64 },
  {RELOC_x86_64::R_X86_64_SIZE32,          32 },
  {RELOC_x86_64::R_X86_64_SIZE64,          64 },
  {RELOC_x86_64::R_X86_64_GOTPC32_TLSDESC, 32 },
  {RELOC_x86_64::R_X86_64_TLSDESC_CALL,     0 },
  {RELOC_x86_64::R_X86_64_TLSDESC,         64 },
  {RELOC_x86_64::R_X86_64_IRELATIVE,       64 },
  {RELOC_x86_64::R_X86_64_RELATIVE64,      64 },
  {RELOC_x86_64::R_X86_64_PC32_BND,        32 },
  {RELOC_x86_64::R_X86_64_PLT32_BND,       32 },
  {RELOC_x86_64::R_X86_64_GOTPCRELX,       32 },
  {RELOC_x86_64::R_X86_64_REX_GOTPCRELX,   32 },
};

CONST_MAP(RELOC_i386, uint32_t, 40) relocation_i386_sizes {
  {RELOC_i386::R_386_NONE,            0 },
  {RELOC_i386::R_386_32,             32 },
  {RELOC_i386::R_386_PC32,           32 },
  {RELOC_i386::R_386_GOT32,          32 },
  {RELOC_i386::R_386_PLT32,          32 },
  {RELOC_i386::R_386_COPY,           32 },
  {RELOC_i386::R_386_GLOB_DAT,       32 },
  {RELOC_i386::R_386_JUMP_SLOT,      32 },
  {RELOC_i386::R_386_RELATIVE,       32 },
  {RELOC_i386::R_386_GOTOFF,         32 },
  {RELOC_i386::R_386_GOTPC,          32 },
  {RELOC_i386::R_386_32PLT,          32 },
  {RELOC_i386::R_386_TLS_TPOFF,      32 },
  {RELOC_i386::R_386_TLS_IE,         32 },
  {RELOC_i386::R_386_TLS_GOTIE,      32 },
  {RELOC_i386::R_386_TLS_LE,         32 },
  {RELOC_i386::R_386_TLS_GD,         32 },
  {RELOC_i386::R_386_TLS_LDM,        32 },
  {RELOC_i386::R_386_16,             16 },
  {RELOC_i386::R_386_PC16,           16 },
  {RELOC_i386::R_386_8,               8 },
  {RELOC_i386::R_386_PC8,             8 },
  {RELOC_i386::R_386_TLS_GD_32,      32 },
  {RELOC_i386::R_386_TLS_GD_PUSH,    32 },
  {RELOC_i386::R_386_TLS_GD_CALL,    32 },
  {RELOC_i386::R_386_TLS_GD_POP,     32 },
  {RELOC_i386::R_386_TLS_LDM_32,     32 },
  {RELOC_i386::R_386_TLS_LDM_PUSH,   32 },
  {RELOC_i386::R_386_TLS_LDM_CALL,    0 },
  {RELOC_i386::R_386_TLS_LDM_POP,    32 },
  {RELOC_i386::R_386_TLS_LDO_32,     32 },
  {RELOC_i386::R_386_TLS_IE_32,      32 },
  {RELOC_i386::R_386_TLS_LE_32,      32 },
  {RELOC_i386::R_386_TLS_DTPMOD32,   32 },
  {RELOC_i386::R_386_TLS_DTPOFF32,   32 },
  {RELOC_i386::R_386_TLS_TPOFF32,    32 },
  {RELOC_i386::R_386_TLS_GOTDESC,    32 },
  {RELOC_i386::R_386_TLS_DESC_CALL,  32 },
  {RELOC_i386::R_386_TLS_DESC,       32 },
  {RELOC_i386::R_386_IRELATIVE,      32 },
};

// From https://github.com/gittup/binutils/blob/gittup/bfd/elf32-arm.c#L75
CONST_MAP(RELOC_ARM, uint32_t, 138) relocation_ARM_sizes {
  {RELOC_ARM::R_ARM_NONE,                    0 },
  {RELOC_ARM::R_ARM_PC24,                   24 },
  {RELOC_ARM::R_ARM_ABS32,                  32 },
  {RELOC_ARM::R_ARM_REL32,                  32 },
  {RELOC_ARM::R_ARM_LDR_PC_G0,              32 },
  {RELOC_ARM::R_ARM_ABS16,                  16 },
  {RELOC_ARM::R_ARM_ABS12,                  12 },
  {RELOC_ARM::R_ARM_THM_ABS5,                5 },
  {RELOC_ARM::R_ARM_ABS8,                    8 },
  {RELOC_ARM::R_ARM_SBREL32,                32 },
  {RELOC_ARM::R_ARM_THM_CALL,               25 },
  {RELOC_ARM::R_ARM_THM_PC8,                 8 },
  {RELOC_ARM::R_ARM_BREL_ADJ,               32 },
  {RELOC_ARM::R_ARM_TLS_DESC,                0 },
  {RELOC_ARM::R_ARM_THM_SWI8,                0 },
  {RELOC_ARM::R_ARM_XPC25,                  25 },
  {RELOC_ARM::R_ARM_THM_XPC22,              22 },
  {RELOC_ARM::R_ARM_TLS_DTPMOD32,           32 },
  {RELOC_ARM::R_ARM_TLS_DTPOFF32,           32 },
  {RELOC_ARM::R_ARM_TLS_TPOFF32,            32 },
  {RELOC_ARM::R_ARM_COPY,                   32 },
  {RELOC_ARM::R_ARM_GLOB_DAT,               32 },
  {RELOC_ARM::R_ARM_JUMP_SLOT,              32 },
  {RELOC_ARM::R_ARM_RELATIVE,               32 },
  {RELOC_ARM::R_ARM_GOTOFF32,               32 },
  {RELOC_ARM::R_ARM_BASE_PREL,              32 },
  {RELOC_ARM::R_ARM_GOT_BREL,               32 },
  {RELOC_ARM::R_ARM_PLT32,                  24 },
  {RELOC_ARM::R_ARM_CALL,                   24 },
  {RELOC_ARM::R_ARM_JUMP24,                 24 },
  {RELOC_ARM::R_ARM_THM_JUMP24,             24 },
  {RELOC_ARM::R_ARM_BASE_ABS,               21 },
  {RELOC_ARM::R_ARM_ALU_PCREL_7_0,          12 },
  {RELOC_ARM::R_ARM_ALU_PCREL_15_8,         12 },
  {RELOC_ARM::R_ARM_ALU_PCREL_23_15,        12 },
  {RELOC_ARM::R_ARM_LDR_SBREL_11_0_NC,      12 },
  {RELOC_ARM::R_ARM_ALU_SBREL_19_12_NC,      8 },
  {RELOC_ARM::R_ARM_ALU_SBREL_27_20_CK,      8 },
  {RELOC_ARM::R_ARM_TARGET1,                32 },
  {RELOC_ARM::R_ARM_SBREL31,                32 },
  {RELOC_ARM::R_ARM_V4BX,                   32 },
  {RELOC_ARM::R_ARM_TARGET2,                32 },
  {RELOC_ARM::R_ARM_PREL31,                 31 },
  {RELOC_ARM::R_ARM_MOVW_ABS_NC,            16 },
  {RELOC_ARM::R_ARM_MOVT_ABS,               16 },
  {RELOC_ARM::R_ARM_MOVW_PREL_NC,           16 },
  {RELOC_ARM::R_ARM_MOVT_PREL,              16 },
  {RELOC_ARM::R_ARM_THM_MOVW_ABS_NC,        16 },
  {RELOC_ARM::R_ARM_THM_MOVT_ABS,           16 },
  {RELOC_ARM::R_ARM_THM_MOVW_PREL_NC,       16 },
  {RELOC_ARM::R_ARM_THM_MOVT_PREL,          16 },
  {RELOC_ARM::R_ARM_THM_JUMP19,             19 },
  {RELOC_ARM::R_ARM_THM_JUMP6,               6 },
  {RELOC_ARM::R_ARM_THM_ALU_PREL_11_0,      13 },
  {RELOC_ARM::R_ARM_THM_PC12,               13 },
  {RELOC_ARM::R_ARM_ABS32_NOI,              32 },
  {RELOC_ARM::R_ARM_REL32_NOI,              32 },
  {RELOC_ARM::R_ARM_ALU_PC_G0_NC,           32 },
  {RELOC_ARM::R_ARM_ALU_PC_G0,              32 },
  {RELOC_ARM::R_ARM_ALU_PC_G1_NC,           32 },
  {RELOC_ARM::R_ARM_ALU_PC_G1,              32 },
  {RELOC_ARM::R_ARM_ALU_PC_G2,              32 },
  {RELOC_ARM::R_ARM_LDR_PC_G1,              32 },
  {RELOC_ARM::R_ARM_LDR_PC_G2,              32 },
  {RELOC_ARM::R_ARM_LDRS_PC_G0,             32 },
  {RELOC_ARM::R_ARM_LDRS_PC_G1,             32 },
  {RELOC_ARM::R_ARM_LDRS_PC_G2,             32 },
  {RELOC_ARM::R_ARM_LDC_PC_G0,              32 },
  {RELOC_ARM::R_ARM_LDC_PC_G1,              32 },
  {RELOC_ARM::R_ARM_LDC_PC_G2,              32 },
  {RELOC_ARM::R_ARM_ALU_SB_G0_NC,           32 },
  {RELOC_ARM::R_ARM_ALU_SB_G0,              32 },
  {RELOC_ARM::R_ARM_ALU_SB_G1_NC,           32 },
  {RELOC_ARM::R_ARM_ALU_SB_G1,              32 },
  {RELOC_ARM::R_ARM_ALU_SB_G2,              32 },
  {RELOC_ARM::R_ARM_LDR_SB_G0,              32 },
  {RELOC_ARM::R_ARM_LDR_SB_G1,              32 },
  {RELOC_ARM::R_ARM_LDR_SB_G2,              32 },
  {RELOC_ARM::R_ARM_LDRS_SB_G0,             32 },
  {RELOC_ARM::R_ARM_LDRS_SB_G1,             32 },
  {RELOC_ARM::R_ARM_LDRS_SB_G2,             32 },
  {RELOC_ARM::R_ARM_LDC_SB_G0,              32 },
  {RELOC_ARM::R_ARM_LDC_SB_G1,              32 },
  {RELOC_ARM::R_ARM_LDC_SB_G2,              32 },
  {RELOC_ARM::R_ARM_MOVW_BREL_NC,           16 },
  {RELOC_ARM::R_ARM_MOVT_BREL,              16 },
  {RELOC_ARM::R_ARM_MOVW_BREL,              16 },
  {RELOC_ARM::R_ARM_THM_MOVW_BREL_NC,       16 },
  {RELOC_ARM::R_ARM_THM_MOVT_BREL,          16 },
  {RELOC_ARM::R_ARM_THM_MOVW_BREL,          16 },
  {RELOC_ARM::R_ARM_TLS_GOTDESC,             0 },
  {RELOC_ARM::R_ARM_TLS_CALL,                0 },
  {RELOC_ARM::R_ARM_TLS_DESCSEQ,             0 },
  {RELOC_ARM::R_ARM_THM_TLS_CALL,            0 },
  {RELOC_ARM::R_ARM_PLT32_ABS,              32 },
  {RELOC_ARM::R_ARM_GOT_ABS,                32 },
  {RELOC_ARM::R_ARM_GOT_PREL,               32 },
  {RELOC_ARM::R_ARM_GOT_BREL12,             12 },
  {RELOC_ARM::R_ARM_GOTOFF12,               12 },
  {RELOC_ARM::R_ARM_GOTRELAX,               12 },
  {RELOC_ARM::R_ARM_GNU_VTENTRY,             0 },
  {RELOC_ARM::R_ARM_GNU_VTINHERIT,           0 },
  {RELOC_ARM::R_ARM_THM_JUMP11,             11 },
  {RELOC_ARM::R_ARM_THM_JUMP8,               8 },
  {RELOC_ARM::R_ARM_TLS_GD32,               32 },
  {RELOC_ARM::R_ARM_TLS_LDM32,              32 },
  {RELOC_ARM::R_ARM_TLS_LDO32,              32 },
  {RELOC_ARM::R_ARM_TLS_IE32,               32 },
  {RELOC_ARM::R_ARM_TLS_LE32,               32 },
  {RELOC_ARM::R_ARM_TLS_LDO12,              12 },
  {RELOC_ARM::R_ARM_TLS_LE12,               12 },
  {RELOC_ARM::R_ARM_TLS_IE12GP,             12 },
  {RELOC_ARM::R_ARM_PRIVATE_0,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_1,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_2,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_3,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_4,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_5,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_6,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_7,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_8,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_9,               0 },
  {RELOC_ARM::R_ARM_PRIVATE_10,              0 },
  {RELOC_ARM::R_ARM_PRIVATE_11,              0 },
  {RELOC_ARM::R_ARM_PRIVATE_12,              0 },
  {RELOC_ARM::R_ARM_PRIVATE_13,              0 },
  {RELOC_ARM::R_ARM_PRIVATE_14,              0 },
  {RELOC_ARM::R_ARM_PRIVATE_15,              0 },
  {RELOC_ARM::R_ARM_ME_TOO,                  0 },
  {RELOC_ARM::R_ARM_THM_TLS_DESCSEQ16,       0 },
  {RELOC_ARM::R_ARM_THM_TLS_DESCSEQ32,       0 },
  {RELOC_ARM::R_ARM_IRELATIVE,               0 },
  {RELOC_ARM::R_ARM_RXPC25,                 25 },
  {RELOC_ARM::R_ARM_RSBREL32,               32 },
  {RELOC_ARM::R_ARM_THM_RPC22,              22 },
  {RELOC_ARM::R_ARM_RREL32,                 32 },
  {RELOC_ARM::R_ARM_RPC24,                  24 },
  {RELOC_ARM::R_ARM_RBASE,                   0 },
};

CONST_MAP(RELOC_AARCH64, uint32_t, 123) relocation_AARCH64_sizes {
  { RELOC_AARCH64::R_AARCH64_NONE,                          0 },
  { RELOC_AARCH64::R_AARCH64_ABS64,                        64 },
  { RELOC_AARCH64::R_AARCH64_ABS32,                        32 },
  { RELOC_AARCH64::R_AARCH64_ABS16,                        16 },
  { RELOC_AARCH64::R_AARCH64_PREL64,                       64 },
  { RELOC_AARCH64::R_AARCH64_PREL32,                       32 },
  { RELOC_AARCH64::R_AARCH64_PREL16,                       16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G0,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G0_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G1,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G1_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G2,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G2_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_UABS_G3,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_SABS_G0,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_SABS_G1,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_SABS_G2,                 16 },
  { RELOC_AARCH64::R_AARCH64_LD_PREL_LO19,                 19 },
  { RELOC_AARCH64::R_AARCH64_ADR_PREL_LO21,                21 },
  { RELOC_AARCH64::R_AARCH64_ADR_PREL_PG_HI21,             21 },
  { RELOC_AARCH64::R_AARCH64_ADR_PREL_PG_HI21_NC,          21 },
  { RELOC_AARCH64::R_AARCH64_ADD_ABS_LO12_NC,              12 },
  { RELOC_AARCH64::R_AARCH64_LDST8_ABS_LO12_NC,            12 },
  { RELOC_AARCH64::R_AARCH64_TSTBR14,                      14 },
  { RELOC_AARCH64::R_AARCH64_CONDBR19,                     19 },
  { RELOC_AARCH64::R_AARCH64_JUMP26,                       26 },
  { RELOC_AARCH64::R_AARCH64_CALL26,                       26 },
  { RELOC_AARCH64::R_AARCH64_LDST16_ABS_LO12_NC,           12 },
  { RELOC_AARCH64::R_AARCH64_LDST32_ABS_LO12_NC,           12 },
  { RELOC_AARCH64::R_AARCH64_LDST64_ABS_LO12_NC,           12 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G0,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G0_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G1,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G1_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G2,                 16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G2_NC,              16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_PREL_G3,                 16 },
  { RELOC_AARCH64::R_AARCH64_LDST128_ABS_LO12_NC,          12 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G0,               16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G0_NC,            16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G1,               16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G1_NC,            16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G2,               16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G2_NC,            16 },
  { RELOC_AARCH64::R_AARCH64_MOVW_GOTOFF_G3,               16 },
  { RELOC_AARCH64::R_AARCH64_GOTREL64,                     64 },
  { RELOC_AARCH64::R_AARCH64_GOTREL32,                     64 },
  { RELOC_AARCH64::R_AARCH64_GOT_LD_PREL19,                19 },
  { RELOC_AARCH64::R_AARCH64_LD64_GOTOFF_LO15,             15 },
  { RELOC_AARCH64::R_AARCH64_ADR_GOT_PAGE,                 21 },
  { RELOC_AARCH64::R_AARCH64_LD64_GOT_LO12_NC,             12 },
  { RELOC_AARCH64::R_AARCH64_LD64_GOTPAGE_LO15,            15 },
  { RELOC_AARCH64::R_AARCH64_TLSGD_ADR_PREL21,             21 },
  { RELOC_AARCH64::R_AARCH64_TLSGD_ADR_PAGE21,             21 },
  { RELOC_AARCH64::R_AARCH64_TLSGD_ADD_LO12_NC,            12 },
  { RELOC_AARCH64::R_AARCH64_TLSGD_MOVW_G1,                16 },
  { RELOC_AARCH64::R_AARCH64_TLSGD_MOVW_G0_NC,             16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADR_PREL21,             21 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADR_PAGE21,             21 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADD_LO12_NC,             0 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_G1,                 0 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_G0_NC,              0 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LD_PREL19,              19 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_DTPREL_G2,         16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_DTPREL_G1,         16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC,      16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_DTPREL_G0,         16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC,      16 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADD_DTPREL_HI12,        12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADD_DTPREL_LO12,        12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC,     12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST8_DTPREL_LO12,      12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC,   12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST16_DTPREL_LO12,     12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC,  12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST32_DTPREL_LO12,     12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC,  12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST64_DTPREL_LO12,     12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC,  12 },
  { RELOC_AARCH64::R_AARCH64_TLSIE_MOVW_GOTTPREL_G1,       16 },
  { RELOC_AARCH64::R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC,    16 },
  { RELOC_AARCH64::R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21,    21 },
  { RELOC_AARCH64::R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC,  12 },
  { RELOC_AARCH64::R_AARCH64_TLSIE_LD_GOTTPREL_PREL19,     19 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_MOVW_TPREL_G2,          16 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_MOVW_TPREL_G1,          16 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_MOVW_TPREL_G1_NC,       16 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_MOVW_TPREL_G0,          16 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_MOVW_TPREL_G0_NC,       16 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_ADD_TPREL_HI12,         12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_ADD_TPREL_LO12,         12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_ADD_TPREL_LO12_NC,      12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST8_TPREL_LO12,       12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC,    12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST16_TPREL_LO12,      12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC,   12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST32_TPREL_LO12,      12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC,   12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST64_TPREL_LO12,      12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC,   12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_LD_PREL19,            19 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_ADR_PREL21,           21 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_ADR_PAGE21,           21 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_LD64_LO12_NC,         12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_ADD_LO12_NC,          12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_OFF_G1,               12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_OFF_G0_NC,            12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_LDR,                  12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_ADD,                  12 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC_CALL,                 12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST128_TPREL_LO12,     12 },
  { RELOC_AARCH64::R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC,  12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST128_DTPREL_LO12,    12 },
  { RELOC_AARCH64::R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC, 12 },
  { RELOC_AARCH64::R_AARCH64_COPY,                         64 },
  { RELOC_AARCH64::R_AARCH64_GLOB_DAT,                     64 },
  { RELOC_AARCH64::R_AARCH64_JUMP_SLOT,                    64 },
  { RELOC_AARCH64::R_AARCH64_RELATIVE,                     64 },
  { RELOC_AARCH64::R_AARCH64_TLS_DTPREL64,                 64 },
  { RELOC_AARCH64::R_AARCH64_TLS_DTPMOD64,                 64 },
  { RELOC_AARCH64::R_AARCH64_TLS_TPREL64,                  64 },
  { RELOC_AARCH64::R_AARCH64_TLSDESC,                      64 },
  { RELOC_AARCH64::R_AARCH64_IRELATIVE,                    64 },
};

CONST_MAP(RELOC_POWERPC32, uint32_t, 57) relocation_PPC_sizes {
  { RELOC_POWERPC32::R_PPC_NONE,              0 },
  { RELOC_POWERPC32::R_PPC_ADDR32,            32 },
  { RELOC_POWERPC32::R_PPC_ADDR24,            32 },
  { RELOC_POWERPC32::R_PPC_ADDR16,            16 },
  { RELOC_POWERPC32::R_PPC_ADDR16_LO,         16 },
  { RELOC_POWERPC32::R_PPC_ADDR16_HI,         16 },
  { RELOC_POWERPC32::R_PPC_ADDR16_HA,         16 },
  { RELOC_POWERPC32::R_PPC_ADDR14,            32 },
  { RELOC_POWERPC32::R_PPC_ADDR14_BRTAKEN,    32 },
  { RELOC_POWERPC32::R_PPC_ADDR14_BRNTAKEN,   32 },
  { RELOC_POWERPC32::R_PPC_REL24,             32 },
  { RELOC_POWERPC32::R_PPC_REL14,             32 },
  { RELOC_POWERPC32::R_PPC_REL14_BRTAKEN,     32 },
  { RELOC_POWERPC32::R_PPC_REL14_BRNTAKEN,    32 },
  { RELOC_POWERPC32::R_PPC_GOT16,             16 },
  { RELOC_POWERPC32::R_PPC_GOT16_LO,          16 },
  { RELOC_POWERPC32::R_PPC_GOT16_HI,          16 },
  { RELOC_POWERPC32::R_PPC_GOT16_HA,          16 },
  { RELOC_POWERPC32::R_PPC_PLTREL24,          32 },
  { RELOC_POWERPC32::R_PPC_JMP_SLOT,          0 },
  { RELOC_POWERPC32::R_PPC_RELATIVE,          32 },
  { RELOC_POWERPC32::R_PPC_LOCAL24PC,         32 },
  { RELOC_POWERPC32::R_PPC_REL32,             32 },
  { RELOC_POWERPC32::R_PPC_TLS,               32 },
  { RELOC_POWERPC32::R_PPC_DTPMOD32,          32 },
  { RELOC_POWERPC32::R_PPC_TPREL16,           16 },
  { RELOC_POWERPC32::R_PPC_TPREL16_LO,        16 },
  { RELOC_POWERPC32::R_PPC_TPREL16_HI,        16 },
  { RELOC_POWERPC32::R_PPC_TPREL16_HA,        16 },
  { RELOC_POWERPC32::R_PPC_TPREL32,           32 },
  { RELOC_POWERPC32::R_PPC_DTPREL16,          16 },
  { RELOC_POWERPC32::R_PPC_DTPREL16_LO,       16 },
  { RELOC_POWERPC32::R_PPC_DTPREL16_HI,       16 },
  { RELOC_POWERPC32::R_PPC_DTPREL16_HA,       16 },
  { RELOC_POWERPC32::R_PPC_DTPREL32,          32 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSGD16,       16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSGD16_LO,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSGD16_HI,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSGD16_HA,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSLD16,       16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSLD16_LO,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSLD16_HI,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TLSLD16_HA,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TPREL16,       16 },
  { RELOC_POWERPC32::R_PPC_GOT_TPREL16_LO,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TPREL16_HI,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_TPREL16_HA,    16 },
  { RELOC_POWERPC32::R_PPC_GOT_DTPREL16,      16 },
  { RELOC_POWERPC32::R_PPC_GOT_DTPREL16_LO,   16 },
  { RELOC_POWERPC32::R_PPC_GOT_DTPREL16_HI,   16 },
  { RELOC_POWERPC32::R_PPC_GOT_DTPREL16_HA,   16 },
  { RELOC_POWERPC32::R_PPC_TLSGD,             32 },
  { RELOC_POWERPC32::R_PPC_TLSLD,             32 },
  { RELOC_POWERPC32::R_PPC_REL16,             16 },
  { RELOC_POWERPC32::R_PPC_REL16_LO,          16 },
  { RELOC_POWERPC32::R_PPC_REL16_HI,          16 },
  { RELOC_POWERPC32::R_PPC_REL16_HA,          16 },
};

CONST_MAP(RELOC_POWERPC64, uint32_t, 84) relocation_PPC64_sizes {
  { RELOC_POWERPC64::R_PPC64_NONE,                 0 },
  { RELOC_POWERPC64::R_PPC64_ADDR32,              32 },
  { RELOC_POWERPC64::R_PPC64_ADDR24,              32 },
  { RELOC_POWERPC64::R_PPC64_ADDR16,              16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_LO,           16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HI,           16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HA,           16 },
  { RELOC_POWERPC64::R_PPC64_ADDR14,              32 },
  { RELOC_POWERPC64::R_PPC64_ADDR14_BRTAKEN,      32 },
  { RELOC_POWERPC64::R_PPC64_ADDR14_BRNTAKEN,     32 },
  { RELOC_POWERPC64::R_PPC64_REL24,               32 },
  { RELOC_POWERPC64::R_PPC64_REL14,               32 },
  { RELOC_POWERPC64::R_PPC64_REL14_BRTAKEN,       32 },
  { RELOC_POWERPC64::R_PPC64_REL14_BRNTAKEN,      32 },
  { RELOC_POWERPC64::R_PPC64_GOT16,               16 },
  { RELOC_POWERPC64::R_PPC64_GOT16_LO,            16 },
  { RELOC_POWERPC64::R_PPC64_GOT16_HI,            16 },
  { RELOC_POWERPC64::R_PPC64_GOT16_HA,            16 },
  { RELOC_POWERPC64::R_PPC64_JMP_SLOT,            64 },
  { RELOC_POWERPC64::R_PPC64_RELATIVE,            64 },
  { RELOC_POWERPC64::R_PPC64_REL32,               32 },
  { RELOC_POWERPC64::R_PPC64_ADDR64,              64 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HIGHER,       16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HIGHERA,      16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HIGHEST,      16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_HIGHESTA,     16 },
  { RELOC_POWERPC64::R_PPC64_REL64,               64 },
  { RELOC_POWERPC64::R_PPC64_TOC16,               16 },
  { RELOC_POWERPC64::R_PPC64_TOC16_LO,            16 },
  { RELOC_POWERPC64::R_PPC64_TOC16_HI,            16 },
  { RELOC_POWERPC64::R_PPC64_TOC16_HA,            16 },
  { RELOC_POWERPC64::R_PPC64_TOC,                 16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_DS,           16 },
  { RELOC_POWERPC64::R_PPC64_ADDR16_LO_DS,        16 },
  { RELOC_POWERPC64::R_PPC64_GOT16_DS,            16 },
  { RELOC_POWERPC64::R_PPC64_GOT16_LO_DS,         16 },
  { RELOC_POWERPC64::R_PPC64_TOC16_DS,            16 },
  { RELOC_POWERPC64::R_PPC64_TOC16_LO_DS,         16 },
  { RELOC_POWERPC64::R_PPC64_TLS,                  0 },
  { RELOC_POWERPC64::R_PPC64_DTPMOD64,            64 },
  { RELOC_POWERPC64::R_PPC64_TPREL16,             16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_LO,          16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HI,          16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HA,          16 },
  { RELOC_POWERPC64::R_PPC64_TPREL64,             64 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16,            16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_LO,         16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HI,         16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HA,         16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL64,            64 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSGD16,         16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSGD16_LO,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSGD16_HI,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSGD16_HA,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSLD16,         16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSLD16_LO,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSLD16_HI,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TLSLD16_HA,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TPREL16_DS,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TPREL16_LO_DS,   16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TPREL16_HI,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_TPREL16_HA,      16 },
  { RELOC_POWERPC64::R_PPC64_GOT_DTPREL16_DS,     16 },
  { RELOC_POWERPC64::R_PPC64_GOT_DTPREL16_LO_DS,  16 },
  { RELOC_POWERPC64::R_PPC64_GOT_DTPREL16_HI,     16 },
  { RELOC_POWERPC64::R_PPC64_GOT_DTPREL16_HA,     16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_DS,          16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_LO_DS,       16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HIGHER,      16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HIGHERA,     16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HIGHEST,     16 },
  { RELOC_POWERPC64::R_PPC64_TPREL16_HIGHESTA,    16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_DS,         16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_LO_DS,      16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HIGHER,     16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HIGHERA,    16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HIGHEST,    16 },
  { RELOC_POWERPC64::R_PPC64_DTPREL16_HIGHESTA,   16 },
  { RELOC_POWERPC64::R_PPC64_TLSGD,               64 },
  { RELOC_POWERPC64::R_PPC64_TLSLD,               64 },
  { RELOC_POWERPC64::R_PPC64_REL16,               16 },
  { RELOC_POWERPC64::R_PPC64_REL16_LO,            16 },
  { RELOC_POWERPC64::R_PPC64_REL16_HI,            16 },
  { RELOC_POWERPC64::R_PPC64_REL16_HA,            16 },
};

CONST_MAP(RELOC_MIPS, uint32_t, 112) relocation_MIPS_sizes {
  { RELOC_MIPS::R_MICROMIPS_26_S1,           26 },
  { RELOC_MIPS::R_MICROMIPS_CALL16,          16 },
  { RELOC_MIPS::R_MICROMIPS_CALL_HI16,       16 },
  { RELOC_MIPS::R_MICROMIPS_CALL_LO16,       16 },
  { RELOC_MIPS::R_MICROMIPS_GOT16,           16 },
  { RELOC_MIPS::R_MICROMIPS_GOT_DISP,        16 },
  { RELOC_MIPS::R_MICROMIPS_GOT_HI16,        16 },
  { RELOC_MIPS::R_MICROMIPS_GOT_LO16,        16 },
  { RELOC_MIPS::R_MICROMIPS_GOT_OFST,        16 },
  { RELOC_MIPS::R_MICROMIPS_GOT_PAGE,        16 },
  { RELOC_MIPS::R_MICROMIPS_GPREL16,         16 },
  { RELOC_MIPS::R_MICROMIPS_GPREL7_S2,        7 },
  { RELOC_MIPS::R_MICROMIPS_HI0_LO16,        16 },
  { RELOC_MIPS::R_MICROMIPS_HI16,            16 },
  { RELOC_MIPS::R_MICROMIPS_HIGHER,          16 },
  { RELOC_MIPS::R_MICROMIPS_HIGHEST,         16 },
  { RELOC_MIPS::R_MICROMIPS_JALR,            32 },
  { RELOC_MIPS::R_MICROMIPS_LITERAL,         16 },
  { RELOC_MIPS::R_MICROMIPS_LO16,            16 },
  { RELOC_MIPS::R_MICROMIPS_PC10_S1,         10 },
  { RELOC_MIPS::R_MICROMIPS_PC16_S1,         16 },
  { RELOC_MIPS::R_MICROMIPS_PC18_S3,         18 },
  { RELOC_MIPS::R_MICROMIPS_PC19_S2,         19 },
  { RELOC_MIPS::R_MICROMIPS_PC21_S2,         21 },
  { RELOC_MIPS::R_MICROMIPS_PC23_S2,         23 },
  { RELOC_MIPS::R_MICROMIPS_PC26_S2,         26 },
  { RELOC_MIPS::R_MICROMIPS_PC7_S1,           7 },
  { RELOC_MIPS::R_MICROMIPS_SCN_DISP,        32 },
  { RELOC_MIPS::R_MICROMIPS_SUB,             64 },
  { RELOC_MIPS::R_MICROMIPS_TLS_DTPREL_HI16, 16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_DTPREL_LO16, 16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_GD,          16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_GOTTPREL,    16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_LDM,         16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_TPREL_HI16,  16 },
  { RELOC_MIPS::R_MICROMIPS_TLS_TPREL_LO16,  16 },
  { RELOC_MIPS::R_MIPS_16,                   16 },
  { RELOC_MIPS::R_MIPS16_26,                 26 },
  { RELOC_MIPS::R_MIPS16_CALL16,             16 },
  { RELOC_MIPS::R_MIPS16_GOT16,              16 },
  { RELOC_MIPS::R_MIPS16_GPREL,              16 },
  { RELOC_MIPS::R_MIPS16_HI16,               16 },
  { RELOC_MIPS::R_MIPS16_LO16,               16 },
  { RELOC_MIPS::R_MIPS16_TLS_DTPREL_HI16,    16 },
  { RELOC_MIPS::R_MIPS16_TLS_DTPREL_LO16,    16 },
  { RELOC_MIPS::R_MIPS16_TLS_GD,             16 },
  { RELOC_MIPS::R_MIPS16_TLS_GOTTPREL,       16 },
  { RELOC_MIPS::R_MIPS16_TLS_LDM,            16 },
  { RELOC_MIPS::R_MIPS16_TLS_TPREL_HI16,     16 },
  { RELOC_MIPS::R_MIPS16_TLS_TPREL_LO16,     16 },
  { RELOC_MIPS::R_MIPS_ADD_IMMEDIATE,         0 },
  { RELOC_MIPS::R_MIPS_26,                   26 },
  { RELOC_MIPS::R_MIPS_32,                   32 },
  { RELOC_MIPS::R_MIPS_64,                   64 },
  { RELOC_MIPS::R_MIPS_CALL16,               16 },
  { RELOC_MIPS::R_MIPS_CALL_HI16,            16 },
  { RELOC_MIPS::R_MIPS_CALL_LO16,            16 },
  { RELOC_MIPS::R_MIPS_COPY,                  0 },
  { RELOC_MIPS::R_MIPS_DELETE,               32 },
  { RELOC_MIPS::R_MIPS_EH,                   32 },
  { RELOC_MIPS::R_MIPS_GLOB_DAT,             32 },
  { RELOC_MIPS::R_MIPS_GOT16,                16 },
  { RELOC_MIPS::R_MIPS_GOT_DISP,             16 },
  { RELOC_MIPS::R_MIPS_GOT_HI16,             16 },
  { RELOC_MIPS::R_MIPS_GOT_LO16,             16 },
  { RELOC_MIPS::R_MIPS_GOT_OFST,             16 },
  { RELOC_MIPS::R_MIPS_GOT_PAGE,             16 },
  { RELOC_MIPS::R_MIPS_GPREL16,              16 },
  { RELOC_MIPS::R_MIPS_GPREL32,              32 },
  { RELOC_MIPS::R_MIPS_HI16,                 16 },
  { RELOC_MIPS::R_MIPS_HIGHER,               16 },
  { RELOC_MIPS::R_MIPS_HIGHEST,              16 },
  { RELOC_MIPS::R_MIPS_INSERT_A,             32 },
  { RELOC_MIPS::R_MIPS_INSERT_B,             32 },
  { RELOC_MIPS::R_MIPS_JALR,                 32 },
  { RELOC_MIPS::R_MIPS_JUMP_SLOT,            64 },
  { RELOC_MIPS::R_MIPS_LITERAL,              16 },
  { RELOC_MIPS::R_MIPS_LO16,                 16 },
  { RELOC_MIPS::R_MIPS_NONE,                  0 },
  { RELOC_MIPS::R_MIPS_NUM,                   0 },
  { RELOC_MIPS::R_MIPS_PC16,                 16 },
  { RELOC_MIPS::R_MIPS_PC18_S3,              18 },
  { RELOC_MIPS::R_MIPS_PC19_S2,              19 },
  { RELOC_MIPS::R_MIPS_PC21_S2,              21 },
  { RELOC_MIPS::R_MIPS_PC26_S2,              26 },
  { RELOC_MIPS::R_MIPS_PC32,                 32 },
  { RELOC_MIPS::R_MIPS_PCHI16,               16 },
  { RELOC_MIPS::R_MIPS_PCLO16,               16 },
  { RELOC_MIPS::R_MIPS_PJUMP,                 0 },
  { RELOC_MIPS::R_MIPS_REL16,                16 },
  { RELOC_MIPS::R_MIPS_REL32,                32 },
  { RELOC_MIPS::R_MIPS_RELGOT,               32 },
  { RELOC_MIPS::R_MIPS_SCN_DISP,             32 },
  { RELOC_MIPS::R_MIPS_SHIFT5,                5 },
  { RELOC_MIPS::R_MIPS_SHIFT6,                6 },
  { RELOC_MIPS::R_MIPS_SUB,                  64 },
  { RELOC_MIPS::R_MIPS_TLS_DTPMOD32,         32 },
  { RELOC_MIPS::R_MIPS_TLS_DTPMOD64,         64 },
  { RELOC_MIPS::R_MIPS_TLS_DTPREL32,         32 },
  { RELOC_MIPS::R_MIPS_TLS_DTPREL64,         64 },
  { RELOC_MIPS::R_MIPS_TLS_DTPREL_HI16,      16 },
  { RELOC_MIPS::R_MIPS_TLS_DTPREL_LO16,      16 },
  { RELOC_MIPS::R_MIPS_TLS_GD,               16 },
  { RELOC_MIPS::R_MIPS_TLS_GOTTPREL,         16 },
  { RELOC_MIPS::R_MIPS_TLS_LDM,              16 },
  { RELOC_MIPS::R_MIPS_TLS_TPREL64,          32 },
  { RELOC_MIPS::R_MIPS_TLS_TPREL64,          64 },
  { RELOC_MIPS::R_MIPS_TLS_TPREL_HI16,       16 },
  { RELOC_MIPS::R_MIPS_TLS_TPREL_LO16,       16 },
  { RELOC_MIPS::R_MIPS_UNUSED1,               0 },
  { RELOC_MIPS::R_MIPS_UNUSED2,               0 },
  { RELOC_MIPS::R_MIPS_UNUSED3,               0 },
};

}
}

#endif
