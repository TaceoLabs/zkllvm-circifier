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

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ZK/ZKEnums.h"
#include <cassert>

namespace llvm {

/// ZK Fixed Point element.
class [[nodiscard]] ZkFixedPoint {

  APFloat F;
  ZkFixedPointKind Kind;
  size_t BitWidth;

public:
  //  ZkFixedPoint() : APFloat(fltSemantics.),
  //  Kind(static_cast<ZkFixedPointKind>(0)) {}
  ZkFixedPoint()
      : F(0.0), Kind(ZkFixedPointKind::ZK_FIXED_POINT_16_16), BitWidth(64) {}
  ZkFixedPoint(ZkFixedPointKind K, APFloat F) : F(F), Kind(K), BitWidth(64) {
    // assert(&F.getSemantics() == &F.IEEEdouble() &&
    //        "FixedPoints must be represented as Double");
  }

  ZkFixedPointKind getKind() const { return Kind; }

  ZkFixedPoint &operator+=(const ZkFixedPoint &other);

  size_t getBitWidth() const { return BitWidth; }

  double getValue() {
    // assert(&F.getSemantics() == &F.IEEEdouble() &&
    // "FixedPoints must be represented as Double");
    return F.convertToDouble();
  }

  const APFloat &getValueAPF() const { return F; }

  bool needsCleanup() const { return F.needsCleanup(); }

  APInt bitcastToAPInt() const { return F.bitcastToAPInt(); }

  bool isZero() { return F.isZero(); }

private:
  static inline ZkFixedPoint getEmptyKey() {
    ZkFixedPoint key(ZkFixedPointKind::ZK_FIXED_POINT_16_16, APFloat(0.0));
    key.BitWidth = 0;
    return key;
  }

  static inline ZkFixedPoint getTombstoneKey() {
    ZkFixedPoint key(ZkFixedPointKind::ZK_FIXED_POINT_16_16, APFloat(0.0));
    key.BitWidth = 1;
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
    return hash_combine(Key.getKind(), hash_value(Key.F));
  }

  static bool isEqual(const ZkFixedPoint &LHS, const ZkFixedPoint &RHS) {
    return LHS.getBitWidth() == RHS.getBitWidth() &&
           LHS.getKind() == RHS.getKind() && LHS.F == RHS.F;
  }
};
} // namespace llvm

#endif // LLVM_ADT_ZKFIXEDPOINT_H
