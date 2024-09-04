#include "offre.h"
#include <QtSql/QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QPdfWriter>
#include <QDate>
#include <QComboBox>
#include <QtSql/QSqlError>
#include <QFile>
#include <QApplication>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
//#include <QPieSlice>

offre::offre()
{

}
offre::offre(int id,QString titre,QString description,QString date_posted,QString exp_posted)
{
     this->id=id;
     this->titre=titre;
     this->description=description;
     this->date_posted=date_posted;
     this->exp_posted=exp_posted;
}

bool offre::ajout()
{
    QSqlQuery  query;
    bool test=false;
    QString id_string = QString::number(id);

    query.prepare("insert into OFFRE (TITRE, DESCRIPTION, DATE_POSTED,EXP_POSTED,ID)" "values (:TITRE, :DESCRIPTION, :DATE_POSTED, :EXP_POSTED,:ID)");


    query.bindValue(":ID",id_string);
    query.bindValue(":TITRE",titre);
    query.bindValue(":DESCRIPTION",description);
    query.bindValue(":DATE_POSTED",date_posted);
    query.bindValue(":EXP_POSTED",exp_posted);
    return query.exec();
    return test;
}

QSqlQueryModel * offre::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM OFFRE ORDER BY TITRE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_POSTED"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXP_POSTED"));
    return  model;
}

bool offre::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("DELETE FROM OFFRE WHERE ID= :id");

    query.bindValue(":id",res);

    return  query.exec();

}

bool offre::modifier(int id,QString titre,QString description,QString date_posted,QString exp_posted)
   {
    QSqlQuery query;
    QString id_string = QString::number(id);

    query.prepare("UPDATE OFFRE SET ID=:ID, TITRE=:TITRE,DESCRIPTION=:DESCRIPTION,DATE_POSTED=:DATE_POSTED,EXP_POSTED=:EXP_POSTED WHERE ID=:ID");

    query.bindValue(":TITRE", titre);
    query.bindValue(":DESCRIPTION", description);
    query.bindValue(":DATE_POSTED", date_posted);
    query.bindValue(":EXP_POSTED", exp_posted);
    query.bindValue(":ID", id_string);
    return query.exec();
   }







void  offre::telechargerPDF()
{

                     QPdfWriter pdf("C:\\Users\\MSI\\Documents\\ratr\\offre.pdf");
                     QPainter painter(&pdf);
                     pdf.setPageSize(QPageSize(QPageSize::A4)); // Définissez la taille de la page
                     int i = 4000;


                    painter.fillRect(QRect(0, 0, pdf.width(), pdf.height()), QColor("#CEF0E8"));

                      painter.setPen(QColor("#008F8A"));
                         QFont titleFont("Roboto", 30, QFont::Bold);
                         painter.setFont(titleFont);
                         painter.drawText(1200,1400,"GESTION OFFRES D'EMPLOI");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Roboto",14));
                         painter.drawRect(800,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Roboto",8));
                         painter.drawText(300,3300,"ID");
                         painter.drawText(1500,3300,"TITRE");
                         painter.drawText(2000,3300,"DESCRIPTION");
                         painter.drawText(3200,3300,"DATE POSTED");
                         painter.drawText(4200,3300,"EXPOSEE POSTED");



                         QSqlQuery query;

                         query.prepare("select * from OFFRE");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2300,i,query.value(2).toString());
                             painter.drawText(3300,i,query.value(3).toString());
                             painter.drawText(4300,i,query.value(4).toString());
                            i = i + 500;
                         }
}







QSqlQueryModel *offre::sortid()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from OFFRE ORDER BY ID ");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_POSTED"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXP_POSTED"));
return model;
}



QSqlQueryModel *offre::sorttitre()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from OFFRE ORDER BY TITRE ");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_POSTED"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXP_POSTED"));
return model;
}



QSqlQueryModel *offre::sortdesc()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from OFFRE ORDER BY DESCRIPTION");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_POSTED"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXP_POSTED"));
return model;
}


void offre::recherche(QTableView * tab_offre ,int id,QString titre, QString description )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString id_string=QString::number(id);

    QSqlQuery *query=new QSqlQuery;
    query->prepare("SELECT * FROM OFFRE WHERE ID LIKE '%"+id_string+"%' OR TITRE LIKE '%"+titre+"%' OR DESCRIPTION LIKE '%"+description+"%' ;");
    query->exec();
    model->setQuery(*query);
    tab_offre->setModel(model);
    tab_offre->show();

}
