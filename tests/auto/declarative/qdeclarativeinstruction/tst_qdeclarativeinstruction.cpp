/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qtest.h>
#include <private/qdeclarativecompiler_p.h>

#ifdef Q_OS_SYMBIAN
// In Symbian OS test data is located in applications private dir
#define SRCDIR "."
#endif

class tst_qdeclarativeinstruction : public QObject
{
    Q_OBJECT
public:
    tst_qdeclarativeinstruction() {}

private slots:
    void dump();
};

static QStringList messages;
static void msgHandler(QtMsgType, const char *msg)
{
    messages << QLatin1String(msg);
}

void tst_qdeclarativeinstruction::dump()
{
    QDeclarativeCompiledData *data = new QDeclarativeCompiledData(0);
    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::Init;
        i.init.bindingsSize = 0;
        i.init.parserStatusSize = 3;
        i.init.contextCache = -1;
        i.init.compiledBinding = -1;
        data->bytecode << i;
    }

    {
        QDeclarativeCompiledData::TypeReference ref;
        ref.className = "Test";
        data->types << ref;

        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::CreateObject;
        i.create.type = 0;
        i.create.data = -1;
        i.create.bindingBits = -1;
        i.create.column = 10;
        data->bytecode << i;
    }

    {
        data->primitives << "testId";

        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::SetId;
        i.setId.value = data->primitives.count() - 1;
        i.setId.index = 0;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::SetDefault;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::CreateComponent;
        i.createComponent.count = 3;
        i.createComponent.column = 4;
        i.createComponent.endLine = 14;
        i.createComponent.metaObject = 0;

        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreMetaObject;
        i.storeMeta.data = 3;
        i.storeMeta.aliasData = 6;
        i.storeMeta.propertyCache = 7;

        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreFloat;
        i.storeFloat.propertyIndex = 3;
        i.storeFloat.value = 11.3;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreDouble;
        i.storeDouble.propertyIndex = 4;
        i.storeDouble.value = 14.8;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreInteger;
        i.storeInteger.propertyIndex = 5;
        i.storeInteger.value = 9;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreBool;
        i.storeBool.propertyIndex = 6;
        i.storeBool.value = true;

        data->bytecode << i;
    }

    {
        data->primitives << "Test String";
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreString;
        i.storeString.propertyIndex = 7;
        i.storeString.value = data->primitives.count() - 1;
        data->bytecode << i;
    }

    {
        data->urls << QUrl("http://www.nokia.com");
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreUrl;
        i.storeUrl.propertyIndex = 8;
        i.storeUrl.value = data->urls.count() - 1;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreColor;
        i.storeColor.propertyIndex = 9;
        i.storeColor.value = 0xFF00FF00;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreDate;
        i.storeDate.propertyIndex = 10;
        i.storeDate.value = 9;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreTime;
        i.storeTime.propertyIndex = 11;
        i.storeTime.valueIndex = 33;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreDateTime;
        i.storeDateTime.propertyIndex = 12;
        i.storeDateTime.valueIndex = 44;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StorePoint;
        i.storeRealPair.propertyIndex = 13;
        i.storeRealPair.valueIndex = 3;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StorePointF;
        i.storeRealPair.propertyIndex = 14;
        i.storeRealPair.valueIndex = 9;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreSize;
        i.storeRealPair.propertyIndex = 15;
        i.storeRealPair.valueIndex = 8;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreSizeF;
        i.storeRealPair.propertyIndex = 16;
        i.storeRealPair.valueIndex = 99;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreRect;
        i.storeRect.propertyIndex = 17;
        i.storeRect.valueIndex = 2;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreRectF;
        i.storeRect.propertyIndex = 18;
        i.storeRect.valueIndex = 19;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreVector3D;
        i.storeVector3D.propertyIndex = 19;
        i.storeVector3D.valueIndex = 9;
        data->bytecode << i;
    }

    {
        data->primitives << "color(1, 1, 1, 1)";
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreVariant;
        i.storeString.propertyIndex = 20;
        i.storeString.value = data->primitives.count() - 1;

        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreObject;
        i.storeObject.propertyIndex = 21;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreVariantObject;
        i.storeObject.propertyIndex = 22;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreInterface;
        i.storeObject.propertyIndex = 23;
        data->bytecode << i;
    }

    {
        data->primitives << "console.log(1921)";

        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreSignal;
        i.storeSignal.signalIndex = 2;
        i.storeSignal.value = data->primitives.count() - 1;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreScriptString;
        i.storeScriptString.propertyIndex = 24;
        i.storeScriptString.value = 3;
        i.storeScriptString.scope = 1;
        data->bytecode << i;
    }

    {
        data->datas << "mySignal";

        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::AssignSignalObject;
        i.assignSignalObject.signal = 0;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::AssignCustomType;
        i.assignCustomType.propertyIndex = 25;
        i.assignCustomType.valueIndex = 4;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreBinding;
        i.assignBinding.property = 26;
        i.assignBinding.value = 3;
        i.assignBinding.context = 2;
        i.assignBinding.owner = 0;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreCompiledBinding;
        i.assignBinding.property = 27;
        i.assignBinding.value = 2;
        i.assignBinding.context = 4;
        i.assignBinding.owner = 0;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreValueSource;
        i.assignValueSource.property = 29;
        i.assignValueSource.owner = 1;
        i.assignValueSource.castValue = 4;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreValueInterceptor;
        i.assignValueInterceptor.property = 30;
        i.assignValueInterceptor.owner = 2;
        i.assignValueInterceptor.castValue = -4;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::BeginObject;
        i.begin.castValue = 4;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreObjectQList;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::AssignObjectList;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::FetchAttached;
        i.fetchAttached.id = 23;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::FetchQList;
        i.fetch.property = 32;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::FetchObject;
        i.fetch.property = 33;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::FetchValueType;
        i.fetchValue.property = 34;
        i.fetchValue.type = 6;
        i.fetchValue.bindingSkipList = 7;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::PopFetchedObject;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::PopQList;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::PopValueType;
        i.fetchValue.property = 35;
        i.fetchValue.type = 8;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::Defer;
        i.defer.deferCount = 7;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::Defer;
        i.defer.deferCount = 7;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreImportedScript;
        i.storeScript.value = 2;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = (QDeclarativeInstruction::Type)(1234); // Non-existent
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreVariantInteger;
        i.storeInteger.value = 11;
        i.storeInteger.propertyIndex = 32;
        data->bytecode << i;
    }

    {
        QDeclarativeInstruction i;
        i.type = QDeclarativeInstruction::StoreVariantDouble;
        i.storeDouble.value = 33.7;
        i.storeDouble.propertyIndex = 19;
        data->bytecode << i;
    }

    QStringList expect;
    expect 
        << "Index\tOperation\t\tData1\tData2\tData3\tComments"
        << "-------------------------------------------------------------------------------"
        << "0\t\tINIT\t\t\t0\t3\t-1\t-1"
        << "1\t\tCREATE\t\t\t0\t-1\t\t\"Test\""
        << "2\t\tSETID\t\t\t0\t\t\t\"testId\""
        << "3\t\tSET_DEFAULT"
        << "4\t\tCREATE_COMPONENT\t3"
        << "5\t\tSTORE_META\t\t3"
        << "6\t\tSTORE_FLOAT\t\t3\t11.3"
        << "7\t\tSTORE_DOUBLE\t\t4\t14.8"
        << "8\t\tSTORE_INTEGER\t\t5\t9"
        << "9\t\tSTORE_BOOL\t\t6\ttrue"
        << "10\t\tSTORE_STRING\t\t7\t1\t\t\"Test String\""
        << "11\t\tSTORE_URL\t\t8\t0\t\tQUrl(\"http://www.nokia.com\") "
        << "12\t\tSTORE_COLOR\t\t9\t\t\t\"ff00ff00\""
        << "13\t\tSTORE_DATE\t\t10\t9"
        << "14\t\tSTORE_TIME\t\t11\t33"
        << "15\t\tSTORE_DATETIME\t\t12\t44"
        << "16\t\tSTORE_POINT\t\t13\t3"
        << "17\t\tSTORE_POINTF\t\t14\t9"
        << "18\t\tSTORE_SIZE\t\t15\t8"
        << "19\t\tSTORE_SIZEF\t\t16\t99"
        << "20\t\tSTORE_RECT\t\t17\t2"
        << "21\t\tSTORE_RECTF\t\t18\t19"
        << "22\t\tSTORE_VECTOR3D\t\t19\t9"
        << "23\t\tSTORE_VARIANT\t\t20\t2\t\t\"color(1, 1, 1, 1)\""
        << "24\t\tSTORE_OBJECT\t\t21"
        << "25\t\tSTORE_VARIANT_OBJECT\t22"
        << "26\t\tSTORE_INTERFACE\t\t23"
        << "27\t\tSTORE_SIGNAL\t\t2\t3\t\t\"console.log(1921)\""
        << "28\t\tSTORE_SCRIPT_STRING\t24\t3\t1"
        << "29\t\tASSIGN_SIGNAL_OBJECT\t0\t\t\t\"mySignal\""
        << "30\t\tASSIGN_CUSTOMTYPE\t25\t4"
        << "31\t\tSTORE_BINDING\t26\t3\t2"
        << "32\t\tSTORE_COMPILED_BINDING\t27\t2\t4"
        << "33\t\tSTORE_VALUE_SOURCE\t29\t4"
        << "34\t\tSTORE_VALUE_INTERCEPTOR\t30\t-4"
        << "35\t\tBEGIN\t\t\t4"
        << "36\t\tSTORE_OBJECT_QLIST"
        << "37\t\tASSIGN_OBJECT_LIST"
        << "38\t\tFETCH_ATTACHED\t\t23"
        << "39\t\tFETCH_QLIST\t\t32"
        << "40\t\tFETCH\t\t\t33"
        << "41\t\tFETCH_VALUE\t\t34\t6\t7"
        << "42\t\tPOP"
        << "43\t\tPOP_QLIST"
        << "44\t\tPOP_VALUE\t\t35\t8"
        << "45\t\tDEFER\t\t\t7"
        << "46\t\tDEFER\t\t\t7"
        << "47\t\tSTORE_IMPORTED_SCRIPT\t2"
        << "48\t\tXXX UNKNOWN INSTRUCTION\t1234"
        << "49\t\tSTORE_VARIANT_INTEGER\t\t32\t11"
        << "50\t\tSTORE_VARIANT_DOUBLE\t\t19\t33.7"
        << "-------------------------------------------------------------------------------";

    messages = QStringList();
    QtMsgHandler old = qInstallMsgHandler(msgHandler);
    data->dumpInstructions();
    qInstallMsgHandler(old);

    QCOMPARE(messages.count(), expect.count());
    for (int ii = 0; ii < messages.count(); ++ii) {
        QCOMPARE(messages.at(ii), expect.at(ii));
    }

    data->release();
}

QTEST_MAIN(tst_qdeclarativeinstruction)

#include "tst_qdeclarativeinstruction.moc"
