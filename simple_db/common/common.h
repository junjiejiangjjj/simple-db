#ifndef SIMPLE_DB_COMMON_H
#define SIMPLE_DB_COMMON_H


#define BEGIN_SIMPLE_DB_NS(x) namespace simple_db { namespace x {
#define END_SIMPLE_DB_NS(x) } }
#define USE_SIMPLE_DB_NS(X) using namepsace simple_db::x


#include <assert.h>
#include <string>
#include <stddef.h>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

#include "logging.h"

BEGIN_SIMPLE_DB_NS(common)

const std::string POLLER("poller");


#define SIMPLE_DB_DELETE_AND_SET_NULL(ptr) do { \
    if ((ptr) != nullptr) {                     \
        delete (ptr);                           \
        (ptr) = nullptr;                        \
    }                                           \
    }while(0)

END_SIMPLE_DB_NS(common)

#endif
