#include "data.h"

Data::Data(Settings &s, int field) {
	settings_ = &s;
	field_ = field;
	time_ = new Time(s);
	values_ = new QVector<double>;
}

void Data::update(QString last_line) {
	// !! TODO: please assert me.
	time_->tick();
	QString v = last_line.split(",")[field_];
	values_->append(v.toDouble());

}


QVector<double> Data::values_limited(int size) {
	return limited_vector<double>(*values_, size);
}

QVector<double> Data::times_limited(int size) {
	return limited_vector<double>(time_->t_count(), size);
}

/*
QVector<double> Data::values_limited(int size) {
	QVector<double> vec;

	if (values_.length < size) {
		for (int i = (values_.length - size); i < values_.length; ++i) {
			vec.push_back(values_[i]);
		}
	}
	else {
		vec = values_;
	}

	return vec;
}
*/



void Time::tick()
{
	t_count_.append(ticks_);
	t_ms_.append(ticks_* settings_->timer_interval());
	++ticks_;
//	t_count_[ticks_] = ticks_;
//	t_ms_[ticks_] = ticks_* settings_->timer_interval();

}
