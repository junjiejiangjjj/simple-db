#ifndef SIMPLE_DB_STATUS_H
#define SIMPLE_DB_STATUS_H

#include <string>

namespace simple_db {
    
class Status {

private:
    Status(int code, const std::string &s): mRetCode(code), mMsg(s) {
    }
public:
    virtual ~Status() = default;

public:    
    Status(const Status&) = default;

    Status& operator=(const Status&) = default;

public:
    
    static Status Error(const std::string &str) {
        return Status(-1, str);
    }

    static Status Ok() {
        return Status(0, "");
    }    
    

public:
    inline bool IsOk() {
        return mRetCode == 0;
    }

    inline std::string Msg() {
        return mMsg;
    }

private:
    int mRetCode;
    std::string mMsg;
};

};

#endif
