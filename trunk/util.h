#ifndef __UtilH__
#define __UtilH__
#include <math.h>
extern "C"
{
# include "lua/src/lua.h"
# include "lua/src/lauxlib.h"
# include "lua/src/lualib.h"
}

#define DIRECTINPUT_VERSION 0x0800

#define MAX_N_OBJECTS 10000
#define TEXTURE_SZ 64.0f

#define PI 3.141592653589793238462643383279502f
#define DEGREE 0.01745329251994329576923690768489f
#define FULL_CIRCLE 6.283185307179586476925286766559f
#define FACING_RIGHT 0.0f
#define FACING_UP 1.5707963267948966192313216916398f
#define FACING_LEFT 3.141592653589793238462643383279502f
#define FACING_DOWN 4.7123889803846898576939650749193f

#define FPS_UPDATE_INTERVAL 20

//This value is for porting shitstorm to vanillab.
//Any reasonable positive real value is fine, as long as
//you do all your scripting and testing with the same value.
#define SPEED_SCALE 0.65106167700097107865980762762041f

enum ObjectClass {ENEMY=0,
				PLAYER_BULLET,
				PLAYER,
				ENEMY_BULLET,
				SPECIAL_OBJECT,
				N_OBJECT_CLASSES};

inline void getPolar(float x,float y,float &r, float &theta)
{
	r=sqrt(x*x+y*y);
	theta=atan2(-y,x);
}

inline void getCartesian(float &x,float &y,float r, float theta)
{
	x=r*cos(theta);
	y=-r*sin(theta);
}

inline float getXFromPolar(float r,float theta)
{
	return r*cos(theta);
}

inline float getYFromPolar(float r,float theta)
{
	return -r*sin(theta);
}

#endif //__UtilH__