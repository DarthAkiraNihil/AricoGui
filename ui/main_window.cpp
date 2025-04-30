//
// Created by EgrZver on 20.04.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QIntValidator>

#include "main_window.h"
#include "ui_main_window.h"
#include "about_dialog.h"

namespace UI {
    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
        this->ui->setupUi(this);
        this->setWindowIcon(QIcon(":/assets/icon.ico"));
        
        auto arico = new Arico::Arico;
        
        this->ui->progressBar->setFormat("Подождите...");
        this->ui->progressBar->setAlignment(Qt::AlignCenter);
        this->ui->progressBar->setTextVisible(false);
        
        this->ui->lineEditWidth->setValidator(new QIntValidator(2, 999999, this));
        this->ui->lineEditScale->setValidator(new QIntValidator(0, 255, this));
        this->ui->lineEditChunkSize->setValidator(new QIntValidator(0, 9999999, this));
        
        this->viewModel = new ViewModel::MainWindowModel(arico, this);
        
        this->connectSignals();
        
        QFont jetBrainsMonoHeader("JetBrains Mono", 12);
        QFont jetBrainsMonoRegular("JetBrains Mono", 10);
        
        QList<QWidget*> applyHeaderFont = {
            this->ui->groupBoxFiles,
            this->ui->groupBoxMode,
            this->ui->groupBoxNonRequiredOptions,
        };
        
        QList<QWidget*> applyRegularFont = {
            this->ui->labelSelectInputFile,
            this->ui->buttonSelectInputFile,
            this->ui->labelInputFile,
            
            this->ui->labelSelectOutputFile,
            this->ui->buttonSelectOutputFile,
            this->ui->labelOutputFile,
            
            this->ui->labelScale,
            this->ui->lineEditScale,
            this->ui->labelWidth,
            this->ui->lineEditWidth,
            this->ui->labelChunkSize,
            this->ui->lineEditChunkSize,
            
            this->ui->buttonExecute,
            this->ui->buttonAbout
        };
        
        this->ui->verticalLayout->setAlignment(this->ui->labelLogo, Qt::AlignHCenter);
        
        this->ui->labelLogo->setPixmap(QPixmap(":/assets/logo_small.png"));
        this->ui->labelLogo->setScaledContents(true);
        // this->ui->labelLogo->setFont(jetBrainsMonoLogo);
        
        for (QWidget*& widget: applyHeaderFont) {
            widget->setFont(jetBrainsMonoHeader);
        }
        
        for (QWidget*& widget: applyRegularFont) {
            widget->setFont(jetBrainsMonoRegular);
        }
        
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
        
        QObject::connect(this->ui->buttonAbout, &QAbstractButton::clicked, this, &MainWindow::showAboutInfo);
        
        QObject::connect(this->ui->radioButtonCompress, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::selectPackMode);
        QObject::connect(this->ui->radioButtonDecompress, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::selectUnpackMode);
        
        QObject::connect(this->ui->buttonSelectInputFile, &QAbstractButton::clicked, this->viewModel,&ViewModel::MainWindowModel::selectInputFile);
        QObject::connect(this->ui->buttonSelectOutputFile, &QAbstractButton::clicked, this->viewModel,&ViewModel::MainWindowModel::selectOutputFile);
        
        QObject::connect(this->ui->buttonExecute, &QAbstractButton::clicked, this->viewModel, &ViewModel::MainWindowModel::executeArico);
        
        QObject::connect(this->ui->lineEditWidth, &QLineEdit::textChanged, this->viewModel, &ViewModel::MainWindowModel::changeWidth);
        QObject::connect(this->ui->lineEditScale, &QLineEdit::textChanged, this->viewModel, &ViewModel::MainWindowModel::changeScale);
        QObject::connect(this->ui->lineEditChunkSize, &QLineEdit::textChanged, this->viewModel, &ViewModel::MainWindowModel::changeChunkSize);
        
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::nonRequiredParametersEnabledChanged, this, &MainWindow::changeNonRequiredParametersEnableState);
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::selectedInputFileChanged, this, &MainWindow::changeSelectedInputFile);
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::selectedOutputFileChanged, this, &MainWindow::changeSelectedOutputFile);
        
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::validationStatusChanged, this, &MainWindow::setExecutionPossibility);
        
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::aricoStarted, this, &MainWindow::onAricoStarted);
        QObject::connect(this->viewModel, &ViewModel::MainWindowModel::aricoFinished, this, &MainWindow::onAricoFinished);
    }
    
    void MainWindow::changeSelectedInputFile(const QString& filename) {
        this->ui->labelInputFile->setText(filename);
    }
    
    void MainWindow::changeSelectedOutputFile(const QString &filename) {
        this->ui->labelOutputFile->setText(filename);
    }
    
    void MainWindow::changeNonRequiredParametersEnableState(bool state) {
        this->ui->lineEditScale->setEnabled(state);
        this->ui->lineEditWidth->setEnabled(state);
        this->ui->lineEditChunkSize->setEnabled(state);
    }
    
    void MainWindow::setExecutionPossibility(bool validationStatus) {
        this->ui->buttonExecute->setEnabled(validationStatus);
    }
    
    void MainWindow::showAboutInfo(bool /*checked*/) {
        AboutDialog aboutDialog(this);
        aboutDialog.exec();
    }
    
    void MainWindow::onAricoStarted() {
        this->ui->progressBar->setMaximum(0);
        this->ui->progressBar->setTextVisible(true);
    }
    
    void MainWindow::onAricoFinished() {
        this->ui->progressBar->setMaximum(1);
        this->ui->progressBar->setTextVisible(false);
    }
    
} // UI
