/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include <QObject>
#include <QPointer>

class DeclarativeInputContext;
class DeclarativeSelectionListModel;
class AbstractInputMethod;
class DeclarativeInputEnginePrivate;

class DeclarativeInputEngine : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarativeInputEngine)
    Q_DECLARE_PRIVATE(DeclarativeInputEngine)
    Q_ENUMS(TextCase)
    Q_ENUMS(InputMode)
    Q_PROPERTY(Qt::Key activeKey READ activeKey NOTIFY activeKeyChanged)
    Q_PROPERTY(Qt::Key previousKey READ previousKey NOTIFY previousKeyChanged)
    Q_PROPERTY(AbstractInputMethod *inputMethod READ inputMethod WRITE setInputMethod NOTIFY inputMethodChanged)
    Q_PROPERTY(QList<int> inputModes READ inputModes NOTIFY inputModesChanged)
    Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged)
    Q_PROPERTY(DeclarativeSelectionListModel *wordCandidateListModel READ wordCandidateListModel NOTIFY wordCandidateListModelChanged)
    Q_PROPERTY(bool wordCandidateListVisibleHint READ wordCandidateListVisibleHint NOTIFY wordCandidateListVisibleHintChanged)

    explicit DeclarativeInputEngine(DeclarativeInputContext *parent = 0);

public:
    enum TextCase {
        Lower,
        Upper
    };
    enum InputMode {
        Latin,
        Numeric,
        Dialable
    };

public:
    ~DeclarativeInputEngine();

    Q_INVOKABLE bool virtualKeyPress(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers, bool repeat);
    Q_INVOKABLE void virtualKeyCancel();
    Q_INVOKABLE bool virtualKeyRelease(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);
    Q_INVOKABLE bool virtualKeyClick(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    DeclarativeInputContext *inputContext() const;
    Qt::Key activeKey() const;
    Qt::Key previousKey() const;

    AbstractInputMethod *inputMethod() const;
    void setInputMethod(AbstractInputMethod *inputMethod);

    QList<int> inputModes() const;

    InputMode inputMode() const;
    void setInputMode(InputMode inputMode);

    DeclarativeSelectionListModel *wordCandidateListModel() const;
    bool wordCandidateListVisibleHint() const;

signals:
    void virtualKeyClicked(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);
    void activeKeyChanged(Qt::Key key);
    void previousKeyChanged(Qt::Key key);
    void inputMethodChanged();
    void inputMethodReset();
    void inputMethodUpdate();
    void inputModesChanged();
    void inputModeChanged();
    void wordCandidateListModelChanged();
    void wordCandidateListVisibleHintChanged();

private slots:
    void reset();
    void update();
    void shiftChanged();
    void localeChanged();

protected:
    void timerEvent(QTimerEvent *timerEvent);

private:
    friend class DeclarativeInputContext;
};

Q_DECLARE_METATYPE(DeclarativeInputEngine::TextCase)
Q_DECLARE_METATYPE(DeclarativeInputEngine::InputMode)

#endif