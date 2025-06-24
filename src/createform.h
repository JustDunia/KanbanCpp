#ifndef CREATEFORM_H
#define CREATEFORM_H

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

private:
    Ui::CreateForm *ui;
};

#endif // CREATEFORM_H
