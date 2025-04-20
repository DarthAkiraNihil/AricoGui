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
        
        Arico::Arico* arico = new Arico::Arico;
        
        this->viewModel = new ViewModel::MainWindowModel(arico, this);
        
        
        
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
        QObject::connect(this->ui->radioButtonCompress, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::selectPackMode);
        QObject::connect(this->ui->radioButtonDecompress, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::selectUnpackMode);
        
        QObject::connect(this->ui->buttonSelectFile, &QAbstractButton::clicked, this->viewModel,&ViewModel::MainWindowModel::selectInputFile);
        QObject::connect(this->ui->buttonExecute, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::executeArico);
        
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::nonRequiredParametersEnabledChanged, this, &MainWindow::changeNonRequiredParametersEnableState);
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::selectedInputFileChanged, this, &MainWindow::changeSelectedInputFile);
    }
    
    void MainWindow::changeSelectedInputFile(const QString& filename) {
        this->ui->labelInputFile->setText(filename);
    }
    
    void MainWindow::changeNonRequiredParametersEnableState(bool state) {
        this->ui->lineEditScale->setEnabled(state);
        this->ui->lineEditWidth->setEnabled(state);
    }
    
} // UI
