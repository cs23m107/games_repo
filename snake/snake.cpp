
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#include <iostream>
#include <unistd.h>   
#include <termios.h> 
#include <fcntl.h>      // For non-blocking input
char direction='W';    // initialising one direction to snake
int height,width;
pair<int,int> food;
vector<vector<char>> board;
deque<pair<int,int>> snake;
pair<int,int> generate_food(){
    vector<pair<int, int>> emptyCells;
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (board[i][j] == ' ') {
                emptyCells.push_back({i, j});  // counting spaces
            }
        }
    }
    if (emptyCells.empty()) {          // if there is no space to place food
        cout << "You Won!"<<endl;   
        exit(0);
    }
    int idx = rand() % emptyCells.size();
    pair<int, int> foodPos = emptyCells[idx];
    board[foodPos.first][foodPos.second] = '$';
    return foodPos;
}
void display_board() {
    cout << "\033[H\033[J"; // Clear screen using ANSI escape sequence
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (make_pair(i, j) == food) cout << "$"; // food
            else if (find(snake.begin(), snake.end(), make_pair(i, j)) != snake.end()) cout << "O"; // snake
            else cout << board[i][j]; // borders or empty spaces
        }
        cout << endl;
    }
    return ;
}

void snake_moves(){
        pair<int,int> head = snake.front();       //head of the snake block
        int i = head.first;
        int j = head.second;
        if(direction=='D'){
            j++;                                //moves Right
        }
        else if(direction=='A'){
            j--;                                // moves Left
        }
        else if(direction=='W'){
            i--;                                // moves Up
        }      
        else if(direction=='S'){
            i++;                               // moves Down
        } 
        if (i<=0 || j<=0 || i>=height-1 || j>=width-1){
        cout << "Game Over!:Wall Collision"<<endl;                                         // wall collision
        exit(0);
        }
        if (find(snake.begin(), snake.end(), make_pair(i, j)) != snake.end()){             // snake itself collision
            cout << "Game Over!:Self Collision"<<endl;
            exit(0);
        } 
        if(make_pair(i, j) == food){        // if eat food then make empty space and generate new food
            board[i][j]=' ';
            food = generate_food();
        }
        else{
            snake.pop_back();        // no food i.e space
        }
        snake.push_front({i, j});    // moving the snake in respective direction
    return ;
}
char getArrowKey() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable echo & buffering
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Make input non-blocking
    int old_flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);

    char ch = '\0';
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == '\033') {  // If first byte is ESC (arrow key sequence)
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': ch = 'W'; break;  // Up
                        case 'B': ch = 'S'; break;  // Down
                        case 'C': ch = 'D'; break;  // Right
                        case 'D': ch = 'A'; break;  // Left
                    }
                }
            }
        }
    }

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, old_flags); // Restore blocking mode

    return ch;
}
void game_looping() {
    while (true) {
        char input = getArrowKey();
        if (input != '\0' && input != direction) { 
            if ((input == 'W' && direction != 'S') ||
                (input == 'S' && direction != 'W') ||
                (input == 'A' && direction != 'D') ||
                (input == 'D' && direction != 'A')) {
                direction = input;
            }
        }
        snake_moves();         // no matter direction changed or not move the snake
        display_board();       // display board present 
        usleep(200000);        // adjust speed
    }
    return ;
}
void prepare_board(int height,int width){ //  start preparing the board
    board.resize(height,vector<char>(width));
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0||j==board[0].size()-1){
                board[i][j]='|';
            }
            else if(i==0||i==board.size()-1){
                board[i][j]='-';
            }
            else{
                board[i][j]=' ';
            }
        }
    }
return ;
}
int main(){
    cout<<"Game Start!"<<endl;
    cin>>height>>width;
    height = height+2;
    width = width+2;
    prepare_board(height,width);    //initialising the board
    snake.push_front({height/2,width/2});  //snake_head generation at random(middle) & head pushing into deque
    food = generate_food();  //food generation at random
    game_looping();           // it involves taking input direction and move the snake and display the board
    return 0;
}


