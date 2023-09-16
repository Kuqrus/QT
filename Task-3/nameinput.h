#ifndef NAMEINPUT_H
#define NAMEINPUT_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class NameInput;
}

class NameInput : public QDialog
{
    Q_OBJECT

public:
    explicit NameInput(QWidget *parent = nullptr);
    ~NameInput();

    void onEnterClicked();
private slots:
    void on_pb_enter_clicked();

private:
    Ui::NameInput *ui;

};

#endif // NAMEINPUT_H
