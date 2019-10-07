//
// Created by rvigee on 10/2/19.
//

#ifndef RISOTTOV2_IDENTIFIEREXPR_H
#define RISOTTOV2_IDENTIFIEREXPR_H


#include <lib/tokenizer/Token.h>
#include <lib/parser/nodes/Expr.h>

class IdentifierExpr: public Expr {
public:
    Token *name;

    explicit IdentifierExpr(Token *name);

    std::vector<ByteResolver *> compile(Compiler *compiler) override;

protected:
    TypesEntries computeReturnType(Compiler *compiler) override;
};


#endif //RISOTTOV2_IDENTIFIEREXPR_H
