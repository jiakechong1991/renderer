#ifndef MESH_H
#define MESH_H

#include "maths.h"

typedef struct mesh mesh_t;

typedef struct {
    vec3_t position;  /*顶点坐标*/
    vec2_t texcoord; /*纹理坐标*/
    vec3_t normal;   /*法线*/
    vec4_t tangent; /*切线*/
    vec4_t joint;    /*关节*/
    vec4_t weight;  /*骨骼权重*/
} vertex_t;

/* mesh loading/releasing */
mesh_t *mesh_load(const char *filename);
void mesh_release(mesh_t *mesh);

/* vertex retrieving */
int mesh_get_num_faces(mesh_t *mesh);
vertex_t *mesh_get_vertices(mesh_t *mesh);
vec3_t mesh_get_center(mesh_t *mesh);

#endif
