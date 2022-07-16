#pragma once
#include "../glfw/glfw3.h"
#include "../glfw/glfw3native.h"
#include <vector>

struct Position {
    double x,y,z;
};

struct Scale {
    double x, y, z;
};

struct Rotation {
    double degX;
    double degY;
    double degZ;
};

struct Velocity {
   double mPerSX;
   double mPerSY;
   double mPerSZ;
};

struct RotVelocity {
   double degPerSX;
   double degPerSY;
   double degPerSZ;
};

struct AssetAttributes {
    Position pos;
    Scale scale;
    Rotation rot;
};

struct DynamicAssetAttributes : AssetAttributes {
    Velocity v;
    RotVelocity rotV;
};

class StaticAsset {
    public:
        void SpawnNew(AssetAttributes a);

        Position GetPosition();
        void SetPosition(Position newPos);
        
        Rotation GetRotation();
        void SetRotation(Rotation newRot);

        virtual void Load();

    private:
        AssetAttributes attributes;

};

class Asset: public StaticAsset {
    public:
        void Translate(double x, double y, double z);
        void Rotate(double degX, double degY, double degZ);
};

class DynamicAsset: public Asset {
    public:
        Velocity GetVelocity();
        void SetVelocity(Velocity v);

        RotVelocity GetRotVelocity();
        void SetRotVelocity(RotVelocity v);
    private:
};