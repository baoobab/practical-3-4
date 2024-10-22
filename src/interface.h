#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "string"
#include "number.h"

using namespace std;


class TInterface : public QWidget{
    Q_OBJECT

    QLabel *name_numerator, *name_denumerator, *output;
    QLineEdit *numerator, *denumerator;

    QPushButton *submit_btn, *add_btn;


public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
    number getNumber();
public slots:
    void submit();
    void add();
};
#endif // INTERFACE_H
