//
// Created by rvigee on 10/2/19.
//

extern "C" {
#include <lib/vm/chunk.h>
}
#include <lib/compiler/Compiler.h>
#include <lib/compiler/CompilerError.h>
#include <lib/parser/nodes/TypeDescriptor.h>
#include "LogicalExpr.h"
#include "lib/compiler/ReturnTypes.h"

LogicalExpr::LogicalExpr(Expr *left, Token *op, Expr *right): left(left), op(op), right(right) {

}

std::vector<ByteResolver *>
LogicalExpr::generateOr(std::vector<ByteResolver *> leftBytes, std::vector<ByteResolver *> rightBytes, Compiler *compiler) {
    auto bytes = std::vector<ByteResolver *>();

    auto trueByte = new ByteResolver(OP_TRUE);
    auto falseByte = new ByteResolver(OP_FALSE);

    // LEFT
    bytes.insert(bytes.end(), leftBytes.begin(), leftBytes.end());

    bytes.push_back(new ByteResolver(OP_JUMPT, op->position));
    bytes.push_back(new ByteResolver([trueByte](Compiler *c){return c->getAddr(trueByte);}));

    // RIGHT
    bytes.insert(bytes.end(), rightBytes.begin(), rightBytes.end());

    bytes.push_back(new ByteResolver(OP_JUMPT, TODO_POSITION));
    bytes.push_back(new ByteResolver([trueByte](Compiler *c){return c->getAddr(trueByte);}));

    // EXIT
    bytes.insert(bytes.end(), falseByte);
    bytes.push_back(new ByteResolver(OP_JUMP, TODO_POSITION));
    bytes.push_back(new ByteResolver([trueByte](Compiler *c){return c->getAddr(trueByte) + 1;}));

    bytes.insert(bytes.end(), trueByte);

    return bytes;
}

std::vector<ByteResolver *>
LogicalExpr::generateAnd(std::vector<ByteResolver *> leftBytes, std::vector<ByteResolver *> rightBytes, Compiler *compiler) {
    auto bytes = std::vector<ByteResolver *>();

    auto trueByte = new ByteResolver(OP_TRUE);
    auto falseByte = new ByteResolver(OP_FALSE);

    // LEFT
    bytes.insert(bytes.end(), leftBytes.begin(), leftBytes.end());

    bytes.push_back(new ByteResolver(OP_JUMPF, op->position));
    bytes.push_back(new ByteResolver([falseByte](Compiler *c){return c->getAddr(falseByte);}));

    // RIGHT
    bytes.insert(bytes.end(), rightBytes.begin(), rightBytes.end());

    bytes.push_back(new ByteResolver(OP_JUMPF, TODO_POSITION));
    bytes.push_back(new ByteResolver([falseByte](Compiler *c){return c->getAddr(falseByte);}));

    // EXIT
    bytes.insert(bytes.end(), trueByte);
    bytes.push_back(new ByteResolver(OP_JUMP, TODO_POSITION));
    bytes.push_back(new ByteResolver([falseByte](Compiler *c){return c->getAddr(falseByte) + 1;}));

    bytes.insert(bytes.end(), falseByte);

    return bytes;
}

std::vector<ByteResolver *> LogicalExpr::compile(Compiler *compiler) {
    auto leftBytes = left->compile(compiler);
    auto rightBytes = right->compile(compiler);

    switch(op->type) {
        case TokenType::AND:
            return generateAnd(leftBytes, rightBytes, compiler);
        case TokenType::OR:
            return generateOr(leftBytes, rightBytes, compiler);
    }

    throw CompilerError("Unhandled logical operator", op->position);
}

ReturnTypes LogicalExpr::computeReturnType(Compiler *compiler) {
    return compiler->frame->types.findNamed("bool");
}

void LogicalExpr::symbolize(Compiler *compiler) {
    left->symbolize(compiler);
    right->symbolize(compiler);
}
