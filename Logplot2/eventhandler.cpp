#include "eventhandler.h"


EventHandler::EventHandler(DataHandler &dh, Time &t, Settings &settings, MainWindow &mw, SettingsForm &sf)
{
	dh_ = &dh;
	t_ = &t;
	settings_ = &settings;
	mw_ = &mw;
	sf_ = &sf;

	timer_ = new QTimer();
}

EventHandler::~EventHandler()
{
}

void EventHandler::start_timer()
{
	timer_->start(settings_->timer_interval());
	disconnect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::start_timer);
	ui_main.b_start_stop->setText(tr("Stop"));
	connect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::stop_timer);
}

void EventHandler::stop_timer()
{
	timer_->stop();
	disconnect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::stop_timer);
	ui_main.b_start_stop->setText(tr("Start"));
	connect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::start_timer);
}

void EventHandler::make_default_connections()
{
	ui_main.setupUi(mw_);
	ui_settingsform.setupUi(sf_);

	// Settings button for bringing up the form
	connect(ui_main.b_settings, &QPushButton::clicked, sf_, &QDialog::exec);
	connect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::start_timer);

	// Timer
	connect(timer_, &QTimer::timeout, this,
		[this] {
		dh_->update_content();
		t_->tick();
		ui_main.textBrowser->append(dh_->current_line());
		ui_main.textBrowser->append(dh_->current_data());
//		ui_main.textBrowser->append(dh_->datta());
	}
	);


	ui_main.w_plot->addGraph();

	QVector<double> x{ 0,1,2,3,4,5,6,3,2,3,4,5,6 };
	QVector<double> y{ 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	ui_main.w_plot->graph(0)->setData(x,x);
	ui_main.w_plot->xAxis->setRange(-1, 10);
	ui_main.w_plot->yAxis->setRange(-1, 10);
	ui_main.w_plot->replot();

}

void EventHandler::make_default_configs()
{
	// Set size of plot and text output
	QList<int> sizes{ 700, 200 };
	ui_main.splitter->setSizes(sizes);
}


