#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "../libs/tcp_client/tcp_client.h"

using namespace godot;

class TcpClient : public RefCounted
{
    GDCLASS(TcpClient, RefCounted);

public:
    int connect_to_server(String host, int port);
    void disconnect_from_server();
    int get_available_bytes();
    PackedByteArray get_data(int size);
    int send_data(PackedByteArray buf);

protected:
    static void _bind_methods();
};

#endif