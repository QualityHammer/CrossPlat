#include "Packet.hpp"

namespace Net {

Packet::Packet() : status{PacketStatus::IDLE}, type{PacketType::NONE}, size{0}, data{} {}

ENetPacket* Packet::toENet() const {
    std::vector<u8> tmp{{static_cast<u8>(type), static_cast<u8>(size & 0xff), static_cast<u8>((size & 0xff00) >> 8)}};
    tmp.insert(tmp.end(), data.begin(), data.end());
    return enet_packet_create(tmp.data(), tmp.size(), ENET_PACKET_FLAG_RELIABLE);
}

Packet& Packet::operator<<(ENetPacket* enetPacket) {
    const u8* recv{reinterpret_cast<const u8*>(enetPacket->data)};
    type = static_cast<PacketType>(*recv);
    size = *(recv + 1) | (*(recv + 2) << 8);
    const u8 dataOffset{3};
    for (u16 i{dataOffset}; i < size + dataOffset; ++i)
        data.push_back(*(recv + i));
    enet_packet_destroy(enetPacket);
    status = PacketStatus::RECIEVED;
    return *this;
}

void broadcastPacket(Packet& packet, ENetHost* host) {
    enet_host_broadcast(host, 0, packet.toENet());
    packet.status = PacketStatus::SENT;
}

void sendPacket(Packet& packet, ENetPeer* peer) {
    enet_peer_send(peer, 0, packet.toENet());
    packet.status = PacketStatus::SENT;
}

}
