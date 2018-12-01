// original BFS ok
#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <utility>
#include <sys/types.h>
#include <unistd.h>
#include <queue>

class Path{	
public :
	//std::stack< std::pair<int, int> > discover_path;
	//std::stack< std::pair<int, int> > short_path;
	//std::vector< std::pair<int, int> > vertex_list;
	//std::vector< std::vector< std::pair<int, int> > > edge_list;
	
	std::vector< std::vector<char> > f_map;
	
	Path() : total_zero(0), overall_step(0), step_cnt(0), zero_cnt(0) {
	};	
	~Path() {
		delete [] vertex_color;
		delete [] pred;
		delete [] depth;
	};	
	
	void BFS(std::pair<int, int>);
	
	int total_zero;
	int limit_steps;
	int overall_step;
	
	int f_row;
	int f_col;	

	std::vector< std::vector<bool> > visited;	
private :
	int step_cnt;
	int zero_cnt;
	
	int* depth;
	std::pair<int, int>* pred;
	int* vertex_color;
};		


void Path::BFS(std::pair<int, int> start) {
	
		//std::cout << "enter" << std::endl;
		//std::cout << "charge(" << start.first << ", " << start.second << ")" << std::endl;
	
	vertex_color = new int[f_row*f_col];
	pred = new std::pair<int, int>[f_row*f_col];
	depth = new int[f_row*f_col];
	
	for(int i = 0; i < f_row*f_col; i++) {
		vertex_color[i] = 0;
		pred[i] = std::make_pair(-1, -1);
		depth[i] = 0;
	}
	
	// check
	visited.resize(f_row, std::vector<bool>(f_col));
	for(int i = 0; i < f_row; i++) {
		for(int j = 0; j < f_col; j++) {
			visited[i][j] = false;
		}	
	}	
	
	
	std::queue< std::pair<int, int> > q;
	std::pair<int, int> current, neighbor;
	
	//for(int i = 0; i < f_row * f_col; i++) {
		if(vertex_color[start.first*f_col + start.second] == 0) {
			vertex_color[start.first*f_col + start.second] = 1;
			depth[start.first*f_col + start.second] = 0;
			pred[start.first*f_col + start.second] = std::make_pair(-1, -1);
			q.push(start);
			
				//std::cout << "q front(" << q.front().first << ", " << q.front().second << ")" << std::endl;	
				//int repeat = 0;
				//int loop = 0;
			
			while(!q.empty()) {
				current = q.front();
				//q.pop();
				
					//++repeat;
					//std::cout << "q pre front(" << q.front().first << ", " << q.front().second << ")" << std::endl;
					//std::cout << repeat << " th enter"<< std::endl;
					//std::cout << "q size " << q.size() << std::endl;
				
				int moves[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
				for(int i = 0; i < 4; i++) {
					
						//++loop;
						//std::cout << loop << "th loop" << std::endl;						
						
					neighbor.first = current.first + moves[i][0];
					neighbor.second = current.second + moves[i][1];
					
						//std::cout << "nei first " << neighbor.first << std::endl;
						//std::cout << "nei second " << neighbor.second << std::endl;
					
					if(neighbor.first < 0 || neighbor.first >= f_row || neighbor.second < 0 || neighbor.second >= f_col) {
						continue;
					}
					if(vertex_color[neighbor.first*f_col + neighbor.second] == 0 && f_map[neighbor.first][neighbor.second] == '0') {
						visited[neighbor.first][neighbor.second] = true;
						
							//std::cout << "go" << std::endl;
						
						vertex_color[neighbor.first*f_col + neighbor.second] = 1;
						depth[neighbor.first*f_col + neighbor.second] = depth[current.first*f_col + current.second] + 1;
						pred[neighbor.first*f_col + neighbor.second] = current;
						q.push(neighbor);
					}
					
							//std::cout << "q pos front(" << q.front().first << ", " << q.front().second << ")" << std::endl;
							//std::cout << "depth " << depth[neighbor.first*f_col + neighbor.second] << std::endl;
				}
				q.pop();
				vertex_color[current.first*f_col + current.second] = 2;	
			}	
		}
			
	//}
		
}	

int main(int argc, char* argv[]) {

		// set input pathway
	char inputPath[20];
		// copy argv[1] to inputPath
		//std::cout << "hi input path" << std::endl;
	strcpy(inputPath, argv[1]);
		// connect inputPath to /matrix.data
		//std::cout << "hi strcpy" << std::endl;
	strcat(inputPath, "/floor.data");
		//cout << "input "<< inputPath << endl;  // for check
		//std::cout << "hi strcat" << std::endl;
	std::ifstream fin(inputPath); 
		//std::cout << "hi iftream" << std::endl;

	Path bot;
	
	if(fin.is_open()) {
			// set the value of row and col from input file
			//std::cout << "hi file open" << std::endl;
		fin >> bot.f_row;
			//std::cout << "hi fin row " << f_row << std::endl;
		fin >> bot.f_col;
			//std::cout << "hi fin col " << f_col << std::endl;
		fin >> bot.limit_steps;
			//std::cout << "hi fin limit " << ro.limit_steps <<std::endl;
			//cout << row << " " << col << endl;   // for check
	} else {
		std::cerr << "cannot open file";
	}
	if(argc < 2) {
		std::cout << "missing argumant" << std::endl;
		exit(0);
	}
	
	bot.f_map.resize(bot.f_row, std::vector<char>(bot.f_col));
			
	std::pair<int, int> charge;
			
	for(int i = 0; i < bot.f_row; i++) {
		for(int j = 0; j < bot.f_col; j++) {
			fin >> bot.f_map[i][j];
			if(bot.f_map[i][j] == '0') {
				++bot.total_zero;
			} else if(bot.f_map[i][j] == 'R') {
				charge = std::make_pair(i, j);
			}		 			 
		}	
	}	
	
	fin.close();
	
	// check
	for(int i = 0; i < bot.f_row; i++) {
		for(int j = 0; j < bot.f_col; j++) {
			std::cout << bot.f_map[i][j];
		}
		std::cout << std::endl;	
	}
		
    char outputPath[20];
    strcpy(outputPath, argv[1]);
    strcat(outputPath, "/final.path");
        std::cout << "output " << outputPath << std::endl;  
    std::ofstream fout(outputPath);

        // open for output during Find_way()
    if(fout.is_open()) {
        std::cout << "file is open " << std::endl; 
    } else {
		std::cerr << "cannot open file " << std::endl;
    }

	bot.BFS(charge);
	
    // output overall_step by lseek()
    FILE* fd;
    if( (fd = fopen( strcat(argv[1], "/final.path"), "r+b") )== NULL) {
		std::cout << "open failed" << std::endl;
    }

    off_t currpos = lseek(fileno(fd), 0, SEEK_SET);
    if(currpos == -1) {
		std::cout << "cannot seek" << std::endl;
        return -1;
    } else {
        fout << bot.overall_step << std::endl;    
    }

    fout.close();
    close(fileno(fd));
    
    // check
	for(int i = 0; i < bot.f_row; i++) {
		for(int j = 0; j < bot.f_col; j++) {
			std::cout << bot.visited[i][j];
		}
		std::cout << std::endl;	
	}	

	std::cout << "complete" << std::endl;
	
	return 0;
}	


