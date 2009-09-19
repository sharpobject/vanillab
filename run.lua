myvalues=-1;

function run()
	myvalues=-2;
	local id=getID();
	myvalues=-3;
	if(not routines[id]==nil) then
		myvalues=-12;
		coroutine.resume(routines[id]);
	else
		myvalues=id;
	end
end