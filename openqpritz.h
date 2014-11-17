#ifndef OPENQPRITZ_H
#define OPENQPRITZ_H

#include <QObject>
#include <QStringList>
#include <QTimer>

class OpenQpritz : public QObject
{
    Q_OBJECT
public:
    explicit OpenQpritz(const QString sentence, const int spritzWpmNumber = 200);
    explicit OpenQpritz(const QStringList wordList, const int spritzWpmNumber = 200);

    QTimer *m_timer;

    QString m_sentence;
    QStringList m_wordList;
    QString m_wordTemp;
    QString wordToShow;
    int m_spritzWpmNumber;

private:
    int spritzLoopNumber;
    int startupLoopNumber;

signals:
    void outputSpritzWord(QString wordToShow);
    void finishSpritz();

public slots:
    QStringList makeWordList(QString sentence);
    void start(int intervalNumber = 0);
    void startup();
    void pause();
    void stop();
    void spritz();
    QString processWordForSpritz(QString word);
    void setSpritzWpmNumber(const int newSpritzWpmNumber);
};

#endif // OPENQPRITZ_H
