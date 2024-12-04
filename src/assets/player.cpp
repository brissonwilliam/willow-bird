#include "player.h"

Player::Player() {
    this->att.maxV = Velocity{0.01, 0.01, 0};
    this->att.pos = Position{0, 0, 0};
    this->att.v = Velocity{0, 0, 0};
}

void Player::Load() {

}

void Player::Update(double elapsed) {
    auto normalVel = this->GetVelocityNormalized();
    this->Translate(normalVel.x * elapsed, normalVel.y * elapsed, this->att.v.z * elapsed);
}

