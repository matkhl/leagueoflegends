#pragma once

#include <iostream>

#include "strings/obfuscator.h"

#define SP_STRING(str) obfs::make_string<xor_<0x50>, xor_<0x50>>(str).decode()

template <char key>
constexpr char xor_(char c) {
    return c ^ key;
}

template <char Key>
constexpr char add(char c) {
    return c + Key;
}

template <char(*f)(char), char(*g)(char)>
constexpr char comp(char c) {
    return f(g(c));
}