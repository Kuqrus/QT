#include "nameinput.h"
#include "ui_mainwindow.h"
#include "ui_nameinput.h"
#include "mainwindow.h"

NameInput::NameInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameInput)
{
    ui->setupUi(this);

}

NameInput::~NameInput()
{
    delete ui;
}

void NameInput::onEnterClicked()
{
    QString host = ui->le_hostInput->text();
    int port = ui->sb_portInput->value();
    QString dbName = ui->le_dbInput->text();
    QString login = ui->le_logInput->text();


    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    if (mainWindow) {
        mainWindow->ui->le_currentHost->setText(host);
        mainWindow->ui->sb_currentPort->setValue(port);
        mainWindow->ui->le_currentDbName->setText(dbName);
        mainWindow->ui->le_currentLogin->setText(login);
    }
    close();
}

void NameInput::on_pb_enter_clicked()
{
    NameInput::onEnterClicked();
}

