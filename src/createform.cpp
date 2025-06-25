#include "createform.h"
#include "priority.h"
#include "ui_createform.h"
#include <QMessageBox>

CreateForm::CreateForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateForm)
{
    ui->setupUi(this);
    ui->priority->addItem("Low", QVariant::fromValue(Priority::Low));
    ui->priority->addItem("Medium", QVariant::fromValue(Priority::Medium));
    ui->priority->addItem("High", QVariant::fromValue(Priority::High));
    ui->priority->setCurrentIndex(0);
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

Priority CreateForm::getPriority() const {
    return ui->priority->currentData().value<Priority>();
}

void CreateForm::setPriority(Priority priority) {
    int index = ui->priority->findData(QVariant::fromValue(priority));
    if (index != -1) {
        ui->priority->setCurrentIndex(index);
    }
}

void CreateForm::accept() {
    if (ui->titleLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Title is required and cannot be empty.");
        return;
    }
    QDialog::accept();
}
