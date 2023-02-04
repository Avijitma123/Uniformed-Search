/*Avijit Dey
Roll: 2022SMCS006*/

/*===++++===Header file section====++++====*/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;



/*================Here I have defined a class Node to store the state information====================*/
class Node
{
    public:
    int n;
    int m ;
    int row;
    vector<vector<int>> vec;
    //Constructor
    Node(int n, int m)
    {
        this->n = n;
        this->m = m;
        //initialize the vector with 0
         for(int i = 0; i < n; i++)
        {
            vector<int> temp;
            for(int j = 0; j < m; j++)
            {
                temp.push_back(0);
            }
            vec.push_back(temp);
        }
        
        
    }
    void inCrementRow()
    {
        this->row++;
    }
      
    

    //Using this method to put the queen at the given position
    void putQueen(int x, int y)
    {
        this->vec[x][y] = 1;
    }
    //Display the state matrix
    void display()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cout<<this->vec[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
/*==================================================================================================*/
/*------------------Queue-----------------------*/
//Queue to store the successor of the states
queue<Node> q;
//Queue to store the goal states
queue<Node> gq;
//Queue to store the non-attacking states
queue<Node> nonAt;
/*-----------------------------------------*/

//Function to check if the queen can be placed at the given position
bool isSafe(Node node, int x, int y)
{
    //Checking the row
    for(int i = 0; i < node.m; i++)
    {
        if(node.vec[x][i] == 1)
        {
            return false;
        }
    }
    //Checking the column
    for(int i = 0; i < node.n; i++)
    {
        if(node.vec[i][y] == 1)
        {
            return false;
        }
    }
    //Checking the diagonal
    for(int i = 0; i < node.n; i++)
    {
        for(int j = 0; j < node.m; j++)
        {
            if((i + j) == (x + y) || (i - j) == (x - y))
            {
                if(node.vec[i][j] == 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//check if the node is a goal node
bool isGoal(Node node)
{
    int count = 0;
    for(int i = 0; i < node.n; i++)
    {
        for(int j = 0; j < node.m; j++)
        {
            if(node.vec[i][j] == 1)
            {
                count++;
            }
        }
    }
    if(count == node.n)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//check repeated state
bool isRepeated(Node node)
{
    queue<Node> temp = q;
    while(!temp.empty())
    {
        Node tempNode = temp.front();
        temp.pop();
       if(tempNode.vec == node.vec)
        {
            return true;
        }
    }
    return false;
}



//Find the successor of the states
void findSuccessor(Node node)
{
    
        int i = node.row;
        for(int j = 0; j < node.m; j++)
        {
            //if the value is 0 and it is safe
            if(node.vec[i][j] == 0 && isSafe(node, i, j))
            {
                Node temp = node;
                temp.putQueen(i, j);
                //check if the node is repeated
                if(!isRepeated(temp))
                {
                    temp.row = i + 1;
                    q.push(temp);
                    nonAt.push(temp);
                }
                
            }
        }
    
}


//Tree Search
void TreeSearch(int n, int m)
{
    //Create the root node
    Node node(n, m);
    node.row = 0;
    q.push(node);
    //while the queue is not empty
    while(!q.empty())
    {
        Node temp = q.front();
        q.pop();
        //check if the node is a goal node
        if(isGoal(temp))
        {
            
            gq.push(temp);
            
        }
        //if not a goal node, find the successor
        else
        {
            findSuccessor(temp);
        }
    }
}
//Main function
int main()
{
    int n, m;
    cout<<"Enter the chess board size in the format n x m"<<endl;
    cin>>n>>m;
    //Call the TreeSearch function. Using BFS I am finding the solutions
    TreeSearch(n, m);
    //Print the number of solutions
    cout<<"Number of solutions:"<<gq.size()<<endl;
    //Print the number of non-attacking solutions
    cout<<"Number of non-attacking solutions:"<<nonAt.size()<<endl;
    //Display the solutions
    int count = 0;
    // while(!gq.empty())
    // {
    //     count++;
    //     cout<<"Solution "<<count<<endl;
    //     Node temp = gq.front();
    //     gq.pop();
    //     temp.display();
        
    //     cout<<"===================="<<endl;
    // }
    // cout<<"===================="<<endl;
    while(!nonAt.empty())
    {
        Node temp = nonAt.front();
        nonAt.pop();
        temp.display();
        cout<<"===================="<<endl;
    }
    return 0;
}


