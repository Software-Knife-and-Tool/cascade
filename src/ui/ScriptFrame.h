/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ScriptFrame.h: ScriptFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_SCRIPTFRAME_H_
#define _GYREIDE_SRC_UI_SCRIPTFRAME_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <utility>
 
#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QScroll;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreide {

class MainTabBar;
class MainWindow;
  
class ScriptFrame : public QFrame {

 Q_OBJECT

 public:
  explicit ScriptFrame(QString, MainTabBar*, GyreEnv*, GyreEnv*);
  
 private:
  static const size_t FNV_prime = 16777619;
  static const uint64_t OFFSET_BASIS = 2166136261UL;
 
  typedef std::unordered_map<uint32_t, QObject*> object_map;
  typedef object_map::const_iterator object_iter;
 
  static object_iter find(const std::shared_ptr<object_map>& map, QString key) {
    return map->find(hash_id(key));
  }
 
  static bool isFound(const std::shared_ptr<object_map>& map, object_iter el) {
    return el != map->end();
  }
 
  static QObject* Insert(const std::shared_ptr<object_map>& map, QString key,
                       QObject* object) {
    (*map.get())[hash_id(key)] = object;
    return object;
  }
 
  static uint64_t hash_id(QString str) {
    uint64_t hash = OFFSET_BASIS;

    for (auto ch : str) {
      hash ^= ch.toLatin1();
      hash *= FNV_prime;
    }
 
    return hash;
  }

 private:
  /** * parser **/
  enum TYPE { FIXNUM, FLOAT, SYMBOL, STRING, LIST };

  struct tag {
    TYPE type;
    QString value;
  };
  
  std::vector<struct tag> parse(QString);  
 
  void evalFrame(GyreEnv*);
  QString evalString(QString, GyreEnv*);

  void clear();
  void load();
  void reset();
  void save();
  void save_as();
  void del();

  void loadConfigFile();
  
  void setContextStatus(QString str) {
    tabBar->setContextStatus(str);
  }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }
  
  void log(QString msg) { tabBar->log(msg); }

  bool eventFilter(QObject*, QEvent*) override;

  static std::string script(std::string);

#if 0
  QString invoke(std::string(*)(std::string), QString);
#endif
  
  static constexpr unsigned int hash(const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
  }

  QString scriptIdOf(std::string (* fn)(std::string)) {
    auto fnp = reinterpret_cast<uint64_t>(fn);

    return QString("%1").arg(fnp);
  }
  
  QString contextIdOf() {
    auto ctxp = reinterpret_cast<uint64_t>(this);

    return QString("%1").arg(ctxp);
  }

  QString loadFileName;
  QString saveFileName;

  MainTabBar *tabBar;
  GyreEnv* devEnv;
  GyreEnv* ideEnv;
  QString name;
  QTextEdit* editText;
  QLabel* evalText;
  QToolBar* toolBar;
  QScrollArea* editScroll;
  QScrollArea* evalScroll;
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_SCRIPTFRAME_H_ */
