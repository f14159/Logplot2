#pragma once
/*
Connects to the DataHandler as well as to the MainWindow and 
the SettingsForm uis, and handles events and connections between them.
Possible TODO: generalize constructor to be variadic (for generalization).
*/
#include <QTimer>
#include "datahandler.h"
#include "mainwindow.h"
#include "settingsform.h"
#include "settings.h"
//#include "ui_mainwindow.h"
//#include "ui_settingsform.h"

class EventHandler : public QObject
{
public:
//	EventHandler(DataHandler&, Time&, Settings&, MainWindow&, SettingsForm&);
	EventHandler(DataHandler&, Settings&, MainWindow&, SettingsForm&);
	~EventHandler() {}

	void start_timer();
	void stop_timer();

	void init_gui();
	void make_default_configs();

private:
// Constructor members
	DataHandler *dh_;
//	Time *t_;
	Settings *settings_;
	MainWindow *mw_;
	SettingsForm *sf_;

// ui classes (for connections)
	Ui::MainWindowClass ui_main;
	Ui::SettingsForm ui_settingsform;

// Other members
	QTimer *timer_;

// Functions
	void add_graph(Ui::MainWindowClass&);
	void add_timer();
};

