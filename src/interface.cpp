#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QtDebug>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent) {

    setWindowTitle("Многочлен на комплексных числах");
    setFixedSize(400, 300);

    // Создаем пустой полином
    polynom = new TPolynom();

    // Создаём метку и поле вывода
    outputLabel = new QLabel("Результат:", this);
    outputField = new QLineEdit(this); // Поле вывода в одну строку
    outputField->setReadOnly(true); // Делаем поле вывода только для чтения
    outputField->setPlaceholderText("Результат будет здесь..."); // Подсказка для пользователя
    outputField->setMaximumWidth(350); // Ограничиваем ширину поля вывода

    dynamicInput = new QLineEdit(this); // Поле для динамического ввода
    dynamicInput->setPlaceholderText("Введите данные..."); // Подсказка для пользователя

    buttons[0] = new QPushButton("Вывод канонического вида полинома", this);
    buttons[1] = new QPushButton("Вывод классического вида полинома", this);
    buttons[2] = new QPushButton("Изменение кол-ва корней", this);
    buttons[3] = new QPushButton("Изменить a_n и корни", this);
    buttons[4] = new QPushButton("Вычислить значение в точке x", this);
    buttons[5] = new QPushButton("Задать новый полином", this);
    buttons[6] = new QPushButton("Выход", this); // Кнопка "Выход"

    QPushButton *inputButton = new QPushButton("Ввод", this); // Кнопка ввода
    QPushButton *clearButton = new QPushButton("Очистить", this); // Кнопка для очистки поля вывода


    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(outputLabel);

    // Создаем горизонтальный макет для метки и поля вывода
    QHBoxLayout *outputLayout = new QHBoxLayout();

    outputField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Растягиваем поле по ширине
    outputLayout->addWidget(outputField); // Добавляем поле вывода
    outputLayout->addWidget(clearButton); // Добавляем кнопку "Очистить"
    layout->addLayout(outputLayout); // Добавляем горизонтальный макет в основной макет

    layout->addWidget(new QLabel("Поле ввода:"));

    // Создаем горизонтальный макет для поля ввода и кнопки "Ввод"
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(dynamicInput); // Добавляем поле ввода
    inputLayout->addWidget(inputButton); // Добавляем кнопку "Ввод"

    layout->addLayout(inputLayout); // Добавляем горизонтальный макет в основной макет

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
    connect(inputButton, &QPushButton::clicked, this, &TInterface::handleInput);
    connect(clearButton, &QPushButton::clicked, this, &TInterface::clearOutput); // Подключаем кнопку "Очистить"
}

TInterface::~TInterface() {
    delete outputLabel;
    delete outputField;
    delete dynamicInput;
    // delete[] buttons;
    for (int i = 0; i < buttonsCount; i++) {
        delete buttons[i];
    }
    delete polynom;
}

void TInterface::clearOutput() {
   outputField->clear(); // Очищаем поле вывода при нажатии на кнопку "Очистить"
}


void TInterface::showCanonicalForm() {

    // Реализация вывода канонического вида полинома
    QString buttonText = "Вывели какнонический вид типа";
    outputField->setText(buttonText); //
}

void TInterface::showClassicalForm() {

    // Реализация вывода классического вида полинома
    QString buttonText = "Вывели классический вид типа";
    outputField->setText(buttonText); //
}

void TInterface::changeRootsCount() {
    // Реализация изменения количества корней
    QString buttonText = "Вывели новый полином idk";
    outputField->setText(buttonText);
}

void TInterface::newANAndRoots() {
    // Реализация нового a_n и корни
    QString buttonText = "Вывели новый полином idk";
    outputField->setText(buttonText);
}

void TInterface::calculateValueAtX() {
    // Реализация вычисления значения в точке x
    outputField->setText("Вывели p(x) = value");
}

void TInterface::setNewPolynomial() {
    // Реализация задания нового полинома вводом a_n и корней
    QString buttonText = "Вывели новый полиномус";
    outputField->setText(buttonText);
}

void TInterface::exitApplication() {
    QApplication::quit();
}

// Новый слот для обработки ввода данных из поля ввода
void TInterface::handleInput() {
    QString inputText = dynamicInput->text();

    if (!inputText.isEmpty()) {
        outputField->setText("Введено: " + inputText);
        dynamicInput->clear(); // Очищаем поле после ввода (по желанию)

        qDebug() << "Введенные данные:" << inputText;

        // Здесь можно добавить дополнительную логику обработки введённых данных.

    } else {
        outputField->setText("Поле ввода пустое!");
    }
}

