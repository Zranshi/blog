---
title: 我的vscode自定义化过程
date: 2021-8-5 10:33:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - vscode
  - 工具
keywords: 工具
description: idea挺好用的，但是我选vscode.jpg
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/80438411_p0.png
---

## 前言

终于开始折腾编辑器了，就怕最后折腾完又回到起点。

我之前一直是使用 idea+python 插件+golang 插件+rust 插件作为日常使用的，然后使用 ide-eval-resetter 插件逃票(⁎⁍̴̛ᴗ⁍̴̛⁎)，因为实在是负担不起那高昂的费用，也懒得去注册学生账号。然后 vscode 仅仅作为日常的 markdown 编写（因为在曾经在知乎上看到了有人关于 idea 和 vscode 的讨论，普遍认为 vscode 不适合作为大型工程的编辑器使用，而工作后为了效率总会回归 idea 的怀抱的 ♪(´ε ｀ )）所以一直没有去尝试将 vscode 作为主力使用的编辑器。

那么是什么原因导致我抛弃 idea 了呢？主要原因是我想写 c++代码，仅仅作为考研的算法题目编写。而在 idea 上这似乎非常困难。具体有一下几点让我有动力去体验 vscode。

- idea 上的 C/C++插件不适用与当前版本（2021.2），于是想要编写 C/C++就需要下载 CLion，而总所周知，JB 系列每个 ide 都超级巨大（至少有 1G 吧），而我的 Mac mini 只有 256G 存储(T ^ T)。而且感觉仅仅为了编写算法题就下载一个专门的编辑器，有种高射炮打蚊子的感觉。
- 我也曾使用过 CLion，但总感觉 CMake 很难用，至少和以前的使用过习惯非常不同（我仅仅只是想写个算法题，用得着这么麻烦嘛！(╯‵□′)╯︵┻━┻）
- 为啥 idea 上总会有那么多的 Java 元素，我又不用 Java。为啥不能出一个啥语言预设都没有，可以自定义安装插件的平台呢？我懂，因为那样卖的钱就少了，唉(´Д` )
- vscode 上 C/C++还挺好配置的，首先 Mac 上本身就有 gcc 编译器，只用下载一个 C/C++插件就完全够用了！ε-(´∀ ｀; )，非常适合我这种怕麻烦，还患有“pc 存储恐惧症 ”的患者。
- 有着一点点私心的极客想法，觉得开源超帅！自定义超帅！所以慢慢地从“以后 C/C++代码就在 vscode 上写吧”到“vscode 就是我家，idea 滚出我的电脑！”，逐渐极端化了呢 ╮(╯▽╰)╭

大致上就是以上的这些原因，总而言之，并不是 idea 不香，而是 vscode 更适合我！（这种无从得出的结论，为了不引战我还真的说得出口呀）。但现在回顾整个配置过程，觉得 vscode 的自定义化之旅并不容易，但一点都不无聊，反而让我感到快乐。所以在此分享我的配置过程(((o(_ﾟ ▽ ﾟ_)o)))

## 配置

不说废话了，先贴出我的 setting.json

```json
{
  // 单独文件设置
  "[go]": {
    "editor.codeActionsOnSave": {
      "source.organizeImports": true
    },
    "editor.formatOnSave": true,
    "editor.insertSpaces": true
  },
  "[html]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  "[http]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "editor.quickSuggestions": {
      "comments": false,
      "other": true,
      "strings": true
    },
    "editor.tabSize": 2
  },
  "[javascript]": {
    "editor.codeActionsOnSave": {
      "source.fixAll": true,
      "source.organizeImports": true
    },
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "editor.detectIndentation": false,
    "editor.tabSize": 2
  },
  "[javascriptreact]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  "[json]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "editor.detectIndentation": false,
    "editor.tabSize": 2
  },
  "[jsonc]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  "[markdown]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  "[python]": {
    "editor.codeActionsOnSave": {
      "source.fixAll": true,
      "source.organizeImports": true
    }
  },
  "[rust]": {
    "editor.codeActionsOnSave": {
      "source.fixAll": true,
      "source.organizeImports": true
    },
    "editor.defaultFormatter": "rust-lang.rust"
  },
  "[vue]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "editor.detectIndentation": false,
    "editor.tabSize": 2
  },
  "[yaml]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  // python 生成文档
  "autoDocstring.startOnNewLine": true,
  // 彩色注释
  "better-comments.highlightPlainText": true,
  "better-comments.tags": [
    {
      "backgroundColor": "transparent",
      "bold": true,
      "color": "#FF8C00",
      "italic": false,
      "strikethrough": false,
      "tag": "todo",
      "underline": false
    },
    {
      "backgroundColor": "transparent",
      "bold": false,
      "color": "#3498DB",
      "italic": false,
      "strikethrough": false,
      "tag": "@",
      "underline": false
    }
  ],
  "bracketPairColorizer.consecutivePairColors": ["()", "[]", "{}", ["Cyan"], "Red"],
  "bracketPairColorizer.forceUniqueOpeningColor": true,
  "breadcrumbs.enabled": false,
  // C++格式化
  "C_Cpp.autocompleteAddParentheses": true,
  "C_Cpp.clang_format_fallbackStyle": "Google",
  "C_Cpp.clang_format_sortIncludes": true,
  "C_Cpp.clang_format_style": "Google",
  // code runner
  "code-runner.executorMap": {
    "applescript": "osascript",
    "bat": "cmd /c",
    "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "csharp": "scriptcs",
    "dart": "dart",
    "fsharp": "fsi",
    "go": "cd $dir && go run $fileName",
    "groovy": "groovy",
    "haskell": "runhaskell",
    "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
    "javascript": "node",
    "julia": "julia",
    "less": "cd $dir && lessc $fileName $fileNameWithoutExt.css",
    "lisp": "sbcl --script",
    "lua": "lua",
    "nim": "nim compile --verbosity:0 --hints:off --run",
    "objective-c": "cd $dir && gcc -framework Cocoa $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "php": "php",
    "powershell": "powershell -ExecutionPolicy ByPass -File",
    "python": "python3 -u $fullFileName",
    "r": "Rscript",
    "ruby": "ruby",
    "rust": "cd $dir && rustc $fileName && $dir$fileNameWithoutExt",
    "sass": "sass --style expanded",
    "scala": "scala",
    "scss": "scss --style expanded",
    "shellscript": "bash",
    "swift": "swift",
    "typescript": "ts-node"
  },
  "code-runner.ignoreSelection": true,
  "code-runner.runInTerminal": true,
  "code-runner.saveFileBeforeRun": true,
  "customizeUI.activityBar": "bottom",
  // vscode advanced 界面
  "customizeUI.font.monospace": "JetBrains Mono",
  "customizeUI.font.regular": "JetBrains Mono",
  "customizeUI.fontSizeMap": {
    "12px": "14px",
    "13px": "15px",
    "menu": "13px",
    "monospace": "15px",
    "tab-title": "14px",
    "window-title": "14px"
  },
  "customizeUI.listRowHeight": 25,
  "customizeUI.moveStatusbar": true,
  "customizeUI.titleBar": "frameless",
  // debug界面
  "debug.allowBreakpointsEverywhere": true,
  "debug.console.fontFamily": "JetBrains Mono",
  "debug.console.fontSize": 16,
  "debug.inlineValues": true,
  "debug.showBreakpointsInOverviewRuler": true,
  "diffEditor.codeLens": true,
  // editor
  "editor.acceptSuggestionOnEnter": "on",
  "editor.cursorBlinking": "solid",
  "editor.cursorSmoothCaretAnimation": true,
  "editor.cursorWidth": 2,
  "editor.detectIndentation": false,
  "editor.foldingImportsByDefault": true,
  "editor.fontFamily": "JetBrains Mono",
  "editor.fontLigatures": true,
  "editor.fontSize": 19,
  "editor.formatOnSave": true,
  "editor.formatOnType": true,
  "editor.hover.delay": 20,
  "editor.inlayHints.fontFamily": "JetBrains Mono",
  "editor.inlineSuggest.enabled": true,
  "editor.linkedEditing": true,
  "editor.minimap.enabled": false,
  "editor.quickSuggestions": true,
  "editor.quickSuggestionsDelay": 5,
  "editor.renderControlCharacters": true,
  "editor.renderLineHighlightOnlyWhenFocus": true,
  "editor.scrollbar.horizontalScrollbarSize": 10,
  "editor.scrollbar.vertical": "visible",
  "editor.scrollbar.verticalScrollbarSize": 10,
  "editor.scrollBeyondLastColumn": 0,
  "editor.showFoldingControls": "always",
  "editor.smoothScrolling": true,
  "editor.suggest.insertMode": "replace",
  "editor.suggest.snippetsPreventQuickSuggestions": false,
  "editor.suggestSelection": "first",
  "editor.tabSize": 4,
  // 错误后缀显示
  "errorLens.fontWeight": "bold",
  "errorLens.onSaveTimeout": 2000,
  "errorLens.statusBarColorsEnabled": true,
  // 资源管理器
  "explorer.confirmDelete": false,
  "explorer.confirmDragAndDrop": false,
  "explorer.incrementalNaming": "smart",
  // 插件扩展
  "extensions.closeExtensionDetailsOnViewChange": true,
  // 文件
  "files.associations": {
    "*.cjson": "jsonc",
    "*.wxs": "javascript",
    "*.wxss": "css"
  },
  "files.autoSave": "afterDelay",
  "files.autoSaveDelay": 500,
  "files.defaultLanguage": "markdown",
  "files.eol": "auto",
  "files.exclude": {
    "**.DS_Store": true,
    "**/__pycache__": true,
    "**/.classpath": true,
    "**/.factorypath": true,
    "**/.project": true,
    "**/.settings": true
  },
  "files.insertFinalNewline": true,
  "files.simpleDialog.enable": true,
  "files.trimFinalNewlines": true,
  "files.trimTrailingWhitespace": true,
  // git
  "git.confirmSync": false,
  "git.enableSmartCommit": true,
  "git.path": "/usr/bin/git",
  // Go
  "go.autocompleteUnimportedPackages": true,
  "go.docsTool": "guru",
  "go.formatTool": "default",
  "go.gocodePackageLookupMode": "go",
  "go.gotoSymbol.includeImports": true,
  "go.toolsManagement.autoUpdate": true,
  "go.useCodeSnippetsOnFunctionSuggest": true,
  "go.useCodeSnippetsOnFunctionSuggestWithoutType": true,
  "go.useLanguageServer": false,
  "hediet.vscode-drawio.local-storage": "eyIuZHJhd2lvLWNvbmZpZyI6IntcImxhbmd1YWdlXCI6XCJcIixcImN1c3RvbUZvbnRzXCI6W3tcIm5hbWVcIjpcIuaJi+acreS9ky3nroBcIn1dLFwibGlicmFyaWVzXCI6XCJnZW5lcmFsXCIsXCJjdXN0b21MaWJyYXJpZXNcIjpbXCJMLnNjcmF0Y2hwYWRcIl0sXCJwbHVnaW5zXCI6W10sXCJyZWNlbnRDb2xvcnNcIjpbXSxcImZvcm1hdFdpZHRoXCI6XCIyNDBcIixcImNyZWF0ZVRhcmdldFwiOmZhbHNlLFwicGFnZUZvcm1hdFwiOntcInhcIjowLFwieVwiOjAsXCJ3aWR0aFwiOjMzMDAsXCJoZWlnaHRcIjo0NjgxfSxcInNlYXJjaFwiOnRydWUsXCJzaG93U3RhcnRTY3JlZW5cIjp0cnVlLFwiZ3JpZENvbG9yXCI6XCIjZDBkMGQwXCIsXCJkYXJrR3JpZENvbG9yXCI6XCIjNmU2ZTZlXCIsXCJhdXRvc2F2ZVwiOnRydWUsXCJyZXNpemVJbWFnZXNcIjpudWxsLFwib3BlbkNvdW50ZXJcIjowLFwidmVyc2lvblwiOjE4LFwidW5pdFwiOjEsXCJpc1J1bGVyT25cIjpmYWxzZSxcInVpXCI6XCJcIn0ifQ==",
  // jupyter
  "jupyter.magicCommandsAsComments": true,
  // lua
  "Lua.color.mode": "SemanticEnhanced",
  "Lua.completion.callSnippet": "Both",
  "Lua.completion.displayContext": 3,
  "Lua.hint.enable": true,
  // markdown
  "markdown.extension.italic.indicator": "_",
  "markdown.preview.breaks": true,
  "markdown.preview.fontFamily": "JetBrains Mono",
  "markdown.preview.fontSize": 20,
  "notebook.cellToolbarVisibility": "hover",
  "prettier.printWidth": 120,
  // prettier
  "prettier.proseWrap": "always",
  // Python
  "python.analysis.completeFunctionParens": true,
  "python.analysis.typeCheckingMode": "off",
  "python.autoComplete.addBrackets": true,
  "python.defaultInterpreterPath": "/opt/homebrew/Caskroom/miniforge/base/envs/rs/bin/python",
  "python.formatting.blackArgs": ["--line-length=100"],
  "python.formatting.blackPath": "/opt/homebrew/Caskroom/miniforge/base/bin/black",
  "python.formatting.provider": "black",
  "python.formatting.yapfPath": "/opt/homebrew/Caskroom/miniforge/base/bin/yapf",
  "python.languageServer": "Default",
  "python.linting.enabled": true,
  "python.linting.flake8Args": [
    "--ignore=E402, E225, E501, E124, W504, E125, W503, E203, E306, E302, E401, E722, F401"
  ],
  "python.linting.flake8Enabled": true,
  "python.linting.flake8Path": "/opt/homebrew/Caskroom/miniforge/base/bin/flake8",
  "python.linting.mypyEnabled": false,
  "python.linting.pylintEnabled": false,
  "python.linting.pylintPath": "/opt/homebrew/Caskroom/miniforge/base/bin/pylint",
  "python.pythonPath": "/opt/homebrew/Caskroom/miniforge/base/envs/rs/bin/python",
  "python.terminal.activateEnvironment": false,
  "redhat.telemetry.enabled": true,
  "scm.alwaysShowActions": true,
  "scm.alwaysShowRepositories": true,
  "scm.defaultViewMode": "tree",
  // 搜索
  "search.actionsPosition": "auto",
  "search.collapseResults": "auto",
  "search.followSymlinks": false,
  "search.maxResults": 100,
  "search.quickOpen.includeSymbols": true,
  "search.smartCase": true,
  "security.workspace.trust.enabled": false,
  // 安全性
  "security.workspace.trust.untrustedFiles": "open",
  // 终端
  "terminal.external.osxExec": "/Applications/iTerm.app",
  "terminal.integrated.cursorStyle": "line",
  "terminal.integrated.cursorWidth": 2,
  "terminal.integrated.defaultProfile.osx": "zsh",
  "terminal.integrated.defaultProfile.windows": "C:\\Windows\\System32\\cmd.exe",
  "terminal.integrated.fontSize": 16,
  "terminal.integrated.gpuAcceleration": "auto",
  "terminal.integrated.inheritEnv": false,
  "terminal.integrated.tabs.hideCondition": "never",
  "terminal.integrated.tabs.showActions": "never",
  "terminal.integrated.tabs.showActiveTerminal": "always",
  // 窗口界面
  "window.nativeTabs": true,
  "window.titleBarStyle": "native",
  "workbench.colorTheme": "Monokai Pro (Filter Spectrum)",
  "workbench.commandPalette.history": 10,
  "workbench.editor.decorations.colors": true,
  "workbench.editorAssociations": {
    "*.ipynb": "jupyter-notebook",
    "*.woff": "default"
  },
  "workbench.fontAliasing": "auto",
  "workbench.hover.delay": 1000,
  "workbench.iconTheme": "Monokai Pro (Filter Spectrum) Icons",
  "workbench.list.smoothScrolling": true,
  "workbench.sash.size": 1,
  "workbench.settings.editor": "json",
  "workbench.startupEditor": "none",
  "workbench.tree.renderIndentGuides": "always",
  "workbench.view.alwaysShowHeaderActions": true
}
```

有需要的人可以直接拿走，但接下来我就来说明一下各种配置详情吧！

### 主题/图标设置

#### 主题

我使用的主题是 Monokai Pro 个人比较喜欢这种暗色的主题.

#### 图标

我使用的是“Material Icon Theme”，相比于“vscode-icons”，颜色更鲜明，不同种类的文件夹颜色不同。而且灰色的初始文件夹感觉还不错。

### 语言设置

#### C++

`"C_Cpp.clang_format_fallbackStyle": "Google"` 仅仅只需要一行，是不是很简单，而且这个还是指定的代码格式化风格。（我个人比较喜欢将左括号放在上面的）

#### Go

go 语言的设置也挺简单的，但在我这出现了一些问题，由于我的 gopls 总是安装不成功，老是显示 XXX 不再 GOROOT 内，所以使用的是 go 的工具链。

在安装完 vscode 的 Go 插件后，只需要在搜索栏敲下 `Go: Install/Update Tools` 命令，并将所有 go tools 勾选并下载就可以了！

剩下的就是关于格式化和自动导包的问题了，这些问题使用我配置中的“go 设置”就可以完成。

不过需要注意的是，刚配置完成，可能并不会起效果，可能需要重启 vscode 才会发挥作用。

#### python

说实话，python 的配置是我话费最长时间的（可能和我主要使用 python 有关吧，总有许多痛点看似解决了，但又没解决...）

首先，我使用 Pylance 作为语言服务，相比于“Microsoft”，我认为其提示得更全面，而且有些库在提示显示后按 tab 可以自动导包。

然后是 linting，我选用导是 flake8，因为其设置非常方便，有些规则我不想使用，可以在 args 中忽略。

最后是 format，这个我非常纠结，在 black 和 yapf 中抉择了很长一段时间，最后选择 yapf 了。具体原因嘛，我认为 yapf 自定义更方便，既然追求自定义，那就贯彻到底吧。

然后就是其他的一些设置。

- 使用“Python Docstring Generator”插件来生成注释字符串。
- 使用“Python Indent”插件来处理 python 换行的缩进问题。
- 使用“TabOut”插件，可以按 tab 跳转至括号后

### 界面进阶设置

由于我是用的是 2K 的外接屏幕，而对于 Mac mini m1 来说，这种屏幕完全没办法开启 hidqi，所以使用 vscode 时侧边栏的字体会显示的特别小，而且非常不好看。

为了解决这个问题，我使用“Customize UI”插件来设置 vscode 页面。

相关设置，可以查
看[插件介绍](https://marketplace.visualstudio.com/items?itemName=iocave.customize-ui)

## 总结

vscode 是真的不错，以后再也不用下载庞大的 ide 了，还可以支持所有的语言！而且配置环境只需要开启“设置同步”就可以完美创建一个属于你的自定义编辑器啦！(´▽ ｀)
