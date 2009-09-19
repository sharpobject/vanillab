function wait(howlong)
	setWaitFrames(howlong);
	coroutine.yield();
end