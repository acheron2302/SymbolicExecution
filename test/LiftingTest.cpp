#include <gmock/gmock.h>
#include <gtest/gtest.h>
extern "C" {
#include <libvex.h>
#include <libvex_guest_offsets.h>
#include <pyvex.h>
}
#include "Analysis/LiftWrapper.h"



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
    vex_arch_info.endness =
        VexEndnessLE; // tell that the lifting is little endian
    vex_arch_info.x86_cr0 = 0xFFFFFFFF;
    vex_arch_info.hwcache_info.caches = NULL;
    unsigned char temp[] = "\x90\x90\x90\x90\x90";

    // Copy from:
    // https://github.com/angr/angr/blob/master/native/sim_unicorn.cpp#L1720
    auto result1 = vex_lift(VexArchAMD64, vex_arch_info, temp, 0x400400, 99, 5,
                            1, 0, 1, 1, 0, VexRegUpdUnwindregsAtMemAccess, 0);
    for (int i = 0; i < result1->irsb->stmts_used; i++) {
        ASSERT_EQ(result1->irsb->stmts[i]->tag, Ist_IMark);
    }

    /*
    * This is equivelence to this IR:
   t0:Ity_I64 t1:Ity_I64 t2:Ity_I64 t3:Ity_I32 t4:Ity_I64 t5:Ity_I64 t6:Ity_I64

   00 | ------ IMark(0x40400, 1, 0) ------
   01 | ------ IMark(0x40401, 1, 0) ------
   02 | ------ IMark(0x40402, 3, 0) ------
   03 | t1 = GET:I64(rbx)
   04 | PUT(rax) = t1
   05 | PUT(rip) = 0x0000000000040405
   06 | ------ IMark(0x40405, 5, 0) ------
   07 | t4 = Add64(t1,0x0000000000000004)
   08 | t3 = 64to32(t4)
   09 | t2 = 32Uto64(t3)
   10 | STle(t2) = 0x04
   11 | ------ IMark(0x4040a, 2, 0) ------
   12 | PUT(ah) = 0x04
   13 | ------ IMark(0x4040c, 2, 0) ------
   14 | PUT(al) = 0x04
   15 | ------ (0x40IMark40e, 1, 0) ------
   NEXT: PUT(rip) = 0x000000000004040f; Ijk_Boring
    */
    unsigned char temp2[] =
        "\x90\x90\x48\x89\xd8\x67\xc6\x40\x04\x04\xb4\x04\xb0\x04\x90";
    auto result2 =
        vex_lift(VexArchAMD64, vex_arch_info, temp2, 0x400400, 99, 15, 1, 0, 0,
                 1, 0, VexRegUpdUnwindregsAtMemAccess, 0);
    ASSERT_EQ(result1, result2);
    ASSERT_EQ(result2->irsb->stmts[4]->tag, Ist_Put);
    auto ir_type = typeOfIRExpr(result2->irsb->tyenv,
                                result2->irsb->stmts[4]->Ist.Put.data);
    ASSERT_EQ(ir_type, Ity_I64);
    ASSERT_EQ(sizeofIRType(ir_type), 8);

    ASSERT_EQ(result2->irsb->stmts[12]->tag, Ist_Put);
    ASSERT_EQ(result2->irsb->stmts[12]->Ist.Put.offset,
              OFFSET_amd64_RAX + 1); // check if it is ah
    auto ir_type2 = typeOfIRExpr(result2->irsb->tyenv,
                                 result2->irsb->stmts[12]->Ist.Put.data);
    ASSERT_EQ(ir_type2, Ity_I8);
    ASSERT_EQ(result2->irsb->tyenv->types[3], Ity_I32);
}

TEST(LifterTest, Lifting) {
    /*
    * This is equivelence to this IR:
   t0:Ity_I64 t1:Ity_I64 t2:Ity_I64 t3:Ity_I32 t4:Ity_I64 t5:Ity_I64 t6:Ity_I64

   00 | ------ IMark(0x40400, 1, 0) ------
   01 | ------ IMark(0x40401, 1, 0) ------
   02 | ------ IMark(0x40402, 3, 0) ------
   03 | t1 = GET:I64(rbx)
   04 | PUT(rax) = t1
   05 | PUT(rip) = 0x0000000000040405
   06 | ------ IMark(0x40405, 5, 0) ------
   07 | t4 = Add64(t1,0x0000000000000004)
   08 | t3 = 64to32(t4)
   09 | t2 = 32Uto64(t3)
   10 | STle(t2) = 0x04
   11 | ------ IMark(0x4040a, 2, 0) ------
   12 | PUT(ah) = 0x04
   13 | ------ IMark(0x4040c, 2, 0) ------
   14 | PUT(al) = 0x04
   15 | ------ (0x40IMark40e, 1, 0) ------
   NEXT: PUT(rip) = 0x000000000004040f; Ijk_Boring
    */
    std::vector<uint8_t> example = {0x90, 0x90, 0x48, 0x89, 0xd8,
                                    0x67, 0xc6, 0x40, 0x04, 0x04,
                                    0xb4, 0x04, 0xb0, 0x04, 0x90};
    vex::Lifter lift;
    auto result = lift.Lift(example, 0x0);
    ASSERT_EQ(result->stmts_used, 16);
    ASSERT_EQ(result->tyenv->types_used, 7);
    ASSERT_TRUE(std::holds_alternative<vex::Put>(result->stmts[12]->var));
}
