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
        this->width = 32;
        this->scale = 0;
        this->mode = Type::AricoMode::Pack;
        
        this->aricoInstance = arico;
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
        QString filename = QFileDialog::getOpenFileName(this->parent, "Выбрать входной файл", ".");
        if (!filename.isEmpty()) {
            this->inputFileName = filename;
            emit this->selectedInputFileChanged(filename);
        }
        emit this->validationStatusChanged(this->validate());
    }
    
    void MainWindowModel::selectOutputFile(bool checked) {
        QString filename = QFileDialog::getSaveFileName(this->parent, "Выбрать выходной файл", ".", tr("Архив Arico (*.ari)"));
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
            QMessageBox::warning(this->parent, "Внимание!", "Вы указали очень большую ширину кодового слова. Возможны потери в точности и потеря производительности!");
        }
        this->aricoInstance->execute({
            this->inputFileName,
            this->inputFileName + QString(".ari"),
            this->width,
            this->scale,
            this->mode
        });
    }
    
    bool MainWindowModel::validate() {
        if (this->mode == Type::AricoMode::Pack) {
            return !this->inputFileName.isEmpty() && !this->outputFileName.isEmpty() && this->width > 2 && this->scale >= 0;
        } else {
            return !this->inputFileName.isEmpty() && !this->outputFileName.isEmpty();
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
} // ViewModel