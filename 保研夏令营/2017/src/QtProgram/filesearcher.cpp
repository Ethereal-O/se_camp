#include "filesearcher.h"
#include "ui_filesearcher.h"
#include<QDebug>
#include<QFile>

void Token::print()
{
    qDebug("%d, %s\n",this->type, this->str.toUtf8().data());
}

void Exp::print(int i)
{
    qDebug()<<i<<": "<<type<<" "<<str;
    if (left)
        left->print(i+1);
    if (right)
        right->print(i+1);
}

void SearchElem::print()
{
    qDebug()<<lineIndex<<" "<<tokenIndex<<" "<<searchStr;
}

fileSearcher::fileSearcher(QVector<QString>& lines, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::fileSearcher),originLines(lines)
{
    ui->setupUi(this);
    connect(ui->searcherBtn,&QPushButton::clicked,this,&fileSearcher::setQL);
    for (auto&&line:lines)
    {
        this->lines.push_back(parseTokens(line));
//        QStringList list=line.split(" ");
//        QVector<Token> tokens;
//        for (auto&&l:list)
//        {
//            processString(l);
//            if (l.size()>0&&l[0]<='z'&&l[0]>='a')
//            {
//                tokens.push_back(Token(l));
//            }
//        }
//        this->lines.push_back(tokens);
    }
    saveTokens();
}

void fileSearcher::saveTokens()
{
    QMap<QString, QVector<QPair<int, int>>> map=makeMap();
    QString s;
    for (auto iter=map.begin();iter!=map.end();iter++)
    {
        s+=iter.key()+" {";
        auto &&v=iter.value();
        for (int i=0;i<v.size()-1;i++)
        {
            s+="("+QString::number(v[i].first)+","+QString::number(v[i].second)+"),";
        }
        if (v.size()>0)
        {
            s+="("+QString::number(v[v.size()-1].first)+","+QString::number(v[v.size()-1].second)+")";
        }
        s+="}\n";
    }
    QFile f("myResult.txt");
    if (!f.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"ERROR: "<<s;
        return;
    }
    f.write(s.toUtf8().data());
    f.flush();
}

fileSearcher::~fileSearcher()
{
    delete ui;
}

void fileSearcher::setQL()
{
    startQL(ui->searcherInput->text());
}

void fileSearcher::startQL(QString ql)
{
    QVector<Token> tokens=parseTokens(ql);
    Exp* exp=parseExp(tokens, 0, tokens.size()-1);
    QVector<SearchElem> elems=search(exp);
    showRes(elems);
}

void fileSearcher::processString(QString& origin)
{
    origin=origin.toLower();
    if (origin.size()>1&&origin[origin.size()-1]=='s')
        origin.remove(origin.size()-1,1);
    if (origin.size()>2&&origin[origin.size()-1]=='d'&&origin[origin.size()-2]=='e')
        origin.remove(origin.size()-2,2);
}

QMap<QString, QVector<QPair<int, int>>> fileSearcher::makeMap()
{
    QMap<QString, QVector<QPair<int, int>>> map;
    for (int i=0;i<lines.size();i++)
    {
        for (int j=0;j<lines[i].size();j++)
        {
            if (map.contains(lines[i][j].str))
            {
                map.find(lines[i][j].str).value().push_back(QPair<int, int>(i,j));
            }else{
                map.insert(lines[i][j].str, QVector<QPair<int, int>>{QPair<int, int>(i,j)});
            }
        }
    }
    return map;
}

QVector<Token> fileSearcher::parseTokens(QString ql)
{
    QVector<Token> tokens;
    for (int i=0;i<ql.size();i++)
    {
        if(ql[i]==' '||ql[i]=='\t')
        {
            continue;
        }else if(ql[i]=='(')
        {
            tokens.push_back(Token(TokenType::LEFT));
        }else if(ql[i]==')')
        {
            tokens.push_back(Token(TokenType::RIGHT));
        }else if(ql[i]=='&'&&i+1<ql.size()&&ql[i+1]=='&')
        {
            tokens.push_back(Token(TokenType::AND));
            i++;
        }else if(ql[i]=='|'&&i+1<ql.size()&&ql[i+1]=='|')
        {
            tokens.push_back(Token(TokenType::OR));
            i++;
        }else if(ql[i]=='!')
        {
            tokens.push_back(Token(TokenType::NOT));
        }else if((ql[i]>='a'&&ql[i]<='z')||(ql[i]>='A'&&ql[i]<='Z'))
        {
            QString s;
            while(i<ql.size()&&((ql[i]>='a'&&ql[i]<='z')||(ql[i]>='A'&&ql[i]<='Z')||ql[i]=='-'))
            {
                s.append(ql[i].toLower());
                i++;
            }
            i--;
            processString(s);
            tokens.push_back(s);
        }else {
            qDebug("warning: jump unknown char %c", ql[i]);
        }
    }
    return tokens;
}

Exp* fileSearcher::parseExp(QVector<Token>& tokens, int from, int to)
{
    if (from>to)
        return nullptr;
    switch (tokens[from].type) {
        case TokenType::NORMAL:
        {
            if (from==to)
            {
                return new Exp(tokens[from].str);
            }
            if (from+1<=to&&tokens[from+1].type==TokenType::AND)
            {
                Exp* e=parseExp(tokens, from+2,to);
                return new Exp(TokenType::AND, new Exp(tokens[from].str), e);
            }
            if (from+1<=to&&tokens[from+1].type==TokenType::OR)
            {
                Exp* e=parseExp(tokens, from+2,to);
                return new Exp(TokenType::OR, new Exp(tokens[from].str), e);
            }
            exit(-1);
            break;
        }
    case TokenType::NOT:
        {
            Exp* e=parseExp(tokens, from+1,to);
            return new Exp(e);
            break;
        }
    case TokenType::LEFT:
        {
            int nextTo=from+1;
            int stackNum=1;
            while(nextTo<=to)
            {
                if (tokens[nextTo].type==TokenType::LEFT)
                {
                    stackNum++;
                }
                if (tokens[nextTo].type==TokenType::RIGHT)
                {
                    stackNum--;
                    if (stackNum==0)
                        break;
                }
                nextTo++;
            }

            if (nextTo<=to){
                Exp* l=parseExp(tokens, from+1,nextTo-1);
                Exp* r=parseExp(tokens, nextTo+2,to);
                if (r==nullptr)
                {
                    return l;
                }else{
                    if (tokens[nextTo+1].type==TokenType::AND)
                    {
                        return new Exp(TokenType::AND, l, r);
                    }
                    if (tokens[nextTo+1].type==TokenType::OR)
                    {
                        return new Exp(TokenType::OR, l, r);
                    }
                }
            }else{
                exit(-1);
                break;
            }
        }
    default:
        exit(-1);
    }
}

QVector<SearchElem> fileSearcher::search(Exp *e)
{
    if (e==nullptr)
        return QVector<SearchElem>();
    switch (e->type)
    {
        case TokenType::NORMAL:
        {
            QVector<SearchElem> elems;
            for (int i=0;i<lines.size();i++)
            {
                for (int j=0;j<lines[i].size();j++)
                {
                    if (lines[i][j].str.compare(e->str)==0)
                    {
                        elems.push_back(SearchElem(i, j, e->str));
                    }
                }
            }
            return elems;
        }
    case TokenType::NOT:
    {
        QVector<SearchElem> elems=search(e->left);
        QVector<SearchElem> res;
        QVector<bool> exist(lines.size(),0);
        for (auto && elem:elems)
        {
            exist[elem.lineIndex]=true;
        }
        for (int i=0;i<exist.size();i++)
        {
            if (!exist[i])
                res.push_back(SearchElem(i,-1,""));
        }
        return res;
    }
    case TokenType::AND:
    {
        QVector<SearchElem> l=search(e->left);
        QVector<SearchElem> r=search(e->right);
        QVector<SearchElem> res;
        for (int i=0;i<l.size();i++)
        {
            for (int j=0;j<r.size();j++)
            {
                if (l[i].lineIndex==r[j].lineIndex)
                {
                    if (l[i].tokenIndex==-1)
                    {
                        res.push_back(SearchElem(l[i].lineIndex,r[j].tokenIndex,r[j].searchStr));
                        continue;
                    }
                    if (r[j].tokenIndex==-1)
                    {
                        res.push_back(SearchElem(l[i].lineIndex,l[i].tokenIndex,l[i].searchStr));
                        continue;
                    }
                    if (l[i].tokenIndex+1==r[j].tokenIndex)
                    {
                        res.push_back(SearchElem(l[i].lineIndex,l[i].tokenIndex,l[i].searchStr+" "+r[j].searchStr));
                        continue;
                    }
                }
            }
        }
        return res;
    }
    case TokenType::OR:
    {
        QVector<SearchElem> l=search(e->left);
        QVector<SearchElem> r=search(e->right);
        QVector<SearchElem> res;
        for (auto && t:l)
        {
            res.push_back(t);
        }
        for (auto && t:r)
        {
            res.push_back(t);
        }

        return res;
    }
    }
}

void fileSearcher::showRes(QVector<SearchElem>& elems)
{
    QString str;
    QVector<QPair<QString, int>> res;
    for (auto &&elem:elems)
    {
        bool find=false;
        for (auto &&r:res)
        {
            if (r.first.compare(elem.searchStr)==0)
            {
                find=true;
                r.second++;
            }
        }
        if(!find)
        {
            res.push_back(QPair<QString, int>(elem.searchStr,1));
        }
    }

    for (auto&& r:res)
    {
        str+=r.first+": "+QString::number(r.second)+" occurrences\n";
    }

    QVector<bool> exist(lines.size(),false);
    for (auto&& elem:elems)
    {
        exist[elem.lineIndex]=true;
    }

    int index=1;
    for(int i=0;i<lines.size();i++)
    {
        if (exist[i])
        {
            str+=QString::number(index)+".("+QString::number(i)+")"+originLines[i]+"\n";
            index++;
        }
    }

    ui->searcherRes->setText(str);

}
