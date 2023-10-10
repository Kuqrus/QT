#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

////Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

//Типы запросов
enum requestType{

    requestAllFilms = 1,
    requestComedy   = 2,
    requestHorrors  = 3

};

class DataModel : public QObject
{
    Q_OBJECT

public:
    explicit DataModel(QObject *parent = nullptr);
    ~DataModel();

    void AddDataBase(QString driver, QString nameDB = "");
    void ConnectToModel(QVector<QString> dataForConnect);
    void DisconnectFromDataBase(QString nameDb = "");
    QSqlError GetLastError(void);

    void RequestToModel(QString request, requestType requestType);
    void ReadFromModel(int requestType);

signals:
    void sig_SendStatusConnection(bool);
    void sig_SendStatusRequest(QSqlError error);
    void sig_SendDataFromModel(QTableView *view);

private:
    QSqlDatabase* dataBase;
    QSqlQuery *query;
    QHash<requestType, QString> GenreSelect;

    QSqlTableModel *TableModel;
    QSqlQueryModel *QueryModel;

    QTableView *TableView;

};

#endif // DATAMODEL_H
