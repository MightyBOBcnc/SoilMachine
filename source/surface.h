/*
================================================================================
              Description of Surface Types and their Properties
================================================================================
*/

#include <map>

using SurfType = size_t;

struct SurfParam {

  //General Parameters
  string name;
  float density;
  float porosity = 0.0f;
  vec4 color = vec4(0.5, 0.5, 0.5, 1.0);

  //Hydrologyical Parameters
  SurfType transports = 0;    //Surface Type it Transports As
  float solubility = 1.0f;    //Relative Solubility in Water
  float equrate = 1.0f;       //Rate of Reaching Equilibrium
  float friction = 1.0f;      //Surface Friction, Water Particles

  SurfType erodes = 0;        //Surface Type it Erodes To
  float erosionrate = 0.0f;   //Rate of Conversion

  //Cascading Parameters
  SurfType cascades = 0;      //Surface Type it Cascades To
  float maxdiff = 1.0f;       //Maximum Settling Height Difference
  float settling = 0.0f;      //Settling Rate

  //Wind Erosion
  SurfType abrades = 0;       //Surface Type it Cascades To
  float suspension = 0.0f;
  float abrasion = 0.0f;      //Rate at which particle size decreases

};

vector<SurfParam> soils = {

    { "Air", 0.0f, 1.0f,
      vec4(0.0, 0.2, 0.4, 1.0),
      0, 0.0f, 0.0f, 0.0f,
      0, 0.0f,
      0, 0.0f, 0.0f,
      0, 0.0f, 0.0f}

};

map<string, int> soilmap = {

  {"Air", 0}

};

/*
================================================================================
                  Description of Noise Layers as a Struct
================================================================================
*/

struct SurfLayer {

  SurfType type;              //Surface Type

  //Formula:
  //  clamp(bias + scale * val, min, max);

  float min =  0.0f;          //Minimum Value
  float bias = 0.0f;          //Add-To-Value
  float scale = 1.0f;         //Multiply-By-Value

  static FastNoiseLite noise; //Noise System
  float octaves = 1.0f;       //
  float lacunarity = 1.0f;    //
  float gain = 0.0f;          //
  float frequency = 1.0f;     //

  void init(){
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(gain);
    noise.SetFrequency(frequency);
  }

  SurfLayer(const SurfType _type){
    type = _type;
  }

  float get(const vec3 pos){
    float val = bias + scale * noise.GetNoise(pos.x, pos.y, pos.z);
    if(val < min) val = min;
    return val;
  }

};

FastNoiseLite SurfLayer::noise;
vector<SurfLayer> layers;
