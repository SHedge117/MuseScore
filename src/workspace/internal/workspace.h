/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_WORKSPACE_WORKSPACE_H
#define MU_WORKSPACE_WORKSPACE_H

#include "io/path.h"
#include "async/asyncable.h"
#include "iworkspace.h"
#include "workspacefile.h"

#include "modularity/ioc.h"
#include "multiinstances/imultiinstancesprovider.h"

namespace mu::workspace {
class Workspace : public IWorkspace, public async::Asyncable
{
    INJECT(workspace, mi::IMultiInstancesProvider, multiInstancesProvider)

public:
    Workspace(const io::path& filePath);

    std::string name() const override;
    std::string title() const override;

    bool isManaged(const DataKey& key) const override;
    void setIsManaged(const DataKey& key, bool val) override;

    RetVal<QByteArray> rawData(const DataKey& key) const override;
    Ret setRawData(const DataKey& key, const QByteArray& data) override;

    async::Notification reloadNotification() override;

    io::path filePath() const;
    bool isLoaded() const;
    Ret load();
    Ret save();

private:
    void reload();

    std::string fileResourceName() const;

    WorkspaceFile m_file;

    async::Notification m_reloadNotification;
};

using WorkspacePtr = std::shared_ptr<Workspace>;
}

#endif // MU_WORKSPACE_WORKSPACE_H
