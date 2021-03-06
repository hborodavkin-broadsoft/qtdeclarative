/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qquickevents_p_p.h"
#include <QtCore/qmap.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickpointerhandler_p.h>
#include <QtQuick/private/qquickwindow_p.h>
#include <private/qdebug_p.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcPointerEvents, "qt.quick.pointer.events")
Q_LOGGING_CATEGORY(lcPointerGrab, "qt.quick.pointer.grab")

/*!
    \qmltype KeyEvent
    \instantiates QQuickKeyEvent
    \inqmlmodule QtQuick
    \ingroup qtquick-input-events

    \brief Provides information about a key event

    For example, the following changes the Item's state property when the Enter
    key is pressed:
    \qml
Item {
    focus: true
    Keys.onPressed: { if (event.key == Qt.Key_Enter) state = 'ShowDetails'; }
}
    \endqml
*/

/*!
    \qmlproperty int QtQuick::KeyEvent::key

    This property holds the code of the key that was pressed or released.

    See \l {Qt::Key}{Qt.Key} for the list of keyboard codes. These codes are
    independent of the underlying window system. Note that this
    function does not distinguish between capital and non-capital
    letters; use the \l {KeyEvent::}{text} property for this purpose.

    A value of either 0 or \l {Qt::Key_unknown}{Qt.Key_Unknown} means that the event is not
    the result of a known key; for example, it may be the result of
    a compose sequence, a keyboard macro, or due to key event
    compression.
*/

/*!
    \qmlproperty string QtQuick::KeyEvent::text

    This property holds the Unicode text that the key generated.
    The text returned can be an empty string in cases where modifier keys,
    such as Shift, Control, Alt, and Meta, are being pressed or released.
    In such cases \c key will contain a valid value
*/

/*!
    \qmlproperty bool QtQuick::KeyEvent::isAutoRepeat

    This property holds whether this event comes from an auto-repeating key.
*/

/*!
    \qmlproperty quint32 QtQuick::KeyEvent::nativeScanCode

    This property contains the native scan code of the key that was pressed. It is
    passed through from QKeyEvent unchanged.

    \sa QKeyEvent::nativeScanCode()
*/

/*!
    \qmlproperty int QtQuick::KeyEvent::count

    This property holds the number of keys involved in this event. If \l KeyEvent::text
    is not empty, this is simply the length of the string.
*/

/*!
    \qmlproperty bool QtQuick::KeyEvent::accepted

    Setting \a accepted to true prevents the key event from being
    propagated to the item's parent.

    Generally, if the item acts on the key event then it should be accepted
    so that ancestor items do not also respond to the same event.
*/

/*!
    \qmlproperty int QtQuick::KeyEvent::modifiers

    This property holds the keyboard modifier flags that existed immediately
    before the event occurred.

    It contains a bitwise combination of:
    \list
    \li Qt.NoModifier - No modifier key is pressed.
    \li Qt.ShiftModifier - A Shift key on the keyboard is pressed.
    \li Qt.ControlModifier - A Ctrl key on the keyboard is pressed.
    \li Qt.AltModifier - An Alt key on the keyboard is pressed.
    \li Qt.MetaModifier - A Meta key on the keyboard is pressed.
    \li Qt.KeypadModifier - A keypad button is pressed.
    \li Qt.GroupSwitchModifier - X11 only. A Mode_switch key on the keyboard is pressed.
    \endlist

    For example, to react to a Shift key + Enter key combination:
    \qml
    Item {
        focus: true
        Keys.onPressed: {
            if ((event.key == Qt.Key_Enter) && (event.modifiers & Qt.ShiftModifier))
                doSomething();
        }
    }
    \endqml
*/

/*!
    \qmlmethod bool QtQuick::KeyEvent::matches(StandardKey key)
    \since 5.2

    Returns \c true if the key event matches the given standard \a key; otherwise returns \c false.

    \qml
    Item {
        focus: true
        Keys.onPressed: {
            if (event.matches(StandardKey.Undo))
                myModel.undo();
            else if (event.matches(StandardKey.Redo))
                myModel.redo();
        }
    }
    \endqml

    \sa QKeySequence::StandardKey
*/

/*!
    \qmltype MouseEvent
    \instantiates QQuickMouseEvent
    \inqmlmodule QtQuick
    \ingroup qtquick-input-events

    \brief Provides information about a mouse event

    The position of the mouse can be found via the \l x and \l y properties.
    The button that caused the event is available via the \l button property.

    \sa MouseArea
*/

/*!
    \internal
    \class QQuickMouseEvent
*/

/*!
    \qmlproperty real QtQuick::MouseEvent::x
    \qmlproperty real QtQuick::MouseEvent::y

    These properties hold the coordinates of the position supplied by the mouse event.
*/


/*!
    \qmlproperty bool QtQuick::MouseEvent::accepted

    Setting \a accepted to true prevents the mouse event from being
    propagated to items below this item.

    Generally, if the item acts on the mouse event then it should be accepted
    so that items lower in the stacking order do not also respond to the same event.
*/

/*!
    \qmlproperty enumeration QtQuick::MouseEvent::button

    This property holds the button that caused the event.  It can be one of:
    \list
    \li Qt.LeftButton
    \li Qt.RightButton
    \li Qt.MiddleButton
    \endlist
*/

/*!
    \qmlproperty bool QtQuick::MouseEvent::wasHeld

    This property is true if the mouse button has been held pressed longer the
    threshold (800ms).
*/

/*!
    \qmlproperty int QtQuick::MouseEvent::buttons

    This property holds the mouse buttons pressed when the event was generated.
    For mouse move events, this is all buttons that are pressed down. For mouse
    press and double click events this includes the button that caused the event.
    For mouse release events this excludes the button that caused the event.

    It contains a bitwise combination of:
    \list
    \li Qt.LeftButton
    \li Qt.RightButton
    \li Qt.MiddleButton
    \endlist
*/

/*!
    \qmlproperty int QtQuick::MouseEvent::modifiers

    This property holds the keyboard modifier flags that existed immediately
    before the event occurred.

    It contains a bitwise combination of:
    \list
    \li Qt.NoModifier - No modifier key is pressed.
    \li Qt.ShiftModifier - A Shift key on the keyboard is pressed.
    \li Qt.ControlModifier - A Ctrl key on the keyboard is pressed.
    \li Qt.AltModifier - An Alt key on the keyboard is pressed.
    \li Qt.MetaModifier - A Meta key on the keyboard is pressed.
    \li Qt.KeypadModifier - A keypad button is pressed.
    \endlist

    For example, to react to a Shift key + Left mouse button click:
    \qml
    MouseArea {
        onClicked: {
            if ((mouse.button == Qt.LeftButton) && (mouse.modifiers & Qt.ShiftModifier))
                doSomething();
        }
    }
    \endqml
*/

/*!
    \qmlproperty int QtQuick::MouseEvent::source
    \since 5.7

    This property holds the source of the mouse event.

    The mouse event source can be used to distinguish between genuine and
    artificial mouse events. When using other pointing devices such as
    touchscreens and graphics tablets, if the application does not make use of
    the actual touch or tablet events, mouse events may be synthesized by the
    operating system or by Qt itself.

    The value can be one of:

    \value Qt.MouseEventNotSynthesized The most common value. On platforms where
    such information is available, this value indicates that the event
    represents a genuine mouse event from the system.

    \value Qt.MouseEventSynthesizedBySystem Indicates that the mouse event was
    synthesized from a touch or tablet event by the platform.

    \value Qt.MouseEventSynthesizedByQt Indicates that the mouse event was
    synthesized from an unhandled touch or tablet event by Qt.

    \value Qt.MouseEventSynthesizedByApplication Indicates that the mouse event
    was synthesized by the application. This allows distinguishing
    application-generated mouse events from the ones that are coming from the
    system or are synthesized by Qt.

    For example, to react only to events which come from an actual mouse:
    \qml
    MouseArea {
        onPressed: if (mouse.source !== Qt.MouseEventNotSynthesized) {
            mouse.accepted = false
        }

        onClicked: doSomething()
    }
    \endqml

    If the handler for the press event rejects the event, it will be propagated
    further, and then another Item underneath can handle synthesized events
    from touchscreens. For example, if a Flickable is used underneath (and the
    MouseArea is not a child of the Flickable), it can be useful for the
    MouseArea to handle genuine mouse events in one way, while allowing touch
    events to fall through to the Flickable underneath, so that the ability to
    flick on a touchscreen is retained. In that case the ability to drag the
    Flickable via mouse would be lost, but it does not prevent Flickable from
    receiving mouse wheel events.
*/

/*!
    \qmltype WheelEvent
    \instantiates QQuickWheelEvent
    \inqmlmodule QtQuick
    \ingroup qtquick-input-events
    \brief Provides information about a mouse wheel event

    The position of the mouse can be found via the \l x and \l y properties.

    \sa MouseArea
*/

/*!
    \internal
    \class QQuickWheelEvent
*/

/*!
    \qmlproperty real QtQuick::WheelEvent::x
    \qmlproperty real QtQuick::WheelEvent::y

    These properties hold the coordinates of the position supplied by the wheel event.
*/

/*!
    \qmlproperty bool QtQuick::WheelEvent::accepted

    Setting \a accepted to true prevents the wheel event from being
    propagated to items below this item.

    Generally, if the item acts on the wheel event then it should be accepted
    so that items lower in the stacking order do not also respond to the same event.
*/

/*!
    \qmlproperty int QtQuick::WheelEvent::buttons

    This property holds the mouse buttons pressed when the wheel event was generated.

    It contains a bitwise combination of:
    \list
    \li Qt.LeftButton
    \li Qt.RightButton
    \li Qt.MiddleButton
    \endlist
*/

/*!
    \qmlproperty point QtQuick::WheelEvent::angleDelta

    This property holds the distance that the wheel is rotated in wheel degrees.
    The x and y cordinate of this property holds the delta in horizontal and
    vertical orientation.

    A positive value indicates that the wheel was rotated up/right;
    a negative value indicates that the wheel was rotated down/left.

    Most mouse types work in steps of 15 degrees, in which case the delta value is a
    multiple of 120; i.e., 120 units * 1/8 = 15 degrees.
*/

/*!
    \qmlproperty point QtQuick::WheelEvent::pixelDelta

    This property holds the delta in screen pixels and is available in platforms that
    have high-resolution trackpads, such as \macos.
    The x and y cordinate of this property holds the delta in horizontal and
    vertical orientation. The value should be used directly to scroll content on screen.

    For platforms without high-resolution trackpad support, pixelDelta will always be (0,0),
    and angleDelta should be used instead.
*/

/*!
    \qmlproperty int QtQuick::WheelEvent::modifiers

    This property holds the keyboard modifier flags that existed immediately
    before the event occurred.

    It contains a bitwise combination of:
    \list
    \li Qt.NoModifier - No modifier key is pressed.
    \li Qt.ShiftModifier - A Shift key on the keyboard is pressed.
    \li Qt.ControlModifier - A Ctrl key on the keyboard is pressed.
    \li Qt.AltModifier - An Alt key on the keyboard is pressed.
    \li Qt.MetaModifier - A Meta key on the keyboard is pressed.
    \li Qt.KeypadModifier - A keypad button is pressed.
    \endlist

    For example, to react to a Control key pressed during the wheel event:
    \qml
    MouseArea {
        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
                adjustZoom(wheel.angleDelta.y / 120);
            }
        }
    }
    \endqml
*/

/*!
    \qmlproperty int QtQuick::WheelEvent::inverted

    Returns whether the delta values delivered with the event are inverted.

    Normally, a vertical wheel will produce a WheelEvent with positive delta
    values if the top of the wheel is rotating away from the hand operating it.
    Similarly, a horizontal wheel movement will produce a QWheelEvent with
    positive delta values if the top of the wheel is moved to the left.

    However, on some platforms this is configurable, so that the same
    operations described above will produce negative delta values (but with the
    same magnitude). For instance, in a QML component (such as a tumbler or a
    slider) where it is appropriate to synchronize the movement or rotation of
    an item with the direction of the wheel, regardless of the system settings,
    the wheel event handler can use the inverted property to decide whether to
    negate the angleDelta or pixelDelta values.

    \note Many platforms provide no such information. On such platforms
    \l inverted always returns false.
*/

typedef QHash<QTouchDevice *, QQuickPointerDevice *> PointerDeviceForTouchDeviceHash;
Q_GLOBAL_STATIC(PointerDeviceForTouchDeviceHash, g_touchDevices)

struct ConstructableQQuickPointerDevice : public QQuickPointerDevice
{
    ConstructableQQuickPointerDevice(DeviceType devType, PointerType pType, Capabilities caps,
                              int maxPoints, int buttonCount, const QString &name,
                              qint64 uniqueId = 0)
        : QQuickPointerDevice(devType, pType, caps, maxPoints, buttonCount, name, uniqueId) {}

};
Q_GLOBAL_STATIC_WITH_ARGS(ConstructableQQuickPointerDevice, g_genericMouseDevice,
                            (QQuickPointerDevice::Mouse,
                             QQuickPointerDevice::GenericPointer,
                             QQuickPointerDevice::Position | QQuickPointerDevice::Scroll | QQuickPointerDevice::Hover,
                             1, 3, QLatin1String("core pointer"), 0))

typedef QHash<qint64, QQuickPointerDevice *> PointerDeviceForDeviceIdHash;
Q_GLOBAL_STATIC(PointerDeviceForDeviceIdHash, g_tabletDevices)

// debugging helpers
static const char *pointStateString(const QQuickEventPoint *point)
{
    static const QMetaEnum stateMetaEnum = point->metaObject()->enumerator(point->metaObject()->indexOfEnumerator("State"));
    return stateMetaEnum.valueToKey(point->state());
}

static const QString pointDeviceName(const QQuickEventPoint *point)
{
    auto device = static_cast<const QQuickPointerEvent *>(point->parent())->device();
    QString deviceName = (device ? device->name() : QLatin1String("null device"));
    deviceName.resize(16, ' '); // shorten, and align in case of sequential output
    return deviceName;
}


QQuickPointerDevice *QQuickPointerDevice::touchDevice(QTouchDevice *d)
{
    if (g_touchDevices->contains(d))
        return g_touchDevices->value(d);

    QQuickPointerDevice::DeviceType type = QQuickPointerDevice::TouchScreen;
    QString name;
    int maximumTouchPoints = 10;
    QQuickPointerDevice::Capabilities caps = QQuickPointerDevice::Capabilities(QTouchDevice::Position);
    if (d) {
        QQuickPointerDevice::Capabilities caps =
            static_cast<QQuickPointerDevice::Capabilities>(static_cast<int>(d->capabilities()) & 0x0F);
        if (d->type() == QTouchDevice::TouchPad) {
            type = QQuickPointerDevice::TouchPad;
            caps |= QQuickPointerDevice::Scroll;
        }
        name = d->name();
        maximumTouchPoints = d->maximumTouchPoints();
    } else {
        qWarning() << "QQuickWindowPrivate::touchDevice: creating touch device from nullptr device in QTouchEvent";
    }

    QQuickPointerDevice *dev = new QQuickPointerDevice(type, QQuickPointerDevice::Finger,
        caps, maximumTouchPoints, 0, name, 0);
    g_touchDevices->insert(d, dev);
    return dev;
}

QList<QQuickPointerDevice*> QQuickPointerDevice::touchDevices()
{
    return g_touchDevices->values();
}

QQuickPointerDevice *QQuickPointerDevice::genericMouseDevice()
{
    return g_genericMouseDevice;
}

QQuickPointerDevice *QQuickPointerDevice::tabletDevice(qint64 id)
{
    auto it = g_tabletDevices->find(id);
    if (it != g_tabletDevices->end())
        return it.value();

    // ### Figure out how to populate the tablet devices
    return nullptr;
}

void QQuickEventPoint::reset(Qt::TouchPointState state, const QPointF &scenePos, int pointId, ulong timestamp, const QVector2D &velocity)
{
    m_scenePos = scenePos;
    m_pointId = pointId;
    m_accept = false;
    m_state = static_cast<QQuickEventPoint::State>(state);
    m_timestamp = timestamp;
    if (state == Qt::TouchPointPressed) {
        m_pressTimestamp = timestamp;
        m_scenePressPos = scenePos;
    }
    m_velocity = (Q_LIKELY(velocity.isNull()) ? estimatedVelocity() : velocity);
}

void QQuickEventPoint::localizePosition(QQuickItem *target)
{
    if (target)
        m_pos = target->mapFromScene(scenePos());
    else
        m_pos = QPointF();
}

/*!
    If this point has an exclusive grabber, returns a pointer to it; else
    returns null, if there is no grabber.  The grabber could be either
    an Item or a PointerHandler.
*/
QObject *QQuickEventPoint::exclusiveGrabber() const
{
    return m_exclusiveGrabber.data();
}

/*!
    Set the given Item or PointerHandler as the exclusive grabber of this point.
    If there was already an exclusive grab, it will be canceled.  If there
    were passive grabbers, they will continue to lurk, but the exclusive grab
    is a behavioral override of the passive grab as long as it remains.
    If you already know whether the grabber is to be an Item or a PointerHandler,
    you should instead call setGrabberItem() or setGrabberPointerHandler(),
    because it is slightly more efficient.
*/
void QQuickEventPoint::setExclusiveGrabber(QObject *grabber)
{
    if (QQuickPointerHandler *phGrabber = qmlobject_cast<QQuickPointerHandler *>(grabber))
        setGrabberPointerHandler(phGrabber, true);
    else
        setGrabberItem(static_cast<QQuickItem *>(grabber));
}

/*!
    If the exclusive grabber of this point is an Item, returns a
    pointer to that Item; else returns null, if there is no grabber or if
    the grabber is a PointerHandler.
*/
QQuickItem *QQuickEventPoint::grabberItem() const
{
    return (m_grabberIsHandler ? nullptr : static_cast<QQuickItem *>(m_exclusiveGrabber.data()));
}

/*!
    Set the given Item \a grabber as the exclusive grabber of this point.
    If there was already an exclusive grab, it will be canceled.  If there
    were passive grabbers, they will continue to lurk, but the exclusive grab
    is a behavioral override of the passive grab as long as it remains.
*/
void QQuickEventPoint::setGrabberItem(QQuickItem *grabber)
{
    if (grabber != m_exclusiveGrabber.data()) {
        if (Q_UNLIKELY(lcPointerGrab().isDebugEnabled())) {
            qCDebug(lcPointerGrab) << pointDeviceName(this) << "point" << hex << m_pointId << pointStateString(this)
                                   << ": grab" << m_exclusiveGrabber << "->" << grabber;
        }
        QQuickPointerHandler *oldGrabberHandler = grabberPointerHandler();
        QQuickItem *oldGrabberItem = grabberItem();
        m_exclusiveGrabber = QPointer<QObject>(grabber);
        m_grabberIsHandler = false;
        m_sceneGrabPos = m_scenePos;
        if (oldGrabberHandler)
            oldGrabberHandler->onGrabChanged(oldGrabberHandler, CancelGrabExclusive, this);
        else if (oldGrabberItem && oldGrabberItem != grabber && grabber && pointerEvent()->asPointerTouchEvent())
            oldGrabberItem->touchUngrabEvent();
        for (QPointer<QQuickPointerHandler> passiveGrabber : m_passiveGrabbers)
            passiveGrabber->onGrabChanged(passiveGrabber, OverrideGrabPassive, this);
    }
}

/*!
    If the exclusive grabber of this point is a PointerHandler, returns a
    pointer to that handler; else returns null, if there is no grabber or if
    the grabber is an Item.
*/
QQuickPointerHandler *QQuickEventPoint::grabberPointerHandler() const
{
    return (m_grabberIsHandler ? static_cast<QQuickPointerHandler *>(m_exclusiveGrabber.data()) : nullptr);
}

/*!
    Set the given PointerHandler \a grabber as grabber of this point. If \a
    exclusive is true, it will override any other grabs; if false, \a grabber
    will be added to the list of passive grabbers of this point.
*/
void QQuickEventPoint::setGrabberPointerHandler(QQuickPointerHandler *grabber, bool exclusive)
{
    if (Q_UNLIKELY(lcPointerGrab().isDebugEnabled())) {
        if (exclusive) {
            if (m_exclusiveGrabber != grabber)
                qCDebug(lcPointerGrab) << pointDeviceName(this) << "point" << hex << m_pointId << pointStateString(this)
                                       << ": grab (exclusive)" << m_exclusiveGrabber << "->" << grabber;
        } else {
            qCDebug(lcPointerGrab) << pointDeviceName(this) << "point" << hex << m_pointId << pointStateString(this)
                                   << ": grab (passive)" << grabber;
        }
    }
    if (exclusive) {
        if (grabber != m_exclusiveGrabber.data()) {
            if (grabber) {
                // set variables before notifying the new grabber
                m_exclusiveGrabber = QPointer<QObject>(grabber);
                m_grabberIsHandler = true;
                m_sceneGrabPos = m_scenePos;
                grabber->onGrabChanged(grabber, GrabExclusive, this);
                for (QPointer<QQuickPointerHandler> passiveGrabber : m_passiveGrabbers) {
                    if (passiveGrabber != grabber)
                        passiveGrabber->onGrabChanged(grabber, OverrideGrabPassive, this);
                }
            } else if (QQuickPointerHandler *oldGrabberPointerHandler = qmlobject_cast<QQuickPointerHandler *>(m_exclusiveGrabber.data())) {
                oldGrabberPointerHandler->onGrabChanged(oldGrabberPointerHandler, UngrabExclusive, this);
            } else if (!m_exclusiveGrabber.isNull()) {
                // If there is a previous grabber and it's not a PointerHandler, it must be an Item.
                QQuickItem *oldGrabberItem = static_cast<QQuickItem *>(m_exclusiveGrabber.data());
                // If this point came from a touchscreen, notify that previous grabber Item that it's losing its touch grab.
                if (pointerEvent()->asPointerTouchEvent())
                    oldGrabberItem->touchUngrabEvent();
            }
            // set variables after notifying the old grabber
            m_exclusiveGrabber = QPointer<QObject>(grabber);
            m_grabberIsHandler = true;
            m_sceneGrabPos = m_scenePos;
        }
    } else {
        if (!grabber) {
            qDebug() << "can't set passive grabber to null";
            return;
        }
        auto ptr = QPointer<QQuickPointerHandler>(grabber);
        if (!m_passiveGrabbers.contains(ptr)) {
            m_passiveGrabbers.append(ptr);
            grabber->onGrabChanged(grabber, GrabPassive, this);
        }
    }
}

/*!
    If this point has an existing exclusive grabber (Item or PointerHandler),
    inform the grabber that its grab is canceled, and remove it as grabber.
    This normally happens when the grab is stolen by another Item.
*/
void QQuickEventPoint::cancelExclusiveGrab()
{
    if (m_exclusiveGrabber.isNull())
        qWarning("cancelGrab: no grabber");
    else
        cancelExclusiveGrabImpl();
}

void QQuickEventPoint::cancelExclusiveGrabImpl(QTouchEvent *cancelEvent)
{
    if (m_exclusiveGrabber.isNull())
        return;
    if (Q_UNLIKELY(lcPointerGrab().isDebugEnabled())) {
        qCDebug(lcPointerGrab) << pointDeviceName(this) << "point" << hex << m_pointId << pointStateString(this)
                               << ": grab (exclusive)" << m_exclusiveGrabber << "-> nullptr";
    }
    if (auto handler = grabberPointerHandler()) {
        handler->onGrabChanged(handler, CancelGrabExclusive, this);
    } else if (auto item = grabberItem()) {
        if (cancelEvent)
            QCoreApplication::sendEvent(item, cancelEvent);
        else
            item->touchUngrabEvent();
    }
    m_exclusiveGrabber.clear();
}

/*!
    If this point has the given \a handler as a passive grabber,
    inform the grabber that its grab is canceled, and remove it as grabber.
    This normally happens when another Item or PointerHandler does an exclusive grab.
*/
void QQuickEventPoint::cancelPassiveGrab(QQuickPointerHandler *handler)
{
    if (removePassiveGrabber(handler)) {
        if (Q_UNLIKELY(lcPointerGrab().isDebugEnabled())) {
            qCDebug(lcPointerGrab) << pointDeviceName(this) << "point" << hex << m_pointId << pointStateString(this)
                                   << ": grab (passive)" << handler << "removed";
        }
        handler->onGrabChanged(handler, CancelGrabPassive, this);
    }
}

/*!
    If this point has the given \a handler as a passive grabber, remove it as grabber.
    Returns true if it was removed, false if it wasn't a grabber.
*/
bool QQuickEventPoint::removePassiveGrabber(QQuickPointerHandler *handler)
{
    return m_passiveGrabbers.removeOne(handler);
}

/*!
    If the given \a handler is grabbing this point passively, exclusively
    or both, cancel the grab and remove it as grabber.
    This normally happens when the handler decides that the behavior of this
    point can no longer satisfy the handler's behavioral constraints within
    the remainder of the gesture which the user is performing: for example
    the handler tries to detect a tap but a drag is occurring instead, or
    it tries to detect a drag in one direction but the drag is going in
    another direction.  In such cases the handler no longer needs or wants
    to be informed of any further movements of this point.
*/
void QQuickEventPoint::cancelAllGrabs(QQuickPointerHandler *handler)
{
    if (m_exclusiveGrabber == handler) {
        handler->onGrabChanged(handler, CancelGrabExclusive, this);
        m_exclusiveGrabber.clear();
    }
    cancelPassiveGrab(handler);
}

/*!
    Set this point as \a accepted (true) or rejected (false).
    Accepting a point is intended to stop event propagation.
    It does not imply any kind of grab, passive or exclusive.
    TODO explain further under what conditions propagation really does stop...
*/
void QQuickEventPoint::setAccepted(bool accepted)
{
    if (m_accept != accepted) {
        qCDebug(lcPointerEvents) << this << m_accept << "->" << accepted;
        m_accept = accepted;
    }
}

QQuickEventTouchPoint::QQuickEventTouchPoint(QQuickPointerTouchEvent *parent)
    : QQuickEventPoint(parent), m_rotation(0), m_pressure(0)
{}

void QQuickEventTouchPoint::reset(const QTouchEvent::TouchPoint &tp, ulong timestamp)
{
    QQuickEventPoint::reset(tp.state(), tp.scenePos(), tp.id(), timestamp, tp.velocity());
    m_exclusiveGrabber.clear();
    m_passiveGrabbers.clear();
    m_rotation = tp.rotation();
    m_pressure = tp.pressure();
    m_ellipseDiameters = tp.ellipseDiameters();
    m_uniqueId = tp.uniqueId();
}

struct PointVelocityData {
    QVector2D velocity;
    QPointF pos;
    ulong timestamp;
};

typedef QMap<quint64, PointVelocityData*> PointDataForPointIdMap;
Q_GLOBAL_STATIC(PointDataForPointIdMap, g_previousPointData)
static const int PointVelocityAgeLimit = 500; // milliseconds

/*!
    \internal
    Estimates the velocity based on a weighted average of all previous velocities.
    The older the velocity is, the less significant it becomes for the estimate.
*/
QVector2D QQuickEventPoint::estimatedVelocity() const
{
    PointVelocityData *prevPoint = g_previousPointData->value(m_pointId);
    if (!prevPoint) {
        // cleanup events older than PointVelocityAgeLimit
        auto end = g_previousPointData->end();
        for (auto it = g_previousPointData->begin(); it != end; ) {
            PointVelocityData *data = it.value();
            if (m_timestamp - data->timestamp > PointVelocityAgeLimit) {
                it = g_previousPointData->erase(it);
                delete data;
            } else {
                ++it;
            }
        }
        // TODO optimize: stop this dynamic memory thrashing
        prevPoint = new PointVelocityData;
        prevPoint->velocity = QVector2D();
        prevPoint->timestamp = 0;
        prevPoint->pos = QPointF();
        g_previousPointData->insert(m_pointId, prevPoint);
    }
    const ulong timeElapsed = m_timestamp - prevPoint->timestamp;
    if (timeElapsed == 0)   // in case we call estimatedVelocity() twice on the same QQuickEventPoint
        return m_velocity;

    QVector2D newVelocity;
    if (prevPoint->timestamp != 0)
        newVelocity = QVector2D(m_scenePos - prevPoint->pos)/timeElapsed;

    // VERY simple kalman filter: does a weighted average
    // where the older velocities get less and less significant
    static const float KalmanGain = 0.7f;
    QVector2D filteredVelocity = newVelocity * KalmanGain + m_velocity * (1.0f - KalmanGain);

    prevPoint->velocity = filteredVelocity;
    prevPoint->pos = m_scenePos;
    prevPoint->timestamp = m_timestamp;
    return filteredVelocity;
}

/*!
    \internal
    \class QQuickPointerEvent

    QQuickPointerEvent is used as a long-lived object to store data related to
    an event from a pointing device, such as a mouse, touch or tablet event,
    during event delivery. It also provides properties which may be used later
    to expose the event to QML, the same as is done with QQuickMouseEvent,
    QQuickTouchPoint, QQuickKeyEvent, etc. Since only one event can be
    delivered at a time, this class is effectively a singleton.  We don't worry
    about the QObject overhead because the instances are long-lived: we don't
    dynamically create and destroy objects of this type for each event.
*/

QQuickPointerEvent::~QQuickPointerEvent()
{}

QQuickPointerEvent *QQuickPointerMouseEvent::reset(QEvent *event)
{
    auto ev = static_cast<QMouseEvent*>(event);
    m_event = ev;
    if (!event)
        return this;

    m_device = QQuickPointerDevice::genericMouseDevice();
    m_device->eventDeliveryTargets().clear();
    m_button = ev->button();
    m_pressedButtons = ev->buttons();
    Qt::TouchPointState state = Qt::TouchPointStationary;
    switch (ev->type()) {
    case QEvent::MouseButtonPress:
        m_mousePoint->clearPassiveGrabbers();
        Q_FALLTHROUGH();
    case QEvent::MouseButtonDblClick:
        state = Qt::TouchPointPressed;
        break;
    case QEvent::MouseButtonRelease:
        state = Qt::TouchPointReleased;
        break;
    case QEvent::MouseMove:
        state = Qt::TouchPointMoved;
        break;
    default:
        break;
    }
    m_mousePoint->reset(state, ev->windowPos(), quint64(1) << 24, ev->timestamp());  // mouse has device ID 1
    return this;
}

void QQuickPointerMouseEvent::localize(QQuickItem *target)
{
    m_mousePoint->localizePosition(target);
}

QQuickPointerEvent *QQuickPointerTouchEvent::reset(QEvent *event)
{
    auto ev = static_cast<QTouchEvent*>(event);
    m_event = ev;
    if (!event)
        return this;

    m_device = QQuickPointerDevice::touchDevice(ev->device());
    m_device->eventDeliveryTargets().clear();
    m_button = Qt::NoButton;
    m_pressedButtons = Qt::NoButton;

    const QList<QTouchEvent::TouchPoint> &tps = ev->touchPoints();
    int newPointCount = tps.count();
    m_touchPoints.reserve(newPointCount);

    for (int i = m_touchPoints.size(); i < newPointCount; ++i)
        m_touchPoints.insert(i, new QQuickEventTouchPoint(this));

    // Make sure the grabbers and on-pressed values are right from one event to the next
    struct ToPreserve {
        int pointId; // just for double-checking
        ulong pressTimestamp;
        QPointF scenePressPos;
        QPointF sceneGrabPos;
        QObject * grabber;
        QVector <QPointer <QQuickPointerHandler> > passiveGrabbers;

        ToPreserve() : pointId(0), pressTimestamp(0), grabber(nullptr) {}
    };
    QVector<ToPreserve> preserves(newPointCount); // jar of pickled touchpoints, in order of points in the _new_ event

    // Copy stuff we need to preserve, because the order of points might have changed in the event.
    // The ID is all that we can rely on (release might remove the first point etc).
    for (int i = 0; i < newPointCount; ++i) {
        int pid = tps.at(i).id();
        if (auto point = pointById(pid)) {
            preserves[i].pointId = pid;
            preserves[i].pressTimestamp = point->m_pressTimestamp;
            preserves[i].scenePressPos = point->scenePressPos();
            preserves[i].sceneGrabPos = point->sceneGrabPos();
            preserves[i].grabber = point->exclusiveGrabber();
            preserves[i].passiveGrabbers = point->passiveGrabbers();
        }
    }

    for (int i = 0; i < newPointCount; ++i) {
        auto point = m_touchPoints.at(i);
        point->reset(tps.at(i), ev->timestamp());
        const auto &preserved = preserves.at(i);
        if (point->state() == QQuickEventPoint::Pressed) {
            if (preserved.grabber)
                qWarning() << "TouchPointPressed without previous release event" << point;
            point->setGrabberItem(nullptr);
            point->clearPassiveGrabbers();
        } else {
            // Restore the grabbers without notifying (don't call onGrabChanged)
            Q_ASSERT(preserved.pointId == 0 || preserved.pointId == point->pointId());
            point->m_pressTimestamp = preserved.pressTimestamp;
            point->m_scenePressPos = preserved.scenePressPos;
            point->m_sceneGrabPos = preserved.sceneGrabPos;
            point->m_exclusiveGrabber = preserved.grabber;
            point->m_grabberIsHandler = (qmlobject_cast<QQuickPointerHandler *>(point->m_exclusiveGrabber) != nullptr);
            point->m_passiveGrabbers = preserved.passiveGrabbers;
        }
    }
    m_pointCount = newPointCount;
    return this;
}

void QQuickPointerTouchEvent::localize(QQuickItem *target)
{
    for (auto point : qAsConst(m_touchPoints))
        point->localizePosition(target);
}

QQuickEventPoint *QQuickPointerMouseEvent::point(int i) const {
    if (i == 0)
        return m_mousePoint;
    return nullptr;
}

QQuickEventPoint *QQuickPointerTouchEvent::point(int i) const {
    if (i >= 0 && i < m_pointCount)
        return m_touchPoints.at(i);
    return nullptr;
}

QQuickEventPoint::QQuickEventPoint(QQuickPointerEvent *parent)
  : QObject(parent), m_pointId(0), m_exclusiveGrabber(nullptr), m_timestamp(0), m_pressTimestamp(0),
    m_state(QQuickEventPoint::Released), m_accept(false), m_grabberIsHandler(false)
{
    Q_UNUSED(m_reserved);
}

QQuickPointerEvent *QQuickEventPoint::pointerEvent() const
{
    return static_cast<QQuickPointerEvent *>(parent());
}

bool QQuickPointerMouseEvent::allPointsAccepted() const {
    return m_mousePoint->isAccepted();
}

bool QQuickPointerMouseEvent::allUpdatedPointsAccepted() const {
    return m_mousePoint->state() == QQuickEventPoint::Pressed || m_mousePoint->isAccepted();
}

bool QQuickPointerMouseEvent::allPointsGrabbed() const
{
    return m_mousePoint->exclusiveGrabber() != nullptr;
}

QMouseEvent *QQuickPointerMouseEvent::asMouseEvent(const QPointF &localPos) const
{
    auto event = static_cast<QMouseEvent *>(m_event);
    event->setLocalPos(localPos);
    return event;
}

/*!
    Returns the exclusive grabber of this event, if any, in a vector.
*/
QVector<QObject *> QQuickPointerMouseEvent::exclusiveGrabbers() const
{
    QVector<QObject *> result;
    if (QObject *grabber = m_mousePoint->exclusiveGrabber())
        result << grabber;
    return result;
}

/*!
    Remove all passive and exclusive grabbers of this event, without notifying.
*/
void QQuickPointerMouseEvent::clearGrabbers() const {
    m_mousePoint->setGrabberItem(nullptr);
    m_mousePoint->clearPassiveGrabbers();
}

/*!
    Returns whether the given \a handler is the exclusive grabber of this event.
*/
bool QQuickPointerMouseEvent::hasExclusiveGrabber(const QQuickPointerHandler *handler) const
{
    return m_mousePoint->exclusiveGrabber() == handler;
}

bool QQuickPointerMouseEvent::isPressEvent() const
{
    auto me = static_cast<QMouseEvent*>(m_event);
    return ((me->type() == QEvent::MouseButtonPress || me->type() == QEvent::MouseButtonDblClick) &&
            (me->buttons() & me->button()) == me->buttons());
}

bool QQuickPointerMouseEvent::isDoubleClickEvent() const
{
    auto me = static_cast<QMouseEvent*>(m_event);
    return (me->type() == QEvent::MouseButtonDblClick);
}

bool QQuickPointerMouseEvent::isUpdateEvent() const
{
    auto me = static_cast<QMouseEvent*>(m_event);
    return me->type() == QEvent::MouseMove;
}

bool QQuickPointerMouseEvent::isReleaseEvent() const
{
    auto me = static_cast<QMouseEvent*>(m_event);
    return me->type() == QEvent::MouseButtonRelease;
}

bool QQuickPointerTouchEvent::allPointsAccepted() const {
    for (int i = 0; i < m_pointCount; ++i) {
        if (!m_touchPoints.at(i)->isAccepted())
            return false;
    }
    return true;
}

bool QQuickPointerTouchEvent::allUpdatedPointsAccepted() const {
    for (int i = 0; i < m_pointCount; ++i) {
        auto point = m_touchPoints.at(i);
        if (point->state() != QQuickEventPoint::Pressed && !point->isAccepted())
            return false;
    }
    return true;
}

bool QQuickPointerTouchEvent::allPointsGrabbed() const
{
    for (int i = 0; i < m_pointCount; ++i) {
        if (!m_touchPoints.at(i)->exclusiveGrabber())
            return false;
    }
    return true;
}

/*!
    Returns the exclusive grabbers of all points in this event, if any, in a vector.
*/
QVector<QObject *> QQuickPointerTouchEvent::exclusiveGrabbers() const
{
    QVector<QObject *> result;
    for (int i = 0; i < m_pointCount; ++i) {
        if (QObject *grabber = m_touchPoints.at(i)->exclusiveGrabber()) {
            if (!result.contains(grabber))
                result << grabber;
        }
    }
    return result;
}

/*!
    Remove all passive and exclusive grabbers of all touchpoints in this event,
    without notifying.
*/
void QQuickPointerTouchEvent::clearGrabbers() const {
    for (auto point: m_touchPoints) {
        point->setGrabberItem(nullptr);
        point->clearPassiveGrabbers();
    }
}

/*!
    Returns whether the given \a handler is the exclusive grabber of any
    touchpoint within this event.
*/
bool QQuickPointerTouchEvent::hasExclusiveGrabber(const QQuickPointerHandler *handler) const
{
    for (auto point: m_touchPoints)
        if (point->exclusiveGrabber() == handler)
            return true;
    return false;
}

bool QQuickPointerTouchEvent::isPressEvent() const
{
    return static_cast<QTouchEvent*>(m_event)->touchPointStates() & Qt::TouchPointPressed;
}

bool QQuickPointerTouchEvent::isUpdateEvent() const
{
    return static_cast<QTouchEvent*>(m_event)->touchPointStates() & (Qt::TouchPointMoved | Qt::TouchPointStationary);
}

bool QQuickPointerTouchEvent::isReleaseEvent() const
{
    return static_cast<QTouchEvent*>(m_event)->touchPointStates() & Qt::TouchPointReleased;
}

QVector<QPointF> QQuickPointerEvent::unacceptedPressedPointScenePositions() const
{
    QVector<QPointF> points;
    for (int i = 0; i < pointCount(); ++i) {
        if (!point(i)->isAccepted() && point(i)->state() == QQuickEventPoint::Pressed)
            points << point(i)->scenePos();
    }
    return points;
}

/*!
    \internal
    Populate the reusable synth-mouse event from one touchpoint.
    It's required that isTouchEvent() be true when this is called.
    If the touchpoint cannot be found, this returns nullptr.
    Ownership of the event is NOT transferred to the caller.
*/
QMouseEvent *QQuickPointerTouchEvent::syntheticMouseEvent(int pointID, QQuickItem *relativeTo) const {
    const QTouchEvent::TouchPoint *p = touchPointById(pointID);
    if (!p)
        return nullptr;
    QEvent::Type type;
    Qt::MouseButton buttons = Qt::LeftButton;
    switch (p->state()) {
    case Qt::TouchPointPressed:
        type = QEvent::MouseButtonPress;
        break;
    case Qt::TouchPointMoved:
    case Qt::TouchPointStationary:
        type = QEvent::MouseMove;
        break;
    case Qt::TouchPointReleased:
        type = QEvent::MouseButtonRelease;
        buttons = Qt::NoButton;
        break;
    default:
        Q_ASSERT(false);
        return nullptr;
    }
    m_synthMouseEvent = QMouseEvent(type, relativeTo->mapFromScene(p->scenePos()),
        p->scenePos(), p->screenPos(), Qt::LeftButton, buttons, m_event->modifiers());
    m_synthMouseEvent.setAccepted(true);
    m_synthMouseEvent.setTimestamp(m_event->timestamp());
    // In the future we will try to always have valid velocity in every QQuickEventPoint.
    // QQuickFlickablePrivate::handleMouseMoveEvent() checks for QTouchDevice::Velocity
    // and if it is set, then it does not need to do its own velocity calculations.
    // That's probably the only usecase for this, so far.  Some day Flickable should handle
    // pointer events, and then passing touchpoint velocity via QMouseEvent will be obsolete.
    // Conveniently (by design), QTouchDevice::Velocity == QQuickPointerDevice.Velocity
    // so that we don't need to convert m_device->capabilities().
    if (m_device)
        QGuiApplicationPrivate::setMouseEventCapsAndVelocity(&m_synthMouseEvent, m_device->capabilities(), p->velocity());
    QGuiApplicationPrivate::setMouseEventSource(&m_synthMouseEvent, Qt::MouseEventSynthesizedByQt);
    return &m_synthMouseEvent;
}

/*!
    \internal
    Returns a pointer to the QQuickEventPoint which has the \a pointId as
    \l {QQuickEventPoint::pointId}{pointId}.
    Returns nullptr if there is no point with that ID.

    \fn QQuickPointerEvent::pointById(int pointId) const
*/
QQuickEventPoint *QQuickPointerMouseEvent::pointById(int pointId) const {
    if (m_mousePoint && pointId == m_mousePoint->pointId())
        return m_mousePoint;
    return nullptr;
}

QQuickEventPoint *QQuickPointerTouchEvent::pointById(int pointId) const {
    auto it = std::find_if(m_touchPoints.constBegin(), m_touchPoints.constEnd(),
        [pointId](const QQuickEventTouchPoint *tp) { return tp->pointId() == pointId; } );
    if (it != m_touchPoints.constEnd())
        return *it;
    return nullptr;
}


/*!
    \internal
    Returns a pointer to the original TouchPoint which has the same
    \l {QTouchEvent::TouchPoint::id}{id} as \a pointId, if the original event is a
    QTouchEvent, and if that point is found. Otherwise, returns nullptr.
*/
const QTouchEvent::TouchPoint *QQuickPointerTouchEvent::touchPointById(int pointId) const {
    const QTouchEvent *ev = asTouchEvent();
    if (!ev)
        return nullptr;
    const QList<QTouchEvent::TouchPoint> &tps = ev->touchPoints();
    auto it = std::find_if(tps.constBegin(), tps.constEnd(),
        [pointId](QTouchEvent::TouchPoint const& tp) { return tp.id() == pointId; } );
    // return the pointer to the actual TP in QTouchEvent::_touchPoints
    return (it == tps.constEnd() ? nullptr : it.operator->());
}

/*!
    \internal
    Make a new QTouchEvent, giving it a subset of the original touch points.

    Returns a nullptr if all points are stationary, or there are no points inside the item,
    or none of the points were pressed inside and the item was not grabbing any of them
    and isFiltering is false.  When isFiltering is true, it is assumed that the item
    cares about all points which are inside its bounds, because most filtering items
    need to monitor eventpoint movements until a drag threshold is exceeded or the
    requirements for a gesture to be recognized are met in some other way.
*/
QTouchEvent *QQuickPointerTouchEvent::touchEventForItem(QQuickItem *item, bool isFiltering) const
{
    QList<QTouchEvent::TouchPoint> touchPoints;
    Qt::TouchPointStates eventStates;
    // TODO maybe add QQuickItem::mapVector2DFromScene(QVector2D) to avoid needing QQuickItemPrivate here
    // Or else just document that velocity is always scene-relative and is not scaled and rotated with the item
    // but that would require changing tst_qquickwindow::touchEvent_velocity(): it expects transformed velocity

    bool anyPressOrReleaseInside = false;
    bool anyGrabber = false;
    QMatrix4x4 transformMatrix(QQuickItemPrivate::get(item)->windowToItemTransform());
    for (int i = 0; i < m_pointCount; ++i) {
        auto p = m_touchPoints.at(i);
        if (p->isAccepted())
            continue;
        // include points where item is the grabber
        bool isGrabber = p->exclusiveGrabber() == item;
        if (isGrabber)
            anyGrabber = true;
        // include points inside the bounds if no other item is the grabber or if the item is filtering
        bool isInside = item->contains(item->mapFromScene(p->scenePos()));
        bool hasAnotherGrabber = p->exclusiveGrabber() && p->exclusiveGrabber() != item;

        // filtering: (childMouseEventFilter) include points that are grabbed by children of the target item
        bool grabberIsChild = false;
        auto parent = p->grabberItem();
        while (isFiltering && parent) {
            if (parent == item) {
                grabberIsChild = true;
                break;
            }
            parent = parent->parentItem();
        }

        bool filterRelevant = isFiltering && grabberIsChild;
        if (!(isGrabber || (isInside && (!hasAnotherGrabber || isFiltering)) || filterRelevant))
            continue;
        if ((p->state() == QQuickEventPoint::Pressed || p->state() == QQuickEventPoint::Released) && isInside)
            anyPressOrReleaseInside = true;
        const QTouchEvent::TouchPoint *tp = touchPointById(p->pointId());
        if (tp) {
            eventStates |= tp->state();
            QTouchEvent::TouchPoint tpCopy = *tp;
            tpCopy.setPos(item->mapFromScene(tpCopy.scenePos()));
            tpCopy.setLastPos(item->mapFromScene(tpCopy.lastScenePos()));
            tpCopy.setStartPos(item->mapFromScene(tpCopy.startScenePos()));
            tpCopy.setRect(item->mapRectFromScene(tpCopy.sceneRect()));
            tpCopy.setVelocity(transformMatrix.mapVector(tpCopy.velocity()).toVector2D());
            touchPoints << tpCopy;
        }
    }

    // Now touchPoints will have only points which are inside the item.
    // But if none of them were just pressed inside, and the item has no other reason to care, ignore them anyway.
    if (eventStates == Qt::TouchPointStationary || touchPoints.isEmpty() || (!anyPressOrReleaseInside && !anyGrabber && !isFiltering))
        return nullptr;

    // if all points have the same state, set the event type accordingly
    const QTouchEvent &event = *asTouchEvent();
    QEvent::Type eventType = event.type();
    switch (eventStates) {
    case Qt::TouchPointPressed:
        eventType = QEvent::TouchBegin;
        break;
    case Qt::TouchPointReleased:
        eventType = QEvent::TouchEnd;
        break;
    default:
        eventType = QEvent::TouchUpdate;
        break;
    }

    QTouchEvent *touchEvent = new QTouchEvent(eventType);
    touchEvent->setWindow(event.window());
    touchEvent->setTarget(item);
    touchEvent->setDevice(event.device());
    touchEvent->setModifiers(event.modifiers());
    touchEvent->setTouchPoints(touchPoints);
    touchEvent->setTouchPointStates(eventStates);
    touchEvent->setTimestamp(event.timestamp());
    touchEvent->accept();
    return touchEvent;
}

QTouchEvent *QQuickPointerTouchEvent::asTouchEvent() const
{
    return static_cast<QTouchEvent *>(m_event);
}

#ifndef QT_NO_DEBUG_STREAM

Q_QUICK_PRIVATE_EXPORT QDebug operator<<(QDebug dbg, const QQuickPointerDevice *dev) {
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    if (!dev) {
        dbg << "QQuickPointerDevice(0)";
        return dbg;
    }
    dbg << "QQuickPointerDevice("<< dev->name() << ' ';
    QtDebugUtils::formatQEnum(dbg, dev->type());
    dbg << ' ';
    QtDebugUtils::formatQEnum(dbg, dev->pointerType());
    dbg << " caps:";
    QtDebugUtils::formatQFlags(dbg, dev->capabilities());
    if (dev->type() == QQuickPointerDevice::TouchScreen ||
            dev->type() == QQuickPointerDevice::TouchPad)
        dbg << " maxTouchPoints:" << dev->maximumTouchPoints();
    else
        dbg << " buttonCount:" << dev->buttonCount();
    dbg << ')';
    return dbg;
}

Q_QUICK_PRIVATE_EXPORT QDebug operator<<(QDebug dbg, const QQuickPointerEvent *event) {
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QQuickPointerEvent(";
    if (event->isValid())
        dbg << event->timestamp();
    else
        dbg << "invalid";
    dbg << " dev:";
    QtDebugUtils::formatQEnum(dbg, event->device()->type());
    if (event->buttons() != Qt::NoButton) {
        dbg << " buttons:";
        QtDebugUtils::formatQEnum(dbg, event->buttons());
    }
    dbg << " [";
    int c = event->pointCount();
    for (int i = 0; i < c; ++i)
        dbg << event->point(i) << ' ';
    dbg << "])";
    return dbg;
}

Q_QUICK_PRIVATE_EXPORT QDebug operator<<(QDebug dbg, const QQuickEventPoint *event) {
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QQuickEventPoint(accepted:" << event->isAccepted()
        << " state:";
    QtDebugUtils::formatQEnum(dbg, event->state());
    dbg << " scenePos:" << event->scenePos() << " id:" << hex << event->pointId() << dec
        << " timeHeld:" << event->timeHeld() << ')';
    return dbg;
}

#endif

QT_END_NAMESPACE
