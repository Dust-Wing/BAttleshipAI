#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

namespace BattleShip{

class Ship{
private:
    char ch;
    int sz;
    int hp;
public:
    Ship(){
        ch='?';
        sz=0;
        hp=0;
    }
    Ship(char c,int s){
        ch=c;
        sz=s;
        hp=0;
    }
    char getCh(){
        return ch;
    }
    int getSz(){
        return sz;
    }
    void hit(){
        hp++;
    }
    bool dead(){
        return hp>=sz;
    }
};

class Board{
private:
    int r;
    int c;
    vector<vector<char>> b;
    vector<vector<char>> s;
public:
    Board(){
        r=0;
        c=0;
    }
    Board(int rr,int cc){
        r=rr;
        c=cc;
        b=vector<vector<char>>(r,vector<char>(c,'*'));
        s=vector<vector<char>>(r,vector<char>(c,'*'));
    }
    int rows(){
        return r;
    }
    int cols(){
        return c;
    }
    bool in(int x,int y){
        return x>=0&&x<r&&y>=0&&y<c;
    }
    bool shot(int x,int y){
        return s[x][y]!='*';
    }
    bool ship(int x,int y){
        return b[x][y]!='*';
    }
    bool can(int x,int y,char d,int n){
        if(d=='h'){
            if(y+n>c){
                return false;
            }
            for(int i=0;i<n;i++){
                if(b[x][y+i]!='*'){
                    return false;
                }
            }
        }else{
            if(x+n>r){
                return false;
            }
            for(int i=0;i<n;i++){
                if(b[x+i][y]!='*'){
                    return false;
                }
            }
        }
        return true;
    }
    void put(int x,int y,char d,char z,int n){
        if(d=='h'){
            for(int i=0;i<n;i++){
                b[x][y+i]=z;
            }
        }else{
            for(int i=0;i<n;i++){
                b[x+i][y]=z;
            }
        }
    }
    char fire(int x,int y){
        if(b[x][y]=='*'){
            s[x][y]='O';
            return '*';
        }
        s[x][y]='X';
        return b[x][y];
    }
    void showOwn(){
        cout<<"  ";
        for(int j=0;j<c;j++){
            cout<<j;
            if(j+1<c){
                cout<<" ";
            }
        }
        cout<<'\n';
        for(int i=0;i<r;i++){
            cout<<i<<" ";
            for(int j=0;j<c;j++){
                cout<<b[i][j];
                if(j+1<c){
                    cout<<" ";
                }
            }
            cout<<'\n';
        }
    }
    void showShot(){
        cout<<"  ";
        for(int j=0;j<c;j++){
            cout<<j;
            if(j+1<c){
                cout<<" ";
            }
        }
        cout<<'\n';
        for(int i=0;i<r;i++){
            cout<<i<<" ";
            for(int j=0;j<c;j++){
                cout<<s[i][j];
                if(j+1<c){
                    cout<<" ";
                }
            }
            cout<<'\n';
        }
    }
};

class Player{
protected:
    string nm;
    Board bd;
    vector<Ship> sh;
public:
    Player(string n,int r,int c,vector<Ship> v){
        nm=n;
        bd=Board(r,c);
        sh=v;
    }
    virtual ~Player(){
    }
    string name(){
        return nm;
    }
    int rows(){
        return bd.rows();
    }
    int cols(){
        return bd.cols();
    }
    bool valid(int x,int y){
        return bd.in(x,y)&&!bd.shot(x,y);
    }
    bool hasShip(int x,int y){
        return bd.ship(x,y);
    }
    void sortShips(){
        for(int i=0;i<(int)sh.size();i++){
            for(int j=i+1;j<(int)sh.size();j++){
                if(sh[j].getCh()<sh[i].getCh()){
                    Ship t=sh[i];
                    sh[i]=sh[j];
                    sh[j]=t;
                }
            }
        }
    }
    bool alive(){
        for(int i=0;i<(int)sh.size();i++){
            if(!sh[i].dead()){
                return true;
            }
        }
        return false;
    }
    void showShot(){
        bd.showShot();
    }
    void turn(Player& e){
        cout<<nm<<"'s shots"<<'\n';
        e.showShot();
        pair<int,int> p=move(e);
        int x=p.first;
        int y=p.second;
        cout<<nm<<" fired at "<<x<<" "<<y<<'\n';
        char z=e.bd.fire(x,y);
        if(z=='*'){
            cout<<nm<<" missed"<<'\n';
        }else{
            cout<<nm<<" hit "<<e.nm<<"'s "<<z<<" ship"<<'\n';
            for(int i=0;i<(int)e.sh.size();i++){
                if(e.sh[i].getCh()==z){
                    e.sh[i].hit();
                    if(e.sh[i].dead()){
                        cout<<nm<<" destroyed "<<e.nm<<"'s "<<z<<" ship"<<'\n';
                    }
                }
            }
        }
        learn(x,y,z,e);
    }
    virtual void place()=0;
    virtual pair<int,int> move(Player& e)=0;
    virtual void learn(int x,int y,char z,Player& e){
    }
};

class HumanPlayer:public Player{
public:
    HumanPlayer(string n,int r,int c,vector<Ship> v):Player(n,r,c,v){
    }
    void place(){
        sortShips();
        for(int i=0;i<(int)sh.size();i++){
            bool ok=false;
            while(!ok){
                cout<<nm<<"'s board"<<'\n';
                bd.showOwn();
                cout<<nm<<", place ship "<<sh[i].getCh()<<" of size "<<sh[i].getSz()<<'\n';
                cout<<"Enter H for horizontal or V for vertical:"<<'\n';
                string d;
                getline(cin,d);
                if(d.size()!=1||(d[0]!='H'&&d[0]!='h'&&d[0]!='V'&&d[0]!='v')){
                    cout<<"Invalid direction"<<'\n';
                    continue;
                }
                char dir=(char)tolower(d[0]);
                cout<<"Enter row and column:"<<'\n';
                string ln;
                getline(cin,ln);
                stringstream ss(ln);
                int x,y;
                string more;
                if(!(ss>>x>>y)||ss>>more){
                    cout<<"Invalid coordinate"<<'\n';
                    continue;
                }
                if(!bd.in(x,y)){
                    cout<<"Invalid coordinate"<<'\n';
                    continue;
                }
                if(!bd.can(x,y,dir,sh[i].getSz())){
                    cout<<"Ship cannot be placed there"<<'\n';
                    continue;
                }
                bd.put(x,y,dir,sh[i].getCh(),sh[i].getSz());
                ok=true;
            }
        }
    }
    pair<int,int> move(Player& e){
        while(true){
            cout<<nm<<", enter row and column to fire:"<<'\n';
            string ln;
            getline(cin,ln);
            stringstream ss(ln);
            int x,y;
            string more;
            if(!(ss>>x>>y)||ss>>more){
                cout<<"Invalid move"<<'\n';
                continue;
            }
            if(!e.valid(x,y)){
                cout<<"Invalid move"<<'\n';
                continue;
            }
            return make_pair(x,y);
        }
    }
};

class AIPlayer:public Player{
public:
    static mt19937 gen;
    AIPlayer(string n,int r,int c,vector<Ship> v):Player(n,r,c,v){
    }
    virtual pair<int,int> move(Player& e)=0;
    void place(){
        sortShips();
        for(int i=0;i<(int)sh.size();i++){
            bool ok=false;
            while(!ok){
                cout<<nm<<"'s board"<<'\n';
                bd.showOwn();
                cout<<nm<<" is placing ship "<<sh[i].getCh()<<" of size "<<sh[i].getSz()<<'\n';
                uniform_int_distribution<int> dd(0,1);
                int a=dd(gen);
                char dir='h';
                if(a==1){
                    dir='v';
                }
                int mr;
                int mc;
                if(dir=='h'){
                    mr=bd.rows()-1;
                    mc=bd.cols()-sh[i].getSz();
                }else{
                    mr=bd.rows()-sh[i].getSz();
                    mc=bd.cols()-1;
                }
                uniform_int_distribution<int> dr(0,mr);
                uniform_int_distribution<int> dc(0,mc);
                int x=dr(gen);
                int y=dc(gen);
                if(bd.can(x,y,dir,sh[i].getSz())){
                    bd.put(x,y,dir,sh[i].getCh(),sh[i].getSz());
                    ok=true;
                }
            }
        }
    }
};

mt19937 AIPlayer::gen;

class CheatingAI:public AIPlayer{
public:
    CheatingAI(string n,int r,int c,vector<Ship> v):AIPlayer(n,r,c,v){
    }
    pair<int,int> move(Player& e){
        for(int i=0;i<e.rows();i++){
            for(int j=0;j<e.cols();j++){
                if(e.valid(i,j)&&e.hasShip(i,j)){
                    return make_pair(i,j);
                }
            }
        }
        for(int i=0;i<e.rows();i++){
            for(int j=0;j<e.cols();j++){
                if(e.valid(i,j)){
                    return make_pair(i,j);
                }
            }
        }
        return make_pair(0,0);
    }
};

class RandomAI:public AIPlayer{
protected:
    vector<pair<int,int>> pts;
public:
    RandomAI(string n,int r,int c,vector<Ship> v):AIPlayer(n,r,c,v){
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                pts.push_back(make_pair(i,j));
            }
        }
    }
    void place(){
        AIPlayer::place();
        shuffle(pts.begin(),pts.end(),gen);
    }
    void rem(int x,int y){
        for(int i=0;i<(int)pts.size();i++){
            if(pts[i].first==x&&pts[i].second==y){
                pts.erase(pts.begin()+i);
                return;
            }
        }
    }
    pair<int,int> move(Player& e){
        while(!pts.empty()){
            pair<int,int> p=pts.back();
            pts.pop_back();
            if(e.valid(p.first,p.second)){
                return p;
            }
        }
        return make_pair(0,0);
    }
};

class SearchAndDestroyAI:public RandomAI{
private:
    vector<pair<int,int>> todo;
public:
    SearchAndDestroyAI(string n,int r,int c,vector<Ship> v):RandomAI(n,r,c,v){
    }
    bool has(int x,int y){
        for(int i=0;i<(int)todo.size();i++){
            if(todo[i].first==x&&todo[i].second==y){
                return true;
            }
        }
        return false;
    }
    void add(Player& e,int x,int y){
        if(e.valid(x,y)&&!has(x,y)){
            todo.push_back(make_pair(x,y));
            rem(x,y);
        }
    }
    pair<int,int> move(Player& e){
        while(!todo.empty()){
            pair<int,int> p=todo[0];
            todo.erase(todo.begin());
            if(e.valid(p.first,p.second)){
                return p;
            }
        }
        return RandomAI::move(e);
    }
    void learn(int x,int y,char z,Player& e){
        if(z!='*'){
            add(e,x,y-1);
            add(e,x-1,y);
            add(e,x,y+1);
            add(e,x+1,y);
        }
    }
};

}

int main(int argc,char** argv){
    using namespace BattleShip;
    if(argc<2){
        cout<<"Missing configuration file"<<'\n';
        return 1;
    }
    ifstream fin(argv[1]);
    if(!fin){
        cout<<"Could not open configuration file"<<'\n';
        return 1;
    }
    int r,c,n;
    fin>>r>>c>>n;
    vector<Ship> v;
    for(int i=0;i<n;i++){
        char ch;
        int sz;
        fin>>ch>>sz;
        v.push_back(Ship(ch,sz));
    }
    unsigned int seed;
    if(argc>=3){
        stringstream ss(argv[2]);
        ss>>seed;
    }else{
        seed=(unsigned int)time(0);
    }
    AIPlayer::gen.seed(seed);
    int md=0;
    while(md<1||md>3){
        cout<<"Choose game mode:"<<'\n';
        cout<<"1. Human Vs Human"<<'\n';
        cout<<"2. Human Vs AI"<<'\n';
        cout<<"3. AI Vs AI"<<'\n';
        string ln;
        getline(cin,ln);
        stringstream ss(ln);
        string more;
        if(!(ss>>md)||ss>>more||md<1||md>3){
            cout<<"Invalid choice"<<'\n';
            md=0;
        }
    }
    Player* p1=0;
    Player* p2=0;
    int ac=1;
    if(md==1){
        string a,b;
        cout<<"Player 1, enter your name:"<<'\n';
        getline(cin,a);
        cout<<"Player 2, enter your name:"<<'\n';
        getline(cin,b);
        p1=new HumanPlayer(a,r,c,v);
        p2=new HumanPlayer(b,r,c,v);
    }else if(md==2){
        string a;
        cout<<"Player 1, enter your name:"<<'\n';
        getline(cin,a);
        int t=0;
        while(t<1||t>3){
            cout<<"Choose AI:"<<'\n';
            cout<<"1. CheatingAI"<<'\n';
            cout<<"2. RandomAI"<<'\n';
            cout<<"3. SearchAndDestroyAI"<<'\n';
            string ln;
            getline(cin,ln);
            stringstream ss(ln);
            string more;
            if(!(ss>>t)||ss>>more||t<1||t>3){
                cout<<"Invalid choice"<<'\n';
                t=0;
            }
        }
        p1=new HumanPlayer(a,r,c,v);
        if(t==1){
            p2=new CheatingAI("AI "+to_string(ac),r,c,v);
        }else if(t==2){
            p2=new RandomAI("AI "+to_string(ac),r,c,v);
        }else{
            p2=new SearchAndDestroyAI("AI "+to_string(ac),r,c,v);
        }
        ac++;
    }else{
        int t1=0;
        while(t1<1||t1>3){
            cout<<"Choose AI for player 1:"<<'\n';
            cout<<"1. CheatingAI"<<'\n';
            cout<<"2. RandomAI"<<'\n';
            cout<<"3. SearchAndDestroyAI"<<'\n';
            string ln;
            getline(cin,ln);
            stringstream ss(ln);
            string more;
            if(!(ss>>t1)||ss>>more||t1<1||t1>3){
                cout<<"Invalid choice"<<'\n';
                t1=0;
            }
        }
        int t2=0;
        while(t2<1||t2>3){
            cout<<"Choose AI for player 2:"<<'\n';
            cout<<"1. CheatingAI"<<'\n';
            cout<<"2. RandomAI"<<'\n';
            cout<<"3. SearchAndDestroyAI"<<'\n';
            string ln;
            getline(cin,ln);
            stringstream ss(ln);
            string more;
            if(!(ss>>t2)||ss>>more||t2<1||t2>3){
                cout<<"Invalid choice"<<'\n';
                t2=0;
            }
        }
        if(t1==1){
            p1=new CheatingAI("AI "+to_string(ac),r,c,v);
        }else if(t1==2){
            p1=new RandomAI("AI "+to_string(ac),r,c,v);
        }else{
            p1=new SearchAndDestroyAI("AI "+to_string(ac),r,c,v);
        }
        ac++;
        if(t2==1){
            p2=new CheatingAI("AI "+to_string(ac),r,c,v);
        }else if(t2==2){
            p2=new RandomAI("AI "+to_string(ac),r,c,v);
        }else{
            p2=new SearchAndDestroyAI("AI "+to_string(ac),r,c,v);
        }
        ac++;
    }
    (*p1).place();
    (*p2).place();
    while((*p1).alive()&&(*p2).alive()){
        (*p1).turn(*p2);
        if(!(*p2).alive()){
            break;
        }
        (*p2).turn(*p1);
    }
    if((*p1).alive()){
        cout<<(*p1).name()<<" won"<<'\n';
    }else{
        cout<<(*p2).name()<<" won"<<'\n';
    }
    delete p1;
    delete p2;
    return 0;
}
