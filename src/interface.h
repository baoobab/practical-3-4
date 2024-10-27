#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "polynom.h"

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void clearOutput();
    void showCanonicalForm(); // Вывод канонического вида полинома
    void showClassicalForm(); // Вывод классического вида полинома
    void changeRootsCount(QString& inputText); // Изменение кол-ва корней
    void newANAndRoots(QString& anText, QString& rootsText); // Новый a_n и корни
    void calculateValueAtX(QString& inputText); // Вычислить значение в точке x
    void setNewPolynomial(QString& anText, QString& rootsText); // Задать новый полином вводом a_n и корней
    void exitApplication(); // Выход из приложения

private:
    TPolynom* polynom;

    QLineEdit* outputField;

    QPushButton* clearButton;

    QPushButton* canonicalFormButton;
    QPushButton* classicalFormButton;

    QLineEdit* changeRootsCountInput;
    QPushButton* changeRootsCountButton;

    QLineEdit* newANInput;
    QLineEdit* newRootsInput;
    QPushButton* newANAndRootsButton;

    QLineEdit* calculateValueAtXInput;
    QPushButton* calculateValueAtXButton;

    QLineEdit* setNewPolynomialANInput;
    QLineEdit* setNewPolynomialRootsInput;
    QPushButton* setNewPolynomialButton;

    QPushButton* exitButton;
};

#endif // INTERFACE_H
