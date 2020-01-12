//
// Created by rvigee on 2018-09-24.
//

#ifndef RISOTTOPROJECT_NATIVE_FUNCTIONS_H
#define RISOTTOPROJECT_NATIVE_FUNCTIONS_H

#include "value.h"

NativeFunctionReturn vm_stats(Value args[], int argc);
NativeFunctionReturn run_gc(Value args[], int argc);

// String

NativeFunctionReturn binary_string_add_string(Value args[], int argc);
NativeFunctionReturn binary_string_add_int(Value args[], int argc);
NativeFunctionReturn binary_string_add_double(Value args[], int argc);
NativeFunctionReturn binary_string_add_bool(Value args[], int argc);

// Int

NativeFunctionReturn binary_int_add_string(Value args[], int argc);

NativeFunctionReturn binary_int_add_double(Value args[], int argc);

NativeFunctionReturn binary_int_sub_double(Value args[], int argc);

NativeFunctionReturn binary_int_mul_double(Value args[], int argc);

NativeFunctionReturn binary_int_div_double(Value args[], int argc);

NativeFunctionReturn binary_int_mod_int(Value args[], int argc);

NativeFunctionReturn binary_int_lower_double(Value args[], int argc);

NativeFunctionReturn binary_int_greater_double(Value args[], int argc);

NativeFunctionReturn binary_int_lower_equal_double(Value args[], int argc);

NativeFunctionReturn binary_int_greater_equal_double(Value args[], int argc);

NativeFunctionReturn binary_int_eq_double(Value args[], int argc);

NativeFunctionReturn binary_int_neq_double(Value args[], int argc);

NativeFunctionReturn unary_prefix_int_negate(Value *args, int argc);

NativeFunctionReturn unary_prefix_int_decrement(Value *args, int argc);
NativeFunctionReturn unary_prefix_int_increment(Value *args, int argc);

NativeFunctionReturn unary_postfix_int_decrement(Value *args, int argc);
NativeFunctionReturn unary_postfix_int_increment(Value *args, int argc);

// Double

NativeFunctionReturn binary_double_add_string(Value args[], int argc);

NativeFunctionReturn binary_double_add_int(Value args[], int argc);
NativeFunctionReturn binary_double_add_double(Value args[], int argc);

NativeFunctionReturn binary_double_sub_int(Value args[], int argc);
NativeFunctionReturn binary_double_sub_double(Value args[], int argc);

NativeFunctionReturn binary_double_mul_int(Value args[], int argc);
NativeFunctionReturn binary_double_mul_double(Value args[], int argc);

NativeFunctionReturn binary_double_div_int(Value args[], int argc);
NativeFunctionReturn binary_double_div_double(Value args[], int argc);

NativeFunctionReturn binary_double_lower_int(Value args[], int argc);
NativeFunctionReturn binary_double_lower_double(Value args[], int argc);

NativeFunctionReturn binary_double_greater_int(Value args[], int argc);
NativeFunctionReturn binary_double_greater_double(Value args[], int argc);

NativeFunctionReturn binary_double_lower_equal_int(Value args[], int argc);
NativeFunctionReturn binary_double_lower_equal_double(Value args[], int argc);

NativeFunctionReturn binary_double_greater_equal_int(Value args[], int argc);
NativeFunctionReturn binary_double_greater_equal_double(Value args[], int argc);

NativeFunctionReturn binary_double_eq_int(Value args[], int argc);
NativeFunctionReturn binary_double_eq_double(Value args[], int argc);

NativeFunctionReturn binary_double_neq_int(Value args[], int argc);
NativeFunctionReturn binary_double_neq_double(Value args[], int argc);

NativeFunctionReturn unary_prefix_double_negate(Value *args, int argc);

NativeFunctionReturn unary_prefix_double_decrement(Value *args, int argc);
NativeFunctionReturn unary_prefix_double_increment(Value *args, int argc);

NativeFunctionReturn unary_postfix_double_decrement(Value *args, int argc);
NativeFunctionReturn unary_postfix_double_increment(Value *args, int argc);

// Bool

NativeFunctionReturn binary_bool_add_string(Value args[], int argc);

NativeFunctionReturn unary_prefix_bool_invert(Value args[], int argc);

// Print

NativeFunctionReturn println_int(Value args[], int argc);
NativeFunctionReturn println_double(Value args[], int argc);
NativeFunctionReturn println_string(Value args[], int argc);
NativeFunctionReturn println_bool(Value args[], int argc);

// Array

NativeFunctionReturn array_size(Value args[], int argc);
NativeFunctionReturn array_add(Value args[], int argc);
NativeFunctionReturn array_at(Value args[], int argc);

#endif //RISOTTOPROJECT_NATIVE_FUNCTIONS_H
