#include "Analysis/LiftWrapper.h"

vex::Lifter::Lifter() {
    vex_init();
    this->vex_arch_info.endness = VexEndnessLE;
    vex_arch_info.x86_cr0 = 0xFFFFFFFF;
    vex_arch_info.hwcache_info.caches = nullptr;
}

void vex::Lifter::Lift(std::vector<uint8_t> _vec) {
    auto lifted = vex_lift(VexArchAMD64, vex_arch_info, _vec.data(), 0x400400, 99, _vec.size(), 1, 0, 1, 1, 0,
             VexRegUpdUnwindregsAtMemAccess, 0);
    this->irsb = lifted->irsb;
    return;
}
