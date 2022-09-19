#include "process.hpp"

void TokenizarInColumn(string line_token, unordered_map<string, vector<int> > *itens,unordered_map<string, vector<int> > *classes, int count_line){

     int count_column = 1;
     stringstream sstream(line_token);
     string token;
     char del = ',';

     unordered_map<string, vector<int> >::iterator it;

     while (getline(sstream, token, del)){

          if(count_column < 5){
               
               token.append(",").append(to_string(count_column));
               (*itens)[token].push_back(count_line);
          
          }else{(*classes)[token].push_back(count_line);}
               
          count_column++;
     }
}

void TokenizarInLine(string line_token, unordered_map<int, vector<string> > *itens,unordered_map<string, vector<int> > *classes, int count_line){

     int count_column = 1;
     stringstream sstream(line_token);
     string token;
     char del = ',';

     unordered_map<string, vector<int> >::iterator it;

     while (getline(sstream, token, del)){

          if(count_column < 5){
               
               token.append(",").append(to_string(count_column));
               (*itens)[count_line].push_back(token);
          
          }else{(*classes)[token].push_back(count_line);}

          count_column++;
     }
}

 void FileReadingD(unordered_map< string, vector<int> > *itensD,  unordered_map< string, vector<int> > *classesD){

     int count_line = 1;
     string line;
     char del = ','; //arquivos .csv

     ifstream process("./src/input/D.csv");

     if(process.is_open()){

          while(!process.eof()){

               getline(process,line);

               TokenizarInColumn(line,itensD,classesD,count_line);
               count_line++;     
          }

     }else{cout << "erro" << endl;}

     process.close();
}

void FileReadingT(unordered_map<int, vector<string> > *itensT,  unordered_map<string, vector<int> > *classesT){

     int count_line = 1;
     string line;
     char del = ','; //arquivos .csv

     ifstream process("./src/input/T.csv");

     if(process.is_open()){

          while(!process.eof()){

               getline(process,line);

               TokenizarInLine(line,itensT,classesT,count_line);
               count_line++;
          }

     }else{cout << "erro" << endl;}

     process.close();
}

void CheckKeyValues(unordered_map<string, vector<int> > *itensD, unordered_map< int, vector<string> > *itensT, unordered_map< int, vector<string> > *newItens){

     unordered_map<int, vector<string> > :: iterator it;
     
     for(it = itensT->begin(); it != itensT->end(); ++it){

          for(string n: it->second){

               if(itensD->find(n) != itensD->end()){(*newItens)[it->first].push_back(n);}
          }
     }

}

void Permutation(unordered_map<int, vector<string> > *newItens, unordered_map<int, vector<vector<string> > > *newItensPerm){

     unordered_map<int, vector<string> > :: iterator it;
     vector<string>::iterator itr, itrv, itrb;
     
     vector<string> vec_aux;
     vector<vector<string> > vec_matrix;
     
     //Acessa cada chave dos itens
     for(it = newItens->begin(); it != newItens->end(); ++it){

          sort((*it).second.begin(), (*it).second.end()); // Custo O(n log(n)) -> ordena cada vetor para facilitar a etapa 3.

          vec_matrix.clear();
          for(itr = it->second.begin(); itr != it->second.end(); ++itr){
               
               vec_aux.clear();
               vec_aux.push_back((*itr));
               vec_matrix.push_back(vec_aux);
          }

          for(itr = it->second.begin(); itr != it->second.end(); ++itr){

               itrv = itr;
               ++itrv;
               vec_aux.clear();
               for(; itrv != it->second.end(); ++itrv){

                    vec_aux.push_back(*itr);
                    vec_aux.push_back(*itrv);
                    vec_matrix.push_back(vec_aux);
               }
          }

          for(itr = it->second.begin(); itr != it->second.end(); ++itr){

               itrv = itr;
               ++itrv;
               vec_aux.clear();

               for(; itrv != it->second.end(); ++itrv){
                    
                    itrb = itrv;
                    ++itrb;
                    vec_aux.clear();

                    for(; itrb != it->second.end(); ++itrb){

                         vec_aux.push_back(*itr);
                         vec_aux.push_back(*itrv);
                         vec_aux.push_back(*itrb);
                         vec_matrix.push_back(vec_aux);

                    }
               }
          }

          (*newItensPerm)[it->first] = vec_matrix;
     }
}

void ReadingFiles(){

     unordered_map<int, vector<string> > itensT;
     unordered_map<string, vector<int> > classesT;
     
     unordered_map<string, vector<int> > itensD;
     unordered_map<string, vector<int> > classesD;

     FileReadingD(&itensD,&classesD);
     FileReadingT(&itensT,&classesT);

     cout << "\nArquivos foram lidos!\n";
     
     /*
     int op = 1;
     while(op != 0){

          cout << "\nQual arquivo deseja imprimir?\n" << "[0] - EXIT!\t[1] - D.csv\t[2] - T.csv\n" << ">>>> ";
          cin >> op;

          switch (op){
               
               case 0:
                    cout << "\nEnd of program\n\n";
               break;

               case 1:
                    cout << "\nArquivo D.csv\n";
                    PrintMap(itensD);
                    PrintMap(classesD);
               break;

               case 2:
                    cout << "\nArquivo T.csv\n";
                    PrintMap1(itensT);
                    PrintMap(classesT);
               break;

               default:
                    cout << "opção invalida!" << endl;
               break;
          }
     }
     */

     //procurando se existe determiando valor na chave de D
     
     unordered_map<int, vector<string> > newItens;
     
     CheckKeyValues(&itensD,&itensT,&newItens);

     PrintMap1(newItens);

     cout << endl << endl;

     // Fazendo as permutacoes e armazenando em um novo Map
     // Percorrendo cada vetor com estes interadores.
     unordered_map<int, vector<vector<string> > > newItensPerm;
     
     Permutation(&newItens, &newItensPerm);

     PrintPermutation(&newItensPerm);
     
}

void PrintMap(unordered_map<string, vector<int> > map){

     unordered_map<string, vector<int> >::iterator it;

     cout << endl << endl;
     
     for(it = map.begin(); it != map.end(); ++it){

          cout << it->first << " :: ";

          for(int n: it->second){

               cout << n << " ";
          }

          cout << endl;
     }
}

void PrintMap1(unordered_map<int, vector<string> > map){

     unordered_map<int, vector<string> >::iterator it;

     cout << endl << endl;
     
     for(it = map.begin(); it != map.end(); ++it){

          cout << it->first << " :: ";

          for(string n: it->second){

               cout << n << " ";
          }

          cout << endl;
     }
}

void PrintPermutation(unordered_map<int, vector<vector<string> > > *newItensPerm){

     unordered_map<int, vector<vector<string> > >::iterator it_map;
     
     for(it_map = newItensPerm->begin(); it_map != newItensPerm->end(); ++it_map){

          cout << it_map->first << " :: " << endl;;

          for(vector<string> n: it_map->second){

               for(string a: n){cout << a << " ";}
               cout << endl;
          }
          cout << endl;
     }
}


