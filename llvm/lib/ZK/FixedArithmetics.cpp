#include "llvm/ZK/FixedArithmetics.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallString.h"

namespace llvm {

unsigned GetNumberBits(ZkFixedPointKind Kind) {
  switch (Kind) {
  case ZK_FIXED_POINT_16_16:
    return 32;
  }
  llvm_unreachable("Unspecified fixed kind");
}

ZkFixedPoint FixedBinOp(ZkFixedOperation Op, const ZkFixedPoint &LHS,
                        const ZkFixedPoint &RHS) {
  assert(LHS.getKind() == RHS.getKind());
  switch (LHS.getKind()) {
  case ZK_FIXED_POINT_16_16:
    // TODO: implement
    break;
  }
}

} // namespace llvm
