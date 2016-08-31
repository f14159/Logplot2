#include "mainwindow.h"
#include "settingsform.h"
#include "data.h"
#include "datahandler.h"
#include "eventhandler.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Model
	Settings settings(QString("C:/users/love/Desktop/mate_out.csv"), 100);
	DataHandler dh(settings);

	// View
	MainWindow mw;
	SettingsForm sf(&mw);

	// Controller
	EventHandler ev(dh, settings, mw, sf);
	ev.init_gui();
	ev.make_default_configs();

	// Qt
	mw.show();
	return a.exec();

}
