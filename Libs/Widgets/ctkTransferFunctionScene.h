/*=========================================================================

  Library:   CTK
 
  Copyright (c) 2010  Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 
=========================================================================*/

#ifndef __ctkTransferFunctionScene_h
#define __ctkTransferFunctionScene_h

/// Qt includes
#include <QGraphicsScene>

/// CTK includes
#include "ctkPimpl.h"
#include "ctkTransferFunction.h"
#include "CTKWidgetsExport.h"

//class ctkTransferFunction;
class ctkTransferFunctionScenePrivate;
//class ctkControlPoint;
//class ctkPoint;

//-----------------------------------------------------------------------------
class CTK_WIDGETS_EXPORT ctkTransferFunctionScene: public QGraphicsScene
{
  Q_OBJECT
  Q_PROPERTY(QColor VerticalGradientColor READ verticalGradientColor WRITE setVerticalGradientColor)

public:
  ctkTransferFunctionScene(QObject* parent = 0);
  ctkTransferFunctionScene(ctkTransferFunction* transferFunction, QObject* parent = 0);
  virtual ~ctkTransferFunctionScene();

  void setTransferFunction(ctkTransferFunction* transferFunction);
  ctkTransferFunction* transferFunction()const;

  inline qreal posX(const ctkControlPoint* cp)const;
  inline qreal posY(const ctkControlPoint* cp)const;
  inline QColor color(const ctkControlPoint* cp) const;

  inline qreal posX(const ctkPoint& point)const;
  inline qreal posY(const ctkPoint& point)const;
  inline QColor color(const ctkPoint& point) const;

  qreal posX(const qreal& tfX)const;
  qreal posY(const QVariant& tfV)const;
  QColor color(const QVariant& tfV) const;
  
  QPointF mapPointToScene(const ctkControlPoint* cp)const;
  QPointF mapPointToScene(const ctkPoint& point)const;
  
 
  qreal mapXToScene(qreal posX)const;
  qreal mapYToScene(qreal posY)const;
  qreal mapXFromScene(qreal ScenePosX)const;
  qreal mapYFromScene(qreal ScenePosY)const;
  inline QPointF mapPointFromScene(const QPointF& point)const;

  QList<ctkPoint> bezierParams(ctkControlPoint* start, ctkControlPoint* end) const;
  QList<ctkPoint> nonLinearPoints(ctkControlPoint* start, ctkControlPoint* end) const;

  const QPainterPath& curve()const;
  const QList<QPointF>& points()const;
  const QGradient& gradient()const;

  void computeCurve();
  void computeGradient();

  QColor verticalGradientColor()const;
  void setVerticalGradientColor(QColor verticalGradientColor);

protected slots:
  virtual void onTransferFunctionChanged();

protected:
  qreal computeRangeXDiff(const QRectF& rect, qreal rangeX[2]);
  qreal computeRangeXOffset(qreal rangeX[2]);
  qreal computeRangeYDiff(const QRectF& rect, const QVariant rangeY[2]);
  qreal computeRangeYOffset(const QVariant rangeY[2]);
private:
  CTK_DECLARE_PRIVATE(ctkTransferFunctionScene);
};

qreal ctkTransferFunctionScene::posX(const ctkControlPoint* cp)const
{
  return this->posX(cp->x());
}
qreal ctkTransferFunctionScene::posY(const ctkControlPoint* cp)const
{
  return this->posY(cp->value());
}
QColor ctkTransferFunctionScene::color(const ctkControlPoint* cp) const
{
  return this->color(cp->value());
}

qreal ctkTransferFunctionScene::posX(const ctkPoint& point)const
{
  return this->posX(point.X);
}
qreal ctkTransferFunctionScene::posY(const ctkPoint& point)const
{
  return this->posY(point.Value);
}
QColor ctkTransferFunctionScene::color(const ctkPoint& point) const
{
  return this->color(point.Value);
}

QPointF ctkTransferFunctionScene::mapPointFromScene(const QPointF& point)const
{
  return QPointF(this->mapXFromScene(point.x()),
                 this->mapYFromScene(point.y()));
}

#endif
