#include "Packet.hpp"

#include <cassert>

#include "Serialize.hpp"
#include "Deserialize.hpp"

namespace Net {

Packet::Packet() : status{PacketStatus::IDLE}, type{PacketType::NONE}, size{0}, data{} {}

void readENetPacket(ENetPacket* enetPacket, u8& command, Packet& packet) {
    packet = Packet{};
    const u8* recv{reinterpret_cast<const u8*>(enetPacket->data)};
    command = *recv;
    packet.type = static_cast<PacketType>(*(recv + 1));
    packet.size = *(recv + 2) | (*(recv + 3) << 8);
    const u8 dataOffset{4};
    for (u16 i{dataOffset}; i < packet.size + dataOffset; ++i)
        packet.data.push_back(*(recv + i));
    enet_packet_destroy(enetPacket);
    packet.status = PacketStatus::RECIEVED;
}

ENetPacket* createENetPacket(const u8 command, Packet& packet) {
    if (packet.size == 0) return nullptr;
    std::vector<u8> tmp{{command, static_cast<u8>(packet.type), static_cast<u8>(packet.size & 0xff),
        static_cast<u8>((packet.size & 0xff00) >> 8)}};
    tmp.insert(tmp.end(), packet.data.begin(), packet.data.end());
    return enet_packet_create(tmp.data(), tmp.size(), ENET_PACKET_FLAG_RELIABLE);
}

void broadcastPacket(const u8 command, Packet& packet, ENetHost* host) {
    ENetPacket* enetPacket{createENetPacket(command, packet)};
    if (enetPacket != nullptr) {
        enet_host_broadcast(host, 0, enetPacket);
        packet.status = PacketStatus::SENT;
    }
}

void sendPacket(const u8 command, Packet& packet, ENetPeer* peer) {
    ENetPacket* enetPacket{createENetPacket(command, packet)};
    if (enetPacket != nullptr) {
        enet_peer_send(peer, 0, enetPacket);
        packet.status = PacketStatus::SENT;
    }
}

}
