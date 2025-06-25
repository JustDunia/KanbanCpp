#include "editform.h"
#include "priority.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditForm)
{
    ui->setupUi(this);
    ui->priority->addItem("Low", QVariant::fromValue(Priority::Low));
    ui->priority->addItem("Medium", QVariant::fromValue(Priority::Medium));
    ui->priority->addItem("High", QVariant::fromValue(Priority::High));
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

void EditForm::setPriority(const Priority &priority){
    int index = ui->priority->findData(QVariant::fromValue(priority));
    if (index != -1) {
        ui->priority->setCurrentIndex(index);
    }
}

QString EditForm::getTitle() const
{
    return ui->titleLineEdit->text();
}

QString EditForm::getDescription() const
{
    return ui->descriptionTextEdit->toPlainText();
}

Priority EditForm::getPriority() const {
    return ui->priority->currentData().value<Priority>();
}
