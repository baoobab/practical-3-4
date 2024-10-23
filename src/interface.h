#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "string"

using namespace std;


class TInterface : public QWidget{
    Q_OBJECT

    QLabel *name_re, *name_im, *output;
    QLineEdit *a_re, *a_im;

    QPushButton *submit_btn, *add_btn;


public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
public slots:
    string submit(); // Возвращает ввдённое к.ч. в виде строки
};
#endif // INTERFACE_H
