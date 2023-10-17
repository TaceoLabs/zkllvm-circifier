#ifndef LLVM_ZK_FIXED_ARITHMETICS_H
#define LLVM_ZK_FIXED_ARITHMETICS_H

#include "llvm/ADT/ZkFixedPoint.h"

namespace llvm {

enum ZkFixedOperation {
  Fix_Add,
  Fix_Sub,
  Fix_Mul,
  Fix_Div,
  Fix_Rem,
};

ZkFixedPoint FixedBinOp(ZkFixedOperation Op, const ZkFixedPoint &LHS,
                        const ZkFixedPoint &RHS);

} // namespace llvm

#endif // LLVM_ZK_FIELD_ARITHMETICS_H
