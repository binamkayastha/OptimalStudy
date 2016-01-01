#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>
#include <QDebug>


bool shortcut; //Shortcuts on and off toggle.
bool c, e, a;
int inc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    shortcut = false;
    c = false;
    e = false;
    a = false;
    inc = 2;

    ui->setupUi(this);

    QFile mFile("results.txt");

    if(!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed opening file to readfirst";
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    mFile.close();

    QRegExp rxc("[c]: [0-9]+");
    QRegExp rxe("e: [0-9]+");
    QRegExp rxa("a: [0-9]+");
    rxc.indexIn(mText);
    rxe.indexIn(mText);
    rxa.indexIn(mText);

    QString valc = rxc.cap(0);
    QString vale = rxe.cap(0);
    QString vala = rxa.cap(0);
    QRegExp num("[0-9]+");
    num.indexIn(valc);
    QString foo = num.cap(0);
    qDebug() << foo;
    ui->progressBar->setValue(foo.toInt());

    num.indexIn(vale);
    foo = num.cap(0);
    qDebug() << foo;
    ui->progressBar_2->setValue(foo.toInt());

    num.indexIn(vala);
    foo = num.cap(0);
    qDebug() << foo;
    ui->progressBar_3->setValue(foo.toInt());


    ui->plainTextEdit_4->setPlainText(QString::number(ui->progressBar->value()/2) + " " + QString::number(ui->progressBar->value()/30) + "%");
    ui->plainTextEdit_5->setPlainText(QString::number(ui->progressBar_2->value()/2) + " " + QString::number(ui->progressBar_2->value()/30) + "%");
    ui->plainTextEdit_6->setPlainText(QString::number(ui->progressBar_3->value()/2) + " " + QString::number(ui->progressBar_3->value()/30) + "%");
}



void Write(QString Filename, Ui::MainWindow *ui)
{
    QFile mFile(Filename);

    if(!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Failed opening file to write";
        return;
    }

    QTextStream out(&mFile);
    out << "c: " << ui->progressBar->value() << '\n' << "e: " << ui->progressBar_2->value() << '\n' << "a: " << ui->progressBar_3->value() << '\n';
    mFile.flush();
    mFile.close();
}

void Read(QString Filename) {
    QFile mFile(Filename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed opening file to read";
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() << mText;

    mFile.close();
}

//void incrementEvent(QProgressBar *progBar, QKeyEvent *event) {
//    if(event->key() == Qt::Key_J) {
//        progBar->setValue(progBar->value() + 1);
//        event->accept();
//    }

//    if(event->key() == Qt::Key_K) {
//        progbar->setValue(progBar->value() - 1);
//        event->accept();
//    }
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (shortcut) {
        if (c) {
            if(event->key() == Qt::Key_J) {
                ui->progressBar->setValue(ui->progressBar->value() + inc);
                event->accept();
            }

            if(event->key() == Qt::Key_K) {
                ui->progressBar->setValue(ui->progressBar->value() - inc);
                event->accept();
            }
        }
        if (e) {
            if(event->key() == Qt::Key_J) {
                ui->progressBar_2->setValue(ui->progressBar_2->value() + inc);
                event->accept();
            }

            if(event->key() == Qt::Key_K) {
                ui->progressBar_2->setValue(ui->progressBar_2->value() - inc);
                event->accept();
            }
        }
        if (a) {
            //incrementEvent(ui->progressBar_3, event);

            if(event->key() == Qt::Key_J) {
                ui->progressBar_3->setValue(ui->progressBar_3->value() + inc);
                event->accept();
            }

            if(event->key() == Qt::Key_K) {
                ui->progressBar_3->setValue(ui->progressBar_3->value() - inc);
                event->accept();
            }
        }

        if(event->key() == Qt::Key_C) {
            c = !c;
        }
        if(event->key() == Qt::Key_E) {
            e = !e;
        }
        if(event->key() == Qt::Key_A) {
            a = !a;
        }

    }
    else {
        c = false;
        e = false;
        a = false;
    }

    if(event->key() == Qt::Key_S) {
        shortcut = !shortcut;
    }

    if(event->key() == Qt::Key_H) {
        if(inc == 1) {
            inc = 2;
        } else {
            inc = 1;
        }
    }


    ui->plainTextEdit_4->setPlainText(QString::number(double(ui->progressBar->value())/2) + " " + QString::number(double(ui->progressBar->value())/30) + "%");
    ui->plainTextEdit_5->setPlainText(QString::number(double(ui->progressBar_2->value())/2) + " " + QString::number(double(ui->progressBar_2->value())/30) + "%");
    ui->plainTextEdit_6->setPlainText(QString::number(double(ui->progressBar_3->value())/2) + " " + QString::number(double(ui->progressBar_3->value())/30) + "%");


    QString mFilename = "results.txt";

    Write(mFilename, ui);
    //Read(mFilename);
}

MainWindow::~MainWindow()
{
    delete ui;
}
