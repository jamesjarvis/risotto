//
// Created by rvigee on 10/8/19.
//
extern "C" {
#include <lib/vm/chunk.h>
}

#include "ArrayExpr.h"
#include <utility>
#include <lib/compiler/Compiler.h>
#include "lib/parser/nodes/TypeDescriptor.h"
#include "lib/compiler/ReturnTypes.h"

ArrayExpr::ArrayExpr(TypeDescriptor *type, std::vector<Expr *> elements) : type(type), elements(std::move(elements)) {

}

std::vector<ByteResolver *> ArrayExpr::compile(Compiler *compiler) {
    auto bytes = std::vector<ByteResolver *>();

    for (auto it = this->elements.rbegin(); it != this->elements.rend(); ++it) {
        auto e = (*it)->compile(compiler);
        bytes.insert(bytes.end(), e.begin(), e.end());
    }

    bytes.push_back(new ByteResolver(OP_ARRAY, TODO_POSITION));
    bytes.push_back(new ByteResolver(static_cast<int>(elements.size())));

    return bytes;
}

ReturnTypes ArrayExpr::computeReturnType(Compiler *compiler) {
    return type;
}

void ArrayExpr::symbolize(Compiler *compiler) {
    compiler->typesManager->createLinkUnits(type, compiler->frame);

    for(auto element: elements) {
        element->symbolize(compiler);
    }
}
