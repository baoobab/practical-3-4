#include "interface.h"
#include "string"

using namespace std;

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №4");
    setFixedSize(400, 350);

    name_numerator = new QLabel("Числитель", this);
    name_numerator->setGeometry(50, 20, 70, 25); // параметры - (X верх.лев.угла px, Y верх.лев.угла px, ширина px, высота px)

    numerator = new QLineEdit("1", this);
    numerator->setGeometry(130, 20, 50, 25);

    name_denumerator = new QLabel("Знаменатель", this);
    name_denumerator->setGeometry(50, 50, 70 ,25);

    denumerator = new QLineEdit("0", this);
    denumerator->setGeometry(130, 50, 50, 25);

    output = new QLabel("тут будет вывод", this);
    output->setGeometry(50, 150, 100, 25);

    submit_btn = new QPushButton("посчитать", this);
    submit_btn->setGeometry(190, 150, 70, 25);
    /* параметры - (указатель на источник сигнала, отслеживаемый сигнал,
     * указатель на приёмник (наше интерфейсное окно т.е. - this), слот который принимает)
    */

    add_btn = new QPushButton("добавить", this);
    add_btn->setGeometry(50, 200, 70, 25);

    connect(submit_btn, SIGNAL(pressed()), this, SLOT(submit()));
    connect(add_btn, SIGNAL(pressed()), this, SLOT(add()));
}

TInterface::~TInterface() {
    delete name_numerator;
    delete name_denumerator;
    delete numerator;
    delete denumerator;

    delete submit_btn;
}

void TInterface::submit() {
    QString numeratorValue = numerator->text();
    QString denumeratorValue = denumerator->text();

    // Преобразование строк в целые числа
    bool numOk, denumOk;
    int num = numeratorValue.toInt(&numOk);
    int denum = denumeratorValue.toInt(&denumOk);

    // Проверка успешности преобразования
    if (!numOk || !denumOk) {
        output->setText("Ошибка!");
        return;
    }

    // Форматирование результата
    QString result = QString::number(num) + " " + QString::number(denum);

    // Установка текста в выходной элемент
    output->setText(result);
}


void TInterface::add() {
    hz 4e tut
}
