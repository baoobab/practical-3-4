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
    void calculateValueAtX(QString& inputText); // Вычислить значение в точке x
    void setNewPolynomial(QString& anText, QString& rootsText); // Задать новый полином вводом a_n и корней
    void changeRootAndAN(QString& anText, QString& indexText); // Новый a_n и корни
    void exitApplication(); // Выход из приложения

private:
    TPolynom *polynom;
    QLineEdit *outputField;
    QPushButton *clearButton;
    QHBoxLayout *outputLayout;
    QVBoxLayout *mainLayout;

    QLabel *canonicalFormLabel;
    QPushButton *canonicalFormButton;
    QHBoxLayout *canonicalFormLayout;

    QLabel *classicalFormLabel;
    QPushButton *classicalFormButton;
    QHBoxLayout *classicalFormLayout;

    QLabel *changeRootsCountLabel;
    QLineEdit *changeRootsCountInput;
    QPushButton *changeRootsCountButton;
    QHBoxLayout *changeRootsCountLayout;

    QLabel *newANAndRootsLabel;
    QLineEdit *newANInput;
    QLineEdit *newRootIndexInput;
    QPushButton *newANAndRootsButton;
    QHBoxLayout *newANAndRootsLayout;

    QLabel *calculateValueAtXLabel;
    QLineEdit *calculateValueAtXInput;
    QPushButton *calculateValueAtXButton;
    QHBoxLayout *calculateValueAtXLayout;

    QLabel *setNewPolynomialLabel;
    QLineEdit *setNewPolynomialANInput;
    QLineEdit *setNewPolynomialRootsInput;
    QPushButton *setNewPolynomialButton;
    QHBoxLayout *setNewPolynomialLayout;

    QPushButton *exitButton;
};

#endif // INTERFACE_H
