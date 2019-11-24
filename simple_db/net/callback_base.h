#ifndef SIMPLE_DB_CALLBACK_BASE_H
#define SIMPLE_DB_CALLBACK_BASE_H

#include "simple_db/common/common.h"
#include "simple_db/net/socket_opt.h"

BEGIN_SIMPLE_DB_NS(net)

using MsgCallback = std::function<void(net::SocketOpt *sckOpt)>;

END_SIMPLE_DB_NS(net)

#endif
