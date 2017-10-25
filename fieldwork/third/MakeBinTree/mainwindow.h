#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QPainter>
#include<QDebug>
#include<QFileDialog>
#include<QClipboard>
#include<QLabel>
#include<QStandardPaths>
#include<QMouseEvent>
#include<QScrollBar>
#include<QPixmap>
#include<math.h>
#include<tuple>
#include"lib/framlessHelper/qwidget/framelesshelper.h"
#include"struct/CharTree.h"
#include"struct/myQueue.h"
#include"lib/logHelper/loghelper.h"
using namespace std;
namespace Ui {
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);



public slots:
private slots:

    void on_maximizeButton_clicked();

    void on_btn_log_clicked();

    void initPixmap();
    void updatePixmap();        //更新二叉树的图像
    void paintDirLine(QPoint start,QPoint end);
    void paintCircle(QPoint center,QChar c);
    //绘制子树,传入子树根节点的位置,以及根节点的层数
    void  paintSonTree(TreeNode<char>* node, int x,int l);
    void on_btnPaste1_clicked();

    void on_btnPaste2_clicked();

    void on_btnSave_clicked();

    void on_btnRefresh_clicked();

    void on_btnDraw_clicked();

private:
    Ui::MainWindow *ui;
    LogHelper* logHelper;
    CharTree myTree;
    QPixmap pixMap;
    QLabel *picLabel;
    double circleR=15;
    int fontSize=15;
    int rootSpace=20;//根节点上方空出的位置
    int imgWidth=2000;
    int imgHeight=700;
    double rowSpace=100;
    double columnSpace[6]={500,250,125,62.5,31,16};
protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // MAINWINDOW_H
