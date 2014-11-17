#include "samplewindow.h"
#include "ui_samplewindow.h"

SampleWindow::SampleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SampleWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startSpritz()));
}

void SampleWindow::startSpritz()
{
    if (ui->pushButton->isChecked()) {
        spritz = new OpenQpritz(ui->plainTextEdit->toPlainText(), 200);
        spritz->start(3);

        connect(spritz, SIGNAL(outputSpritzWord(QString)),
                this, SLOT(showSpritzWord(QString)));
    } else {
        delete spritz;
    }
}

void SampleWindow::showSpritzWord(QString wordToShow)
{
    ui->label->setText(wordToShow);
}

SampleWindow::~SampleWindow()
{
    delete ui;
}
