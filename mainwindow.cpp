#include "mainwindow.h"
#include "entry.h"

#include <QtWidgets>
#include <string>
#include <iostream>
#include <QTimer>

#define BIN_BASE 2
#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Setup bases hash map
    bases_setup();

    // Context setup
    executeOperation(context_initialization, &context);

    // Widgets setup and packing
    widgets_setup();

    // Slots for widgets connection
    slots_connect();
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

void MainWindow::widgets_setup() {
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

    // Input line setup
    inputLine = new QLineEdit;
    inputLine->setText("0");
    inputLine->setFixedHeight(40);

    // Output line combo box setup
    outputBaseBox = new QComboBox;
    outputBaseBox->addItems(convertionBases);

    // Output line setup
    outputLine = new QLineEdit;
    outputLine->setReadOnly(true);
    outputLine->setText("0");
    outputLine->setFixedHeight(40);

    // Copy to clipboard button setup
    copyButton = new QPushButton("Copy");
    copyButton->setFixedHeight(50);

    // Convert button setup
    convertButton = new QPushButton("Convert");
    convertButton->setFixedHeight(50);

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

void MainWindow::slots_connect() {
    QObject::connect(inputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInputBase(QString)));

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(updateInputValue(QString)));

    QObject::connect(outputBaseBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateOutputBase(QString)));

    QObject::connect(copyButton, &QPushButton::clicked, this, &MainWindow::copyResult);

    QObject::connect(convertButton, &QPushButton::clicked, this, &MainWindow::convertNumber);
}

void MainWindow::bases_setup() {
    bases["Binary"] = BIN_BASE;
    bases["Octal"] = OCT_BASE;
    bases["Decimal"] = DEC_BASE;
    bases["Hexidecimal"] = HEX_BASE;
}
