routines={};
DEGREES=0.017453292519943295769236907684886;
function wait(howlong)
	if(howlong==0) then
		return
	end
	setWaitFrames(howlong);
	coroutine.yield();
end
function run()
	local id=getID();
	if(routines[id]) then
		coroutine.resume(routines[id]);
	end
end
function register(f)
	routines[getNewest()]=coroutine.create(f);
end
function fire(a,b,c)
	cfire(a,b);
	if(c==nil) then
		return
	end
	register(c);
end
function cleanup()
	routines[getID()]=nil;
end

NO_SPRITE=-1;
SPR_MED_CIR_BULLET=NO_SPRITE+1;
SPR_ARROW=SPR_MED_CIR_BULLET+1;
SPR_PLAYER=SPR_ARROW+1;
SPR_APPLE=SPR_PLAYER+1;
N_SPRITES=SPR_APPLE+1;

ENEMY=0
PLAYER_BULLET=ENEMY+1;
PLAYER=PLAYER_BULLET+1;
ENEMY_BULLET=PLAYER+1;
SPECIAL_OBJECT=ENEMY_BULLET+1;
N_OBJECT_CLASSES=SPECIAL_OBJECT+1;