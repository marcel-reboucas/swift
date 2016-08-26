//
//  MscrStaticAnalyzer.hpp
//  swift
//
//  Class used to handle the retrieval of static metrics.
//
//  Created by Marcel de Siqueira Campos Rebouças on 3/30/16.
//
//

#ifndef MscrStaticAnalyzer_hpp
#define MscrStaticAnalyzer_hpp

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

class MscrStaticAnalyzer
{
public:
    
    // Method used to get the instance of this Singleton.
    static MscrStaticAnalyzer* Instance();

    // Method used to handle variable (and constants) declarations.
    void handleVarDecl(swift::PatternBindingDecl *PBD);

private:
    
    MscrStaticAnalyzer();
    
    ~MscrStaticAnalyzer();
    
    // static  initialisation
    static bool g_initialised;
    
    // dynamic initialisation
    static MscrStaticAnalyzer g_instance;
    
};

#endif /* MscrStaticAnalyzer_hpp */
