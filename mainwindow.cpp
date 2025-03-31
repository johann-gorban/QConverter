#include "mainwindow.h"
#include "entry.h"

#include <QtWidgets>
#include <string>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Setup bases hash map
    bases["Binary"] = 2;
    bases["Octal"] = 8;
    bases["Decimal"] = 10;
    bases["Hexidecimal"] = 16;

    // Setup context default values
    context.source_num = (char *)"0\0";
    context.source_base = 2;
    context.final_num = (char *)"0\0";
    context.final_base = 2;

    // Set maximum window size
    setFixedSize(350, 250);

    QStringList convertionBases;
    for (auto key : bases.keys()) {
        convertionBases.append(key);
    }

    // Central widget setup
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Input line combo box setup
    auto inputBaseBox = new QComboBox;
    inputBaseBox->addItems(convertionBases);

    QObject::connect(inputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInputBase(QString)));

    // Input line setup
    auto inputLine = new QLineEdit;
    inputLine->setText("0");
    inputLine->setFixedHeight(40);

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(updateInputValue(QString)));

    // Output line combo box setup
    auto outputBaseBox = new QComboBox;
    outputBaseBox->addItems(convertionBases);

    QObject::connect(outputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateOutputBase(QString)));

    // Output line setup
    outputLine = new QLineEdit;
    outputLine->setReadOnly(true);
    outputLine->setText("0");
    outputLine->setFixedHeight(40);

    // Copy to clipboard button setup
    auto copyButton = new QPushButton("Copy");
    copyButton->setFixedHeight(50);

    QObject::connect(copyButton, &QPushButton::clicked, this, &MainWindow::copyResult);

    // Convert button setup
    auto convertButton = new QPushButton("Convert");
    convertButton->setFixedHeight(50);

    QObject::connect(convertButton, &QPushButton::clicked, this, &MainWindow::convertNumber);

    // Button layout setup
    auto buttonBox = new QHBoxLayout;

    buttonBox->addWidget(copyButton);
    buttonBox->addWidget(convertButton);

    // Layout setup
    auto box = new QVBoxLayout;

    box->addWidget(inputBaseBox);
    box->addWidget(inputLine);

    box->addWidget(outputBaseBox);
    box->addWidget(outputLine);

    box->addLayout(buttonBox);

    // Set layout
    centralWidget->setLayout(box);
}

void MainWindow::convertNumber() {
    executeOperation(convert, &context);
    updateDisplay();
}

void MainWindow::copyResult() {
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(context.final_num);
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
    auto fb = bases.find(base);
    if (fb != bases.end()) {
        context.source_base = fb.value();
    }
    else {
        context.source_base = 0;
    }
}

void MainWindow::updateOutputBase(const QString &base) {
    auto fb = bases.find(base);
    if (fb != bases.end()) {
        context.final_base = fb.value();
    }
    else {
        context.final_base = 0;
    }
}
