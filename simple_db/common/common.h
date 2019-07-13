#ifndef SIMPLE_DB_COMMON_H
#define SIMPLE_DB_COMMON_H
#define BEGIN_SIMPLE_DB_NS(x) namespace simple_db { namespace x {
#define END_SIMPLE_DB_NS(x) } }
#define USE_SIMPLE_DB_NS(X) using namepsace simple_db::x
#include <string>
#include <stddef.h>
#include <iostream>
#endif