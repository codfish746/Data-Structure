#include "mainwindow.h"
#include"ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
  :QWidget(parent, Qt::FramelessWindowHint)
  , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    this->setGeometry(200,100,750,500);
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(26);  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放
    picLabel=new QLabel(this);
    ui->showScroll->setWidget(picLabel);
    logHelper=new LogHelper(this);
    logHelper->setOutWidget(ui->out_log);

    initPixmap();
}



void MainWindow::on_maximizeButton_clicked()
{
    if(isFullScreen()){
        showNormal();
        ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
    }else{
        showFullScreen();
        ui->maximizeButton->setIcon(QIcon(":/res/maximize-button2.png"));
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QImage backgroundImage(QStringLiteral(":/img/res/background.png"));
    //painter.drawImage(rect(), backgroundImage);

    painter.setPen(QColor(50, 177, 122));
    painter.setBrush(QBrush(QColor(50, 177, 122),Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,this->width(),26);
    painter.end();


    QWidget::paintEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->y()<26){
        if(isFullScreen()){
            showNormal();
            ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
        }else{
            showFullScreen();
            ui->maximizeButton->setIcon(QIcon(":/res/maximize-button2.png"));
        }
    }

    QWidget::mouseDoubleClickEvent(event);
}


void MainWindow::on_btn_log_clicked()
{
    if(ui->out_log->isHidden()){
        ui->out_log->show();
    }else {
        ui->out_log->hide();
    }

}

void MainWindow::on_btn_parst_clicked()
{
    ui->input_tree->setPlainText(QApplication::clipboard()->text());
}

void MainWindow::on_btn_front_clicked()
{
    QString str=ui->input_tree->toPlainText();
    str.remove(QRegExp("\\s"));  //过滤所有的空白符号
    if(str.isEmpty()){
        logHelper->outWarm("你输入的序列不合法");
        return;
    }
    try{
        myTree.getTree(str.toStdString(),1);
    }catch(char* error){
        logHelper->outErr(error);
        initPixmap();
        return;
    }catch(...){
        logHelper->outErr("遇到不知名错误");
    }
    logHelper->outLog("前序生成二叉树,输入的序列是"+str);
    updatePixmap();
}

void MainWindow::on_btn_layout_clicked()
{
    QString str=ui->input_tree->toPlainText();
    str.remove(QRegExp("\\s"));  //过滤所有的空白符号
    if(str.isEmpty()){
        logHelper->outWarm("你输入的序列不合法");
        return;
    }
    try{
        myTree.getTree(str.toStdString(),2);
    }catch(char* error){
        logHelper->outErr(error);
        initPixmap();
        return;
    }catch(...){
        logHelper->outErr("遇到不知名错误");
    }
    logHelper->outLog("层序生成二叉树,输入的序列是"+str);
    updatePixmap();
}

void MainWindow::on_btn_find_clicked()
{
    QString findKey=ui->input_key->text();
    if(findKey.length()!=1){
        logHelper->outWarm("对不起,只能输入单个字符进行查找");
        return;
    }

    auto result=myTree.find(findKey[0].toLatin1());
    if(get<0>(result)){
        logHelper->outLog(QString("找到了这个节点,他的祖先节点的序列是:").append(get<1>(result).c_str()));
    }else{
        logHelper->outLog("没有找到这个节点");
    }
}

void MainWindow::on_btn_swap_clicked()
{
    myTree.swapTree();
    updatePixmap();
}

void MainWindow::on_btn_refrer_clicked()
{
    updatePixmap();
}

void MainWindow::on_btn_saveImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"),QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0], tr("Image Files (*.png *.jpg *.bmp)"));
    pixMap.save(fileName);

}

void MainWindow::initPixmap()
{
    pixMap=QPixmap(imgWidth,imgHeight);
    picLabel->setPixmap(pixMap);
}

void MainWindow::updatePixmap()
{
    initPixmap();
    if(!myTree.getRootNode()){
        return;
    }
    try{
        paintSonTree(myTree.getRootNode(),imgWidth/2,0);
    }catch(const char* str){
        logHelper->outWarm(str);
        initPixmap();
        return;
    }catch(...){
        logHelper->outErr("不知名错误");
        initPixmap();
        return;
    }

    picLabel->setPixmap(pixMap);

    ui->showScroll->verticalScrollBar()->setSliderPosition(imgHeight/2);
    ui->showScroll->horizontalScrollBar()->setSliderPosition(imgWidth/2);




    /*
    paintDirLine(QPoint(10,200),QPoint(100,100),pixmap);
    paintDirLine(QPoint(200,200),QPoint(100,100),pixmap);
    paintCircle(QPoint(100,100),'A',pixmap);
    picLabel->deleteLater();
    picLabel=new QLabel(this);
    ui->showScroll->setWidget(picLabel);
    picLabel->setPixmap(pixmap);

 老师,我在可视化二叉树中,遇到了一个问题:我是通过将图像绘制在QPixmap上,然后将QPixmap设置到QLabel上来显示这个图像,
但是我发现,当我多次刷新图像,就是说,我重复
 */



}

void MainWindow::paintDirLine(QPoint start, QPoint end)
{
    double c= atan2((start-end).y(),(start-end).x());
    end=end-(end-start)/sqrt(QPoint::dotProduct((end-start),(end-start)))*circleR*0.90;
    start=start+(end-start)/sqrt(QPoint::dotProduct((end-start),(end-start)))*circleR;
    QPainter painter(&pixMap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));

    double arrow_lenght_ = 10;//箭头长度，一般固定
    double arrow_degrees_ = 0.5;//箭头角度，一般固定

    double angle = atan2(end.y() - start.y(), end.x() - start.x()) + 3.1415926;//
    QPointF p1,p2;
    p1.setX( end.x() + arrow_lenght_ * cos(angle - arrow_degrees_));//求得箭头点1坐标
    p1.setY(end.y() + arrow_lenght_ * sin(angle - arrow_degrees_))  ;
    p2.setX(end.x() + arrow_lenght_ * cos(angle + arrow_degrees_));//求得箭头点2坐标
    p2.setY(end.y() + arrow_lenght_ * sin(angle + arrow_degrees_));
    painter.drawLine(start,end);
    painter.drawLine(p1,end);
    painter.drawLine(p2,end);
}

void MainWindow::paintCircle(QPoint center, QChar c)
{
    QPainter painter(&pixMap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Arial",fontSize,QFont::Bold,true));
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter.drawEllipse(center,circleR,circleR);
    QRect rect(center.x()-circleR,center.y()-circleR,circleR*2,circleR*2);
    painter.drawText(rect,Qt::AlignCenter,c);
}

void MainWindow::paintSonTree(TreeNode<char> *node, int x, int l)
{
    if(l>6){
        throw "对不起，你所输入的序列太深，所以无法进行显示";
    }
    paintCircle(QPoint(x,l*rowSpace+rootSpace),node->data);
    if(node->lNode){
        paintDirLine(QPoint(x,l*rowSpace+rootSpace),QPoint(x-columnSpace[l],(l+1)*rowSpace+rootSpace));
        paintSonTree(node->lNode,x-columnSpace[l],l+1);
    }
    if(node->rNode){
        paintDirLine(QPoint(x,l*rowSpace+rootSpace),QPoint(x+columnSpace[l],(l+1)*rowSpace+rootSpace));
        paintSonTree(node->rNode,x+columnSpace[l],l+1);
    }

}
