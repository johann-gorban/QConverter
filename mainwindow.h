#pragma once

#include "context.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QMap>
#include <QString>
#include <QPushButton>

#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Context context;
    QMap<QString, unsigned int> bases;
private:
    QLineEdit *inputLine;
    QLineEdit *outputLine;

    QComboBox *inputBaseBox;
    QComboBox *outputBaseBox;

    QPushButton *convertButton;
    QPushButton *copyButton;

    QHBoxLayout *buttonBox;
    QVBoxLayout *centralLayout;

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
