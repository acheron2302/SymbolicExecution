#include "Analysis/LiftWrapper.h"

std::unique_ptr<vex::WrapTypeEnv>
vex::WrapIRSB::CopyIRTypeEnv(const IRSB *_irsb) {
    auto dst = std::make_unique<WrapTypeEnv>();
    dst->types_size = _irsb->tyenv->types_size;
    dst->types_used = _irsb->tyenv->types_used;
    for (int i = 0; i < dst->types_used; i++) {
        dst->types.push_back(_irsb->tyenv->types[i]);
    }
    return dst;
}

std::unique_ptr<IRConst> vex::WrapIRSB::CopyConst(const IRConst *_c) {
    std::unique_ptr<IRConst> c;
    switch (c->tag) {
    case Ico_U1:
        c->tag = Ico_U1;
        c->Ico.U1 = _c->Ico.U1;
        break;
    case Ico_U8:
        c->tag = Ico_U8;
        c->Ico.U1 = _c->Ico.U8;
        break;
    case Ico_U16:
        c->tag = Ico_U16;
        c->Ico.U1 = _c->Ico.U16;
        break;
    case Ico_U32:
        c->tag = Ico_U32;
        c->Ico.U1 = _c->Ico.U32;
        break;
    case Ico_U64:
        c->tag = Ico_U64;
        c->Ico.U1 = _c->Ico.U64;
        break;
    case Ico_F32:
        c->tag = Ico_F32;
        c->Ico.U1 = _c->Ico.F32;
        break;
    case Ico_F32i:
        c->tag = Ico_F32i;
        c->Ico.U1 = _c->Ico.F32i;
        break;
    case Ico_F64:
        c->tag = Ico_F64;
        c->Ico.U1 = _c->Ico.F64;
        break;
    case Ico_F64i:
        c->tag = Ico_F64i;
        c->Ico.U1 = _c->Ico.F64i;
        break;
    case Ico_V128:
        c->tag = Ico_V128;
        c->Ico.U1 = _c->Ico.V128;
        break;
    case Ico_V256:
        c->tag = Ico_V256;
        c->Ico.U1 = _c->Ico.V256;
        break;
    default:
        throw std::invalid_argument("vex::WrapIRSB::CopyConst");
    }
    return c;
}

std::vector<std::unique_ptr<vex::WrapIRExpr>>
vex::WrapIRSB::CopyIRExprVec(IRExpr **const _vec) {
    size_t size;
    for (size = 0; _vec[size]; size++)
        ;
    std::vector<std::unique_ptr<vex::WrapIRExpr>> result;
    for (int i = 0; i < size; i++) {
        result.push_back(CopyIRExpr(_vec[i]));
    }
    return result;
}

std::unique_ptr<IRRegArray>
vex::WrapIRSB::CopyRegArray(const IRRegArray *_arr) {
    auto temp_array = std::make_unique<IRRegArray>();
    temp_array->base = _arr->base;
    temp_array->elemTy = _arr->elemTy;
    temp_array->nElems = _arr->nElems;
    return temp_array;
}

std::unique_ptr<vex::WrapIRExpr> vex::WrapIRSB::CopyIRExpr(const IRExpr *_e) {

    auto result = std::make_unique<vex::WrapIRExpr>();
    result->tag = _e->tag;
    switch (_e->tag) {
    case Iex_Get:
        vex::Get temp;
        temp.offset = _e->Iex.Get.offset;
        temp.ty = _e->Iex.Get.ty;
        result->var = temp;
        break;
    case Iex_GetI: {
        vex::GetI temp3;
        temp3.descr = CopyRegArray(_e->Iex.GetI.descr);
        temp3.bias = _e->Iex.GetI.bias;
        temp3.ix = std::move(CopyIRExpr(_e->Iex.GetI.ix));
        result->var = std::move(temp3);
        break;
    }
    case Iex_RdTmp:
        vex::RdTmp temp2;
        temp2.tmp = _e->Iex.RdTmp.tmp;
        result->var = temp2;
        break;

    case Iex_Qop: {
        vex::Qop temp4;
        temp4.op = _e->Iex.Qop.details->op;
        temp4.arg1 = std::move(CopyIRExpr(_e->Iex.Qop.details->arg1));
        temp4.arg2 = std::move(CopyIRExpr(_e->Iex.Qop.details->arg2));
        temp4.arg3 = std::move(CopyIRExpr(_e->Iex.Qop.details->arg3));
        temp4.arg4 = std::move(CopyIRExpr(_e->Iex.Qop.details->arg4));
        result->var = std::move(temp4);
        break;
    }
    case Iex_Triop: {
        vex::Triop temp5;
        temp5.op = _e->Iex.Triop.details->op;
        temp5.arg1 = std::move(CopyIRExpr(_e->Iex.Triop.details->arg1));
        temp5.arg2 = std::move(CopyIRExpr(_e->Iex.Triop.details->arg2));
        temp5.arg3 = std::move(CopyIRExpr(_e->Iex.Triop.details->arg3));
        result->var = std::move(temp5);
        break;
    }
    case Iex_Binop: {
        vex::Binop temp6;
        temp6.op = _e->Iex.Binop.op;
        temp6.arg1 = std::move(CopyIRExpr(_e->Iex.Binop.arg1));
        temp6.arg2 = std::move(CopyIRExpr(_e->Iex.Binop.arg2));
        result->var = std::move(temp6);
        break;
    }
    case Iex_Unop: {
        vex::Unop temp7;
        temp7.op = _e->Iex.Unop.op;
        temp7.arg = std::move(CopyIRExpr(_e->Iex.Unop.arg));
        result->var = std::move(temp7);
        break;
    }
    case Iex_Load: {
        vex::Load temp8;
        temp8.end = _e->Iex.Load.end;
        temp8.ty = _e->Iex.Load.ty;
        temp8.addr = std::move(CopyIRExpr(_e->Iex.Load.addr));
        result->var = std::move(temp8);
        break;
    }
    case Iex_Binder: {
        vex::Binder temp9;
        temp9.binder = _e->Iex.Binder.binder;
        result->var = temp9;
        break;
    }
    case Iex_GSPTR:
        break;
    case Iex_VECRET:
        break;
    case Iex_ITE: {
        vex::ITE temp10;
        temp10.cond = std::move(CopyIRExpr(_e->Iex.ITE.cond));
        temp10.iftrue = std::move(CopyIRExpr(_e->Iex.ITE.iftrue));
        temp10.iffalse = std::move(CopyIRExpr(_e->Iex.ITE.iffalse));
        result->var = std::move(temp10);
        break;
    }
    case Iex_CCall: {
        vex::CCall temp11;
        temp11.cee = CopyCallee(_e->Iex.CCall.cee);
        temp11.retty = _e->Iex.CCall.retty;
        temp11.args = CopyIRExprVec(_e->Iex.CCall.args);
        result->var = std::move(temp11);
        break;
    }
    }
    return result;
}

std::unique_ptr<IRCallee> vex::WrapIRSB::CopyCallee(const IRCallee *_calle) {
    auto callee = std::make_unique<IRCallee>();
    *callee = *_calle;
    return callee;
}

std::unique_ptr<vex::WrapIRStmt> vex::WrapIRSB::CopyIRStmt(const IRStmt *s) {
    auto result = std::make_unique<vex::WrapIRStmt>();
    result->tag = s->tag;
    switch (s->tag) {
    case Ist_NoOp:
        break;
    case Ist_AbiHint: {
        AbiHint temp1;
        temp1.base = CopyIRExpr(s->Ist.AbiHint.base);
        temp1.len = s->Ist.AbiHint.len;
        temp1.nia = CopyIRExpr(s->Ist.AbiHint.nia);
        result->var = std::move(temp1);
        break;
    }
    case Ist_Put: {

        Put temp2;
        temp2.offset = s->Ist.Put.offset;
        temp2.data = CopyIRExpr(s->Ist.Put.data);
        result->var = std::move(temp2);
        break;
    }
    case Ist_PutI: {
        PutI temp3;
        temp3.bias = s->Ist.PutI.details->bias;
        temp3.data = CopyIRExpr(s->Ist.PutI.details->data);
        temp3.descr = CopyRegArray(s->Ist.PutI.details->descr);
        temp3.ix = CopyIRExpr(s->Ist.PutI.details->ix);
        result->var = std::move(temp3);
        break;
    }
    case Ist_WrTmp: {
        WrTmp temp4;
        temp4.tmp = s->Ist.WrTmp.tmp;
        temp4.data = CopyIRExpr(s->Ist.WrTmp.data);
        result->var = std::move(temp4);
        break;
    }
    case Ist_Store: {
        Store temp5;
        temp5.end = s->Ist.Store.end;
        temp5.addr = CopyIRExpr(s->Ist.Store.addr);
        temp5.data = CopyIRExpr(s->Ist.Store.data);
        result->var = std::move(temp5);
        break;
    }
    case Ist_StoreG: {
        StoreG temp6;
        temp6.addr = CopyIRExpr(s->Ist.StoreG.details->addr);
        temp6.data = CopyIRExpr(s->Ist.StoreG.details->data);
        temp6.end = s->Ist.StoreG.details->end;
        temp6.guard = CopyIRExpr(s->Ist.StoreG.details->guard);
        result->var = std::move(temp6);
        break;
    }
    case Ist_LoadG: {
        LoadG temp7;
        temp7.end = s->Ist.LoadG.details->end;
        temp7.addr = CopyIRExpr(s->Ist.LoadG.details->addr);
        temp7.alt = CopyIRExpr(s->Ist.LoadG.details->alt);
        temp7.cvt = s->Ist.LoadG.details->cvt;
        temp7.dst = s->Ist.LoadG.details->dst;
        temp7.guard = CopyIRExpr(s->Ist.LoadG.details->guard);
        result->var = std::move(temp7);
        break;
    }
    case Ist_CAS: {
        CAS temp8;
        temp8.addr = CopyIRExpr(s->Ist.CAS.details->addr);
        temp8.dataHi = CopyIRExpr(s->Ist.CAS.details->dataHi);
        temp8.dataLo = CopyIRExpr(s->Ist.CAS.details->dataLo);
        temp8.expdHi = CopyIRExpr(s->Ist.CAS.details->expdHi);
        temp8.expdLo = CopyIRExpr(s->Ist.CAS.details->expdLo);
        temp8.end = s->Ist.CAS.details->end;
        temp8.oldHi = s->Ist.CAS.details->oldHi;
        temp8.oldLo = s->Ist.CAS.details->oldLo;
        result->var = std::move(temp8);
        break;
    }
    case Ist_LLSC: {
        LLSC temp9;
        temp9.addr = CopyIRExpr(s->Ist.LLSC.addr);
        temp9.end = s->Ist.LLSC.end;
        temp9.result = s->Ist.LLSC.result;
        temp9.storedata = CopyIRExpr(s->Ist.LLSC.storedata);
        result->var = std::move(temp9);
        break;
    }
    case Ist_Dirty: {
        Dirty temp10;
        temp10.args = CopyIRExprVec(s->Ist.Dirty.details->args);
        temp10.cee = CopyCallee(s->Ist.Dirty.details->cee);
        // we have to do this because C++ doesn't allow to copy type with
        // unknown name
        for (int i = 0; i < VEX_N_FXSTATE; i++) {
            temp10.fxState[i].fx = s->Ist.Dirty.details->fxState[i].fx;
            temp10.fxState[i].offset = s->Ist.Dirty.details->fxState[i].offset;
            temp10.fxState[i].nRepeats =
                s->Ist.Dirty.details->fxState[i].nRepeats;
            temp10.fxState[i].repeatLen =
                s->Ist.Dirty.details->fxState[i].repeatLen;
            temp10.fxState[i].size = s->Ist.Dirty.details->fxState[i].size;
        }
        temp10.guard = CopyIRExpr(s->Ist.Dirty.details->guard);
        temp10.mAddr = CopyIRExpr(s->Ist.Dirty.details->mAddr);
        temp10.mFx = s->Ist.Dirty.details->mFx;
        temp10.mSize = s->Ist.Dirty.details->mSize;
        temp10.nFxState = s->Ist.Dirty.details->nFxState;
        temp10.tmp = s->Ist.Dirty.details->tmp;
        result->var = std::move(temp10);
        break;
    }
    case Ist_MBE: {
        MBE temp11;
        temp11.event = s->Ist.MBE.event;
        break;
    }
    case Ist_Exit: {
        Exit temp12;
        temp12.dst = CopyConst(s->Ist.Exit.dst);
        temp12.guard = CopyIRExpr(s->Ist.Exit.guard);
        temp12.jk = s->Ist.Exit.jk;
        temp12.offsIP = s->Ist.Exit.offsIP;
        result->var = std::move(temp12);
        break;
    }
    }
    return result;
}

std::unique_ptr<vex::WrapIRSB> vex::Lifter::CopyIRSB(const IRSB *_irsb) {
    auto irsb = std::make_unique<vex::WrapIRSB>();
    irsb->tyenv = irsb->CopyIRTypeEnv(_irsb);
    irsb->next = irsb->CopyIRExpr(_irsb->next);
    irsb->jumpkind = _irsb->jumpkind;
    irsb->offsIP = _irsb->offsIP;
    irsb->stmts_used = irsb->stmts_size = _irsb->stmts_used;
    for (int i = 0; i < irsb->stmts_used; i++) {
        auto stmt = irsb->CopyIRStmt(_irsb->stmts[i]);
        irsb->stmts.push_back(std::move(stmt));
    }
    return irsb;
}

vex::Lifter::Lifter() {
    vex_init();
    this->vex_arch_info.endness = VexEndnessLE;
    vex_arch_info.x86_cr0 = 0xFFFFFFFF;
    vex_arch_info.hwcache_info.caches = nullptr;
}

std::unique_ptr<vex::WrapIRSB> vex::Lifter::Lift(std::vector<uint8_t> _vec,
                                                 uint64_t _base_addr) {
    auto lifted =
        vex_lift(VexArchAMD64, vex_arch_info, _vec.data(), _base_addr, 99,
                 _vec.size(), 1, 0, 0, 1, 0, VexRegUpdUnwindregsAtMemAccess, 0);
    auto irsb = CopyIRSB(lifted->irsb);
    return irsb;
}
