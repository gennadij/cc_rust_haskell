#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "hello_world.pb.h"

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4000);

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    std::cout << "Server wartet auf Verbindung..." << std::endl;
    int client_fd = accept(server_fd, nullptr, nullptr);

    // Länge der Nachricht lesen (4 Byte)
    uint32_t size = 0;
    read(client_fd, &size, sizeof(size));

    size = ntohl(size);

    // Nachricht lesen
    std::string buffer(size, '\0');
    read(client_fd, buffer.data(), size);

    demo::ChatMessage msg;
    msg.ParseFromString(buffer);

    std::cout << "Empfangen: " << msg.text() << " (ID=" << msg.id() << ")\n";

    // Antwort
    demo::ChatMessage reply;
    reply.set_text("Hallo Client!");
    reply.set_id(999);

    std::string out;
    reply.SerializeToString(&out);

    uint32_t out_size = htonl(out.size());
    write(client_fd, &out_size, sizeof(out_size));
    write(client_fd, out.data(), out.size());

    close(client_fd);
    close(server_fd);
}
