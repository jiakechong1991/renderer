#ifndef BLINN_SHADER_H
#define BLINN_SHADER_H

#include "../core/api.h"

/* low-level api */

typedef struct {
    vec3_t position;
    vec2_t texcoord;
    vec3_t normal;
    vec4_t joint;
    vec4_t weight;
} blinn_attribs_t;

typedef struct {
    vec3_t world_position;
    vec3_t depth_position;
    vec2_t texcoord;
    vec3_t normal;
} blinn_varyings_t;

typedef struct {
    vec3_t light_dir; /*光线方向*/
    vec3_t camera_pos;
    mat4_t model_matrix; 
    mat3_t normal_matrix; 
    mat4_t light_vp_matrix;
    mat4_t camera_vp_matrix;
    mat4_t *joint_matrices;
    mat3_t *joint_n_matrices;
    float ambient_intensity;
    float punctual_intensity;
    texture_t *shadow_map;
    /* surface parameters */
    vec4_t basecolor;   /*基础色*/
    float shininess;    /*光滑度*/
    texture_t *diffuse_map; /*漫反射贴图*/
    texture_t *specular_map; /*镜面反射（高光）贴图*/
    texture_t *emission_map;  /*自发光贴图*/
    /* render controls */
    float alpha_cutoff; /*透明度阈值*/
    int shadow_pass; /*是否渲染阴影*/
} blinn_uniforms_t;   /**/

vec4_t blinn_vertex_shader(void *attribs, void *varyings, void *uniforms);
vec4_t blinn_fragment_shader(void *varyings, void *uniforms,
                             int *discard, int backface);

/* high-level api */

typedef struct {
    vec4_t basecolor;
    float shininess;
    const char *diffuse_map;
    const char *specular_map;
    const char *emission_map;
    /* render settings */
    int double_sided;
    int enable_blend;
    float alpha_cutoff;
} blinn_material_t;

model_t *blinn_create_model(const char *mesh, mat4_t transform,
                            const char *skeleton, int attached,
                            blinn_material_t *material);

#endif
