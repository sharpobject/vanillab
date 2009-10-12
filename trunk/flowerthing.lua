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