//
// Created by raphael on 10/04/18.
//

#include <stdio.h>

#include "debug.h"

void printValue(Value value) {
    switch (TGET(value)) {
        case T_NIL:
        case T_P:
        case T_UINT:
        case T_INT:
        case T_DOUBLE:
        case T_ARRAY:
        case T_BOOL:
            printf("%s", v2s(value));
            return;
        case T_STR:
            printf("`%s`", v2s(value));
            return;
        case T_OBJECT: {
            Object *object = v2o(value);
            printf("O: %p {", object->values);
            for (int i = 0; i < object->size; ++i) {
                Value v = object->values[i];
                if (typecheck(v, T_OBJECT) && v2o(v) == object) {
                    printf("<self>");
                } else {
                    printValue(v);
                }

                if (i != object->size - 1) {
                    printf(", ");
                }
            }
            printf("}");
            return;
        }
        case T_VALUE_P: {
            printf("+");
            Value *vp = (Value *) DGET(value, p);
            printValue(*vp);
            return;
        }
    }

    printf("# Unknown type: %p #", &value);
}

void disassembleChunk(Chunk *chunk, const char *name) {
    printf("== %s ==\n", name);

    for (int i = 0; i < chunk->count;) {
        i = disassembleInstruction(chunk, i);
    }

    printf("== end %s ==\n", name);
}

static int simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
    OP_T constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    if (constant <= chunk->constants.object.size) {
        printValue(chunk->constants.object.values[constant]);
    } else {
        printf("# Constant '%d' not found #", constant);
    }
    printf("'\n");
    return offset + 2;
}

static int addrInstruction(const char *name, Chunk *chunk, int offset) {
    int addr = chunk->code[offset + 1];
    printf("%-16s => %4d \n", name, addr);
    return offset + 2;
}

static int biIntInstruction(const char *name, const char *l1, const char *l2, Chunk *chunk, int offset) {
    int dist = chunk->code[offset + 1];
    int addr = chunk->code[offset + 2];
    printf("%-11s %s:%-3d %s:%-3d \n", name, l1, dist, l2, addr);

    return offset + 3;
}

static int callInstruction(const char *name, Chunk *chunk, int offset) {
//    bool needReso = chunk->code[offset + 1];
//    int c = chunk->code[offset + 2];
//    printf("%-11s C:%-3d %i\n", name, c, needReso);
//
//    return offset + 3 + c;

    int c = chunk->code[offset + 1];
    printf("%-11s C:%-3d\n", name, c);

    return offset + 2 + c;
}

static int newInstruction(const char *name, Chunk *chunk, int offset) {
    int vtableAddr = chunk->code[offset + 1];
    int c = chunk->code[offset + 2];
    printf("%-11s VA: ", name);
    printValue(chunk->constants.object.values[vtableAddr]);
    printf(" C:%-3d\n", c);

    return offset + 3 + c;
}

static int intInstruction(const char *name, Chunk *chunk, int offset) {
    int i = chunk->code[offset + 1];
    printf("%-16s %4d \n", name, i);

    return offset + 2;
}

#define NAME(op) case op: return #op;

char *getName(OP_T instruction) {
    switch (instruction) {
        NAME(OP_SET)
        NAME(OP_NOOP)
        NAME(OP_FRAME)
        NAME(OP_FRAME_END)
        NAME(OP_CONST)
        NAME(OP_RETURN)
        NAME(OP_JUMP)
        NAME(OP_JUMPT)
        NAME(OP_JUMPF)
        NAME(OP_END)
        NAME(OP_LOAD)
        NAME(OP_LOAD_GLOBAL)
        NAME(OP_LOAD_STACK)
        NAME(OP_LOAD_LOCAL)
        NAME(OP_LOAD_INSTANCE)
        NAME(OP_ARRAY)
        NAME(OP_ARRAY_INSERT)
        NAME(OP_CALL)
        NAME(OP_POP)
        NAME(OP_COPY)
        NAME(OP_NIL)
        NAME(OP_TRUE)
        NAME(OP_FALSE)
        NAME(OP_EQ)
        NAME(OP_NEQ)
        NAME(OP_EQ_NIL)
        NAME(OP_NEQ_NIL)
        NAME(OP_NEW)
        NAME(OP_RESOLVE_ADDR)
        NAME(OP_IADD)
        NAME(OP_ISUB)
        NAME(OP_IMUL)
        NAME(OP_IDIV)
        NAME(OP_IMOD)
        NAME(OP_ILT)
        NAME(OP_IGT)
        default:
            return "Unknown opcode";
    }
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    int line = chunk->lines[offset];
    int previousLine = chunk->lines[offset - 1];

    if (offset == 0 && line == 0) {
        line = 1;
    }

    if (offset > 0 && (line == 0 || line == previousLine)) {
        printf("   | ");
    } else {
        printf("%4d ", line);
    }

    OP_T instruction = chunk->code[offset];
    switch (instruction) {
        case OP_IADD:
            return simpleInstruction(getName(instruction), offset);
        case OP_ISUB:
            return simpleInstruction(getName(instruction), offset);
        case OP_IMUL:
            return simpleInstruction(getName(instruction), offset);
        case OP_IDIV:
            return simpleInstruction(getName(instruction), offset);
        case OP_ILT:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_IGT:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_EQ:
            return simpleInstruction(getName(instruction), offset);
        case OP_NEQ:
            return simpleInstruction(getName(instruction), offset);
        case OP_SET:
            return simpleInstruction(getName(instruction), offset);
        case OP_NOOP:
            return simpleInstruction(getName(instruction), offset);
        case OP_FRAME:
            return simpleInstruction(getName(instruction), offset);
        case OP_FRAME_END:
            return simpleInstruction(getName(instruction), offset);
        case OP_CONST:
            return constantInstruction(getName(instruction), chunk, offset);
        case OP_RETURN:
            return biIntInstruction(getName(instruction), "D", "C", chunk, offset);
        case OP_JUMP:
            return addrInstruction(getName(instruction), chunk, offset);
        case OP_JUMPT:
            return addrInstruction(getName(instruction), chunk, offset);
        case OP_JUMPF:
            return addrInstruction(getName(instruction), chunk, offset);
        case OP_END:
            return simpleInstruction(getName(instruction), offset);
        case OP_LOAD:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_LOAD_GLOBAL:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_RESOLVE_ADDR    :
            return intInstruction(getName(instruction), chunk, offset);
        case OP_LOAD_STACK:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_LOAD_LOCAL:
            return biIntInstruction(getName(instruction), "D", "A", chunk, offset);
        case OP_LOAD_INSTANCE:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_ARRAY:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_ARRAY_INSERT:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_CALL:
            return callInstruction(getName(instruction), chunk, offset);
        case OP_POP:
            return intInstruction(getName(instruction), chunk, offset);
        case OP_COPY:
            return simpleInstruction(getName(instruction), offset);
        case OP_NIL:
            return simpleInstruction(getName(instruction), offset);
        case OP_TRUE:
            return simpleInstruction(getName(instruction), offset);
        case OP_FALSE:
            return simpleInstruction(getName(instruction), offset);
        case OP_EQ_NIL:
            return simpleInstruction(getName(instruction), offset);
        case OP_NEQ_NIL:
            return simpleInstruction(getName(instruction), offset);
        case OP_NEW:
            return newInstruction(getName(instruction), chunk, offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

void printVtable(Value v) {
    if (v.vtable == NULL) {
        printf("<null>\n");
        return;
    }

    printf("==== vtable %p ====\n", v.vtable);
    printf("%-4s %-4s %s\n", "i", "va", "a");

    int i;
    vtable_entry *entry;
    vec_foreach_ptr(&v.vtable->addrs, entry, i) {
            printf("%-4d %-4d ", i, entry->vaddr);
            printValue(entry->addr);
            printf("\n");
        }

    printf("================\n");
}
