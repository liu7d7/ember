#version 450
in vec2 v_uv;

out vec4 color;

uniform sampler2D u_tex0;
uniform vec3 palette[256];
uniform int paletteSize;

const int indexMatrix4x4[16] = int[](
  0,  8,  2,  10,
  12, 4,  14, 6,
  3,  11, 1,  9,
  15, 7,  13, 5
);

//const int indexMatrix8x8as4x4[64] = int[](
//  0, 0, 8, 8, 2, 2, 10, 10,
//  0, 0, 8, 8, 2, 2, 10, 10,
//  12, 12, 4, 4, 14, 14, 6, 6,
//  12, 12, 4, 4, 14, 14, 6, 6,
//  3, 3, 11, 11, 1, 1, 9, 9,
//  3, 3, 11, 11, 1, 1, 9, 9,
//  15, 15, 7, 7, 13, 13, 5, 5,
//  15, 15, 7, 7, 13, 13, 5, 5
//);

//const int indexMatrix8x8[64] = int[](
//  0,  32, 8,  40, 2,  34, 10, 42,
//  48, 16, 56, 24, 50, 18, 58, 26,
//  12, 44, 4,  36, 14, 46, 6,  38,
//  60, 28, 52, 20, 62, 30, 54, 22,
//  3,  35, 11, 43, 1,  33, 9,  41,
//  51, 19, 59, 27, 49, 17, 57, 25,
//  15, 47, 7,  39, 13, 45, 5,  37,
//  63, 31, 55, 23, 61, 29, 53, 21
//);


float lightnessStep(float l) {
  const float lightnessSteps = 4.0;
  return floor((0.5 + l * lightnessSteps)) / lightnessSteps;
}

float idx_val() {
  int x = int(mod(gl_FragCoord.x, 4));
  int y = int(mod(gl_FragCoord.y, 4));
  return indexMatrix4x4[x + y * 4] / 16.;
}

float hue_dist(float h1, float h2) {
  float diff = abs(h1 - h2);
  return min(abs(1. - diff), diff);
}

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

vec3[2] closest_cols(float hue) {
  vec3 ret[2];
  vec3 closest = vec3(-2., 0., 0.);
  vec3 secondClosest = vec3(-2., 0., 0.);
  vec3 temp;
  for (int i = 0; i < paletteSize; i++) {
    temp = to_hsl(palette[i]);
    float tempDistance = hue_dist(hue, temp.r);
    if (tempDistance < hue_dist(closest.x, hue)) {
      secondClosest = closest;
      closest = temp;
    } else if (tempDistance < hue_dist(secondClosest.x, hue)) {
      secondClosest = temp;
    }
  }
  ret[0] = closest;
  ret[1] = secondClosest;
  return ret;
}

vec3 dither(vec3 col) {
  vec3 hsl = to_hsl(col);
  vec3 colors[2] = closest_cols(hsl.x);
  float hueDiff = hue_dist(hsl.x, colors[0].x) / hue_dist(colors[1].x, colors[0].x);

  float l1 = lightnessStep(max((hsl.z - 0.125), 0.0));
  float l2 = lightnessStep(min((hsl.z + 0.124), 1.0));
  float lightnessDiff = (hsl.z - l1) / (l2 - l1);

  vec3 res = hueDiff < idx_val() ? colors[0] : colors[1];
  res.z = (lightnessDiff < idx_val()) ? l1 : l2;
  return to_rgb(res);
}

void main() {
  color = vec4(dither(texture(u_tex0, v_uv).rgb), 1.);
}