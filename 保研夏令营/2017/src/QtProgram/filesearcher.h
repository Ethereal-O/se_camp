#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QMainWindow>

enum TokenType{
    LEFT,
    RIGHT,
    AND,
    OR,
    NOT,
    NORMAL,
    UNKNOWN,
};

class Token{
public:
    Token():type(TokenType::UNKNOWN){}
    Token(TokenType t):type(t){}
    Token(QString s):type(TokenType::NORMAL),str(s){}
    void print();
    TokenType type;
    QString str;
};

class Exp{
public:
    Exp():type(TokenType::UNKNOWN){}
    Exp(QString s):type(TokenType::NORMAL),str(s){};
    Exp(TokenType t, Exp* l, Exp* r):type(t),left(l),right(r){}
    Exp(Exp* l):type(TokenType::NOT),left(l){}
    void print(int i);
    TokenType type;
    QString str;
    Exp* left=nullptr;
    Exp* right=nullptr;
};

class SearchElem{
public:
    SearchElem(){}
    SearchElem(int l, int t, QString s):lineIndex(l),tokenIndex(t),searchStr(s){}
    void print();
    int lineIndex;
    int tokenIndex;
    QString searchStr;
};

namespace Ui {
class fileSearcher;
}

class fileSearcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileSearcher(QVector<QString>& lines, QWidget *parent = nullptr);
    ~fileSearcher();

private:
    Ui::fileSearcher *ui;
    QVector<QString> originLines;
    QVector<QVector<Token>> lines;
    QString searchQL;

    void setQL();
    void startQL(QString ql);
    void processString(QString& origin);
    void saveTokens();
    QMap<QString, QVector<QPair<int, int>>> makeMap();
    QVector<Token> parseTokens(QString ql);
    Exp* parseExp(QVector<Token>& tokens, int from, int to);
    QVector<SearchElem> search(Exp *e);
    void showRes(QVector<SearchElem>& elems);
};

#endif // FILESEARCHER_H
