/*******
 **
 ** Copyright (c) 2017, James M. Putnam
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** 1. Redistributions of source code must retain the above copyright notice,
 **    this list of conditions and the following disclaimer.
 **
 ** 2. Redistributions in binary form must reproduce the above copyright
 **    notice, this list of conditions and the following disclaimer in the
 **    documentation and/or other materials provided with the distribution.
 **
 ** 3. Neither the name of the copyright holder nor the names of its
 **    contributors may be used to endorse or promote products derived from
 **    this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 ** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 ** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 ** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 ** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 ** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 ** POSSIBILITY OF SUCH DAMAGE.
 **
 *******/

/********
 **
 **  ScriptFrame.h: ScriptFrame class
 **
 **/
#ifndef _LOGICAIDE_SRC_UI_SCRIPTFRAME_H_
#define _LOGICAIDE_SRC_UI_SCRIPTFRAME_H_

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

#include "CanonEnv.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QScroll;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace logicaide {

class MainTabBar;
class MainWindow;
  
class ScriptFrame : public QFrame {

 Q_OBJECT

 public:
  explicit ScriptFrame(QString, MainTabBar*, CanonEnv*, CanonEnv*);
  
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
  void clear();
  void evalFrame(CanonEnv*);
  QString evalString(QString, CanonEnv*);
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
  static constexpr unsigned int hash(const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
  }

  QString idOf(std::string (*)(std::string));
  QString invoke(std::string(*)(std::string), QString);

  QString loadFileName;
  QString saveFileName;

  MainTabBar *tabBar;
  CanonEnv* devEnv;
  CanonEnv* ideEnv;
  QString name;
  QTextEdit* editText;
  QLabel* evalText;
  QToolBar* toolBar;
  QScrollArea* editScroll;
  QScrollArea* evalScroll;
};

} /* logicaide namespace */

#endif  /* _LOGICAIDE_SRC_UI_SCRIPTFRAME_H_ */
