function flowerthing()
	setChildType(ENEMY_BULLET);
	local dir=-6
	while true do
		for j=0,3 do
			setChildSprite(SPR_MED_CIR_BULLET);
			for i=8,1,-1 do
				fire(2.5*i,dir*DEGREES)
			end
			dir=dir+12
			setChildSprite(SPR_ARROW);
			for i=8,1,-1 do
				fire(2.5*i,dir*DEGREES)
			end
			dir=dir+78
		end
		dir=math.fmod(dir+3,360)
		wait(3)
	end
end
function bomb()
	setChildType(ENEMY_BULLET)
	setChildSprite(SPR_MED_CIR_BULLET)
	local nbulletsalongslope=60
	local step=math.pi/(4*(2+2*nbulletsalongslope))
	local dir=0
	local startspeed=7
	local speedstep=.105/3
	local speed=startspeed
	for i=0,7 do
		for j=0,nbulletsalongslope do
			fire(speed,dir)
			speed=speed-speedstep
			dir=dir+step
		end
		for j=0,nbulletsalongslope do
			fire(speed,dir)
			speed=speed+speedstep
			dir=dir+step
		end
	end
	vanish()
end