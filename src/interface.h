#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <vector>
#include <string>
#include <QTextEdit>
#include "polynom.h"

class TInterface : public QWidget {
    Q_OBJECT

    static const int buttonsCount = 7; // Общее количество кнопок в интерфейсе

    QLabel *outputLabel; // Метка для результата
    QLineEdit *outputField; // Поле вывода с горизонтальной прокруткой
    QLineEdit *dynamicInput; // Поле для ввода, изменяющееся в зависимости от нажатой кнопки
    QPushButton *buttons[buttonsCount]; // Массив кнопок

    TPolynom *polynom; // Полином для работы с интерфесом
public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void showCanonicalForm(); // Вывод канонического вида полинома
    void showClassicalForm(); // Вывод классического вида полинома
    void changeRootsCount(); // Изменение кол-ва корней
    void newANAndRoots(); // Новый a_n и корни
    void calculateValueAtX(); // Вычислить значение в точке x
    void setNewPolynomial(); // Задать новый полином вводом a_n и корней
    void exitApplication(); // Выход из приложения
    void handleInput();
    void clearOutput();
};

#endif // INTERFACE_H
