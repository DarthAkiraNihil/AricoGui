//
// Created by EgrZver on 26.04.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_about_dialog.h" resolved

#include "about_dialog.h"
#include "ui_about_dialog.h"
#include <QPushButton>

namespace UI {
    
    inline const QString ABOUT = "Курсовой проект по дисциплине \"АСД\", представляющий собой реализацию целочисленного арифметического кодера и декодера.\n\nАвтор - Егор \"Akira Nihil\" Зверев - https://github.com/DarthAkiraNihil\n\nАлгоритм разработан с применением Python 3.12.9\n\nИнтерфейс разработан с применением C++26 и Qt 6.8.0\n\nПроект лицензирован под Apache 2.0. License";
    
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
        
        this->ui->labelInfo->setText(ABOUT);
        
    }
    
    AboutDialog::~AboutDialog() {
        delete this->ui;
    }
} // UI
