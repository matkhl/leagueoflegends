#pragma once

#include "strings/obfuscator.hpp"

#include <iostream>

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

using table = obfs::make_pair_table<
    obfs::encoder_pair<xor_<0x50>, xor_<0x50>>,
    obfs::encoder_pair<add<10>, add<-10>>,
    obfs::encoder_pair<comp<xor_<0x50>, add<10>>, comp<add<-10>, xor_<0x50>>>
>;

#define SP_STRING(str) obfs::make_string<table>(str).decode()