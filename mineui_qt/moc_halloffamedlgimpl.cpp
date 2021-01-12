/****************************************************************************
** HallOfFameDlg meta object code from reading C++ file 'halloffamedlgimpl.h'
**
** Created: Sat Jul 13 23:27:49 2002
**      by: The Qt MOC ($Id: moc_halloffamedlgimpl.cpp,v 1.4 2002-07-14 00:54:30+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "halloffamedlgimpl.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *HallOfFameDlg::className() const
{
    return "HallOfFameDlg";
}

QMetaObject *HallOfFameDlg::metaObj = 0;

void HallOfFameDlg::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(HallOfFameDlgBase::className(), "HallOfFameDlgBase") != 0 )
    badSuperclassWarning("HallOfFameDlg","HallOfFameDlgBase");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString HallOfFameDlg::tr(const char* s)
{
    return qApp->translate( "HallOfFameDlg", s, 0 );
}

QString HallOfFameDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "HallOfFameDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* HallOfFameDlg::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) HallOfFameDlgBase::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (HallOfFameDlg::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &HallOfFameDlg::clearScoreTable;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "clearScoreTable()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
    "HallOfFameDlg", "HallOfFameDlgBase",
    slot_tbl, 1,
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
