//
//  MscrStaticAnalyzer.cpp
//  swift
//
//  Created by Marcel de Siqueira Campos Rebouças on 3/30/16.
//
//

#include "swift/AST/MscrStaticAnalyzer.hpp"

#include "swift/Basic/QuotedString.h"
#include "swift/AST/AST.h"
#include "swift/AST/ASTPrinter.h"
#include "swift/AST/ASTVisitor.h"
#include "swift/AST/ForeignErrorConvention.h"
#include "swift/AST/ParameterList.h"
#include "swift/AST/TypeVisitor.h"
#include "swift/Basic/STLExtras.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/SaveAndRestore.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/FileSystem.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace swift;

// static  initialisation
bool MscrStaticAnalyzer::g_initialised;

// dynamic initialisation
MscrStaticAnalyzer MscrStaticAnalyzer::g_instance;

//===----------------------------------------------------------------------===//
//===                           Singleton Methods                          ===//
//===----------------------------------------------------------------------===//

// Singleton constructor.
MscrStaticAnalyzer::MscrStaticAnalyzer()
{
    g_initialised = true;
}

MscrStaticAnalyzer::~MscrStaticAnalyzer()
{
    g_initialised = false;
}

// Method used to get the instance of this Singleton.
MscrStaticAnalyzer* MscrStaticAnalyzer::Instance()
{
    return g_initialised ? &g_instance : 0;
}

//===----------------------------------------------------------------------===//
//===                       Component Handler Methods                      ===//
//===----------------------------------------------------------------------===//


// Method used to handle variable (and constant) declarations.
void MscrStaticAnalyzer::handleVarDecl(swift::PatternBindingDecl *PBD) {
    
    std::error_code EC;
    llvm::raw_fd_ostream os("build-metrics-output.txt", EC, llvm::sys::fs::OpenFlags::F_Append);
    
    for (unsigned i = 0, e = PBD->getNumPatternEntries(); i != e; ++i) {
        auto entry = PBD->getPatternList()[i];
    
        
        entry.getPattern()->forEachVariable([&](VarDecl *var) {
            
            if (auto Ty = var->getType()) {
                auto &Ctx = Ty->getASTContext();
                auto L = var->getLoc();
                if (L.isValid()) {
                    os << " location=";
                    L.print(os, Ctx.SourceMgr);
                }
            }
            
            if (var->isLet()) {
                 os << " Found new let decl! ";
            } else {
                 os << " Found new var decl! ";
            }
           
            os << " Name: " << var->getFullName();
            os << " IsLet: " << var->isLet();
            
            if (var->hasType()) {
                os << " Type: " << var->getType();
            }
            
            os << "\n";
        });
    }
}
