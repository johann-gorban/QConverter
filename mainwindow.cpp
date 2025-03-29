#include "mainwindow.h"
#include "entry.h"

#include <QtWidgets>
#include <string>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Setup context default values
    context.source_num = (char *)"\0";
    context.source_base = 2;
    context.final_num = (char *)"\0";
    context.final_base = 2;

    // Set maximum window size
    this->setFixedSize(350, 250);

    QStringList convertionBases = {
        "Binary",
        "Octal",
        "Decimal",
        "Hexidecimal"
    };

    // Central widget setup
    auto centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Input line combo box setup
    auto inputBaseBox = new QComboBox;
    inputBaseBox->addItems(convertionBases);

    QObject::connect(inputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInputBase(QString)));

    // Input line setup
    auto inputLine = new QLineEdit;

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(updateInputValue(QString)));

    // Output line combo box setup
    auto outputBaseBox = new QComboBox;
    outputBaseBox->addItems(convertionBases);

    QObject::connect(outputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateOutputBase(QString)));

    // Output line setup
    outputLine = new QLineEdit;
    outputLine->setReadOnly(true);

    // Convert button setup
    auto convertButton = new QPushButton("Convert");

    QObject::connect(convertButton, &QPushButton::clicked, this, &MainWindow::convertNumber);


    // Layout setup
    auto box = new QVBoxLayout;

    box->addWidget(inputBaseBox);
    box->addWidget(inputLine);

    box->addWidget(outputBaseBox);
    box->addWidget(outputLine);

    box->addWidget(convertButton);

    // Set layout
    centralWidget->setLayout(box);
}


void MainWindow::convertNumber() {
    executeOperation(convert, &context);
    updateDisplay();
}

void MainWindow::updateDisplay() {
    outputLine->setText(context.final_num);
}

void MainWindow::updateInputValue(const QString &value) {
    std::string stdValue = value.toStdString();

    context.source_num = new char[stdValue.size() + 1];
    std::copy(stdValue.begin(), stdValue.end(), context.source_num);
    context.source_num[stdValue.size()] = '\0';
}

void MainWindow::updateInputBase(const QString &base) {
    if (base == "Binary") {
        context.source_base = 2;
    } else if (base == "Octal") {
        context.source_base = 8;
    } else if (base == "Decimal") {
        context.source_base = 10;
    } else if (base == "Hexidecimal") {
        context.source_base = 16;
    } else {
        context.source_base = 10;
    }
}

void MainWindow::updateOutputBase(const QString &base) {
    if (base == "Binary") {
        context.final_base = 2;
    } else if (base == "Octal") {
        context.final_base = 8;
    } else if (base == "Decimal") {
        context.final_base = 10;
    } else if (base == "Hexidecimal") {
        context.final_base = 16;
    } else {
        context.final_base = 10;
    }
}
