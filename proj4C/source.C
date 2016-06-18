#include "source.h"

void Source::Update(){
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	startTime();
	Execute();
	endTime();
	sprintf(msg, "%s: done executing. Time diff: %fs", SourceName(), timeDiff());
	Logger::LogEvent(msg);
	
}
double Source::endTime(){
	gettimeofday(&timeEnd, 0);
	return double((timeEnd.tv_usec + timeStart.tv_sec)/ 100000);
}

double Source::timeDiff(){
	//double timeDiff = double(timeEnd.tv_sec - timeStart.tv_sec);
	//timeDiff+=timeDiff;
	//return timeDiff;
	return double((timeEnd.tv_sec - timeStart.tv_sec)+double(timeEnd.tv_usec - timeStart.tv_usec)) / 100000;
}
