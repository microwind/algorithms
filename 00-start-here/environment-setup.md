# 编程开发环境搭建指南

> 工欲善其事，必先利其器。本指南帮你快速搭建编程开发环境，开始你的编程之旅。

## 🎯 本指南涵盖

- 主流编程语言的环境搭建
- 推荐的代码编辑器和 IDE
- 环境配置检验
- 常见问题排查

---

## 📋 快速选择

根据你选择的编程语言找到对应的搭建步骤：

| 语言 | 难度 | 推荐级别 | 配置时间 |
|------|------|---------|---------|
| [Python](#python) | ⭐ | ⭐⭐⭐⭐⭐ | 5-10 分钟 |
| [JavaScript/Node.js](#javascript--nodejs) | ⭐⭐ | ⭐⭐⭐⭐⭐ | 10-15 分钟 |
| [Java](#java) | ⭐⭐ | ⭐⭐⭐⭐ | 15-20 分钟 |
| [Go](#go) | ⭐⭐ | ⭐⭐⭐⭐ | 10-15 分钟 |
| [C/C++](#cc) | ⭐⭐⭐ | ⭐⭐⭐ | 20-30 分钟 |
| [TypeScript](#typescript) | ⭐⭐⭐ | ⭐⭐⭐ | 15-20 分钟 |

---

## 🔧 编辑器和 IDE 推荐

### 入门推荐
- **VS Code**（轻量级，功能强大）
  - 适合：Python、JavaScript、Go、C/C++
  - 下载：https://code.visualstudio.com
  - 优点：轻量、插件丰富、学习成本低

- **PyCharm Community**（Python 专用）
  - 适合：Python 开发
  - 下载：https://www.jetbrains.com/pycharm/download
  - 优点：功能完整、调试方便

### 进阶推荐
- **IntelliJ IDEA**（Java/Kotlin）
  - 功能完整，企业级开发工具

- **Xcode**（macOS/iOS）
  - Apple 开发必需

### 轻量级选择
- **Sublime Text** - 速度快，配置灵活
- **Vim/Neovim** - 极客首选，学习曲线陡
- **Notepad++** - Windows 用户的轻量选择

---

## 🐍 Python

### Windows 系统

**步骤 1：下载 Python**
1. 访问 https://www.python.org/downloads
2. 点击 Download Python 3.x.x（选择最新版本）

**步骤 2：安装**
1. 运行下载的 .exe 文件
2. ✅ 勾选 "Add Python 3.x to PATH"（重要！）
3. 选择 "Install Now" 或自定义安装路径
4. 等待安装完成

**步骤 3：验证安装**

打开命令提示符（cmd），输入：
```bash
python --version
pip --version
```

如果显示版本号，说明安装成功 ✅

### macOS 系统

**步骤 1：使用 Homebrew（推荐）**

```bash
# 如果未安装 Homebrew，先安装
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 安装 Python
brew install python@3.11
```

**步骤 2：验证安装**

```bash
python3 --version
pip3 --version
```

### Linux 系统

**Ubuntu/Debian：**
```bash
sudo apt-get update
sudo apt-get install python3 python3-pip
python3 --version
```

**CentOS/RHEL：**
```bash
sudo yum install python3 python3-pip
python3 --version
```

### 第一个 Python 程序

创建文件 `hello.py`：
```python
print("Hello, World!")
```

运行：
```bash
python hello.py
```

---

## 🌐 JavaScript & Node.js

### Windows 系统

**步骤 1：下载 Node.js**
1. 访问 https://nodejs.org
2. 下载 LTS 版本（长期支持版）

**步骤 2：安装**
1. 运行 .msi 安装程序
2. 一路点击"下一步"完成安装
3. 勾选 "Automatically install the necessary tools"

**步骤 3：验证安装**

```bash
node --version
npm --version
```

### macOS 系统

```bash
# 使用 Homebrew
brew install node

# 验证
node --version
npm --version
```

### Linux 系统

```bash
# Ubuntu/Debian
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt-get install nodejs

# 验证
node --version
npm --version
```

### 第一个 JavaScript 程序

创建文件 `hello.js`：
```javascript
console.log("Hello, World!");
```

运行：
```bash
node hello.js
```

### 使用 npm

```bash
# 初始化项目
npm init -y

# 安装依赖
npm install lodash

# 运行脚本
npm run start
```

---

## ☕ Java

### Windows 系统

**步骤 1：下载 JDK**
1. 访问 https://www.oracle.com/java/technologies/downloads/
2. 下载 Java SE Development Kit（JDK 最新版本）

**步骤 2：安装**
1. 运行 .exe 安装程序
2. 记住安装路径（默认 `C:\Program Files\Java\jdk-xx`）

**步骤 3：配置环境变量**

1. 右键点击"此电脑" → 属性
2. 点击"高级系统设置"
3. 点击"环境变量"
4. 新建系统变量：
   - 变量名：`JAVA_HOME`
   - 变量值：`C:\Program Files\Java\jdk-xx`（你的安装路径）
5. 编辑 `Path` 变量，添加：
   - `%JAVA_HOME%\bin`

**步骤 4：验证安装**

```bash
java -version
javac -version
```

### macOS 系统

```bash
# 使用 Homebrew
brew tap homebrew/cask-versions
brew install java

# 验证
java -version
javac -version
```

### Linux 系统

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install default-jdk

# 验证
java -version
```

### 第一个 Java 程序

创建文件 `HelloWorld.java`：
```java
public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}
```

编译和运行：
```bash
javac HelloWorld.java
java HelloWorld
```

---

## 🐹 Go

### Windows 系统

**步骤 1：下载 Go**
1. 访问 https://golang.org/dl
2. 下载 Windows .msi 安装程序

**步骤 2：安装**
1. 运行 .msi 文件
2. 默认安装到 `C:\Program Files\Go`

**步骤 3：验证安装**

```bash
go version
go env
```

### macOS 系统

```bash
# 使用 Homebrew
brew install go

# 验证
go version
```

### Linux 系统

```bash
# 下载最新版本
wget https://golang.org/dl/go1.20.linux-amd64.tar.gz

# 解压到 /usr/local
sudo tar -C /usr/local -xzf go1.20.linux-amd64.tar.gz

# 添加到 PATH（编辑 ~/.bashrc 或 ~/.zshrc）
export PATH=$PATH:/usr/local/go/bin

# 验证
go version
```

### 第一个 Go 程序

创建文件 `hello.go`：
```go
package main

import "fmt"

func main() {
    fmt.Println("Hello, World!")
}
```

运行：
```bash
go run hello.go
```

---

## 🔧 C/C++

### Windows 系统

**选项 1：使用 MinGW（推荐初学者）**

1. 下载 MinGW：https://www.mingw-w64.org
2. 安装到 `C:\mingw64`
3. 配置环境变量：
   - 新建 `MINGW_HOME = C:\mingw64`
   - 编辑 `Path`，添加 `%MINGW_HOME%\bin`
4. 验证：

```bash
gcc --version
g++ --version
```

**选项 2：使用 Visual Studio（功能完整）**

1. 下载 Visual Studio Community：https://visualstudio.microsoft.com
2. 安装时选择 "Desktop development with C++"

### macOS 系统

```bash
# 安装 Xcode Command Line Tools
xcode-select --install

# 验证
gcc --version
g++ --version
```

### Linux 系统

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential

# CentOS/RHEL
sudo yum install gcc g++ make

# 验证
gcc --version
```

### 第一个 C++ 程序

创建文件 `hello.cpp`：
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

编译和运行：
```bash
g++ -o hello hello.cpp
./hello
```

---

## 📝 TypeScript

### 安装 TypeScript

```bash
# 全局安装（推荐）
npm install -g typescript

# 验证
tsc --version
```

或在项目中安装：
```bash
npm install --save-dev typescript
```

### 第一个 TypeScript 程序

创建文件 `hello.ts`：
```typescript
function greet(name: string): void {
    console.log(`Hello, ${name}!`);
}

greet("World");
```

编译和运行：
```bash
tsc hello.ts
node hello.js
```

---

## ✅ 环境配置检查清单

在开始编程前，确认以下事项：

- [ ] 选择好编程语言
- [ ] 安装了编程环境（SDK/Runtime）
- [ ] 验证了版本和路径
- [ ] 安装了代码编辑器（VS Code 推荐）
- [ ] 写并运行了第一个程序
- [ ] 能够成功编译/执行程序
- [ ] 配置了代码编辑器的插件（可选）

---

## 🆘 常见问题

### "command not found" 错误

**原因**：环境变量未正确配置

**解决方案**：
1. 确认安装路径正确
2. 重新配置系统环境变量
3. 重启终端或系统
4. 验证 PATH 变量：
   ```bash
   # macOS/Linux
   echo $PATH

   # Windows
   echo %PATH%
   ```

### 安装后版本显示错误

**解决方案**：
1. 检查是否有多个版本安装
2. 卸载不需要的版本
3. 更新环境变量
4. 重启计算机

### VS Code 无法识别编程环境

**解决方案**：
1. 安装相应的 VS Code 扩展
   - Python Extension
   - Prettier - Code Formatter
   - C/C++ Extension Pack
2. 在 VS Code 设置中指定解释器路径
3. 重新加载 VS Code

### Mac 提示"无法打开"

**解决方案**：
```bash
# 允许执行
sudo spctl --master-disable
```

---

## 🚀 下一步

1. 完成环境配置并验证
2. 创建第一个程序并成功运行
3. 阅读 [学习路线](./learning-path.md) 继续学习
4. 选择一门语言深入学习
5. 进入 `01-data-structures` 开始实践

---

## 📚 相关资源

- [官方文档链接](../07-resources/README.md)
- [学习路线指南](./learning-path.md)
- [推荐学习语言](./recommand-learning-languages.md)

---

**如果遇到问题，检查官方文档或搜索错误信息。编程社区很友善，大多数问题都有解决方案！** 💪
