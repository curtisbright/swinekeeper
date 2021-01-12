/****************************************************************************
** ScoreNameDlg meta object code from reading C++ file 'scorenamedlgimpl.h'
**
** Created: Sat Jul 13 23:28:02 2002
**      by: The Qt MOC ($Id: moc_scorenamedlgimpl.cpp,v 1.4 2002-07-14 00:54:31+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "scorenamedlgimpl.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *ScoreNameDlg::className() const
{
    return "ScoreNameDlg";
}

QMetaObject *ScoreNameDlg::metaObj = 0;

void ScoreNameDlg::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(ScoreNameDlgBase::className(), "ScoreNameDlgBase") != 0 )
    badSuperclassWarning("ScoreNameDlg","ScoreNameDlgBase");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ScoreNameDlg::tr(const char* s)
{
    return qApp->translate( "ScoreNameDlg", s, 0 );
}

QString ScoreNameDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "ScoreNameDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ScoreNameDlg::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) ScoreNameDlgBase::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
    "ScoreNameDlg", "ScoreNameDlgBase",
    0, 0,
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
