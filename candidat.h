#ifndef CANDIDAT_H
#define CANDIDAT_H
#include<QString>
#include<QtSql/QSqlQuery>
#include <QDate>
#include<QtSql/QSqlQueryModel>
#include <QTableView>
#include <QComboBox>

class candidat
{
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString resume;
    int tel;
public:
    candidat();
    candidat(int id,QString nom,QString prenom,QString email,QString resume,int tel);

    //Getters
    int getid(){return  id;}
    QString getnom(){return  nom;}
    QString getprenom(){return  prenom;}
    QString getemail(){return  email;}
    QString getresume(){return  resume;}
    int gettel(){return tel;}
    //Setters
    void setid(int i){this->id=i;}
    void setnom(QString n){nom=n;}
    void setprenom(QString a){prenom=a;}
    void setemail(QString em){email=em;}
    void setresume(QString rs){resume=rs;}
    void setel(int i){this->tel=i;}
    //  base features
    bool ajout ();
    QSqlQueryModel * afficher ();
    bool supprimer (int id);
    bool modifier (int,QString,QString,QString,QString,int);
     QSqlQueryModel* sortid();
     QSqlQueryModel* sortnom();
     QSqlQueryModel* sortprenom();
     //QSqlQueryModel* recherche(int id);
    void recherche(QTableView * table ,int ,QString , QString );
    void  telechargerPDF();

};
#endif // CANDIDAT_H
