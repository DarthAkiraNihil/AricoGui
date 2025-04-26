//
// Created by EgrZver on 26.04.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_about_dialog.h" resolved

#include "about_dialog.h"
#include "ui_about_dialog.h"
#include <QPushButton>

namespace UI {
    AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AboutDialog) {
        this->ui->setupUi(this);
        
        QObject::connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        
        QFont jetBrainsMonoRegular("JetBrains Mono", 10);
        
        this->ui->buttonBox->setFont(jetBrainsMonoRegular);
        this->ui->buttonBox->button(QDialogButtonBox::Ok)->setFont(jetBrainsMonoRegular);
        this->ui->labelInfo->setFont(jetBrainsMonoRegular);
        
        this->ui->labelLogo->setPixmap(QPixmap(":/assets/logo.png"));
        this->ui->labelLogo->setScaledContents(true);
        
    }
    
    AboutDialog::~AboutDialog() {
        delete ui;
    }
} // UI
