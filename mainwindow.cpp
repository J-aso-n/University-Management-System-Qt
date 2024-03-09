#include "mainwindow.h"
#include "ui_mainwindow.h"

//全局变量，不然会出问题，qt很多匪夷所思
top _school,_party,_committee,_d_unit,_a_unit;//五个顶层模块,设为全局
QVariant varValue[5]={QVariant::fromValue(_school),QVariant::fromValue(_party),QVariant::fromValue(_committee)
                     ,QVariant::fromValue(_d_unit),QVariant::fromValue(_a_unit)};//包装五个结构体
unit person_list;//人员列表，全局
int check[5]={0,0,0,0,0};//正在查看哪一个top
QLineEdit *edit1;//避免connect出现的弱智错误，设为全局算了
QLineEdit *edit2;//避免connect出现的弱智错误，设为全局算了

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTableWidget *Table=ui->table;//表格，用来显示list信息
    Table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不允许编辑
    Table->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单
    this->setWindowTitle("manage_system");
    initial(varValue);
    //测试
    //qDebug()<<varValue[0].value<top>().list[0]->name;


    //单击学院按钮，显示属下的学院list
    QObject::connect(ui->school,&QPushButton::clicked,[&](){
        const top school = varValue[0].value<top>();//学院
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        check_(0);
        showTable(school,Table);
    });
    //单击党群组织按钮，显示属下的list
    QObject::connect(ui->party,&QPushButton::clicked,[&](){
        const top party = varValue[1].value<top>();//党群组织
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        check_(1);
        showTable(party,Table);
    });
    //单击行政机构按钮，显示属下的list
    QObject::connect(ui->committee,&QPushButton::clicked,[&](){
        const top committee = varValue[2].value<top>();//行政机构
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        check_(2);
        showTable(committee,Table);
    });
    //单击直属机构按钮，显示属下的list
    QObject::connect(ui->d_unit,&QPushButton::clicked,[&](){
        const top d_unit = varValue[3].value<top>();//直属机构
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        check_(3);
        showTable(d_unit,Table);
    });
    //单击附属机构按钮，显示属下的list
    QObject::connect(ui->a_unit,&QPushButton::clicked,[&](){
        const top a_unit = varValue[4].value<top>();//附属机构
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        check_(4);
        showTable(a_unit,Table);
    });

    //查找人员
    QObject::connect(ui->find_person,&QPushButton::clicked,[&](){
        QTableWidget *Table=ui->table;//表格，用来显示list信息
        QString name=ui->textEdit2->toPlainText();//要查找的姓名
        person *target=NULL;

        for(auto mid:person_list.list){
            if(mid->name==name){//找到了
                target=mid;
                //qDebug()<<target->name;
            }
        }
        if(target==NULL){//没找到
            QMessageBox::warning(this,"Warning",QStringLiteral("未找到该人员"));
        }
        else{//此时已经找到了,显示在表格中
            check_(7);
            showPerson(target,Table);
        }
    });

}

//初始化顶层
//先new一个所需结构，然后从varvalue中分离出要加入的top层，加入top层之后再replace原来的varvalue数组
void initial(QVariant *varValue){
    //学院部分
    unit *s_electron=new unit();//电信学院
    s_electron->name="电信学院";
    unit *s_economic=new unit();//经管学院
    s_economic->name="经管学院";
    unit *s_medicine=new unit();//医学院
    s_medicine->name="医学院";
    unit *s_software=new unit();//软件学院
    s_software->name="软件学院";
    unit *s_math=new unit();//数学学院
    s_math->name="数学学院";
    unit *s_material=new unit();//材料学院
    s_material->name="材料学院";
    unit *s_car=new unit();//汽车学院
    s_car->name="汽车学院";

    top school = varValue[0].value<top>();//学院
    school.list.append(s_electron);
    school.list.append(s_economic);
    school.list.append(s_medicine);
    school.list.append(s_software);
    school.list.append(s_math);
    school.list.append(s_material);
    school.list.append(s_car);
    school.name="学院";

        //党群组织部分
        unit *p_office=new unit();//党委办公室
        p_office->name="党委办公室";

        top party = varValue[1].value<top>();//党群组织
        party.list.append(p_office);
        party.name="党群组织";


            //行政机构部分
            unit *c_board=new unit();//校务委员会
            c_board->name="校务委员会";
            unit *c_student=new unit();//学生代表大会
            c_student->name="学生代表大会";
            unit *c_master=new unit();//研究生委员会
            c_master->name="研究生委员会";

            top committee = varValue[2].value<top>();
            committee.list.append(c_board);
            committee.list.append(c_student);
            committee.list.append(c_master);
            committee.name="行政机构";


                //直属机构部分
                top d_unit = varValue[3].value<top>();
                d_unit.name="直属单位";


                    //附属机构部分
                    top a_unit = varValue[4].value<top>();
                    a_unit.name="附属单位";


                        //添加person部分
                        person *LiHong = new person();
                        LiHong->name="李红";
                        LiHong->list.append(p_office);//属于党委办公室
                        LiHong->job.append("主管");//党委办公室主管
                        p_office->list.append(LiHong);
                        LiHong->list.append(s_electron);//属于电信学院
                        LiHong->job.append("副主管");
                        s_electron->list.append(LiHong);
                        LiHong->list.append(c_board);//属于校务委员会
                        LiHong->job.append("员工");
                        c_board->list.append(LiHong);

                        person* lv =new person();
                        lv->name="氯雷他定";
                        lv->list.append(p_office);//属于党委办公室
                        lv->job.append("员工");
                        p_office->list.append(lv);

                        person *Maotao = new person();
                        Maotao->name="五指毛桃";
                        Maotao->list.append(p_office);//属于党委办公室
                        Maotao->job.append("副主管");
                        p_office->list.append(Maotao);
                        Maotao->list.append(s_electron);//属于电信学院
                        Maotao->job.append("主管");
                        s_electron->list.append(Maotao);

                        person_list.list.append(LiHong);
                        person_list.list.append(lv);
                        person_list.list.append(Maotao);


    varValue[0]=QVariant::fromValue(school);
    varValue[1]=QVariant::fromValue(party);
    varValue[2]=QVariant::fromValue(committee);
    varValue[3]=QVariant::fromValue(d_unit);
    varValue[4]=QVariant::fromValue(a_unit);
}

//显示表格内容
void MainWindow::showTable(const top theTop,QTableWidget *Table){
    Table->clearContents();

    ui->title->setText(theTop.name);
    int row=theTop.list.size()/3+(theTop.list.size()%3!=0);//表格行
    int col=(theTop.list.size()<3)?theTop.list.size():3;//表格列
    Table->setRowCount(row);
    Table->setColumnCount(col);

    QStringList strs = {"1", "2","3"};//表头标题
    Table->setHorizontalHeaderLabels(strs);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(i*3+j<theTop.list.size()){
                Table->setItem(i,j,new QTableWidgetItem(theTop.list[i*3+j]->name));
                Table->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }
        }
    }
}

//显示unit中的人员
void MainWindow::showUnit(unit *theUnit,QTableWidget *Table){
    Table->clearContents();

    ui->title->setText(theUnit->name);
    int row=theUnit->list.size();//表格行
    int col=2;//表格列
    Table->setRowCount(row);
    Table->setColumnCount(col);

    QStringList strs = {"职位", "姓名"};//表头标题
    Table->setHorizontalHeaderLabels(strs);

    my_sort(theUnit);

    //第一列职位
    for(int i=0;i<row;i++){
        person *mid = theUnit->list[i];
        int place = std::find(mid->list.begin(),mid->list.end(),theUnit)-mid->list.begin();//找到person对应的unit中的job
        Table->setItem(i,0,new QTableWidgetItem(theUnit->list[i]->job[place]));
        Table->item (i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    //第二列名字
    for(int i=0;i<row;i++){
        Table->setItem(i,1,new QTableWidgetItem(theUnit->list[i]->name));
        Table->item (i,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

//显示该人员具体信息
void MainWindow::showPerson(const person *thePerson,QTableWidget *Table){
    Table->clearContents();

    ui->title->setText(thePerson->name);
    int row=thePerson->list.size();//表格行
    int col=2;//表格列
    Table->setRowCount(row);
    Table->setColumnCount(col);

    QStringList strs = {"部门", "职位"};//表头标题
    Table->setHorizontalHeaderLabels(strs);

    //第一列部门
    for(int i=0;i<row;i++){
        Table->setItem(i,0,new QTableWidgetItem(thePerson->list[i]->name));
        Table->item (i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    //第二列职位
    for(int i=0;i<row;i++){
        Table->setItem(i,1,new QTableWidgetItem(thePerson->job[i]));
        Table->item (i,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

//给unit中的人员进行排序，默认主管，副主管，员工
void my_sort(unit *theUnit){
    int i=0;
    for(auto mid : theUnit->list){
        int place = std::find(mid->list.begin(),mid->list.end(),theUnit)-mid->list.begin();//找到person对应的unit中的job
        if(mid->job[place]=="主管"){
            std::swap(theUnit->list[i],theUnit->list[0]);
        }
        else if(mid->job[place]=="副主管"){
            std::swap(theUnit->list[i],theUnit->list[(1>=theUnit->list.size())?0:1]);
        }
        i++;
    }
}

//查找是否存在该unit
unit* find_unit(QString name){
    unit* result=NULL;
    top school = varValue[0].value<top>();//学院
    top party = varValue[1].value<top>();//学院
    top committee = varValue[2].value<top>();//学院
    top d_unit = varValue[3].value<top>();//学院
    top a_unit = varValue[4].value<top>();//学院

    for(auto mid:school.list){
        if(mid->name==name){//找到了
            return result=mid;
        }
    }
    for(auto mid:party.list){
        if(mid->name==name){//找到了
            return result=mid;
        }
    }
    for(auto mid:committee.list){
        if(mid->name==name){//找到了
            return result=mid;
        }
    }
    for(auto mid:d_unit.list){
        if(mid->name==name){//找到了
            return result=mid;
        }
    }
    for(auto mid:a_unit.list){
        if(mid->name==name){//找到了
            return result=mid;
        }
    }
    return result;
}

//更新ena数组，0-5正在查看top，(6)check[0]=-1正在查看unit中的人，(7)check[0]=-2正在查看人的具体信息
void check_(int n){
    for(int i=0;i<5;i++){
        if(i==n){
            check[i]=1;
        }
        else{
            check[i]=0;
        }
    }
    if(n==6){
        check[0]=-1;
    }
    else if(n==7){
        check[0]=-2;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//定义双击表格事件
void MainWindow::on_table_cellDoubleClicked(int row, int column)
{
    QTableWidget *Table=ui->table;//表格，用来显示list信息

    int now_check=(check[0]==1)?0:
                ((check[1]==1)?1:
                ((check[2]==1)?2:
                ((check[3]==1)?3:
                ((check[4]==1)?4:
                ((check[0]==-1)?5:
                ((check[0]==-2)?6:-1))))));
    if(now_check==-1 || Table->rowHeight(0)==0){
        return;
    }
    else if(now_check>=0&&now_check<=4){//查看top中的unit
        top check_top = varValue[now_check].value<top>();
        if(row*3+column>=check_top.list.size()){//错误处理
            return;
        }
        unit *check_unit = check_top.list[row*3+column];

        showUnit(check_unit,Table);
        check_(6);//查看unit中的具体人
    }
    else if(now_check==5){//正在查看unit中的人
        QString name = Table->item(row,column)->text();

        person *target=NULL;

        for(auto mid:person_list.list){
            if(mid->name==name){//找到了
                target=mid;
            }
        }
        if(target==NULL){//没找到
            return;
        }
        else{//此时已经找到了,显示在表格中
            showPerson(target,Table);
        }
        check_(7);//查看具体person中
    }
    else if(now_check==6){//正在查看具体person
        QString check_unit = Table->item(row,column)->text();//选中的unit
        unit* target=NULL;

        if(column==1){//选中的是职业，不管
            return;
        }
        target=find_unit(check_unit);
        if(target==NULL){//没找到unit
            QMessageBox::warning(this,"Warning",QStringLiteral("未找到该部门"));
            return;
        }
        else{
            //qDebug()<<target->name;
            showUnit(target,Table);
            check_(6);//查看unit中的具体人
        }
    }

}

//添加unit事件
void MainWindow::add_unit(top& check_top,int now_check,QTableWidget *Table){
    addWindow *w = new addWindow;

    w->setWindowTitle("添加部门");
    w->resize(400,100);

    QPushButton *btn = new QPushButton("添加部门");//添加一个按钮
    //设置按钮的父亲是当前窗口，等于是添加到窗口中显示
    btn->setParent(w);
    btn->setGeometry(200,60,100,30);

    edit1 = new QLineEdit(w);
    edit1->setPlaceholderText("请输入部门名称");
    edit1->setGeometry(100, 25, 200, 30);//(x, y, w, h)

    w->show();

    connect(btn,&QPushButton::clicked,[this,check_top,w,now_check,Table]()mutable{//注意调用函数的部分，参数表示const，mutable让他们可以被改变
        QString text = edit1->text();

        if(text!=""){//有内容
            unit* target=find_unit(text);//看是否已经存在的
            if(target!=NULL){//已经存在，加入即可
                int exist=0;
                for(auto mid:check_top.list){
                    if(mid==target){//本top中已经有了，不用加了
                        exist=1;
                        break;
                    }
                }
                if(exist==1){
                    QMessageBox::warning(w,"Warning",QStringLiteral("已经存在该部门"));
                }
                else{//加入该top中
                    check_top.list.append(target);
                    varValue[now_check]=QVariant::fromValue(check_top);
                    QMessageBox::warning(w,"Warning",QStringLiteral("添加成功"));
                    showTable(check_top,Table);
                }
            }
            else{//创建一个unit
                target=new unit;
                target->name=text;

                check_top.list.append(target);
                varValue[now_check]=QVariant::fromValue(check_top);
                QMessageBox::warning(w,"Warning",QStringLiteral("成功创建部门，添加成功"));
                showTable(check_top,Table);
            }
        }
    });
}

//添加person事件
void MainWindow::add_person(unit *check_unit,QTableWidget *Table){
    addWindow *w = new addWindow;

    w->setWindowTitle("添加人员");
    w->resize(400,200);

    QPushButton *btn = new QPushButton("添加人员");//添加一个按钮
    //设置按钮的父亲是当前窗口，等于是添加到窗口中显示
    btn->setParent(w);
    btn->setGeometry(220,100,100,30);

    QLabel *name = new QLabel("人名");
    name->setParent(w);
    name->setGeometry(50,25,50,30);

    QLabel *job = new QLabel("职位");
    job->setParent(w);
    job->setGeometry(50,65,50,30);

    edit1 = new QLineEdit(w);
    edit1->setPlaceholderText("请输入人名");
    edit1->setGeometry(100, 25, 200, 30);//(x, y, w, h)

    edit2 = new QLineEdit(w);
    edit2->setPlaceholderText("请输入职位");
    edit2->setGeometry(100, 65, 200, 30);//(x, y, w, h)

    w->show();

    connect(btn,&QPushButton::clicked,[this,check_unit,w,Table]()mutable{//注意调用函数的部分，参数表示const，mutable让他们可以被改变
        QString text1 = edit1->text();
        QString text2 = edit2->text();

        if(text1==""){
            QMessageBox::warning(w,"Warning",QStringLiteral("请输入人名"));
        }
        else if(text2==""){
            QMessageBox::warning(w,"Warning",QStringLiteral("请输入职位"));
        }
        else{//有内容
            person* target=NULL;
            for(auto mid:person_list.list){
                if(mid->name==text1){
                    target=mid;
                    break;
                }
            }
            if(target!=NULL){//已经存在，加入即可
                int exist=0;
                for(auto mid:check_unit->list){
                    if(mid==target){//本unit中已经有了，不用加了
                        exist=1;
                        break;
                    }
                }
                if(exist==1){
                    QMessageBox::warning(w,"Warning",QStringLiteral("已经存在该人员"));
                }
                else{//加入该unit中
                    check_unit->list.append(target);//unit加入人

                    target->list.append(check_unit);//人加入unit
                    target->job.append(text2);

                    QMessageBox::warning(w,"Warning",QStringLiteral("添加成功"));
                    showUnit(check_unit,Table);
                }
            }
            else{//创建一个人
                target=new person;
                target->name=text1;

                check_unit->list.append(target);
                target->list.append(check_unit);//人加入unit
                target->job.append(text2);

                person_list.list.append(target);

                QMessageBox::warning(w,"Warning",QStringLiteral("成功创建人员，欢迎回家"));
                showUnit(check_unit,Table);
            }
        }
    });
}

//person添加unit
void MainWindow::add_3(person *check_person,QTableWidget *Table){
    addWindow *w = new addWindow;

    w->setWindowTitle("添加职位");
    w->resize(400,200);

    QPushButton *btn = new QPushButton("添加职位");//添加一个按钮
    //设置按钮的父亲是当前窗口，等于是添加到窗口中显示
    btn->setParent(w);
    btn->setGeometry(220,100,100,30);

    QLabel *name = new QLabel("部门");
    name->setParent(w);
    name->setGeometry(50,25,50,30);

    QLabel *job = new QLabel("职位");
    job->setParent(w);
    job->setGeometry(50,65,50,30);

    edit1 = new QLineEdit(w);
    edit1->setPlaceholderText("请输入部门");
    edit1->setGeometry(100, 25, 200, 30);//(x, y, w, h)

    edit2 = new QLineEdit(w);
    edit2->setPlaceholderText("请输入职位");
    edit2->setGeometry(100, 65, 200, 30);//(x, y, w, h)

    w->show();

    connect(btn,&QPushButton::clicked,[this,check_person,w,Table]()mutable{//注意调用函数的部分，参数表示const，mutable让他们可以被改变
        QString text1 = edit1->text();
        QString text2 = edit2->text();

        if(text1==""){
            QMessageBox::warning(w,"Warning",QStringLiteral("请输入部门"));
        }
        else if(text2==""){
            QMessageBox::warning(w,"Warning",QStringLiteral("请输入职位"));
        }
        else{//有内容
            unit* target=find_unit(text1);
            if(target!=NULL){//已经存在，加入即可
                int exist=0;
                for(auto mid:check_person->list){
                    if(mid==target){//本unit中已经有了，不用加了
                        exist=1;
                        break;
                    }
                }
                if(exist==1){
                    QMessageBox::warning(w,"Warning",QStringLiteral("该人员已经是该部门员工"));
                }
                else{//加入该unit中
                    check_person->list.append(target);
                    check_person->job.append(text2);

                    target->list.append(check_person);//人加入unit

                    QMessageBox::warning(w,"Warning",QStringLiteral("添加成功"));
                    showPerson(check_person,Table);
                }
            }
            else{//不可创建
                QMessageBox::warning(w,"Warning",QStringLiteral("不存在此部门"));
            }
        }
    });
}

//右键添加或删除事件
void MainWindow::on_table_customContextMenuRequested(const QPoint &pos)
{
    QTableWidget *Table=ui->table;//表格，用来显示list信息
    QLabel *title = ui->title;
    QMenu menu;

    int now_check=(check[0]==1)?0:
                ((check[1]==1)?1:
                ((check[2]==1)?2:
                ((check[3]==1)?3:
                ((check[4]==1)?4:
                ((check[0]==-1)?5:
                ((check[0]==-2)?6:-1))))));
    if(now_check==-1){
        //QMessageBox::warning(this,"Warning",QStringLiteral("无内容"));
        return;
    }
    else if(now_check>=0&&now_check<=4 && Table->rowHeight(0)!=0){//正在查看top中的unit
        QAction *add = menu.addAction(tr("添加"));
        //menu.addSeparator();
        QAction *clear = menu.addAction(tr("删除"));

        int row=pos.y()/Table->rowHeight(0)+(pos.y()%Table->rowHeight(0)!=0) -1;//选中的行和列（从0开始）
        int col=pos.x()/Table->columnWidth(0)+(pos.x()%Table->columnWidth(0)!=0) -1;
        top check_top = varValue[now_check].value<top>();

        //删除事件
        connect(clear, &QAction::triggered, [&](){
            if(row*3+col<check_top.list.size()){
                unit* check_unit = check_top.list[row*3+col];
                check_top.list.erase(check_top.list.begin()+row*3+col);//top删除这个unit
                varValue[now_check]=QVariant::fromValue(check_top);

                if(find_unit(check_unit->name)==NULL){//其他的top中也没有这个unit了
                    //对应所有人都要删除这个unit
                    for(auto mid:person_list.list){
                        QVector<unit*>::iterator num = std::find(mid->list.begin(),mid->list.end(),check_unit);
                        if(num!=mid->list.end()){//该人属于这个unit
                            int place=num-mid->list.begin();
                            mid->list.erase(mid->list.begin()+place);
                            mid->job.erase(mid->job.begin()+place);
                        }
                    }
                    //清除该unit空间
                    delete check_unit;
                }

                showTable(check_top,Table);
            }
        });
        //添加事件
        connect(add, &QAction::triggered, [=,&check_top](){
            //qDebug()<<check_top.list[0]->name;
            add_unit(check_top,now_check,Table);
        });
    }
    else if(now_check>=0&&now_check<=4 && Table->rowHeight(0)==0){//正在查看top中的unit但是没有unit
        QAction *add = menu.addAction(tr("添加"));

        top check_top = varValue[now_check].value<top>();

        //添加事件
        connect(add, &QAction::triggered, [=,&check_top](){
            add_unit(check_top,now_check,Table);
        });
    }
    else if(now_check==5 && Table->rowHeight(0)!=0){//正在查看unit中的person
        QAction *add = menu.addAction(tr("添加"));
        //menu.addSeparator();
        QAction *clear = menu.addAction(tr("删除"));

        int row=pos.y()/Table->rowHeight(0)+(pos.y()%Table->rowHeight(0)!=0) -1;//选中的行和列（从0开始）
        //int col=pos.x()/Table->columnWidth(0)+(pos.x()%Table->columnWidth(0)!=0) -1;
        QString unit_name = title->text();
        unit *check_unit = find_unit(unit_name);
        if(check_unit==NULL) return;//一般不存在这个情况

        //删除事件
        connect(clear, &QAction::triggered, [&](){
            if(row<check_unit->list.size()){
                person *check_person = check_unit->list[row];
                check_unit->list.erase(check_unit->list.begin()+row);//对应unit删除这个人
                //对应人删除这个unit
                int place = std::find(check_person->list.begin(),check_person->list.end(),check_unit)-check_person->list.begin();
                check_person->list.erase(check_person->list.begin()+place);
                check_person->job.erase(check_person->job.begin()+place);

                showUnit(check_unit,Table);
            }
        });
        //添加事件
        connect(add, &QAction::triggered, [&](){
            add_person(check_unit,Table);
        });
    }
    else if(now_check==5 && Table->rowHeight(0)==0){//正在查看unit中的person但是没有person
        QAction *add = menu.addAction(tr("添加"));

        QString unit_name = title->text();
        unit *check_unit = find_unit(unit_name);
        if(check_unit==NULL) return;//一般不存在这个情况

        //添加事件
        connect(add, &QAction::triggered, [&](){
            add_person(check_unit,Table);
        });
    }
    else if(now_check==6 && Table->rowHeight(0)!=0){//正在查看person具体所属
        QAction *add = menu.addAction(tr("添加"));
        //menu.addSeparator();
        QAction *clear = menu.addAction(tr("删除"));

        int row=pos.y()/Table->rowHeight(0)+(pos.y()%Table->rowHeight(0)!=0) -1;//选中的行和列（从0开始）
        //int col=pos.x()/Table->columnWidth(0)+(pos.x()%Table->columnWidth(0)!=0) -1;
        QString person_name = title->text();
        person *check_person=NULL;
        for(auto mid:person_list.list){
            if(mid->name==person_name){
                check_person=mid;
            }
        }
        if(check_person==NULL) return;//一般不会有

        //删除事件
        connect(clear, &QAction::triggered, [&](){
            if(row<check_person->list.size()){
                unit* check_unit = check_person->list[row];
                check_person->list.erase(check_person->list.begin()+row);//对应person删除unit
                check_person->job.erase(check_person->job.begin()+row);
                //对应unit删除这个人
                int place = std::find(check_unit->list.begin(),check_unit->list.end(),check_person)-check_unit->list.begin();
                check_unit->list.erase(check_unit->list.begin()+place);
                showPerson(check_person,Table);
            }
        });
        //添加事件
        connect(add, &QAction::triggered, [&](){
            add_3(check_person,Table);
        });
    }
    //qDebug()<<pos<<row<<col<<check_top.list.size();

    menu.exec(QCursor::pos());
}

