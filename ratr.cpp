#include "ratr.h"
#include "ui_ratr.h"
#include"offre.h"
#include "candidat.h"
#include <QRadioButton>
#include <QDate>
#include<QIntValidator>
#include <QMessageBox>
#include <QValidator>
#include <QObject>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QTableView>
#include<QApplication>
#include <QtCharts>
#include <QChart>
#include "qrcode.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QDialog>
#include <QWidgetData>





ratr::ratr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ratr)
{
    ui->setupUi(this);
    ui->id_ajout->setValidator ( new QIntValidator(0, 99999999, this));
    ui->tab_offre->setModel(O.afficher());
    ui->tab_candidat->setModel(c.afficher());
}

ratr::~ratr()
{
    delete ui;
}








void ratr::on_add_clicked()
{
    int id=ui->id_ajout->text().toInt();
    QString exp_posted=ui->exp_posted_ajout->text();
    QString date_posted=ui->date_posted_ajout->text();
    QString titre=ui->titre_ajout->text();
    QString description=ui->description_ajout->text();
    offre O(id,titre,description,date_posted,exp_posted);

     bool test= O.ajout();
    if(test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Add successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    } else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("Add failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_offre->setModel(O.afficher());

}







void ratr::on_trier_clicked()
{
    ui->tab_offre->setModel(O.sortid());
}



void ratr::on_trier_titre_clicked()
{
    ui->tab_offre->setModel(O.sorttitre());
}



void ratr::on_trier_desc_clicked()
{
    ui->tab_offre->setModel(O.sortdesc());
}







void ratr::on_suppr_clicked()
{
    offre O;
       O.setid(ui->id_suppr->text().toInt());
       bool test=O.supprimer(O.getid());
       QMessageBox msgBox;
       if(test)
       {msgBox.setText("Deleted succesfully.");

       }
       else
           msgBox.setText("Failed");
           msgBox.exec();
           ui->tab_offre->setModel(O.afficher());
}





void ratr::on_modif_clicked()
{

    int id=ui->id_modif->text().toInt();
    QString titre=ui->titre_modif->text();
     QString description=ui->description_modif->text();
      QString date_posted=ui->date_posted_modif->text();
      QString exp_posted=ui->exp_posted_modif->text();
      offre O(id,titre,description,date_posted,exp_posted);



bool test=O.modifier(id,titre,description,date_posted,exp_posted);
if (test){
    ui->tab_offre->setModel(O.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("update successfully.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           ui->id_modif->clear();
           ui->titre_modif->clear();
           ui->description_modif->clear();
           ui->date_posted_modif->clear();
}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr(" update Faild.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}





/*
void ratr::on_recherche_clicked()
{
    int id=ui->rech->text().toInt();

           if (id==NULL) {

               QMessageBox::information(this, tr("Empty Field"),

                   tr("Please enter a Number."));

               return;

           } else {

           ui->tab_offre->setModel(O.recherche(id));

           }

}
*/


void ratr::on_rech_textChanged(const QString &arg1)
{
    //Q_UNUSED(arg1);
    offre o;
    int id= ui->rech->text().toInt();
     QString titre = ui->rech->text();
    QString description = ui->rech->text();
    o.recherche(ui->tab_offre,id,titre,description);
    if (ui->rech->text().isEmpty())
    {
        ui->tab_offre->setModel(o.afficher());
    }
}



void ratr::on_export_2_clicked()
{

    offre o;
    o.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);

}

void ratr::on_stat_clicked()
{
    QSqlQuery query;
         query.prepare("SELECT COUNT(*) FROM OFFRE WHERE TITRE='devloppeur web'");
         query.exec();
         query.next();
         int tn = query.value(0).toInt();

         query.prepare("SELECT COUNT(*) FROM OFFRE WHERE TITRE='marketing'");
         query.exec();
         query.next();
         int gb = query.value(0).toInt();

         query.prepare("SELECT COUNT(*) FROM OFFRE WHERE TITRE='comptable'");
         query.exec();
         query.next();
         int bi = query.value(0).toInt();

         QPieSeries *series = new QPieSeries();
         series->append("devloppeur web", tn);
         series->append("marketing", gb);
         series->append("comptable", bi);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Static");

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         QDialog *dialog = new QDialog(this);
         dialog->setWindowTitle("Static");
         dialog->resize(400, 300);
         QVBoxLayout *layout = new QVBoxLayout(dialog);
         layout->addWidget(chartView);

         dialog->exec();

}












//candidats








void ratr::on_cadd_clicked()
{
    int id = ui->cid_ajout->text().toInt();
    QString telStr = ui->ctel_ajout->text();
    QString resume = ui->cresume_ajout->text();
    QString email = ui->cemail_ajout->text();
    QString nom = ui->cnom_ajout->text();
    QString prenom = ui->cprenom_ajout->text();

    // Regular expression to validate email
    QRegExp emailRegex("^[\\w-\\.]+@[\\w-]+\\.[a-z]{2,4}$", Qt::CaseInsensitive);

    // Regular expression to validate telephone number (only digits)
    QRegExp telRegex("^\\d+$");  // ^\\d+$ ensures that the string contains only digits

    // Check if the email is valid
    if (!emailRegex.exactMatch(email)) {
        QMessageBox::warning(nullptr, QObject::tr("Invalid Email"),
                             QObject::tr("Please enter a valid email address.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        return;  // Exit the function if the email is invalid
    }

    // Check if the telephone number is valid
    if (!telRegex.exactMatch(telStr)) {
        QMessageBox::warning(nullptr, QObject::tr("Invalid Telephone Number"),
                             QObject::tr("Please enter a valid telephone number (digits only).\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        return;  // Exit the function if the telephone number is invalid
    }

    // Convert the valid telephone number to an integer
    int tel = telStr.toInt();

    candidat c(id, nom, prenom, email, resume, tel);

    bool test = c.ajout();
    if(test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Added successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                              QObject::tr("Add failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->tab_candidat->setModel(c.afficher());
}



/*
void ratr::on_cadd_clicked()
{
    int id=ui->cid_ajout->text().toInt();
    int tel=ui->ctel_ajout->text().toInt();
    QString resume=ui->cresume_ajout->text();
    QString email=ui->cemail_ajout->text();
    QString nom=ui->cnom_ajout->text();
    QString prenom=ui->cprenom_ajout->text();
    candidat c(id,nom,prenom,email,resume,tel);

     bool test= c.ajout();
    if(test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Add successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    } else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("Add failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_candidat->setModel(c.afficher());

}
*/






void ratr::on_ctrier_clicked()
{
    ui->tab_candidat->setModel(c.sortid());
}



void ratr::on_ctrier_nom_clicked()
{
    ui->tab_candidat->setModel(c.sortnom());
}



void ratr::on_ctrier_prenom_clicked()
{
    ui->tab_candidat->setModel(c.sortprenom());
}







void ratr::on_csuppr_clicked()
{
    candidat c;
       c.setid(ui->cid_suppr->text().toInt());
       bool test=c.supprimer(c.getid());
       QMessageBox msgBox;
       if(test)
       {msgBox.setText("Deleted succesfully.");

       }
       else
           msgBox.setText("Failed");
           msgBox.exec();
           ui->tab_candidat->setModel(c.afficher());
}





void ratr::on_cmodif_clicked()
{

    int id=ui->cid_modif->text().toInt();
    int tel=ui->ctel_modif->text().toInt();
    QString nom=ui->cnom_modif->text();
     QString prenom=ui->cprenom_modif->text();
      QString email=ui->cemail_modif->text();
      QString resume=ui->cresume_modif->text();
      candidat c(id,nom,prenom,email,resume,tel);



bool test=c.modifier(id,nom,prenom,email,resume,tel);
if (test){
    ui->tab_candidat->setModel(c.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("update successfully.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           ui->cid_modif->clear();
           ui->cnom_modif->clear();
           ui->cprenom_modif->clear();
           ui->cemail_modif->clear();
           ui->cresume_modif->clear();
           ui->ctel_modif->clear();

}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr(" update Faild.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}






void ratr::on_crech_textChanged(const QString &arg1)
{
    //Q_UNUSED(arg1);
    candidat c;
    int id= ui->crech->text().toInt();
     QString nom = ui->crech->text();
    QString prenom = ui->crech->text();
  c.recherche(ui->tab_candidat,id,nom,prenom);
    if (ui->crech->text().isEmpty())
    {
        ui->tab_candidat->setModel(c.afficher());
    }

}





void ratr::on_cexport_2_clicked()
{
        candidat c;
        c.telechargerPDF();

                 QMessageBox::information(nullptr,QObject::tr("OK"),
                            QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}

void ratr::on_cstat_clicked()
{
    QSqlQuery query;
         query.prepare("SELECT COUNT(*) FROM CANDIDAT WHERE RESUME='devloppeur web'");
         query.exec();
         query.next();
         int dw = query.value(0).toInt();

         query.prepare("SELECT COUNT(*) FROM CANDIDAT WHERE RESUME='marketing'");
         query.exec();
         query.next();
         int mr = query.value(0).toInt();

         query.prepare("SELECT COUNT(*) FROM CANDIDAT WHERE RESUME='comptable'");
         query.exec();
         query.next();
         int cm = query.value(0).toInt();

         QPieSeries *series = new QPieSeries();
         series->append("devloppeur web", dw);
         series->append("marketing", mr);
         series->append("comptable", cm);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Static");

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         QDialog *dialog = new QDialog(this);
         dialog->setWindowTitle("Static");
         dialog->resize(400, 300);
         QVBoxLayout *layout = new QVBoxLayout(dialog);
         layout->addWidget(chartView);

         dialog->exec();

}










void ratr::on_qrcode_clicked()
{



    // Get the selected row
      int selectedRow = ui->tab_offre->currentIndex().row();

      // Ensure a valid row is selected
      if (selectedRow < 0) {
          qDebug() << "No row selected!";
          return;
    }


    QString text ="Details de l'offre d'emplois: "+ ui->tab_offre->model()->data(ui->tab_offre->model()->index(ui->tab_offre->currentIndex().row(),0)).toString()
                            +"\n"+ui->tab_offre->model()->data(ui->tab_offre->model()->index(ui->tab_offre->currentIndex().row(),1)).toString()
                            +"\n"+ui->tab_offre->model()->data(ui->tab_offre->model()->index(ui->tab_offre->currentIndex().row(),2)).toString()
                            +"\n"+ui->tab_offre->model()->data(ui->tab_offre->model()->index(ui->tab_offre->currentIndex().row(),3)).toString()
                            +ui->tab_offre->model()->data(ui->tab_offre->model()->index(ui->tab_offre->currentIndex().row(),4)).toString();
                    //librairie
                    using namespace qrcodegen;
                      // Create the QR Code object
                      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                      qint32 sz = qr.getSize();
                      QImage im(sz,sz, QImage::Format_RGB32);
                        QRgb black = qRgb(  0,  0,  0);
                        QRgb white = qRgb(255,255,255);
                      for (int y = 0; y < sz; y++)
                        for (int x = 0; x < sz; x++)
                          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                      ui->qr_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}



void ratr::on_appliquer_clicked()
{
    int id = ui->id_app->text().toInt();
    int candidatId = ui->idcan_app->text().toInt();
    int offreId = ui->idoffre_app->text().toInt();
    QString date = ui->date_app->text();

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CANDIDAT WHERE ID = :candidatId");
    query.bindValue(":candidatId", candidatId);
    query.exec();

    if (query.next() && query.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Invalid Candidate ID", "The candidate ID does not exist.");
        return;
    }

    query.prepare("SELECT COUNT(*) FROM OFFRE WHERE ID = :offreId");
    query.bindValue(":offreId", offreId);
    query.exec();

    if (query.next() && query.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Invalid Offer ID", "offer ID does not exist.");
        return;
    }

    query.prepare("INSERT INTO APPLICATION (ID, CAN_ID, OFFRE_ID, DATE_APPLIED) VALUES (:id, :candidatId, :offreId, :date)");
    query.bindValue(":id", id);
    query.bindValue(":candidatId", candidatId);
    query.bindValue(":offreId", offreId);
    query.bindValue(":date", date);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Application submitted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to submit the application.");
    }
}




