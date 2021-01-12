/****************************************************************************
** MineUI_QtWindow meta object code from reading C++ file 'mineui_qtwindow.h'
**
** Created: Sat Jul 13 23:27:53 2002
**      by: The Qt MOC ($Id: moc_mineui_qtwindow.cpp,v 1.4 2002-07-14 00:54:31+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mineui_qtwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *MineUI_QtWindow::className() const
{
    return "MineUI_QtWindow";
}

QMetaObject *MineUI_QtWindow::metaObj = 0;

void MineUI_QtWindow::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(QMainWindow::className(), "QMainWindow") != 0 )
    badSuperclassWarning("MineUI_QtWindow","QMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MineUI_QtWindow::tr(const char* s)
{
    return qApp->translate( "MineUI_QtWindow", s, 0 );
}

QString MineUI_QtWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "MineUI_QtWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MineUI_QtWindow::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) QMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MineUI_QtWindow::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (MineUI_QtWindow::*m1_t1)(int);
    typedef void (QObject::*om1_t1)(int);
    typedef void (MineUI_QtWindow::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (MineUI_QtWindow::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (MineUI_QtWindow::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (MineUI_QtWindow::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (MineUI_QtWindow::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (MineUI_QtWindow::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    typedef void (MineUI_QtWindow::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    typedef void (MineUI_QtWindow::*m1_t9)();
    typedef void (QObject::*om1_t9)();
    m1_t0 v1_0 = &MineUI_QtWindow::game_newGame;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MineUI_QtWindow::game_setGameLevelSlot;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MineUI_QtWindow::game_toggleMarker;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &MineUI_QtWindow::game_showHallOfFame;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &MineUI_QtWindow::game_quit;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &MineUI_QtWindow::view_solve;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &MineUI_QtWindow::view_reset;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &MineUI_QtWindow::view_prev;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &MineUI_QtWindow::view_next;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &MineUI_QtWindow::help_about;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    QMetaData *slot_tbl = QMetaObject::new_metadata(10);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(10);
    slot_tbl[0].name = "game_newGame()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "game_setGameLevelSlot(int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "game_toggleMarker()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "game_showHallOfFame()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "game_quit()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "view_solve()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "view_reset()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "view_prev()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "view_next()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "help_about()";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
    "MineUI_QtWindow", "QMainWindow",
    slot_tbl, 10,
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
