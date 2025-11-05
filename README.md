# MiniDJ 音乐播放列表管理系统 - 课程作业

## 📋 作业概述

本项目是一个 C++ 音乐播放列表管理系统（MiniDJ），要求您完成 `Song` 类的实现，并配置相应的 CMake 构建文件。

### ⚠️ 重要提示：文件修改限制

**您只能修改以下两个文件：**

- `Song.cpp` - 实现 Song 类的所有功能
- `CMakeLists.txt` - 配置项目构建，默认提供的版本会缺少步骤，请自己找出并补全

**严禁修改以下文件：**

- `main.cpp` - 主程序（已提供）
- `Song.h` - 头文件（已提供）
- 任何测试文件和脚本
- 任何其他项目文件

❌ **如果修改了其他文件，您提交的作业将直接判定为不合格（0 分）。**

---

## 🎯 功能要求

实现一个音乐播放列表管理系统，需要支持以下功能：

### 核心功能

1. **添加歌曲** - 支持添加歌曲到播放列表
2. **显示列表** - 显示当前播放列表中的所有歌曲
3. **查找歌曲** - 按歌曲名称查找
4. **修改歌曲** - 修改歌曲的艺术家信息
5. **标签管理** - 为歌曲添加标签
6. **排序功能** - 按名称或艺术家排序
7. **删除歌曲** - 从播放列表中删除歌曲
8. **数据验证** - 确保数据的有效性

### 详细功能说明

请参考 `Song.h` 中的接口定义，在 cpp 文件中实现类本身，以及所有声明的成员函数。

---

## 📊 评分标准（总分 100 分）

您的作业将通过自动化系统进行评分，评分规则如下：

### 1. Git 提交信息检查（-10 分 / 条）

- ✅ **要求**：提交信息必须符合 [组织规范](https://github.com/unnc-aim/#14-git-message-regulation)
- 📝 **格式**：`<type>(<scope>): <subject>` 或 `<type>: <subject>`
  - **type**（必需）：feat, fix, docs, style, refactor, test, chore, perf, ci, build
  - **scope**（可选）：影响范围，如 user-auth, api, ui
  - **subject**（必需）：简短描述，**首字母小写**，**不超过 50 字符**，**无标点结尾**
- 🌍 **语言**：必须使用**英文**
- 📏 **长度**：**10-50 个字符**
- ❌ **检查范围**：**所有历史提交**（包括之前的提交）
- 💰 **扣分**：每条不符合要求的提交扣 **10 分**
- 🔧 **修复**：如有提交失误，请使用 `git rebase -i` 修改提交历史

**示例**：

- ✅ 正确：`feat(song): add search functionality`
- ✅ 正确：`fix: resolve sorting bug in playlist`
- ❌ 错误：`update` （太短）
- ❌ 错误：`Add new feature.` （首字母大写 + 标点结尾）
- ❌ 错误：`添加新功能` （使用中文）

### 2. 文件修改检查（直接不合格）

- ✅ **要求**：只能修改 `Song.cpp` 和 `CMakeLists.txt`
- ❌ **不合格**：修改了其他任何文件
- 💰 **扣分**：作业判定为 **0 分（不合格）**

### 3. 代码格式检查（-10 至 -20 分）

- ✅ **要求**：必须遵循 [C++ 嵌入式工程代码规范](https://github.com/unnc-aim/.github-private/blob/master/profile/standard.cpp.md)
- 🔍 **检查项目**：
  - 函数名：必须使用 `lowercase_with_underscores` 格式（包括类成员函数）
  - 变量名：必须使用 `camelCase` 格式（首字母小写）
  - 类名：必须使用 `PascalCase` 格式（首字母大写）
  - 宏定义：必须使用 `UPPERCASE_WITH_UNDERSCORES` 格式
  - 全局变量：必须使用 `static` 修饰
- 💰 **扣分规则**：
  - 第一个违规：扣 **10 分**
  - 每个额外违规：扣 **2 分**
  - 最多扣除：**20 分**

### 4. 构建检查（不通过则终止）

- ✅ **要求**：项目必须能够成功编译
- ❌ **不合格**：编译失败
- 💰 **扣分**：无法继续后续测试，直接 0 分

### 5. 功能测试（每个测试 -10 分）

- ✅ **要求**：通过所有 8 个测试用例
- 🧪 **测试用例**：
  1. Test 1: 基础添加和列表显示
  2. Test 2: 数据验证（空名称、非法时长）
  3. Test 3: 查找功能
  4. Test 4: 修改功能
  5. Test 5: 标签管理
  6. Test 6: 排序功能
  7. Test 7: 删除功能
  8. Test 8: 综合场景测试
- 💰 **扣分**：每个失败的测试扣 **10 分**

### 6. 人工审核扣分（每个问题-5 分）

- ⚠️ **警告**：助教会人工审核您的提问记录
- ❌ **明显问题**包括但不限于：
  - 询问如何修改 `main.cpp` 或 `Song.h`（已明确说明不能修改）
  - 询问代码格式规范的链接（已在 README 中提供）
  - 询问评分标准（已在 README 中详细说明）
  - 询问如何运行测试（已在下方说明）
  - 其他在 README 中已明确说明的内容
- 💰 **扣分**：每个明显问题扣 **5 分**，无上限

### 最终评分计算

```bash
最终得分 = 100 - Git扣分 - 格式扣分 - 测试失败扣分 - 人工审核扣分
```

**_及格线：60 分_**

---

## 🏗️ 本地开发指南

### 环境要求

- CMake 3.10 或更高版本
- C++14 兼容的编译器（g++, clang++等）
- Python 3.x（用于格式检查）

### 构建项目

```bash
# 创建构建目录
mkdir -p build
cd build

# 配置项目
cmake ..

# 编译
cmake --build .
```

### 运行程序

```bash
# 在 build 目录中
./cpp_exam
```

### 本地测试 - 使用 CTest

```bash
# 在 build 目录中
ctest --output-on-failure
```

或查看详细输出：

```bash
ctest -V
```

### 代码格式检查

在提交前，强烈建议运行格式检查：

```bash
# 在项目根目录
python3 check_format.py Song.cpp
```

这将检查您的代码是否符合格式规范，并显示所有违规项。

---

## 🔄 GitHub Actions 自动评分

每次 push 到 GitHub 后，系统会自动运行评分流程：

### 评分流程

1. ✅ **Git 提交检查** - 验证提交信息长度
2. ✅ **文件修改检查** - 确保只修改了允许的文件
3. ✅ **代码格式检查** - 运行 `check_format.py`
4. ✅ **构建检查** - 使用 CMake 编译项目
5. ✅ **功能测试** - 运行 CTest 执行所有测试
6. 📊 **生成评分报告** - 显示详细的扣分明细

### 查看评分结果

1. 访问您的 GitHub 仓库
2. 点击 "Actions" 标签
3. 选择最新的 workflow run
4. 查看 Summary 的输出

## 🚀 提交建议

### 开发流程建议

1. **先阅读** - 仔细阅读本 README 和代码规范
2. **再实现** - 在 `Song.cpp` 中实现功能
3. **本地测试** - 使用 `./test.sh` 测试所有功能
4. **格式检查** - 使用 `python3 check_format.py Song.cpp` 检查格式
5. **提交代码** - 使用符合规范的 commit message（见下方）
6. **查看结果** - 在 GitHub Actions 中查看自动评分

### Git Commit Message 规范详解

**基础格式**：

```text
<type>(<scope>): <subject>

<body>

<footer>
```

**必需部分**：

- `<type>`: 提交类型（见下方类型列表）
- `<subject>`: 简短描述（10-50 字符，首字母小写，无标点结尾）

**可选部分**：

- `<scope>`: 影响范围（如：song, playlist, ui）
- `<body>`: 详细描述（可换行，每行不超过 72 字符）
- `<footer>`: 备注信息（如：BREAKING CHANGE, Closes #123），这个你大概率不需要

**Type 类型**：

| Type       | 说明         | 示例                                   |
| ---------- | ------------ | -------------------------------------- |
| `feat`     | 新增功能     | `feat(song): add search functionality` |
| `fix`      | 修复 Bug     | `fix: resolve sorting bug in playlist` |
| `docs`     | 文档变更     | `docs: update README instructions`     |
| `style`    | 代码格式调整 | `style: fix indentation in Song.cpp`   |
| `refactor` | 代码重构     | `refactor: simplify addSong logic`     |
| `chore`    | 杂项         | `chore: update CMakeLists.txt`         |
| `perf`     | 性能优化     | `perf: optimize sorting algorithm`     |

**Subject 规则**：

- ✅ 使用祈使句（如 "add" 而不是 "added"）
- ✅ 首字母**必须小写**
- ✅ **不要**以标点符号结尾
- ✅ **必须**使用英文
- ✅ 长度 10-50 字符

**良好示例**：

```bash
# 基本格式（无 scope）
git commit -m "feat: add song deletion feature"

# 完整格式（带 scope）
git commit -m "fix(search): correct case-sensitive matching"

# 多行提交（带详细说明）
git commit -m "refactor(song): improve data validation

Simplified the validation logic for song duration.
Added comprehensive error messages for invalid inputs."
```

**错误示例**：

```bash
❌ git commit -m "update"              # 太短
❌ git commit -m "Fix bug."            # 首字母大写 + 标点结尾
❌ git commit -m "添加搜索功能"         # 使用中文
❌ git commit -m "Added search feature" # 使用过去式，首字母大写
```

### 修改提交历史

如果已经提交了不符合规范的 commit，可以使用以下方法修改：

**修改最后一次提交**：

```bash
git commit --amend -m "feat: add search functionality"
```

**修改多个历史提交**：

```bash
# 交互式 rebase（修改最近 3 个提交）
git rebase -i HEAD~3

# 在编辑器中，将要修改的提交前的 'pick' 改为 'reword'
# 保存后，会依次打开编辑器让你修改每个提交信息
```

**强制推送**（修改历史后需要）：

```bash
git push --force
```

⚠️ **注意**：强制推送会覆盖远程历史，请确保没有其他人基于你的分支工作。

---

## 📚 参考资源

- **代码规范**: [C++ 嵌入式工程代码规范](https://github.com/unnc-aim/.github-private/blob/master/profile/standard.cpp.md)
- **Git Message 规范**: [组织 Git 规范](https://github.com/unnc-aim/#14-git-message-regulation)
- **CMake 文档**: [CMake Official Docs](https://cmake.org/documentation/)
- **CTest 文档**: [CTest Documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html)

---

## ❓ 常见问题

### Q: 代码格式规范在哪里？

**A**: 已在本 README 中提供链接：<https://github.com/unnc-aim/.github-private/blob/master/profile/standard.cpp.md>

### Q: 如何知道我的分数？

**A**: 每次 push 后，GitHub Actions 会自动运行评分，在 Actions 标签中查看结果。

### Q: 及格分数是多少？

**A**: 60 分及格。

### Q: 格式检查具体检查什么？

**A**: 请参考上面的"代码格式检查"部分，或直接查看代码规范链接。

### Q: 我可以问队员问题吗？

**A**: 参见 [技术支持部分](#-技术支持)

---

## 📞 技术支持

如果遇到**非明显问题**（不在本 README 说明范围内），可以：

1. 检查群消息是否有人问过
2. 上网搜索 / 问 AI
3. 参考提供的代码规范文档

**请注意**：询问上面方案能轻易解决的问题会导致扣分。

这次作业难度较大，祝顺利完成 ;)
