---
title: 我的vscode自定义化过程
date: 2021-8-5 10:33:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
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
- vscode 上 C/C++还挺好配置的，首先 Mac 上本身就有 gcc 编译器，只用下载一个 C/C++插件就完全够用了！ε-(´∀ ｀; )，非常适合我这种怕麻烦，还患有“pc 存储恐惧症”的患者。
- 有着一点点私心的极客想法，觉得开源超帅！自定义超帅！所以慢慢地从“以后 C/C++代码就在 vscode 上写吧”到“vscode 就是我家，idea 滚出我的电脑！”，逐渐极端化了呢 ╮(╯▽╰)╭

大致上就是以上的这些原因，总而言之，并不是 idea 不香，而是 vscode 更适合我！（这种无从得出的结论，为了不引战我还真的说得出口呀）。但现在回顾整个配置过程，觉得 vscode 的自定义化之旅并不容易，但一点都不无聊，反而让我感到快乐。所以在此分享我的配置过程(((o(_ﾟ ▽ ﾟ_)o)))

## 配置

不说废话了，先贴出我的 setting.json

```json
{
  // 工作区的图标主题
  "workbench.iconTheme": "material-icon-theme",
  "workbench.editorAssociations": {
    "*.ipynb": "jupyter-notebook"
  },
  // 主题
  "workbench.preferredDarkColorTheme": "rs-theme-dark",
  "workbench.preferredLightColorTheme": "rs-theme-dark",
  "workbench.colorTheme": "rs-theme-dark",
  // 字体设置
  "editor.fontSize": 17,
  "debug.console.fontSize": 16,
  "terminal.integrated.fontSize": 16,
  "editor.fontFamily": "'Menlo', '手札体-简'",
  "markdown.preview.fontFamily": "'Menlo', '手札体-简'",
  // 光标设置
  "editor.cursorBlinking": "solid",
  "editor.cursorSmoothCaretAnimation": true,
  // 高亮
  "editor.renderLineHighlight": "all",
  "editor.renderLineHighlightOnlyWhenFocus": true,
  // tab设置
  "editor.tabSize": 4,
  "editor.detectIndentation": false,
  // 代码建议
  "editor.inlineSuggest.enabled": true,
  "editor.quickSuggestions": true,
  "editor.acceptSuggestionOnEnter": "on",
  "editor.quickSuggestionsDelay": 5,
  "editor.suggest.insertMode": "replace",
  "editor.suggestSelection": "first",
  "editor.suggest.snippetsPreventQuickSuggestions": false,
  // 自动折叠Import语句
  "editor.foldingImportsByDefault": false,
  // 终端设置
  // mac系统下的默认终端
  "terminal.integrated.defaultProfile.osx": "zsh",
  // win系统下的默认终端
  "terminal.integrated.defaultProfile.windows": "C:\\Windows\\System32\\cmd.exe",
  // 窗口失去焦点后自动保存
  "files.autoSave": "afterDelay",
  "editor.linkedEditing": true,
  "workbench.editor.decorations.colors": true,
  "window.autoDetectColorScheme": true,
  "files.associations": {
    "*.cjson": "jsonc",
    "*.wxss": "css",
    "*.wxs": "javascript"
  },
  "emmet.includeLanguages": {
    "wxml": "html"
  },
  // code runner 设置
  // code runner 执行映射
  "code-runner.executorMap": {
    "javascript": "node",
    "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
    "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "objective-c": "cd $dir && gcc -framework Cocoa $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "php": "php",
    "python": "export PYTHONPATH=$PYTHONPATH:$workspaceRoot && python -u $fullFileName",
    "ruby": "ruby",
    "go": "cd $dir && go run $fileName",
    "lua": "lua",
    "groovy": "groovy",
    "powershell": "powershell -ExecutionPolicy ByPass -File",
    "bat": "cmd /c",
    "shellscript": "bash",
    "fsharp": "fsi",
    "csharp": "scriptcs",
    "typescript": "ts-node",
    "scala": "scala",
    "swift": "swift",
    "julia": "julia",
    "r": "Rscript",
    "applescript": "osascript",
    "rust": "cd $dir && rustc $fileName && $dir$fileNameWithoutExt",
    "dart": "dart",
    "haskell": "runhaskell",
    "nim": "nim compile --verbosity:0 --hints:off --run",
    "lisp": "sbcl --script",
    "sass": "sass --style expanded",
    "scss": "scss --style expanded",
    "less": "cd $dir && lessc $fileName $fileNameWithoutExt.css"
  },
  "code-runner.runInTerminal": true,
  "code-runner.saveFileBeforeRun": true,
  "code-runner.ignoreSelection": true,
  "terminal.integrated.inheritEnv": false,
  // 关闭小地图
  "editor.minimap.enabled": false,
  // vue设置
  "[vue]": {
    "editor.defaultFormatter": "vscode.npm",
    "editor.tabSize": 2,
    "editor.detectIndentation": false
  },
  // javascript 设置
  "[javascript]": {
    "editor.defaultFormatter": "vscode.typescript-language-features",
    "editor.tabSize": 2,
    "editor.detectIndentation": false
  },
  // json 设置
  "[jsonc]": {
    "editor.defaultFormatter": "vscode.json-language-features"
  },
  // c++设置
  "C_Cpp.clang_format_fallbackStyle": "Google",
  // go 设置
  "go.useLanguageServer": false,
  "go.autocompleteUnimportedPackages": true,
  "go.gocodePackageLookupMode": "go",
  "go.gotoSymbol.includeImports": true,
  "go.useCodeSnippetsOnFunctionSuggest": true,
  "go.useCodeSnippetsOnFunctionSuggestWithoutType": true,
  "go.docsTool": "guru",
  "go.formatTool": "goimports",
  "go.toolsManagement.autoUpdate": true,
  "[go]": {
    "editor.insertSpaces": false,
    "editor.formatOnSave": true,
    "editor.codeActionsOnSave": {
      "source.organizeImports": true
    }
  },
  // python 设置
  // python 终端设置
  "python.terminal.activateEnvironment": false,
  // 类型检查
  "python.analysis.typeCheckingMode": "basic",
  // 语言服务
  "python.languageServer": "Pylance",
  // python format
  "python.formatting.provider": "yapf",
  "python.formatting.yapfArgs": [
    "--style={based_on_style: google}" // 使用 google 代码风格
  ],
  // python linting
  "python.linting.pylintEnabled": false,
  "python.linting.enabled": true,
  "python.linting.flake8Enabled": true,
  "python.linting.lintOnSave": true,
  "python.linting.flake8Args": ["--ignore=E402, E225, E501, E124, W504, E125"],
  // python 代码提示自动添加括号
  "python.autoComplete.addBrackets": true,
  "python.analysis.completeFunctionParens": true,
  "[python]": {
    "editor.codeActionsOnSave": {
      "source.fixAll": true,
      "source.organizeImports": true
    }
  },
  // markdown 格式化
  "[markdown]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  // advance vscode setting
  "customizeUI.titleBar": "inline",
  "customizeUI.fontSizeMap": {
    "13px": "15px",
    "monospace": "15px"
  },
  "customizeUI.listRowHeight": 25,
  "customizeUI.font.monospace": "Menlo",
  "customizeUI.font.regular": "Menlo",
  "customizeUI.activityBarHideSettings": true,
  "customizeUI.activityBar": "top",
  // Better Comments
  "better-comments.tags": [
    {
      "tag": "todo",
      "color": "#FF8C00",
      "strikethrough": false,
      "underline": false,
      "backgroundColor": "transparent",
      "bold": true,
      "italic": false
    },
    {
      "tag": "@",
      "color": "#3498DB",
      "strikethrough": false,
      "underline": false,
      "backgroundColor": "transparent",
      "bold": false,
      "italic": false
    }
  ],
  // 彩色括号
  "bracketPairColorizer.forceIterationColorCycle": true,
  "bracketPairColorizer.consecutivePairColors": [
    "()",
    "[]",
    "{}",
    [
      "Tomato",
      // "LightSkyBlue",
      "Cyan",
      "Darkorange"
    ],
    "Red"
  ],
  // 其他
  "files.eol": "auto",
  "files.exclude": {
    "**/__pycache__": true,
    "**/.classpath": true,
    "**/.factorypath": true,
    "**/.project": true,
    "**/.settings": true
  },
  "workbench.startupEditor": "none",
  "terminal.integrated.gpuAcceleration": "auto",
  "security.workspace.trust.untrustedFiles": "open",
  "git.confirmSync": false,
  "window.titleBarStyle": "native",
  "git.enableSmartCommit": true,
  "markdown.preview.fontSize": 20,
  "notebook.cellToolbarLocation": {
    "default": "right",
    "jupyter-notebook": "left"
  },
  "explorer.confirmDragAndDrop": false,
  "workbench.editor.limit.enabled": true,
  "workbench.list.smoothScrolling": true,
  "explorer.confirmDelete": false,
  "[html]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  },
  "jupyter.magicCommandsAsComments": true,
  "[json]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "editor.tabSize": 2,
    "editor.detectIndentation": false
  },
  "workbench.sideBar.location": "right",
  "autoDocstring.startOnNewLine": true,
  "breadcrumbs.enabled": false
}
```

有需要的人可以直接拿走，但接下来我就来说明一下各种配置详情吧！

### 主题/图标设置

#### 主题

我使用的是自己设计的主题 rs-theme-dark。

我比较喜欢暗色的主题，而这个主题的颜色丰富，并且粗体让我看的比较舒服。但最重要的是，光标是橙色的！好评！

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

相关设置，可以查看[插件介绍](https://marketplace.visualstudio.com/items?itemName=iocave.customize-ui)

## 总结

vscode 是真的不错，以后再也不用下载庞大的 ide 了，还可以支持所有的语言！而且配置环境只需要开启“设置同步”就可以完美创建一个属于你的自定义编辑器啦！(´▽ ｀)
