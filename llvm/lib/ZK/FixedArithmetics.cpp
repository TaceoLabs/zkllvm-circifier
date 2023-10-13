#include "llvm/ZK/FixedArithmetics.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallString.h"

namespace llvm {

unsigned GetNumberBits(ZkFixedPointKind Kind) {
  switch (Kind) {
  case ZK_FIXED_POINT_16_16:
    return 32; // TODO: is this what we want?
  }
  llvm_unreachable("Unspecified fixed kind");
}

ZkFixedPoint FixedBinOp(ZkFixedOperation Op, const ZkFixedPoint &LHS,
                        const ZkFixedPoint &RHS) {
  assert(LHS.getKind() == RHS.getKind());
  llvm_unreachable("TACEO TODO Do we need this?????");
  switch (LHS.getKind()) {
  case ZK_FIXED_POINT_16_16:
    // TODO: implement
    break;
  }
}

} // namespace llvm
