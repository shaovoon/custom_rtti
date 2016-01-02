#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#ifndef CPP11
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <MMSystem.h>

#pragma comment(lib, "winmm.lib")

class timer
{
public: 
	timer()
	{
		wTimerRes = 0;
		TIMECAPS tc;

		if (::timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
		{
			return;
		}

		wTimerRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
		::timeBeginPeriod(wTimerRes); 
	}
	~timer()
	{
		::timeEndPeriod(wTimerRes);
	}

	void start_timing(const std::string& text_)
	{
		text = text_;
		begin = timeGetTime();
	}
	void stop_timing()
	{
		DWORD end = timeGetTime();
		DWORD timing = end-begin;
		std::cout << std::setw(16) << text << ":" << std::setw(5) << timing << "ms" << std::endl;
	}

private:
	std::string text;
	DWORD begin;
	UINT wTimerRes;
};
#else

#include <chrono>

class timer
{
public: 
	timer() = default;
	void start_timing(const std::string& text_)
	{
		text = text_;
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop_timing()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << std::setw(16) << text << ":" << std::setw(5) << ms << "ms" << std::endl;
	}

private:
	std::string text;
	std::chrono::system_clock::time_point begin;
};
#endif