#ifndef CREATEFORM_H
#define CREATEFORM_H

#include "priority.h"
#include <QDialog>

namespace Ui {
class CreateForm;
}

class CreateForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateForm(QWidget *parent = nullptr);
    ~CreateForm();

    QString getTitle() const;
    QString getDescription() const;
    Priority getPriority() const;
    void setPriority(Priority priority);

public slots:
    void accept() override;

private:
    Ui::CreateForm *ui;
};

#endif // CREATEFORM_H
