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
#include "espressiftoolchain.h"
#include "espressifconstants.h"

#include "projectexplorer/toolchain.h"
#include "projectexplorer/projectexplorerconstants.h"
#include "utils/pathchooser.h"

#include <QLabel>
#include <QFormLayout>

using namespace ProjectExplorer;
using namespace Utils;

namespace Espressif {
namespace Internal {

static QStringList reinterpretOptions(const QStringList &args)
{
    return args;
}

EspressifToolChain::EspressifToolChain(ToolChain::Detection d)
    : GccToolChain(Constants::ESPRESSIF_TOOLCHAIN_ID, d)
{
    setOptionsReinterpreter(&reinterpretOptions);
}

EspressifToolChain::EspressifToolChain(Core::Id l, ToolChain::Detection d)
    : EspressifToolChain(d)
{
    setLanguage(l);
}

QString EspressifToolChain::typeDisplayName() const
{
    return EspressifToolChainFactory::tr("Espressif");
}

ToolChainConfigWidget *EspressifToolChain::configurationWidget()
{
    return new EspressifToolChainConfigWidget(this);
}

// --------------------------------------------------------------------------
// EspressifToolChainFactory
// --------------------------------------------------------------------------

EspressifToolChainFactory::EspressifToolChainFactory()
{
    setDisplayName(tr("Espressif"));
}

QSet<Core::Id> EspressifToolChainFactory::supportedLanguages() const
{
    return {ProjectExplorer::Constants::C_LANGUAGE_ID};
}

bool EspressifToolChainFactory::canCreate()
{
    return true;
}

ToolChain *EspressifToolChainFactory::create(Core::Id l)
{
    return new EspressifToolChain(l, ToolChain::ManualDetection);
}

// --------------------------------------------------------------------------
// ToolChainConfigWidget
// --------------------------------------------------------------------------

EspressifToolChainConfigWidget::EspressifToolChainConfigWidget(EspressifToolChain *tc)
    : ToolChainConfigWidget(tc)
    , m_compilerCommand(new PathChooser)
{
    m_compilerCommand->setExpectedKind(PathChooser::File);
    m_compilerCommand->setFileName(FileName::fromString("xtensa-lx106-elf-gcc"));
    m_mainLayout->addRow(tr("Compiler path:"), m_compilerCommand);

    connect(m_compilerCommand, &PathChooser::rawPathChanged,
            this, &EspressifToolChainConfigWidget::handleCompilerCommandChange);
}

void EspressifToolChainConfigWidget::handleCompilerCommandChange()
{
    // TODO : validate the compiler

    emit dirty();
}

} // namespace Internal
} // namespace Espressif
