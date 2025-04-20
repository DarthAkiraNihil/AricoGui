//
// Created by EgrZver on 20.04.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>

#include "main_window.h"
#include "ui_main_window.h"

namespace UI {
    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
        this->ui->setupUi(this);
        
        this->viewModel = new ViewModel::MainWindowModel;
        
        this->connectSignals();
        
        QFont serif("JetBrains Mono",32, QFont::Weight::Bold); // serif is a variable, change later
        this->ui->labelLogo->setFont(serif);
        
        this->ui->radioButtonCompress->setIcon(QIcon(":/assets/icon_compress.png"));
        this->ui->radioButtonDecompress->setIcon(QIcon(":/assets/icon_decompress.png"));
    }
    
    MainWindow::~MainWindow() {
        delete this->ui;
        delete this->viewModel;
    }
    
    void MainWindow::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        this->resize({
            event->size().width(),
            (event->size().width() * 9) / 16
        });
    }
    
    void MainWindow::connectSignals() {
        QObject::connect(this->ui->radioButtonCompress, &QAbstractButton::clicked, this->viewModel,
                         &ViewModel::MainWindowModel::selectPackMode);
        QObject::connect(this->ui->radioButtonDecompress, &QAbstractButton::clicked, this->viewModel,
                         &ViewModel::MainWindowModel::selectUnpackMode);
    }
    
    void MainWindow::changeSelectedInputFile(QString filename) {
    
    }
    
} // UI
