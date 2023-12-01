//
// Created by hemingguo on 2023-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_first.h" resolved

#include "first.h"
#include "ui_first.h"


first::first(QWidget *parent) :
        QWidget(parent), ui(new Ui::first)
{
    ui->setupUi(this);
}

first::~first()
{
    delete ui;
}
