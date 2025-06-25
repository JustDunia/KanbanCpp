#include "editform.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditForm)
{
    ui->setupUi(this);
}

EditForm::~EditForm()
{
    delete ui;
}

void EditForm::setTitle(const QString &title)
{
    ui->titleLineEdit->setText(title);
}

void EditForm::setDescription(const QString &description)
{
    ui->descriptionTextEdit->setPlainText(description);
}

QString EditForm::getTitle() const
{
    return ui->titleLineEdit->text();
}

QString EditForm::getDescription() const
{
    return ui->descriptionTextEdit->toPlainText();
}
