
#ifndef TEST_STATE_H
#define TEST_STATE_H

#include "../gamestate.h"
#include "../window.h"
#include "../shader.h"
#include "../image.h"
#include "../font.h"
#include "../lights.h"
#include "../billboard.h"

static ShaderProgram main_shader;
static ShaderProgram text_shader;
static ShaderProgram bill_shader;
static Image box;
static Image ground;
static Camera cam;
static Font font;
static Billboard board;

unsigned int test_init();
unsigned int test_update(Game*, float);
unsigned int test_render(GameWindow*);

GameState test_state;

#endif
