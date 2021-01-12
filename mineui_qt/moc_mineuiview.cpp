/****************************************************************************
** MineUIView meta object code from reading C++ file 'mineuiview.h'
**
** Created: Sat Jul 13 23:27:57 2002
**      by: The Qt MOC ($Id: moc_mineuiview.cpp,v 1.4 2002-07-14 00:54:30+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mineuiview.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *MineUIView::className() const
{
    return "MineUIView";
}

QMetaObject *MineUIView::metaObj = 0;

void MineUIView::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
    badSuperclassWarning("MineUIView","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MineUIView::tr(const char* s)
{
    return qApp->translate( "MineUIView", s, 0 );
}

QString MineUIView::tr(const char* s, const char * c)
{
    return qApp->translate( "MineUIView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MineUIView::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MineUIView::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (MineUIView::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (MineUIView::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (MineUIView::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (MineUIView::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    m1_t0 v1_0 = &MineUIView::solveSlot;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MineUIView::resetSolveSlot;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MineUIView::prevSlot;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &MineUIView::nextSlot;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &MineUIView::updateTimeSlot;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "solveSlot()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "resetSolveSlot()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "prevSlot()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "nextSlot()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "updateTimeSlot()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
    "MineUIView", "QWidget",
    slot_tbl, 5,
    0, 0,
#ifndef QT_NO_PROPERTIES
    0, 0,
    0, 0,
#endif // QT_NO_PROPERTIES
    0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
