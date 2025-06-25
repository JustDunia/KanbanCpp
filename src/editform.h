#ifndef EDITFORM_H
#define EDITFORM_H

#include "priority.h"
#include <QDialog>

namespace Ui {
class EditForm;
}

class EditForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditForm(QWidget *parent = nullptr);
    ~EditForm();

    void setTitle(const QString &title);
    void setDescription(const QString &description);

    QString getTitle() const;
    QString getDescription() const;
    Priority getPriority() const;
    void setPriority(const Priority &priority);
private:
    Ui::EditForm *ui;
};

#endif // EDITFORM_H
