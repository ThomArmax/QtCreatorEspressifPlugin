/****************************************************************************
**
** Copyright (c) 2018 Thomas COIN
** Contact: Thomas Coin<esvcorp@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/
#ifndef ESPRESSIFTOOLCHAIN_H
#define ESPRESSIFTOOLCHAIN_H

#pragma once

#include <projectexplorer/gcctoolchain.h>
#include <projectexplorer/gcctoolchainfactories.h>

namespace Espressif {
namespace Internal {

// --------------------------------------------------------------------------
// EspressifToolChain
// --------------------------------------------------------------------------

class EspressifToolChain : public ProjectExplorer::GccToolChain
{
public:
    explicit EspressifToolChain(Detection d);
    explicit EspressifToolChain(Core::Id l, Detection d);

    QString typeDisplayName() const override;
    ProjectExplorer::ToolChainConfigWidget *configurationWidget() override;
};

// --------------------------------------------------------------------------
// EspressifToolChainFactory
// --------------------------------------------------------------------------

class EspressifToolChainFactory : public ProjectExplorer::ToolChainFactory
{
    Q_OBJECT

public:
    EspressifToolChainFactory();

    QSet<Core::Id> supportedLanguages() const override;

    bool canCreate() override;
    ProjectExplorer::ToolChain *create(Core::Id l) override;
};

// --------------------------------------------------------------------------
// EspressifToolChainConfigWidget
// --------------------------------------------------------------------------

class EspressifToolChainConfigWidget : public ProjectExplorer::ToolChainConfigWidget
{
    Q_OBJECT
public:
    explicit EspressifToolChainConfigWidget(EspressifToolChain *tc);

private:
    void handleCompilerCommandChange();

    void applyImpl() override {}
    void discardImpl() override {}
    bool isDirtyImpl() const override { return false; }
    void makeReadOnlyImpl() override {}

    Utils::PathChooser *m_compilerCommand;
};


} // namespace Internal
} // namespace Espressif

#endif // ESPRESSIFTOOLCHAIN_H
