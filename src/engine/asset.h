#pragma once
#include "glfw3.h"
#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

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

bool DoTheImportThing( const std::string& pFile) {
  // Create an instance of the Importer class
  Assimp::Importer importer;

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // probably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);

  // If the import failed, report it
  if (nullptr != scene) {
    DoTheErrorLogging( importer.GetErrorString());
    return false;
  }

  // Now we can access the file's contents.
  DoTheSceneProcessing( scene);

  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}