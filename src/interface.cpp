#include "interface.h"
#include "string"

using namespace std;

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №4");
    setFixedSize(400, 350);

    name_re = new QLabel("Комл. число", this);
    name_re->setGeometry(50, 20, 70, 25); // параметры - (X верх.лев.угла px, Y верх.лев.угла px, ширина px, высота px)

    a_re = new QLineEdit("", this);
    a_re->setGeometry(130, 20, 50, 25);

    name_im = new QLabel("+i", this);
    name_im->setGeometry(190, 20, 70 ,25);

    a_im = new QLineEdit("", this);
    a_im->setGeometry(210, 20, 50, 25);

    output = new QLabel("тут будет вывод", this);
    output->setGeometry(50, 150, 100, 25);

    submit_btn = new QPushButton("добавить", this);
    submit_btn->setGeometry(190, 150, 70, 25);
    /* параметры - (указатель на источник сигнала, отслеживаемый сигнал,
     * указатель на приёмник (наше интерфейсное окно т.е. - this), слот который принимает)
    */

    connect(submit_btn, SIGNAL(pressed()), this, SLOT(submit()));
}

TInterface::~TInterface() {
    delete name_re;
    delete name_im;
    delete a_re;
    delete a_im;

    delete submit_btn;
}

string TInterface::submit() {
    QString reValue = a_re->text();
    QString imValue = a_im->text();

    // Преобразование строк в целые числа
    bool reOk, imOk;
    double re = reValue.toDouble(&reOk);
    double im = imValue.toDouble(&imOk);

    // Проверка успешности преобразования
    if (!reOk || !imOk) {
        output->setText("Ошибка!");
        return "";
    }

    // Форматирование результата
    QString result = QString::number(re) + " " + QString::number(im);

    // Установка текста в выходной элемент
    if (im < 0) {
        output->setText(QString::number(re) + QString::number(im) + "i");
    } else {
        output->setText(QString::number(re) + "+" + QString::number(im) + "i");
    }

    return result.toStdString();
}
