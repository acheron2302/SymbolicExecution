#include <gtest/gtest.h>
extern "C" {
#include <libvex.h>
#include <pyvex.h>
}

class TestLifting : public ::testing::Test {
  protected:
    static void SetUpTestSuite() {
        if (!vex_init()) {
            FAIL() << "Failed to initialise vex";
        }
    }

    static void TearDownTestSuite() {}

    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(TestLifting, TestPyVexArchx86) {

    VexArchInfo vex_arch_info;
    LibVEX_default_VexArchInfo(&vex_arch_info);
    vex_arch_info.endness = VexEndnessLE; // tell that the lifting is little endian
    vex_arch_info.x86_cr0 = 0xFFFFFFFF;
    unsigned char temp[] = "\x90\x90\x90\x90\x90";

    // Copy from: https://github.com/angr/angr/blob/master/native/sim_unicorn.cpp#L1720
    auto result1 = vex_lift(VexArchAMD64, vex_arch_info, temp, 0x400400, 99, 5,
                            1, 0, 1, 1, 0, VexRegUpdAllregsAtMemAccess, 0);
    for (int i = 0; i < result1->irsb->stmts_used; i++) {
        ASSERT_EQ(result1->irsb->stmts[i]->tag, Ist_IMark);
    }
}
