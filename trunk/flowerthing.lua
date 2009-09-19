de=0.017453292519943295769236907684886;
function flowerthing()
	wait(170);
	while true do
		local dir=-6;
		for i=0,3 do
			for i=1,8 do
				fire(2.5*i,dir*de);
			end
			dir=dir+12;
			for i=1,8 do
				fire(2.5*i,dir*de);
			end
			dir=dir+78;
		end
		wait(140);
	end
end