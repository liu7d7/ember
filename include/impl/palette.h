//
// Created by richard may clarkson on 29/01/2023.
//

#ifndef EMBER_IML_PALETTE_H
#define EMBER_IML_PALETTE_H

#include "global.h"

namespace Ember::Palette {
  namespace Tila {
    static const uint SIZE = 8;

    static const uint C1 = 0xff371a47;
    static const uint C2 = 0xff602547;
    static const uint C3 = 0xff923a47;
    static const uint C4 = 0xffac5043;
    static const uint C5 = 0xffc36d44;
    static const uint C6 = 0xffe39454;
    static const uint C7 = 0xffe7b06c;
    static const uint C8 = 0xfff7ecae;

    static const uint ALL[] = {C1, C2, C3, C4, C5, C6, C7, C8};

    static const glm::vec4 C1_VEC4 = to_vec4(C1);
    static const glm::vec4 C2_VEC4 = to_vec4(C2);
    static const glm::vec4 C3_VEC4 = to_vec4(C3);
    static const glm::vec4 C4_VEC4 = to_vec4(C4);
    static const glm::vec4 C5_VEC4 = to_vec4(C5);
    static const glm::vec4 C6_VEC4 = to_vec4(C6);
    static const glm::vec4 C7_VEC4 = to_vec4(C7);
    static const glm::vec4 C8_VEC4 = to_vec4(C8);

    static const glm::vec4 ALL_VEC4[] = {C1_VEC4, C2_VEC4, C3_VEC4, C4_VEC4, C5_VEC4, C6_VEC4, C7_VEC4, C8_VEC4};

    static const glm::vec3 C1_VEC3 = glm::vec3(C1_VEC4.r, C1_VEC4.g, C1_VEC4.b);
    static const glm::vec3 C2_VEC3 = glm::vec3(C2_VEC4.r, C2_VEC4.g, C2_VEC4.b);
    static const glm::vec3 C3_VEC3 = glm::vec3(C3_VEC4.r, C3_VEC4.g, C3_VEC4.b);
    static const glm::vec3 C4_VEC3 = glm::vec3(C4_VEC4.r, C4_VEC4.g, C4_VEC4.b);
    static const glm::vec3 C5_VEC3 = glm::vec3(C5_VEC4.r, C5_VEC4.g, C5_VEC4.b);
    static const glm::vec3 C6_VEC3 = glm::vec3(C6_VEC4.r, C6_VEC4.g, C6_VEC4.b);
    static const glm::vec3 C7_VEC3 = glm::vec3(C7_VEC4.r, C7_VEC4.g, C7_VEC4.b);
    static const glm::vec3 C8_VEC3 = glm::vec3(C8_VEC4.r, C8_VEC4.g, C8_VEC4.b);

    static const glm::vec3 ALL_VEC3[] = {C1_VEC3, C2_VEC3, C3_VEC3, C4_VEC3, C5_VEC3, C6_VEC3, C7_VEC3, C8_VEC3};
  }

  namespace Pear {
    static const uint SIZE = 36;

    static const uint C1 = 0xff5e315b;
    static const uint C2 = 0xff8c3f5d;
    static const uint C3 = 0xffba6156;
    static const uint C4 = 0xfff2a65e;
    static const uint C5 = 0xffffe478;
    static const uint C6 = 0xffcfff70;
    static const uint C7 = 0xff8fde5d;
    static const uint C8 = 0xff3ca370;
    static const uint C9 = 0xff3d6e70;
    static const uint C10 = 0xff323e4f;
    static const uint C11 = 0xff322947;
    static const uint C12 = 0xff473b78;
    static const uint C13 = 0xff4b5bab;
    static const uint C14 = 0xff4da6ff;
    static const uint C15 = 0xff66ffe3;
    static const uint C16 = 0xffffffeb;
    static const uint C17 = 0xffc2c2d1;
    static const uint C18 = 0xff7e7e8f;
    static const uint C19 = 0xff606070;
    static const uint C20 = 0xff43434f;
    static const uint C21 = 0xff272736;
    static const uint C22 = 0xff3e2347;
    static const uint C23 = 0xff57294b;
    static const uint C24 = 0xff964253;
    static const uint C25 = 0xffe36956;
    static const uint C26 = 0xffffb570;
    static const uint C27 = 0xffff9166;
    static const uint C28 = 0xffeb564b;
    static const uint C29 = 0xffb0305c;
    static const uint C30 = 0xff73275c;
    static const uint C31 = 0xff422445;
    static const uint C32 = 0xff5a265e;
    static const uint C33 = 0xff80366b;
    static const uint C34 = 0xffbd4882;
    static const uint C35 = 0xffff6b97;
    static const uint C36 = 0xffffb5b5;

    static const uint ALL[] = {
      C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19, C20,
      C21, C22, C23, C24, C25, C26, C27, C28, C29, C30, C31, C32, C33, C34, C35, C36
    };

    static const glm::vec4 C1_VEC4 = to_vec4(C1);
    static const glm::vec4 C2_VEC4 = to_vec4(C2);
    static const glm::vec4 C3_VEC4 = to_vec4(C3);
    static const glm::vec4 C4_VEC4 = to_vec4(C4);
    static const glm::vec4 C5_VEC4 = to_vec4(C5);
    static const glm::vec4 C6_VEC4 = to_vec4(C6);
    static const glm::vec4 C7_VEC4 = to_vec4(C7);
    static const glm::vec4 C8_VEC4 = to_vec4(C8);
    static const glm::vec4 C9_VEC4 = to_vec4(C9);
    static const glm::vec4 C10_VEC4 = to_vec4(C10);
    static const glm::vec4 C11_VEC4 = to_vec4(C11);
    static const glm::vec4 C12_VEC4 = to_vec4(C12);
    static const glm::vec4 C13_VEC4 = to_vec4(C13);
    static const glm::vec4 C14_VEC4 = to_vec4(C14);
    static const glm::vec4 C15_VEC4 = to_vec4(C15);
    static const glm::vec4 C16_VEC4 = to_vec4(C16);
    static const glm::vec4 C17_VEC4 = to_vec4(C17);
    static const glm::vec4 C18_VEC4 = to_vec4(C18);
    static const glm::vec4 C19_VEC4 = to_vec4(C19);
    static const glm::vec4 C20_VEC4 = to_vec4(C20);
    static const glm::vec4 C21_VEC4 = to_vec4(C21);
    static const glm::vec4 C22_VEC4 = to_vec4(C22);
    static const glm::vec4 C23_VEC4 = to_vec4(C23);
    static const glm::vec4 C24_VEC4 = to_vec4(C24);
    static const glm::vec4 C25_VEC4 = to_vec4(C25);
    static const glm::vec4 C26_VEC4 = to_vec4(C26);
    static const glm::vec4 C27_VEC4 = to_vec4(C27);
    static const glm::vec4 C28_VEC4 = to_vec4(C28);
    static const glm::vec4 C29_VEC4 = to_vec4(C29);
    static const glm::vec4 C30_VEC4 = to_vec4(C30);
    static const glm::vec4 C31_VEC4 = to_vec4(C31);
    static const glm::vec4 C32_VEC4 = to_vec4(C32);
    static const glm::vec4 C33_VEC4 = to_vec4(C33);
    static const glm::vec4 C34_VEC4 = to_vec4(C34);
    static const glm::vec4 C35_VEC4 = to_vec4(C35);
    static const glm::vec4 C36_VEC4 = to_vec4(C36);

    static const glm::vec4 ALL_VEC4[] = {
      C1_VEC4, C2_VEC4, C3_VEC4, C4_VEC4, C5_VEC4, C6_VEC4, C7_VEC4, C8_VEC4,
      C9_VEC4, C10_VEC4, C11_VEC4, C12_VEC4, C13_VEC4, C14_VEC4, C15_VEC4, C16_VEC4,
      C17_VEC4, C18_VEC4, C19_VEC4, C20_VEC4, C21_VEC4, C22_VEC4, C23_VEC4, C24_VEC4,
      C25_VEC4, C26_VEC4, C27_VEC4, C28_VEC4, C29_VEC4, C30_VEC4, C31_VEC4, C32_VEC4,
      C33_VEC4, C34_VEC4, C35_VEC4, C36_VEC4
    };

    static const glm::vec3 C1_VEC3 = glm::vec3(C1_VEC4.r, C1_VEC4.g, C1_VEC4.b);
    static const glm::vec3 C2_VEC3 = glm::vec3(C2_VEC4.r, C2_VEC4.g, C2_VEC4.b);
    static const glm::vec3 C3_VEC3 = glm::vec3(C3_VEC4.r, C3_VEC4.g, C3_VEC4.b);
    static const glm::vec3 C4_VEC3 = glm::vec3(C4_VEC4.r, C4_VEC4.g, C4_VEC4.b);
    static const glm::vec3 C5_VEC3 = glm::vec3(C5_VEC4.r, C5_VEC4.g, C5_VEC4.b);
    static const glm::vec3 C6_VEC3 = glm::vec3(C6_VEC4.r, C6_VEC4.g, C6_VEC4.b);
    static const glm::vec3 C7_VEC3 = glm::vec3(C7_VEC4.r, C7_VEC4.g, C7_VEC4.b);
    static const glm::vec3 C8_VEC3 = glm::vec3(C8_VEC4.r, C8_VEC4.g, C8_VEC4.b);
    static const glm::vec3 C9_VEC3 = glm::vec3(C9_VEC4.r, C9_VEC4.g, C9_VEC4.b);
    static const glm::vec3 C10_VEC3 = glm::vec3(C10_VEC4.r, C10_VEC4.g, C10_VEC4.b);
    static const glm::vec3 C11_VEC3 = glm::vec3(C11_VEC4.r, C11_VEC4.g, C11_VEC4.b);
    static const glm::vec3 C12_VEC3 = glm::vec3(C12_VEC4.r, C12_VEC4.g, C12_VEC4.b);
    static const glm::vec3 C13_VEC3 = glm::vec3(C13_VEC4.r, C13_VEC4.g, C13_VEC4.b);
    static const glm::vec3 C14_VEC3 = glm::vec3(C14_VEC4.r, C14_VEC4.g, C14_VEC4.b);
    static const glm::vec3 C15_VEC3 = glm::vec3(C15_VEC4.r, C15_VEC4.g, C15_VEC4.b);
    static const glm::vec3 C16_VEC3 = glm::vec3(C16_VEC4.r, C16_VEC4.g, C16_VEC4.b);
    static const glm::vec3 C17_VEC3 = glm::vec3(C17_VEC4.r, C17_VEC4.g, C17_VEC4.b);
    static const glm::vec3 C18_VEC3 = glm::vec3(C18_VEC4.r, C18_VEC4.g, C18_VEC4.b);
    static const glm::vec3 C19_VEC3 = glm::vec3(C19_VEC4.r, C19_VEC4.g, C19_VEC4.b);
    static const glm::vec3 C20_VEC3 = glm::vec3(C20_VEC4.r, C20_VEC4.g, C20_VEC4.b);
    static const glm::vec3 C21_VEC3 = glm::vec3(C21_VEC4.r, C21_VEC4.g, C21_VEC4.b);
    static const glm::vec3 C22_VEC3 = glm::vec3(C22_VEC4.r, C22_VEC4.g, C22_VEC4.b);
    static const glm::vec3 C23_VEC3 = glm::vec3(C23_VEC4.r, C23_VEC4.g, C23_VEC4.b);
    static const glm::vec3 C24_VEC3 = glm::vec3(C24_VEC4.r, C24_VEC4.g, C24_VEC4.b);
    static const glm::vec3 C25_VEC3 = glm::vec3(C25_VEC4.r, C25_VEC4.g, C25_VEC4.b);
    static const glm::vec3 C26_VEC3 = glm::vec3(C26_VEC4.r, C26_VEC4.g, C26_VEC4.b);
    static const glm::vec3 C27_VEC3 = glm::vec3(C27_VEC4.r, C27_VEC4.g, C27_VEC4.b);
    static const glm::vec3 C28_VEC3 = glm::vec3(C28_VEC4.r, C28_VEC4.g, C28_VEC4.b);
    static const glm::vec3 C29_VEC3 = glm::vec3(C29_VEC4.r, C29_VEC4.g, C29_VEC4.b);
    static const glm::vec3 C30_VEC3 = glm::vec3(C30_VEC4.r, C30_VEC4.g, C30_VEC4.b);
    static const glm::vec3 C31_VEC3 = glm::vec3(C31_VEC4.r, C31_VEC4.g, C31_VEC4.b);
    static const glm::vec3 C32_VEC3 = glm::vec3(C32_VEC4.r, C32_VEC4.g, C32_VEC4.b);
    static const glm::vec3 C33_VEC3 = glm::vec3(C33_VEC4.r, C33_VEC4.g, C33_VEC4.b);
    static const glm::vec3 C34_VEC3 = glm::vec3(C34_VEC4.r, C34_VEC4.g, C34_VEC4.b);
    static const glm::vec3 C35_VEC3 = glm::vec3(C35_VEC4.r, C35_VEC4.g, C35_VEC4.b);
    static const glm::vec3 C36_VEC3 = glm::vec3(C36_VEC4.r, C36_VEC4.g, C36_VEC4.b);

    static const glm::vec3 ALL_VEC3[] = {
      C1_VEC3, C2_VEC3, C3_VEC3, C4_VEC3, C5_VEC3, C6_VEC3, C7_VEC3, C8_VEC3, C9_VEC3, C10_VEC3, C11_VEC3, C12_VEC3,
      C13_VEC3, C14_VEC3, C15_VEC3, C16_VEC3, C17_VEC3, C18_VEC3, C19_VEC3, C20_VEC3, C21_VEC3, C22_VEC3, C23_VEC3,
      C24_VEC3, C25_VEC3, C26_VEC3, C27_VEC3, C28_VEC3, C29_VEC3, C30_VEC3, C31_VEC3, C32_VEC3, C33_VEC3, C34_VEC3,
      C35_VEC3, C36_VEC3
    };

  }

  namespace Mocha {
    static const uint SIZE = 26;

    static const uint ROSEWATER = 0xfff5e0dc;
    static const uint FLAMINGO = 0xfff2cdcd;
    static const uint PINK = 0xfff5c2e7;
    static const uint MAUVE = 0xffcba6f7;
    static const uint RED = 0xfff38ba8;
    static const uint MAROON = 0xffeba0ac;
    static const uint PEACH = 0xfffab387;
    static const uint YELLOW = 0xfff9e2af;
    static const uint GREEN = 0xffa6e3a1;
    static const uint TEAL = 0xff94e2d5;
    static const uint SKY = 0xff89dceb;
    static const uint SAPPHIRE = 0xff74c7ec;
    static const uint BLUE = 0xff89b4fa;
    static const uint LAVENDER = 0xffb4befe;
    static const uint TEXT = 0xffcdd6f4;
    static const uint SUBTEXT1 = 0xffbac2de;
    static const uint SUBTEXT0 = 0xffa6adc8;
    static const uint OVERLAY2 = 0xff9399b2;
    static const uint OVERLAY1 = 0xff7f849c;
    static const uint OVERLAY0 = 0xff6c7086;
    static const uint SURFACE2 = 0xff585b70;
    static const uint SURFACE1 = 0xff45475a;
    static const uint SURFACE0 = 0xff313244;
    static const uint BASE = 0xff1e1e2e;
    static const uint MANTLE = 0xff181825;
    static const uint CRUST = 0xff11111b;

    static const uint ALL[] = {
      ROSEWATER, FLAMINGO, PINK, MAUVE, RED, MAROON, PEACH, YELLOW, GREEN, TEAL, SKY, SAPPHIRE,
      BLUE,
      LAVENDER, TEXT, SUBTEXT1, SUBTEXT0, OVERLAY2, OVERLAY1, OVERLAY0, SURFACE2, SURFACE1,
      SURFACE0,
      BASE, MANTLE, CRUST
    };

    static const glm::vec4 ROSEWATER_VEC4 = to_vec4(ROSEWATER);
    static const glm::vec4 FLAMINGO_VEC4 = to_vec4(FLAMINGO);
    static const glm::vec4 PINK_VEC4 = to_vec4(PINK);
    static const glm::vec4 MAUVE_VEC4 = to_vec4(MAUVE);
    static const glm::vec4 RED_VEC4 = to_vec4(RED);
    static const glm::vec4 MAROON_VEC4 = to_vec4(MAROON);
    static const glm::vec4 PEACH_VEC4 = to_vec4(PEACH);
    static const glm::vec4 YELLOW_VEC4 = to_vec4(YELLOW);
    static const glm::vec4 GREEN_VEC4 = to_vec4(GREEN);
    static const glm::vec4 TEAL_VEC4 = to_vec4(TEAL);
    static const glm::vec4 SKY_VEC4 = to_vec4(SKY);
    static const glm::vec4 SAPPHIRE_VEC4 = to_vec4(SAPPHIRE);
    static const glm::vec4 BLUE_VEC4 = to_vec4(BLUE);
    static const glm::vec4 LAVENDER_VEC4 = to_vec4(LAVENDER);
    static const glm::vec4 TEXT_VEC4 = to_vec4(TEXT);
    static const glm::vec4 SUBTEXT1_VEC4 = to_vec4(SUBTEXT1);
    static const glm::vec4 SUBTEXT0_VEC4 = to_vec4(SUBTEXT0);
    static const glm::vec4 OVERLAY2_VEC4 = to_vec4(OVERLAY2);
    static const glm::vec4 OVERLAY1_VEC4 = to_vec4(OVERLAY1);
    static const glm::vec4 OVERLAY0_VEC4 = to_vec4(OVERLAY0);
    static const glm::vec4 SURFACE2_VEC4 = to_vec4(SURFACE2);
    static const glm::vec4 SURFACE1_VEC4 = to_vec4(SURFACE1);
    static const glm::vec4 SURFACE0_VEC4 = to_vec4(SURFACE0);
    static const glm::vec4 BASE_VEC4 = to_vec4(BASE);
    static const glm::vec4 MANTLE_VEC4 = to_vec4(MANTLE);
    static const glm::vec4 CRUST_VEC4 = to_vec4(CRUST);

    static const glm::vec4 ALL_VEC4[] = {
      ROSEWATER_VEC4, FLAMINGO_VEC4, PINK_VEC4, MAUVE_VEC4, RED_VEC4, MAROON_VEC4,
      PEACH_VEC4, YELLOW_VEC4, GREEN_VEC4, TEAL_VEC4, SKY_VEC4, SAPPHIRE_VEC4,
      BLUE_VEC4,
      LAVENDER_VEC4, TEXT_VEC4, SUBTEXT1_VEC4, SUBTEXT0_VEC4, OVERLAY2_VEC4,
      OVERLAY1_VEC4,
      OVERLAY0_VEC4, SURFACE2_VEC4, SURFACE1_VEC4, SURFACE0_VEC4, BASE_VEC4,
      MANTLE_VEC4,
      CRUST_VEC4
    };

    static const glm::vec3 ROSWATER_VEC3 = glm::vec3(ROSEWATER_VEC4.x, ROSEWATER_VEC4.y, ROSEWATER_VEC4.z);
    static const glm::vec3 FLAMINGO_VEC3 = glm::vec3(FLAMINGO_VEC4.x, FLAMINGO_VEC4.y, FLAMINGO_VEC4.z);
    static const glm::vec3 PINK_VEC3 = glm::vec3(PINK_VEC4.x, PINK_VEC4.y, PINK_VEC4.z);
    static const glm::vec3 MAUVE_VEC3 = glm::vec3(MAUVE_VEC4.x, MAUVE_VEC4.y, MAUVE_VEC4.z);
    static const glm::vec3 RED_VEC3 = glm::vec3(RED_VEC4.x, RED_VEC4.y, RED_VEC4.z);
    static const glm::vec3 MAROON_VEC3 = glm::vec3(MAROON_VEC4.x, MAROON_VEC4.y, MAROON_VEC4.z);
    static const glm::vec3 PEACH_VEC3 = glm::vec3(PEACH_VEC4.x, PEACH_VEC4.y, PEACH_VEC4.z);
    static const glm::vec3 YELLOW_VEC3 = glm::vec3(YELLOW_VEC4.x, YELLOW_VEC4.y, YELLOW_VEC4.z);
    static const glm::vec3 GREEN_VEC3 = glm::vec3(GREEN_VEC4.x, GREEN_VEC4.y, GREEN_VEC4.z);
    static const glm::vec3 TEAL_VEC3 = glm::vec3(TEAL_VEC4.x, TEAL_VEC4.y, TEAL_VEC4.z);
    static const glm::vec3 SKY_VEC3 = glm::vec3(SKY_VEC4.x, SKY_VEC4.y, SKY_VEC4.z);
    static const glm::vec3 SAPPHIRE_VEC3 = glm::vec3(SAPPHIRE_VEC4.x, SAPPHIRE_VEC4.y, SAPPHIRE_VEC4.z);
    static const glm::vec3 BLUE_VEC3 = glm::vec3(BLUE_VEC4.x, BLUE_VEC4.y, BLUE_VEC4.z);
    static const glm::vec3 LAVENDER_VEC3 = glm::vec3(LAVENDER_VEC4.x, LAVENDER_VEC4.y, LAVENDER_VEC4.z);
    static const glm::vec3 TEXT_VEC3 = glm::vec3(TEXT_VEC4.x, TEXT_VEC4.y, TEXT_VEC4.z);
    static const glm::vec3 SUBTEXT1_VEC3 = glm::vec3(SUBTEXT1_VEC4.x, SUBTEXT1_VEC4.y, SUBTEXT1_VEC4.z);
    static const glm::vec3 SUBTEXT0_VEC3 = glm::vec3(SUBTEXT0_VEC4.x, SUBTEXT0_VEC4.y, SUBTEXT0_VEC4.z);
    static const glm::vec3 OVERLAY2_VEC3 = glm::vec3(OVERLAY2_VEC4.x, OVERLAY2_VEC4.y, OVERLAY2_VEC4.z);
    static const glm::vec3 OVERLAY1_VEC3 = glm::vec3(OVERLAY1_VEC4.x, OVERLAY1_VEC4.y, OVERLAY1_VEC4.z);
    static const glm::vec3 OVERLAY0_VEC3 = glm::vec3(OVERLAY0_VEC4.x, OVERLAY0_VEC4.y, OVERLAY0_VEC4.z);
    static const glm::vec3 SURFACE2_VEC3 = glm::vec3(SURFACE2_VEC4.x, SURFACE2_VEC4.y, SURFACE2_VEC4.z);
    static const glm::vec3 SURFACE1_VEC3 = glm::vec3(SURFACE1_VEC4.x, SURFACE1_VEC4.y, SURFACE1_VEC4.z);
    static const glm::vec3 SURFACE0_VEC3 = glm::vec3(SURFACE0_VEC4.x, SURFACE0_VEC4.y, SURFACE0_VEC4.z);
    static const glm::vec3 BASE_VEC3 = glm::vec3(BASE_VEC4.x, BASE_VEC4.y, BASE_VEC4.z);
    static const glm::vec3 MANTLE_VEC3 = glm::vec3(MANTLE_VEC4.x, MANTLE_VEC4.y, MANTLE_VEC4.z);
    static const glm::vec3 CRUST_VEC3 = glm::vec3(CRUST_VEC4.x, CRUST_VEC4.y, CRUST_VEC4.z);

    static const glm::vec3 ALL_VEC3[] = {
      ROSWATER_VEC3, FLAMINGO_VEC3, PINK_VEC3, MAUVE_VEC3, RED_VEC3, MAROON_VEC3,
      PEACH_VEC3, YELLOW_VEC3, GREEN_VEC3, TEAL_VEC3, SKY_VEC3, SAPPHIRE_VEC3,
      BLUE_VEC3, LAVENDER_VEC3, TEXT_VEC3, SUBTEXT1_VEC3, SUBTEXT0_VEC3,
      OVERLAY2_VEC3,
      OVERLAY1_VEC3, OVERLAY0_VEC3, SURFACE2_VEC3, SURFACE1_VEC3, SURFACE0_VEC3,
      BASE_VEC3,
      MANTLE_VEC3, CRUST_VEC3
    };
  }

  namespace DreamyHaze {
    static const uint SIZE = 8;

    static const uint C1 = 0xff3c42c4;
    static const uint C2 = 0xff6e51c8;
    static const uint C3 = 0xffa065cd;
    static const uint C4 = 0xffce79d2;
    static const uint C5 = 0xffd68fb8;
    static const uint C6 = 0xffdda2a3;
    static const uint C7 = 0xffeac4ae;
    static const uint C8 = 0xfff4dfbe;

    static const uint ALL[] = {C1, C2, C3, C4, C5, C6, C7, C8};

    static const glm::vec4 C1_VEC4 = to_vec4(C1);
    static const glm::vec4 C2_VEC4 = to_vec4(C2);
    static const glm::vec4 C3_VEC4 = to_vec4(C3);
    static const glm::vec4 C4_VEC4 = to_vec4(C4);
    static const glm::vec4 C5_VEC4 = to_vec4(C5);
    static const glm::vec4 C6_VEC4 = to_vec4(C6);
    static const glm::vec4 C7_VEC4 = to_vec4(C7);
    static const glm::vec4 C8_VEC4 = to_vec4(C8);

    static const glm::vec4 ALL_VEC4[] = {C1_VEC4, C2_VEC4, C3_VEC4, C4_VEC4, C5_VEC4, C6_VEC4, C7_VEC4, C8_VEC4};

    static const glm::vec3 C1_VEC3 = glm::vec3(C1_VEC4.x, C1_VEC4.y, C1_VEC4.z);
    static const glm::vec3 C2_VEC3 = glm::vec3(C2_VEC4.x, C2_VEC4.y, C2_VEC4.z);
    static const glm::vec3 C3_VEC3 = glm::vec3(C3_VEC4.x, C3_VEC4.y, C3_VEC4.z);
    static const glm::vec3 C4_VEC3 = glm::vec3(C4_VEC4.x, C4_VEC4.y, C4_VEC4.z);
    static const glm::vec3 C5_VEC3 = glm::vec3(C5_VEC4.x, C5_VEC4.y, C5_VEC4.z);
    static const glm::vec3 C6_VEC3 = glm::vec3(C6_VEC4.x, C6_VEC4.y, C6_VEC4.z);
    static const glm::vec3 C7_VEC3 = glm::vec3(C7_VEC4.x, C7_VEC4.y, C7_VEC4.z);
    static const glm::vec3 C8_VEC3 = glm::vec3(C8_VEC4.x, C8_VEC4.y, C8_VEC4.z);

    static const glm::vec3 ALL_VEC3[] = {C1_VEC3, C2_VEC3, C3_VEC3, C4_VEC3, C5_VEC3, C6_VEC3, C7_VEC3, C8_VEC3};
  }
}

#endif //EMBER_IML_PALETTE_H
