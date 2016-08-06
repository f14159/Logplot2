#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>
#include "ui_settingsform.h"

class SettingsForm : public QDialog
{
	Q_OBJECT

public:
	SettingsForm(QWidget * parent = 0);
	~SettingsForm();

private:
	Ui::SettingsForm ui_settingsform;
};

#endif // SETTINGSFORM_H

