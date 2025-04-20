//
// Created by EgrZver on 20.04.2025.
//

#include "Arico.h"
#include <QDir>

namespace Arico {
    Arico::Arico() {
        this->_process = new QProcess;
    }
    
    Arico::~Arico() {
        delete this->_process;
    }
    
    void Arico::run(AricoParameters parameters) {
        QString cmd;
        QStringList args;
        args << "arico.py";
        if (parameters.mode == Type::AricoMode::Pack) {
            args << "-a" << "-i" << parameters.inputFile << "-o" << parameters.outputFile << "-w" << QString::number(parameters.width) << "-s" << QString::number(parameters.scale);
        } else if (parameters.mode == Type::AricoMode::Unpack) {
            args << "-e" << "-i" << parameters.inputFile << "-o" << parameters.outputFile;
        }
        qDebug() << "args: " << args;
        qDebug() << "status code: " << QProcess::execute("./python/python", args);
    }
    
} // Arico