#pragma once

#include <utility>
#include <iostream>

#include <zmq.h>
#include <msgpack.hpp>

namespace messages {
// TODO: extend if needed
using header = msgpack::type::tuple<int>;
}

template<class Arg>
void send_message(void *z_sock, int flags, Arg &&arg) {
  msgpack::sbuffer buf;
  msgpack::pack(buf, arg);

  zmq_msg_t msg;
  zmq_msg_init_size(&msg, buf.size());
  memcpy(zmq_msg_data(&msg), buf.data(), buf.size());
  zmq_sendmsg(z_sock, &msg, flags);
  zmq_msg_close(&msg);
}

template<class... Args>
void send_message_tuple(void *z_sock, int flags, Args... args) {
  using message_t = msgpack::type::tuple<
    typename std::remove_reference<Args>::type...>;
  send_message(z_sock, flags, message_t(args...));
}

template<class... RpcArgs>
void send_rpc_message(void *z_sock, int rpcId, RpcArgs... args) {
  send_message_tuple(z_sock, ZMQ_SNDMORE, rpcId);
  send_message_tuple(z_sock, 0, args...);
}

template<class Ret>
Ret get_reply(void *z_sock)
{
  zmq_msg_t msg;
  zmq_msg_init(&msg);
  zmq_recvmsg(z_sock, &msg, 0);

  msgpack::unpacked reply_unpacked;
  msgpack::unpack(reply_unpacked,
    static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
  zmq_msg_close(&msg);

  Ret reply_data;
  reply_unpacked.get().convert(reply_data);
  return reply_data;
}

template<class Ret, class... Args>
auto unpack_message(Ret(*fptr)(Args...), const msgpack::object &obj) {
  (void)fptr;
  msgpack::type::tuple<
    typename std::decay<Args>::type...> msg;
  obj.convert(msg);
  return msg;
}
