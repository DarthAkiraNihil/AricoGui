//
// Created by EgrZver on 20.04.2025.
//

#include <QDebug>
#include <QFileDialog>
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
    }
    
    void MainWindowModel::selectUnpackMode(bool checked) {
        if (checked) {
            this->mode = Type::AricoMode::Unpack;
            emit this->nonRequiredParametersEnabledChanged(false);
            qDebug() << "Mode: unpack";
        }
    }
    
    void MainWindowModel::selectInputFile(bool checked) {
        QString filename = QFileDialog::getOpenFileName(this->parent, "Выбрать входной файл", ".");
        if (!filename.isEmpty()) {
            this->inputFileName = filename;
            emit this->selectedInputFileChanged(filename);
        }
    }
    
    void MainWindowModel::executeArico(bool checked) {
        this->aricoInstance->run({
            this->inputFileName,
            this->inputFileName + QString(".ari"),
            this->width,
            this->scale,
            this->mode
        });
    }
} // ViewModel