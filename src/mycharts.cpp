#include"mycharts.h"

void mycharts::setupUI() {
    // 主布局
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // 1. 文档监控区
    QGroupBox *docGroup = createGroupBox("📚 文档监控", 300, 200);
    QGridLayout *docLayout = new QGridLayout(docGroup);

    docLayout->addWidget(createStatCard("文档总数", "142", "份"), 0, 0);
    docLayout->addWidget(createStatCard("待更新文档", "12", "份"), 0, 1);
    docLayout->addWidget(createStatCard("健康度", "82", "%"), 0, 2);

    QProgressBar *healthBar = new QProgressBar;
    healthBar->setRange(0, 100);
    healthBar->setValue(82);
    healthBar->setFormat("");
    healthBar->setObjectName("healthBar");
    docLayout->addWidget(healthBar, 1, 0, 1, 3);

    QLabel *warningLabel = new QLabel("⚠️ utils/date.h 缺少文档说明");
    warningLabel->setObjectName("warningLabel");
    docLayout->addWidget(warningLabel, 2, 0, 1, 3);

    mainLayout->addWidget(docGroup, 0, 0);

    // 2. 项目数据区
    QGroupBox *projectGroup = createGroupBox("📊 项目数据", 300, 200);
    QGridLayout *projectLayout = new QGridLayout(projectGroup);

    projectLayout->addWidget(createStatCard("贡献者", "24", "人"), 0, 0);
    projectLayout->addWidget(createStatCard("今日提交", "8", "次"), 0, 1);
    projectLayout->addWidget(createStatCard("问题数", "5", "个"), 0, 2);

    // 贡献者表格
    QTableWidget *contributorsTable = new QTableWidget(5, 3);
    contributorsTable->setHorizontalHeaderLabels({"姓名", "贡献", "活跃度"});
    contributorsTable->verticalHeader()->setVisible(false);
    contributorsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    contributorsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    contributorsTable->setObjectName("contributorsTable");
    projectLayout->addWidget(contributorsTable, 1, 0, 1, 3);

    mainLayout->addWidget(projectGroup, 0, 1);

    // 3. 系统状态区
    QGroupBox *systemGroup = createGroupBox("⚙️ 系统状态", 300, 200);
    QGridLayout *systemLayout = new QGridLayout(systemGroup);

    systemLayout->addWidget(createStatCard("AI调用", "142", "次"), 0, 0);
    systemLayout->addWidget(createStatCard("响应时间", "0.8", "秒"), 0, 1);
    systemLayout->addWidget(createStatCard("同步状态", "正常", ""), 0, 2);

    QLabel *syncLabel = new QLabel("最后同步: 2023-11-15 14:30");
    syncLabel->setAlignment(Qt::AlignCenter);
    systemLayout->addWidget(syncLabel, 1, 0, 1, 3);

    QProgressBar *syncBar = new QProgressBar;
    syncBar->setRange(0, 100);
    syncBar->setValue(100);
    syncBar->setFormat("");
    syncBar->setObjectName("syncBar");
    systemLayout->addWidget(syncBar, 2, 0, 1, 3);

    mainLayout->addWidget(systemGroup, 0, 2);

    // 4. 趋势图区域（占满宽度）
    // 4. 趋势图区域（替换之前的占位图）
    QGroupBox *chartGroup = createGroupBox("📈 活动趋势", 800, 250);
    QVBoxLayout *chartLayout = new QVBoxLayout(chartGroup);

    // 创建图表视图
    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    // 创建图表
    QChart *chart = new QChart;
    chart->setTitle("文档活动趋势 (最近7天)");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 创建数据系列
    QLineSeries *docCreatedSeries = new QLineSeries;
    docCreatedSeries->setName("创建文档");
    docCreatedSeries->setColor(QColor("#3498db")); // 蓝色

    QLineSeries *docUpdatedSeries = new QLineSeries;
    docUpdatedSeries->setName("更新文档");
    docUpdatedSeries->setColor(QColor("#2ecc71")); // 绿色

    QLineSeries *aiRequestsSeries = new QLineSeries;
    aiRequestsSeries->setName("AI请求");
    aiRequestsSeries->setColor(QColor("#9b59b6")); // 紫色

    // 模拟数据 (实际应用中应从数据源获取)
    QDateTime now = QDateTime::currentDateTime();
    for (int i = 6; i >= 0; --i) {
        QDateTime date = now.addDays(-i);
        qint64 msecs = date.toMSecsSinceEpoch();

        // 生成随机数据 (实际应用中替换为真实数据)
        int created = QRandomGenerator::global()->bounded(5, 15);
        int updated = QRandomGenerator::global()->bounded(3, 12);
        int aiReq = QRandomGenerator::global()->bounded(20, 50);

        docCreatedSeries->append(msecs, created);
        docUpdatedSeries->append(msecs, updated);
        aiRequestsSeries->append(msecs, aiReq);
    }

    // 添加系列到图表
    chart->addSeries(docCreatedSeries);
    chart->addSeries(docUpdatedSeries);
    chart->addSeries(aiRequestsSeries);

    // 创建X轴 (时间轴)
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("MM-dd");
    axisX->setTitleText("日期");
    axisX->setRange(now.addDays(-6), now);
    chart->addAxis(axisX, Qt::AlignBottom);
    docCreatedSeries->attachAxis(axisX);
    docUpdatedSeries->attachAxis(axisX);
    aiRequestsSeries->attachAxis(axisX);

    // 创建Y轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setTitleText("数量");
    axisY->setRange(0, 60);
    chart->addAxis(axisY, Qt::AlignLeft);
    docCreatedSeries->attachAxis(axisY);
    docUpdatedSeries->attachAxis(axisY);
    aiRequestsSeries->attachAxis(axisY);

    // 添加图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 设置图表视图
    chartView->setChart(chart);
    chartLayout->addWidget(chartView);

    // 添加到主布局 (跨三列)
    mainLayout->addWidget(chartGroup, 1, 0, 1, 3);

    // 图表占位图
    QLabel *chartPlaceholder = new QLabel;
    chartPlaceholder->setPixmap(QPixmap(":/charts/placeholder").scaled(750, 150, Qt::KeepAspectRatio));
    chartPlaceholder->setAlignment(Qt::AlignCenter);
    chartLayout->addWidget(chartPlaceholder);

    mainLayout->addWidget(chartGroup, 1, 0, 1, 3);

    // 5. 操作按钮区
    QWidget *actionWidget = new QWidget;
    QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(0, 0, 0, 0);

    // QPushButton *refreshBtn = new QPushButton("刷新数据");
    // refreshBtn->setObjectName("refreshBtn");
    // QPushButton *exportBtn = new QPushButton("导出报告");
    // exportBtn->setObjectName("exportBtn");
    // QPushButton *settingsBtn = new QPushButton("设置");
    // settingsBtn->setObjectName("settingsBtn");

    //actionLayout->addWidget(refreshBtn);
    //actionLayout->addWidget(exportBtn);
    actionLayout->addStretch();
    //actionLayout->addWidget(settingsBtn);

    mainLayout->addWidget(actionWidget, 2, 0, 1, 3);

    // 设置定时刷新UI效果
    QTimer *uiTimer = new QTimer(this);
    connect(uiTimer, &QTimer::timeout, this, &mycharts::animateUI);
    uiTimer->start(2000); // 每2秒更新一次UI效果
}

void mycharts::setupStyles() {
    // 基础样式
    setStyleSheet(R"(
            QWidget {
                font-family: 'Segoe UI', Arial, sans-serif;
                font-size: 12px;
            }

            QGroupBox {
                border: 1px solid #e0e0e0;
                border-radius: 8px;
                margin-top: 10px;
                background: white;
            }

            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px;
                color: #2c3e50;
                font-weight: bold;
                font-size: 14px;
            }

            #healthBar, #syncBar {
                height: 10px;
                border-radius: 5px;
                background: #ecf0f1;
            }

            #healthBar::chunk {
                background: #2ecc71;
                border-radius: 5px;
            }

            #syncBar::chunk {
                background: #3498db;
                border-radius: 5px;
            }

            #warningLabel {
                color: #e74c3c;
                font-weight: bold;
            }

            #contributorsTable {
                border: none;
                background: #f8f9fa;
                gridline-color: #e0e0e0;
            }

            QHeaderView::section {
                background: #3498db;
                color: white;
                padding: 4px;
            }

            QPushButton {
                padding: 6px 12px;
                border-radius: 4px;
                border: 1px solid #3498db;
                background: white;
                color: #3498db;
            }

            QPushButton:hover {
                background: #3498db;
                color: white;
            }

            #refreshBtn { border-color: #2ecc71; color: #2ecc71; }
            #refreshBtn:hover { background: #2ecc71; }

            #exportBtn { border-color: #9b59b6; color: #9b59b6; }
            #exportBtn:hover { background: #9b59b6; }

            #settingsBtn { border-color: #95a5a6; color: #7f8c8d; }
            #settingsBtn:hover { background: #95a5a6; }
        )");
}

void mycharts::setupMockData() {
    // 模拟贡献者数据
    QStringList contributors = {
        "luobiwen, 42次, ★★★★",
        "bomberman, 38次, ★★★★",
        "mapmap, 28次, ★★★☆",
        "ContractTest, 18次, ★★☆☆",
        "Androidclient, 12次, ★★☆☆"
    };

    QTableWidget *table = findChild<QTableWidget*>("contributorsTable");
    if (table) {
        table->setRowCount(contributors.size());
        for (int i = 0; i < contributors.size(); ++i) {
            QStringList parts = contributors[i].split(',');
            table->setItem(i, 0, new QTableWidgetItem(parts[0]));
            table->setItem(i, 1, new QTableWidgetItem(parts[1]));
            table->setItem(i, 2, new QTableWidgetItem(parts[2]));
        }
    }
}

void mycharts::animateUI() {
    // 简单的UI动画效果
    static bool alt = false;

    // 切换警告状态
    QLabel *warning = findChild<QLabel*>("warningLabel");
    if (warning) {
        warning->setText(alt ?
                             "⚠️ network.cpp 需要更新示例" :
                             "⚠️ utils/date.h 缺少文档说明");
    }

    // 更新统计数据
    QLabel *aiCalls = findChild<QLabel*>("aiCallsValue");
    if (aiCalls) {
        static int calls = 142;
        calls += QRandomGenerator::global()->bounded(1, 5);
        aiCalls->setText(QString::number(calls));
    }

    alt = !alt;
}

QGroupBox* mycharts::createGroupBox(const QString &title, int minWidth, int minHeight ) {
    QGroupBox *group = new QGroupBox(title);
    if (minWidth > 0) group->setMinimumWidth(minWidth);
    if (minHeight > 0) group->setMinimumHeight(minHeight);
    return group;
}

QWidget* mycharts::createStatCard(const QString &title, const QString &value, const QString &unit) {
    QWidget *card = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(5);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #7f8c8d; font-size: 11px;");

    QLabel *valueLabel = new QLabel(value);
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet("font-weight: bold; font-size: 20px; color: #2c3e50;");

    QLabel *unitLabel = new QLabel(unit);
    unitLabel->setAlignment(Qt::AlignCenter);
    unitLabel->setStyleSheet("color: #7f8c8d; font-size: 11px;");

    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    layout->addWidget(unitLabel);

    return card;
}
