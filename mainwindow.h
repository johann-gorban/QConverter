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
    // Class attributes
    Context context;
    QMap<QString, unsigned int> bases;

    // Widgets
    QLineEdit *inputLine;
    QLineEdit *outputLine;

    QComboBox *inputBaseBox;
    QComboBox *outputBaseBox;

    QPushButton *convertButton;
    QPushButton *copyButton;

    QHBoxLayout *buttonBox;
    QVBoxLayout *centralLayout;
private:
    void widgets_setup();
    void bases_setup();
    void slots_connect();
private slots:
    void convertNumber();

    void copyResult();

    void updateDisplay();

    void updateInputValue(const QString&);

    void updateInputBase(const QString&);

    void updateOutputBase(const QString&);
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow() = default;
};
