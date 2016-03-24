#pragma once

#include "rpc-common.hpp"

#include <msgpack.hpp>

void execute_rpc_request(rpc_call_name call_name, const msgpack::object &msg);
