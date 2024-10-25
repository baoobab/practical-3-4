#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QtDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "number.h"

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

    QPushButton *inputButton = new QPushButton("Подтвердить", this); // upd: Теперь это кнопка подтверждения действия (и ввода в том числе)
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


    // Добавляем переменную для хранения текущего действия
    currentAction = EAction::None;

    for (int i = 0; i < 7; ++i) {
        layout->addWidget(buttons[i]); // Добавляем кнопки
        connect(buttons[i], &QPushButton::clicked, this, [this, i]() {
            QString buttonText = buttons[i]->text(); // Получаем текст кнопки
            dynamicInput->setPlaceholderText(buttonText); // Устанавливаем текст подсказки

            switch (i) { // Индекс для обработки нажатий
            case 0: currentAction = EAction::ShowCanonicalForm; break;
            case 1: currentAction = EAction::ShowClassicalForm; break;
            case 2: currentAction = EAction::ChangeRootsCount; break;
            case 3: currentAction = EAction::NewANAndRoots; break;
            case 4: currentAction = EAction::CalculateValueAtX; break;
            case 5: currentAction = EAction::SetNewPolynomial; break;
            case 6: currentAction = EAction::ExitApplication; break;
            }
        });
    }

    connect(inputButton, &QPushButton::clicked, this, &TInterface::handleInputAndPerformAction);
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
    QString buttonText = "Вывели какнонический вид типа";
    outputField->setText(buttonText);

    currentAction = EAction::None; // Сбрасываем текущее действие
}

void TInterface::showClassicalForm() {
    QString outputText;

    polynom->setPrintMode(EPrintMode::EPrintModeClassic);
    outputText << *polynom;

    outputField->setText(outputText);

    currentAction = EAction::None; // Сбрасываем текущее действие
}

void TInterface::changeRootsCount() {
    // Реализация изменения количества корней
    QString buttonText = "Вывели новый полином idk";
    outputField->setText(buttonText);

    currentAction = EAction::None; // Сбрасываем текущее действие
}

void TInterface::newANAndRoots() {
    // Реализация нового a_n и корни
    QString buttonText = "Вывели новый полином idk";
    outputField->setText(buttonText);

    currentAction = EAction::None; // Сбрасываем текущее действие
}

void TInterface::calculateValueAtX() {
    // Реализация вычисления значения в точке x
    outputField->setText("Вывели p(x) = value");

    currentAction = EAction::None; // Сбрасываем текущее действие
}

void TInterface::exitApplication() {
    QApplication::quit();
}

// Новый слот для обработки ввода данных из поля ввода
QString TInterface::handleInput() {
    QString inputText = dynamicInput->text();

    if (!inputText.isEmpty()) {
        // outputField->setText("Введено: " + inputText);
        dynamicInput->clear(); // Очищаем поле после ввода (по желанию)
        qDebug() << "Введенные данные:" << inputText;

        return inputText;
    } else {
        outputField->setText("Поле ввода пустое!");
        return "";
    }
}

// Обновлённый метод setNewPolynomial для принятия ввода от пользователя
void TInterface::setNewPolynomial(QString& inputText) {

    if (inputText.length() > 0) {
        number numInput; // Введённые данные в числовом представлении
        QString outputText; // Результирующая строка
        inputText >> numInput;

        polynom->flushMemory();
        polynom->setCanonicCoef(numInput);

        outputText << *polynom;
        outputField->setText(outputText);

        dynamicInput->setPlaceholderText("Введите корень");
        currentAction = EAction::SetNewPolynomialRoot; // Сбрасываем текущее действие
    } else {
        outputField->setText("Поле ввода пустое!");
    }
}

// Добавляем новое действие для ввода корня
void TInterface::handleInputAndPerformActionForRoot(QString& inputText) {

    if (inputText.length() > 0) {
        number numInput;
        QString outputText;

        inputText >> numInput;

        polynom->addRoot(numInput);
        polynom->calcCoefFromRoots();

        outputText << *polynom;
        outputField->setText(outputText);
        currentAction = EAction::SetNewPolynomialRoot; // Сбрасываем текущее действие
    } else {
        outputField->setText("Поле ввода пустое!");
    }

    // currentAction = EAction::None; // Не сбрасываем, чтобы корни можно было добавлять сколько угодно
}

// Новый слот для обработки ввода данных и выполнения действия
void TInterface::handleInputAndPerformAction() {
    QString inputText = handleInput();

    switch (currentAction) {
    case EAction::ShowCanonicalForm:
        showCanonicalForm();
        break;
    case EAction::ShowClassicalForm:
        showClassicalForm();
        break;
    case EAction::ChangeRootsCount:
        changeRootsCount();
        break;
    case EAction::NewANAndRoots:
        newANAndRoots();
        break;
    case EAction::CalculateValueAtX:
        calculateValueAtX();
        break;
    case EAction::SetNewPolynomial:
        setNewPolynomial(inputText);
        break;
    case EAction::SetNewPolynomialRoot:
        handleInputAndPerformActionForRoot(inputText);
        break;
    case EAction::ExitApplication:
        exitApplication();
        break;
    default:
        break;
    }

    // currentAction = EAction::None; // Сбрасываем в каждом методе, чтобы можно было строить цепочки событий
}
