//
// Created by raphael on 21/06/18.
//

#include <gtest/gtest.h>
#include "../common.h"

//#define OPERATOR_INPUT(op) "println(-2.1 " #op " 2) println(2 " #op " -2.2) println(2.0 " #op " 2.0) println(1 " #op " 2)"
#define OPERATOR_INPUT(op) "println(1.0 " #op " 2) println(1 " #op " 2.0) println(1 " #op " 2)"
#define SHORTHAND_OPERATOR_INPUT(op) "var a = 1 println(a) a " #op " 2 println(a) a " #op " 5 println(a)"
#define LOGICAL_OPERATOR_INPUT(op) "println(true " #op " false) println(false " #op " true) println(true " #op " true) println(false " #op " false)"

TEST(Operators, Precedence) {
    INIT_TEST

    risotto.run("println(2 + 3 % 4 * 5) println(2 + ((3 % 4) * 5)) println(2 + (3 * 5)) println(2 + 15)");

    EXPECT_STDOUT("17\n17\n17\n17\n");
}

TEST(Operators, DISABLED_UnaryPrefixMinus) {
    INIT_TEST

    risotto.run("println(-2) println(-(-2)) println(- -2) println(-2.0) println(-(-2.0)) println(- -2.0)");

    EXPECT_STDOUT("-2\n2\n2\n-2.000000\n2.000000\n2.000000\n");
}

TEST(Operators, DISABLED_UnaryPrefixMinusMinus) {
    INIT_TEST

    risotto.run("var a = 3) print --a; print a; var b = 3.0; print --b; print b;");

    EXPECT_STDOUT("2\n2\n2.000000\n2.000000\n");
}

TEST(Operators, DISABLED_UnaryPostfixMinusMinus) {
    INIT_TEST

    risotto.run("var a = 3; print a--; print a; var b = 3.0; print b--; print b;");

    EXPECT_STDOUT("3\n2\n3.000000\n2.000000\n");
}

TEST(Operators, DISABLED_UnaryPrefixBang) {
    INIT_TEST

    risotto.run("print !true; print !false; print !!true; print !!false;");

    EXPECT_STDOUT("false\ntrue\ntrue\nfalse\n");
}

TEST(Operators, DISABLED_UnaryPrefixPlusPlus) {
    INIT_TEST

    risotto.run("var a = 3; print ++a; print a; var b = 3.0; print ++b; print b;");

    EXPECT_STDOUT("4\n4\n4.000000\n4.000000\n");
}

TEST(Operators, DISABLED_UnaryPostfixPlusPlus) {
    INIT_TEST

    risotto.run("var a = 3; print a++; print a; var b = 3.0; print b++; print b;");

    EXPECT_STDOUT("3\n4\n3.000000\n4.000000\n");
}

TEST(Operators, BinaryPlus) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(+));

//    EXPECT_STDOUT("-0.100000\n-0.200000\n4.000000\n3\n");
    EXPECT_STDOUT("3.000000\n3.000000\n3\n");
}

TEST(Operators, BinaryPlusString) {
    INIT_TEST

    risotto.runFile(INPUT("plus_string"));

    EXPECT_STDOUT(OUTPUT("plus_string"));
}

TEST(Operators, BinaryMinus) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(-));

//    EXPECT_STDOUT("-4.100000\n4.200000\n0.000000\n-1\n");
    EXPECT_STDOUT("-1.000000\n-1.000000\n-1\n");
}

TEST(Operators, BinaryDivide) {
    INIT_TEST

    auto s = OPERATOR_INPUT(/);
    risotto.run(s);

//    EXPECT_STDOUT("-1.050000\n-0.909091\n1.000000\n0\n");
    EXPECT_STDOUT("0.500000\n0.500000\n0\n");
}

TEST(Operators, BinaryMultiply) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(*));

//    EXPECT_STDOUT("-4.200000\n-4.400000\n4.000000\n2\n");
    EXPECT_STDOUT("2.000000\n2.000000\n2\n");
}

TEST(Operators, BinaryModulo) {
    INIT_TEST

    risotto.run("println(10 % 2) println(11 % 2)");

    EXPECT_STDOUT("0\n1\n");
}

TEST(Operators, BinaryLower) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(<));

    EXPECT_STDOUT("true\ntrue\ntrue\n");
}

TEST(Operators, BinaryLowerEqual) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(<=));

    EXPECT_STDOUT("true\ntrue\ntrue\n");
}

TEST(Operators, BinaryGreater) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(>));

    EXPECT_STDOUT("false\nfalse\nfalse\n");
}

TEST(Operators, BinaryGreaterEqual) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(>=));

    EXPECT_STDOUT("false\nfalse\nfalse\n");
}

TEST(Operators, BinaryEqualEqual) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(==));

    EXPECT_STDOUT("false\nfalse\nfalse\n");
}

TEST(Operators, BinaryBangEqual) {
    INIT_TEST

    risotto.run(OPERATOR_INPUT(!=));

    EXPECT_STDOUT("true\ntrue\ntrue\n");
}

TEST(Operators, DISABLED_PlusEqual) {
    INIT_TEST

    risotto.run(SHORTHAND_OPERATOR_INPUT(+=));

    EXPECT_STDOUT("1\n3\n8\n");
}

TEST(Operators, DISABLED_MinusEqual) {
    INIT_TEST

    risotto.run(SHORTHAND_OPERATOR_INPUT(-=));

    EXPECT_STDOUT("1\n-1\n-6\n");
}

TEST(Operators, DISABLED_StarEqual) {
    INIT_TEST

    risotto.run(SHORTHAND_OPERATOR_INPUT(*=));

    EXPECT_STDOUT("1\n2\n10\n");
}

TEST(Operators, DISABLED_SlashEqual) {
    INIT_TEST

    risotto.run(SHORTHAND_OPERATOR_INPUT(/=));

    EXPECT_STDOUT("1\n0\n0\n");
}

TEST(Operators, LogicalOr) {
    INIT_TEST

    risotto.run(LOGICAL_OPERATOR_INPUT(||));

    EXPECT_STDOUT("true\ntrue\ntrue\nfalse\n");
}


TEST(Operators, LogicalAnd) {
    INIT_TEST

    risotto.run(LOGICAL_OPERATOR_INPUT(&&));

    EXPECT_STDOUT("false\nfalse\ntrue\nfalse\n");
}

TEST(Operators, LogicalTestOrder) {
    INIT_TEST

    risotto.runFile(INPUT("logical_test_order"));

    EXPECT_STDOUT(OUTPUT("logical_test_order"));
}

TEST(Operators, DISABLED_Overloading) {
    INIT_TEST

    risotto.runFile(INPUT("overloading"));

    EXPECT_STDOUT(OUTPUT("overloading"));
}