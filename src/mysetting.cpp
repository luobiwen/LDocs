#include"mysetting.h"

GitHubSettingsUI::GitHubSettingsUI(QWidget *parent )
    : QMainWindow(parent) {
    // 设置窗口属性
    setWindowTitle("GitHub 项目设置");
    resize(900, 700);
    setMinimumSize(800, 600);

    // 应用样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // 创建主部件
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // 标题区域
    QHBoxLayout *headerLayout = new QHBoxLayout;

    // 标题文本
    QLabel *titleLabel = new QLabel("GitHub 项目设置");
    titleLabel->setFont(QFont("Arial", 18, QFont::Bold));
    titleLabel->setStyleSheet("color: #24292e;");

    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // 项目选择区域
    QHBoxLayout *projectLayout = new QHBoxLayout;
    projectLayout->setContentsMargins(10, 0, 10, 0);

    QLabel *projectLabel = new QLabel("当前项目:");
    projectLabel->setFont(QFont("Arial", 10));

    QComboBox *projectCombo = new QComboBox;
    projectCombo->setMinimumWidth(300);
    projectCombo->setFont(QFont("Arial", 10));
    projectCombo->addItems({
        "LDocs - 开源文档助手",
        "PyQt-UI-Library",
        "AI-Integration-Toolkit"
    });
    projectCombo->setCurrentIndex(0);

    projectLayout->addWidget(projectLabel);
    projectLayout->addWidget(projectCombo);
    projectLayout->addStretch();

    mainLayout->addLayout(projectLayout);

    // 创建标签页
    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->setFont(QFont("Arial", 10));

    // 添加标签页
    tabWidget->addTab(createGeneralTab(), "常规设置");
    tabWidget->addTab(createRepoSettingsTab(), "仓库设置");
    tabWidget->addTab(createAccessControlTab(), "访问控制");
    tabWidget->addTab(createIntegrationTab(), "集成");
    tabWidget->addTab(createAdvancedTab(), "高级");

    mainLayout->addWidget(tabWidget, 1); // 设置伸缩因子为1

    // 按钮区域
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();

    QPushButton *saveButton = new QPushButton("保存更改");
    saveButton->setFixedSize(120, 40);
    saveButton->setFont(QFont("Arial", 10, QFont::Bold));
    saveButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #2ea44f;"
        "   color: white;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #22863a;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1a6b30;"
        "}"
        );

    QPushButton *cancelButton = new QPushButton("取消");
    cancelButton->setFixedSize(120, 40);
    cancelButton->setFont(QFont("Arial", 10));
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #fafbfc;"
        "   color: #24292e;"
        "   border: 1px solid #d1d5da;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f3f4f6;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #eaecef;"
        "}"
        );

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // 设置整体样式
    centralWidget->setStyleSheet(
        "QTabWidget::pane {"
        "   border: 1px solid #e1e4e8;"
        "   border-top: none;"
        "   border-radius: 0 0 6px 6px;"
        "   background: white;"
        "}"
        "QTabBar::tab {"
        "   background: #f6f8fa;"
        "   color: #24292e;"
        "   border: 1px solid #e1e4e8;"
        "   border-bottom: none;"
        "   padding: 8px 16px;"
        "   border-top-left-radius: 6px;"
        "   border-top-right-radius: 6px;"
        "   margin-right: 2px;"
        "}"
        "QTabBar::tab:selected {"
        "   background: white;"
        "   border-bottom: 2px solid #f9826c;"
        "   font-weight: bold;"
        "}"
        "QGroupBox {"
        "   border: 1px solid #e1e4e8;"
        "   border-radius: 6px;"
        "   margin-top: 20px;"
        "   padding-top: 30px;"
        "   background: white;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   left: 16px;"
        "   padding: 0 8px;"
        "   background: white;"
        "   font-weight: bold;"
        "   color: #24292e;"
        "}"
        "QLabel {"
        "   color: #24292e;"
        "}"
        "QLineEdit, QTextEdit, QComboBox {"
        "   border: 1px solid #e1e4e8;"
        "   border-radius: 6px;"
        "   padding: 6px 8px;"
        "}"
        "QLineEdit:focus, QTextEdit:focus, QComboBox:focus {"
        "   border: 1px solid #0366d6;"
        "   outline: none;"
        "}"
        "QCheckBox {"
        "   spacing: 8px;"
        "}"
        "QCheckBox::indicator {"
        "   width: 16px;"
        "   height: 16px;"
        "}"
        "QListWidget {"
        "   border: 1px solid #e1e4e8;"
        "   border-radius: 6px;"
        "   background: white;"
        "}"
        "QScrollArea {"
        "   border: none;"
        "   background: transparent;"
        "}"
        );
}

QWidget* GitHubSettingsUI::createGeneralTab() {
    QWidget *tab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(20, 20, 20, 20);

    // 基本信息组
    QGroupBox *infoGroup = new QGroupBox("基本信息");
    QFormLayout *formLayout = new QFormLayout(infoGroup);
    formLayout->setContentsMargins(5, 5, 5, 5);
    formLayout->setSpacing(15);

    QLineEdit *projectName = new QLineEdit;
    projectName->setPlaceholderText("输入项目名称");
    projectName->setMinimumHeight(30);
    formLayout->addRow("项目名称:", projectName);

    QTextEdit *projectDesc = new QTextEdit;
    projectDesc->setPlaceholderText("项目描述...");
    projectDesc->setMinimumHeight(40);
    formLayout->addRow("项目描述:", projectDesc);

    QComboBox *visibility = new QComboBox;
    visibility->addItems({"公开", "私有", "内部"});
    visibility->setMinimumHeight(30);
    formLayout->addRow("可见性:", visibility);

    layout->addWidget(infoGroup);

    // 主题组
    QGroupBox *topicsGroup = new QGroupBox("主题标签");
    QVBoxLayout *topicsLayout = new QVBoxLayout(topicsGroup);
    topicsLayout->setContentsMargins(5, 5, 5, 5);

    QLineEdit *topicInput = new QLineEdit;
    topicInput->setPlaceholderText("添加主题标签 (按回车添加)");
    topicsLayout->addWidget(topicInput);

    QListWidget *topicsList = new QListWidget;
    topicsList->addItems({"documentation", "qt", "c++", "github-api"});
    topicsLayout->addWidget(topicsList);

    layout->addWidget(topicsGroup);

    // 底部占位
    layout->addStretch();

    return tab;
}

QWidget* GitHubSettingsUI::createRepoSettingsTab() {
    QWidget *tab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(20, 20, 20, 20);

    // 仓库设置组
    QGroupBox *repoGroup = new QGroupBox("仓库设置");
    QFormLayout *formLayout = new QFormLayout(repoGroup);
    formLayout->setContentsMargins(5, 5, 5, 5);
    formLayout->setSpacing(5);

    QComboBox *defaultBranch = new QComboBox;
    defaultBranch->addItems({"main", "develop", "feature/docs"});
    defaultBranch->setMinimumHeight(45);
    formLayout->addRow("默认分支:", defaultBranch);

    QCheckBox *autoMerge = new QCheckBox("启用自动合并");
    autoMerge->setMinimumHeight(20);
    formLayout->addRow("合并选项:", autoMerge);

    QCheckBox *wiki = new QCheckBox("启用项目维基");
    wiki->setMinimumHeight(20);
    formLayout->addRow("维基:", wiki);

    QCheckBox *projects = new QCheckBox("启用项目板");
    projects->setMinimumHeight(20);
    formLayout->addRow("项目板:", projects);

    QCheckBox *discussions = new QCheckBox("启用讨论区");
    discussions->setMinimumHeight(20);
    formLayout->addRow("讨论区:", discussions);

    layout->addWidget(repoGroup);

    // 合并选项组
    QGroupBox *mergeGroup = new QGroupBox("合并请求选项");
    QVBoxLayout *mergeLayout = new QVBoxLayout(mergeGroup);
    mergeLayout->setContentsMargins(5, 5, 5, 5);

    QComboBox *mergeMethod = new QComboBox;
    mergeMethod->addItems({"创建合并提交", "压缩合并", "变基合并"});
    mergeMethod->setMinimumHeight(40);
    mergeLayout->addWidget(mergeMethod);

    QCheckBox *requireReview = new QCheckBox("需要代码审查");
    mergeLayout->addWidget(requireReview);

    QCheckBox *requireChecks = new QCheckBox("需要状态检查通过");
    mergeLayout->addWidget(requireChecks);

    QCheckBox *requireLinear = new QCheckBox("需要线性历史");
    mergeLayout->addWidget(requireLinear);

    layout->addWidget(mergeGroup);

    // 底部占位
    layout->addStretch();

    return tab;
}

QWidget* GitHubSettingsUI::createAccessControlTab() {
    QWidget *tab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(20, 20, 20, 20);

    // 成员管理
    QGroupBox *membersGroup = new QGroupBox("成员管理");
    QVBoxLayout *membersLayout = new QVBoxLayout(membersGroup);
    membersLayout->setContentsMargins(5, 5, 5, 5);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    QLineEdit *searchInput = new QLineEdit;
    searchInput->setPlaceholderText("搜索用户...");
    QPushButton *addButton = new QPushButton("添加成员");
    addButton->setFixedWidth(120);

    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(addButton);
    membersLayout->addLayout(searchLayout);

    QListWidget *membersList = new QListWidget;
    membersList->addItems({
        "luobiwen (管理员)",
        "bomberman (维护者)",
        "mapmap (贡献者)",
        "ContractTest (贡献者)"
    });
    membersLayout->addWidget(membersList);

    layout->addWidget(membersGroup);

    // 团队权限
    QGroupBox *teamsGroup = new QGroupBox("团队权限");
    QFormLayout *teamsLayout = new QFormLayout(teamsGroup);
    teamsLayout->setContentsMargins(5, 5, 5, 5);
    teamsLayout->setSpacing(15);

    QComboBox *teamCombo = new QComboBox;
    teamCombo->addItems({"文档团队", "开发团队", "测试团队"});
    teamsLayout->addRow("团队:", teamCombo);

    QComboBox *permissionCombo = new QComboBox;
    permissionCombo->addItems({"管理员", "写入", "读取"});
    teamsLayout->addRow("权限:", permissionCombo);

    QPushButton *addTeamButton = new QPushButton("添加团队权限");
    teamsLayout->addRow(addTeamButton);

    layout->addWidget(teamsGroup);

    // 底部占位
    layout->addStretch();

    return tab;
}

QWidget* GitHubSettingsUI::createIntegrationTab() {
    QWidget *tab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(20, 20, 20, 20);

    // Webhooks
    QGroupBox *webhooksGroup = new QGroupBox("Webhooks");
    QVBoxLayout *webhooksLayout = new QVBoxLayout(webhooksGroup);
    webhooksLayout->setContentsMargins(5, 5, 5, 5);

    QListWidget *webhooksList = new QListWidget;
    webhooksList->addItems({
        "https://api.example.com/docs-updated",
        "https://ci.example.com/github-webhook"
    });
    webhooksLayout->addWidget(webhooksList);

    QPushButton *addWebhookButton = new QPushButton("添加 Webhook");
    webhooksLayout->addWidget(addWebhookButton);

    layout->addWidget(webhooksGroup);

    // 服务集成
    QGroupBox *servicesGroup = new QGroupBox("服务集成");
    QVBoxLayout *servicesLayout = new QVBoxLayout(servicesGroup);
    servicesLayout->setContentsMargins(5, 5, 5, 5);

    QComboBox *serviceCombo = new QComboBox;
    serviceCombo->addItems({
        "选择服务...",
        "Slack",
        "Microsoft Teams",
        "Discord",
        "Jenkins",
        "Travis CI"
    });
    servicesLayout->addWidget(serviceCombo);

    QFormLayout *serviceForm = new QFormLayout;
    QLineEdit *serviceUrl = new QLineEdit;
    serviceUrl->setPlaceholderText("https://");
    serviceForm->addRow("URL:", serviceUrl);

    QLineEdit *serviceToken = new QLineEdit;
    serviceToken->setPlaceholderText("访问令牌");
    serviceToken->setEchoMode(QLineEdit::Password);
    serviceForm->addRow("令牌:", serviceToken);

    servicesLayout->addLayout(serviceForm);

    QPushButton *addServiceButton = new QPushButton("添加服务");
    servicesLayout->addWidget(addServiceButton);

    layout->addWidget(servicesGroup);

    // 底部占位
    layout->addStretch();

    return tab;
}

QWidget* GitHubSettingsUI::createAdvancedTab() {
    QWidget *tab = new QWidget;
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->setContentsMargins(20, 20, 20, 20);

    // 归档选项
    QGroupBox *archiveGroup = new QGroupBox("归档选项");
    QVBoxLayout *archiveLayout = new QVBoxLayout(archiveGroup);
    archiveLayout->setContentsMargins(5, 5, 5, 5);

    QCheckBox *archiveRepo = new QCheckBox("归档此仓库");
    archiveRepo->setToolTip("归档的仓库是只读的，不能再提交或创建问题");
    archiveLayout->addWidget(archiveRepo);

    layout->addWidget(archiveGroup);

    // 转移所有权
    QGroupBox *transferGroup = new QGroupBox("转移所有权");
    QFormLayout *transferLayout = new QFormLayout(transferGroup);
    transferLayout->setContentsMargins(5, 5, 5, 5);
    transferLayout->setSpacing(15);

    QLineEdit *newOwner = new QLineEdit;
    newOwner->setPlaceholderText("新所有者用户名");
    transferLayout->addRow("新所有者:", newOwner);

    QComboBox *teamsCombo = new QComboBox;
    teamsCombo->addItems({"保留当前团队", "迁移到新所有者的团队"});
    transferLayout->addRow("团队:", teamsCombo);

    QPushButton *transferButton = new QPushButton("转移仓库");
    transferButton->setStyleSheet("background-color: #cb2431; color: white;");
    transferLayout->addRow(transferButton);

    layout->addWidget(transferGroup);

    // 删除仓库
    QGroupBox *deleteGroup = new QGroupBox("删除仓库");
    QVBoxLayout *deleteLayout = new QVBoxLayout(deleteGroup);
    deleteLayout->setContentsMargins(5, 5, 5, 5);

    QLabel *warningLabel = new QLabel(
        "删除此仓库将永久删除所有代码、问题和评论。此操作不可撤销。"
        );
    warningLabel->setWordWrap(true);
    warningLabel->setStyleSheet("color: #cb2431; font-weight: bold;");
    deleteLayout->addWidget(warningLabel);

    QLineEdit *confirmInput = new QLineEdit;
    confirmInput->setPlaceholderText("输入仓库名称以确认删除");
    deleteLayout->addWidget(confirmInput);

    QPushButton *deleteButton = new QPushButton("删除此仓库");
    deleteButton->setStyleSheet("background-color: #cb2431; color: white;");
    deleteLayout->addWidget(deleteButton);

    layout->addWidget(deleteGroup);

    // 底部占位
    layout->addStretch();

    scrollArea->setWidget(content);

    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->addWidget(scrollArea);

    return tab;
}
