//
//  main.cpp
//  maze_bfs
//
//  Created by 范镇钧 on 2017/11/30.
//  Copyright © 2017年 范镇钧. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const uint8_t kMaxMazeX = 10;
const uint8_t kMaxMazeY = 10;
static int maze[10][10]=
{
    {1,1,1,1,1,1,1,1,1,1},
    {5,0,0,0,0,0,0,1,1,1},
    {1,0,1,1,1,1,0,1,1,1},
    {1,0,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,0,1,0,1,1,1,1,0,1},
    {1,0,0,0,1,1,1,1,0,8},
    {1,1,1,1,1,1,1,1,1,1}
};

int entrancex = 0;
int entrancey = 1;
int exitx = 9;
int exity = 8;

struct maze_node
{
    int x , y;
    int prex,prey;
    int visited;
};

const uint8_t kDirNum = 4;

int dir[kDirNum][2]={{0,1},{1,0},{0,-1},{-1,0}};

maze_node g_node[10][10];

bool maze_bfs(int entrancex , int entrancey , int exitx , int exity)
{
    queue<maze_node> maze_queue;
    
    g_node[entrancey][entrancex].x = entrancex;
    g_node[entrancey][entrancex].y = entrancey;
    g_node[entrancey][entrancex].visited = 1;
    maze_queue.push(g_node[entrancey][entrancex]);
    
    while(!maze_queue.empty())
    {
        maze_node node = maze_queue.front();
        maze_queue.pop();
        
        if(node.x== exitx && node.y == exity)
            break;
        
        for(uint8_t i = 0 ; i < kDirNum ; i++)
        {
            int x = node.x + dir[i][0];
            int y = node.y + dir[i][1];
            if(x < 0 || y < 0 || x >= kMaxMazeX || y >= kMaxMazeY || maze[y][x] == 1 || g_node[y][x].visited == 1)
                continue;
            
            g_node[y][x].x = x;
            g_node[y][x].y = y;
            g_node[y][x].prex = node.x;
            g_node[y][x].prey = node.y;
            g_node[y][x].visited = 1;
            
            maze_queue.push(g_node[y][x]);
            cout << "push:" << x << "  " << y << " "<< node.x << " "<< node.y << endl;
        }
    }
    
    int prex = exitx , prey = exity;
    stack<maze_node> stacknode;
    while(prex != entrancex || prey != entrancey)
    {
        cout << prex << " " << prey << endl;
        stacknode.push(g_node[prey][prex]);
        int tmpprex = g_node[prey][prex].prex;
        int tmpprey = g_node[prey][prex].prey;
        prex = tmpprex;
        prey = tmpprey;
    }
    
    cout << "path:" << endl;
    while(!stacknode.empty())
    {
        maze_node nodetmp = stacknode.top();
        stacknode.pop();
        cout <<"x:"<< nodetmp.x  << " y:" << nodetmp.y<< endl;
    }
    cout << endl;
    return true;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    maze_bfs(entrancex , entrancey , exitx , exity);
    return 0;
}
