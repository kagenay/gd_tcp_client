#include "tcp_client.h"

TcpClientAPI tcp;

int TcpClient::connect_to_server(String host, int port)
{
    const char *host_ptr = host.utf8().get_data();
    int error = tcp.connectToServer(host_ptr, port);
    return error;
}

void TcpClient::disconnect_from_server()
{
    tcp.disconnectFromServer();
}

int TcpClient::get_available_bytes()
{
    int ret = tcp.getAvailableBytes();
    return ret;
}

PackedByteArray TcpClient::get_data(int size)
{
    char *data = tcp.getData(size);

    PackedByteArray ret;
    ret.resize(size);

    for (int i = 0; i < ret.size(); i++)
    {
        ret[i] = data[i];
    }

    return ret;
}

int TcpClient::send_data(PackedByteArray buf)
{
    uint8_t *buf_ptrw = buf.ptrw();
    char *buf_char = (char *)buf_ptrw;

    int error = tcp.sendData(buf_char, buf.size());

    return error;
}

void TcpClient::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("connect_to_server", "host", "port"), &TcpClient::connect_to_server);
    ClassDB::bind_method(D_METHOD("disconnect_from_server"), &TcpClient::disconnect_from_server);
    ClassDB::bind_method(D_METHOD("get_available_bytes"), &TcpClient::get_available_bytes);
    ClassDB::bind_method(D_METHOD("send_data", "data"), &TcpClient::send_data);
    ClassDB::bind_method(D_METHOD("get_data", "size"), &TcpClient::get_data);
}