# 🚀 Qt Event Filter Demo

![Qt Version](https://img.shields.io/badge/Qt-5.15%2B-brightgreen)
![License](https://img.shields.io/badge/License-MIT-blue)

## 📌 项目简介
演示如何为 Qt UI 控件批量添加事件过滤器实现悬停交互效果

```cpp
// mainwindow.cpp
void MainWindow::setupEventFilters() 
{
    // 递归安装事件过滤器
    auto installToChildren = [this](QWidget* parent) {
        for (QObject* child : parent->children()) {
            if (auto* widget = qobject_cast<QWidget*>(child)) {
                widget->installEventFilter(this);
                installToChildren(widget);
            }
        }
    };
    
    installToChildren(this);
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (auto* widget = qobject_cast<QWidget*>(watched)) {
        switch (event->type()) {
            case QEvent::Enter:
                widget->setStyleSheet("background: #f5f5f5;");
                return true;
            case QEvent::Leave:
                widget->setStyleSheet("");
                return true;
            default: break;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
```

## 📑 项目文档

paper:

## 🛠️ 安装指南

### 依赖项
| 组件 | 最低版本 | 推荐版本 |
|------|---------|---------|
| Qt   | 5.15    | 6.2+    |
| CMake| 3.5     | 3.20+   |
| C++  | 17      | 20      |

### 构建步骤
```bash
# 克隆仓库（含子模块）
git clone --recursive https://github.com/yourname/qt-eventfilter-demo.git
cd qt-eventfilter-demo

# 生成构建系统
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/lib/cmake

# 编译项目
cmake --build build --config Release
```

## 🎮 使用方法

### 基础功能
1. **悬停高亮** - 鼠标经过控件时显示背景色
2. **点击反馈** - 鼠标按下时改变控件样式
3. **自定义样式** - 通过 CSS 修改效果

```qss
/* styles.qss */
QPushButton:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:0, y2:1,
        stop:0 #e0e0e0, stop:1 #f5f5f5
    );
    border: 1px solid #ccc;
}
```

### 键盘快捷键
| 快捷键 | 功能 |
|--------|------|
| Ctrl+H | 显示帮助 |
| F5     | 刷新样式 |

## 🤝 贡献指南

### 开发流程
1. 创建 issue 描述问题/功能
2. Fork 仓库并创建分支：
   ```bash
   git checkout -b fix/issue-123
   ```
3. 提交符合规范的代码：
   ```bash
   git commit -m "fix: resolve hover flickering (close #123)"
   ```
4. 创建 Pull Request

### 代码规范
```diff
// 良好的代码示例
+ void processData();  // 动词开头的函数名
+ int m_itemCount;    // m_前缀的成员变量

// 应避免的写法
- void data();        // 名词作为函数名
- int _count;         // 下划线前缀
```

## 📋 系统要求

### 最低配置
- **Windows**: 10 (x64)
- **macOS**: 10.14+
- **Linux**: Ubuntu 18.04+
- **内存**: 2GB RAM
- **磁盘**: 200MB 可用空间

### 推荐配置
- 支持 OpenGL 3.2+ 的 GPU
- 4GB+ 内存
- SSD 存储

## 📜 许可证
本项目采用 [MIT License](LICENSE)：

```text
Copyright (c) 2023 Your Name

Permission is hereby granted...
```

## 📬 联系方式
- 提交 Issue: [问题追踪](https://github.com/yourname/qt-eventfilter-demo/issues)
- 讨论区: [GitHub Discussions](https://github.com/yourname/qt-eventfilter-demo/discussions)
- 紧急联系: project@example.com

---

> 💡 提示：本模板包含 GitHub 专属功能（徽章、表情符号、表格等），在其他平台可能显示效果不同
