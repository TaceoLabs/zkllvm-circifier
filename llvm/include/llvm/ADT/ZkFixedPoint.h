//===-- llvm/ADT/ZkFixedPoint.h ----- ZK Fixed Point --------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file implements the ZkFixedPoint class, which is a simple class that
/// represents a fixed point number for ZK uses.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_ADT_ZKFIXEDPOINT_H
#define LLVM_ADT_ZKFIXEDPOINT_H

#include "llvm/ADT/APInt.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ZK/ZKEnums.h"

namespace llvm {

/// ZK Fixed Point element.
class [[nodiscard]] ZkFixedPoint : public APInt {
  ZkFixedPointKind Kind;

public:
  ZkFixedPoint() : APInt(), Kind(static_cast<ZkFixedPointKind>(0)) {}
  ZkFixedPoint(ZkFixedPointKind k, APInt v)
      : APInt(v.zext(GetNumberBits(k) + 1)), Kind(k) {} // +1 for sign

  ZkFixedPointKind getKind() const { return Kind; }

  ZkFixedPoint &operator+=(const ZkFixedPoint &other);

  uint64_t *getData() const {
    assert(!isSingleWord());
    return U.pVal;
  }

private:
  static inline ZkFixedPoint getEmptyKey() {
    ZkFixedPoint key;
    key.BitWidth = 0;
    key.U.VAL = ~0ULL;
    return key;
  }

  static inline ZkFixedPoint getTombstoneKey() {
    ZkFixedPoint key;
    key.BitWidth = 0;
    key.U.VAL = ~1ULL;
    return key;
  }

  friend struct DenseMapInfo<ZkFixedPoint, void>;
};

inline ZkFixedPoint operator+(ZkFixedPoint a, const ZkFixedPoint &b) {
  a += b;
  return a;
}

/// Provide DenseMapInfo for APSInt, using the DenseMapInfo for APInt.
template <> struct DenseMapInfo<ZkFixedPoint, void> {
  static inline ZkFixedPoint getEmptyKey() {
    return ZkFixedPoint::getEmptyKey();
  }

  static inline ZkFixedPoint getTombstoneKey() {
    return ZkFixedPoint::getTombstoneKey();
  }

  static unsigned getHashValue(const ZkFixedPoint &Key) {
    return hash_combine(Key.getKind(),
                        DenseMapInfo<APInt, void>::getHashValue(Key));
  }

  static bool isEqual(const ZkFixedPoint &LHS, const ZkFixedPoint &RHS) {
    return LHS.getBitWidth() == RHS.getBitWidth() &&
           LHS.getKind() == RHS.getKind() && LHS == RHS;
  }
};
} // namespace llvm

#endif // LLVM_ADT_ZKFIXEDPOINT_H
