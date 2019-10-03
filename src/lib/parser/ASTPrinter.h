//
// Created by rvigee on 10/3/19.
//

#ifndef RISOTTOV2_ASTPRINTER_H
#define RISOTTOV2_ASTPRINTER_H


#include <lib/parser/nodes/Stmt.h>
#include <vector>
#include <lib/parser/nodes/Stmt/FunctionStmt.h>
#include <lib/parser/nodes/Stmt/PrintStmt.h>
#include <lib/parser/nodes/Stmt/IfStmt.h>
#include <lib/parser/nodes/Stmt/ReturnStmt.h>
#include <lib/parser/nodes/Expr/BinaryExpr.h>
#include <lib/parser/nodes/Expr/VariableExpr.h>
#include <lib/parser/nodes/Expr/LiteralExpr.h>
#include <lib/parser/nodes/Expr/GroupingExpr.h>
#include <lib/parser/nodes/Stmt/BlockStmt.h>
#include <lib/parser/nodes/Expr/CallExpr.h>

class ASTPrinter {
public:
    static std::string indent(std::string str, int n);

    template<typename T>
    static std::string print(T stmt);

    template<>
    std::string print<Stmt *>(Stmt * stmt);

    template<>
    std::string print<Expr *>(Expr * stmt);

    template<>
    std::string print<std::vector<Stmt *>>(std::vector<Stmt *> stmts);

    template<>
    std::string print<std::vector<Expr *>>(std::vector<Expr *> stmts);

    template<>
    std::string print<FunctionStmt *>(FunctionStmt *stmt);

    template<>
    std::string print<PrintStmt *>(PrintStmt *stmt);

    template<>
    std::string print<IfStmt *>(IfStmt *stmt);

    template<>
    std::string print<ReturnStmt *>(ReturnStmt *stmt);

    template<>
    std::string print<BinaryExpr *>(BinaryExpr *stmt);

    template<>
    std::string print<VariableExpr *>(VariableExpr *stmt);

    template<>
    std::string print<LiteralExpr *>(LiteralExpr *stmt);

    template<>
    std::string print<GroupingExpr *>(GroupingExpr *stmt);

    template<>
    std::string print<BlockStmt *>(BlockStmt *stmt);

    template<>
    std::string print<CallExpr *>(CallExpr *stmt);
};


#endif //RISOTTOV2_ASTPRINTER_H