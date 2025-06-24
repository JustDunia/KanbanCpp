#ifndef KANBANLISTWIDGET_H
#define KANBANLISTWIDGET_H

#include "status.h"
#include <QListWidget>

class KanbanListWidget : public QListWidget
{
    Q_OBJECT
public:
    KanbanListWidget(QWidget *parent = nullptr);
    Status getStatus() const;
    void setStatus(Status s);

signals:
    void taskDropped(const QUuid &id, Status newStatus);

protected:
    void dropEvent(QDropEvent *event) override;
    QMimeData *mimeData(const QList<QListWidgetItem *> &items) const override;

private:
    Status listStatus;
};

#endif // KANBANLISTWIDGET_H
