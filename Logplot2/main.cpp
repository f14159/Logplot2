#include "mainwindow.h"
#include "settingsform.h"
#include "datahandler.h"
#include "eventhandler.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Model
	Settings settings(QString("C:/users/love/Desktop/mate_out.csv"), 1000);
	DataHandler dh(settings);
	Time t(settings);

	// View
	MainWindow mw;
	SettingsForm sf(&mw);

	// Controller
	EventHandler ev(dh, t, settings, mw, sf);
	ev.make_default_connections();
	ev.make_default_configs();

	mw.show();
	return a.exec();
}
