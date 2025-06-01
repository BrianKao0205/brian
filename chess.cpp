#include<bits/stdc++.h>
using namespace std;

const int BOARD_SIZE=8;
class ChessBoard{
private:
    vector< vector< char > > board;
    void generatePawnmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        int d=isWhite(board[row][col])? -1:1;
        int srow=isWhite(board[row][col])? 6:1;
        int erow=isWhite(board[row][col])? 0:7;
        if(board[row+d][col]=='.'){
            ChessBoard newBoard=*this;
            newBoard.board[row+d][col]=board[row][col];
            if(row+d==erow)newBoard.board[row+d][col]=isWhite(board[row][col])? 'q':'Q';
            newBoard.board[row][col]='.';
            possiblemoves.push_back(newBoard);
        }
        if(row==srow&&board[row+d][col]=='.'&&board[row+2*d][col]=='.'){
            ChessBoard newBoard=*this;
            newBoard.board[row+d][col]=board[row][col];
            newBoard.board[row][col]='.';
            possiblemoves.push_back(newBoard);
        }
        for(int dy=-1;dy<=1;dy+=2) {
            int newRow=row+d;
            int newCol=col+dy;
            if (newCol>=0&&newCol<BOARD_SIZE&&isWhite(board[row][col])!=isWhite(board[newRow][newCol])&&board[newRow][newCol]!='.'){
                ChessBoard newBoard=*this;
                newBoard.board[newRow][newCol]=board[row][col];
                newBoard.board[row][col]='.';
                possiblemoves.push_back(newBoard);
            }
        }
    }
    void generateRookmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        generateLinearMoves(row,col,possiblemoves,{{1,0},{-1,0},{0,1},{0,-1}});
    }
    void generateBishopmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        generateLinearMoves(row,col,possiblemoves,{{1,1},{-1,1},{-1,-1},{1,-1}});
    }
    void generateQueenmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        generateLinearMoves(row,col,possiblemoves,{{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{-1,-1},{1,-1}});
    }
    void generateKnightmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        vector< pair<int,int> >dirc={{2,1},{2,-1},{-2,-1},{-2,1},{1,2},{1,-2},{-1,-2},{-1,2}};
        for(pair<int,int>d:dirc){
            int newRow=row+d.first;
            int newCol=col+d.second;
            if(newRow>=0&&newRow<BOARD_SIZE&&newCol>=0&&newCol<BOARD_SIZE){
                if(isWhite(board[newRow][newCol])!=isWhite(board[row][col])){
                    ChessBoard newBoard=*this;
                    newBoard.board[newRow][newCol]=board[row][col];
                    newBoard.board[row][col]='.';
                    possiblemoves.push_back(newBoard);
                }
            }
        }
    }
    void generateKingmoves(int row,int col,vector<ChessBoard> &possiblemoves){
        vector< pair<int,int> >dirc={{1,1},{1,-1},{-1,-1},{-1,1},{1,0},{-1,0},{0,1},{0,-1}};
        for(pair<int,int>d:dirc){
            int newRow=row+d.first;
            int newCol=col+d.second;
            if(newRow>=0&&newRow<BOARD_SIZE&&newCol>=0&&newCol<BOARD_SIZE){
                if(isWhite(board[newRow][newCol])!=isWhite(board[row][col])){
                    ChessBoard newBoard=*this;
                    newBoard.board[newRow][newCol]=board[row][col];
                    newBoard.board[row][col]='.';
                    newBoard.updateKingMoved(board[row][col]);
                    possiblemoves.push_back(newBoard);
                }
            }
        }
    }
    void generateCastlingmoves(int row,int col,vector<ChessBoard>& possiblemoves){
        if (isWhite(board[row][col])){
            if(!whiteKingMoved&&!whiteRookRightMoved&&board[7][5]=='.'&&board[7][6]=='.'){
                ChessBoard newBoard=*this;
                newBoard.board[7][6]='k';
                newBoard.board[7][5]='r';
                newBoard.board[7][4]='.';
                newBoard.board[7][7]='.';
                newBoard.whiteKingMoved=true;
                newBoard.whiteRookRightMoved=true;
                possiblemoves.push_back(newBoard);
            }
            if(!whiteKingMoved&&!whiteRookLeftMoved&&board[7][1]=='.'&&board[7][2]=='.'&&board[7][3]=='.'){
                ChessBoard newBoard=*this;
                newBoard.board[7][2]='k';
                newBoard.board[7][3]='r';
                newBoard.board[7][4]='.';
                newBoard.board[7][0]='.';
                newBoard.whiteKingMoved=true;
                newBoard.whiteRookRightMoved=true;
                possiblemoves.push_back(newBoard);
            }
        }
        else{
            if(!blackKingMoved&&!blackRookRightMoved&&board[0][5]=='.'&&board[0][6]=='.'){
                ChessBoard newBoard=*this;
                newBoard.board[0][6]='K';
                newBoard.board[0][5]='R';
                newBoard.board[0][4]='.';
                newBoard.board[0][7]='.';
                newBoard.blackKingMoved=true;
                newBoard.blackRookRightMoved=true;
                possiblemoves.push_back(newBoard);
            }
            if(!blackKingMoved&&!blackRookLeftMoved&&board[0][1]=='.'&&board[0][2]=='.'&&board[0][3]=='.'){
                ChessBoard newBoard=*this;
                newBoard.board[0][2]='K';
                newBoard.board[0][5]='R';
                newBoard.board[0][4]='.';
                newBoard.board[0][0]='.';
                newBoard.blackKingMoved=true;
                newBoard.blackRookRightMoved=true;
                possiblemoves.push_back(newBoard);
            }
        }
    }
    void generateLinearMoves(int row,int col,vector<ChessBoard>& possiblemoves,vector<pair <int,int> >directions){
        for(pair<int,int>d:directions){
            int newRow=row+d.first;
            int newCol=col+d.second;
            while(newRow>=0&&newRow<BOARD_SIZE&&newCol>=0&&newCol<BOARD_SIZE){
                if(board[newRow][newCol]=='.'){
                    ChessBoard newBoard=*this;
                    newBoard.board[newRow][newCol]=board[row][col];
                    if(board[row][col]=='r'||board[row][col]=='R'){
                        newBoard.updateRookMoved(board[row][col],row,col);
                    }
                    newBoard.board[row][col]='.';
                    possiblemoves.push_back(newBoard);
                }
                else{
                    if(isWhite(board[row][col])!=isWhite(board[newRow][newCol])) {
                        ChessBoard newBoard=*this;
                        newBoard.board[newRow][newCol]=board[row][col];
                        if(board[row][col]=='r'||board[row][col]=='R'){
                            newBoard.updateRookMoved(board[row][col],row,col);
                        }
                        newBoard.board[row][col]='.';
                        possiblemoves.push_back(newBoard);
                    }
                    break;
                }
                newRow+=d.first;
                newCol+=d.second;
            }
        }
    }
public:
    bool isWhiteTurn;
    bool whiteKingMoved,blackKingMoved;
    bool whiteRookLeftMoved,whiteRookRightMoved;
    bool blackRookLeftMoved,blackRookRightMoved;
    ChessBoard(){
        board.resize(BOARD_SIZE+1,vector< char >(BOARD_SIZE+1,' '));    //set the boundaries of the chessboard
        board[0][0]='R';     //rook
        board[0][1]='N';     //knight
        board[0][2]='B';     //bishop
        board[0][3]='Q';     //qween
        board[0][4]='K';     //king
        board[0][5]='B';
        board[0][6]='N';
        board[0][7]='R';
        board[7][0]='r';
        board[7][1]='n';
        board[7][2]='b';
        board[7][3]='q';
        board[7][4]='k';
        board[7][5]='b';
        board[7][6]='n';
        board[7][7]='r';
        for(int i=0;i<BOARD_SIZE;i++){
            board[1][i]='P';    //pawn
            board[6][i]='p';
        }
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(board[i][j]==' '){
                    board[i][j]='.';     //'.' represents empty
                }
            }
        }
        isWhiteTurn=true;
        whiteKingMoved=blackKingMoved=false;
        whiteRookLeftMoved=whiteRookRightMoved=false;
        blackRookLeftMoved=blackRookRightMoved=false;
    }
    void initBoard(){
        board[0][0]='R';     //rook
        board[0][1]='N';     //knight
        board[0][2]='B';     //bishop
        board[0][3]='Q';     //queen
        board[0][4]='K';     //king
        board[0][5]='B';
        board[0][6]='N';
        board[0][7]='R';
        board[7][0]='r';
        board[7][1]='n';
        board[7][2]='b';
        board[7][3]='q';
        board[7][4]='k';
        board[7][5]='b';
        board[7][6]='n';
        board[7][7]='r';
        for(int i=0;i<BOARD_SIZE;i++){
            board[1][i]='P';    //pawn
            board[6][i]='p';
        }
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(board[i][j]==' '){
                    board[i][j]='.';     //'.' represents empty
                }
            }
        }
    }
    void displayBoard(){
        cout<<"  a b c d e f g h"<<endl;
        for(int i=0;i<BOARD_SIZE;i++){
            cout<<8-i<<" ";
            for(int j=0;j<BOARD_SIZE;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"--------------------------------------------------------\n";
    }
    char getChar(int row, int column){
        return board[row][column];
    }
    bool isWhite(char p){
        return (p>='a'&&p<='z');
    }
    void updateKingMoved(char king){
        if(king=='k')whiteKingMoved=true;
        if(king=='K')blackKingMoved=true;
    }
    void updateRookMoved(char rook,int row,int col){
        if(rook=='r'&&row==7&&col==0)whiteRookLeftMoved=true;
        if(rook=='r'&&row==7&&col==7)whiteRookRightMoved=true;
        if(rook=='R'&&row==0&&col==0)blackRookLeftMoved=true;
        if(rook=='R'&&row==0&&col==7)blackRookRightMoved=true;
    }
    void findPiece(int &row,int &col,char p){
        bool f=0;
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(getChar(i,j)==p){
                    row=i;
                    col=j;
                    f=1;
                    break;
                }
            }
            if(f) break;
        }
    }
    bool pathClear(int row,int col,int r,int c){    //Determine whether the middle grid is empty when a chess piece is to be moved to another position
        int rowStep, colStep;                       //row col represents the initial position, r c represents the final
        if (row< r) rowStep=1;                      //rowStep, colStep is to judge whether to check in the positive or negative direction
        else if (row> r) rowStep=-1;
        else rowStep=0;
        if (col< c) colStep=1;
        else if (col > c) colStep=-1;
        else colStep=0;
        int Row = row+ rowStep;      //The initial position of the chess piece won't be checked, start from the next one
        int Col = col + colStep;
        while (Row != r || Col != c) {
            if (getChar(Row,Col)!='.') {
                return false;
            }
            Row += rowStep;
            Col += colStep;
        }
        return true;
    }
    bool move(int row, int col, int r, int c){     //the function to see whether the move is legal
        if(getChar(row,col)=='.'){
            return false;
        }
        else if(islower(getChar(row,col))){        //we can't move one piece to our another piece
            if(islower(getChar(r,c))){
                return false;
            }
        }
        else{
            if(isupper(getChar(r,c))){
                return false;
            }
        }
        if(getChar(row,col)=='k'||getChar(row,col)=='K'){    //check if the king's move is legal
            if(abs(row-r)<=1&&abs(col-c)<=1&&!(r==row&&c==col)){
                return true;
            }
        }
        else if(getChar(row,col)=='q'||getChar(row,col)=='Q'){    //check if the qween's move is legal
            if(r==row&&c==col){
                return false;
            }
            else if((r==row||c==col||abs(r-row)==abs(c-col))&&pathClear(row,col,r,c)){
                return true;
            }
            else {
                return false;
            }
        }
        else if(getChar(row,col)=='b'||getChar(row,col)=='B'){    //check if the bishop's move is legal
            if(r==row&&c==col){
                return false;
            }
            else if(abs(r-row)==abs(c-col)&&pathClear(row,col,r,c)){
                return true;
            }
            else {
                return false;
            }
        }
        else if(getChar(row,col)=='r'||getChar(row,col)=='R'){    //check if the rook's move is legal
            if(r==row&&c==col){
                return false;
            }
            else if((r==row||c==col)&&pathClear(row,col,r,c)){
                return true;
            }
            else {
                return false;
            }
        }
        else if(getChar(row,col)=='n'||getChar(row,col)=='N'){    //check if the knight's move is legal
            if(r==row&&c==col){
                return false;
            }
            else if((abs(r-row)==2&&abs(c-col)==1)||(abs(r-row)==1&&abs(c-col)==2)){
                return true;
            }
            else {
                return false;
            }
        }
        else if(getChar(row,col)=='P'){    //check if the black pawn's move is legal
            if(r-row==1&&abs(c-col)==1){
                if(islower(getChar(r,c))){
                    return true;
                }
            }
            if(row==1){
                if(c==col&&pathClear(row,col,r,c)&&r-row==1){
                    if(getChar(r,c)=='.'){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else if(c==col&&pathClear(row,col,r,c)&&r-row==2){
                    if(getChar(r,c)=='.'&&getChar(r-1,c)=='.'){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                if(c==col&&r-row==1&&getChar(r,c)=='.'){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else if(getChar(row,col)=='p'){    //check if the white pawn's move is legal
            if(r-row==-1&&abs(c-col)==1){
                if(isupper(getChar(r,c))){
                    return true;
                }
            }
            if(row==6){
                if(c==col&&pathClear(row,col,r,c)&&r-row==-1){
                    if(getChar(r,c)=='.'){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else if(c==col&&pathClear(row,col,r,c)&&r-row==-2){
                    if(getChar(r,c)=='.'&&getChar(r+1,c)=='.'){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                if(c==col&&r-row==-1&&getChar(r,c)=='.'){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else{
            return false;
        }
        return false;
    }
    bool pawnTurn(int r,int c){     //to see whether the pawn can turn into other pieces
        if(getChar(r,c)=='P'&&r==7){
            return true;
        }
        else if(getChar(r,c)=='p'&&r==0){
            return true;
        }
        else{
            return false;
        }
    }
    bool whiteCheck(){     //whether white is checked
        int krow=-1;        //the position of white's king
        int kcol=-1;
        findPiece(krow,kcol,'k');
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(isupper(getChar(i,j))&&move(i,j,krow,kcol)){
                    return true;
                }
            }
        }
        return false;
    }
    bool blackCheck(){     //whether black is checked
        int krow=-1;
        int kcol=-1;
        findPiece(krow,kcol,'K');
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(islower(getChar(i,j))&&move(i,j,krow,kcol)){
                    return true;
                }
            }
        }
        return false;
    }
    bool moveCausesCheck(int row, int col, int r, int c, char king){
        char piece=board[row][col];
        char piece2=board[r][c];
        board[row][col]='.';
        board[r][c]=piece;
        if(king=='k'){
            bool causesCheck=whiteCheck();
            board[row][col]=piece;
            board[r][c]=piece2;
            return causesCheck;
        }
        else if(king=='K'){
            bool causesCheck=blackCheck();
            board[row][col]=piece;
            board[r][c]=piece2;
            return causesCheck;
        }
        return false;
    }
    bool castle(int row, int col, int r, int c, bool king, bool rook1, bool rook2){
        if(getChar(row,col)=='k'){
            if(c-col==2&&!king&&r==row&&pathClear(row,col,r,c)&&!whiteCheck()&&!moveCausesCheck(row,col,r,c-1,'k')&&!rook2){
                return true;
            }
            else if(c-col==-2&&!king&&r==row&&pathClear(row,col,r,c)&&getChar(r,c-1)=='.'&&!whiteCheck()&&!moveCausesCheck(row,col,r,c+1,'k')&&!rook1){
                return true;
            }
            else{
                return false;
            }
        }
        else if(getChar(row,col)=='K'){
            if(c-col==2&&!king&&r==row&&pathClear(row,col,r,c)&&!blackCheck()&&!moveCausesCheck(row,col,r,c-1,'K')&&!rook2){
                return true;
            }
            else if(c-col==-2&&!king&&r==row&&pathClear(row,col,r,c)&&getChar(r,c-1)=='.'&&!blackCheck()&&!moveCausesCheck(row,col,r,c+1,'K')&&!rook1){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
    bool enPassant(int row, int col, int r, int c, bool pawn){
        if(!pawn){
            return false;
        }
        else{
            if(getChar(row,col)=='p'&&getChar(r,c)=='.'&&getChar(row,c)=='P'&&r-row==-1&&abs(c-col)==1){
                return true;
            }
            else if(getChar(row,col)=='P'&&getChar(r,c)=='.'&&getChar(row,c)=='p'&&r-row==1&&abs(c-col)==1){
                return true;
            }
            else{
                return false;
            }
        }
    }
    bool checkmate(char king){     //checkmate
        for (int i=0; i<BOARD_SIZE;i++) {
            for (int j=0;j<BOARD_SIZE;j++) {
                if (getChar(i, j) == king){
                    for (int r=0;r<BOARD_SIZE;r++) {
                        for (int c=0;c<BOARD_SIZE;c++) {
                            char piece=board[r][c];
                            if (move(i, j, r, c)&&!moveCausesCheck(i, j, r, c, king)) {
                                if(king=='k'&&!whiteCheck()){
                                    board[r][c]='k';
                                    board[i][j]='.';
                                    if(!whiteCheck()){
                                        board[r][c]=piece;
                                        board[i][j]='k';
                                        return false;
                                    }
                                    else{
                                        board[r][c]=piece;
                                        board[i][j]='k';
                                    }
                                }
                                else if(king=='K'&&!blackCheck()){
                                    board[r][c]='K';
                                    board[i][j]='.';
                                    if(!blackCheck()){
                                        board[r][c]=piece;
                                        board[i][j]='K';
                                        return false;
                                    }
                                    else{
                                        board[r][c]=piece;
                                        board[i][j]='K';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if((islower(getChar(i,j))&&king=='k')||(isupper(getChar(i,j))&&king=='K')){
                    for(int r=0;r<BOARD_SIZE;r++){
                        for(int c=0;c<BOARD_SIZE;c++){;
                            if(move(i,j,r,c)&&!moveCausesCheck(i,j,r,c,king)){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    bool stalemate(char king){     //stalemate
        int kingRow=-1;
        int kingCol=-1;
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if(getChar(i,j)==king){
                    kingRow=i;
                    kingCol=j;
                }
            }
        }
        for (int dr=-1; dr<=1;dr++) {
            for (int dc=-1; dc<=1;dc++) {
                int newRow=kingRow + dr;
                int newCol=kingCol + dc;
                if (newRow>=0&&newRow<BOARD_SIZE&&newCol>=0&&newCol<BOARD_SIZE) {
                    char piece=board[newRow][newCol];
                    if (move(kingRow, kingCol, newRow, newCol)) {
                        if(king=='k'&&!whiteCheck()){
                            board[newRow][newCol]='k';
                            board[kingRow][kingCol]='.';
                            if(!whiteCheck()){
                                board[newRow][newCol]=piece;
                                board[kingRow][kingCol]='k';
                                return false;
                            }
                            else{
                                board[newRow][newCol]=piece;
                                board[kingRow][kingCol]='k';
                            }
                        }
                        else if(king=='K'&&!blackCheck()){
                            board[newRow][newCol]='K';
                            board[kingRow][kingCol]='.';
                            if(!blackCheck()){
                                board[newRow][newCol]=piece;
                                board[kingRow][kingCol]='K';
                                return false;
                            }
                            else{
                                board[newRow][newCol]=piece;
                                board[kingRow][kingCol]='K';
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                if((islower(getChar(i,j))&&king=='k')||(isupper(getChar(i,j))&&king=='K')){
                    for(int r=0;r<BOARD_SIZE;r++){
                        for(int c=0;c<BOARD_SIZE;c++){
                            if(move(i,j,r,c)&&!moveCausesCheck(i,j,r,c,king)){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    void whitemove(string p1,bool &wt ,bool &rm1,bool &rm2,bool &wkm, bool &pm2s,bool &e){
        char piece,erow,ecol;     //s represents start, e represents end
        cout<<p1<<"'s turn.\nEnter the chess piece you want to move and the position of the place you want to move to (ex:pd4) : ";
        int r,c,rr,cc;
        bool l=false;
        while(!l){
            bool ll=true;
            cin>>piece;
            if(piece=='p'||piece=='P') piece='p';
            else if(piece=='k'||piece=='K') piece='k';
            else if(piece=='q'||piece=='Q') piece='q';
            else if(piece=='n'||piece=='N') piece='n';
            else if(piece=='r'||piece=='R') piece='r';
            else if(piece=='b'||piece=='B') piece='b';
            else {
                cout<<"Invalid input, please enter the pieces that are in the board:";
                ll=false;
            }
            cin>>ecol>>erow;
            cc=ecol-'a';
            rr=BOARD_SIZE-(erow-'0');
            if(cc<0||cc>7||rr<0||rr>7){
                cout<<"Invalid input, please enter the position of the place you want to move to again:";
                ll=false;
            }
            if(ll) l=true;
        }
        bool moved=false;
        for(int i=0;i<BOARD_SIZE;i++){
            if(moved){
                break;
            }
            for(int j=0;j<BOARD_SIZE;j++){
                if(moved){
                    break;
                }
                if(getChar(i,j)==piece){
                    r=i;
                    c=j;
                }
                else{
                    continue;
                }
                if(move(r,c,rr,cc)||castle(r,c,rr,cc,wkm,rm1,rm2)||enPassant(r,c,rr,cc,pm2s)){
                    if(!moveCausesCheck(r,c,rr,cc,'k')){
                        char piece=getChar(r,c);
                        bool m=false;
                        if(move(r,c,rr,cc)){
                            board[rr][cc]=piece;
                            board[r][c]='.';
                            m=true;
                        }
                        if(piece=='r'){
                            if(c==0) rm1=true;
                            else rm2=true;
                        }
                        if(piece=='k'){
                            if(castle(r,c,rr,cc,wkm,rm1,rm2)){
                                if(cc-c==2){
                                    board[7][7]='.';
                                    board[7][5]='r';
                                    board[7][6]='k';
                                    board[7][4]='.';
                                }
                                else{
                                    board[7][0]='.';
                                    board[7][3]='r';
                                    board[7][2]='k';
                                    board[7][4]='.';
                                }
                            }
                            wkm=true;
                        }
                        if(piece=='p'){
                            if(!move(r,c,rr,cc)&&!castle(r,c,rr,cc,wkm,rm1,rm2)&&!m){
                                board[rr][cc]='p';
                                board[r][c]='.';
                                board[r][cc]='.';
                            }
                            if(rr-r==-2){
                                pm2s=true;
                            }
                            else{
                                pm2s=false;
                            }
                        }
                        if(pawnTurn(rr,cc)){
                            char turn;
                            cout<<"Which type of chess piece do you want to transform into (q/b/r/n)"<<endl;
                            cin>>turn;
                            while(turn!='q'&&turn!='b'&&turn!='r'&&turn!='n'){
                                char t;
                                cout<<"Invalid input, please enter the type of chess piece you want to transform into again (q/b/r/n)"<<endl;
                                cin>>t;
                                turn=t;
                            }
                            board[rr][cc]=turn;
                        }
                        displayBoard();
                        if(blackCheck()){
                            if(checkmate('K')){
                                cout<<"Checkmate!\n"<<p1<<" Wins!"<<endl;
                                moved=true;
                                e=true;
                                break;
                            }
                            else{
                                cout<<"Check!"<<endl;
                            }
                        }
                        else if(stalemate('K')){
                            cout<<"Stalemate!\nDraw!"<<endl;
                            moved=true;
                            e=true;
                            break;
                        }
                        wt=false;
                        moved=true;
                    }
                    else{
                        cout<<"The move is illegal, your king will be checked, please re-enter."<<endl;
                    }
                }
            }
        }
        if(!moved){
            cout<<"The move is illegal, please re-enter."<<endl;
        }
    }
    void blackmove(string p2,bool &wt ,bool &rm1,bool &rm2,bool &bkm, bool &pm2s,bool &e){
        char piece,erow,ecol;
        cout<<p2<<"'s turn.\nEnter the chess piece you want to move and the position of the place you want to move to (ex:pd4) : ";
        int r,c,rr,cc;
        bool l=false;
        while(!l){
            bool ll=true;
            cin>>piece;
            if(piece=='p'||piece=='P') piece='P';
            else if(piece=='k'||piece=='K') piece='K';
            else if(piece=='q'||piece=='Q') piece='Q';
            else if(piece=='n'||piece=='N') piece='N';
            else if(piece=='r'||piece=='R') piece='R';
            else if(piece=='b'||piece=='B') piece='B';
            else {
                cout<<"Invalid input, please enter the pieces that are in the board:";
                ll=false;
            }
            cin>>ecol>>erow;
            cc=ecol-'a';
            rr=BOARD_SIZE-(erow-'0');
            if(cc<0||cc>7||rr<0||rr>7){
                cout<<"Invalid input, please enter the position of the place you want to move to again:";
                ll=false;
            }
            if(ll) l=true;
        }
        bool moved=false;
        for(int i=0;i<BOARD_SIZE;i++){
            if(moved){
                break;
            }
            for(int j=0;j<BOARD_SIZE;j++){
                if(moved){
                    break;
                }
                if(getChar(i,j)==piece){
                    r=i;
                    c=j;
                }
                else{
                    continue;
                }
                if(move(r,c,rr,cc)||castle(r,c,rr,cc,bkm,rm1,rm2)||enPassant(r,c,rr,cc,pm2s)){
                    if(!moveCausesCheck(r,c,rr,cc,'K')){
                        char piece=getChar(r,c);
                        bool m=false;
                        if(move(r,c,rr,cc)){
                            board[rr][cc]=piece;
                            board[r][c]='.';
                            m=true;
                        }
                        if(piece=='R'){
                            if(c==0) rm1=true;
                            else rm2=true;
                        }
                        if(piece=='K'){
                            if(castle(r,c,rr,cc,bkm,rm1,rm2)){
                                if(cc-c==2){
                                    board[0][7]='.';
                                    board[0][5]='R';
                                    board[0][6]='K';
                                    board[0][4]='.';
                                }
                                else{
                                    board[0][0]='.';
                                    board[0][3]='R';
                                    board[0][2]='K';
                                    board[0][4]='.';
                                }
                            }
                            bkm=true;
                        }
                        if(piece=='P'){
                            if(!move(r,c,rr,cc)&&!castle(r,c,rr,cc,bkm,rm1,rm2)&&!m){
                                board[rr][cc]='P';
                                board[r][c]='.';
                                board[r][cc]='.';
                            }
                            if(rr-r==2){
                                pm2s=true;
                            }
                            else{
                                pm2s=false;
                            }
                        }
                        if(pawnTurn(rr,cc)){
                            char turn;
                            cout<<"Which type of chess piece do you want to transform into (Q/B/R/N)"<<endl;
                            cin>>turn;
                            while(turn!='Q'&&turn!='B'&&turn!='R'&&turn!='N'){
                                char t;
                                cout<<"Invalid input, please enter the type of chess piece you want to transform into again (Q/B/R/N)"<<endl;
                                cin>>t;
                                turn=t;
                            }
                            board[rr][cc]=turn;
                        }
                        displayBoard();
                        if(whiteCheck()){
                            if(checkmate('k')){
                                cout<<"Checkmate!\n"<<p2<<" Wins!"<<endl;
                                moved=true;
                                e=true;
                                break;
                            }
                            else{
                                cout<<"Check!"<<endl;
                            }
                        }
                        else if(stalemate('k')){
                            cout<<"Stalemate!\nDraw!"<<endl;
                            moved=true;
                            e=true;
                            break;
                        }
                        wt=true;
                        moved=true;
                    }
                    else{
                        cout<<"The move is illegal, your king will be checked, please re-enter."<<endl;
                    }
                }
            }
        }
        if(!moved){
            cout<<"The move is illegal, please re-enter."<<endl;
        }
    }
    vector<ChessBoard>getPossibleMoves(bool MaxP){
        vector<ChessBoard>possiblemoves;
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                char piece=board[i][j];
                if((MaxP&&isWhite(piece))||(!MaxP&&!isWhite(piece))){
                    switch(piece){
                        case 'P': case 'p':
                            generatePawnmoves(i,j,possiblemoves);
                            break;
                        case 'n': case 'N':
                            generateKnightmoves(i,j,possiblemoves);
                            break;
                        case 'r': case 'R':
                            generateRookmoves(i,j,possiblemoves);
                            break;
                        case 'B': case 'b':
                            generateBishopmoves(i,j,possiblemoves);
                            break;
                        case 'Q': case 'q':
                            generateQueenmoves(i,j,possiblemoves);
                            break;
                        case 'K': case 'k':
                            generateKingmoves(i,j,possiblemoves);
                            generateCastlingmoves(i,j,possiblemoves);
                            break;
                    }
                }
            }
        }
        return possiblemoves;
    }
    int evaluate(bool maxP){
        if(checkmate('k'))return(maxP? 99999999:-99999999);
        if(checkmate('K'))return(maxP? -99999999:99999999);
        if(stalemate('k')||stalemate('K'))return 0;
        unordered_map<char,int>pieceValues={
            {'p', 100},  {'P', -100},
            {'n', 320},  {'N', -320},
            {'b', 330},  {'B', -330},
            {'r', 500},  {'R', -500},
            {'q', 9000},  {'Q', -9000},
            {'k', 999999999}, {'K', -999999999}
        };
        int pawnTable[8][8]={
            {  0,   0,   0,   0,   0,   0,   0,   0},
            { 50,  50,  50,  50,  50,  50,  50,  50},
            { 10,  10,  20,  30,  30,  20,  10,  10},
            {  5,   5,  10,  25,  25,  10,   5,   5},
            {  0,   0,   0,  20,  20,   0,   0,   0},
            {  5,  -5, -10,   0,   0, -10,  -5,   5},
            {  5,  10,  10, -20, -20,  10,  10,   5},
            {  0,   0,   0,   0,   0,   0,   0,   0}
        };
        int knightTable[8][8]={
            {-50, -40, -30, -30, -30, -30, -40, -50},
            {-40, -20,   0,   0,   0,   0, -20, -40},
            {-30,   0,  10,  15,  15,  10,   0, -30},
            {-30,   5,  15,  20,  20,  15,   5, -30},
            {-30,   0,  15,  20,  20,  15,   0, -30},
            {-30,   5,  10,  15,  15,  10,   5, -30},
            {-40, -20,   0,   5,   5,   0, -20, -40},
            {-50, -40, -30, -30, -30, -30, -40, -50}
        };
        int bishopTable[8][8]={
            {-20, -10, -10, -10, -10, -10, -10, -20},
            {-10,   5,   0,   0,   0,   0,   5, -10},
            {-10,  10,  10,  10,  10,  10,  10, -10},
            {-10,   0,  10,  10,  10,  10,   0, -10},
            {-10,   5,   5,  10,  10,   5,   5, -10},
            {-10,   0,   5,  10,  10,   5,   0, -10},
            {-10,   0,   0,   0,   0,   0,   0, -10},
            {-20, -10, -10, -10, -10, -10, -10, -20}
        };
        int rookTable[8][8]={
            {  0,   0,   0,   5,   5,   0,   0,   0},
            { -5,   0,   0,   0,   0,   0,   0,  -5},
            { -5,   0,   0,   0,   0,   0,   0,  -5},
            { -5,   0,   0,   0,   0,   0,   0,  -5},
            { -5,   0,   0,   0,   0,   0,   0,  -5},
            { -5,   0,   0,   0,   0,   0,   0,  -5},
            {  5,  10,  10,  10,  10,  10,  10,   5},
            {  0,   0,   0,   0,   0,   0,   0,   0}
        };
        int queenTable[8][8]={
            {-20, -10, -10,  -5,  -5, -10, -10, -20},
            {-10,   0,   0,   0,   0,   0,   0, -10},
            {-10,   0,   5,   5,   5,   5,   0, -10},
            { -5,   0,   5,   5,   5,   5,   0,  -5},
            {  0,   0,   5,   5,   5,   5,   0,  -5},
            {-10,   5,   5,   5,   5,   5,   0, -10},
            {-10,   0,   5,   0,   0,   0,   0, -10},
            {-20, -10, -10,  -5,  -5, -10, -10, -20}
        };
        int kingTable[8][8]={
            {-30, -40, -40, -50, -50, -40, -40, -30},
            {-30, -40, -40, -50, -50, -40, -40, -30},
            {-30, -40, -40, -50, -50, -40, -40, -30},
            {-30, -40, -40, -50, -50, -40, -40, -30},
            {-20, -30, -30, -40, -40, -30, -30, -20},
            {-10, -20, -20, -20, -20, -20, -20, -10},
            { 20,  20,   0,   0,   0,   0,  20,  20},
            { 20,  30,  10,   0,   0,  10,  30,  20}
        };
        int score=0;
        vector< pair<int,int> >center={{3,3},{3,4},{4,3},{4,4}};
        int centercontrol=20;
        int krow=-1;
        int kcol=-1;
        int Krow=-1;
        int Kcol=-1;
        bool rconnect=false;
        bool Rconnect=false;
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                char piece=getChar(i,j);
                if(piece=='.')continue;
                int piecescore=pieceValues[piece];
                int posscore;
                if(piece=='p')posscore=pawnTable[i][j];
                else if(piece=='P')posscore=pawnTable[8-i][j];
                else if(piece=='n'||piece=='N')posscore=knightTable[i][j];
                else if(piece=='b')posscore=bishopTable[i][j];
                else if(piece=='B')posscore=bishopTable[8-i][j];
                else if(piece=='r')posscore=rookTable[i][j];
                else if(piece=='R')posscore=rookTable[8-i][j];
                else if(piece=='q')posscore=queenTable[i][j];
                else if(piece=='Q')posscore=queenTable[i][8-j];
                else if(piece=='k')posscore=kingTable[i][j];
                else posscore=kingTable[8-i][j];
                for(pair<int,int>c:center){
                    if(i==c.first&&j==c.second)posscore+=centercontrol;
                }
                vector<ChessBoard>possiblemoves;
                possiblemoves=getPossibleMoves(true);
                int mob=possiblemoves.size()*5;
                if(piece=='k'){
                    krow=i;
                    kcol=j;
                }
                if(piece=='K'){
                    Krow=i;
                    Kcol=j;
                }
                if(piece=='r'&&!rconnect){
                    for(int k=j+1;k<BOARD_SIZE;k++){
                        if(board[i][k]=='r'){
                            rconnect=true;
                            break;
                        }
                        if(board[i][k]!='.')break;
                    }
                }
                if(piece=='R'&&!Rconnect){
                    for(int k=j+1;k<BOARD_SIZE;k++){
                        if(board[i][k]=='R'){
                            Rconnect=true;
                            break;
                        }
                        if(board[i][k]!='.')break;
                    }
                }
                if(isWhite(piece)){
                    score+=piecescore+posscore+mob;
                }
                else{
                    score-=piecescore+posscore+mob;
                }
            }
        }
        vector< pair<int,int> >kingsurrounding={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
        for(pair<int,int>ks:kingsurrounding){
            int ksrow=krow+ks.first;
            int kscol=kcol+ks.second;
            int Ksrow=Krow+ks.first;
            int Kscol=Kcol+ks.second;
            if(ksrow>=0&&ksrow<=8&&kscol>=0&&kscol<=8&&isWhite(board[ksrow][kscol]))score+=30;
            if(Ksrow>=0&&Ksrow<=8&&Kscol>=0&&Kscol<=8&&!isWhite(board[Ksrow][Kscol])&&board[Ksrow][Kscol]!='.')score-=30;
        }
        if(rconnect)score+=50;
        if(Rconnect)score-=50;
        return maxP? score:-score;
    }
    int minimax(ChessBoard board,int depth,int alpha,int beta,bool maxP){
        if(depth==0){
            return board.evaluate(maxP);
        }
        if(maxP){
            int M=-2147483647;
            vector<ChessBoard>possiblemoves=board.getPossibleMoves(maxP);
            for(ChessBoard b:possiblemoves){
                int p=minimax(b,depth-1,alpha,beta,false);
                M=max(M,p);
                alpha=max(alpha,p);
                if(alpha>=beta)break;
            }
            return M;
        }
        else{
            int m=2147483647;
            vector<ChessBoard>possiblemoves=board.getPossibleMoves(maxP);
            for(ChessBoard b:possiblemoves){
                int p=minimax(b,depth-1,alpha,beta,true);
                m=min(m,p);
                beta=min(beta,m);
                if(alpha>=beta)break;
            }
            return m;
        }
    }
    ChessBoard bestmove(ChessBoard board,int depth){
        int M=-2147483647;
        ChessBoard bestb=board;
        vector<ChessBoard> possiblemoves=board.getPossibleMoves(true);
        for(ChessBoard b:possiblemoves){
            int p=minimax(b,depth-1,-2147483647,2147483647,false);
            if(p>M){
                M=p;
                bestb=b;
            }
        }
        return bestb;
    }
    void playGame(){
        initBoard();
        bool white_turn=true;     //whose turn
        bool whitekingmoved=false;
        bool blackkingmoved=false;
        bool rookmoved[4]={false};
        int player_num;
        bool End=false;
        string p1,p2;
        player_num=2;
        if(player_num==2){
            cout<<"Please enter the name of player 1(white):"<<endl;
            cin>>p1;
            cout<<"Please enter the name of player 2(black):"<<endl;
            cin>>p2;
            cout<<p1<<" will move first."<<endl;
            displayBoard();
            while(!End){
                bool pawnMovedTwoSteps;
                if(white_turn){
                    whitemove(p1,white_turn,rookmoved[0],rookmoved[1],whitekingmoved,pawnMovedTwoSteps,End);
                }
                else{
                    blackmove(p2,white_turn,rookmoved[2],rookmoved[3],blackkingmoved,pawnMovedTwoSteps,End);
                }
            }
            return;
        }
        else{
            cout<<"ERROR"<<endl;
            return;
        }
    }
    void playGame_ai(){
        initBoard();
        bool white_turn=true;     //whose turn
        bool whitekingmoved=false;
        bool blackkingmoved=false;
        bool rookmoved[4]={false};
        int player_num;
        bool End=false;
        int depth=4;
        string p1,p2;
        player_num=1;
        if(player_num==1){
            cout<<"Do you want to be at the white side or the black side(w/b):"<<endl;
            cin>>p1;
            cout<<"Please enter your name:"<<endl;
            cin>>p2;
            if(p1=="w")cout<<p2<<" will move first\n";
            else cout<<"AI will move first\n";
            displayBoard();
            while(!End){
                bool pawnMovedTwoSteps;
                if(p1=="w"){
                    if(white_turn){
                        whitemove(p2,white_turn,rookmoved[0],rookmoved[1],whitekingmoved,pawnMovedTwoSteps,End);
                    }
                    else{
                        ChessBoard newboard=bestmove(*this,depth);
                        *this=newboard;
                        newboard.displayBoard();
                        if(checkmate('k')||checkmate('K')||stalemate('k')||stalemate('K'))End=true;
                        white_turn=!white_turn;
                    }
                }
                else{
                    if(white_turn){
                        ChessBoard newboard=bestmove(*this,depth);
                        *this=newboard;
                        newboard.displayBoard();
                        if(checkmate('k')||checkmate('K')||stalemate('k')||stalemate('K'))End=true;
                        white_turn=!white_turn;
                    }
                    else{
                        blackmove(p2,white_turn,rookmoved[2],rookmoved[3],blackkingmoved,pawnMovedTwoSteps,End);
                    }
                }
            }
            return;
        }
        else{
            cout<<"ERROR"<<endl;
            return;
        }
    }
};

int main(){
    srand (time(0));
    ChessBoard chessboard;
    cout<<"Welcome to play chess. Please press \"Enter\" to play the game.";
    cin.get();
    cout<<"How many players are there(1/2):\n";
    int playernum;
    cin>>playernum;
    if(playernum==2)chessboard.playGame();
    else if(playernum==1) chessboard.playGame_ai();
    else cout<<"error\n";
    return 0;
}

