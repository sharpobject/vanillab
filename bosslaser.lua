function bossturret()
	setChildType(ENEMY_BULLET)
	setChildSprite(SPR_ARROW)
	while true do
		fire(5,aim(),bomb)
		wait(300)
	end
end
function bosslaser()
	setChildType(ENEMY_BULLET)
	setChildSprite(SPR_ARROW)
	wait(40)
	local mydirection=getDirection()
	fire(2,mydirection+90*DEGREES,turnrightpew)
	fire(2/3,mydirection+90*DEGREES,turnrightpew)
	fire(2/3,mydirection-90*DEGREES,turnleftpew)
	fire(2,mydirection-90*DEGREES,turnleftpew)
	vanish()
end
function turnrightpew()
	setChildType(ENEMY_BULLET)
	setChildSprite(SPR_MED_CIR_BULLET)
	changeSpeed(0,30)
	wait(30)
	local mydirection=getDirection()
	changeDirection(mydirection-90*DEGREES,40)
	wait(40)
	mydirection=getDirection()
	for i=0,30 do
		fire(1.4+i*1.87,mydirection,stopdie)
	end
	vanish()
end
function turnleftpew()
	setChildType(ENEMY_BULLET)
	setChildSprite(SPR_MED_CIR_BULLET)
	changeSpeed(0,30)
	wait(30)
	local mydirection=getDirection()
	changeDirection(mydirection+90*DEGREES,40)
	wait(40)
	mydirection=getDirection()
	for i=0,30 do
		fire(1.4+i*1.87,mydirection,stopdie)
	end
	vanish()
end
function stopdie()
	changeSpeed(0,60)
	wait(90)
	vanish()
end