#ifndef EDITFORM_H
#define EDITFORM_H

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

private:
    Ui::EditForm *ui;
};

#endif // EDITFORM_H
