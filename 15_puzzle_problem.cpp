/* Avijit Dey , Roll: 2022SMCS006, IACS   */
/*I used graph search to solve 15-puzzle problem*/

/*==========Here I have defined header files============*/
#include<iostream>
#include<queue>
#include<vector>
#include<list>
using namespace std;
/*Here I hvae define a class Board to store the state information*/
class Board
{
    public:
    int n;
    //Matrix to store the state
     vector<vector<int>> vec;
    //Constructor
    Board(int n)
    {
        this->n = n;
        //initialize the vector with 0
         for(int i = 0; i < n; i++)
        {
            vector<int> temp;
            for(int j = 0; j < n; j++)
            {
                temp.push_back(0);
            }
            vec.push_back(temp);
        }
    }
    
    // //Define initial state
    // void initialState()
    // {
    //     //initialize matrix manually

    //     vec[0][0] = 2;
    //     vec[0][1] = 1;
    //     vec[0][2] = 3;
    //     vec[0][3] = 4;
    //     vec[1][0] = 5;
    //     vec[1][1] = 6;
    //     vec[1][2] = 7;
    //     vec[1][3] = 8;
    //     vec[2][0] = 9;
    //     vec[2][1] = 10;
    //     vec[2][2] = 11;
    //     vec[2][3] = 12;
    //     vec[3][0] = 13;
    //     vec[3][1] = 14;
    //     vec[3][2] = 15;
    //     vec[3][3] = 0;
    // }
   
    // void goalState()
    // {
    //     //initialize matrix manually
    //     vec[0][0] = 1;
    //     vec[0][1] = 2;
    //     vec[0][2] = 3;
    //     vec[0][3] = 4;
    //     vec[1][0] = 5;
    //     vec[1][1] = 6;
    //     vec[1][2] = 7;
    //     vec[1][3] = 8;
    //     vec[2][0] = 9;
    //     vec[2][1] = 10;
    //     vec[2][2] = 11;
    //     vec[2][3] = 12;
    //     vec[3][0] = 13;
    //     vec[3][1] = 14;
    //     vec[3][2] = 15;
    //     vec[3][3] = 0;
    // }

    /*=======================================================================*/
    //define a function to take input the initial state
     void initialState()
    {
        cout<<"Enter the initial state"<<endl;
        //row wise matrix input from user
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cin>>vec[i][j];
                
            }
            cout<<endl;
        }

        
       
    }
    //Define a function to take input of goal state
    void goalState()
    {
        cout<<"Enter the goal state"<<endl;
       //row wise matrix input from user
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cin>>vec[i][j];
                
            }
            cout<<endl;
        }
    }

    //Define a function to print the state
    void printState()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(vec[i][j] >9)
                    cout<<vec[i][j]<<" ";
                else
                    cout<<" "<<vec[i][j]<<" ";
            
            }
            cout<<endl;
        }
    }
    //Move the blank block up.
    void moveUp(int x, int y)
    {
        if(x>0)
        {
            int temp = vec[x-1][y];
            vec[x-1][y] = vec[x][y];
            vec[x][y] = temp;
           
        }
    }
    //Move the block down for a given position (x,y) if downer block is empty
    void moveDown(int x, int y)
    {
        if(x < n-1)
        {
            int temp = vec[x+1][y];
            vec[x+1][y] = vec[x][y];
            vec[x][y] = temp;
            
        }
       
        
    }
    //Move the block left for a given position (x,y) if left block is empty
    void moveLeft(int x, int y)
    {
        if(y > 0)
        {
            int temp = vec[x][y-1];
            vec[x][y-1] = vec[x][y];
            vec[x][y] = temp;
           
        }
        
         
    }
    //Move the block right for a given position (x,y) if right block is empty
    void moveRight(int x, int y)
    {
        if(y < n-1)
        {
            int temp = vec[x][y+1];
            vec[x][y+1] = vec[x][y];
            vec[x][y] = temp;
            
        }
       
    }
    //get the position of the blank block
    vector<int> getBlank()
    {
        int x,y;
        vector<int> temp;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(vec[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
            }
        }
        
        temp.push_back(x);
        temp.push_back(y);
        return temp;
    }
    ////operator overload to check similarity of two state
    bool operator==(const Board& b)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(this->vec[i][j] != b.vec[i][j])
                    return false;
            }
        }
        return true;
    }


};

// I used a queue to store the successor states
queue <Board> succ;
//I used a list to store the visited states
list <Board> visited;

//===========================================================
//Define a function to check if the state is already visited
bool checkVisited(Board board)
{
    for(list<Board>::iterator it = visited.begin(); it != visited.end(); it++)
    {
        if(*it == board)
            return true;
    }
    return false;
}
//copy the state of the board to another board
Board copyBoard(Board board, int n)
{
    Board temp(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            temp.vec[i][j] = board.vec[i][j];
        }
    }
    return temp;
}

//Define a function to check if the state is already in the successor list
bool inSucc(Board board)
{
    //check if the state is already in the successor queue
    queue<Board> temp = succ;
    while(!temp.empty())
    {
        if(temp.front() == board)
            return true;
        temp.pop();
    }
    return false;
    
}


//Define a function to generate the successors
void generateSuccessors(Board board,int n)
{
    vector<int> temp = board.getBlank();
    int x = temp[0];
    int y = temp[1];
    Board temp1 = copyBoard(board,n);
    Board temp2 = copyBoard(board,n);
    Board temp3 = copyBoard(board,n);
    Board temp4 = copyBoard(board,n);
    temp1.moveUp(x, y);
    if(!checkVisited(temp1) && !inSucc(temp1) )
    {
        succ.push(temp1);
        
    }
    
    temp2.moveDown(x, y);
    if(!checkVisited(temp2) && !inSucc(temp2))
    {
        succ.push(temp2);
        
    }
    
    temp3.moveLeft(x, y);
    if(!checkVisited(temp3)&& !inSucc(temp3) )
    {
        succ.push(temp3);
        
    }
    
    temp4.moveRight(x, y);
    if(!checkVisited(temp4)&& !inSucc(temp4))
    {
        succ.push(temp4);
        
    }
}
//Define a function to check goal state
bool checkGoal(Board board, Board f_state)
{
    for(int i = 0; i < board.n; i++)
    {
        for(int j = 0; j < board.n; j++)
        {
            if(board.vec[i][j] != f_state.vec[i][j])
                return false;
        }
    }
    return true;
}
//Define a function to find the distance current state from the goal state using Manhattan Distance
int findDistance(Board board, Board f_state)
{
    int distance = 0;
    for(int i = 0; i < board.n; i++)
    {
        for(int j = 0; j < board.n; j++)
        {
            if(board.vec[i][j] != f_state.vec[i][j])
            {
                int x = board.vec[i][j];
                for(int k = 0; k < board.n; k++)
                {
                    for(int l = 0; l < board.n; l++)
                    {
                        if(f_state.vec[k][l] == x)
                        {
                            distance += abs(i-k) + abs(j-l);
                        }
                    }
                }
            }
        }
    }
    return distance;
}
//Define a function to search the goal state
void Graph_search(int n)
{
 Board board(n);
 board.initialState();
 Board f_state(n);
 f_state.goalState();
 succ.push(board);
    while(!succ.empty())
    {
        Board temp = succ.front();
        succ.pop();
        if(checkGoal(temp, f_state))
        {
            cout<<"Goal State Found: "<<endl;
            temp.printState();
            return;
        }
        else{
              cout<<"Visited State: "<<endl;
              temp.printState();
              cout<<endl;
               generateSuccessors(temp,n);
              visited.push_back(temp);
             
        }
       
    }
}


//main
int main()
{
    //Take the board size as input
    int n;
    cout<<"Enter the board size: ";
    cin>>n;
    Graph_search(n);
    //Display the visited states
    // cout<<"Visited States: "<<endl;
    // for(list<Board>::iterator it = visited.begin(); it != visited.end(); it++)
    // {
    //     it->printState();
    //     cout<<endl;
    // }
    // Board board(4);
    // Board f_state(4);
    // f_state.goalState();
    // board.initialState();
    // generateSuccessors(board);
    // cout<<"Successors: "<<endl;
    // while(!succ.empty())
    // {
    //     Board temp = succ.front();
    //     succ.pop();
    //     int distance = findDistance(temp, f_state);
    //     cout<<"Distance: "<<distance<<endl;
    //     temp.printState();
    //     cout<<endl;
    // }
    // //print the visited states
    // cout<<"Visited States: "<<endl;
    // for(list<Board>::iterator it = visited.begin(); it != visited.end(); it++)
    // {
    //     it->printState();
    //     cout<<endl;
    // }
    

    
    
    return 0;
}