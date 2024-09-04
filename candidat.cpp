#include "candidat.h"
#include <QtSql/QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QDate>
#include<QMessageBox>
#include <QTableWidget>
#include <QPdfWriter>
#include <QComboBox>
#include <QtSql/QSqlError>
#include <QFile>
#include <QApplication>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
//#include <QPieSlice>

candidat::candidat()
{

}
candidat::candidat(int id,QString nom,QString prenom,QString email,QString resume,int tel) 
{
     this->id=id;
     this->nom=nom;
     this->prenom=prenom;
     this->email=email;
     this->resume=resume;
     this->tel=tel;
}

bool candidat::ajout()
{
    QSqlQuery  query;
    bool test=false;
    QString id_string = QString::number(id);
    QString tel_string = QString::number(tel);


    query.prepare("insert into CANDIDAT (NOM, PRENOM, EMAIL,RESUME,TEL,ID)" "values (:NOM, :PRENOM, :EMAIL, :RESUME,:TEL,:ID)");


    query.bindValue(":ID",id_string);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":EMAIL",email);
    query.bindValue(":RESUME",resume);
    query.bindValue(":TEL",tel_string);
    return query.exec();
    return test;
}

QSqlQueryModel * candidat::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM CANDIDAT ORDER BY NOM");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("RESUME"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TEL"));
    return  model;
}

bool candidat::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("DELETE FROM CANDIDAT WHERE ID= :id");

    query.bindValue(":id",res);

    return  query.exec();

}

bool candidat::modifier(int id,QString nom,QString prenom,QString email,QString resume,int tel)
   {
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString tel_string = QString::number(tel);

    query.prepare("UPDATE CANDIDAT SET ID=:ID, NOM=:NOM,PRENOM=:PRENOM,EMAIL=:EMAIL,RESUME=:RESUME,TEL=:TEL WHERE ID=:ID");

    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":EMAIL", email);
    query.bindValue(":RESUME", resume);
    query.bindValue(":TEL", tel_string);
    query.bindValue(":ID", id_string);
    return query.exec();
   }






void  candidat::telechargerPDF()
{

                     QPdfWriter pdf("C:\\Users\\MSI\\Documents\\ratr\\candidats.pdf");
                     QPainter painter(&pdf);
                     pdf.setPageSize(QPageSize(QPageSize::A4)); // Définissez la taille de la page
                     int i = 4000;


                    painter.fillRect(QRect(0, 0, pdf.width(), pdf.height()), QColor("#CEF0E8"));

                      painter.setPen(QColor("#008F8A"));
                         QFont titleFont("Roboto", 30, QFont::Bold);
                         painter.setFont(titleFont);
                         painter.drawText(1200,1400,"GESTION CANDIDATS");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Roboto",14));
                         painter.drawRect(800,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Roboto",8));
                         painter.drawText(300,3300,"ID");
                         painter.drawText(1500,3300,"NOM");
                         painter.drawText(2000,3300,"PRENOM");
                         painter.drawText(3200,3300,"EMAIL");
                         painter.drawText(4200,3300,"RESUME");
                         painter.drawText(5000,3300,"NUMERO TEL");



                         QSqlQuery query;

                         query.prepare("select * from CANDIDAT");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2300,i,query.value(2).toString());
                             painter.drawText(3300,i,query.value(3).toString());
                             painter.drawText(4300,i,query.value(4).toString());
                             painter.drawText(6000,i,query.value(5).toString());
                            i = i + 500;
                         }
}










QSqlQueryModel *candidat::sortid()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from CANDIDAT ORDER BY ID ");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("RESUME"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TEL"));
return model;
}



QSqlQueryModel *candidat::sortnom()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from CANDIDAT ORDER BY NOM ");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("RESUME"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TEL"));
return model;
}



QSqlQueryModel *candidat::sortprenom()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from CANDIDAT ORDER BY PRENOM");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("RESUME"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TEL"));
return model;
}





void candidat::recherche(QTableView * tab_candidat , int id, QString nom, QString prenom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString id_string=QString::number(id);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("SELECT * FROM CANDIDAT WHERE ID LIKE '%"+id_string+"%' OR NOM LIKE '%"+nom+"%' OR PRENOM LIKE '%"+prenom+"%' ;");


    query->exec();
    model->setQuery(*query);
    tab_candidat->setModel(model);
    tab_candidat->show();

}
