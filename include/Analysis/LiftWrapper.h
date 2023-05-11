extern "C" {
#include <libvex.h>
#include <libvex_guest_offsets.h>
#include <pyvex.h>
}
#include <memory>
#include <variant>
#include <vector>
#include <stdexcept>


namespace vex {
struct WrapIRExpr;

struct Binder {
    Int binder;
};

/* Read a guest register, at a fixed offset in the guest state.
ppIRExpr output: GET:<ty>(<offset>), eg. GET:I32(0)
*/
struct Get {
    Int offset; /* Offset into the guest state */
    IRType ty;  /* Type of the value being read */
};

/* Read a guest register at a non-fixed offset in the guest
state.  This allows circular indexing into parts of the guest
state, which is essential for modelling situations where the
identity of guest registers is not known until run time.  One
example is the x87 FP register stack.
The part of the guest state to be treated as a circular array
is described in the IRRegArray 'descr' field.  It holds the
offset of the first element in the array, the type of each
element, and the number of elements.
The array index is indicated rather indirectly, in a way
which makes optimisation easy: as the sum of variable part
(the 'ix' field) and a constant offset (the 'bias' field).
Since the indexing is circular, the actual array index to use
is computed as (ix + bias) % num-of-elems-in-the-array.
Here's an example.  The description
    (96:8xF64)[t39,-7]
describes an array of 8 F64-typed values, the
guest-state-offset of the first being 96.  This array is
being indexed at (t39 - 7) % 8.
It is important to get the array size/type exactly correct
since IR optimisation looks closely at such info in order to
establish aliasing/non-aliasing between seperate GetI and
PutI events, which is used to establish when they can be
reordered, etc.  Putting incorrect info in will lead to
obscure IR optimisation bugs.
    ppIRExpr output: GETI<descr>[<ix>,<bias]
                eg. GETI(128:8xI8)[t1,0]
*/
struct GetI {
    std::unique_ptr<IRRegArray>
        descr; /* Part of guest state treated as circular */
    std::unique_ptr<WrapIRExpr> ix; /* Variable part of index into array */
    Int bias; /* Constant offset part of index into array */
};

/* The value held by a temporary.
ppIRExpr output: t<tmp>, eg. t1
*/
struct RdTmp {
    IRTemp tmp; /* The temporary number */
};

/* A quaternary operation.
ppIRExpr output: <op>(<arg1>, <arg2>, <arg3>, <arg4>),
            eg. MAddF64r32(t1, t2, t3, t4)
*/
struct Qop {
    IROp op;                          /* op-code   */
    std::unique_ptr<WrapIRExpr> arg1; /* operand 1 */
    std::unique_ptr<WrapIRExpr> arg2; /* operand 2 */
    std::unique_ptr<WrapIRExpr> arg3; /* operand 3 */
    std::unique_ptr<WrapIRExpr> arg4; /* operand 4 */
};

/* A ternary operation.
ppIRExpr output: <op>(<arg1>, <arg2>, <arg3>),
            eg. MulF64(1, 2.0, 3.0)
*/
struct Triop {
    IROp op;                          /* op-code   */
    std::unique_ptr<WrapIRExpr> arg1; /* operand 1 */
    std::unique_ptr<WrapIRExpr> arg2; /* operand 2 */
    std::unique_ptr<WrapIRExpr> arg3; /* operand 3 */
};

/* A binary operation.
ppIRExpr output: <op>(<arg1>, <arg2>), eg. Add32(t1,t2)
*/
struct Binop {
    IROp op;                          /* op-code   */
    std::unique_ptr<WrapIRExpr> arg1; /* operand 1 */
    std::unique_ptr<WrapIRExpr> arg2; /* operand 2 */
};

/* A unary operation.
ppIRExpr output: <op>(<arg>), eg. Neg8(t1)
*/
struct Unop {
    IROp op;                         /* op-code */
    std::unique_ptr<WrapIRExpr> arg; /* operand */
};

/* A load from memory -- a normal load, not a load-linked.
Load-Linkeds (and Store-Conditionals) are instead represented
by IRStmt.LLSC since Load-Linkeds have side effects and so
are not semantically valid IRExpr's.
ppIRExpr output: LD<end>:<ty>(<addr>), eg. LDle:I32(t1)
*/
struct Load {
    IREndness end;                    /* Endian-ness of the load */
    IRType ty;                        /* Type of the loaded value */
    std::unique_ptr<WrapIRExpr> addr; /* Address being loaded from */
};

/* A constant-valued expression.
ppIRExpr output: <con>, eg. 0x4:I32
*/
struct Const {
    std::unique_ptr<IRConst> con; /* The constant itself */
};

/* A call to a pure (no side-effects) helper C function.
With the 'cee' field, 'name' is the function's name.  It is
only used for pretty-printing purposes.  The address to call
(host address, of course) is stored in the 'addr' field
inside 'cee'.
The 'args' field is a NULL-terminated array of arguments.
The stated return IRType, and the implied argument types,
must match that of the function being called well enough so
that the back end can actually generate correct code for the
call.
The called function **must** satisfy the following:
* no side effects -- must be a pure function, the result of
    which depends only on the passed parameters.
* it may not look at, nor modify, any of the guest state
    since that would hide guest state transitions from
    instrumenters
* it may not access guest memory, since that would hide
    guest memory transactions from the instrumenters
* it must not assume that arguments are being evaluated in a
    particular order. The oder of evaluation is unspecified.
This is restrictive, but makes the semantics clean, and does
not interfere with IR optimisation.
If you want to call a helper which can mess with guest state
and/or memory, instead use Ist_Dirty.  This is a lot more
flexible, but you have to give a bunch of details about what
the helper does (and you better be telling the truth,
otherwise any derived instrumentation will be wrong).  Also
Ist_Dirty inhibits various IR optimisations and so can cause
quite poor code to be generated.  Try to avoid it.
In principle it would be allowable to have the arg vector
contain an IRExpr_VECRET(), although not IRExpr_GSPTR(). However,
at the moment there is no requirement for clean helper calls to
be able to return V128 or V256 values.  Hence this is not allowed.
ppIRExpr output: <cee>(<args>):<retty>
            eg. foo{0x80489304}(t1, t2):I32
*/
struct CCall {
    std::unique_ptr<IRCallee> cee; /* Function to call. */
    IRType retty;                  /* Type of return value. */
    std::vector<std::unique_ptr<WrapIRExpr>>
        args; /* Vector of argument expressions. */
};

/* A ternary if-then-else operator.  It returns iftrue if cond is
nonzero, iffalse otherwise.  Note that it is STRICT, ie. both
iftrue and iffalse are evaluated in all cases.
ppIRExpr output: ITE(<cond>,<iftrue>,<iffalse>),
                eg. ITE(t6,t7,t8)
*/
struct ITE {
    std::unique_ptr<WrapIRExpr> cond;    /* Condition */
    std::unique_ptr<WrapIRExpr> iftrue;  /* True expression */
    std::unique_ptr<WrapIRExpr> iffalse; /* False expression */
};

typedef std::variant<Binder, Get, GetI, RdTmp, Qop, Triop, Binop, Unop, Load,
                     Const, CCall, ITE>
    IEXVariant;


         /* A no-op (usually resulting from IR optimisation).  Can be
   omitted without any effect.
   ppIRStmt output: IR-NoOp
*/
struct NoOp {
    UInt dummy;
} ;

/* META: instruction mark.  Marks the start of the statements
   that represent a single machine instruction (the end of
   those statements is marked by the next IMark or the end of
   the IRSB).  Contains the address and length of the
   instruction.
   It also contains a delta value.  The delta must be
   subtracted from a guest program counter value before
   attempting to establish, by comparison with the address
   and length values, whether or not that program counter
   value refers to this instruction.  For x86, amd64, ppc32,
   ppc64 and arm, the delta value is zero.  For Thumb
   instructions, the delta value is one.  This is because, on
   Thumb, guest PC values (guest_R15T) are encoded using the
   top 31 bits of the instruction address and a 1 in the lsb;
   hence they appear to be (numerically) 1 past the start of
   the instruction they refer to.  IOW, guest_R15T on ARM
   holds a standard ARM interworking address.
   ppIRStmt output: ------ IMark(<addr>, <len>, <delta>) ------,
                eg. ------ IMark(0x4000792, 5, 0) ------,
*/
struct IMark {
    Addr addr;   /* instruction address */
    UInt len;    /* instruction length */
    UChar delta; /* addr = program counter as encoded in guest state
                           - delta */
} ;

/* META: An ABI hint, which says something about this
   platform's ABI.
   At the moment, the only AbiHint is one which indicates
   that a given chunk of address space, [base .. base+len-1],
   has become undefined.  This is used on amd64-linux and
   some ppc variants to pass stack-redzoning hints to whoever
   wants to see them.  It also indicates the address of the
   next (dynamic) instruction that will be executed.  This is
   to help Memcheck to origin tracking.
   ppIRStmt output: ====== AbiHint(<base>, <len>, <nia>) ======
                eg. ====== AbiHint(t1, 16, t2) ======
*/
struct AbiHint {
    std::unique_ptr<WrapIRExpr> base; /* Start  of undefined chunk */
    Int len;      /* Length of undefined chunk */
    std::unique_ptr<WrapIRExpr> nia;  /* Address of next (guest) insn */
} ;

/* Write a guest register, at a fixed offset in the guest state.
   ppIRStmt output: PUT(<offset>) = <data>, eg. PUT(60) = t1
*/
struct Put {
    Int offset;   /* Offset into the guest state */
    std::unique_ptr<WrapIRExpr> data; /* The value to write */
} ;

/* Write a guest register, at a non-fixed offset in the guest
   state.  See the comment for GetI expressions for more
   information.
   ppIRStmt output: PUTI<descr>[<ix>,<bias>] = <data>,
                eg. PUTI(64:8xF64)[t5,0] = t1
*/
struct PutI {
    std::unique_ptr<IRRegArray> descr; /* Part of guest state treated as circular */
    std::unique_ptr<WrapIRExpr> ix;        /* Variable part of index into array */
    Int bias;          /* Constant offset part of index into array */
    std::unique_ptr<WrapIRExpr> data;      /* The value to write */
} ;

/* Assign a value to a temporary.  Note that SSA rules require
   each tmp is only assigned to once.  IR sanity checking will
   reject any block containing a temporary which is not assigned
   to exactly once.
   ppIRStmt output: t<tmp> = <data>, eg. t1 = 3
*/
struct WrTmp {
    IRTemp tmp;   /* Temporary  (LHS of assignment) */
    std::unique_ptr<WrapIRExpr> data; /* Expression (RHS of assignment) */
} ;

/* Write a value to memory.  This is a normal store, not a
   Store-Conditional.  To represent a Store-Conditional,
   instead use IRStmt.LLSC.
   ppIRStmt output: ST<end>(<addr>) = <data>, eg. STle(t1) = t2
*/
struct Store {
    IREndness end; /* Endianness of the store */
    std::unique_ptr<WrapIRExpr> addr;  /* store address */
    std::unique_ptr<WrapIRExpr> data;  /* value to write */
} ;

/* Guarded store.  Note that this is defined to evaluate all
   expression fields (addr, data) even if the guard evaluates
   to false.
   ppIRStmt output:
     if (<guard>) ST<end>(<addr>) = <data> */
struct StoreG {
    IREndness end; /* Endianness of the store */
    std::unique_ptr<WrapIRExpr> addr; /* store address */
    std::unique_ptr<WrapIRExpr> data; /* value to write */
    std::unique_ptr<WrapIRExpr> guard; /* Guarding value */
} ;

/* Guarded load.  Note that this is defined to evaluate all
   expression fields (addr, alt) even if the guard evaluates
   to false.
   ppIRStmt output:
     t<tmp> = if (<guard>) <cvt>(LD<end>(<addr>)) else <alt> */
struct LoadG {
    IREndness end; /* Endianness of the load */
    IRLoadGOp cvt; /* Conversion to apply to the loaded value */
    IRTemp dst;    /* Destination (LHS) of assignment */
    std::unique_ptr<WrapIRExpr> addr; /* Address being loaded from */
    std::unique_ptr<WrapIRExpr> alt;  /* Value if load is not done. */
    std::unique_ptr<WrapIRExpr> guard; /* Guarding value */
} ;

/* Do an atomic compare-and-swap operation.  Semantics are
   described above on a comment at the definition of IRCAS.
   ppIRStmt output:
      t<tmp> = CAS<end>(<addr> :: <expected> -> <new>)
   eg
      t1 = CASle(t2 :: t3->Add32(t3,1))
      which denotes a 32-bit atomic increment
      of a value at address t2
   A double-element CAS may also be denoted, in which case <tmp>,
   <expected> and <new> are all pairs of items, separated by
   commas.
*/
struct CAS {
    IRTemp oldHi; /* old value of *addr is written here */
    IRTemp oldLo;
    IREndness end;  /* endianness of the data in memory */
    std::unique_ptr<WrapIRExpr> addr; /* store address */
    std::unique_ptr<WrapIRExpr> expdHi; /* expected old value at *addr */
    std::unique_ptr<WrapIRExpr> expdLo;
    std::unique_ptr<WrapIRExpr> dataHi; /* new value for *addr */
    std::unique_ptr<WrapIRExpr> dataLo;
} ;

/* Either Load-Linked or Store-Conditional, depending on
   STOREDATA.
   If STOREDATA is NULL then this is a Load-Linked, meaning
   that data is loaded from memory as normal, but a
   'reservation' for the address is also lodged in the
   hardware.
      result = Load-Linked(addr, end)
   The data transfer type is the type of RESULT (I32, I64,
   etc).  ppIRStmt output:
      result = LD<end>-Linked(<addr>), eg. LDbe-Linked(t1)
   If STOREDATA is not NULL then this is a Store-Conditional,
   hence:
      result = Store-Conditional(addr, storedata, end)
   The data transfer type is the type of STOREDATA and RESULT
   has type Ity_I1. The store may fail or succeed depending
   on the state of a previously lodged reservation on this
   address.  RESULT is written 1 if the store succeeds and 0
   if it fails.  eg ppIRStmt output:
      result = ( ST<end>-Cond(<addr>) = <storedata> )
      eg t3 = ( STbe-Cond(t1, t2) )
   In all cases, the address must be naturally aligned for
   the transfer type -- any misaligned addresses should be
   caught by a dominating IR check and side exit.  This
   alignment restriction exists because on at least some
   LL/SC platforms (ppc), stwcx. etc will trap w/ SIGBUS on
   misaligned addresses, and we have to actually generate
   stwcx. on the host, and we don't want it trapping on the
   host.
   Summary of rules for transfer type:
     STOREDATA == NULL (LL):
       transfer type = type of RESULT
     STOREDATA != NULL (SC):
       transfer type = type of STOREDATA, and RESULT :: Ity_I1
*/
struct LLSC {
    IREndness end;
    IRTemp result;
    std::unique_ptr<WrapIRExpr> addr;
    std::unique_ptr<WrapIRExpr> storedata; /* NULL => LL, non-NULL => SC */
} ;

/* Call (possibly conditionally) a C function that has side
   effects (ie. is "dirty").  See the comments above the
   IRDirty type declaration for more information.
   ppIRStmt output:
      t<tmp> = DIRTY <guard> <effects>
         ::: <callee>(<args>)
   eg.
      t1 = DIRTY t27 RdFX-gst(16,4) RdFX-gst(60,4)
            ::: foo{0x380035f4}(t2)
*/
struct Dirty {
    std::unique_ptr<IRCallee> cee; /* where to call */
    std::unique_ptr<WrapIRExpr> guard; /* :: Ity_Bit.  Controls whether call happens */
    /* The args vector may contain IRExpr_GSPTR() and/or
       IRExpr_VECRET(), in both cases, at most once. */
    std::vector<std::unique_ptr<WrapIRExpr>> args; /* arg vector, ends in NULL. */
    IRTemp tmp;    /* to assign result to, or IRTemp_INVALID if none */

    /* Mem effects; we allow only one R/W/M region to be stated */
    IREffect mFx;  /* indicates memory effects, if any */
    std::unique_ptr<WrapIRExpr> mAddr; /* of access, or NULL if mFx==Ifx_None */
    Int mSize;     /* of access, or zero if mFx==Ifx_None */

    /* Guest state effects; up to N allowed */
    Int nFxState; /* must be 0 .. VEX_N_FXSTATE */
    struct {
        IREffect fx : 16; /* read, write or modify?  Ifx_None is invalid. */
        UShort offset;
        UShort size;
        UChar nRepeats;
        UChar repeatLen;
    } fxState[VEX_N_FXSTATE];
    /* The access can be repeated, as specified by nRepeats and
       repeatLen.  To describe only a single access, nRepeats and
       repeatLen should be zero.  Otherwise, repeatLen must be a
       multiple of size and greater than size. */
    /* Overall, the parts of the guest state denoted by (offset,
       size, nRepeats, repeatLen) is
             [offset, +size)
          and, if nRepeats > 0,
             for (i = 1; i <= nRepeats; i++)
                [offset + i * repeatLen, +size)
       A convenient way to enumerate all segments is therefore
          for (i = 0; i < 1 + nRepeats; i++)
             [offset + i * repeatLen, +size)
    */
} ;

/* A memory bus event - a fence, or acquisition/release of the
   hardware bus lock.  IR optimisation treats all these as fences
   across which no memory references may be moved.
   ppIRStmt output: MBusEvent-Fence,
                    MBusEvent-BusLock, MBusEvent-BusUnlock.
*/
struct MBE {
    IRMBusEvent event;
} ;

/* Conditional exit from the middle of an IRSB.
   ppIRStmt output: if (<guard>) goto {<jk>} <dst>
                eg. if (t69) goto {Boring} 0x4000AAA:I32
   If <guard> is true, the guest state is also updated by
   PUT-ing <dst> at <offsIP>.  This is done because a
   taken exit must update the guest program counter.
*/
struct Exit {
    std::unique_ptr<WrapIRExpr> guard; /* Conditional expression */
    std::unique_ptr<IRConst> dst;  /* Jump target (constant only) */
    IRJumpKind jk; /* Jump kind */
    Int offsIP;    /* Guest state offset for IP */
} ;

typedef std::variant<Exit, MBE, Dirty, NoOp, IMark, AbiHint, Put, PutI, WrTmp,
                    Store, StoreG, LoadG, CAS, LLSC>
    IstVariant;

// ====================================== Actual Wrapper
// =========================================
struct WrapIRExpr {
    IRExprTag tag;
    IEXVariant var;
};
struct WrapTypeEnv {
    long types_size;
    long types_used;
    std::vector<IRType> types;
};

struct WrapIRStmt {
    IRStmtTag tag;
    IstVariant var;
};

struct WrapIRSB {
    std::unique_ptr<WrapTypeEnv> tyenv;
    std::vector<std::unique_ptr<WrapIRStmt>> stmts;
    Int stmts_size;
    Int stmts_used;
    std::unique_ptr<WrapIRExpr> next;
    IRJumpKind jumpkind;
    Int offsIP;

  public:
    std::unique_ptr<WrapTypeEnv> CopyIRTypeEnv(const IRSB *_irsb);
    std::unique_ptr<IRConst> CopyConst(const IRConst *c);
    std::vector<std::unique_ptr<vex::WrapIRExpr>>
    CopyIRExprVec(IRExpr **const _e);
    std::unique_ptr<IRRegArray> CopyRegArray(const IRRegArray *_arr);
    std::unique_ptr<WrapIRExpr> CopyIRExpr(const IRExpr *_e);
    std::unique_ptr<IRCallee> CopyCallee(const IRCallee *_calle);
    std::unique_ptr<WrapIRStmt> CopyIRStmt(const IRStmt *s);
};

class Lifter {
  private:
    WrapIRSB irsb;
    VexArchInfo vex_arch_info;

  public:
    std::unique_ptr<vex::WrapIRSB> CopyIRSB(const IRSB *_irsb);
    Lifter();
    std::unique_ptr<WrapIRSB> Lift(std::vector<uint8_t> _vec, uint64_t base_addr);
};
} // namespace vex