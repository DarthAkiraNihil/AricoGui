//
// Created by EgrZver on 20.04.2025.
//

#include "Arico.h"
#include <QDir>
#include <QElapsedTimer>

namespace Arico {
    
    inline const QString PYTHON_PATH = "./python/python";
    
    Arico::Arico() {
        this->_process = new QProcess;
    }
    
    Arico::~Arico() {
        delete this->_process;
    }
    
    AricoResult Arico::execute(const AricoParameters& parameters) {
        QStringList args;
        
        args << "arico.py";
        
        if (parameters.mode == Type::AricoMode::Pack) {
            args << "-a" << "-i" << parameters.inputFile << "-o" << parameters.outputFile << "-w" << QString::number(parameters.width) << "-s" << QString::number(parameters.scale);
        } else if (parameters.mode == Type::AricoMode::Unpack) {
            args << "-e" << "-i" << parameters.inputFile << "-o" << parameters.outputFile;
        }
        
        qDebug() << "args: " << args;
        
        QElapsedTimer elapsed;
        elapsed.start();
        int statusCode = QProcess::execute(PYTHON_PATH, args);
        qDebug() << "status code: " << statusCode;
        
        AricoResult result;
        
        switch (statusCode) {
            case 0: {
                result.status = AricoExecutionStatus::Success;
                
                QFile input(parameters.inputFile);
                QFile output(parameters.outputFile);
                
                result.compressionCoefficient = ((double) (input.size() - output.size()) / (double) input.size()) * 100.0;
                result.elapsedTime = elapsed.elapsed();
                return result;
            }
            default: {
                result.status = AricoExecutionStatus::Error;
                return result;
            }
        }
    }
    
} // Arico