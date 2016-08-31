#pragma once
#include <QFile>
#include <QString>
#include <QVector>

#include "settings.h"
#include "data.h"

class DataHandler
{
public:
	DataHandler(Settings& s); 
	~DataHandler() {}

	int update_content();
	void print_all();
	QVector<Data> datas() { return datas_; }

private:
	Settings *settings_;

	QVector<QString> file_content_;
	QVector<QString> current_lines_; 
	// should have length equivalent to number of datapoints to
	// be plotted

	int file_length_;
	int fields; // Of CSV formatted data
//	QString current_line_;


	QVector<Data> datas_;

	// Functions
	int read_file();

};



