#include "asset.h"
#include "../../lib/glm/glm.hpp"

Position StaticAsset::GetPosition() {
    return this->att.pos;
}

void Asset::Translate(double x, double y, double z) {
    this->att.pos.x += x;
    this->att.pos.y += y;
    this->att.pos.z += z;
}

void Asset::Rotate(double degX, double degY, double degZ) {

}           

Velocity DynamicAsset::GetVelocity() {
    return this->att.v;
}

Velocity DynamicAsset::GetVelocityNormalized() {
    // x^2 + y^2 = hypothenus^2
    // signs will be lost when doing math operations, so keep track of signs
    auto x = this->att.v.x;
    auto xSign = x < 0.0 ? -1 : 1;
    auto y = this->att.v.y;
    auto ySign = y < 0.0 ? -1 : 1;
    auto hSquared = x*x + y*y;

    auto newX = glm::sqrt(hSquared - (y * y));
    auto newY = glm::sqrt(hSquared - (x * x));

    return Velocity{newX * xSign, newY * ySign, this->att.v.z};
}

void DynamicAsset::AddVelocityNormalized(double x, double y, double z) {
    this->AddXVelocity(x);
    this->AddYVelocity(y);
    this->AddZVelocity(z);
    this->att.v = this->GetVelocityNormalized();
}

void DynamicAsset::AddXVelocity(double n) {
    this->att.v.x = n;
    if (this->att.v.x > this->att.maxV.x) {
        this->SetXVelocity(this->att.maxV.x);
    } else if (this->att.v.x < this->att.maxV.x * -1) {
        this->SetXVelocity(this->att.maxV.x * -1);
    }
}

void DynamicAsset::AddYVelocity(double n) {
    this->att.v.y = n;
    if (this->att.v.y > this->att.maxV.y) {
        this->SetYVelocity(this->att.maxV.y);
    } else if (this->att.v.y < this->att.maxV.y * -1) {
        this->SetYVelocity(this->att.maxV.y * -1);
    }
}

void DynamicAsset::AddZVelocity(double n) {
    this->att.v.z = n;
    if (this->att.v.z > this->att.maxV.z) {
        this->SetZVelocity(this->att.maxV.z);
    } else if (this->att.v.z < this->att.maxV.z * -1) {
        this->SetZVelocity(this->att.maxV.z * -1);
    }
}

void DynamicAsset::SetVelocity(double x, double y, double z) {
    this->SetXVelocity(x);
    this->SetYVelocity(y);
    this->SetZVelocity(z);
}

void DynamicAsset::SetXVelocity(double n) {
    this->att.v.x = n;
}

void DynamicAsset::SetYVelocity(double n) {
    this->att.v.y = n;
}

void DynamicAsset::SetZVelocity(double n) {
    this->att.v.z = n;
}


