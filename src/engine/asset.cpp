#include "asset.h"

Position StaticAsset::GetPosition() {
    return this->attributes.pos;
}


void Asset::Translate(double x, double y, double z) {
    this->attributes.pos.x += x;
    this->attributes.pos.y += y;
    this->attributes.pos.z += z;
}

void Asset::Rotate(double degX, double degY, double degZ) {

}           

void DynamicAsset::SetVelocity(double x, double y, double z) {
    this->vel.mPerSX = x;
    this->vel.mPerSY = y;
    this->vel.mPerSZ = z;
}

void DynamicAsset::Update() {
    this->Translate(this->vel.mPerSX, this->vel.mPerSY, this->vel.mPerSZ);
}


