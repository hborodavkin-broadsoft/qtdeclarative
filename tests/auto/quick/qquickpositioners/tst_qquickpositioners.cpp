/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtTest/QtTest>
#include <private/qlistmodelinterface_p.h>
#include <QtQuick/qquickview.h>
#include <qqmlengine.h>
#include <QtQuick/private/qquickrectangle_p.h>
#include <QtQuick/private/qquickpositioners_p.h>
#include <QtQuick/private/qquicktransition_p.h>
#include <private/qquickitem_p.h>
#include <qqmlexpression.h>
#include "../shared/viewtestutil.h"
#include "../shared/visualtestutil.h"
#include "../../shared/util.h"

using namespace QQuickViewTestUtil;
using namespace QQuickVisualTestUtil;

class tst_qquickpositioners : public QQmlDataTest
{
    Q_OBJECT
public:
    tst_qquickpositioners();

private slots:
    void test_horizontal();
    void test_horizontal_rtl();
    void test_horizontal_spacing();
    void test_horizontal_spacing_rightToLeft();
    void test_horizontal_animated();
    void test_horizontal_animated_rightToLeft();
    void test_horizontal_animated_disabled();
    void test_vertical();
    void test_vertical_spacing();
    void test_vertical_animated();
    void test_grid();
    void test_grid_topToBottom();
    void test_grid_rightToLeft();
    void test_grid_spacing();
    void test_grid_row_column_spacing();
    void test_grid_animated();
    void test_grid_animated_rightToLeft();
    void test_grid_zero_columns();
    void test_propertychanges();
    void test_repeater();
    void test_flow();
    void test_flow_rightToLeft();
    void test_flow_topToBottom();
    void test_flow_resize();
    void test_flow_resize_rightToLeft();
    void test_flow_implicit_resize();
    void test_conflictinganchors();
    void test_mirroring();
    void test_allInvisible();
    void test_attachedproperties();
    void test_attachedproperties_data();
    void test_attachedproperties_dynamic();

    void populateTransitions_row();
    void populateTransitions_row_data();
    void populateTransitions_column();
    void populateTransitions_column_data();
    void populateTransitions_grid();
    void populateTransitions_grid_data();
    void populateTransitions_flow();
    void populateTransitions_flow_data();
    void addTransitions_row();
    void addTransitions_row_data();
    void addTransitions_column();
    void addTransitions_column_data();
    void addTransitions_grid();
    void addTransitions_grid_data();
    void addTransitions_flow();
    void addTransitions_flow_data();
    void moveTransitions_row();
    void moveTransitions_row_data();
    void moveTransitions_column();
    void moveTransitions_column_data();
    void moveTransitions_grid();
    void moveTransitions_grid_data();
    void moveTransitions_flow();
    void moveTransitions_flow_data();

private:
    QQuickView *createView(const QString &filename, bool wait=true);

    void populateTransitions(const QString &positionerObjectName);
    void populateTransitions_data();
    void addTransitions(const QString &positionerObjectName);
    void addTransitions_data();
    void moveTransitions(const QString &positionerObjectName);
    void moveTransitions_data();
    void matchIndexLists(const QVariantList &indexLists, const QList<int> &expectedIndexes);
    void matchItemsAndIndexes(const QVariantMap &items, const QaimModel &model, const QList<int> &expectedIndexes);
    void matchItemLists(const QVariantList &itemLists, const QList<QQuickItem *> &expectedItems);
    void checkItemPositions(QQuickItem *positioner, QaimModel *model, qreal incrementalSize);
};

void tst_qquickpositioners::populateTransitions_row()
{
    populateTransitions("row");
}

void tst_qquickpositioners::populateTransitions_row_data()
{
    populateTransitions_data();
}

void tst_qquickpositioners::populateTransitions_column()
{
    populateTransitions("column");
}

void tst_qquickpositioners::populateTransitions_column_data()
{
    populateTransitions_data();
}

void tst_qquickpositioners::populateTransitions_grid()
{
    populateTransitions("grid");
}

void tst_qquickpositioners::populateTransitions_grid_data()
{
    populateTransitions_data();
}

void tst_qquickpositioners::populateTransitions_flow()
{
    populateTransitions("flow");
}

void tst_qquickpositioners::populateTransitions_flow_data()
{
    populateTransitions_data();
}

void tst_qquickpositioners::addTransitions_row()
{
    addTransitions("row");
}

void tst_qquickpositioners::addTransitions_row_data()
{
    addTransitions_data();
}

void tst_qquickpositioners::addTransitions_column()
{
    addTransitions("column");
}

void tst_qquickpositioners::addTransitions_column_data()
{
    addTransitions_data();
}

void tst_qquickpositioners::addTransitions_grid()
{
    addTransitions("grid");
}

void tst_qquickpositioners::addTransitions_grid_data()
{
    // don't use addTransitions_data() because grid displaces items differently
    // (adding items further down the grid can cause displace transitions at
    // previous indexes, since grid is auto-resized to tightly fit all of its items)

    QTest::addColumn<int>("initialItemCount");
    QTest::addColumn<int>("insertionIndex");
    QTest::addColumn<int>("insertionCount");
    QTest::addColumn<ListRange>("expectedDisplacedIndexes");

    QTest::newRow("add one @ start") << 10 << 0 << 1 << ListRange(0, 9);
    QTest::newRow("add one @ middle") << 10 << 5 << 1 << ListRange(3, 3) + ListRange(5, 9);
    QTest::newRow("add one @ end") << 10 << 10 << 1 << ListRange(3, 3) + ListRange(7, 7);

    QTest::newRow("add multiple @ start") << 10 << 0 << 3 << ListRange(0, 9);
    QTest::newRow("add multiple @ middle") << 10 << 5 << 3 << ListRange(1, 3) + ListRange(5, 9);
    QTest::newRow("add multiple @ end") << 10 << 10 << 3 << ListRange(1, 3) + ListRange(5, 7) + ListRange(9, 9);
}

void tst_qquickpositioners::addTransitions_flow()
{
    addTransitions("flow");
}

void tst_qquickpositioners::addTransitions_flow_data()
{
    addTransitions_data();
}

void tst_qquickpositioners::moveTransitions_row()
{
    moveTransitions("row");
}

void tst_qquickpositioners::moveTransitions_row_data()
{
    moveTransitions_data();
}

void tst_qquickpositioners::moveTransitions_column()
{
    moveTransitions("column");
}

void tst_qquickpositioners::moveTransitions_column_data()
{
    moveTransitions_data();
}

void tst_qquickpositioners::moveTransitions_grid()
{
    moveTransitions("grid");
}

void tst_qquickpositioners::moveTransitions_grid_data()
{
    // don't use moveTransitions_data() because grid displaces items differently
    // (removing items further down the grid can cause displace transitions at
    // previous indexes, since grid is auto-resized to tightly fit all of its items)

    QTest::addColumn<int>("initialItemCount");
    QTest::addColumn<ListChange>("change");
    QTest::addColumn<ListRange>("expectedDisplacedIndexes");

    QTest::newRow("remove one @ start") << 10 << ListChange::remove(0, 1) << ListRange(1, 9);
    QTest::newRow("remove one @ middle") << 10 << ListChange::remove(4, 1) << ListRange(2, 3) + ListRange(5, 9);
    QTest::newRow("remove one @ end") << 10 << ListChange::remove(9, 1) << ListRange(2, 3) + ListRange(6, 7);

    QTest::newRow("remove multiple @ start") << 10 << ListChange::remove(0, 3) << ListRange(3, 9);
    QTest::newRow("remove multiple @ middle") << 10 << ListChange::remove(4, 3) << ListRange(1, 3) + ListRange(7, 9);
    QTest::newRow("remove multiple @ end") << 10 << ListChange::remove(7, 3) << ListRange(1, 3) + ListRange(5, 6);
}

void tst_qquickpositioners::moveTransitions_flow()
{
    moveTransitions("flow");
}

void tst_qquickpositioners::moveTransitions_flow_data()
{
    moveTransitions_data();
}

tst_qquickpositioners::tst_qquickpositioners()
{
}

void tst_qquickpositioners::test_horizontal()
{
    QQuickView *canvas = createView(testFile("horizontal.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QCOMPARE(row->width(), 110.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_rtl()
{
    QQuickView *canvas = createView(testFile("horizontal.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 60.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 40.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 0.0);

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QCOMPARE(row->width(), 110.0);
    QCOMPARE(row->height(), 50.0);

    // Change the width of the row and check that items stay to the right
    row->setWidth(200);
    QTRY_COMPARE(one->x(), 150.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 130.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 90.0);
    QCOMPARE(three->y(), 0.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_spacing()
{
    QQuickView *canvas = createView(testFile("horizontal-spacing.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 60.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 90.0);
    QCOMPARE(three->y(), 0.0);

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QCOMPARE(row->width(), 130.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_spacing_rightToLeft()
{
    QQuickView *canvas = createView(testFile("horizontal-spacing.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 80.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 00.0);
    QCOMPARE(three->y(), 0.0);

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QCOMPARE(row->width(), 130.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_animated()
{
    QQuickView *canvas = createView(testFile("horizontal-animated.qml"), false);

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    //Note that they animate in
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(three->x(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QVERIFY(row);
    QCOMPARE(row->width(), 100.0);
    QCOMPARE(row->height(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->x(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);
    QTRY_COMPARE(row->width(), 150.0);
    QTRY_COMPARE(row->height(), 50.0);

    QTest::qWait(0);//Let the animation start
    QVERIFY(two->x() >= -100.0 && two->x() < 50.0);
    QVERIFY(three->x() >= 50.0 && three->x() < 100.0);

    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(three->x(), 100.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_animated_rightToLeft()
{
    QQuickView *canvas = createView(testFile("horizontal-animated.qml"), false);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    //Note that they animate in
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(three->x(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QVERIFY(row);
    QCOMPARE(row->width(), 100.0);
    QCOMPARE(row->height(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->x(), 50.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->x(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 0.0);
    QTRY_COMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);

    // New size should propagate after visible change
    QTRY_COMPARE(row->width(), 150.0);
    QTRY_COMPARE(row->height(), 50.0);

    QTest::qWait(0);//Let the animation start
    QVERIFY(one->x() >= 50.0 && one->x() < 100);
    QVERIFY(two->x() >= -100.0 && two->x() < 50.0);

    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(two->x(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_horizontal_animated_disabled()
{
    QQuickView *canvas = createView(testFile("horizontal-animated-disabled.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QQuickItem *row = canvas->rootObject()->findChild<QQuickItem*>("row");
    QVERIFY(row);

    qApp->processEvents();

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->isVisible(), false);
    QCOMPARE(two->x(), -100.0);//Not 'in' yet
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    QTRY_COMPARE(row->width(), 150.0);
    QTRY_COMPARE(row->height(), 50.0);

    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(three->x(), 100.0);

    delete canvas;
}

void tst_qquickpositioners::populateTransitions(const QString &positionerObjectName)
{
    QFETCH(bool, dynamicallyPopulate);
    QFETCH(bool, usePopulateTransition);

    QPointF targetItems_transitionFrom(-50, -50);
    QPointF displacedItems_transitionVia(100, 100);

    QaimModel model;
    if (!dynamicallyPopulate) {
        for (int i = 0; i < 30; i++)
            model.addItem("Original item" + QString::number(i), "");
    }

    QaimModel model_targetItems_transitionFrom;
    QaimModel model_displacedItems_transitionVia;

    QQuickView *canvas = QQuickViewTestUtil::createView();
    QQmlContext *ctxt = canvas->rootContext();
    ctxt->setContextProperty("usePopulateTransition", usePopulateTransition);
    ctxt->setContextProperty("enableAddTransition", true);
    ctxt->setContextProperty("dynamicallyPopulate", dynamicallyPopulate);
    ctxt->setContextProperty("testModel", &model);
    ctxt->setContextProperty("model_targetItems_transitionFrom", &model_targetItems_transitionFrom);
    ctxt->setContextProperty("model_displacedItems_transitionVia", &model_displacedItems_transitionVia);
    ctxt->setContextProperty("targetItems_transitionFrom", targetItems_transitionFrom);
    ctxt->setContextProperty("displacedItems_transitionVia", displacedItems_transitionVia);
    ctxt->setContextProperty("testedPositioner", positionerObjectName);
    canvas->setSource(testFileUrl("transitions.qml"));

    QQuickItem *positioner = canvas->rootObject()->findChild<QQuickItem*>(positionerObjectName);
    QVERIFY(positioner);
    canvas->show();
    qApp->processEvents();

    if (!dynamicallyPopulate && usePopulateTransition) {
        QTRY_COMPARE(canvas->rootObject()->property("populateTransitionsDone").toInt(), model.count());
        QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), 0);

        QList<QPair<QString, QString> > targetData;
        QList<int> targetIndexes;
        for (int i=0; i<model.count(); i++) {
            targetData << qMakePair(model.name(i), model.number(i));
            targetIndexes << i;
        }
        QList<QQuickItem *> targetItems = findItems<QQuickItem>(positioner, "wrapper", targetIndexes);
        model_targetItems_transitionFrom.matchAgainst(targetData, "wasn't animated from target 'from' pos", "shouldn't have been animated from target 'from' pos");
        matchItemsAndIndexes(canvas->rootObject()->property("targetTrans_items").toMap(), model, targetIndexes);
        matchIndexLists(canvas->rootObject()->property("targetTrans_targetIndexes").toList(), targetIndexes);
        matchItemLists(canvas->rootObject()->property("targetTrans_targetItems").toList(), targetItems);

    } else if (dynamicallyPopulate) {
        QTRY_COMPARE(canvas->rootObject()->property("populateTransitionsDone").toInt(), 0);
        QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), model.count());
    } else {
        QTRY_COMPARE(QQuickItemPrivate::get(positioner)->polishScheduled, false);
        QTRY_COMPARE(canvas->rootObject()->property("populateTransitionsDone").toInt(), 0);
        QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), 0);
    }

    checkItemPositions(positioner, &model, canvas->rootObject()->property("incrementalSize").toInt());

    // add an item and check this is done with add transition, not populate
    canvas->rootObject()->setProperty("populateTransitionsDone", 0);
    canvas->rootObject()->setProperty("addTransitionsDone", 0);
    model.insertItem(0, "new item", "");
    QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), 1);
    QTRY_COMPARE(canvas->rootObject()->property("populateTransitionsDone").toInt(), 0);

    delete canvas;
}

void tst_qquickpositioners::populateTransitions_data()
{
    QTest::addColumn<bool>("dynamicallyPopulate");
    QTest::addColumn<bool>("usePopulateTransition");

    QTest::newRow("statically populate") << false << true;
    QTest::newRow("statically populate, no populate transition") << false << false;

    QTest::newRow("dynamically populate") << true << true;
    QTest::newRow("dynamically populate, no populate transition") << true << false;
}

void tst_qquickpositioners::addTransitions(const QString &positionerObjectName)
{
    QFETCH(int, initialItemCount);
    QFETCH(int, insertionIndex);
    QFETCH(int, insertionCount);
    QFETCH(ListRange, expectedDisplacedIndexes);

    QPointF targetItems_transitionFrom(-50, -50);
    QPointF displacedItems_transitionVia(100, 100);

    QaimModel model;
    QaimModel model_targetItems_transitionFrom;
    QaimModel model_displacedItems_transitionVia;

    QQuickView *canvas = QQuickViewTestUtil::createView();
    QQmlContext *ctxt = canvas->rootContext();
    ctxt->setContextProperty("usePopulateTransition", false);
    ctxt->setContextProperty("enableAddTransition", true);
    ctxt->setContextProperty("model_targetItems_transitionFrom", &model_targetItems_transitionFrom);
    ctxt->setContextProperty("model_displacedItems_transitionVia", &model_displacedItems_transitionVia);
    ctxt->setContextProperty("targetItems_transitionFrom", targetItems_transitionFrom);
    ctxt->setContextProperty("displacedItems_transitionVia", displacedItems_transitionVia);
    canvas->setSource(testFileUrl("transitions.qml"));
    canvas->show();
    qApp->processEvents();

    QQuickItem *positioner = canvas->rootObject()->findChild<QQuickItem*>(positionerObjectName);
    QVERIFY(positioner);
    positioner->findChild<QQuickItem*>("repeater")->setProperty("model", QVariant::fromValue(&model));
    QTRY_COMPARE(QQuickItemPrivate::get(positioner)->polishScheduled, false);

    for (int i = 0; i < initialItemCount; i++)
        model.addItem("Original item" + QString::number(i), "");

    QList<QPair<QString,QString> > expectedDisplacedValues = expectedDisplacedIndexes.getModelDataValues(model);
    QList<QPair<QString, QString> > targetData;
    QList<int> targetIndexes;
    for (int i=0; i<model.count(); i++) {
        targetData << qMakePair(model.name(i), model.number(i));
        targetIndexes << i;
    }
    QList<QQuickItem *> targetItems = findItems<QQuickItem>(positioner, "wrapper", targetIndexes);

    // check add transition was run for first lot of added items
    QTRY_COMPARE(canvas->rootObject()->property("populateTransitionsDone").toInt(), 0);
    QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), initialItemCount);
    QTRY_COMPARE(canvas->rootObject()->property("displaceTransitionsDone").toInt(), 0);
    model_targetItems_transitionFrom.matchAgainst(targetData, "wasn't animated from target 'from' pos", "shouldn't have been animated from target 'from' pos");
    matchItemsAndIndexes(canvas->rootObject()->property("targetTrans_items").toMap(), model, targetIndexes);
    matchIndexLists(canvas->rootObject()->property("targetTrans_targetIndexes").toList(), targetIndexes);
    matchItemLists(canvas->rootObject()->property("targetTrans_targetItems").toList(), targetItems);

    model_targetItems_transitionFrom.clear();
    canvas->rootObject()->setProperty("addTransitionsDone", 0);
    canvas->rootObject()->setProperty("targetTrans_items", QVariantMap());
    canvas->rootObject()->setProperty("targetTrans_targetIndexes", QVariantList());
    canvas->rootObject()->setProperty("targetTrans_targetItems", QVariantList());

    // do insertion
    targetData.clear();
    targetIndexes.clear();
    for (int i=insertionIndex; i<insertionIndex+insertionCount; i++) {
        targetData << qMakePair(QString("New item %1").arg(i), QString(""));
        targetIndexes << i;
    }
    model.insertItems(insertionIndex, targetData);
    QTRY_COMPARE(model.count(), positioner->property("count").toInt());

    targetItems = findItems<QQuickItem>(positioner, "wrapper", targetIndexes);

    QTRY_COMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), targetData.count());
    QTRY_COMPARE(canvas->rootObject()->property("displaceTransitionsDone").toInt(), expectedDisplacedIndexes.count());

    // check the target and displaced items were animated
    model_targetItems_transitionFrom.matchAgainst(targetData, "wasn't animated from target 'from' pos", "shouldn't have been animated from target 'from' pos");
    model_displacedItems_transitionVia.matchAgainst(expectedDisplacedValues, "wasn't animated with displaced anim", "shouldn't have been animated with displaced anim");

    // check attached properties
    matchItemsAndIndexes(canvas->rootObject()->property("targetTrans_items").toMap(), model, targetIndexes);
    matchIndexLists(canvas->rootObject()->property("targetTrans_targetIndexes").toList(), targetIndexes);
    matchItemLists(canvas->rootObject()->property("targetTrans_targetItems").toList(), targetItems);
    if (expectedDisplacedIndexes.isValid()) {
        // adjust expectedDisplacedIndexes to their final values after the move
        QList<int> displacedIndexes = adjustIndexesForAddDisplaced(expectedDisplacedIndexes.indexes, insertionIndex, insertionCount);
        matchItemsAndIndexes(canvas->rootObject()->property("displacedTrans_items").toMap(), model, displacedIndexes);
        matchIndexLists(canvas->rootObject()->property("displacedTrans_targetIndexes").toList(), targetIndexes);
        matchItemLists(canvas->rootObject()->property("displacedTrans_targetItems").toList(), targetItems);
    }

    checkItemPositions(positioner, &model, canvas->rootObject()->property("incrementalSize").toInt());

    delete canvas;
}

void tst_qquickpositioners::addTransitions_data()
{
    // If this data changes, update addTransitions_grid_data() also

    QTest::addColumn<int>("initialItemCount");
    QTest::addColumn<int>("insertionIndex");
    QTest::addColumn<int>("insertionCount");
    QTest::addColumn<ListRange>("expectedDisplacedIndexes");

    QTest::newRow("add one @ start") << 10 << 0 << 1 << ListRange(0, 9);
    QTest::newRow("add one @ middle") << 10 << 5 << 1 << ListRange(5, 9);
    QTest::newRow("add one @ end") << 10 << 10 << 1 << ListRange();

    QTest::newRow("add multiple @ start") << 10 << 0 << 3 << ListRange(0, 9);
    QTest::newRow("add multiple @ middle") << 10 << 5 << 3 << ListRange(5, 9);
    QTest::newRow("add multiple @ end") << 10 << 10 << 3 << ListRange();
}

void tst_qquickpositioners::moveTransitions(const QString &positionerObjectName)
{
    QFETCH(int, initialItemCount);
    QFETCH(ListChange, change);
    QFETCH(ListRange, expectedDisplacedIndexes);

    QPointF targetItems_transitionFrom(-50, -50);
    QPointF displacedItems_transitionVia(100, 100);

    QaimModel model;
    for (int i = 0; i < initialItemCount; i++)
        model.addItem("Item" + QString::number(i), "");
    QaimModel model_targetItems_transitionFrom;
    QaimModel model_displacedItems_transitionVia;

    QQuickView *canvas = QQuickViewTestUtil::createView();
    QQmlContext *ctxt = canvas->rootContext();
    ctxt->setContextProperty("usePopulateTransition", false);
    ctxt->setContextProperty("enableAddTransition", QVariant(false));
    ctxt->setContextProperty("model_targetItems_transitionFrom", &model_targetItems_transitionFrom);
    ctxt->setContextProperty("model_displacedItems_transitionVia", &model_displacedItems_transitionVia);
    ctxt->setContextProperty("targetItems_transitionFrom", targetItems_transitionFrom);
    ctxt->setContextProperty("displacedItems_transitionVia", displacedItems_transitionVia);
    canvas->setSource(testFileUrl("transitions.qml"));
    canvas->show();
    qApp->processEvents();

    QList<QPair<QString,QString> > expectedDisplacedValues = expectedDisplacedIndexes.getModelDataValues(model);

    QQuickItem *positioner = canvas->rootObject()->findChild<QQuickItem*>(positionerObjectName);
    QVERIFY(positioner);
    positioner->findChild<QQuickItem*>("repeater")->setProperty("model", QVariant::fromValue(&model));
    QTRY_COMPARE(QQuickItemPrivate::get(positioner)->polishScheduled, false);

    switch (change.type) {
        case ListChange::Removed:
            model.removeItems(change.index, change.count);
            QTRY_COMPARE(model.count(), positioner->property("count").toInt());
            break;
        case ListChange::Moved:
            model.moveItems(change.index, change.to, change.count);
            QTRY_COMPARE(QQuickItemPrivate::get(positioner)->polishScheduled, false);
            break;
        case ListChange::Inserted:
        case ListChange::SetCurrent:
        case ListChange::SetContentY:
            QVERIFY(false);
            break;
    }

    QTRY_COMPARE(canvas->rootObject()->property("displaceTransitionsDone").toInt(), expectedDisplacedIndexes.count());
    QCOMPARE(canvas->rootObject()->property("addTransitionsDone").toInt(), 0);

    // check the target and displaced items were animated
    QCOMPARE(model_targetItems_transitionFrom.count(), 0);
    model_displacedItems_transitionVia.matchAgainst(expectedDisplacedValues, "wasn't animated with displaced anim", "shouldn't have been animated with displaced anim");

    // check attached properties
    QCOMPARE(canvas->rootObject()->property("targetTrans_items").toMap().count(), 0);
    QCOMPARE(canvas->rootObject()->property("targetTrans_targetIndexes").toList().count(), 0);
    QCOMPARE(canvas->rootObject()->property("targetTrans_targetItems").toList().count(), 0);
    if (expectedDisplacedIndexes.isValid()) {
        // adjust expectedDisplacedIndexes to their final values after the move
        QList<int> displacedIndexes;
        if (change.type == ListChange::Inserted)
            displacedIndexes = adjustIndexesForAddDisplaced(expectedDisplacedIndexes.indexes, change.index, change.count);
        else if (change.type == ListChange::Moved)
            displacedIndexes = adjustIndexesForMove(expectedDisplacedIndexes.indexes, change.index, change.to, change.count);
        else if (change.type == ListChange::Removed)
            displacedIndexes = adjustIndexesForRemoveDisplaced(expectedDisplacedIndexes.indexes, change.index, change.count);
        else
            QVERIFY(false);
        matchItemsAndIndexes(canvas->rootObject()->property("displacedTrans_items").toMap(), model, displacedIndexes);

        QVariantList listOfEmptyIntLists;
        for (int i=0; i<displacedIndexes.count(); i++)
            listOfEmptyIntLists << QVariant::fromValue(QList<int>());
        QCOMPARE(canvas->rootObject()->property("displacedTrans_targetIndexes").toList(), listOfEmptyIntLists);
        QVariantList listOfEmptyObjectLists;
        for (int i=0; i<displacedIndexes.count(); i++)
            listOfEmptyObjectLists.insert(listOfEmptyObjectLists.count(), QVariantList());
        QCOMPARE(canvas->rootObject()->property("displacedTrans_targetItems").toList(), listOfEmptyObjectLists);
    }

    checkItemPositions(positioner, &model, canvas->rootObject()->property("incrementalSize").toInt());

    delete canvas;
}

void tst_qquickpositioners::moveTransitions_data()
{
    // If this data changes, update moveTransitions_grid_data() also

    QTest::addColumn<int>("initialItemCount");
    QTest::addColumn<ListChange>("change");
    QTest::addColumn<ListRange>("expectedDisplacedIndexes");

    QTest::newRow("remove one @ start") << 10 << ListChange::remove(0, 1) << ListRange(1, 9);
    QTest::newRow("remove one @ middle") << 10 << ListChange::remove(4, 1) << ListRange(5, 9);
    QTest::newRow("remove one @ end") << 10 << ListChange::remove(9, 1) << ListRange();

    QTest::newRow("remove multiple @ start") << 10 << ListChange::remove(0, 3) << ListRange(3, 9);
    QTest::newRow("remove multiple @ middle") << 10 << ListChange::remove(4, 3) << ListRange(7, 9);
    QTest::newRow("remove multiple @ end") << 10 << ListChange::remove(7, 3) << ListRange();
}


void tst_qquickpositioners::checkItemPositions(QQuickItem *positioner, QaimModel *model, qreal incrementalSize)
{
    QVERIFY(model->count() > 0);
    qreal padding = 0;
    qreal currentSize = 30;
    qreal rowX = 0;
    qreal rowY = 0;

    for (int i=0; i<model->count(); ++i) {
        QQuickItem *item = findItem<QQuickItem>(positioner, "wrapper", i);
        QVERIFY2(item, QTest::toString(QString("Item %1 not found").arg(i)));

        QCOMPARE(item->width(), currentSize);
        QCOMPARE(item->height(), currentSize);

        if (qobject_cast<QQuickRow*>(positioner)) {
            QCOMPARE(item->x(), (i * 30.0) + padding);
            QCOMPARE(item->y(), 0.0);
        } else if (qobject_cast<QQuickColumn*>(positioner)) {
            QCOMPARE(item->x(), 0.0);
            QCOMPARE(item->y(), (i * 30.0) + padding);
        } else if (qobject_cast<QQuickGrid*>(positioner)) {
            int columns = 4;
            int rows = qCeil(model->count() / qreal(columns));
            int lastMatchingRowIndex = (rows * columns) - (columns - i%columns);
            if (lastMatchingRowIndex >= model->count())
                lastMatchingRowIndex -= columns;
            if (i % columns > 0) {
                QQuickItem *finalAlignedRowItem = findItem<QQuickItem>(positioner, "wrapper", lastMatchingRowIndex);
                QVERIFY(finalAlignedRowItem);
                QCOMPARE(item->x(), finalAlignedRowItem->x());
            } else {
                QCOMPARE(item->x(), 0.0);
            }
            if (i / columns > 0) {
                QQuickItem *prevRowLastItem = findItem<QQuickItem>(positioner, "wrapper", (i/columns * columns) - 1);
                QVERIFY(prevRowLastItem);
                QCOMPARE(item->y(), prevRowLastItem->y() + prevRowLastItem->height());
            } else {
                QCOMPARE(item->y(), 0.0);
            }
        } else if (qobject_cast<QQuickFlow*>(positioner)) {
            if (rowX + item->width() > positioner->width()) {
                QQuickItem *prevItem = findItem<QQuickItem>(positioner, "wrapper", i-1);
                QVERIFY(prevItem);
                rowX = 0;
                rowY = prevItem->y() + prevItem->height();
            }
            QCOMPARE(item->x(), rowX);
            QCOMPARE(item->y(), rowY);
            rowX += item->width();
        } else {
            QVERIFY2(false, "Unknown positioner type");
        }
        QQuickText *name = findItem<QQuickText>(positioner, "name", i);
        QVERIFY(name != 0);
        QTRY_COMPARE(name->text(), model->name(i));

        padding += i * incrementalSize;
        currentSize += incrementalSize;
    }
}

void tst_qquickpositioners::test_vertical()
{
    QQuickView *canvas = createView(testFile("vertical.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 50.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 60.0);

    QQuickItem *column = canvas->rootObject()->findChild<QQuickItem*>("column");
    QVERIFY(column);
    QCOMPARE(column->height(), 80.0);
    QCOMPARE(column->width(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_vertical_spacing()
{
    QQuickView *canvas = createView(testFile("vertical-spacing.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 60.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 80.0);

    QQuickItem *column = canvas->rootObject()->findChild<QQuickItem*>("column");
    QCOMPARE(column->height(), 100.0);
    QCOMPARE(column->width(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_vertical_animated()
{
    QQuickView *canvas = createView(testFile("vertical-animated.qml"), false);

    //Note that they animate in
    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->y(), -100.0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->y(), -100.0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QQuickItem *column = canvas->rootObject()->findChild<QQuickItem*>("column");
    QVERIFY(column);
    QCOMPARE(column->height(), 100.0);
    QCOMPARE(column->width(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->x(), 0.0);
    QTRY_COMPARE(three->y(), 50.0);
    QTRY_COMPARE(three->x(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);
    QTRY_COMPARE(column->height(), 150.0);
    QTRY_COMPARE(column->width(), 50.0);
    QTest::qWait(0);//Let the animation start
    QVERIFY(two->y() >= -100.0 && two->y() < 50.0);
    QVERIFY(three->y() >= 50.0 && three->y() < 100.0);

    QTRY_COMPARE(two->y(), 50.0);
    QTRY_COMPARE(three->y(), 100.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid()
{
    QQuickView *canvas = createView(testFile("gridtest.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 50.0);

    QQuickGrid *grid = canvas->rootObject()->findChild<QQuickGrid*>("grid");
    QCOMPARE(grid->flow(), QQuickGrid::LeftToRight);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 100.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_topToBottom()
{
    QQuickView *canvas = createView(testFile("grid-toptobottom.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 50.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 100.0);
    QCOMPARE(four->x(), 50.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 50.0);

    QQuickGrid *grid = canvas->rootObject()->findChild<QQuickGrid*>("grid");
    QCOMPARE(grid->flow(), QQuickGrid::TopToBottom);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 120.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_rightToLeft()
{
    QQuickView *canvas = createView(testFile("gridtest.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 50.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 30.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 50.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 40.0);
    QCOMPARE(five->y(), 50.0);

    QQuickGrid *grid = canvas->rootObject()->findChild<QQuickGrid*>("grid");
    QCOMPARE(grid->layoutDirection(), Qt::RightToLeft);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 100.0);

    // Change the width of the grid and check that items stay to the right
    grid->setWidth(200);
    QTRY_COMPARE(one->x(), 150.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 130.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 100.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 150.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 140.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_spacing()
{
    QQuickView *canvas = createView(testFile("grid-spacing.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 54.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 78.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 54.0);
    QCOMPARE(five->x(), 54.0);
    QCOMPARE(five->y(), 54.0);

    QQuickItem *grid = canvas->rootObject()->findChild<QQuickItem*>("grid");
    QCOMPARE(grid->width(), 128.0);
    QCOMPARE(grid->height(), 104.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_row_column_spacing()
{
    QQuickView *canvas = createView(testFile("grid-row-column-spacing.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 61.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 92.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 57.0);
    QCOMPARE(five->x(), 61.0);
    QCOMPARE(five->y(), 57.0);

    QQuickItem *grid = canvas->rootObject()->findChild<QQuickItem*>("grid");
    QCOMPARE(grid->width(), 142.0);
    QCOMPARE(grid->height(), 107.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_animated()
{
    QQuickView *canvas = createView(testFile("grid-animated.qml"), false);

    canvas->rootObject()->setProperty("testRightToLeft", false);

    //Note that all animate in
    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(one->y(), -100.0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->x(), -100.0);
    QCOMPARE(three->y(), -100.0);

    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QCOMPARE(four->x(), -100.0);
    QCOMPARE(four->y(), -100.0);

    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);
    QCOMPARE(five->x(), -100.0);
    QCOMPARE(five->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QQuickItem *grid = canvas->rootObject()->findChild<QQuickItem*>("grid");
    QVERIFY(grid);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);
    QTRY_COMPARE(two->x(), -100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(four->y(), 0.0);
    QTRY_COMPARE(four->x(), 100.0);
    QTRY_COMPARE(five->y(), 50.0);
    QTRY_COMPARE(five->x(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);
    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);
    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 100.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 0.0);
    QCOMPARE(five->y(), 50.0);
    //Let the animation complete
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(three->x(), 100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_animated_rightToLeft()
{
    QQuickView *canvas = createView(testFile("grid-animated.qml"), false);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    //Note that all animate in
    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(one->y(), -100.0);

    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);

    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->x(), -100.0);
    QCOMPARE(three->y(), -100.0);

    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QCOMPARE(four->x(), -100.0);
    QCOMPARE(four->y(), -100.0);

    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);
    QCOMPARE(five->x(), -100.0);
    QCOMPARE(five->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QQuickItem *grid = canvas->rootObject()->findChild<QQuickItem*>("grid");
    QVERIFY(grid);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);
    QTRY_COMPARE(two->x(), -100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(four->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(five->y(), 50.0);
    QTRY_COMPARE(five->x(), 100.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);
    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);
    QCOMPARE(one->x(), 100.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 100.0);
    QCOMPARE(five->y(), 50.0);
    //Let the animation complete
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(three->x(), 0.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 100.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_grid_zero_columns()
{
    QQuickView *canvas = createView(testFile("gridzerocolumns.qml"));

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 120.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 0.0);
    QCOMPARE(five->y(), 50.0);

    QQuickItem *grid = canvas->rootObject()->findChild<QQuickItem*>("grid");
    QCOMPARE(grid->width(), 170.0);
    QCOMPARE(grid->height(), 60.0);

    delete canvas;
}

void tst_qquickpositioners::test_propertychanges()
{
    QQuickView *canvas = createView(testFile("propertychangestest.qml"));

    QQuickGrid *grid = qobject_cast<QQuickGrid*>(canvas->rootObject());
    QVERIFY(grid != 0);
    QQuickTransition *rowTransition = canvas->rootObject()->findChild<QQuickTransition*>("rowTransition");
    QQuickTransition *columnTransition = canvas->rootObject()->findChild<QQuickTransition*>("columnTransition");

    QSignalSpy addSpy(grid, SIGNAL(addChanged()));
    QSignalSpy moveSpy(grid, SIGNAL(moveChanged()));
    QSignalSpy columnsSpy(grid, SIGNAL(columnsChanged()));
    QSignalSpy rowsSpy(grid, SIGNAL(rowsChanged()));

    QVERIFY(grid);
    QVERIFY(rowTransition);
    QVERIFY(columnTransition);
    QCOMPARE(grid->add(), columnTransition);
    QCOMPARE(grid->move(), columnTransition);
    QCOMPARE(grid->columns(), 4);
    QCOMPARE(grid->rows(), -1);

    grid->setAdd(rowTransition);
    grid->setMove(rowTransition);
    QCOMPARE(grid->add(), rowTransition);
    QCOMPARE(grid->move(), rowTransition);
    QCOMPARE(addSpy.count(),1);
    QCOMPARE(moveSpy.count(),1);

    grid->setAdd(rowTransition);
    grid->setMove(rowTransition);
    QCOMPARE(addSpy.count(),1);
    QCOMPARE(moveSpy.count(),1);

    grid->setAdd(0);
    grid->setMove(0);
    QCOMPARE(addSpy.count(),2);
    QCOMPARE(moveSpy.count(),2);

    grid->setColumns(-1);
    grid->setRows(3);
    QCOMPARE(grid->columns(), -1);
    QCOMPARE(grid->rows(), 3);
    QCOMPARE(columnsSpy.count(),1);
    QCOMPARE(rowsSpy.count(),1);

    grid->setColumns(-1);
    grid->setRows(3);
    QCOMPARE(columnsSpy.count(),1);
    QCOMPARE(rowsSpy.count(),1);

    grid->setColumns(2);
    grid->setRows(2);
    QCOMPARE(columnsSpy.count(),2);
    QCOMPARE(rowsSpy.count(),2);

    delete canvas;
}

void tst_qquickpositioners::test_repeater()
{
    QQuickView *canvas = createView(testFile("repeatertest.qml"));

    QQuickRectangle *one = findItem<QQuickRectangle>(canvas->rootItem(), "one");
    QVERIFY(one != 0);

    QQuickRectangle *two = findItem<QQuickRectangle>(canvas->rootItem(), "two");
    QVERIFY(two != 0);

    QQuickRectangle *three = findItem<QQuickRectangle>(canvas->rootItem(), "three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 100.0);
    QCOMPARE(three->y(), 0.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow()
{
    QQuickView *canvas = createView(testFile("flowtest.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 70.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 70.0);

    QQuickItem *flow = canvas->rootObject()->findChild<QQuickItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->width(), 90.0);
    QCOMPARE(flow->height(), 120.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow_rightToLeft()
{
    QQuickView *canvas = createView(testFile("flowtest.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 40.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 20.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 40.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 40.0);
    QCOMPARE(four->y(), 70.0);
    QCOMPARE(five->x(), 30.0);
    QCOMPARE(five->y(), 70.0);

    QQuickItem *flow = canvas->rootObject()->findChild<QQuickItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->width(), 90.0);
    QCOMPARE(flow->height(), 120.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow_topToBottom()
{
    QQuickView *canvas = createView(testFile("flowtest-toptobottom.qml"));

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 100.0);
    QCOMPARE(four->y(), 00.0);
    QCOMPARE(five->x(), 100.0);
    QCOMPARE(five->y(), 50.0);

    QQuickItem *flow = canvas->rootObject()->findChild<QQuickItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->height(), 90.0);
    QCOMPARE(flow->width(), 150.0);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QVERIFY(flow);
    QCOMPARE(flow->height(), 90.0);
    QCOMPARE(flow->width(), 150.0);

    QCOMPARE(one->x(), 100.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 80.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 40.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow_resize()
{
    QQuickView *canvas = createView(testFile("flowtest.qml"));

    QQuickItem *root = qobject_cast<QQuickItem*>(canvas->rootObject());
    QVERIFY(root);
    root->setWidth(125);
    root->setProperty("testRightToLeft", false);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QVERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 70.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow_resize_rightToLeft()
{
    QQuickView *canvas = createView(testFile("flowtest.qml"));

    QQuickItem *root = qobject_cast<QQuickItem*>(canvas->rootObject());
    QVERIFY(root);
    root->setWidth(125);
    root->setProperty("testRightToLeft", true);

    QQuickRectangle *one = canvas->rootObject()->findChild<QQuickRectangle*>("one");
    QTRY_VERIFY(one != 0);
    QQuickRectangle *two = canvas->rootObject()->findChild<QQuickRectangle*>("two");
    QVERIFY(two != 0);
    QQuickRectangle *three = canvas->rootObject()->findChild<QQuickRectangle*>("three");
    QVERIFY(three != 0);
    QQuickRectangle *four = canvas->rootObject()->findChild<QQuickRectangle*>("four");
    QVERIFY(four != 0);
    QQuickRectangle *five = canvas->rootObject()->findChild<QQuickRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 75.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 55.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 5.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 75.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 65.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qquickpositioners::test_flow_implicit_resize()
{
    QQuickView *canvas = createView(testFile("flow-testimplicitsize.qml"));
    QVERIFY(canvas->rootObject() != 0);

    QQuickFlow *flow = canvas->rootObject()->findChild<QQuickFlow*>("flow");
    QVERIFY(flow != 0);

    QCOMPARE(flow->width(), 100.0);
    QCOMPARE(flow->height(), 120.0);

    canvas->rootObject()->setProperty("flowLayout", 0);
    QCOMPARE(flow->flow(), QQuickFlow::LeftToRight);
    QCOMPARE(flow->width(), 220.0);
    QCOMPARE(flow->height(), 50.0);

    canvas->rootObject()->setProperty("flowLayout", 1);
    QCOMPARE(flow->flow(), QQuickFlow::TopToBottom);
    QCOMPARE(flow->width(), 100.0);
    QCOMPARE(flow->height(), 120.0);

    canvas->rootObject()->setProperty("flowLayout", 2);
    QCOMPARE(flow->layoutDirection(), Qt::RightToLeft);
    QCOMPARE(flow->width(), 220.0);
    QCOMPARE(flow->height(), 50.0);

    delete canvas;
}

QString warningMessage;

void interceptWarnings(QtMsgType type, const char *msg)
{
    Q_UNUSED( type );
    warningMessage = msg;
}

void tst_qquickpositioners::test_conflictinganchors()
{
    QtMsgHandler oldMsgHandler = qInstallMsgHandler(interceptWarnings);
    QQmlEngine engine;
    QQmlComponent component(&engine);

    component.setData("import QtQuick 2.0\nColumn { Item { width: 100; height: 100; } }", QUrl::fromLocalFile(""));
    QQuickItem *item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { width: 100; height: 100; } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item { width: 100; height: 100; } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nFlow { Item { width: 100; height: 100; } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { width: 100; height: 100; anchors.top: parent.top } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Column: Cannot specify top, bottom, verticalCenter, fill or centerIn anchors for items inside Column. Column will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { width: 100; height: 100; anchors.centerIn: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Column: Cannot specify top, bottom, verticalCenter, fill or centerIn anchors for items inside Column. Column will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { width: 100; height: 100; anchors.left: parent.left } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { width: 100; height: 100; anchors.left: parent.left } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Row: Cannot specify left, right, horizontalCenter, fill or centerIn anchors for items inside Row. Row will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { width: 100; height: 100; Item { anchors.fill: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Row: Cannot specify left, right, horizontalCenter, fill or centerIn anchors for items inside Row. Row will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { width: 100; height: 100; anchors.top: parent.top } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item { width: 100; height: 100; anchors.horizontalCenter: parent.horizontalCenter } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Grid: Cannot specify anchors for items inside Grid. Grid will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item { width: 100; height: 100; anchors.centerIn: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Grid: Cannot specify anchors for items inside Grid. Grid will not function."));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nFlow { Item { width: 100; height: 100; anchors.verticalCenter: parent.verticalCenter } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Flow: Cannot specify anchors for items inside Flow. Flow will not function."));
    delete item;

    component.setData("import QtQuick 2.0\nFlow {  width: 100; height: 100; Item { anchors.fill: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QQuickItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Flow: Cannot specify anchors for items inside Flow. Flow will not function."));
    qInstallMsgHandler(oldMsgHandler);
    delete item;
}

void tst_qquickpositioners::test_mirroring()
{
    QList<QString> qmlFiles;
    qmlFiles << "horizontal.qml" << "gridtest.qml" << "flowtest.qml";
    QList<QString> objectNames;
    objectNames << "one" << "two" << "three" << "four" << "five";

    foreach (const QString qmlFile, qmlFiles) {
        QQuickView *canvasA = createView(testFile(qmlFile));
        QQuickItem *rootA = qobject_cast<QQuickItem*>(canvasA->rootObject());

        QQuickView *canvasB = createView(testFile(qmlFile));
        QQuickItem *rootB = qobject_cast<QQuickItem*>(canvasB->rootObject());

        rootA->setProperty("testRightToLeft", true); // layoutDirection: Qt.RightToLeft

        // LTR != RTL
        foreach (const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QQuickItem *itemA = rootA->findChild<QQuickItem*>(objectName);
            QQuickItem *itemB = rootB->findChild<QQuickItem*>(objectName);
            QTRY_VERIFY(itemA->x() != itemB->x());
        }

        QQmlProperty enabledProp(rootB, "LayoutMirroring.enabled", qmlContext(rootB));
        enabledProp.write(true);
        QQmlProperty inheritProp(rootB, "LayoutMirroring.childrenInherit", qmlContext(rootB));
        inheritProp.write(true);

        // RTL == mirror
        foreach (const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QQuickItem *itemA = rootA->findChild<QQuickItem*>(objectName);
            QQuickItem *itemB = rootB->findChild<QQuickItem*>(objectName);
            QTRY_COMPARE(itemA->x(), itemB->x());
        }

        rootA->setProperty("testRightToLeft", false); // layoutDirection: Qt.LeftToRight
        rootB->setProperty("testRightToLeft", true); // layoutDirection: Qt.RightToLeft

        // LTR == RTL + mirror
        foreach (const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QQuickItem *itemA = rootA->findChild<QQuickItem*>(objectName);
            QQuickItem *itemB = rootB->findChild<QQuickItem*>(objectName);
            QTRY_COMPARE(itemA->x(), itemB->x());
        }
        delete canvasA;
        delete canvasB;
    }
}

void tst_qquickpositioners::test_allInvisible()
{
    //QTBUG-19361
    QQuickView *canvas = createView(testFile("allInvisible.qml"));

    QQuickItem *root = qobject_cast<QQuickItem*>(canvas->rootObject());
    QVERIFY(root);

    QQuickRow *row = canvas->rootObject()->findChild<QQuickRow*>("row");
    QVERIFY(row != 0);
    QVERIFY(row->width() == 0);
    QVERIFY(row->height() == 0);
    QQuickColumn *column = canvas->rootObject()->findChild<QQuickColumn*>("column");
    QVERIFY(column != 0);
    QVERIFY(column->width() == 0);
    QVERIFY(column->height() == 0);
}

void tst_qquickpositioners::test_attachedproperties()
{
    QFETCH(QString, filename);

    QQuickView *canvas = createView(filename);
    QVERIFY(canvas->rootObject() != 0);

    QQuickRectangle *greenRect = canvas->rootObject()->findChild<QQuickRectangle *>("greenRect");
    QVERIFY(greenRect != 0);

    int posIndex = greenRect->property("posIndex").toInt();
    QVERIFY(posIndex == 0);
    bool isFirst = greenRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == true);
    bool isLast = greenRect->property("isLastItem").toBool();
    QVERIFY(isLast == false);

    QQuickRectangle *yellowRect = canvas->rootObject()->findChild<QQuickRectangle *>("yellowRect");
    QVERIFY(yellowRect != 0);

    posIndex = yellowRect->property("posIndex").toInt();
    QVERIFY(posIndex == -1);
    isFirst = yellowRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = yellowRect->property("isLastItem").toBool();
    QVERIFY(isLast == false);

    yellowRect->metaObject()->invokeMethod(yellowRect, "onDemandPositioner");

    posIndex = yellowRect->property("posIndex").toInt();
    QVERIFY(posIndex == 1);
    isFirst = yellowRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = yellowRect->property("isLastItem").toBool();
    QVERIFY(isLast == true);

    delete canvas;
}

void tst_qquickpositioners::test_attachedproperties_data()
{
    QTest::addColumn<QString>("filename");

    QTest::newRow("column") << testFile("attachedproperties-column.qml");
    QTest::newRow("row") << testFile("attachedproperties-row.qml");
    QTest::newRow("grid") << testFile("attachedproperties-grid.qml");
    QTest::newRow("flow") << testFile("attachedproperties-flow.qml");
}

void tst_qquickpositioners::test_attachedproperties_dynamic()
{
    QQuickView *canvas = createView(testFile("attachedproperties-dynamic.qml"));
    QVERIFY(canvas->rootObject() != 0);

    QQuickRow *row = canvas->rootObject()->findChild<QQuickRow *>("pos");
    QVERIFY(row != 0);

    QQuickRectangle *rect0 = canvas->rootObject()->findChild<QQuickRectangle *>("rect0");
    QVERIFY(rect0 != 0);

    int posIndex = rect0->property("index").toInt();
    QVERIFY(posIndex == 0);
    bool isFirst = rect0->property("firstItem").toBool();
    QVERIFY(isFirst == true);
    bool isLast = rect0->property("lastItem").toBool();
    QVERIFY(isLast == false);

    QQuickRectangle *rect1 = canvas->rootObject()->findChild<QQuickRectangle *>("rect1");
    QVERIFY(rect1 != 0);

    posIndex = rect1->property("index").toInt();
    QVERIFY(posIndex == 1);
    isFirst = rect1->property("firstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = rect1->property("lastItem").toBool();
    QVERIFY(isLast == true);

    row->metaObject()->invokeMethod(row, "createSubRect");

    QTRY_VERIFY(rect1->property("index").toInt() == 1);
    QTRY_VERIFY(rect1->property("firstItem").toBool() == false);
    QTRY_VERIFY(rect1->property("lastItem").toBool() == false);

    QQuickRectangle *rect2 = canvas->rootObject()->findChild<QQuickRectangle *>("rect2");
    QVERIFY(rect2 != 0);

    posIndex = rect2->property("index").toInt();
    QVERIFY(posIndex == 2);
    isFirst = rect2->property("firstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = rect2->property("lastItem").toBool();
    QVERIFY(isLast == true);

    row->metaObject()->invokeMethod(row, "destroySubRect");

    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
    QCoreApplication::processEvents();

    QTRY_VERIFY(rect1->property("index").toInt() == 1);
    QTRY_VERIFY(rect1->property("firstItem").toBool() == false);
    QTRY_VERIFY(rect1->property("lastItem").toBool() == true);

    delete canvas;
}

QQuickView *tst_qquickpositioners::createView(const QString &filename, bool wait)
{
    QQuickView *canvas = new QQuickView(0);
    qDebug() << "1";

    canvas->setSource(QUrl::fromLocalFile(filename));
    qDebug() << "2";
    canvas->show();
    qDebug() << "3";
    if (wait)
        QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn
    qDebug() << "4";

    return canvas;
}

void tst_qquickpositioners::matchIndexLists(const QVariantList &indexLists, const QList<int> &expectedIndexes)
{
    for (int i=0; i<indexLists.count(); i++) {
        QSet<int> current = indexLists[i].value<QList<int> >().toSet();
        if (current != expectedIndexes.toSet())
            qDebug() << "Cannot match actual targets" << current << "with expected" << expectedIndexes;
        QCOMPARE(current, expectedIndexes.toSet());
    }
}

void tst_qquickpositioners::matchItemsAndIndexes(const QVariantMap &items, const QaimModel &model, const QList<int> &expectedIndexes)
{
    for (QVariantMap::const_iterator it = items.begin(); it != items.end(); ++it) {
        QVERIFY(it.value().type() == QVariant::Int);
        QString name = it.key();
        int itemIndex = it.value().toInt();
        QVERIFY2(expectedIndexes.contains(itemIndex), QTest::toString(QString("Index %1 not found in expectedIndexes").arg(itemIndex)));
        if (model.name(itemIndex) != name)
            qDebug() << itemIndex;
        QCOMPARE(model.name(itemIndex), name);
    }
    QCOMPARE(items.count(), expectedIndexes.count());
}

void tst_qquickpositioners::matchItemLists(const QVariantList &itemLists, const QList<QQuickItem *> &expectedItems)
{
    for (int i=0; i<itemLists.count(); i++) {
        QVERIFY(itemLists[i].type() == QVariant::List);
        QVariantList current = itemLists[i].toList();
        for (int j=0; j<current.count(); j++) {
            QQuickItem *o = qobject_cast<QQuickItem*>(current[j].value<QObject*>());
            QVERIFY2(o, QTest::toString(QString("Invalid actual item at %1").arg(j)));
            QVERIFY2(expectedItems.contains(o), QTest::toString(QString("Cannot match item %1").arg(j)));
        }
        QCOMPARE(current.count(), expectedItems.count());
    }
}

QTEST_MAIN(tst_qquickpositioners)

#include "tst_qquickpositioners.moc"
