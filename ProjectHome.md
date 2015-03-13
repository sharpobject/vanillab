## Introduction ##

The existing open-source language for scripting bullet hell games, [BulletML](http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html), leaves a lot to be desired.  The aim of this project is to move many of the things that must be done in code under BulletML into script.  vanillab will be a minimalist bullet hell game built to demonstrate a more robust scripting system, likely in lua instead of XML.  While the new system should retain the same per-object procedural feel of writing in BulletML, the following features that BulletML lacks will be included:
  * Each object, when created, may include additional variables to define various attributes, such as the object's texture, scale, or hue.
  * Objects will be able to fire lasers.
  * Objects will be able to spawn other objects from locations other than their center in various frames of reference.
  * Objects will be able to create children anchored to the original object.

I have noticed that [Danmakufu](http://touhou.wikia.com/wiki/Touhou_Danmakufu) provides functionality similar to these objectives, with a some important differences.  There is no open-source library for interpreting Danmakufu scripts, and Danmakufu scripts simply have a main function that is called each frame and must decide what to do based on the bullet's age.  In my opinion this style of scripting is inferior to per-object procedural scripting like in BulletML.  So really, this project should be all the good things about Danmakufu and all the good things about BulletML at the same time.

## Notes ##

I have noticed that it is possible to circumvent this problem entirely by associating a number of coroutines with each bullet, and calling resume() on each of them during the main loop.  If this solution does not cause problems for reasonable numbers of bullets (up to about 4000), then we may as well go with it.

The real substance of the project should be a system to turn per-object procedural scripts into functions that can be called periodically.  This must be efficient so that it can be done for a large number of scripts at runtime, either when the game starts or when the individual stage loads.  To illustrate the type of transformation desired, I will provide a very simple example.

This code:
```
function top()
	setSpeed(5);
	changeSpeed(10,180);	--//Double speed over the next 3 seconds.
	wait(200);		--//Wait until I'm 3.33 seconds old.
	local myoffset=math.random()*360/17.0;

	--//Fire 3 concentric regular rings of 17 bullets.
	for i=0,17 do
		for speed=3,7,2 do
			fireBullet(myoffset+i*360/17.0,speed,nulltop);
		end
	end
	vanish();
	return 1;
end

function nulltop()
	return 1;
end
```

Should become something like this:
```
function top(turn)
	if(turn==0) then
		setSpeed(5);
		changeSpeed(10,180);
	end
	if(turn==200) then
		local myoffset=math.random()*360/17.0;
		for i=0,17 do
			for speed=3,7,2 do
				fireBullet(myoffset+i*360/17.0,speed,nulltop);
			end
		end
		vanish();
	end
	return 1;
end

function nulltop(turn)
	return 1;
end
```

Ironically, the core of the project is on hold until I have a working engine from scratch that can run scripts in the latter format.