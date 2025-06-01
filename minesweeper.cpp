#include<bits/stdc++.h>
using namespace std;

const int BOARD_SIZE=18;
const int MINES=1;
char board[BOARD_SIZE][BOARD_SIZE];
char board_ans[BOARD_SIZE][BOARD_SIZE];
void countmines(int row,int col,char board_ans[BOARD_SIZE][BOARD_SIZE]){
    int cnt=0;
    for(int i=row-1;i<=row+1;i++){
        for(int j=col-1;j<=col+1;j++){
            if(i>=0&&i<BOARD_SIZE&&j>=0&&j<BOARD_SIZE&&board_ans[i][j]=='*')cnt++;
        }
    }
    char c=cnt+'0';
    board_ans[row][col]=c;
}
void initboard(){
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            board[i][j]='.';
        }
    }
}
void initboard_ans(int row,int col){
    vector< pair<int,int> > pos;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(!(i==row&&j==col)){
                pos.emplace_back(i,j);
            }
        }
    }
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            board_ans[i][j]='!';
        }
    }
    random_shuffle(pos.begin(),pos.end());
    int r,c;
    for(int i=0;i<MINES;i++){
        r=pos[i].first;
        c=pos[i].second;
        board_ans[r][c]='*';
    }
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(board_ans[i][j]!='*'){
                countmines(i,j,board_ans);
            }
        }
    }
}
void displayboard(char board[BOARD_SIZE][BOARD_SIZE]){
    cout<<"    a b c d e f g h i j k l m n o p q r"<<endl;
    cout<<"    -----------------------------------" << endl;
    for(int i=0;i<BOARD_SIZE;i++){
        if(i<=8)cout<<" ";
        cout<<i+1<<"| ";
        for(int j=0;j<BOARD_SIZE;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
void revealzeros(int row,int col){
    if(row<0||row>=BOARD_SIZE||col<0||col>=BOARD_SIZE||board[row][col]!='.'){
        return;
    }
    board[row][col]=board_ans[row][col]; 
    if(board_ans[row][col]=='0'){
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if(i==0&&j==0)continue;
                revealzeros(row+i,col+j);
            }
        }
    }
}

bool win(){
    int cnt=0;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(board[i][j]=='.'||board[i][j]=='f'){
                cnt++;
            }
        }
    }
    return cnt==MINES;
}
bool lose(int row,int col){
    return board_ans[row][col]=='*';
}

int main(){
    srand(time(0));
    initboard();
    displayboard(board);
    cout<<"Welcome to the minesweeper game.\nPlease enter the position of the block you want to check first:";
    char c;
    int r;
    while(r>BOARD_SIZE||r<1||c>'r'||c<'a'){
        cin>>c>>r;
    }
    initboard_ans(r-1,c-'a');
    if(board_ans[r-1][c-'a']=='0'){
        revealzeros(r-1,c-'a');
    }
    else{
        board[r-1][c-'a']=board_ans[r-1][c-'a'];
    }
    displayboard(board);
    int mode=1;
    while(true){
        if(win()){
            for(int i=0;i<BOARD_SIZE;i++){
                for(int j=0;j<BOARD_SIZE;j++){
                    if(board_ans[i][j]=='*')board_ans[i][j]='f';
                }
            }
            displayboard(board_ans);
            cout<<"Congratulations, you win!!!\n";
            break;
        }
        if(mode==1){
            cout<<"Please enter the position of the block you want to check.\nIf you want to switch to establishing-flag mode,press \'s\':\n";
            char col;
            int row;
            bool ll=false;
            while(true){
                cin>>col;
                if((col>='a'&&col<='r')||col=='s'){
                    break;
                }
                ll=true;
                cout<<"Invalid input. Please enter a valid position(ex.a1):\n";
            }
            if(col=='s'){
                mode=2;
                continue;
            }
            while(true){
                cin>>row;
                if(row>=1&&row<=BOARD_SIZE)break;
                if(!ll)cout<<"Invalid input. Please enter a valid position(ex.a1):\n";
            }
            if(lose(row-1,col-'a')){
                displayboard(board_ans);
                cout<<"Boom!\nSorry, you lose.:(\nPlease try it again.\n";
                break;
            }
            else{
                if(board_ans[row-1][col-'a']=='0'){
                    revealzeros(row-1,col-'a');
                }
                else{
                    board[row-1][col-'a']=board_ans[row-1][col-'a'];
                }
                displayboard(board);
            }
        }
        if(mode==2){
            cout<<"Please enter the position of the block you want to establish or cancel a flag.\nIf you want to switch to digging mode,press \'s\':\n";
            char col;
            int row;
            bool ll=false;
            while(true){
                cin>>col;
                if((col>='a'&&col<='r')||col=='s'){
                    break;
                }
                ll=true;
                cout<<"Invalid input. Please enter a valid position(ex.a1):\n";
            }
            if(col=='s'){
                mode=1;
                continue;
            }
            while(true){
                cin>>row;
                if(row>=1&&row<=BOARD_SIZE)break;
                if(!ll)cout<<"Invalid input. Please enter a valid position(ex.a1):\n";
            }
            if(board[row-1][col-'a']=='.')board[row-1][col-'a']='f';
            else if(board[row-1][col-'a']=='f')board[row-1][col-'a']='.';
            displayboard(board);
        }
    }
}


