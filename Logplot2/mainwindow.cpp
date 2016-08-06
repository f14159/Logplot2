#include <QDialog>
#include <QList>

#include "mainwindow.h"
#include "settingsform.h"
#include "eventhandler.h"

#include "ui_mainwindow.h"
#include "ui_settingsform.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
//	SettingsForm *sf = new SettingsForm(this);

//EventHandler eh()
	ui_main.setupUi(this);
	ui_main.textBrowser->setHtml("");


//	connect(ui_main.button_settings, &QPushButton::clicked, sf, &QDialog::exec);

}

MainWindow::~MainWindow()
{

}
