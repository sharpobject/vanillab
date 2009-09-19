routines={};
function register(f)
	local id=getID();
	routines[id]=coroutine.create(f);
end