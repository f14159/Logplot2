#include <QStringList>
#include <QVector>
#include "datahandler.h"
#include <QDebug>


DataHandler::DataHandler(Settings& settings)
{
	settings_ = &settings;
}


DataHandler::~DataHandler()
{
}

void DataHandler::update_content()
{
	read_file();
	current_line_ = file_content_[file_content_.size() - 1];
	// !! Assume double. This needs some checks.
// !! Format of input should be in settings.
	extract_data();

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

void DataHandler::read_file()
{
	// Should only be done once?
	input_file_ = new QFile(settings_->input_filename());

	if (!input_file_->open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	while (!input_file_->atEnd()) {
		file_content_.append(input_file_->readLine());
	}
}

void Time::tick()
{
	++ticks_;
	t_count_[ticks_] = ticks_;
	t_ms_[ticks_] = ticks_* settings_->timer_interval();
}
