#pragma once
#include <QString>

/*
Container for settings. Interface for sanity checks.
Setters/getters implemented in header.
/**/ 

class Settings
{
public:
	Settings(QString input_filename, int update_interval);
	~Settings();

// !! TODO: Setters should do sanity checks
	bool set_input_filename(QString fname) { input_filename_ = fname; }
	bool set_output_filename(QString fname) { output_filename_ = fname; }

// Getters
	int timer_interval();
	QString input_filename();

private:
	QString input_filename_;
	QString output_filename_;
	QString csv_format_;
 	int timer_interval_;
};

