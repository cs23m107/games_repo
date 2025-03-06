#include<bits/stdc++.h>
using namespace std;
int board[4][4];
int is_2048;
int get_random(int x){
    return rand()%x;
}
void print_board(){
    for(int i =0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j]==0?cout<<"_ ":cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
void setup_game(){
       for(int i =0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j]=0;
        }
    }
    int twice=2;
    while(twice){
            int i = get_random(4);
            int j = get_random(4);
            if(board[i][j]==0){
            board[i][j]=2;
            twice--;
            }
        }
        print_board();
        cout<<"Game Start!"<<endl;
    return ;
}
bool check_empty(){
    int cnt=0;
        for(int i =0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]!=0)
                cnt++;
            }
        }
        if(cnt==16) return true;
        return false;
}
bool check_moves(int (&prev_board)[4][4]){
    for(int i =0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]!=prev_board[i][j])
                return true;
            }
        }
        return false;
}
bool generate_2or4(){
        while(true){
            int i = get_random(4);
            int j = get_random(4);
            if(board[i][j]==0){
            board[i][j]=(get_random(10)==0)?4:2;
            return true;
            }
        }
        return false;
}
void move_up(){
    for(int col=0;col<4;col++){
    int right_most=0;
    int left_move=right_most+1;
    int row = 0;
    while(left_move<4){
        if(board[right_most][col]==0){
            right_most++;
            left_move=right_most+1;
        }
        else if(board[left_move][col]==0){
            left_move++;
        }
        else if(board[right_most][col]==board[left_move][col]){
            board[row][col]=2*board[right_most][col];
            if(board[row][col]==2048){
                is_2048=1;
                return ;
            }
            right_most=left_move+1;
            left_move=right_most+1;
            row++;
        }
        else if(board[right_most][col]!=board[left_move][col]){
            board[row][col]=board[right_most][col];
            right_most=right_most+1;
            left_move=right_most+1;
            row++;
        }
    }
    while(row<4&&right_most<4){
        board[row][col]=board[right_most][col];
        row++;
        right_most++;
    }
    while(row<4){
        board[row][col]=0;
        row++;
    }
    }
    return ;
}
void move_down(){
    for(int col=0;col<4;col++){
    int right_most=3;
    int left_move=right_most-1;
    int row = 3;
    while(left_move>=0){
        if(board[right_most][col]==0){
            right_most--;
            left_move=right_most-1;
        }
        else if(board[left_move][col]==0){
            left_move--;
        }
        else if(board[right_most][col]==board[left_move][col]){
            board[row][col]=2*board[right_most][col];
            if(board[row][col]==2048){
                is_2048=1;
                return ;
            }
            right_most=left_move-1;
            left_move=right_most-1;
            row--;
        }
        else if(board[right_most][col]!=board[left_move][col]){
            board[row][col]=board[right_most][col];
            right_most=right_most-1;
            left_move=right_most-1;
            row--;
        }
    }
    while(row>=0&&right_most>=0){
        board[row][col]=board[right_most][col];
        row--;
        right_most--;
    }
    while(row>=0){
        board[row][col]=0;
        row--;
    }
    }
    return ;
}
void move_left(){
     for(int row=0;row<4;row++){
    int left_most=0;
    int right_move=left_most+1;
    int col = 0;
    while(right_move<4){
        if(board[row][left_most]==0){
            left_most++;
            right_move=left_most+1;
        }
        else if(board[row][right_move]==0){
            right_move++;
        }
        else if(board[row][left_most]==board[row][right_move]){
            board[row][col]=2*board[row][left_most];
            if(board[row][col]==2048){
                is_2048=1;
                return ;
            }
            left_most=right_move+1;
            right_move=left_most+1;
            col++;
        }
        else if(board[row][left_most]!=board[row][right_move]){
            board[row][col]=board[row][left_most];
            left_most=left_most+1;
            right_move=left_most+1;
            col++;
        }
    }
    while(col<4&&left_most<4){
        board[row][col]=board[row][left_most];
        col++;
        left_most++;
        
    }
    while(col<4){
        board[row][col]=0;
        col++;
    }
    }
    return ;
}
void move_right(){
    for(int row=0;row<4;row++){
    int right_most=3;
    int left_move=right_most-1;
    int col = 3;
    while(left_move>=0){
        if(board[row][right_most]==0){
            right_most--;
            left_move=right_most-1;
        }
        else if(board[row][left_move]==0){
            left_move--;
        }
        else if(board[row][right_most]==board[row][left_move]){
            board[row][col]=2*board[row][right_most];
            if(board[row][col]==2048){
                is_2048=1;
                return ;
            }
            right_most=left_move-1;
            left_move=right_most-1;
            col--;
        }
        else if(board[row][right_most]!=board[row][left_move]){
            board[row][col]=board[row][right_most];
            right_most=right_most-1;
            left_move=right_most-1;
            col--;
        }
    }
    while(col>=0&&right_most>=0){
        board[row][col]=board[row][right_most];
        col--;
        right_most--;
        
    }
    while(col>=0){
        board[row][col]=0;
        col--;
    }
    }
    return ;
}

int main(){
    srand(time(0));
    setup_game();
    bool possible_to_swipe=0;
    char swipe_side;
    while(!possible_to_swipe){
        int prev_board[4][4];
        memcpy(prev_board,board,sizeof(board));
        cout<<"Move to : U or D or L or R"<<endl;
        cin>>swipe_side;
        if(swipe_side=='U'){
               move_up();
        }
        else if(swipe_side=='D'){
               move_down();
        }
        else if(swipe_side=='L'){
               move_left();
        }
        else if(swipe_side=='R'){
               move_right();
        }
        else{
            cout<<"Invalid Move"<<endl;
            continue;
        }
        if(is_2048){
            print_board();
            cout<<"You Won!"<<endl;
            return 0;
        }
        possible_to_swipe=check_empty();
        if(possible_to_swipe) break;
        bool moved = check_moves(prev_board);
        if(moved){
            generate_2or4();
        }
        print_board();
        if(!moved){
            cout<<"No Tiles Moved"<<endl;
        }
    }
    cout<<"Game Over!"<<endl;
    return 0;
}