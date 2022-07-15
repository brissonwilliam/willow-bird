#pragma once
#include "../glfw/glfw3.h"

struct AssetAttributes {
    Position pos;
    Rotation rot;
};

struct Position {
    double x;
    double y;
    double z;
};

struct Rotation {
    double degX;
    double degY;
    double degZ;
};

class StaticAsset {
    public:
        Position GetPosition();
        void SetPosition(Position newPos);
        
        Rotation GetRotation();
        void SetRotation();

    private:
        AssetAttributes attributes;
};

class Asset: public StaticAsset {
    public:
        Asset WithTime(double t);
        void Translate(double x, double y, double z);
        void Rotate(double degX, double degY, double degZ);

    private:
        double deltaTime; // time to apply for constant velocity or physics (not frame dependant). Omitted if 0
};

class DynamicAsset: public Asset {
    public:
        void SetVelocity();
        void SetRotVelocity();
    private:
};