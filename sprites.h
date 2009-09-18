#ifndef __SpritesH__
#define __SpritesH__

enum SpriteName {NO_SPRITE=0,
				SPR_MED_CIR_BULLET,
				SPR_ARROW,
				SPR_PLAYER,
				N_SPRITES};

/*typedef struct
{
	const char filename[60];

} SpriteInfo;*/

const char gSpriteFiles[N_SPRITES][60]={"",
										"textures/medium_circle_bullet.png",
										"textures/arrow.png",
										"textures/pointy_guy.png"
										};

#endif // __SpritesH__