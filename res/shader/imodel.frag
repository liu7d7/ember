#version 460

in vec4 v_pos;
in vec3 v_normal;
in vec3 v_color;
in vec3 v_shadingModel;

out vec4 color;

uniform vec3 u_camPos;
uniform vec3 u_playerPos;

vec3 rgb(int r, int g, int b) {
  return vec3(r / 255., g / 255., b / 255.);
}

const vec3 lightDir = normalize(vec3(-1., 2.5, -1.));
const vec3 dark = rgb(60, 66, 196);
const vec3 outOfSight = rgb(60, 66, 196);
const float radiusSquared = 441.;

vec3 to_hsl(vec3 c) {
  vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
  vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
  vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

  float d = q.x - min(q.w, q.y);
  float e = 1.0e-10;
  return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 to_rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

const vec3 outOfSightHSL = to_hsl(outOfSight);

vec4 phong() {
  vec3 N = normalize(v_normal);
  vec3 L = normalize(lightDir);
  vec3 V = normalize(u_camPos - v_pos.xyz);
  vec3 R = reflect(-L, N);
  float lambert = max(dot(N, L), 0.0);
  float shininess = 8.;
  float specular = pow(max(dot(R, V), 0.0), shininess);
  float amt = clamp(v_shadingModel.x + lambert * v_shadingModel.y + specular * v_shadingModel.z, 0., 1.);
  return vec4(mix(dark, v_color, smoothstep(0., 1., amt)), 1.0);
}

void main() {
  const float bloom = 144.f;
  float dx = v_pos.x - u_playerPos.x;
  float dz = v_pos.z - u_playerPos.z;
  float distSquared = dx * dx + dz * dz;
  vec3 col = phong().xyz;
  vec3 oos = outOfSightHSL;
  oos.z = to_hsl(col).z * 0.33;
  oos = to_rgb(oos);
  if (distSquared > radiusSquared + bloom * 0.5) {
    color = vec4(oos, 1.);
  } else if (distSquared > radiusSquared - bloom * 0.5) {
    color = vec4(mix(oos, col, smoothstep(1., 0., (distSquared - radiusSquared + bloom * 0.5) / bloom)), 1.);
  } else {
    color = vec4(col, 1.);
  }
}
