#pragma once

#include "context.h"

#include <QMainWindow>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Context context;
    QLineEdit *outputLine;
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow() = default;
private slots:
    void convertNumber();

    void updateDisplay();

    void updateInputValue(const QString&);

    void updateInputBase(const QString&);

    void updateOutputBase(const QString&);
};
