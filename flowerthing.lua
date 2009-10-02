function flowerthing()
	wait(0)
	local dir=-6
	while true do
		for i=0,3 do
			for i=8,1,-1 do
				fire(2.5*i,dir*de)
			end
			dir=dir+12
			for i=8,1,-1 do
				fire(2.5*i,dir*de)
			end
			dir=dir+78
		end
		dir=dir+3
		wait(3)
	end
end