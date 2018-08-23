/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QVIRTUALKEYBOARDSELECTIONLISTMODEL_H
#define QVIRTUALKEYBOARDSELECTIONLISTMODEL_H

#include <QAbstractListModel>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardAbstractInputMethod;
class QVirtualKeyboardInputEngine;
class QVirtualKeyboardSelectionListModelPrivate;

class QVIRTUALKEYBOARD_EXPORT QVirtualKeyboardSelectionListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardSelectionListModel)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    explicit QVirtualKeyboardSelectionListModel(QObject *parent = nullptr);

public:
    enum Type
    {
        WordCandidateList = 0
    };
    enum Role
    {
        DisplayRole = Qt::DisplayRole,
        WordCompletionLengthRole = Qt::UserRole + 1,
        DictionaryTypeRole,
        CanRemoveSuggestionRole,
    };
    enum DictionaryType
    {
        DefaultDictionary = 0,
        UserDictionary
    };

    Q_ENUM(Type)
    Q_ENUM(Role)
    Q_ENUM(DictionaryType)

    ~QVirtualKeyboardSelectionListModel();
    void setDataSource(QVirtualKeyboardAbstractInputMethod *dataSource, Type type);
    QVirtualKeyboardAbstractInputMethod *dataSource() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

    int count() const;

    Q_INVOKABLE void selectItem(int index);
    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE QVariant dataAt(int index, int role = Qt::DisplayRole) const;

Q_SIGNALS:
    void countChanged();
    void activeItemChanged(int index);
    void itemSelected(int index);

protected Q_SLOTS:
    void selectionListChanged(int type);
    void selectionListActiveItemChanged(int type, int index);

private:
    friend class QVirtualKeyboardInputEngine;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::Type)
Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::Role)
Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::DictionaryType)

#endif // QVIRTUALKEYBOARDSELECTIONLISTMODEL_H