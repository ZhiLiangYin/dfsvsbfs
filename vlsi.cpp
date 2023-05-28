#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <list>
#include <utility>          
#include <queue>
#include <iomanip>        
#include <cmath>    

using namespace std;



struct nw {
	string name;
	int weight;
};
struct nn {
	int num;
	int weight;
};

struct HeapNode{
    int element, key;
    HeapNode():element(0),key(0){};
    HeapNode(int node, int key):element(node), key(key){};
};
vector <string> vname ;
vector < vector<string> > nname ;
vector < vector<string> > iname ;
vector < vector<nw> > iwname ;
const int Max_Distance = 100;

fstream first;
fstream last;




class Graph{
	private:
		int num_vertex ;
		vector< list<int> > List ;
		int *color, *discover, *predecessor, *finish ;// 0:白色, 1:灰色, 2:黑色
	public:
   		Graph():num_vertex(0){};          
    	Graph(int N):num_vertex(N){        
        	List.resize(num_vertex);
    	};
    void AddEdgeList(int from, int to){
    	List[from].push_back(to);
    	
	}
	void DFS(int Start){
    	color = new int[num_vertex];           // 配置記憶體位置
    	discover = new int[num_vertex];
    	finish = new int[num_vertex];
    	predecessor = new int[num_vertex];

    	int time = 0;                          // 初始化
    	for (int i = 0; i < num_vertex; i++) { 
        	color[i] = 0;
       		discover[i] = 0;
        	finish[i] = 0;
        	predecessor[i] = -1;
    	}

    	int i = Start;
    	for (int j = 0; j < num_vertex; j++) { // 檢查所有Graph中的vertex都要被搜尋到
        	if (color[i] == 0) {               // 若vertex不是白色, 則進行以該vertex作為起點之搜尋
            	DFSVisit(i, time);
        	}
        	i = j;                             // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    	}
	}
	
    void DFSVisit(int vertex, int &time){
    	color[vertex] = 1;     
		cout << " >> " << vname[vertex]  ;                    // 把vertex塗成灰色
    	discover[vertex] = ++time;                 // 更新vertex的discover時間
    	for ( list<int>::iterator itr = List[vertex].begin();   // for loop參數太長
              itr != List[vertex].end(); itr++) {                    // 分成兩段
        	if (color[*itr] == 0) {                // 若搜尋到白色的vertex
            	predecessor[*itr] = vertex;        // 更新其predecessor
            	DFSVisit(*itr, time);              // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
        	}
    	}
    	color[vertex] = 2;                         // 當vertex已經搜尋過所有與之相連的vertex後, 將其塗黑
    	finish[vertex] = ++time;                   // 並更新finish時間

	}
    
    
};


class Graph2{
	private:
		int num_vertex ;
		//vector< list<int> > List ;
		vector< vector<nn> > List;
    	//vector<int> predecessor, distance;
    	vector<bool> visited;
    	int *color, *distance, *predecessor, *finish ; // 0:白色, 1:灰色, 2:黑色
	public:
   		Graph2():num_vertex(0){};          
    	Graph2(int N):num_vertex(N){        
        	List.resize(num_vertex);
    	};
    	void AddEdgeList(int from, int to, int weight ){
    		nn c ;
    		c.num = to ;
    		c.weight = weight ;
    		List[from].push_back(c);
		}
		
		void BFS(int Start){

    		color = new int[num_vertex];
    		predecessor = new int[num_vertex];
    		distance = new int[num_vertex];

    		for (int i = 0; i < num_vertex; i++) {  // 初始化，如圖二(b)
        		color[i] = 0;                       // 0:白色;
        		predecessor[i] = -1;                // -1表示沒有predecessor
        		distance[i] = num_vertex+1;         // num_vertex個vertex, 
    		}                                       // 最長距離 distance = num_vertex -1條edge

    		queue<int> q;
    		int i = Start;

    		for (int j = 0; j < num_vertex; j++) {  // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
        		if (color[i] == 0) {	                // 第一次i會是起點vertex, 如圖二(c)
            		color[i] = 1;                   // 1:灰色
            		distance[i] = 0;                // 每一個connected component的起點之距離設成0
            		predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
            		q.push(i);
            		
            		while (!q.empty()) {
            			
                		int u = q.front();    
						    
					     // u 為新的搜尋起點
                		for (int v = 0 ; v < List[u].size() ; v++) {  
						    int itr = List[u][v].num ;
                    		if (color[itr] == 0) {                // 若被「找到」的vertex是白色
                        		color[itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        		distance[itr] = distance[u] + List[u][v].weight;  // 距離是predecessor之距離加一
                        		predecessor[itr] = u;             // 更新被「找到」的vertex的predecessor
                        		q.push(itr);                      // 把vertex推進queue
                    		}
                    		else if (color[itr] == 1) {                // 若被「找到」的vertex是白色
                        		color[itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        		int ddddd = distance[u] + List[u][v].weight;
								if(distance[itr] > ddddd){
                        			distance[itr] = ddddd;  // 距離是predecessor之距離加一
                        			predecessor[itr] = u; 									
								} 
            // 更新被「找到」的vertex的predecessor
                        		//q.push(itr);                      // 把vertex推進queue
                    		}
                    		
                    		
                		}
                		q.pop();        // 把u移出queue
                		color[u] = 2;   // 並且把u塗成黑色
            		}
        		}
        // 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
        // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
        		i = j;
        	}
        	
        	cout << "Single source shortest path algorithm (Dijkstra)\n" ;
        	for( int w = 0 ; w < vname.size() ; w++ ){
        		cout << "Vertex" << " (" << vname[w] << ") distancs = "<< distance[w] <<"\n" ;
        		
			}
    	}
    	

		

    
};
int main() {

  	string firstname;
  	
  	cout << "input a file :" ;
  	cin >> firstname;  		
  	
	  
	  
	int issic = 0 ;
  	
  	
	
    int mission = 0 ;
    cout << "input 1 to DFS,2 to Dijkstra\n" ;	
    cin >> mission;
  		
  	bool isc = false;

//  	fstream last;



	  	first.open(firstname.c_str(), ios::in);
  		while ( first.is_open() == false ){
  			cout << "Please input a file again : " ;
  			cin >> firstname;
  			cout << "input 1 to DFS,2 to Dijkstra\n" ;	
	        cin >> mission;		
  			first.open(firstname.c_str(), ios::in);
  			
		}

//////////////////////////////////////input/////////////////////////////////////////////////////////////////////////
        if(mission == 1){
        	
     		string temp;
  			getline( first,temp );     	
			  
        	while( !first.eof() ){

				getline( first,temp );
        		if ( temp == "ENDCIRCUIT" ) {
        			break ;
        			
				}				
				string tvn = "\0" ;
				for( int i = 9 ; temp[i] != ' ' && temp[i] != '\t' ; i++ ) tvn = tvn + temp[i] ;
				vname.push_back(tvn) ;
				
				getline( first,temp );
				string tnn = "\0" ;
				vector<string> tnns ;
				
				
				for( int i = 0 ; i < temp.size() ; i++ ) {
					
					if(temp[i] == ','){
						if(temp[i+1] == 'o'){
							int x = i ;
							while( temp[x-1] != ' ' )x-- ;
							tnn = tnn + temp[x] ;
							x++ ;
							while( temp[x] != '(' ){
								tnn = tnn + temp[x] ;
								x++;
							}
							tnns.push_back(tnn) ;
							
						}
						
					}
					tnn = "\0" ;
				}
				
				
				string tin = "\0" ;
				vector<string> tins ;
				for( int i = 0 ; i < temp.size() ; i++ ) {
					
					if(temp[i] == ','){
						if(temp[i+1] == 'i'){
							int x = i ;
							while( temp[x-1] != ' ' )x-- ;
							tin = tin + temp[x] ;
							x++ ;
							while( temp[x] != '(' ){
								tin = tin + temp[x] ;
								x++;
							}
							tins.push_back(tin) ;
							
						}
						
					}
					tin = "\0" ;
				}
				
				iname.push_back(tins) ;
				tins.clear() ;
				
				nname.push_back(tnns) ;
				tnns.clear() ;
				
			}
			/*
			    for( int f = 0 ; f < nname.size() ; f++ ) {
			    	cout << vname[f] <<"\n" ;
				    for( int g = 0 ; g < iname[f].size() ; g++ ) {
						cout << iname[f][g] << " " ;
					
					}
					cout << "\n" ;
				    for( int g = 0 ; g < nname[f].size() ; g++ ) {
						cout << nname[f][g] << " " ;
					
					}		
					cout << "\n" ;			
					
				}
			*/	
				
			Graph ggg(vname.size());
			
			
			for( int f = 0 ; f < vname.size() ; f++ ) {
			    for( int g = 0 ; g < iname[f].size() ; g++ ) {
			    	
			    	for( int h = 0 ; h < nname.size() ; h++ ) {
						
			    		for( int k = 0 ; k < nname[h].size() ; k++ ) {
			    			if ( nname[h][k] == iname[f][g] ){
			    				ggg.AddEdgeList(h,f) ;
			    				// cout << vname[f] << " " << nname[h][k] << "\n" ;
							}
			    			
			    		
						}
					}
			   
			    
				}
			    
			   			
			
			}
			
			/*
			
			for( int f = 0 ; f < vname.size() ; f++ ) {
			    for( int g = 0 ; g < nname[f].size() ; g++ ) {
			    	
			    	for( int h = f+1 ; h < iname.size() ; h++ ) {	
			    		for( int k = 0 ; k < iname[h].size() ; k++ ) {
			    			if ( iname[h][k] == nname[f][g] ){
			    				ggg.AddEdgeList(f,h) ;
							}
			    			
			    		
						}
					}
			   
			    
				}
			    
			   			
			
			}
			*/
			cout << "DFS algorithm (depth first search)\n" ;
			cout << "order:" ;
			ggg.DFS(0);
			cout << "\n" ;
			iname.clear() ;
			vname.clear() ;
			nname.clear() ;
			// g.AddEdgeList() ;
				
    		first.close();
        	
        	
        	
        	
		  	
		}
		else if(mission == 2){
     		string temp;
  			getline( first,temp );     	
			  
        	while( !first.eof() ){

				getline( first,temp );
        		if ( temp == "ENDCIRCUIT" ) {
        			break ;
        			
				}				
				string tvn = "\0" ;
				for( int i = 9 ; temp[i] != ' ' && temp[i] != '\t' ; i++ ) tvn = tvn + temp[i] ;
				vname.push_back(tvn) ;
				
				getline( first,temp );
				string tnn = "\0" ;
				vector<string> tnns ;
				
				
				for( int i = 0 ; i < temp.size() ; i++ ) {
					
					if(temp[i] == ','){
						if(temp[i+1] == 'o'){
							int x = i ;
							while( temp[x-1] != ' ' )x-- ;
							tnn = tnn + temp[x] ;
							x++ ;
							while( temp[x] != '(' ){
								tnn = tnn + temp[x] ;
								x++;
							}
							tnns.push_back(tnn) ;
							
						}
						
					}
					tnn = "\0" ;
				}
				
				nw onenw ;
				string tin = "\0" ;
				vector<nw> comnw ;
				for( int i = 0 ; i < temp.size() ; i++ ) {
					
					if(temp[i] == ','){
						if(temp[i+1] == 'i'){
							int x = i ;
							while( temp[x-1] != ' ' )x-- ;
							onenw.name = onenw.name + temp[x] ;
							x++ ;
							while( temp[x] != '(' ){
								onenw.name = onenw.name + temp[x] ;
								x++;
							}
							
							char snum[] = "\0" ;
							x++;
							int s = 0 ;
							while( temp[x] != ',' ){
								snum[s] = temp[x] ;
								s++ ;
								x++;
							}
							
							
							onenw.weight = atoi(snum) ;
							
							comnw.push_back(onenw) ;
							
						}
						
					}
					onenw.name = "\0";
					onenw.weight = 0 ;
				}
				
				iwname.push_back(comnw) ;
				comnw.clear() ;
				
				nname.push_back(tnns) ;
				tnns.clear() ;
				
			}
			
			
			
			/*
			
			    for( int f = 0 ; f < nname.size() ; f++ ) {
			    	cout << vname[f] <<"\n" ;
				    for( int g = 0 ; g < iwname[f].size() ; g++ ) {
						cout << iwname[f][g].name << "," << iwname[f][g].weight << " " ;
					
					}
					cout << "\n" ;
				    for( int g = 0 ; g < nname[f].size() ; g++ ) {
						cout << nname[f][g] << " " ;
					
					}		
					cout << "\n" ;			
					
				}
			
			
			
			
			*/
			Graph2 gggg(vname.size());
			
			
			for( int f = 0 ; f < vname.size() ; f++ ) {
			    for( int g = 0 ; g < iwname[f].size() ; g++ ) {
			    	
			    	for( int h = 0 ; h < nname.size() ; h++ ) {
						
			    		for( int k = 0 ; k < nname[h].size() ; k++ ) {
			    			if ( nname[h][k] == iwname[f][g].name ){
			    				gggg.AddEdgeList(h,f, iwname[f][g].weight ) ;
			    				// cout << vname[f] << " " << iwname[f][g].weight << "\n" ;
							}
			    			
			    		
						}
					}
			   
			    
				}
			    
			   			
			
			}
			gggg.BFS(0);
			iwname.clear() ;
			vname.clear() ;
			nname.clear() ;
			iname.clear() ;
			
			
			
			
			
			
		}
        else ;

		
  		
  		// syntax() ;
  		
  		
  		
  		

}
