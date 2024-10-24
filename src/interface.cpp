#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent) {

    setWindowTitle("Многочлен на комплексных числах");
    setFixedSize(400, 300);

    output = new QLabel("Результат:", this);

    dynamicInput = new QLineEdit(this); // Поле для динамического ввода
    dynamicInput->setPlaceholderText("Введите данные..."); // Подсказка для пользователя

    buttons[0] = new QPushButton("Вывод канонического вида полинома", this);
    buttons[1] = new QPushButton("Вывод классического вида полинома", this);
    buttons[2] = new QPushButton("Изменение кол-ва корней", this);
    buttons[3] = new QPushButton("Изменить a_n и корни", this);
    buttons[4] = new QPushButton("Вычислить значение в точке x", this);
    buttons[5] = new QPushButton("Задать новый полином", this);
    buttons[6] = new QPushButton("Выход", this); // Кнопка "Выход"

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(output);

    layout->addWidget(new QLabel("Поле ввода:"));
    layout->addWidget(dynamicInput); // Динамическое поле ввода

    for (int i = 0; i < 7; ++i) {
        layout->addWidget(buttons[i]); // Добавляем кнопки
        connect(buttons[i], &QPushButton::clicked, this, [this, i]() {
            QString buttonText = buttons[i]->text(); // Получаем текст кнопки
            dynamicInput->setPlaceholderText(buttonText); // Устанавливаем текст подсказки

            switch (i) { // Индекс для обработки нажатий
                case 0: showCanonicalForm(); break; // Вывод канонического вида полинома
                case 1: showClassicalForm(); break; // Вывод классического вида полинома
                case 2: changeRootsCount(); break; // Изменение кол-ва корней
                case 3: newANAndRoots(); break; // Новый a_n и корни
                case 4: calculateValueAtX(); break; // Вычислить значение в точке x
                case 5: setNewPolynomial(); break; // Задать новый полином
                case 6: exitApplication(); break; // Выход из программы
            }
        });
    }
}

TInterface::~TInterface() {
}

void TInterface::showCanonicalForm() {
    // Реализация вывода канонического вида полинома
}

void TInterface::showClassicalForm() {
    // Реализация вывода классического вида полинома
}

void TInterface::changeRootsCount() {
    // Реализация изменения количества корней
}

void TInterface::newANAndRoots() {
    // Реализация нового a_n и корни
}

void TInterface::calculateValueAtX() {
    // Реализация вычисления значения в точке x
}

void TInterface::setNewPolynomial() {
    // Реализация задания нового полинома вводом a_n и корней
}

void TInterface::exitApplication() {
    QApplication::quit();
}
