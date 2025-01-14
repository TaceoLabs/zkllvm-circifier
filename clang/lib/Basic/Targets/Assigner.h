//===--- Assigner.h - Declare Assigner target feature support ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares Assigner TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_ASSIGNER_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_ASSIGNER_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY AssignerTargetInfo : public TargetInfo {
  static const Builtin::Info BuiltinInfo[];

public:
  AssignerTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    LongWidth = LongAlign = PointerWidth = PointerAlign = 64;
    RegParmMax = 255;
    // copied from x64_86:
    resetDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
    MaxAtomicPromoteWidth = 64;
    MaxAtomicInlineWidth = 64;
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  void setFeatureEnabled(llvm::StringMap<bool> &Features, StringRef Name,
                         bool Enabled) const override {
    Features[Name] = Enabled;
  }

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  const char *getClobbers() const override { return ""; }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  bool isValidGCCRegisterName(StringRef Name) const override { return true; }
  ArrayRef<const char *> getGCCRegNames() const override { return std::nullopt; }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return true;
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }

  bool allowDebugInfoForExternalRef() const override { return true; }
};
} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_ASSIGNER_H
