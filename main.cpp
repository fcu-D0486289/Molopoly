#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <sstream>

#define origiMoney 10000
#define passStart 500
#define stayPrison 3
#define stayHospital 1

using namespace std;

class Prop{
    private:
        static char sign[3];
        static string name[3];
        static int price[3];
    public:
        static char Sign(int i){
            return sign[i];
        }
        static string Name(int i){
            return name[i];
        }
        static int Price(int i){
            return price[i];
        }
};
char Prop::sign[]  = {'@', '*', '#'};
string Prop::name[] = {"毒品", "地雷", "路障"};
int Prop::price[] = {300, 500, 1000};


class infomation{
    private:
        int price[5];   //建設費用
        int tolls[5];   //過路費
        int level;      //建設等級
        char owner;     //擁有者
    public:
        infomation(int p[], int t[]){
            for(int i = 0; i < 5; i++){
                price[i] = p[i];
                tolls[i] = t[i];
            }
            level = -1;
            owner = '\0';
        }

        void initial(char id){
            if(owner == id){
                level = -1;
                owner = '\0';
            }
        }

        void setowner(char o){
            owner = o;
        }

        void levelup(int n){
            level+=n;
        }

        int getprice(){
            return price[level+1];
        }

        int gettolls(){
            if(level == -1)  return 0;
            return tolls[level];
        }

        int getlevel(){
            return level;
        }

        char getowner(){
            return owner;
        }
};

class Map{
    private:
        int number;     //編號
        int type;       //起點:0 空地:1 機會:2 命運:3 醫院:4 監獄:5 商店:6
        string name;    //地名
        char prop;
    public:
        Map* next;
        infomation* info;
        Map(int num, int t, string n){
            number = num;
            type = t;
            name = n;
            prop = NULL;
            next = NULL;
            info = NULL;
        }

        int getnumber(){
            return number;
        }

        int gettype(){
            return type;
        }

        string getname(){
            return name;
        }

        char getprop(){
            return prop;
        }

        void setprop(char p){
            this->prop = p;
        }
};

int mapCount = 0;
int msgArea = 0;
Map* head = new Map(0, 0, "起點");
Map* temp = head;


class player{
    private:
        char id;
        string name;
        int money;
        int stay;
        int prop[3];
    public:
        Map* locate;
        player* next;
        player(char i, string n, int m){
            id = i;
            name = n;
            money = m;
            stay = 0;
            for(int k = 0; k < 3; k++)  prop[k] = 1;
            locate = head;
            next = NULL;
        }

        void addmoney(int m){
            this->money += m;
        }

        void addstay(int s){
            this->stay += s;
        }

        void addprop(int i, int n){
            this->prop[i] += n;
        }

        char getid(){
            return id;
        }

        string getname(){
            return name;
        }

        int getmoney(){
            return money;
        }

        int getstay(){
            return stay;
        }

        int getprop(int i){
            return prop[i];
        }
};

int playerCount = 0;
player* front = NULL;
player* rear = NULL;
player* flag = NULL;
player* out = NULL;

void searchMap(int n){
    temp = head;
    for(int i = 0; i < n; i++)
        temp = temp->next;
}

string* msg;
void initialMsg(){
    msg[0] = "\t\t\t\t\t    輪到玩家 " + front->getname() + "\t\t\t\t\t";
    for(int i = 1; i < msgArea; i++)
        msg[i] = "\t\t\t\t\t\t\t\t\t\t\t\t";
}

void Display(){
    system("CLS");
    int count;
//display Player information
    cout << endl << "\t\t\t\t\t\t\t\t";
    flag = front;
    do{
        cout << flag->getid() << "\t\t";
        flag = flag->next;
    }while(flag != NULL);
    cout << "\t\t\t";
    if(out != NULL){
        flag = out;
        do{
            cout << flag->getid() << "\t\t";
            flag = flag->next;
        }while(flag != NULL);
    }
    cout << endl << "\t\t\t\t\t\t\t\t";

    flag = front;
    do{
        cout << flag->getname() << "\t\t";
        flag = flag->next;
    }while(flag != NULL);
    cout << "\t\t\t";
    if(out != NULL){
        flag = out;
        do{
            cout << flag->getname() << "\t\t";
            flag = flag->next;
        }while(flag != NULL);
    }
    cout << endl << "\t\t\t\t\t\t\t\t";

    flag = front;
    do{
        cout << flag->getmoney() << "\t\t";
        flag = flag->next;
    }while(flag != NULL);
    cout << "\t\t\t";
    if(out != NULL){
        flag = out;
        do{
            cout << flag->getmoney() << "\t\t";
            flag = flag->next;
        }while(flag != NULL);
    }
    cout << endl << "\t\t\t\t\t\t\t\t";
    flag = front;
    do{
        for(int i = 0; i < 3; i++)
            cout << Prop::Sign(i) << ":" << flag->getprop(i) << " ";
        cout << "\t";
        flag = flag->next;
    }while(flag != NULL);
    cout << "\t\t\t";
    if(out != NULL){
        flag = out;
        do{
            for(int i = 0; i < 3; i++)
                cout << Prop::Sign(i) << ":" << flag->getprop(i) << " ";
            cout << "\t";
            flag = flag->next;
        }while(flag != NULL);
    }

    cout << endl << front->getname() << "'s turn:" << endl << endl;

//display Map
    cout << "\t\t\t";
    //TOP player and prop location
    searchMap(mapCount/2);
    for(int i = 0; i < mapCount/4+1; i++){
        count = 0;
        if(temp->getprop() != NULL){
            cout << temp->getprop();
            count++;
        }
        flag = front;
        for(int j = 0; j < playerCount; j++){
            if(temp->getnumber() == flag->locate->getnumber()){
                cout << flag->getid();
                count++;
            }
            flag = flag->next;
        }
        for(int k = count; k < 16; k++)  cout << " ";
        temp = temp->next;
    }
    cout << endl << "\t\t\t";
    //TOP map name
    searchMap(mapCount/2);
    for(int i = 0; i < mapCount/4+1; i++){
        cout << temp->getname() << "\t\t";
        temp = temp->next;
    }
    cout << endl << "\t\t\t";
    //TOP level
    searchMap(mapCount/2);
    for(int i = 0; i < mapCount/4+1; i++){
        if(temp->gettype() == 1){
            if(temp->info->getowner() != '\0')
                cout << " " << temp->info->getowner() << temp->info->getlevel()+1 << "\t\t";
            else
                cout << "Lv." << temp->info->getlevel()+1 << "\t\t";
        }
        else    cout << "\t\t";
        temp = temp->next;
    }
    cout << endl << "\t\t";
    //MID
    for(int i = 0; i < mapCount/4-1; i++){
        searchMap(mapCount/2-1-i);
        //左半邊
        if(temp->getprop() != NULL)
            cout << temp->getprop();
        flag = front;
        for(int j = 0; j < playerCount; j++){
            if(temp->getnumber() == flag->locate->getnumber())
                cout << flag->getid();
            flag = flag->next;
        }
        cout << "\t" << temp->getname() << "\t";
        if(temp->gettype() == 1){
            if(temp->info->getowner() != '\0')
                cout << " " << temp->info->getowner() << temp->info->getlevel()+1;
            else
                cout << "Lv." << temp->info->getlevel()+1;
        }
        cout << msg[i];
        for(int j = 0; j < mapCount/4+(2 * (i+1)); j++) temp = temp->next;
        //右半邊
        if(temp->gettype() == 1){
            if(temp->info->getowner() != '\0')
                cout << "" << temp->info->getowner() << temp->info->getlevel()+1 << "    ";
            else
                cout << "Lv." << temp->info->getlevel()+1 << "  ";
        }
        else    cout << "      ";

        cout << "  " << temp->getname() << "  ";

        if(temp->getprop() != NULL)
            cout << temp->getprop();
        flag = front;
        for(int j = 0; j < playerCount; j++){
            if(temp->getnumber() == flag->locate->getnumber())
                cout << flag->getid();
            flag = flag->next;
        }
        cout << endl << endl << "\t\t";
    }
    cout << "\t";
    //BOT level
    for(int i = mapCount/4; i >= 0; i--){
        searchMap(i);
        if(temp->gettype() == 1){
            if(temp->info->getowner() != '\0')
                cout << " " << temp->info->getowner() << temp->info->getlevel()+1 << "\t\t";
            else
                cout << "Lv." << temp->info->getlevel()+1 << "\t\t";
        }
        else    cout << "\t\t";
    }
    cout << endl << "\t\t\t";
    //BOT map name
    for(int i = mapCount/4; i >= 0; i--){
        searchMap(i);
        cout << temp->getname() << "\t\t";
    }
    cout << endl << "\t\t\t";
    //BOT player and prop location
    for(int i = mapCount/4; i >= 0; i--){
        searchMap(i);
        count = 0;
        if(temp->getprop() != NULL){
            cout << temp->getprop();
            count++;
        }
        flag = front;
        for(int k = 0; k < playerCount; k++){
            if(temp->getnumber() == flag->locate->getnumber()){
                cout << flag->getid();
                count++;
            }
            flag = flag->next;
        }
        for(int k = count; k < 16; k++)  cout << " ";
    }
    cout << endl << "\t\t\t";
}

bool createMap(){
    string name;
    int i, j, price[5], tolls[5];
    char in[100];
    fstream read;
    read.open("map.txt",ios::in);
    if(!read)   return false;
    for(mapCount = 1; read.getline(in,sizeof(in),'\t'); mapCount++){
        name = in;
        for(j = 0; j < 5; j++){
            read.getline(in,sizeof(in),'\t');
            price[j] = atoi(in);
        }
        for(j = 0; j < 5; j++){
            read.getline(in,sizeof(in),'\t');
            tolls[j] = atoi(in);
        }
        if(price[0] != 0){
            temp->next = new Map(mapCount,1,name);
            temp = temp->next;
            temp->info = new infomation(price,tolls);
        }
        else{
            if(name == "機會")    temp->next = new Map(mapCount,2,name);
            if(name == "命運")    temp->next = new Map(mapCount,3,name);
            if(name == "醫院")    temp->next = new Map(mapCount,4,name);
            if(name == "監獄")    temp->next = new Map(mapCount,5,name);
            if(name == "商店")    temp->next = new Map(mapCount,6,name);
            temp = temp->next;
        }
        read.getline(in,sizeof(in),'\n');
    }
    temp->next = head;
    temp = head;
    if(mapCount % 4 != 0)  return false;
    temp = head;
    msgArea = mapCount/4-1;     //Create magArea
    msg = new string[msgArea];
    return true;
}

void createPlayer(int money, int n){
    string name;
    cout << "Enter player's name" << endl;
    for(int i = 0; i < n; i++){
        cout << "P" << i+1 << ":";
        cin >> name;
        if(i == 0){
            front = new player(i+65,name,money);
            rear = front;
        }
        else{
            rear->next = new player(i+65,name,money);
            rear = rear->next;
        }
    }
}

bool yesORno(string m){
    bool choose = true;
    char keyboard;
    while(true){
        if(choose)  msg[msgArea/2-1] = "\t\t\t\t      " + m + " 是\t\t\t\t\t";
        else        msg[msgArea/2-1] = "\t\t\t\t      " + m + " 否\t\t\t\t\t";
        Display();
        fflush(stdin);
        keyboard = _getch();
        if(keyboard == 's' || keyboard == 'w'){
            if(choose == true)    choose = false;
            else                choose = true;
        }
        else if(keyboard == '\r'){
            return choose;
        }
    }
}

void selectMap(){
    int num = front->locate->getnumber();
    char keyboard;
    Map* sel = front->locate;
    while(true){
        msg[msgArea/2] = "\t\t\t\t\t  選擇一個位置:" + sel->getname() + "\t\t\t\t\t";
        Display();
        fflush(stdin);
        keyboard = _getch();
        if(keyboard == 's'){
            num--;
            if(num < 0) num = mapCount-1;
            sel = head;
            for(int i = 0; i < num; i++)
                sel = sel->next;
        }
        else if(keyboard == 'w'){
            num++;
            if(num == mapCount)  num = 0;
            sel = sel->next;
        }
        else if(keyboard == '\r')
            break;
    }
    temp = sel;
}

void selectPlayer(){
    int num = 0;
    char keyboard;
    flag = front;
    while(true){
        Display();
        cout << msg << "  選擇一位玩家: " << flag->getid();
        keyboard = _getch();
        if(keyboard == 's'){
            num--;
            if(num < 0) num = playerCount-1;
            flag = front;
            for(int i = 0; i < num; i++)
                flag = flag->next;

        }
        else if(keyboard == 'w'){
            num++;
            if(num = playerCount)   num = 0;
            flag = flag->next;
        }
        else if(keyboard == ' ')
            break;
        if(flag == NULL)    flag = front;
    }
}

int selectProp(){
    int num = 0;
    char keyboard;
    while(true){
        msg[msgArea/2] = "\t\t\t\t\t  選擇一個道具:" + Prop::Name(num) + "\t\t\t\t\t";
        Display();
        fflush(stdin);
        keyboard = _getch();
        if(keyboard == 's'){
            num--;
            if(num < 0) num = 2;
        }
        else if(keyboard == 'w'){
            num++;
            if(num == 3)  num = 0;
        }
        else if(keyboard == '\r')
            return num;
    }
}

void act(){
    Prop prop;
    int c;
    string m;
    char choose;
    switch(front->locate->gettype()){
        case 6: //Store
            cout << "Price:\n  drug\t\tLandmine\tRoadlock\n";
            cout << "  300\t\t  500\t\t  1000\n";
            for(int i = 0; i < 3; i++){
                cout << "How many " << prop.Name(i) << " do you want to buy?";
                cin >> c;
                if(front->getmoney() - prop.Price(i)*(-c) < 0){
                    cout << "Not enough money to buy the prop!!" << endl;
                    break;
                }
                front->addprop(i,c);
                front->addmoney(prop.Price(i)*(-c));
            }
            break;
        case 5: //Prison
            cout << "Stay in prison for 3 days" << endl;
            front->addstay(stayPrison);
            break;
        case 4: //Hospital
            cout << "Spend 200 dollar to be hospitalized for 1 day" << endl;
            front->addstay(stayHospital);
            front->addmoney(-200);
            break;
        case 3: //Fortune
            c = rand()%7;
            switch(c){
                case 0:
                    c = rand()%mapCount;
                    while(temp->getnumber() != c)
                        temp = temp->next;
                    cout << "被指派送公文至" << temp->getname() << endl;
                    front->locate = temp;
                    break;
                case 1:
                    cout << "生日被丟到學思湖裡" << endl;
                    while(temp->getname() != "學思")
                        temp = temp->next;
                    front->locate = temp;
                case 2:
                    cout << "不小心走進21步道,媽媽收到21通知單,零用錢扣500元" << endl;
                    front->addmoney(-500);
                    break;
                case 3:
                    cout << "不小心走進分手步道,右手骨折送醫住院兩天" << endl;
                    while(temp->getname() != "醫院")
                        temp = temp->next;
                    front->locate = temp;
                    front->addstay(2);
                    break;
                case 4:
                    cout << "期末考快到了,停留一天讀書抱佛腳" << endl;
                    front->addstay(1);
                    break;
                case 5:
                    cout << "福星小偷來襲,每人各被偷了300元" << endl;
                    flag = front;
                    do{
                        flag->addmoney(-300);
                        flag = flag->next;
                    }while(flag != NULL);
                    break;
                case 6:
                    cout << "逢甲清冰哥勇逮福星小偷,歸還每人200元贓款" << endl;
                    flag = front;
                    do{
                        flag->addmoney(200);
                        flag = flag->next;
                    }while(flag != NULL);
                    break;
                case 7:
                    c = rand()%mapCount;
                    while(temp->getnumber() != c)
                        temp = temp->next;
                    cout << temp->getname() << "施工中,安全考量加設路障" << endl;
                    temp->setprop('#');
                    break;
                case 8:
                    do{
                        c = rand()%mapCount;
                        while(temp->getnumber() != c)
                            temp = temp->next;
                    }while(temp->gettype()!=1);
                    cout << "校長將簽賭贏得的賭金重點發展在 " << temp->getname() << " 上" << endl;
                    cout << temp->getname() << " 等級上升一級!!" << endl;
                    temp->info->levelup(1);
                    break;
                case 9:
                    do{
                        c = rand()%mapCount;
                        while(temp->getnumber() != c)
                            temp = temp->next;
                    }while(temp->gettype()!=1);
                    cout << temp->getname() << " 的實驗室發生意外,損失慘重" << endl;
                    cout << temp->getname() << " 等級下降一級!!" << endl;
                    temp->info->levelup(-1);
                    break;
            }
            break;
        case 2: //Chanced
            c = rand()%3;
            switch(c){
                case 0:
                    m = "寫信給校長,請他幫忙升級一塊地\n";
                    while(true){
                        selectMap();
                        if(temp->gettype() == 1)    break;
                        cout << "無法升級特殊地標!!" << endl;
                    }
                    temp->info->levelup(1);
                    break;
                case 1:
                    m = "半夜偷偷剪掉某地的總電源線路,損失慘重造成降低一級\n";
                    while(true){
                        selectMap();
                        if(temp->gettype() == 1)    break;
                        cout << "無法攻擊特殊地標!!" << endl;
                    }
                    temp->info->levelup(-1);
                    break;
                case 2:
                    m = "選擇一塊土地,以500元強制徵收該地\n";
                    if(front->getmoney() < 500){
                        cout << "您的財產不足以徵收任何土地" << endl;
                        break;
                    }
                    while(true){
                        selectMap();
                        if(temp->gettype() == 1)    break;
                        cout << "無法徵收特殊地標!!" << endl;
                    }
                    if(temp->info->getowner() != '\0'){
                        flag = front;
                        do{
                            flag = flag->next;
                        }while(temp->info->getowner() != flag->getid());
                        flag->addmoney(500);
                    }
                    temp->info->setowner(front->getid());
                    front->addmoney(-500);
                    break;
            }
            break;
        case 1: //land
            //無主
            if(front->locate->info->getowner() == '\0'){
                if(front->getmoney() > front->locate->info->getprice()){
                    cout << "This land's price is " << front->locate->info->getprice() << endl;
                    cout << "After you buy it, you still have " << front->getmoney()-front->locate->info->getprice() << " dollars" << endl;
                    cout << "Wanna buy the land?(y/n):";
                    fflush(stdin);
                    do{
                        cin >> choose;
                        if(choose == 'y' || choose == 'n')  break;
                        cout << "Please enter again:";
                    }while(true);
                    if(choose == 'y'){
                        front->addmoney(-front->locate->info->getprice());
                        front->locate->info->setowner(front->getid());
                        front->locate->info->levelup(1);
                    }
                }
                else{
                    cout << "Not enough money to buy the land" << endl;
                    cout << "land price :" << front->locate->info->getprice() << endl;
                }

            }
            //為主
            else if(front->locate->info->getowner() == front->getid()){
                if(front->locate->info->getlevel() == 5){
                    cout << "The level is highest!!" << endl;
                }
                else if(front->getmoney() > front->locate->info->getprice()){
                    cout << "Upgrade this land's price is " << front->locate->info->getprice() << " dollars" << endl;
                    cout << "After you upgrade it, you still have " << front->getmoney()-front->locate->info->getprice() << " dollars" << endl;
                    cout << "Wanna upgrade the land?(y/n):";
                    fflush(stdin);
                    do{
                        cin >> choose;
                        if(choose == 'y' || choose == 'n')  break;
                        cout << "Please enter again:";
                    }while(true);
                    if(choose == 'y'){
                        front->addmoney(-front->locate->info->getprice());
                        front->locate->info->levelup(1);
                    }
                }
                else{
                    cout << "Not enough money to upgrade the land" << endl;
                    cout << "land price :" << front->locate->info->getprice() << endl;
                }
            }
            //他主
            else if(front->locate->info->getowner() != '\0'){
                front->addmoney(-front->locate->info->gettolls());
                flag = front;
                while(flag->getid() != front->locate->info->getowner())
                    flag = flag->next;
                flag->addmoney(front->locate->info->gettolls());
                cout << "The land is belong to " << front->locate->info->getowner() << endl;
                cout << "You should pay " << front->locate->info->gettolls() << " dollars" << endl;
            }
    }
}

void move(int n){
    initialMsg();
    msg[msgArea/4] = "\t\t\t\t\t    【擲骰移動】\t\t\t\t\t";
    stringstream ss;
    int i, dice, step = 0;
    string toString, diceTotal = "";
    msg[msgArea/2-1] = "\t\t\t\t\t  按任何鍵擲骰子...\t\t\t\t\t";
    Display();
    fflush(stdin);  _getch();
    msg[msgArea/2-1] = "\t\t\t\t\t\t\t\t\t\t\t\t";
    for(i = 0; i < n; i++){
        dice = rand()%6+1;
        ss << dice; ss >> toString;
        diceTotal += toString;
        if(i != n-1)    diceTotal += " + ";
        step += dice;
        ss.clear();
    }
    ss << step; ss >> toString;
    diceTotal += (" = " + toString);
    msg[msgArea/2] = "\t\t\t\t\t     " + diceTotal + "\t\t\t\t\t\t";
    Display();
    ss.clear();
    msg[msgArea/2-1] = "\t\t\t\t\t  按任何鍵開始移動...\t\t\t\t\t";
    Display();
    fflush(stdin);  _getch();
    msg[msgArea/2-1] = "\t\t\t\t\t\t\t\t\t\t\t\t";
    for(i = 0; i < step; i++){
        front->locate = front->locate->next;
        if(front->locate->gettype() == 0 && step - i > 1){   //經過起點
            ss << passStart; ss >> toString;
            msg[msgArea/2-1] = "\t\t\t\t\t  經過起點,獲得 " + toString + " 元\t\t\t\t\t";
            front->addmoney(passStart);
            ss.clear();
        }
        ss << step-i-1; ss >> toString;
        msg[msgArea/2+1] = "\t\t\t\t\t         " + toString + "\t\t\t\t\t\t";
        Display();
        if(front->locate->getprop() == '#'){
            front->locate->setprop(NULL);
            msg[msgArea/2-1] = "\t\t\t\t       一個路障擋住了你的去路\t\t\t\t\t";
            Display();
            break;
        }
        ss.clear();
        Sleep(350);
    }
    cout << "Arrive: " << front->locate->getname() << endl;
    if(front->locate->getprop() == '@'){
        front->locate->setprop(NULL);
        while(front->locate->getname() != "監獄") front->locate = front->locate->next;
        msg[msgArea/2-1] = "\t\t\t\t     你撿起一包白白的粉末,碰巧被警察看到...\t\t\t\t\t";
        Display();
    }
    if(front->locate->getprop() == '*'){
        front->locate->setprop(NULL);
        while(front->locate->getname() != "醫院") front->locate = front->locate->next;
    }
    act();
}

void setprop(){
    initialMsg();
    msg[msgArea/4] = "\t\t\t\t\t    【設置道具】\t\t\t\t\t";
    string m;
    int prop, place;
    bool choose;
    if(front->getprop(0) != 0 || front->getprop(1) != 0 || front->getprop(2) != 0){
        m = "是否在地圖上設置道具?";
        choose = yesORno(m);
        Display();
        while(choose){
            msg[msgArea/2+1] = "\t\t\t\t\t\t\t\t\t\t\t\t";
            while(true){
                prop = selectProp();
                if(front->getprop(prop) != 0)  break;
                msg[msgArea/2+1] = "\t\t\t\t    你眼睛業障重啊," + Prop::Name(prop) + "什麼的都是假的\t\t\t\t";
                Display();
            }
            msg[msgArea/2+1] = "\t\t\t\t\t\t\t\t\t\t\t\t";
            while(true){
                selectMap();
                if(temp->getprop() == NULL) break;
                msg[msgArea/2+1] = "\t\t\t\t\t    該處已有道具\t\t\t\t\t";
                Display();
            }

            temp->setprop(Prop::Sign(prop));
            front->addprop(prop, -1);
            msg[msgArea/2] = "\t\t\t\t\t\t\t\t\t\t\t\t";
            msg[msgArea/2+1] = "\t\t\t\t\t    道具設置成功\t\t\t\t\t";
            Display();

            if(front->getprop(0) == 0 && front->getprop(1) == 0 && front->getprop(2) == 0)  break;
            m = "\t是否繼續設置道具?";
            choose = yesORno(m);
        }
    }
    move(2);
}

bool switchplayer(){
    flag = front;
    front = front->next;
    if(flag->getmoney() < 0){
        if(out == NULL){
            out = flag;
            out->next = NULL;
        }
        else{
            flag->next = out;
            out = flag;
        }
        return false;
    }
    else{
        rear->next = flag;
        rear = flag;
        rear->next = NULL;
        return true;
    }
}

void initialmap(player* o){
    temp = head;
    do{
        if(temp->gettype() == 1)
            temp->info->initial(o->getid());
        temp = temp->next;
    }while(temp != head);
}

int main(){
    srand(time(NULL));
    int m = origiMoney;
    string name;
    if(!createMap()){
        cout << "Loading map failed\n";
        return 0;
    }
    system("CLS");
    cout << "How many players:";
    cin >> playerCount;
    createPlayer(m,playerCount);
    while(playerCount != 1){
        Display();
        if(front->getstay() != 0){
            cout << front->getname() << " still stay " << front->getstay() << " days\n";
            front->addstay(-1);
        }
        else    setprop();
        if(!switchplayer()){
            initialmap(out);
            playerCount--;
        }
        system("pause");
    }
    Display();
    return 0;
}
