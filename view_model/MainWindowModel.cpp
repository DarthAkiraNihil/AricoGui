//
// Created by EgrZver on 20.04.2025.
//

#include <QDebug>
#include "MainWindowModel.h"

namespace ViewModel {
    MainWindowModel::MainWindowModel() {
        this->inputFileName = "";
        this->outputFileName = "";
        this->width = 32;
        this->scale = 0;
        this->mode = Type::AricoMode::Pack;
    }
    
    void MainWindowModel::selectPackMode(bool checked) {
        if (checked) {
            this->mode = Type::AricoMode::Pack;
            qDebug() << "Mode: pack";
        }
    }
    
    void MainWindowModel::selectUnpackMode(bool checked) {
        if (checked) {
            this->mode = Type::AricoMode::Unpack;
            qDebug() << "Mode: unpack";
        }
    }
    
    void MainWindowModel::selectInputFileButtonPressed(bool checked) {
    
    }
} // ViewModel