#ifndef RATR_H
#define RATR_H

#include "candidat.h"
#include "offre.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class ratr; }
QT_END_NAMESPACE

class ratr : public QMainWindow
{
    Q_OBJECT

public:
    ratr(QWidget *parent = nullptr);
    ~ratr();
private slots:
    //offres
    void on_add_clicked();
    void on_suppr_clicked();
    void on_modif_clicked();
    void on_rech_textChanged(const QString &arg1);
    void on_trier_clicked();
    void on_trier_titre_clicked();
    void on_trier_desc_clicked();
    void on_export_2_clicked();
    void on_stat_clicked();
    //candidats
    void on_cadd_clicked();
    void on_ctrier_clicked();
    void on_ctrier_nom_clicked();
    void on_ctrier_prenom_clicked();
    void on_csuppr_clicked();
    void on_cmodif_clicked();
    void on_crech_textChanged(const QString &arg1);
    void on_cexport_2_clicked();
    void on_cstat_clicked();
    void on_qrcode_clicked();
    void on_appliquer_clicked();
private:
    Ui::ratr *ui;
    offre O;
    candidat c;
    QSqlDatabase db;

    void setupDatabase();
};
#endif // RATR_H
