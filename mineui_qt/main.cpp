#include "StdAfx.h"

#include <qapplication.h>
#include "mineui_qtwindow.h"
#include "uidrawcontextqt.h"
#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <qmessagebox.h>
#include <mineui_common/TransientDictionary.h>
#include <mineui_common/RCFileDictionary.h>
#include <stdio.h>
#include <qdir.h>

static QString getMineIconPath(const std::string &dirArg, const char *pszIconFilename) {
  // return kapp->kde_datadir() + QString("/mineui_kde/") + QString(pszIconFilename);

  std::string dir(dirArg); 
  if (dir.size() > 0 && dir[dir.size()-1] != '\\' && dir[dir.size()-1] != '/') 
  {
      dir += "/"; 
  }

  // the path below points to the location of the bitmaps in the dev environment
  return QString(dir.c_str()) + QString(pszIconFilename);
}

static CIconSetBase *loadIconSet(CPersistentDictionary *pDict, const char *pszFileName, const char *pszResName, int nXCount) 
{
    CUISystemQt *pQtSys = CUISystemQt::instanceQt();
    std::string iconDir; 
    bool bLoadIcons = pDict->getString("icondir", iconDir); 
    if (bLoadIcons) {
	return pQtSys->loadIconSet(getMineIconPath(iconDir, pszFileName), nXCount, 1); 
    }
    else {
	return pQtSys->loadIconSetEmbedded(pszResName, nXCount, 1); 
    }
}

static void fatalError(const std::string &msg) {
  QMessageBox::critical(NULL, "Fatal error", QString(msg.c_str()));
  fprintf(stderr, "Fatal Error: %s\n", msg.c_str());
  exit(1);
}

int main( int argc, char** argv )
{
   QApplication app( argc, argv );

   // initialize minesweeper
   if (CUISystemQt::instance() == NULL)
      CUISystemQt::setInstance(new CUISystemQt);

   std::string rcfile; 

   if (argc>=2) {
      rcfile = argv[1]; 
   }
   else {
       QDir homeDir(QDir::home());
       rcfile = std::string(homeDir.filePath(".truffleswinekeeperrc")); 
       // rcfile = ".truffleswinekeeperrc"; 
   }

   CRCFileDictionary *pDict = new CRCFileDictionary(rcfile, "game"); 
   if (!pDict->verify()) 
      fatalError("Unable to create .truffleswinekeeperrc"); 
   
   if (CGlobalResourceSet::instance() == NULL)
   {
      CGlobalResourceSet *pRes = new CGlobalResourceSet;
        
      std::auto_ptr<CIconSetBase> pSmilies(loadIconSet(pDict, "Smilies.bmp", "Smilies", IconType::SMILIE_COUNT)); 
      std::auto_ptr<CIconSetBase> pDigits(loadIconSet(pDict, "Digits.bmp", "Digits_padded", IconType::DIGIT_COUNT)); 
      std::auto_ptr<CIconSetBase> pFieldIcons(loadIconSet(pDict, "FieldIcons.bmp", "FieldIcons", IconType::FIELD_COUNT)); 
      std::auto_ptr<CIconSetBase> pFieldInfos(loadIconSet(pDict, "FieldInfos.bmp", "FieldInfos", IconType::FIELDINFO_COUNT)); 

      pRes->m_pSmilies = pSmilies;
      pRes->m_pDigits = pDigits;
      pRes->m_pFieldIcons = pFieldIcons;
      pRes->m_pFieldInfoIcons = pFieldInfos;

      if (!pRes->isValid())
         fatalError("Unable to load bitmaps!\n"
                    "(They should be in the directory specified by the entry 'icondir' in the rc file)"); 

      CGlobalResourceSet::setInstance(pRes);
   }

    MineUI_QtWindow window(pDict);
    app.setMainWidget(&window);

    window.show();

    return app.exec();
}

