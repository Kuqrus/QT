#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include "dbdata.h"
#include "datamodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_SendModel(QSqlTableModel *model);

public slots:
    void ReceiveStatusConnectionToModel(bool status);
    void ReceiveStatusRequestToModel(QSqlError err);
    void ScreenDataFromModel(QTableView *view);


private slots:
    void on_act_addData_triggered();
    void on_act_connect_triggered();

    void on_pb_request_clicked();
    void on_pb_clear_clicked();

private:
    QVector<QString> dataForConnect; //Данные для подключения к БД.

    Ui::MainWindow *ui;
    QMessageBox* msg;

    QHash<QString, requestType> typeR;

    DbData *dataDb;
    DataModel *dataModel;
    QSqlDatabase dataBase;

    QString request = "SELECT title, description FROM film f "
                      "JOIN film_category fc on f.film_id = fc.film_id "
                      "JOIN category c on c.category_id  = fc.category_id "
                      ;


};
#endif // MAINWINDOW_H
