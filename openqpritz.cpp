#include "openqpritz.h"

// コンストラクタ(sentenceの場合) / Constructor
OpenQpritz::OpenQpritz(const QString sentence, const int spritzWpmNumber)
{
    m_wordList = makeWordList(sentence);
    m_spritzWpmNumber = spritzWpmNumber;

    spritzLoopNumber = 0;
    m_timer = new QTimer();
}


// コンストラクタ(wordListの場合) / Constructor
OpenQpritz::OpenQpritz(const QStringList wordList, const int spritzWpmNumber)
{
    m_wordList = wordList;
    m_spritzWpmNumber = spritzWpmNumber;

    spritzLoopNumber = 0;
    m_timer = new QTimer();
}


// 文章を単語リストに加工 / make wordList from sentence
QStringList OpenQpritz::makeWordList(QString sentence)
{
    QStringList wordListTemp;

    // 無選択の場合はreturn / if nothing selected, return
    if (sentence == "" | sentence == " ") {
        wordListTemp.clear();
        return wordListTemp;
    }

    // webViewの選択範囲の先頭・後尾の空白文字の要素消去、分割
    wordListTemp = sentence.trimmed().split(QRegExp("(\\s|\n)+"));

    // wordListを返す / return the wordListTemp
    return wordListTemp;
}


// spritzの開始 / start spritz
void OpenQpritz::start(int intervalNumber)
{
    if (intervalNumber > 0) {
        qDebug("start(%d)", intervalNumber);

        startupLoopNumber = intervalNumber + 1;
        connect(m_timer, SIGNAL(timeout()),
                this, SLOT(startup()));

        m_timer->start(60 * 1000 / m_spritzWpmNumber);
    } else {
        qDebug("spritz");

        if (m_spritzWpmNumber) {
            connect(m_timer, SIGNAL(timeout()),
                    this, SLOT(spritz()));

            m_timer->start(60 * 1000 / m_spritzWpmNumber);
        }
    }
}


// 始動動作 / startup action
void OpenQpritz::startup()
{
    QString startupWordToShow = "";
    QString startupWord = ".";

    if (startupLoopNumber > 0) {
        qDebug("startup(%d)", startupLoopNumber);

        startupWordToShow += "<font color = black>" + startupWord.repeated(startupLoopNumber - 1) + "</font>";
        startupWordToShow += "<font color = red>" + startupWord + "</font>";
        startupWordToShow += "<font color = black>" + startupWord.repeated(startupLoopNumber - 1) + "</font>";
        startupWordToShow += "<font color = transparent>.</font>";

        emit outputSpritzWord(startupWordToShow);
        startupLoopNumber --;
        qDebug("loop");
    } else {
        qDebug("%d startup", startupLoopNumber);

        emit outputSpritzWord(startupWordToShow);
        startupLoopNumber --;
        qDebug("loop end");

        disconnect(m_timer, SIGNAL(timeout()),
                   this, SLOT(startup()));
        start(0);
    }
}


// spritzの一時停止 / pause spritz
void OpenQpritz::pause()
{
    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()),
               this, SLOT(startup()));
    disconnect(m_timer, SIGNAL(timeout()),
               this, SLOT(spritz()));
}


// spritzの停止 / stop spritz
void OpenQpritz::stop()
{
    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()),
               this, SLOT(startup()));
    disconnect(m_timer, SIGNAL(timeout()),
               this, SLOT(spritz()));
    spritzLoopNumber = 0;
}


// spritzCore関数 / spritz core function
void OpenQpritz::spritz()
{
    if (spritzLoopNumber < m_wordList.count()) {
        m_wordTmp = m_wordList[spritzLoopNumber];
        wordToShow = processWordForSpritz(m_wordList[spritzLoopNumber]);
        emit outputSpritzWord(wordToShow);

        qDebug("%d\t" + m_wordTmp.toLatin1(), spritzLoopNumber);

        spritzLoopNumber += 1;
    } else {
        m_wordTmp = "";
        wordToShow = m_wordTmp;
        emit outputSpritzWord(m_wordTmp);

        qDebug("%d\t" + m_wordTmp.toLatin1(), spritzLoopNumber);

        m_timer->stop();
        spritzLoopNumber = 0;
        qDebug("%d\t" + m_wordTmp.toLatin1(), spritzLoopNumber);

        disconnect(m_timer, SIGNAL(timeout()),
                   this, SLOT(spritz()));

        emit finishSpritz();
    }
}


// 単語をspritz用に加工 / process word for spritz
QString OpenQpritz::processWordForSpritz(QString word)
{
    int length = word.length();

    int bestLetter = 1;

    switch (length) {
    case 1:
        bestLetter = 1; // first
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        bestLetter = 2; // second
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        bestLetter = 3; // third
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        bestLetter = 4; // fourth
        break;
    default:
        bestLetter = 5;
    }

    QString frontSpacer = QString(".").repeated(11 - bestLetter);
    QString frontWordPeace = word.mid(0, bestLetter - 1);
    QString coreWordPeace = word.mid(bestLetter - 1, 1);
    QString backWordPeace = word.mid(bestLetter, length - bestLetter);
    QString backSpacer = QString(".").repeated((11-(word.length() - bestLetter)));

    QString result = "<font color = Transparent>" + frontSpacer + "</font>";
    result += "<font color = black>" + frontWordPeace + "</font>";
    result += "<font color = red>" + coreWordPeace + "</font>";
    result += "<font clor = black>" + backWordPeace + "</font>";
    result += "<font color = Transparent>" + backSpacer + "</font>";

    return result;
}


// spritzWpmNumの更新 / update spritzWpmNum
void OpenQpritz::setSpritzWpmNumber(const int newSpritzWpmNumber)
{
    m_spritzWpmNumber = newSpritzWpmNumber;
}
