#version 450
in vec3 v_pos;
in vec3 v_norm;

out vec4 color;

uniform vec3 u_playerPos;
uniform vec3 u_camPos;

const float radiusSquared = 441.;

vec3 rgb(int r, int g, int b) {
  return vec3(r / 255., g / 255., b / 255.);
}

const vec3 light = rgb(244, 223, 190);
const vec3 dark = rgb(206, 121, 210);
const vec3 outOfSight = rgb(60, 66, 196);
const vec3 lightDir = normalize(vec3(-1., 2.5, -1.));

vec3 to_hsl(vec3 c) {
  vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
  vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
  vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

  float d = q.x - min(q.w, q.y);
  float e = 1.0e-10;
  return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

const vec3 lightHSL = to_hsl(light);
const vec3 darkHSL = to_hsl(dark);
const vec3 outOfSightHSL = to_hsl(outOfSight);

vec3 to_rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 light_calc(vec3 color) {
  const vec3 ldark = rgb(60, 66, 196);
  vec3 N = v_norm;
  vec3 L = lightDir;
  vec3 V = normalize(u_camPos - v_pos.xyz);
  vec3 R = reflect(-L, N);
  float lambert = max(dot(N, L), 0.0);
  float ambient = 0.;
  float amt = clamp(ambient + lambert, 0., 1.);
  return mix(ldark, color, smoothstep(0., 1., amt));
}

void main() {
  // if dist(v_pos, u_playerPos) > radius, set col to grayscale, for 144.f in between use smoothstep between the two
  const float bloom = 144.f;
  float dx = v_pos.x - u_playerPos.x;
  float dz = v_pos.z - u_playerPos.z;
  float distSquared = dx * dx + dz * dz;
  const float blendMax = 0., blendMin = 0.;
  const float mul = 1. / (blendMax - blendMin);
  vec3 col = light_calc(v_pos.y > blendMax ? light : v_pos.y < blendMin ? dark : mix(light, dark, smoothstep(1., 0., mul * (v_pos.y - blendMin))));
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

//void main() {
//  // if dist(v_pos, u_playerPos) > radius, set col to grayscale, for 144.f in between use smoothstep between the two
//  float dx = v_pos.x - u_playerPos.x;
//  float dz = v_pos.z - u_playerPos.z;
//  float distSquared = dx * dx + dz * dz;
//  const float _half = 6.;
//  vec3 col = v_pos.y > _half ? light : dark;
//  float gray = dot(col, vec3(0.299, 0.587, 0.114));
//  vec3 grayCol = vec3(gray) * 0.2;
//  if (distSquared > radiusSquared) {
//    color = vec4(grayCol, 1.);
//  } else {
//    color = vec4(col, 1.);
//  }
//}