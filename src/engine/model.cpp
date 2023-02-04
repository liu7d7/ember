//
// Created by richard may clarkson on 21/12/2022.
//
#include "engine/model.h"

namespace Ember {
  void Model::to_mesh() const {
    mesh->begin();
    for (const Face& face : faces) {
      glm::vec3 p0 = positions[face.p0];
      glm::vec3 p1 = positions[face.p1];
      glm::vec3 p2 = positions[face.p2];
      glm::vec3 n0 = normals[face.n0];
      glm::vec3 n1 = normals[face.n1];
      glm::vec3 n2 = normals[face.n2];
      mesh->tri(
        mesh->put({p0, n0, face.color, face.shadingModel}),
        mesh->put({p1, n1, face.color, face.shadingModel}),
        mesh->put({p2, n2, face.color, face.shadingModel})
      );
    }
    mesh->end();
  }

  Model::Model(const std::string& src, Args args) {
    mesh = new Mesh<Vertex>(DrawModes::triangle, {Attribute::FLOAT3, Attribute::FLOAT3, Attribute::FLOAT3, Attribute::FLOAT3});
    int hasUvs = -1;
    std::ifstream in(src);
    glm::vec3 color;
    glm::vec3 shadingModel;
    glm::vec3 windiness;
    std::string ln;
    while (getline(in, ln)) {
      if (ln[0] == '#') continue;
      if (ln[0] == 'o') {
        std::string matName = ln.substr(2);
        if (args[COLOR].find(matName) == args[COLOR].end()) {
          if (args[COLOR].find("") == args[COLOR].end()) color = glm::vec4(1, 1, 1, 0);
          else {
            glm::vec4 c = args[COLOR][""];
            color.x = c.x;
            color.y = c.y;
            color.z = c.z;
          }
        } else {
          glm::vec4 c = args[COLOR][matName];
          color.x = c.x;
          color.y = c.y;
          color.z = c.z;
        }
        if (args[SHADING_MODEL].find(matName) == args[SHADING_MODEL].end()) {
          if (args[SHADING_MODEL].find("") == args[SHADING_MODEL].end()) shadingModel = glm::vec3(0.1, 1., 0);
          else {
            shadingModel.x = args[SHADING_MODEL][""].x;
            shadingModel.y = args[SHADING_MODEL][""].y;
            shadingModel.z = args[SHADING_MODEL][""].z;
          }
        } else {
          shadingModel.x = args[SHADING_MODEL][matName].x;
          shadingModel.y = args[SHADING_MODEL][matName].y;
          shadingModel.z = args[SHADING_MODEL][matName].z;
        }
      }
      if (ln[0] == 'v') {
        if (ln[1] == 'n') {
          glm::vec3 vec;
          sscanf(ln.c_str(), "vn %f %f %f", &vec.x, &vec.y, &vec.z);
          normals.push_back(vec);
          continue;
        }
        if (ln[1] == 't') {
          continue;
        }
        glm::vec3 vec;
        sscanf(ln.c_str(), "v %f %f %f", &vec.x, &vec.y, &vec.z);
        positions.push_back(vec);
      } else if (ln[0] == 'f') {
        uint p[9];
        if (hasUvs == -1) {
          hasUvs = ln.find("//") == std::string::npos;
        }
        if (hasUvs) {
          sscanf(ln.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6], &p[7],
                 &p[8]);
        } else {
          sscanf(ln.c_str(), "f %u//%u %u//%u %u//%u", &p[0], &p[2], &p[3], &p[5], &p[6], &p[8]);
          p[1] = p[4] = p[7] = 1;
        }
        Face face{p[0] - 1, p[3] - 1, p[6] - 1, p[2] - 1, p[5] - 1, p[8] - 1, color, shadingModel};
        faces.push_back(face);
      }
    }

    scale(1.5f);
  }
}