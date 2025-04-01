#include "mainwindow.h"
#include "entry.h"

#include <QtWidgets>
#include <string>
#include <iostream>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Setup bases hash map
    bases["Binary"] = 2; // decompose
    bases["Octal"] = 8;
    bases["Decimal"] = 10;
    bases["Hexidecimal"] = 16; // define (hardcode)

    // Setup context default values
    context.source_num = (char *)"0\0"; // move to logic func
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
    inputBaseBox = new QComboBox;
    inputBaseBox->addItems(convertionBases);

    QObject::connect(inputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInputBase(QString)));

    // Input line setup
    inputLine = new QLineEdit;
    inputLine->setText("0");
    inputLine->setFixedHeight(40);

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(updateInputValue(QString)));

    // Output line combo box setup
    outputBaseBox = new QComboBox;
    outputBaseBox->addItems(convertionBases);

    QObject::connect(outputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateOutputBase(QString)));

    // Output line setup
    outputLine = new QLineEdit;
    outputLine->setReadOnly(true);
    outputLine->setText("0");
    outputLine->setFixedHeight(40);

    // Copy to clipboard button setup
    copyButton = new QPushButton("Copy");
    copyButton->setFixedHeight(50);

    QObject::connect(copyButton, &QPushButton::clicked, this, &MainWindow::copyResult);

    // Convert button setup
    convertButton = new QPushButton("Convert");
    convertButton->setFixedHeight(50);

    QObject::connect(convertButton, &QPushButton::clicked, this, &MainWindow::convertNumber);

    // Button layout setup
    buttonBox = new QHBoxLayout;

    buttonBox->addWidget(copyButton);
    buttonBox->addWidget(convertButton);

    // Layout setup
    centralLayout = new QVBoxLayout;

    centralLayout->addWidget(inputBaseBox);
    centralLayout->addWidget(inputLine);

    centralLayout->addWidget(outputBaseBox);
    centralLayout->addWidget(outputLine);

    centralLayout->addLayout(buttonBox);

    // Set layout
    centralWidget->setLayout(centralLayout);
}

void MainWindow::convertNumber() {
    executeOperation(convert, &context);
    updateDisplay();
}

void MainWindow::copyResult() {
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(context.final_num);

    auto main_label = copyButton->text();
    copyButton->setText("Copied!");
    QTimer::singleShot(2000, this, [this, main_label]{
        copyButton->setText(main_label);
    });
}

void MainWindow::updateDisplay() {
    outputLine->setText(context.final_num);
}

void MainWindow::updateInputValue(const QString &value) {
    std::string stdValue = value.toStdString();

    context.source_num = new char[stdValue.size() + 1]; // To logic
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
