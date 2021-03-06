//
// Created by rvigee on 10/3/19.
//

#ifndef RISOTTOV2_BYTERESOLVER_H
#define RISOTTOV2_BYTERESOLVER_H


#include <functional>
#include <lib/tokenizer/Token.h>
extern "C" {
#include <lib/vm/common.h>
}

#define TODO_POSITION {}

class Compiler;

class ByteResolver {
public:
    bool final;
    std::function<OP_T(Compiler *c)> resolver = nullptr;
    OP_T byte = -1;
    Position position = {};

    explicit ByteResolver(OP_T byte, Position position);
    explicit ByteResolver(OP_T byte);
    explicit ByteResolver(std::function<OP_T(Compiler *c)> resolver, Position position);
    explicit ByteResolver(std::function<OP_T(Compiler *c)> resolver);

    void finalize(Compiler *c);
};


#endif //RISOTTOV2_BYTERESOLVER_H
