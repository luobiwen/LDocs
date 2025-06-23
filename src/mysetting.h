#ifndef MYSETTING_H
#define MYSETTING_H
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QTabWidget>
#include <QFrame>
#include <QScrollArea>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include <QIcon>

class GitHubSettingsUI : public QMainWindow {
    Q_OBJECT

public:
    explicit GitHubSettingsUI(QWidget *parent = nullptr);

private:
    QWidget* createGeneralTab();
    QWidget* createRepoSettingsTab();
    QWidget* createAccessControlTab();
    QWidget* createIntegrationTab();
    QWidget* createAdvancedTab();

};
#endif // MYSETTING_H
