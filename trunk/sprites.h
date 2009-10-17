#ifndef __SpritesH__
#define __SpritesH__

enum SpriteName {NO_SPRITE=-1,
				SPR_MED_CIR_BULLET,
				SPR_ARROW,
				SPR_PLAYER,
				SPR_APPLE,
				SPR_BLACK,
				N_SPRITES};

/*typedef struct
{
	const char filename[60];

} SpriteInfo;*/

const char gSpriteFiles[N_SPRITES][60]={"textures/medium_circle_bullet.png",
										"textures/arrow.png",
										"textures/pointy_guy.png",
										"textures/apple.png",
										"textures/black.png"
										};

const float gSpriteCollisionRadius[N_SPRITES]={8.3f,
												5.0f,
												0.0f,
												45.0f,
												0.0f
												};

const float gSpriteScales[N_SPRITES]={25.0f/64.0f,
										25.0f/64.0f,
										25.0f/64.0f,
										100.0f/128.0f,
										4.0f/4.0f,
										};

#endif // __SpritesH__