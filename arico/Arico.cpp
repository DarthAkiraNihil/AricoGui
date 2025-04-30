//
// Created by EgrZver on 20.04.2025.
//

#include "Arico.h"
#include <QDir>
#include <QElapsedTimer>

namespace Arico {
    
    inline const QString PYTHON_PATH = "./python/python";
    
    Arico::Arico(): elapsed() {
        this->_process = new QProcess;
        QObject::connect(this->_process, &QProcess::finished, this, &Arico::onAricoFinished);
    }
    
    Arico::~Arico() {
        delete this->_process;
    }
    
    void Arico::execute(const AricoParameters& parameters) {
        this->lastUsedParameters = parameters;
        QStringList args;
        
        args << "arico.py";
        
        if (parameters.mode == Type::AricoMode::Pack) {
            args << "-a" << "-i" << parameters.inputFile << "-o" << parameters.outputFile << "-w" << QString::number(parameters.width) << "-s" << QString::number(parameters.scale) << "-c" << QString::number(parameters.chunkSize);
        } else if (parameters.mode == Type::AricoMode::Unpack) {
            args << "-e" << "-i" << parameters.inputFile << "-o" << parameters.outputFile << "-c" << QString::number(parameters.chunkSize);
        }
        
        qDebug() << "args: " << args;
        
        this->elapsed.start();
        // int statusCode = QProcess::execute(PYTHON_PATH, args);
        this->_process->start(PYTHON_PATH, args);
        //qDebug() << "status code: " << statusCode;
        
    }
    
    void Arico::onAricoFinished(int code, QProcess::ExitStatus status) {
        AricoResult result;
        qDebug() << "Status code" << code;
        switch (code) {
            case 0: {
                result.status = AricoExecutionStatus::Success;
                
                QFile input(this->lastUsedParameters.inputFile);
                QFile output(this->lastUsedParameters.outputFile);
                
                result.compressionCoefficient = ((double) (input.size() - output.size()) / (double) input.size()) * 100.0;
                result.elapsedTime = elapsed.elapsed();
                emit this->aricoFinished(result, "");
                return;
            }
            case 1: {
                result.status = AricoExecutionStatus::ErrorWidthTooSmall;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
            case 2: {
                result.status = AricoExecutionStatus::ErrorChunkSizeTooSmall;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
            case 10: {
                result.status = AricoExecutionStatus::ErrorInvalidSignature;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
            case 11: {
                result.status = AricoExecutionStatus::ErrorLengthCheckpointNotFound;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
            case 12: {
                result.status = AricoExecutionStatus::ErrorCountsCheckpointNotFound;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
            case 62097: {
                result.status = AricoExecutionStatus::Killed;
                emit this->aricoFinished(result, "");
                return;
            }
            default: {
                result.status = AricoExecutionStatus::UnknownError;
                emit this->aricoFinished(result, QString(this->_process->readAllStandardOutput()));
                return;
            }
        }
    }
    
    void Arico::kill() {
        if (this->_process->processId() > 0) {
            this->_process->kill();
            qDebug() << "Last output: " << this->lastUsedParameters.outputFile;
            QFile file(this->lastUsedParameters.outputFile);
            file.remove();
        }
    }
    
} // Arico