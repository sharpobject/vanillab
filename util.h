#ifndef __UtilH__
#define __UtilH__
#include <math.h>

#define DIRECTINPUT_VERSION 0x0800

const float PI=3.141592653589793238462643383279502f;
const float TEXTURE_SZ =(64.0f);
const float DEGREE=PI/180;
const float FULL_CIRCLE=PI*2;
const float FACING_RIGHT=0;
const float FACING_UP=PI*.5f;
const float FACING_LEFT=PI;
const float FACING_DOWN=PI*1.5f;
const int FPS_UPDATE_FREQ=20;

inline void getPolar(float &x,float &y,float &r, float &theta)
{
	r=sqrt(x*x+y*y);
	theta=atan2(-y,x);
}

inline void getCartesian(float &x,float &y,float &r, float &theta)
{
	x=r*cos(theta);
	y=-r*sin(theta);
}

#endif //__UtilH__D: