/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * File is based on linux/arch/x86/include/asm/vmx.h:
 *
 * Copyright (c) 2004, Intel Corporation.
 * Copyright (c) 2006 Qumranet
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 */

#ifndef _JAILHOUSE_ASM_VMX_H
#define _JAILHOUSE_ASM_VMX_H

#define GUEST_SEG_LIMIT			(GUEST_ES_LIMIT - GUEST_ES_SELECTOR)
#define GUEST_SEG_AR_BYTES		(GUEST_ES_AR_BYTES - GUEST_ES_SELECTOR)
#define GUEST_SEG_BASE			(GUEST_ES_BASE - GUEST_ES_SELECTOR)

#define GUEST_ACTIVITY_ACTIVE			0
#define GUEST_ACTIVITY_HLT			1

#define VMX_MSR_BMP_0000_READ			0
#define VMX_MSR_BMP_C000_READ			1
#define VMX_MSR_BMP_0000_WRITE			2
#define VMX_MSR_BMP_C000_WRITE			3

#define PIN_BASED_NMI_EXITING			(1UL << 3)
#define PIN_BASED_VMX_PREEMPTION_TIMER		(1UL << 6)

#define CPU_BASED_CR3_LOAD_EXITING		(1UL << 15)
#define CPU_BASED_CR3_STORE_EXITING		(1UL << 16)
#define CPU_BASED_USE_IO_BITMAPS		(1UL << 25)
#define CPU_BASED_USE_MSR_BITMAPS		(1UL << 28)
#define CPU_BASED_ACTIVATE_SECONDARY_CONTROLS	(1UL << 31)

#define SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES	(1UL << 0)
#define SECONDARY_EXEC_ENABLE_EPT		(1UL << 1)
#define SECONDARY_EXEC_RDTSCP			(1UL << 3)
#define SECONDARY_EXEC_UNRESTRICTED_GUEST	(1UL << 7)
#define SECONDARY_EXEC_INVPCID			(1UL << 12)
#define SECONDARY_EXEC_XSAVES			(1UL << 20)

#define VM_EXIT_HOST_ADDR_SPACE_SIZE		(1UL << 9)
#define VM_EXIT_SAVE_IA32_PAT			(1UL << 18)
#define VM_EXIT_LOAD_IA32_PAT			(1UL << 19)
#define VM_EXIT_SAVE_IA32_EFER			(1UL << 20)
#define VM_EXIT_LOAD_IA32_EFER			(1UL << 21)

#define VM_ENTRY_IA32E_MODE			(1UL << 9)
#define VM_ENTRY_LOAD_IA32_PAT			(1UL << 14)
#define VM_ENTRY_LOAD_IA32_EFER			(1UL << 15)

#define VMX_MISC_ACTIVITY_HLT			(1UL << 6)

#define INTR_INFO_INTR_TYPE_MASK		BIT_MASK(10, 8)
#define INTR_INFO_UNBLOCK_NMI			(1UL << 12)

#define INTR_TYPE_NMI_INTR			(2UL << 8)

#define INTR_TO_VECTORING_INFO_MASK		((1UL << 31) | BIT_MASK(11, 0))

#define EXIT_REASONS_FAILED_VMENTRY		(1UL << 31)

#define EXIT_REASON_EXCEPTION_NMI		0
#define EXIT_REASON_EXTERNAL_INTERRUPT		1
#define EXIT_REASON_TRIPLE_FAULT		2
#define EXIT_REASON_INIT_SIGNAL			3
#define EXIT_REASON_SIPI			4
#define EXIT_REASON_IO_SMI			5
#define EXIT_REASON_OTHER_SMI			6
#define EXIT_REASON_PENDING_INTERRUPT		7
#define EXIT_REASON_NMI_WINDOW			8
#define EXIT_REASON_TASK_SWITCH			9
#define EXIT_REASON_CPUID			10
#define EXIT_REASON_HLT				12
#define EXIT_REASON_INVD			13
#define EXIT_REASON_INVLPG			14
#define EXIT_REASON_RDPMC			15
#define EXIT_REASON_RDTSC			16
#define EXIT_REASON_VMCALL			18
#define EXIT_REASON_VMCLEAR			19
#define EXIT_REASON_VMLAUNCH			20
#define EXIT_REASON_VMPTRLD			21
#define EXIT_REASON_VMPTRST			22
#define EXIT_REASON_VMREAD			23
#define EXIT_REASON_VMRESUME			24
#define EXIT_REASON_VMWRITE			25
#define EXIT_REASON_VMXOFF			26
#define EXIT_REASON_VMXON			27
#define EXIT_REASON_CR_ACCESS			28
#define EXIT_REASON_DR_ACCESS			29
#define EXIT_REASON_IO_INSTRUCTION		30
#define EXIT_REASON_MSR_READ			31
#define EXIT_REASON_MSR_WRITE			32
#define EXIT_REASON_INVALID_STATE		33
#define EXIT_REASON_MWAIT_INSTRUCTION		36
#define EXIT_REASON_MONITOR_INSTRUCTION		39
#define EXIT_REASON_PAUSE_INSTRUCTION		40
#define EXIT_REASON_MCE_DURING_VMENTRY		41
#define EXIT_REASON_TPR_BELOW_THRESHOLD		43
#define EXIT_REASON_APIC_ACCESS			44
#define EXIT_REASON_EPT_VIOLATION		48
#define EXIT_REASON_EPT_MISCONFIG		49
#define EXIT_REASON_INVEPT			50
#define EXIT_REASON_PREEMPTION_TIMER		52
#define EXIT_REASON_WBINVD			54
#define EXIT_REASON_XSETBV			55
#define EXIT_REASON_INVPCID			58

#define EPT_PAGE_DIR_LEVELS			4

#define EPT_FLAG_READ				0x001
#define EPT_FLAG_WRITE				0x002
#define EPT_FLAG_EXECUTE			0x004
#define EPT_FLAG_WB_TYPE			0x030

#define EPT_TYPE_UNCACHEABLE			0
#define EPT_TYPE_WRITEBACK			6
#define EPT_PAGE_WALK_LEN			((4-1) << 3)

#define EPT_PAGE_WALK_4				(1UL << 6)
#define EPTP_WB					(1UL << 14)
#define EPT_2M_PAGES				(1UL << 16)
#define EPT_1G_PAGES				(1UL << 17)
#define EPT_INVEPT				(1UL << 20)
#define EPT_INVEPT_SINGLE			(1UL << 25)
#define EPT_INVEPT_GLOBAL			(1UL << 26)
#define EPT_MANDATORY_FEATURES			(EPT_PAGE_WALK_4 | EPTP_WB | \
						 EPT_INVEPT)

#define VMX_INVEPT_SINGLE			1
#define VMX_INVEPT_GLOBAL			2

#define APIC_ACCESS_OFFSET_MASK			0x00000fff
#define APIC_ACCESS_TYPE_MASK			0x0000f000
#define APIC_ACCESS_TYPE_LINEAR_READ		0x00000000
#define APIC_ACCESS_TYPE_LINEAR_WRITE		0x00001000






#define BITS_PER_LONG			64



#define _JAILHOUSE_TYPES_H


#define NULL				((void *)0)















#define _JAILHOUSE_ASM_PROCESSOR_H


#define X86_FEATURE_VMX					(1 << 5)
#define X86_FEATURE_XSAVE				(1 << 26)
#define X86_FEATURE_OSXSAVE				(1 << 27)
#define X86_FEATURE_HYPERVISOR				(1 << 31)

#define X86_FEATURE_INVPCID				(1 << 10)
#define X86_FEATURE_CAT					(1 << 15)

#define X86_FEATURE_XSAVES				(1 << 3)

#define X86_FEATURE_SVM					(1 << 2)

#define X86_FEATURE_GBPAGES				(1 << 26)
#define X86_FEATURE_RDTSCP				(1 << 27)

#define X86_FEATURE_NP					(1 << 0)
#define X86_FEATURE_FLUSH_BY_ASID			(1 << 6)
#define X86_FEATURE_DECODE_ASSISTS			(1 << 7)
#define X86_FEATURE_AVIC				(1 << 13)

#define X86_RFLAGS_VM					(1 << 17)

#define X86_CR0_PE					(1UL << 0)
#define X86_CR0_MP					(1UL << 1)
#define X86_CR0_TS					(1UL << 3)
#define X86_CR0_ET					(1UL << 4)
#define X86_CR0_NE					(1UL << 5)
#define X86_CR0_WP					(1UL << 16)
#define X86_CR0_NW					(1UL << 29)
#define X86_CR0_CD					(1UL << 30)
#define X86_CR0_PG					(1UL << 31)
#define X86_CR0_RESERVED				\
	(BIT_MASK(28, 19) |  (1UL << 17) | BIT_MASK(15, 6))

#define X86_CR4_PAE					(1UL << 5)
#define X86_CR4_VMXE					(1UL << 13)
#define X86_CR4_OSXSAVE					(1UL << 18)
#define X86_CR4_RESERVED				\
	(BIT_MASK(31, 23) | (1UL << 19) | (1UL << 15) | (1UL << 12))

#define X86_XCR0_FP					0x00000001

#define MSR_IA32_APICBASE				0x0000001b
#define MSR_IA32_FEATURE_CONTROL			0x0000003a
#define MSR_IA32_PAT					0x00000277
#define MSR_IA32_MTRR_DEF_TYPE				0x000002ff
#define MSR_IA32_SYSENTER_CS				0x00000174
#define MSR_IA32_SYSENTER_ESP				0x00000175
#define MSR_IA32_SYSENTER_EIP				0x00000176
#define MSR_IA32_PERF_GLOBAL_CTRL			0x0000038f
#define MSR_IA32_VMX_BASIC				0x00000480
#define MSR_IA32_VMX_PINBASED_CTLS			0x00000481
#define MSR_IA32_VMX_PROCBASED_CTLS			0x00000482
#define MSR_IA32_VMX_EXIT_CTLS				0x00000483
#define MSR_IA32_VMX_ENTRY_CTLS				0x00000484
#define MSR_IA32_VMX_MISC				0x00000485
#define MSR_IA32_VMX_CR0_FIXED0				0x00000486
#define MSR_IA32_VMX_CR0_FIXED1				0x00000487
#define MSR_IA32_VMX_CR4_FIXED0				0x00000488
#define MSR_IA32_VMX_CR4_FIXED1				0x00000489
#define MSR_IA32_VMX_PROCBASED_CTLS2			0x0000048b
#define MSR_IA32_VMX_EPT_VPID_CAP			0x0000048c
#define MSR_IA32_VMX_TRUE_PROCBASED_CTLS		0x0000048e
#define MSR_X2APIC_BASE					0x00000800
#define MSR_X2APIC_ICR					0x00000830
#define MSR_X2APIC_END					0x0000083f
#define MSR_IA32_PQR_ASSOC				0x00000c8f
#define MSR_IA32_L3_MASK_0				0x00000c90
#define MSR_EFER					0xc0000080
#define MSR_STAR					0xc0000081
#define MSR_LSTAR					0xc0000082
#define MSR_CSTAR					0xc0000083
#define MSR_SFMASK					0xc0000084
#define MSR_FS_BASE					0xc0000100
#define MSR_GS_BASE					0xc0000101
#define MSR_KERNGS_BASE					0xc0000102

#define FEATURE_CONTROL_LOCKED				(1 << 0)
#define FEATURE_CONTROL_VMXON_ENABLED_OUTSIDE_SMX	(1 << 2)

#define PAT_RESET_VALUE					0x0007040600070406UL
#define PAT_HOST_VALUE					0x070106UL

#define MTRR_ENABLE					(1UL << 11)

#define EFER_LME					0x00000100
#define EFER_LMA					0x00000400
#define EFER_NXE					0x00000800

#define PQR_ASSOC_COS_SHIFT				32

#define CAT_RESID_L3					1

#define CAT_CBM_LEN_MASK				BIT_MASK(4, 0)
#define CAT_COS_MAX_MASK				BIT_MASK(15, 0)

#define GDT_DESC_NULL					0
#define GDT_DESC_CODE					1
#define GDT_DESC_TSS					2
#define GDT_DESC_TSS_HI					3
#define NUM_GDT_DESC					16

#define X86_INST_LEN_CPUID				2
#define X86_INST_LEN_RDMSR				2
#define X86_INST_LEN_WRMSR				2
#define X86_INST_LEN_HYPERCALL				3
#define X86_INST_LEN_MOV_TO_CR				3
#define X86_INST_LEN_XSETBV				3

#define X86_REX_CODE					4

#define X86_PREFIX_OP_SZ				0x66
#define X86_PREFIX_ADDR_SZ				0x67

#define X86_OP_MOVZX_OPC1				0x0f
#define X86_OP_MOVZX_OPC2_B				0xb6
#define X86_OP_MOVZX_OPC2_W				0xb7
#define X86_OP_MOVB_TO_MEM				0x88
#define X86_OP_MOV_TO_MEM				0x89
#define X86_OP_MOVB_FROM_MEM				0x8a
#define X86_OP_MOV_FROM_MEM				0x8b
#define X86_OP_MOV_IMMEDIATE_TO_MEM			0xc7
#define X86_OP_MOV_MEM_TO_AX    			0xa1
#define X86_OP_MOV_AX_TO_MEM				0xa3

#define DB_VECTOR					1
#define NMI_VECTOR					2
#define PF_VECTOR					14
#define AC_VECTOR					17

#define DESC_TSS_BUSY					(1UL << (9 + 32))
#define DESC_PRESENT					(1UL << (15 + 32))
#define DESC_CODE_DATA					(1UL << (12 + 32))
#define DESC_PAGE_GRAN					(1UL << (23 + 32))

void check_vmx_support(void);
#endif /* !_JAILHOUSE_ASM_PROCESSOR_H */
