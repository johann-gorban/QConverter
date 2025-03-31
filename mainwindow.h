#pragma once

#include "context.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QMap>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Context context;
    QLineEdit *outputLine;
    QMap<QString, unsigned int> bases;
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow() = default;
private slots:
    void convertNumber();

    void copyResult();

    void updateDisplay();

    void updateInputValue(const QString&);

    void updateInputBase(const QString&);

    void updateOutputBase(const QString&);
};
