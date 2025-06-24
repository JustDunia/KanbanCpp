#include "kanbanlistwidget.h"
#include "quuid.h"
#include "status.h"
#include <QDropEvent>
#include <QMimeData>

KanbanListWidget::KanbanListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::DropAction::MoveAction);
}

Status KanbanListWidget::getStatus() const {
    return listStatus;
}

void KanbanListWidget::setStatus(Status s)
{
    listStatus = s;
}

void KanbanListWidget::dropEvent(QDropEvent *event)
{
    QListWidget::dropEvent(event);

    const QByteArray data = event->mimeData()->data("application/x-kanban-task-id");
    if (!data.isEmpty()) {
        QUuid id(QString::fromUtf8(data));
        emit taskDropped(id, listStatus);
    }
}

QMimeData *KanbanListWidget::mimeData(const QList<QListWidgetItem *> &items) const {
    QMimeData *mimeData = QListWidget::mimeData(items);

    if (!items.isEmpty()) {
        const QUuid id = items.first()->data(Qt::UserRole).toUuid();
        mimeData->setData("application/x-kanban-task-id", id.toByteArray());
    }

    return mimeData;
}
