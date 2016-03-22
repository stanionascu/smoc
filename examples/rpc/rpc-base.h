#pragma once

#include <string>

extern void *rpc_socket;

void rpc_say(const std::string &what);
int rpc_add(int x, int y);
