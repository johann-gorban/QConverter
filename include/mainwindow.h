#pragma once

#include "context.h"

#include <QMap>
#include <QString>

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
    QPushButton *swapButton;

    QHBoxLayout *buttonBox;
    QVBoxLayout *centralLayout;
private:
    void widgets_setup();

    void bases_setup();

    void slots_connect();

private slots:
    void convertNumber();

    void copyResult();

    void swapLines();

    void updateDisplay();

    void showErrorWarning();

    void updateInputValue(const QString&);

    void updateInputBase(const QString&);

    void updateOutputBase(const QString&);
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
};
