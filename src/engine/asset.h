#pragma once
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
   double x;
   double y;
   double z;
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
    Velocity maxV;
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

        virtual void Load() = 0;

        AssetAttributes att;
};

class Asset: public StaticAsset {
    public:
        void Translate(double x, double y, double z);
        void Rotate(double degX, double degY, double degZ);
};

class DynamicAsset: public Asset {
    public:
        Velocity GetVelocity();
        Velocity GetVelocityNormalized();

        // add velocity considers velocity being added 
        // as vector, so it normalizes new values being added on x and y
        void AddVelocityNormalized(double x, double y, double z);

        void AddXVelocity(double n);
        void AddYVelocity(double n);
        void AddZVelocity(double n);

        void SetVelocity(double x, double y, double z);
        void SetXVelocity(double n);
        void SetYVelocity(double n);
        void SetZVelocity(double n);
};
