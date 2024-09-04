#ifndef OFFRE_H
#define OFFRE_H
#include<QString>
#include <QDate>
#include<QtSql/QSqlQuery>
#include <QTableView>
#include<QtSql/QSqlQueryModel>
#include <QComboBox>

class offre
{
    int id;
    QString titre;
    QString description;
    QString date_posted;
    QString exp_posted;
public:
    offre();
    offre(int id,QString titre,QString description,QString date_posted,QString exp_posted);

    //Getters
    int getid(){return  id;}
    QString gettitre(){return  titre;}
    QString getdescription(){return  description;}
    QString getdate_posted(){return  date_posted;}
    QString getexp_posted(){return  exp_posted;}
    //Setters
    void setid(int i){this->id=i;}
    void settitre(QString n){titre=n;}
    void setdescription(QString a){description=a;}
    void setdate_posted(QString dp){date_posted=dp;}
    void setexp_posted(QString ep){exp_posted=ep;}
    //  base features
    bool ajout ();
    QSqlQueryModel * afficher ();
    bool supprimer (int id);
    bool modifier (int,QString,QString,QString,QString);
     QSqlQueryModel* sortid();
     QSqlQueryModel* sorttitre();
     QSqlQueryModel* sortdesc();
     void recherche(QTableView * table ,int ,QString , QString );
     void  telechargerPDF();

};
#endif // OFFRE_H
