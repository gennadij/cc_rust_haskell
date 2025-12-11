#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "hello_world.pb.h"

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    demo::ChatMessage msg;
    msg.set_text("Hallo Server!");
    msg.set_id(123);

    // serialisieren
    std::string data;
    msg.SerializeToString(&data);

    // Länge der Nachricht übertragen
    uint32_t size = htonl(data.size());
    write(sock, &size, sizeof(size));

    // Nachricht übertragen
    write(sock, data.data(), data.size());

    // Antwort lesen
    uint32_t reply_size = 0;
    read(sock, &reply_size, sizeof(reply_size));
    reply_size = ntohl(reply_size);

    std::string buffer(reply_size, '\0');
    read(sock, buffer.data(), reply_size);

    demo::ChatMessage reply;
    reply.ParseFromString(buffer);

    std::cout << "Server sagt: " << reply.text() << " (ID=" << reply.id() << ")\n";

    close(sock);
}
