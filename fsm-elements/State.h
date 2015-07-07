#pragma once

#include <fsm-editor/fsm-elements/Transition.h>

#include <functional>

#include <QGraphicsRectItem>
#include <QUndoCommand>

class FSMScene;

class State : public QGraphicsRectItem
{
  using super = QGraphicsRectItem;
public:
  State(const QString& title, const QPointF& position, std::function<void(QUndoCommand*)>&& pushStack);

  virtual ~State();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

  void shrinkTextToFit(QPainter * painter);

  static bool fitInRect(const QRectF& rect, const QRect& bounding);

  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

  void setSilentMove(bool silent);

  QString title() const;

  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

  FSMScene* scene() const;
  void pushCommand(QUndoCommand* command);

  void transitionTo(State* destination);
  void removeTransitionTo(State* destination);
private:
  static const qreal WIDTH;
  static const qreal HEIGHT;
  static const qreal H_MARGIN;
  static const qreal V_MARGIN;
  static const QColor PEN_COLOR;

private:
  QString title_;
  QString content_;
  std::function<void(QUndoCommand*)> pushStack_;
  bool silent_;
  Transition dangling_;
  QList<Transition*> transitions_;
};
