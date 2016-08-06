#pragma once
#include <QFile>
#include <QString>
#include <QVector>
#include "settings.h"

class DataHandler
{
public:
	DataHandler(Settings&);
	~DataHandler();

	void update_content();
	QString current_line();
	QString current_data();


private:
	QFile *input_file_;
	Settings *settings_;

	QString current_line_;
	QVector<QString> file_content_;

	QVector<double> current_data_;
	// !! index 0 is always time
	QVector<QVector<double>> data_; 

	// Functions
	void read_file();
	void extract_data();
};


// For storing the current time
// !! Todo: add datetime
class Time {
public:
	Time(Settings &s) { settings_ = &s; }
	~Time() {};
	void tick();
	QVector<int> t_count() { return t_count_; }

private:
	Settings *settings_;
	int ticks_;
	QVector<int> t_count_;
	QVector<int> t_ms_;
};