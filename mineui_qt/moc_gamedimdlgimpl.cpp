/****************************************************************************
** GameDimDlg meta object code from reading C++ file 'gamedimdlgimpl.h'
**
** Created: Sat Jul 13 23:27:46 2002
**      by: The Qt MOC ($Id: moc_gamedimdlgimpl.cpp,v 1.3 2002-07-14 00:54:30+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "gamedimdlgimpl.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *GameDimDlg::className() const
{
    return "GameDimDlg";
}

QMetaObject *GameDimDlg::metaObj = 0;

void GameDimDlg::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(GameDimDlgBase::className(), "GameDimDlgBase") != 0 )
    badSuperclassWarning("GameDimDlg","GameDimDlgBase");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString GameDimDlg::tr(const char* s)
{
    return qApp->translate( "GameDimDlg", s, 0 );
}

QString GameDimDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "GameDimDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* GameDimDlg::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) GameDimDlgBase::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (GameDimDlg::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (GameDimDlg::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    m1_t0 v1_0 = &GameDimDlg::acceptWithValidate;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &GameDimDlg::setPercentSlot;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "acceptWithValidate()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "setPercentSlot()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
    "GameDimDlg", "GameDimDlgBase",
    slot_tbl, 2,
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
