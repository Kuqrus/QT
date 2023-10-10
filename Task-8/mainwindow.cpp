#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtConcurrent/qtconcurrentrun.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Исходное состояние виджетов
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);    

    typeR["Все"] = requestAllFilms;
    typeR["Комедия"] = requestComedy;
    typeR["Ужасы"] = requestHorrors;

    /*
     * Выделим память под необходимые объекты. Все они наследники
     * QObject, поэтому воспользуемся иерархией.
    */
    dataDb = new DbData(this);
    dataModel = new DataModel(this);
    msg = new QMessageBox(this);    

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    //Добавим БД используя стандартный драйвер PSQL и зададим имя.
    dataModel->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    /*
     * Устанавливаем данные для подключениея к БД.
     * Поскольку метод небольшой используем лямбда-функцию.
     */
    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });

    //Сигнал для подключения к БД
    connect(dataModel, &DataModel::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToModel);

    //Сигнал запроса модели БД
    connect(dataModel, &DataModel::sig_SendStatusRequest, this, &MainWindow::ReceiveStatusRequestToModel);

    //Соединяем сигнал, который передает ответ от БД с QTableView, который отображает ответ в ПИ
    connect(dataModel, &DataModel::sig_SendDataFromModel, this, &MainWindow::ScreenDataFromModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered()
{
    dataDb->show();
}

/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */
void MainWindow::on_act_connect_triggered()
{
    if(ui->lb_statusConnect->text() == "Отключено") {

       ui->lb_statusConnect->setText("Подключение");
       ui->lb_statusConnect->setStyleSheet("color : black");

       auto connect = [&]{dataModel->ConnectToModel(dataForConnect);};
       QtConcurrent::run(connect);
    }
    else {
        dataModel->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
    }

}

/*!
 * \brief Обработчик кнопки "Очистить"
 */
void MainWindow::on_pb_clear_clicked()
{
    ui->tb_result->setModel(0);
    ui->pb_clear->setEnabled(false);
}

/*!
 * \brief Обработчик кнопки "Получить"
 */
void MainWindow::on_pb_request_clicked()
{
    auto get = [&]{
        dataModel->RequestToModel(request, typeR[ui->cb_category->currentText()]);
    };
    QtConcurrent::run(get);
}

/*!
 * \brief Слот переносит табилцу в QTableView
 * \param view
 */
void MainWindow::ScreenDataFromModel(QTableView *view)
{
    ui->tb_result->setModel(view->model());

    if(ui->cb_category->currentText() == typeR.key(requestAllFilms)){
        for(int i = 0; i < ui->tb_result->model()->columnCount(); i++){
            if(i == 1 || i == 2){
                continue;
            }
            ui->tb_result->setColumnHidden(i, true);
        }
    }
    else{
        for(int i = 0; i < ui->tb_result->model()->columnCount(); i++){
            ui->tb_result->setColumnHidden(i, false);
        }
    }

    ui->pb_clear->setEnabled(true);
}

/*!
 * \brief Метод изменяет стотояние формы в зависимости от статуса подключения к БД
 * \param status
 */
void MainWindow::ReceiveStatusConnectionToModel(bool status)
{
    if(status){
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
    }
    else{
        dataModel->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataModel->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
    }
}

void MainWindow::ReceiveStatusRequestToModel(QSqlError err)
{
    if(err.type() != QSqlError::NoError){
        msg->setText(err.text());
        msg->exec();
    }
    else{
        dataModel->ReadFromModel(typeR[ui->cb_category->currentText()]);
    }

}
