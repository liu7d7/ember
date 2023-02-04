//
// Created by richard may clarkson on 10/12/2022.
//
#include "ember.h"
#include "stb_image.h"
#include "engine/fbo.h"
#include "iomanip"
#include "engine/glsm.h"
#include "impl/entity.h"
#include "impl/comp.h"
#include "impl/world.h"
#include "impl/palette.h"

namespace Ember {
  GLFWwindow* window;
  int width, height;

  int age;
  uint mouseState;
  float mouseX, mouseY, lastMouseX, lastMouseY;
  float tickDelta;
  bool firstMove = true;

  Font* font;
  World* world;
  Entity* player;
  Mesh<glm::vec2>* postProcessMesh;
  bool dither = true;

  void initGL() {
    if (glfwInit() != GLFW_TRUE) {
      die("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    if ((window = glfwCreateWindow(1152, 720, "test", nullptr, nullptr)) == nullptr) {
      die("Failed to create Window!");
    }
    width = 1152;
    height = 720;
    glfwMakeContextCurrent(window);

    GL::init();
    stbi_set_flip_vertically_on_load(true);

    mouseState = GLFW_CURSOR_NORMAL;

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
      if (win != window) return;
      Ember::width = width;
      Ember::height = height;
      glViewport(0, 0, width, height);
      GL::fbo->resize(width, height);
      GL::intermediaryFbo->resize(width, height);
      GL::postProcessFbo->resize(width / 2, height / 2);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double x, double y) {
      if (win != window) return;
      GL::cam.scroll((float) y);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scan, int action, int mods) {
      if (win != window) return;
      if (key == GLFW_KEY_T && action == GLFW_PRESS)
        dither = !dither;
    });

    glClearColor(yellow.r, yellow.g, yellow.b, yellow.a);

    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glEnable(GL_MULTISAMPLE);

    glfwSwapInterval(0);
  }

  void init() {
    initGL();
    {
      var bytes = Files::read_bytes("res/font/futur.ttf");
      font = new Font(bytes, 1024, 20);
      delete[] bytes.ptr;
    }
    GL::fbo = new Framebuffer(width, height, true, true, true);
    GL::intermediaryFbo = new Framebuffer(width, height, true, false, false);
    GL::postProcessFbo = new Framebuffer(width / 2, height / 2, true, false, false);
    player = new Entity;
    player->add(new Position);
    player->add(new Velocity);
    player->add(new Player);
    world = new World;
    world->entities.push_back(player);
    postProcessMesh = new Mesh<glm::vec2>(DrawModes::triangle, {Attribute::FLOAT2});
    postProcessMesh->begin();
    postProcessMesh->quad(
      postProcessMesh->put({0, 0}),
      postProcessMesh->put({1, 0}),
      postProcessMesh->put({1, 1}),
      postProcessMesh->put({0, 1})
    );
    postProcessMesh->end();
  }

  void input(float dt) {

  }

  int update_ticks() {
    const float tickTime = 50.f; // 20 tps
    static float lastFrame = 0.f;
    static float prevTimeMs = 0.f;
    auto time = now;
    lastFrame = (time - prevTimeMs) / tickTime;
    prevTimeMs = time;
    tickDelta += lastFrame;
    int i = (int) tickDelta;
    tickDelta -= (float) i;
    return i;
  }

  void run() {
    auto t = float(glfwGetTime());
    float dt;
    while (!glfwWindowShouldClose(window)) {
      GL::cam.yaw = 90;
      GL::cam.pitch = -45.f;
      GL::cam.update();
      auto time = float(glfwGetTime());
      dt = time - t;
      t = time;
      input(dt);

      int j = update_ticks();
      for (int i = 0; i < std::min(j, 10); i++) {
        tick();
      }
      draw(dt);

      glfwPollEvents();
      glfwSwapBuffers(window);
    }

    glfwTerminate();
  }

  void tick() {
    age++;
    world->update(player->get<Position>()->pos);
  }

  double avg = 0.;
  double avgc = 1;
  std::wstring fps;
  int ptick = 0;

  void draw(double dt) {
    GL::cam.pos = player->get<Position>()->to_lerped(tickDelta);
    GL::fbo->use();
    GL::fbo->clear();
    GL::as_3d();
    GL::look = GL::cam.get_look();
    draw_3d();

    if (dither) {
      GL::shader = GL::get_dither();
      GL::shader.use();
      for (int i = 0; i < current_palette::SIZE; i++) {
        GL::shader.set_vec3("palette[" + std::to_string(i) + "]", current_palette::ALL_VEC3[i]);
      }
      GL::shader.set_int("paletteSize", current_palette::SIZE);
      GL::fbo->blit_by_handle(GL::intermediaryFbo->handle, width, height);
      GL::intermediaryFbo->blit_by_handle(GL::postProcessFbo->handle, width / 2, height / 2);
      GL::postProcessFbo->use();
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, GL::intermediaryFbo->color);
      glViewport(0, 0, width / 2, height / 2);
      postProcessMesh->draw();
      glViewport(0, 0, width, height);
    }

    // THIS IS SO GOOD!!!
    Framebuffer::unuse();
    if (dither) {
      GL::postProcessFbo->blit_by_handle(GL::intermediaryFbo->handle, width, height);
      GL::intermediaryFbo->blit_by_handle(0, width, height);
    } else
      GL::fbo->blit_by_handle(0, width, height);

    glDepthFunc(GL_ALWAYS);
    GL::shader = Font::get_shader();
    GL::as_2d();
    avg += dt;
    avgc++;
    if (age % 20 == 0 && age != ptick) {
      ptick = age;
      fps = (std::wstringstream() << std::fixed << std::setprecision(2) << L"fps: ~" << (1. / avg * avgc) << L", mspf: ~" << std::setprecision(6) << (avg / avgc) * 1000).str();
      avg = 0.;
      avgc = 0.;
    }
    font->add(fps, 10, 10, 0xffffffff, true);
    font->add((std::wstringstream() << std::fixed << std::setprecision(2) << L"xyz: " << GL::cam.pos.x << L", " << GL::cam.pos.y << L", " << GL::cam.pos.z).str(), 10, 30, 0xffffffff, true);
    font->draw();
    glDepthFunc(GL_LEQUAL);
  }

  void draw_3d() {
    world->render(player->get<Position>()->pos);
    InstancedModel::draw_all();
  }
}