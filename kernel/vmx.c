#include "types.h"
#include "defs.h"
#include "x86.h"
#include "vmx.h"

void check_vmx_support(void) {
    cprintf("checking vmx\n");

    // SDM3 23.6:
    // If CPUID.1:ECX.VMX[bit 5] = 1, then VMX operation is supported.
    uint32 eax, ebx, ecx, edx;
    cpuid(1, &eax, &ebx, &ecx, &edx);
    if (!(ecx & (1<<5)))
        panic("VMX support not detected!");
    else
        cprintf("  VMX support detected!\n");

    // Copy from jailhouse
    int vmx_proc_ctrl2 = read_msr(MSR_IA32_VMX_PROCBASED_CTLS2) >> 32;
    int ept_cap = read_msr(MSR_IA32_VMX_EPT_VPID_CAP);
    if (!(vmx_proc_ctrl2 & SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES) ||
            !(vmx_proc_ctrl2 & SECONDARY_EXEC_ENABLE_EPT) ||
            (ept_cap & EPT_MANDATORY_FEATURES) != EPT_MANDATORY_FEATURES ||
            !(ept_cap & (EPT_INVEPT_SINGLE | EPT_INVEPT_GLOBAL)) ||
            !(vmx_proc_ctrl2 & SECONDARY_EXEC_UNRESTRICTED_GUEST))
        panic("EPT support not detected!");
    else
        cprintf("  EPT support detected!\n");
}
