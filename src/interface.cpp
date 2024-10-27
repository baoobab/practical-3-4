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
    : QWidget(parent)
{
    setWindowTitle("Многочлен на комплексных числах");
    setMaximumSize(600, 300);

    // Создаем пустой полином
    polynom = new TPolynom();

    // Создаём метку и поле вывода
    outputField = new QLineEdit(this); // Поле вывода в одну строку
    outputField->setReadOnly(true); // Делаем поле вывода только для чтения
    outputField->setPlaceholderText("Результат любого пункта будет здесь..."); // Подсказка для пользователя
    outputField->setMaximumWidth(350); // Ограничиваем ширину поля вывода

    // Кнопка "Очистить"
    QPushButton *clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked, this, &TInterface::clearOutput);

    // Создаем горизонтальный макет для метки и поля вывода
    QHBoxLayout *outputLayout = new QHBoxLayout();
    outputLayout->addWidget(outputField); // Добавляем поле вывода
    outputLayout->addWidget(clearButton); // Добавляем кнопку "Очистить"

    // Создаем вертикальный макет для всего интерфейса
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(outputLayout);

    // Пункт 1: Вывод канонического вида полинома
    QLabel *canonicalFormLabel = new QLabel("Вывод канонического вида полинома", this);
    QPushButton *canonicalFormButton = new QPushButton("Вывести", this);
    connect(canonicalFormButton, &QPushButton::clicked, this, &TInterface::showCanonicalForm);
    QHBoxLayout *canonicalFormLayout = new QHBoxLayout();
    canonicalFormLayout->addWidget(canonicalFormLabel);
    canonicalFormLayout->addWidget(canonicalFormButton);
    mainLayout->addLayout(canonicalFormLayout);

    // Пункт 2: Вывод классического вида полинома
    QLabel *classicalFormLabel = new QLabel("Вывод классического вида полинома", this);
    QPushButton *classicalFormButton = new QPushButton("Вывести", this);
    connect(classicalFormButton, &QPushButton::clicked, this, &TInterface::showClassicalForm);
    QHBoxLayout *classicalFormLayout = new QHBoxLayout();
    classicalFormLayout->addWidget(classicalFormLabel);
    classicalFormLayout->addWidget(classicalFormButton);
    mainLayout->addLayout(classicalFormLayout);

    // Пункт 3: Изменение количества корней
    QLabel *changeRootsCountLabel = new QLabel("Изменение количества корней", this);
    QLineEdit *changeRootsCountInput = new QLineEdit(this);
    QPushButton *changeRootsCountButton = new QPushButton("Изменить", this);
    connect(changeRootsCountButton, &QPushButton::clicked, this, [this, changeRootsCountInput]() {
        QString inputText = changeRootsCountInput->text();
        changeRootsCount(inputText);
    });
    QHBoxLayout *changeRootsCountLayout = new QHBoxLayout();
    changeRootsCountLayout->addWidget(changeRootsCountLabel);
    changeRootsCountLayout->addWidget(changeRootsCountInput);
    changeRootsCountLayout->addWidget(changeRootsCountButton);
    mainLayout->addLayout(changeRootsCountLayout);

    // Пункт 4: Изменить a_n и корни
    QLabel *newANAndRootsLabel = new QLabel("Изменить a_n и корни", this);
    QLineEdit *newANInput = new QLineEdit(this);
    newANInput->setPlaceholderText("a_n");
    newANInput->setMaximumWidth(60);
    QLineEdit *newRootsInput = new QLineEdit(this);
    QPushButton *newANAndRootsButton = new QPushButton("Изменить", this);
    connect(newANAndRootsButton, &QPushButton::clicked, this, [this, newANInput, newRootsInput]() {
        QString anText = newANInput->text();
        QString rootsText = newRootsInput->text();
        newANAndRoots(anText, rootsText);
    });
    QHBoxLayout *newANAndRootsLayout = new QHBoxLayout();
    newANAndRootsLayout->addWidget(newANAndRootsLabel);
    newANAndRootsLayout->addWidget(newANInput);
    newANAndRootsLayout->addWidget(newRootsInput);
    newANAndRootsLayout->addWidget(newANAndRootsButton);
    mainLayout->addLayout(newANAndRootsLayout);

    // Пункт 5: Вычислить значение в точке x
    QLabel *calculateValueAtXLabel = new QLabel("Вычислить значение в точке x", this);
    QLineEdit *calculateValueAtXInput = new QLineEdit(this);
    calculateValueAtXInput->setPlaceholderText("число X");
    QPushButton *calculateValueAtXButton = new QPushButton("Вычислить", this);
    connect(calculateValueAtXButton, &QPushButton::clicked, this, [this, calculateValueAtXInput]() {
        QString inputText = calculateValueAtXInput->text();
        calculateValueAtX(inputText);
    });
    QHBoxLayout *calculateValueAtXLayout = new QHBoxLayout();
    calculateValueAtXLayout->addWidget(calculateValueAtXLabel);
    calculateValueAtXLayout->addWidget(calculateValueAtXInput);
    calculateValueAtXLayout->addWidget(calculateValueAtXButton);
    mainLayout->addLayout(calculateValueAtXLayout);

    // Пункт 6: Задать новый полином
    QLabel *setNewPolynomialLabel = new QLabel("Задать новый полином", this);
    QLineEdit *setNewPolynomialANInput = new QLineEdit(this);
    setNewPolynomialANInput->setPlaceholderText("a_n");
    setNewPolynomialANInput->setMaximumWidth(60);
    QLineEdit *setNewPolynomialRootsInput = new QLineEdit(this);
    setNewPolynomialRootsInput->setPlaceholderText("корни (через пробел)");
    setNewPolynomialRootsInput->setMinimumWidth(150);
    QPushButton *setNewPolynomialButton = new QPushButton("Задать", this);

    // Создаем горизонтальный макет для метки и полей ввода
    QHBoxLayout *setNewPolynomialLayout = new QHBoxLayout();
    setNewPolynomialLayout->addWidget(setNewPolynomialLabel);
    setNewPolynomialLayout->addWidget(setNewPolynomialANInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialRootsInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialButton);
    mainLayout->addLayout(setNewPolynomialLayout);

    // Подключаем кнопку "Задать новый полином" к слоту
    connect(setNewPolynomialButton, &QPushButton::clicked, this, [this, setNewPolynomialANInput, setNewPolynomialRootsInput]() {
        QString anText = setNewPolynomialANInput->text();
        QString rootsText = setNewPolynomialRootsInput->text();
        setNewPolynomial(anText, rootsText);
    });

    // Добавляем кнопку "Выход"
    QPushButton *exitButton = new QPushButton("Выход", this);
    mainLayout->addWidget(exitButton);

    // Подключаем кнопку "Выход" к слоту
    connect(exitButton, &QPushButton::clicked, this, &TInterface::exitApplication);

    // Установка основного макета
    setLayout(mainLayout);
}

void TInterface::clearOutput() {
    outputField->clear(); // Очищаем поле вывода при нажатии на кнопку "Очистить"
}

void TInterface::exitApplication() {
    QApplication::quit();
}

TInterface::~TInterface()
{
    delete polynom;
    // TODO: мб делетнуть и все остальные указатели по Егорову
}

void TInterface::showCanonicalForm()
{
    QString outputText;

    polynom->setPrintMode(EPrintMode::EPrintModeCanonical);
    outputText << *polynom;

    outputField->setText(outputText);
}

void TInterface::showClassicalForm()
{
    QString outputText;

    polynom->setPrintMode(EPrintMode::EPrintModeClassic);
    outputText << *polynom;

    outputField->setText(outputText);
}

void TInterface::changeRootsCount(QString& inputText)
{
    // Реализация изменения количества корней
    // Для начала, просто выводим сообщение
    QMessageBox::information(this, "Изменение количества корней", "Не реализовано");
}

void TInterface::newANAndRoots(QString& anText, QString& rootsText)
{
    // Реализация изменения a_n и корней
    // Для начала, просто выводим сообщение
    QMessageBox::information(this, "Изменение a_n и корней", "Не реализовано");
}

void TInterface::calculateValueAtX(QString& inputText)
{
    QString outputText;
    number x;
    inputText >> x;
    number value = polynom->value(x);

    outputText += "P(";
    outputText << x;
    outputText += ") = ";
    outputText << value;

    outputField->setText(outputText);
}

void TInterface::setNewPolynomial(QString& anText, QString& rootsText)
{
    if (anText.length() > 0 && rootsText.length() > 0)
    {
        number numAN; // Введённые данные для a_n в числовом представлении
        QString outputText; // Результирующая строка

        anText >> numAN;

        polynom->flushMemory();
        polynom->setCanonicCoef(numAN);

        QStringList rootsList = rootsText.split(' '); // Разделяем строку на части по пробелу
        QString arr[2] = {};
        int tmp = 0;

        for (QString& rootText : rootsList)
        {
            if (!rootText.isEmpty())
            { // Проверяем, что часть не пустая
                arr[tmp++] = rootText;
            }

            if (tmp == 2)
            {
                QString concaetedNum;
                number tmpNum;
                concaetedNum = arr[0] + " " + arr[1];

                concaetedNum >> tmpNum;
                polynom->addRoot(tmpNum);
                polynom->calcCoefFromRoots();

                clearOutput();
                outputText.clear();
                outputText << *polynom;
                outputField->setText(outputText);

                tmp = 0;
            }

        }

    }
    else
    {
        outputField->setText("Поле ввода пустое!");
    }
}
