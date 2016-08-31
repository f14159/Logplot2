#include <QStringList>
#include <QVector>
#include <QDebug>

#include "datahandler.h"

DataHandler::DataHandler(Settings &s) {
	settings_ = &s;
	read_file();

	file_length_ = file_content_.length();
	QString last_line = file_content_.last();

	fields = last_line.split(",").length();


	// !! TODO check first line for field descriptors
	for (int i = 0; i < fields; ++i) {
		Data *d = new Data(s, i);
		d->update(last_line);
		datas_.append(*d);
	}
}

int DataHandler::update_content() {
	// !! TODO: should seek to file_length_
	// !! TODO: tries and catches
    // !! TODO: move duplicate code from constructor to own function

	if (read_file() != 0) {
		qDebug() << "Error updating.";
		return 1;
	};
	file_length_ = file_content_.length();
	QString last_line = file_content_.last();

	fields = last_line.split(",").length();

	// !! TODO check first line for field descriptors
	for (auto data : datas_) {
		data.update(last_line);
	}

	return 0;
}


/*
void DataHandler::update_content()
{
	read_file();
	
	for (int i = 0; i < data_.length; ++i)
		data_[i].update(file_content_[file_content_.length() - 1], i);




	// !! Assume double. This needs some checks.
// !! Format of input should be in settings.
/**
extract_data();
data_.append(new Data(file_content_[file_content_.size() - 1]))
}

void DataHandler::extract_data() {
	// Make data from current_line_ and save it.
	QStringList qsl = current_line_.split(",");
	current_data_.clear();
	for (QString e : qsl) {
		current_data_.append(e.toDouble());
//		qDebug() << e;
	}

	data_.append(current_data_);
}


QString DataHandler::current_line()
{
	return current_line_;
}

QString DataHandler::current_data() {
	QString data_as_string = QString();
	for (double d : current_data_) {
		data_as_string += "<b>";
		data_as_string += QString::number(d);
		data_as_string += "</b>\t";
	}
	return data_as_string;
}

*/

int DataHandler::read_file()
{
	// Should only be done once?
//	qDebug() << "Reading file.";


	auto input_file_ = new QFile(settings_->input_filename());


	if (!input_file_->open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Could not open file for reading.\n";
		return 1;
	}


	while (!input_file_->atEnd()) {
		file_content_.append(input_file_->readLine());
	}

//	qDebug() << file_content_.last();
	delete input_file_;
	return 0;
}

void DataHandler::print_all() {
	for (auto e : datas_) 
		e.print_content();
}