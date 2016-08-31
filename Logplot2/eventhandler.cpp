#include "eventhandler.h"

//EventHandler::EventHandler(DataHandler &dh, Time &t, Settings &settings, MainWindow &mw, SettingsForm &sf)
EventHandler::EventHandler(DataHandler &dh, Settings &settings, MainWindow &mw, SettingsForm &sf)
{
	dh_ = &dh;
//	t_ = &t;
	settings_ = &settings;
	mw_ = &mw;
	sf_ = &sf;

	timer_ = new QTimer();
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



void EventHandler::init_gui()
{
	ui_main.setupUi(mw_);
	ui_settingsform.setupUi(sf_);

	// Settings button for bringing up the form
//	connect(ui_main.b_settings, &QPushButton::clicked, sf_, &QDialog::exec);
	add_graph(ui_main);

	connect(ui_main.b_settings, &QPushButton::clicked, this, [this] {
		QPushButton	*qp = new QPushButton;
		ui_main.t_data_toggles->insertRow(0);
		ui_main.t_data_toggles->insertColumn(0);
		ui_main.t_data_toggles->setCellWidget(0, 0, qp);
		ui_main.t_data_toggles->setCellWidget(0, 0, qp);
//		ui_main.t_data_toggles->insertRow
		qp->show();
	}
		);
	connect(ui_main.b_start_stop, &QPushButton::clicked, this, &EventHandler::start_timer);

	// Timer for updating content
	add_timer();
}


// Set size of plot and text output
void EventHandler::make_default_configs()
{
	QList<int> sizes{ 700, 200 };
	ui_main.splitter->setSizes(sizes);
}


void EventHandler::add_timer() {
	connect(timer_, &QTimer::timeout, this,
		[this] {
		// !!
		dh_->update_content();
		ui_main.textBrowser->setText(QString::number(dh_->datas()[0].values_limited(3)[1]));
		ui_main.w_plot->graph(0)->setData(dh_->datas()[0].times_limited(200), dh_->datas()[0].values_limited(200));
		ui_main.w_plot->graph(1)->setData(dh_->datas()[1].times_limited(200), dh_->datas()[1].values_limited(200));
		ui_main.w_plot->rescaleAxes();
		ui_main.w_plot->replot();
	}
	);
}


// Adds the graph to a widget
void EventHandler::add_graph(Ui::MainWindowClass& mc) {
	mc.w_plot->addGraph();
	mc.w_plot->addGraph();
	mc.w_plot->xAxis->setVisible(true);

	mc.w_plot->graph(0)->setPen(QPen(Qt::blue));
	mc.w_plot->graph(0)->setPen(QPen(Qt::red));

	mc.w_plot->setInteraction(QCP::iRangeDrag, true);
	mc.w_plot->setInteraction(QCP::iRangeZoom, true);
	mc.w_plot->setInteraction(QCP::iSelectPlottables, true);
}