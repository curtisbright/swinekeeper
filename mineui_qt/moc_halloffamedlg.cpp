/****************************************************************************
** HallOfFameDlgBase meta object code from reading C++ file 'halloffamedlg.h'
**
** Created: Sat Jul 13 23:28:08 2002
**      by: The Qt MOC ($Id: moc_halloffamedlg.cpp,v 1.4 2002-07-14 00:54:30+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "halloffamedlg.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *HallOfFameDlgBase::className() const
{
    return "HallOfFameDlgBase";
}

QMetaObject *HallOfFameDlgBase::metaObj = 0;

void HallOfFameDlgBase::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
    badSuperclassWarning("HallOfFameDlgBase","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString HallOfFameDlgBase::tr(const char* s)
{
    return qApp->translate( "HallOfFameDlgBase", s, 0 );
}

QString HallOfFameDlgBase::tr(const char* s, const char * c)
{
    return qApp->translate( "HallOfFameDlgBase", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* HallOfFameDlgBase::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
    "HallOfFameDlgBase", "QDialog",
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
