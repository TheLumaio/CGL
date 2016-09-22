#include "splash.h"

GameState splash_state;

unsigned int splash_init()
{
	timer = 0;
	alpha = 0;
	flag = 0;
	staytimer = 0;
	cgl_InitSprite(&logo, "data/logo.png");
	cgl_InitSprite(&powered, "data/powered.png");
	cgl_InitShaderProgram(&shader, "data/sprite_vert.glsl", "data/sprite_frag.glsl");
	// printf("splash_init\n");
	return 0;
}

unsigned int splash_update(Game* game, float dt)
{
	timer += dt;
	
	if (alpha < 1 && flag == 0) alpha += dt*0.3f;
	if (alpha >= 1) flag = 1;
	if (flag == 1) staytimer += dt;
	if (staytimer > 1) flag = 2;
	if (flag == 2 && alpha > 0) alpha -= dt*0.3f;
	if (flag == 2 && alpha <= 0) cgl_SetStateGame(game, &test_state);
	
	return 0;
}

unsigned int splash_render(GameWindow* window)
{
	glClearColor(0, 0, 0, 1);
	vec4 color = {alpha, alpha, alpha, alpha};
	cgl_DrawSpriteColor(&powered, &shader, _cgl_window_size[0]/2-powered.width/2, _cgl_window_size[1]/1.2-powered.height/2, color);
	vec2 scale = {0.5, 0.5};
	cgl_DrawSpriteScaleColor(&logo, &shader, _cgl_window_size[0]/2-logo.width*scale[0]/2, _cgl_window_size[1]/2-logo.height*scale[1]/2, scale, color);
	
	return 0;
}

unsigned int splash_mousemoved(double x, double y)
{
	
}
