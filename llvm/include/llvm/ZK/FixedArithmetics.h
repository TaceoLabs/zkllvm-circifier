#ifndef LLVM_ZK_FIELD_ARITHMETICS_H
#define LLVM_ZK_FIELD_ARITHMETICS_H

#include "llvm/ADT/ZkFixedPoint.h"

namespace llvm {

enum ZkFixedOperation {
  F_Add,
  F_Sub,
  F_Mul,
  F_Div,
  F_Rem,
};

ZkFixedPoint FixedBinOp(ZkFixedOperation Op, const ZkFixedPoint &LHS,
                        const ZkFixedPoint &RHS);

} // namespace llvm

#endif // LLVM_ZK_FIELD_ARITHMETICS_H
