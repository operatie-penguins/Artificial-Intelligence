#pragma once

class ITimer
{
protected:
	ITimer()
	{}
	ITimer( const ITimer& );
	ITimer& operator=( const ITimer& );
public:
	virtual void Reset() = 0;
	virtual void GetTime( float* AbsTime, float* ElapsedTime ) = 0; 
};