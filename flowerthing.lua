function slowdown()
	changeSpeed(0,200);
	wait(210);
	vanish();
end
function flowerthing()
	setChildSprite(SPR_MED_CIR_BULLET);
	setChildType(ENEMY_BULLET);
	wait(0)
	local dir=-6
	while true do
		for j=0,3 do
			setChildSprite(SPR_MED_CIR_BULLET);
			for i=8,1,-1 do
				fire(2.5*i,dir*de)
			end
			dir=dir+12
			setChildSprite(SPR_ARROW);
			for i=8,1,-1 do
				fire(2.5*i,dir*de)
			end
			dir=dir+78
		end
		dir=math.fmod(dir+3,360)
		wait(3)
	end
end
function level1()
	
	wait(60);
end