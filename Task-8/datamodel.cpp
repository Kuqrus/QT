#include "datamodel.h"

DataModel::DataModel(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();

    query = new QSqlQuery();

    QueryModel = new QSqlQueryModel();
    TableView = new QTableView();

    GenreSelect[requestAllFilms] = "";
    GenreSelect[requestComedy] = "WHERE c.name = 'Comedy'";
    GenreSelect[requestHorrors] = "WHERE c.name = 'Horror'";

}

DataModel::~DataModel()
{
    delete dataBase;
}

void DataModel::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}
void DataModel::DisconnectFromDataBase(QString nameDb)
{
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}
QSqlError DataModel::GetLastError()
{
    return dataBase->lastError();
}

void DataModel::ConnectToModel(QVector<QString> dataForConnect)
{
//    dataBase->setHostName("981757-ca08998.tmweb.ru");
//    dataBase->setDatabaseName("netology_cpp");
//    dataBase->setUserName("netology_usr_cpp");
//    dataBase->setPassword("CppNeto3");
//    dataBase->setPort(5432);

    dataBase->setHostName(dataForConnect[hostName]);
    dataBase->setDatabaseName(dataForConnect[dbName]);
    dataBase->setUserName(dataForConnect[login]);
    dataBase->setPassword(dataForConnect[pass]);
    dataBase->setPort(dataForConnect[port].toInt());

    bool status;
    status = dataBase->open();

    TableModel = new QSqlTableModel(this, *dataBase);

    emit sig_SendStatusConnection(status);
}

void DataModel::RequestToModel(QString request, requestType requestType)
{
    request += GenreSelect[requestType];
    *query = QSqlQuery(*dataBase);
    QSqlError error;
    if(!query->exec(request)){
        error = query->lastError();
    }

    if(requestType == requestAllFilms){
        TableModel->setTable("film");
        TableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
        TableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Описание"));
        TableModel->select();
    }
    else{
        QueryModel->setQuery(*query);
        QueryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));
        QueryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Описание"));
    }

    emit sig_SendStatusRequest(error);
}

void DataModel::ReadFromModel(int requestType)
{
    if(requestType == requestAllFilms){
        TableView->setModel(TableModel);
    }
    else{
        TableView->setModel(QueryModel);

    }
    emit sig_SendDataFromModel(TableView);
}



