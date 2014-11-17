#ifndef SAMPLEWINDOW_H
#define SAMPLEWINDOW_H

#include <QMainWindow>
#include "openqpritz.h"

namespace Ui {
class SampleWindow;
}

class SampleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SampleWindow(QWidget *parent = 0);
    ~SampleWindow();

    OpenQpritz *spritz;

private:
    Ui::SampleWindow *ui;

public slots:
    void startSpritz();
    void showSpritzWord(QString wordToShow);
};

#endif // SAMPLEWINDOW_H
