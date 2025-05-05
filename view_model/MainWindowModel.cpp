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
        
        this->aricoRunning = false;
        
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
        
        if (this->aricoRunning) {
            if (QMessageBox::question(this->parent, "Предупреждение", "В действительно хотите отменить текущую операцию?") == QMessageBox::Yes) {
                this->aricoInstance->kill();
                this->aricoRunning = false;
                emit this->aricoFinished();
            }
            return;
        }
        
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
        this->frozenMode = this->mode;
        this->aricoRunning = true;
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
    
    void MainWindowModel::onAricoFinished(Arico::AricoResult result, QString message) {
        emit this->aricoFinished();
        this->aricoRunning = false;
        switch(result.status) {
            case Arico::AricoExecutionStatus::Success: {
                
                long long timeSeconds = result.elapsedTime / 1000;
                long long timeMicroSeconds = result.elapsedTime % 1000;
                long long timeMinutes = timeSeconds / 60;
                long long timeHours = timeMinutes / 60;
                long long timeDays = timeHours / 24;
                
                QString time = QString("%0:%1:%2:%3.%4")
                    .arg(timeDays)
                    .arg(timeHours % 24)
                    .arg(timeMinutes % 60)
                    .arg(timeSeconds % 60)
                    .arg(timeMicroSeconds);
                
                if (this->frozenMode == Type::AricoMode::Pack) {
                    QMessageBox::information(
                        this->parent, "Успех!",
                        QString("Сжатие данных успешно!\n\nВремя выполнения: %0\n\nСтепень сжатия: %1")
                            .arg(time).arg(result.compressionCoefficient)
                    );
                } else {
                    QMessageBox::information(
                        this->parent, "Успех!",
                        QString("Распаковка данных успешна!\n\nВремя выполнения: %0")
                            .arg(time).arg(result.compressionCoefficient)
                    );
                }
                break;
            }
            case Arico::AricoExecutionStatus::ErrorWidthTooSmall: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    "Ошибка - ширина кодового слова слишком маленькая. Введите значение, хотя бы большее 2!"
                );
                return;
            }
            case Arico::AricoExecutionStatus::ErrorChunkSizeTooSmall: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    "Ошибка - размер блока при чтении данных слишком маленький. Введите значение, хотя бы большее 1!"
                );
                return;
            }
            case Arico::AricoExecutionStatus::ErrorInvalidSignature: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    "Ошибка - файл имеет некорректную сигнатуру, а следовательно не является файлом архива Arico"
                );
                return;
            }
            case Arico::AricoExecutionStatus::ErrorLengthCheckpointNotFound: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    QString("Ошибка - не найдена контрольная точка длин в архиве. Возможно, он повреждён.\n\nПодробнее:\n\n%0").arg(message)
                );
                return;
            }
            case Arico::AricoExecutionStatus::ErrorCountsCheckpointNotFound: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    QString("Ошибка - не найдена контрольная точка частотной таблицы в архиве. Возможно, он повреждён.\n\nПодробнее:\n\n%0").arg(message)
                );
                return;
            }
            
            case Arico::AricoExecutionStatus::UnknownError: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    QString("Ошибка - неизвестная ошибка\n\nПодробнее:\n\n%0").arg(message)
                );
                return;
            }
            case Arico::AricoExecutionStatus::Killed: {
                return;
            }
            default: {
                QMessageBox::critical(
                    this->parent, "Saatana vittu perkele",
                    "Ошибка - результат выполнения - не запущен"
                );
                return;
            }
        }
    }
} // ViewModel