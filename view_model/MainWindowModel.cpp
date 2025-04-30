//
// Created by EgrZver on 20.04.2025.
//

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "MainWindowModel.h"

namespace ViewModel {
    MainWindowModel::MainWindowModel(Arico::Arico* arico, QWidget* parent) {
    
        this->parent = parent;
    
        this->inputFileName = "";
        this->outputFileName = "";
        this->chunkSize = 63366;
        this->width = 32;
        this->scale = 0;
        this->mode = Type::AricoMode::Pack;
        
        this->aricoInstance = arico;
        
        QObject::connect(this->aricoInstance, &Arico::Arico::aricoFinished, this, &MainWindowModel::onAricoFinished);
        
    }
    
    void MainWindowModel::selectPackMode(bool checked) {
        if (checked) {
            this->mode = Type::AricoMode::Pack;
            emit this->nonRequiredParametersEnabledChanged(true);
            qDebug() << "Mode: pack";
        }
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::selectUnpackMode(bool checked) {
        if (checked) {
            this->mode = Type::AricoMode::Unpack;
            emit this->nonRequiredParametersEnabledChanged(false);
            qDebug() << "Mode: unpack";
        }
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::selectInputFile(bool checked) {
        QString filename;
        if (this->mode == Type::AricoMode::Unpack) {
            filename = QFileDialog::getOpenFileName(this->parent, "Выбрать входной файл", ".", tr("Архив Arico (*.ari)"));
        } else {
            filename = QFileDialog::getOpenFileName(this->parent, "Выбрать входной файл", ".");
        }
        if (!filename.isEmpty()) {
            this->inputFileName = filename;
            emit this->selectedInputFileChanged(filename);
        }
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::selectOutputFile(bool checked) {
        QString filename;
        if (this->mode == Type::AricoMode::Pack) {
            filename = QFileDialog::getSaveFileName(this->parent, "Выбрать выходной файл", ".", tr("Архив Arico (*.ari)"));
        } else {
            filename = QFileDialog::getSaveFileName(this->parent, "Выбрать выходной файл", ".");
        }
        if (!filename.isEmpty()) {
            this->outputFileName = filename;
            emit this->selectedOutputFileChanged(filename);
        }
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::executeArico(bool checked) {
        if (!this->validate()) {
            QMessageBox::critical(this->parent, "Saatana vittu perkele", "Произошла ошибка валидации входных данных. Убедитесь, что входные данные введены правильно!");
            return;
        }
        if (this->width > 4096) {
            QMessageBox::warning(this->parent, "Внимание!", "Вы указали очень большую ширину кодового слова. Возможны потери в точности и производительности!");
        }
        
        this->aricoInstance->execute({
            this->inputFileName,
            this->outputFileName,
            this->width,
            this->scale,
            this->chunkSize,
            this->mode
        });
        emit this->aricoStarted();
        
    }
    
    bool MainWindowModel::validate() {
        if (this->mode == Type::AricoMode::Pack) {
            return !this->inputFileName.isEmpty() && !this->outputFileName.isEmpty() && this->width > 2 && this->scale >= 0 && this->chunkSize > 0;
        } else {
            return !this->inputFileName.isEmpty() && !this->outputFileName.isEmpty()  && this->chunkSize > 0;
        }
    }
    
    void MainWindowModel::changeWidth(const QString &text) {
        this->width = text.toInt();
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::changeScale(const QString &text) {
        this->scale = text.toInt();
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::changeChunkSize(const QString &text) {
        this->chunkSize = text.toInt();
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::onAricoFinished(Arico::AricoResult result) {
        emit this->aricoFinished();
        if (result.status == Arico::AricoExecutionStatus::Success) {
            QMessageBox::information(
                this->parent, "Успех!",
                QString("Сжатие данных успешно!\n\nВремя выполнения: %0\n\nКоэффициент сжатия: %1")
                    .arg(result.elapsedTime).arg(result.compressionCoefficient));
        } else {
            QMessageBox::critical(
                this->parent, "Saatana vittu perkele",
                "Произошла ошибка выполнения"
            );
        }
    }
} // ViewModel