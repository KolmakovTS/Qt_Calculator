#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void MainWindow::on_pushButton1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void MainWindow::on_pushButton2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void MainWindow::on_pushButton3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void MainWindow::on_pushButton4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void MainWindow::on_pushButton5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void MainWindow::on_pushButton6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void MainWindow::on_pushButton7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void MainWindow::on_pushButton8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void MainWindow::on_pushButton9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void MainWindow::on_pushButtonSeparator_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_pushButtonModule_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + " % ");
}

void MainWindow::on_pushButtonSplit_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + " : ");
}

void MainWindow::on_pushButtonMultiply_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + " x ");
}

void MainWindow::on_pushButtonMinus_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + " - ");
}

void MainWindow::on_pushButtonPlus_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + " + ");
}

void MainWindow::on_pushButtonErase_clicked()
{
    ui->lineEdit->clear();
}


double MainWindow::operation(double a, double b, const QChar &op)
{
    switch(op.toLatin1())
    {
        case '+': return a + b;
        case '-': return a - b;
        case 'x': return a * b;
        case ':': return a / b;
        case '%': return std::fmod(a, b);
        default: return 0;
    }
}


void MainWindow::on_pushButtonEquals_clicked()
{
    QString expression = ui->lineEdit->text();
    QStringList parts = expression.split(" ");

    if(parts.size() < 3)
        return;

    // Операции с высоким приоритетом: умножение x, деление :, деление по модулю %
    for(int i = 1; i < parts.size() - 1; i += 2)
    {
        QChar op = parts[i][0];
        if (op == 'x' || op == ':' || op == '%')
        {
            double leftValue = parts[i - 1].toDouble();
            double rightValue = parts[i + 1].toDouble();
            double result = operation(leftValue, rightValue, op);

            parts[i - 1] = QString::number(result);
            parts.removeAt(i);
            parts.removeAt(i);
            i -= 2;
        }
    }

    // Операции с низким приоритетом: минус - и плюс +
    double result = parts[0].toDouble();
    for(int i = 1; i < parts.size(); i += 2)
    {
        QChar op = parts[i][0];
        double nextValue = parts[i + 1].toDouble();
        result = operation(result, nextValue, op);
    }

    ui->lineEdit->setText(expression + " = " + QString::number(result));
}
