/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Dominick Battinelli and Zachary Rimshnick
 * Version     : 1.0
 * Date        : 12/7/22
 * Description : Implementation of Floyds algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <utility>
#include <fstream>
#include <climits>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int len(long num) {
    // Returns num of digits
	int digits = 1;
	while(num > 9){
		num = num/10;
		digits++;
	}
    return digits;
}

string findPath(long** matrix,long A, long B){
  string str;
  if(matrix[A][B] != LONG_MAX){
      string first = findPath(matrix,A,matrix[A][B]);
      string second = findPath(matrix,matrix[A][B],B);
      str  = first;
      str += second;
      return str;
  }
  else{
    str = " -> "; 
    str += char(65 + B);
    return str;
  }
  
}
/** 
 * Displays the matrix on the screen formatted as a table. 
 */ 
void display_table(long** const matrix, int const num_vertices, const string &label, const bool use_letters) { 
  cout << label << endl; 
  long max_val = 0; 
  long INF = LONG_MAX;
  for (int i = 0; i < num_vertices; i++) { 
    for (int j = 0; j < num_vertices; j++) { 
      long cell = matrix[i][j]; 
      if (cell < INF && cell > max_val) { 
        max_val = matrix[i][j]; 
      } 
    } 
  } 
  int max_cell_width = use_letters ? len(max_val) : 
    len(max(static_cast<long>(num_vertices), max_val)); 
  cout << ' '; 
  for (int j = 0; j < num_vertices; j++) { 
    cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
  } 
  cout << endl; 
  for (int i = 0; i < num_vertices; i++) { 
    cout << static_cast<char>(i + 'A'); 
    for (int j = 0; j < num_vertices; j++) { 
      cout << " " << setw(max_cell_width); 
      if (matrix[i][j] == INF) { 
        cout << "-"; 
      } else if (use_letters) { 
        cout << static_cast<char>(matrix[i][j] + 'A'); 
      } else { 
        cout << matrix[i][j]; 
      } 
    } 
    cout << endl; 
  } 
  cout << endl; 
} 

void deleteMatrix(long **matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

bool isNumber(string str){
  for(auto ch : str){
    if(!isdigit(ch)){
      return false;
    }
  }
  return true;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
  
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        int num_vertices = 0; 
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        getline(input_file,line);
        if(!isNumber(line)){
                cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                return -1;
              }
               num_vertices = stoi(line);
               if(num_vertices < 1 || num_vertices > 26){
                 cerr << "Error: Invalid number of vertices '" << num_vertices << "' on line 1." << endl;
                 return -1;
               }
              
              long** matrix = new long*[num_vertices];
                for(int i = 0; i < num_vertices; i++){
                  matrix[i] = new long[num_vertices];
                  for(int j = 0; j < num_vertices; j++){
                    if(j == i){
                       matrix[i][j] = 0;
                    }
                    else{
                      matrix[i][j] = LONG_MAX;
                    }
                  }
                }
        ++line_number;
        while (getline(input_file, line)) {
                string parts[3];
                string seg = "";
                int i = 0;
                for(auto ch : line){
                  if(ch == ' '){
                    parts[i] = seg;
                    seg = "";
                    i++;
                  }
                  else{
                    seg = seg + ch;
                  }
                }
                parts[i] = seg;
                if(i != 2){
                  cerr << "Error: Invalid edge data '"<< line << "' on line "<<line_number <<"." << endl;
                  deleteMatrix(matrix,num_vertices);
                  return -1;
                }
                if(parts[0][0] < 'A' || parts[0][0] > ('A' + num_vertices) || parts[0].length() > 1){
                  cerr << "Error: Starting vertex '"<< parts[0] << "' on line "<< line_number<<" is not among valid values A-"<< char('A' + num_vertices - 1)<<"." << endl;
                  deleteMatrix(matrix,num_vertices); 
                  return -1;
                }
              
                if(parts[1][0] > ('A' + num_vertices) || parts[1][0] < 'A' || parts[1].length() > 1){
                   cerr << "Error: Ending vertex '"<< parts[1] << "' on line "<< line_number<<" is not among valid values A-"<< char('A' + num_vertices - 1)<<"." << endl;
                  deleteMatrix(matrix,num_vertices);
                  return -1;
                }
                string weightstr = parts[2];
                if(!isNumber(weightstr)){
                  cerr << "Error: Invalid edge weight '"<< parts[2] << "' on line "<< line_number<<"." << endl;
                  deleteMatrix(matrix,num_vertices);
                  return -1;
                }
                int weight = stoi(weightstr);
                if(weight <= 0 ){
                   cerr << "Error: Invalid edge weight '"<< parts[2] << "' on line "<< line_number<<"." << endl;
                  deleteMatrix(matrix,num_vertices);
                  return -1;
                }

              matrix[(parts[0][0] - 65)][(parts[1][0] - 65)]  = weight;
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
        display_table(matrix,num_vertices,"Distance matrix:", false);
        long** path = new long*[num_vertices];
                for(int i = 0; i < num_vertices; i++){
                  path[i] = new long[num_vertices];
                  for(int j = 0; j < num_vertices; j++){
                      path[i][j] = matrix[i][j];
                    }
                  }
        long** inter = new long*[num_vertices];
                for(int i = 0; i < num_vertices; i++){
                  inter[i] = new long[num_vertices];
                  for(int j = 0; j < num_vertices; j++){
                      inter[i][j] = LONG_MAX;
                    }
                  }
        for(int k = 0; k < num_vertices; k++){
          for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
              if(path[i][k] != LONG_MAX && path[k][j] != LONG_MAX){
                if(path[i][k] + path[k][j] < path[i][j]){
                    inter[i][j] = k;
                    long dist = path[i][k] + path[k][j];
                    path[i][j] = dist;
                }
                
              }
            }
          }
        }
        display_table(path,num_vertices,"Path lengths:", false);
        display_table(inter,num_vertices,"Intermediate vertices:", true);
      //DISPLAY PATHS
        for(int i = 0; i < num_vertices; i++){
          for(int j = 0; j < num_vertices; j++){
            cout << char(65 + i) << " -> " << char(65 + j);
            if(i == j){
              cout << ", distance: 0, path: " << char(65 + i)<< endl;
            }
            else if(path[i][j] == LONG_MAX){
              cout << ", distance: infinity, path: none"<<endl;
            }
            else{
              cout << ", distance: " << path[i][j] << ", path: " << char(65 + i);
              if(inter[i][j] == LONG_MAX){
                cout << " -> " << char(65 + j) << endl;
              }
              else{
                string str = findPath(inter,i,j);
                cout << str << endl;
              }
             
            }
          }
        }
        deleteMatrix(matrix,num_vertices);
        deleteMatrix(path,num_vertices);
        deleteMatrix(inter,num_vertices);
      
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    return 0;
}

