routines={};
de=0.017453292519943295769236907684886;
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
	local id=getID();
	routines[id]=coroutine.create(f);
end