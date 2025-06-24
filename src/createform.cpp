#include "createform.h"
#include "ui_createform.h"

CreateForm::CreateForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateForm)
{
    ui->setupUi(this);
}

CreateForm::~CreateForm()
{
    delete ui;
}

QString CreateForm::getTitle() const {
    return ui->titleLineEdit->text();
}

QString CreateForm::getDescription() const {
    return ui->descriptionTextEdit->toPlainText();
}
