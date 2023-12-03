//
// Created by hemingguo on 2023-12-1.
//

#ifndef SHAPEZ_FIRST_H
#define SHAPEZ_FIRST_H

#include <QWidget>
#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class first; }
QT_END_NAMESPACE

class first : public QWidget
{
Q_OBJECT

public:
    explicit first(QWidget *parent = nullptr);

    ~first() override;

private:
    Ui::first *ui;
    int windowWidth;
    int windowHeight;

};


#endif //SHAPEZ_FIRST_H
