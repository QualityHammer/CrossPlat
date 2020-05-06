#include "Client.hpp"

#include <iostream>
#include <cmath>

#include "render/Pixels.hpp"
#include <common/constructs/PlayerControl.hpp>

namespace Client {

ClientEngine::ClientEngine() : m_status{ClientStatus::IDLE}, m_window{},
m_gameState{}, m_keyState{}, m_mouseState{}, m_network{m_gameState}, m_frameTimer{},
focusMouse{true} {
  init();
}

void ClientEngine::run() {
  m_status = ClientStatus::GOOD;
  m_network.connect();
  m_frameTimer.start();
  while (m_status == ClientStatus::GOOD) {
    m_network.getUpdates();
    manageInputs(*this);
    update();
    m_frameTimer.unpause();
    draw();
    m_frameTimer.pause();
  }
  m_network.disconnect();
  m_frameTimer.stop();
}

void ClientEngine::draw() {
  m_window.draw(m_gameState);
}

void ClientEngine::init() {
  m_status = ClientStatus::IDLE;
}

void ClientEngine::update() {
  m_gameState.player.velX = 0.0f;
  m_gameState.player.velY = 0.0f;
  if (m_mouseState.xMov != 0) {
    m_gameState.player.a += (float)m_mouseState.xMov * 0.01f;
  }
  if (m_keyState.FORWARD || m_keyState.BACK) {
    m_gameState.player.velX += ((float)m_keyState.FORWARD + (float)(-m_keyState.BACK)) *
      std::cos(m_gameState.player.a) * 0.2f;
    m_gameState.player.velY += ((float)m_keyState.FORWARD + (float)(-m_keyState.BACK)) *
      std::sin(m_gameState.player.a) * 0.2f;
  }
  m_network.sendPlayerPos(m_gameState.player);
  m_gameState.player.x += m_gameState.player.velX;
  m_gameState.player.y += m_gameState.player.velY;
  
  if (m_keyState.K_P) {
    m_keyState.K_P = false;
    focusMouse = !focusMouse;
    m_window.setMouseFocus(focusMouse);
  }
}

}
