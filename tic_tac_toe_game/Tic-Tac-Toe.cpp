#include<bits/stdc++.h>
using namespace std;
char board[3][3];
int count_player;
int count_AI;
void setup_game(){
    for(int i=0;i<3;i++){                                           //initialising board
        for(int j=0;j<3;j++){
            board[i][j]='_';
        }
    }
    return ;
}
void display_board(){                                                  // printing board
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){ 
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    return ;
}
int check_score(){                                                         // if AI won +10 and Player won -10
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1]!='_'){            //left_to_right diagonal 
        return (board[1][1]=='+')?10:-10;                 
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1]!='_'){           //right_to_left diagonal
        return (board[1][1]=='+')?10:-10;
    }
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][1]!='_'){              //row_wise checking
            return (board[i][0]=='+')?10:-10;  
        }
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[1][i]!='_'){              //col_wise checking
            return (board[0][i]=='+')?10:-10;  
        }
    }
    return 0;
}
bool moves_left(){
    for(int i=0;i<3;i++){                                                     // empty place present or not to put a coin
        for(int j=0;j<3;j++){
            if(board[i][j]=='_')
            return true;
        }
    }
    return false;
}
int minimax_algo(bool AI_turn){
    int score = check_score();
    if(score==10||score==-10)                                                         //if final someone won then return appropriately
    return score;
    if(moves_left()==0){                                                              // if no space i.e draw type no point further exploration
        return 0;
    }
    if(AI_turn){
        int best=-1e9;
        for(int i=0;i<3;i++){                                                         //exploring for AI winning bolck(i,j)
            for(int j=0;j<3;j++){
                if(board[i][j]=='_'){
                        board[i][j]='+';
                        best = max(best,minimax_algo(false));
                        board[i][j]='_'; 
                    }
            }
        }
        return best;
    }
    else{
        int best = 1e9;                                                              //exploring for player winning block and should exclude this(that is why it it -ve) inorder to achieve above 
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]=='_'){
                        board[i][j]='*';
                        best = min(best,minimax_algo(true));
                        board[i][j]='_'; 
                    }
            }
        }
        return best;
    }
    return 0;
}
void best_move_AI(){
    int max_val=-1e9;
    int best_i=-1,best_j=-1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]=='_'){
                board[i][j]='+';
                int curr_val =minimax_algo(false);
                board[i][j]='_';
            if(curr_val>max_val){
                best_i=i;                                            //find one of the block(i,j) such that AI will win
                best_j=j;
                max_val = curr_val;
            }
            }
        }
    }
    if(best_i!=-1 && best_j!=-1)
    board[best_i][best_j]='+';
    return ;
}

int main(){
    setup_game();
    display_board();
    cout<<"Welcome Tic-Tac-Toe Game Start!"<<endl;
    while(true){
        int row,col;
        cout<<"@player please pick block (i,j) to place coin"<<endl;
        while(true){
            cin>>row>>col;
            if(board[row][col]!='_' || row>=3 || col>=3){
                cout<<"Invalid Move"<<endl;
        }
        else{
        board[row][col]='*';
        break;
        }
        }
        display_board();
        count_player++;
        if(count_player>=3){
            if(check_score()==-10){
                display_board();
                cout<<"Player Won"<<endl;
                break;
            }
        }
        cout<<"now AI's turn please wait..."<<endl;
        best_move_AI();
        count_AI = count_AI + 1;
        if(count_AI>=3){
            if(check_score()==10){
                display_board();
                cout<<"AI Won"<<endl;
                break;
            }
        }
        display_board();
        if(moves_left()==0){
            cout<<"It's a Draw!"<<endl;
            break;
        }
    }
    return 0;
}