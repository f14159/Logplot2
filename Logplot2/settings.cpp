#include "settings.h"


Settings::Settings(QString input_filename, int timer_interval = 1000)
{
	timer_interval_ = timer_interval;
	input_filename_ = input_filename;
}

Settings::~Settings()
{
}



int Settings::timer_interval()
{
	return timer_interval_;
}

QString Settings::input_filename()
{
	return input_filename_;
}
