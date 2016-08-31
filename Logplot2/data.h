#pragma once

#include <QString>
#include <QVector>
#include <QDebug>

#include "settings.h"


template <class T>

/*
* Fixed size queue, containing the last n elements
* inserted.
*
*/
class FixedQueue {
	// Fixed size queue
public:
	FixedQueue(int s) { max_size_ = s; }
	~FixedQueue() {};

	QVector<T> content() { return content_; }

	void add(T e) {
		if (content_.length() < max_size_)
			content_.append(e);
		else {
			content_.pop_front();
			content_.append(e);
		}
	}

private:
	int max_size_;
	QVector<T> content_;
};


class Time {
	// !! TODO: datetime
public:
	Time(Settings &s) { settings_ = &s; ticks_ = 0; }
	~Time() {};
	void tick();
	QVector<double> t_count() { return t_count_; }
	QVector<double> t_ms() { return t_ms_; }

private:
	Settings *settings_;

	int ticks_;
	QVector<double> t_count_;
	QVector<double> t_ms_;
};


class Data {
public:
	Data() {};
	Data(Settings &s, int field);
	~Data() { }//delete time_; delete values_;
//}


	void print_content() {
		qDebug() << "Field: " << field_;
		qDebug() << "values: ";
		for (auto v : *values_)
			qDebug() << v << " ";

		qDebug() << "\n";

		qDebug() << "times: ";
		for (auto t : time_->t_ms())
			qDebug() << t;

		qDebug() << "\n------------------------\n";

	}
	void update(QString last_line);
	QVector<double> values() { return *values_; }
	QVector<double> times() { return time_->t_count(); }

	// last n values; set in settings
	QVector<double> values_limited(int);
	QVector<double> times_limited(int);

private:
	QString last_line_;
	int field_; // of the CSV string

	QVector<double> *values_;
	Time *time_;

	Settings *settings_;

	// Functions
	template <typename T>
	QVector<T> limited_vector(QVector<T> &full_vector, int size) {
		QVector<T> vec;

		if (size < full_vector.length()) {
			for (int i = (full_vector.length() - size); i < full_vector.length(); ++i) {
				vec.push_back(full_vector[i]);
			}
		}
		else {
			vec = full_vector;
		}
		return vec;
	}
};


