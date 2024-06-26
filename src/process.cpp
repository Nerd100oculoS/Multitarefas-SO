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

void Combination(unordered_map<int, vector<string> > *newItens, unordered_map<int, vector<vector<string> > > *newItensPerm){

     unordered_map<int, vector<string> > :: iterator it;
     vector<string>::iterator itr, itrv, itrb, itrc;
     
     vector<string> vec_aux;
     vector<vector<string> > vec_matrix;
     
     //Acessa cada chave dos itens
     for(it = newItens->begin(); it != newItens->end(); ++it){

          sort((*it).second.begin(), (*it).second.end()); // Custo O(n log(n)) -> ordena cada vetor para facilitar a etapa 3.

          vec_matrix.clear();

          // 1 a 1
          for(itr = it->second.begin(); itr != it->second.end(); ++itr){
               
               vec_aux.clear();
               vec_aux.push_back((*itr));
               vec_matrix.push_back(vec_aux);
          }

          //2 a 2
          for(itr = it->second.begin(); itr != it->second.end(); ++itr){

               itrv = itr;
               ++itrv;
               for(; itrv != it->second.end(); ++itrv){
                    
                    vec_aux.clear();
                    vec_aux.push_back(*itr);
                    vec_aux.push_back(*itrv);
                    vec_matrix.push_back(vec_aux);
               }
          }

          //3 a 3
          for(itr = it->second.begin(); itr != it->second.end(); ++itr){

               itrv = itr;
               ++itrv;

               for(; itrv != it->second.end(); ++itrv){
                    
                    itrb = itrv;
                    ++itrb;

                    for(; itrb != it->second.end(); ++itrb){

                         vec_aux.clear();
                         vec_aux.push_back(*itr);
                         vec_aux.push_back(*itrv);
                         vec_aux.push_back(*itrb);
                         vec_matrix.push_back(vec_aux);

                    }
               }
          }

          
          //4 a 4
          for(itr = it->second.begin(); itr != it->second.end(); ++itr){

               itrv = itr;
               ++itrv;

               for(; itrv != it->second.end(); ++itrv){
                    
                    itrb = itrv;
                    ++itrb;

                    for(; itrb != it->second.end(); ++itrb){
                         
                         itrc = itrb;
                         ++itrc;

                         for(; itrc != it->second.end(); ++itrc){

                              vec_aux.clear();
                              vec_aux.push_back(*itr);
                              vec_aux.push_back(*itrv);
                              vec_aux.push_back(*itrb);
                              vec_aux.push_back(*itrc);
                              vec_matrix.push_back(vec_aux);
                         }
                    }
               }
          }
          

          (*newItensPerm)[it->first] = vec_matrix;
     }
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

               for(string a: n){
                    cout << a << " ";
               }

               cout << endl;
          }
          cout << endl;
     }
}

void InitHashIntersection(
    unordered_map<string, vector<int> > *classesD,
    unordered_map<string, int > *c_intersection
){

     unordered_map<string, vector<int> >::iterator it;

     for(it = classesD->begin(); it != classesD->end(); ++it){

          (*c_intersection)[it->first] = 0;
     }

}

void PrintHashIntersection(unordered_map<string, int> *c_intersection){

     unordered_map<string, int >::iterator itv;

     for(itv = c_intersection->begin(); itv != c_intersection->end(); ++itv){

          cout << itv->first << " -> " << itv->second << endl;
     } 
}

void VerifyMaxClass(
    unordered_map<string, int > *class_aux,
    unordered_map<string, int > *class_inter
){

     unordered_map<string, int >::iterator itb;
     string class_aux_str;
     int tam = -1;
     for(itb = class_aux->begin(); itb != class_aux->end(); ++itb){

          if(itb->second > tam){

               tam = itb->second;
               class_aux_str.assign(itb->first);
          }
          
     }

     // cout << "Classe: " << class_aux_str << endl;
     (*class_inter)[class_aux_str]++;
}

void IntersectionOnClass(
    unordered_map<string, vector<int> > *classesD,
    unordered_map<string, int > *class_aux,
    vector<int> vec_result
){
     
     unordered_map<string, vector<int> >::iterator itr;

     for(itr = classesD->begin(); itr != classesD->end(); ++itr){

               vector<int> aux;

               set_intersection(
                    vec_result.begin(),vec_result.end(),
                    (*classesD)[itr->first].begin(),(*classesD)[itr->first].end(),
                    back_inserter(aux)
               );

               (*class_aux)[itr->first] += aux.size();
               
     }
}

void MakeIntersection(
    unordered_map<int, vector<vector<string> > > *newItensPerm,
    unordered_map< string, vector<int> > *itensD,
    unordered_map< string, vector<int> > *classesD,
    unordered_map<string, vector<int>> *cache,
    unordered_map<string, int > *class_inter
){

     unordered_map<string, vector<int>> aux_vec;
     unordered_map<int, vector<vector<string> > >::iterator it;
     unordered_map<string, vector<int> >::iterator itr, it_vecAux;
     unordered_map<string, int > class_aux;

     InitHashIntersection(classesD,class_inter);

     int qtd_cache = 0;
     //Caminha por cada KEY da Hash que armazena as combinações
     for(it = newItensPerm->begin(); it != newItensPerm->end(); ++it){

          InitHashIntersection(classesD,&class_aux); // A cada loop, reseta a classe auxiliar.
          
          for(vector<string> vec: it->second){
               
               vector<int> vec_result;// a cada loop reseta o vetor.
               unordered_map<string, vector<int>>::iterator it_aux;

               if(vec.size() == 1){

                    itr = itensD->find(vec[0]);

                    if(itr != itensD->end()){
                         
                         vec_result = itr->second;

                         // Insere na cache
                         cache->insert({vec[0],vec_result});
                    }

               }else{

                    string s1, s2;
                    vector<int> vec1, vec2;
                    bool var_bool = false;
                    
                    string aux_cache = "";

                    for(string str: vec){
                    
                         if(var_bool){

                              aux_cache.append(s1).append(" ");
                              s2.assign(str);
                              vec2 = itensD->find(s2)->second;
                              
                              vec_result.clear();
                              s1.clear();
                              aux_cache.append(s2);
                              
                              //Verifica na Cache se a combinaçãi ja esta presente
                              it_aux = cache->find(aux_cache);
                              if(it_aux != cache->end()){
                                   
                                   vec_result = (*cache)[aux_cache];
                                   qtd_cache++;
                              }else{

                                   set_intersection(
                                        vec1.begin(), vec1.end(),
                                        vec2.begin(),vec2.end(),
                                        back_inserter(vec_result)
                                   );

                                   cache->insert({aux_cache,vec_result});
                              }

                              vec1 = vec_result; 
                              s1.assign(aux_cache);

                         }else{
                              
                              var_bool = true;
                              s1.assign(str);
                              vec1 = itensD->find(s1)->second;

                         } 
                    }
               }

               IntersectionOnClass(classesD,&class_aux,vec_result);
          }

          
          // cout << "Linha de T.csv => " << it->first << endl;
          VerifyMaxClass(&class_aux,class_inter);
          // PrintHashIntersection(&class_aux);
          // cout << endl;
     }

     cout << "\nA política de ROUND-ROBIN acessou a cache: " << qtd_cache << "vezes\n";

     // cout << endl << endl;
}


void ReadingFiles(){

     unordered_map<int, vector<string> > itensT;
     unordered_map<string, vector<int> > classesT;
     
     unordered_map<string, vector<int> > itensD;
     unordered_map<string, vector<int> > classesD;

     unordered_map<int, vector<string> > newItens;
     unordered_map<int, vector<vector<string> > > newItensPerm;

     unordered_map<string, int > IntersectionClass;

     unordered_map<string, vector<int>> Cache;

     
     FileReadingD(&itensD,&classesD);
     
     FileReadingT(&itensT,&classesT);
     
     CheckKeyValues(&itensD,&itensT,&newItens);

     Combination(&newItens, &newItensPerm);
     // PrintPermutation(&newItensPerm);
     
     steady_clock::time_point start, end;
     
     start = steady_clock::now();
     MakeIntersection(&newItensPerm,&itensD,&classesD,&Cache,&IntersectionClass);
     end = steady_clock::now();

     auto time = duration_cast<duration<double>>(end-start);

     cout << "\nROUND-ROBIN na intersecção levou: " << 
     fixed << setprecision(9) << time.count() << " segundos\n\n";
     
     PrintHashIntersection(&IntersectionClass);
}


// ------------------------ etapa 5 ------------------------

void NewPolitics_SJF(HASH_int_MatrixString *newItensPerm, SUPER_DATAset *data_set){

     vector<vector<string>> MatrixS_aux;
     map<int, MATRIX_string> hash_tam;
     unordered_map<int, map<int, MATRIX_string>> hash_linha;
     map<int, vector<unordered_map<int, map<int, MATRIX_string>> > > superMap_aux;
     vector<unordered_map<int, map<int, MATRIX_string>> > superVec_aux;

     HASH_int_MatrixString::iterator it;
     map<int, vector<unordered_map<int, map<int, MATRIX_string>> > >::iterator its;

     for(it = newItensPerm->begin(); it != newItensPerm->end(); ++it){
          
               
          int tam_aux;
          for(vector<string> n: it->second){
               
               tam_aux = n.size();

               hash_tam.clear();
               hash_linha.clear();
               MatrixS_aux.clear();

               MatrixS_aux.push_back(n);

               hash_tam.insert({tam_aux,MatrixS_aux});
               hash_linha.insert({it->first,hash_tam});

               its = superMap_aux.find(tam_aux);
               
               if(its != superMap_aux.end()){

                    its->second.push_back(hash_linha);
               
               }else{

                    superVec_aux.clear();
                    superVec_aux.push_back(hash_linha);
                    superMap_aux.insert({tam_aux,superVec_aux});
                    
               }
          }
     }

     for(its = superMap_aux.begin(); its != superMap_aux.end(); ++its){

          // cout << "index vec: " << its->first << endl;
          for(auto vec: its->second){

               data_set->push_back(vec);
          }
     }
}



void PrintSuperDataset(SUPER_DATAset *data){

     for(auto vec: *data){

          unordered_map<int, map<int, MATRIX_string>>::iterator itr;
                    
          for(itr = vec.begin(); itr != vec.end(); ++itr){

               cout << "linha: " << itr->first;
               map<int, MATRIX_string>::iterator itb;
               for(itb = itr->second.begin(); itb != itr->second.end(); ++itb){

                    cout << " tam: " << itb->first << endl;
                    for(auto matrix: itb->second){

                         for(auto vec_int: matrix){

                              for(auto str: vec_int){

                                   cout << str;
                              }
                              
                              cout << " ";
                         }

                         cout << endl;
                    }

               }
          }

          cout << endl;
     }
}

void MakeIntersection_SJF(
    SUPER_DATAset *data,
    unordered_map< string, vector<int>> *itensD,
    unordered_map<string, vector<int>> *classesD,
    unordered_map<string, vector<int>> *cache,
    unordered_map<string, int > *class_inter
){
     unordered_map<int, unordered_map<string, int>> SuperMap_aux;
     unordered_map<int, unordered_map<string, int>>::iterator itz;
     

     InitHashIntersection(classesD,class_inter);
     int qtd_cache = 0;
     //Percorre a Super estrutura.
     for(auto vec: *data){

          
          unordered_map<string, vector<int> >::iterator itt;
          unordered_map<string, vector<int>>::iterator itv;
          unordered_map<int, map<int, MATRIX_string>>::iterator itr;

          //Acessa hash de linhas
          for(itr = vec.begin(); itr != vec.end(); ++itr){

               itz = SuperMap_aux.find(itr->first);

               if(!(itz != SuperMap_aux.end())){

                    unordered_map<string, int > class_aux;
                    InitHashIntersection(classesD,&class_aux);
                    SuperMap_aux.insert({itr->first,class_aux});
               }

               itz = SuperMap_aux.find(itr->first);

               // cout << "linha: " << itr->first;

               //Acessando a hash de tamanhos de vetores nas matrizes
               map<int, MATRIX_string>::iterator itb;
               for(itb = itr->second.begin(); itb != itr->second.end(); ++itb){
                    
               
                    // cout << " tam: " << itb->first << endl;
                    for(vector<string> vec: itb->second){
                         
                         vector<int> vec_result;
                         
                         if(vec.size() == 1){

                              itt = itensD->find(vec[0]);
                              
                              if(itt != itensD->end()){
                                   
                                   vec_result = itt->second;

                                   cache->insert({vec[0], vec_result});
                              }

                         }else{

                              string s1, s2;
                              vector<int> vec1, vec2;
                              bool var_bool = false;
                              
                              string aux_cache = "";

                              for(string str: vec){
                              
                                   if(var_bool){

                                        aux_cache.append(s1).append(" ");
                                        s2.assign(str);
                                        vec2 = itensD->find(s2)->second;
                                        
                                        vec_result.clear();
                                        s1.clear();
                                        aux_cache.append(s2);
                                        
                                        //Verifica na Cache se a combinaçãi ja esta presente
                                        itv = cache->find(aux_cache);
                                        if(itv != cache->end()){
                                             
                                             vec_result = (*cache)[aux_cache];
                                             qtd_cache++;
                                        }else{

                                             set_intersection(
                                                  vec1.begin(), vec1.end(),
                                                  vec2.begin(),vec2.end(),
                                                  back_inserter(vec_result)
                                             );

                                             cache->insert({aux_cache,vec_result});
                                        }

                                        vec1 = vec_result; 
                                        s1.assign(aux_cache);

                                   }else{
                                        
                                        var_bool = true;
                                        s1.assign(str);
                                        vec1 = itensD->find(s1)->second;

                                   } 
                              }

                         }

                         
          
                         IntersectionOnClass(classesD,&itz->second,vec_result);
                    }         
               }
          }
     }

     for(itz = SuperMap_aux.begin(); itz != SuperMap_aux.end(); ++itz){

          // cout << "Linha " << itz->first << endl;
          VerifyMaxClass(&itz->second,class_inter);
          // PrintHashIntersection(&itz->second);
          // cout << endl;
     
     }
     // cout << endl;

     cout << "\nA política de SJF acessou a cache: " << qtd_cache << "vezes\n";
     
}

void MakeStage5(){

     unordered_map<int, vector<string> > itensT;
     unordered_map<string, vector<int> > classesT;
     
     unordered_map<string, vector<int> > itensD;
     unordered_map<string, vector<int> > classesD;

     unordered_map<int, vector<string> > newItens;
     unordered_map<int, vector<vector<string> > > newItensPerm;

     unordered_map<string, vector<int>> cache;
     unordered_map<string, int > class_inter;
     SUPER_DATAset DATA;

     //Etapa 1
          FileReadingD(&itensD,&classesD);
          
          FileReadingT(&itensT,&classesT);
          
     //Etapa 2
          CheckKeyValues(&itensD,&itensT,&newItens);
          
          Combination(&newItens, &newItensPerm);
     
     //Novo formato
     NewPolitics_SJF(&newItensPerm,&DATA);

     steady_clock::time_point start, end;

     start = steady_clock::now();
     MakeIntersection_SJF(&DATA,&itensD,&classesD,&cache,&class_inter);
     end = steady_clock::now();

     auto time = duration_cast<duration<double>>(end-start);

     cout << "\nSFJ na intersecção levou: " << 
     fixed << setprecision(9) << time.count() << " segundos\n\n";

     PrintHashIntersection(&class_inter);
     // PrintSuperDataset(&DATA);
}

void MakeStage_aux(){

     unordered_map<int, vector<string> > itensT;
     unordered_map<string, vector<int> > classesT;
     
     unordered_map<string, vector<int> > itensD;
     unordered_map<string, vector<int> > classesD;

     unordered_map<int, vector<string> > newItens;
     unordered_map<int, vector<vector<string> > > newItensPerm;

     unordered_map<string, vector<int>> cache;
     unordered_map<string, int > class_inter;
     SUPER_DATAset DATA;

     //Etapa 1
          FileReadingD(&itensD,&classesD);
          
          FileReadingT(&itensT,&classesT);
          
     //Etapa 2
          CheckKeyValues(&itensD,&itensT,&newItens);
          
          Combination(&newItens, &newItensPerm);
     
     // Proximas etapas
     
     NewPolitics_SJF(&newItensPerm,&DATA);

     estrutura_global vglobal;
     pthread_t cons[NUMCONS];
     pthread_mutex_init(&vglobal.mutex_b, NULL);
     pthread_mutex_init(&vglobal.mutex_c, NULL);

     steady_clock::time_point start, end;
     
     start = steady_clock::now();
     PreecheQueue(
          &vglobal,
          &DATA,
          &itensD,
          &classesD,
          &cache,
          &class_inter
     );

     for(int i=0; i<NUMCONS; i++)
		pthread_create(&(cons[i]), NULL, consumidor, &vglobal);

	for(int i=0; i<NUMCONS; i++)
		pthread_join(cons[i], NULL);

     unordered_map<int, unordered_map<string, int>>::iterator itz;
     
     for(itz = vglobal.SuperMap_aux.begin(); itz != vglobal.SuperMap_aux.end(); ++itz){

          // cout << "Linha " << itz->first << endl;
          VerifyMaxClass(&itz->second,vglobal.class_inter);
          // PrintHashIntersection(&itz->second);
          // cout << endl;
     
     }
     end = steady_clock::now();

      auto time = duration_cast<duration<double>>(end-start);

     cout << "\nSFJ com " << NUMCONS << " THREADS na intersecção levou: " << 
     fixed << setprecision(9) << time.count() << " segundos\n\n";
     // cout << endl;

     PrintHashIntersection(&class_inter);
};

void *consumidor(void *arg){

     estrutura_global *vglobal = (estrutura_global*)arg;

     unordered_map<int, unordered_map<string, int>>::iterator itz;
     unordered_map<string, vector<int> >::iterator itt;
     unordered_map<string, vector<int>>::iterator itv;
     unordered_map<int, map<int, MATRIX_string>>::iterator itr;
     
     while(vglobal->fila_buffer.size() > 0){
          
          if(!(vglobal->fila_buffer.empty())){

               pthread_mutex_lock(&vglobal->mutex_b);
               DATAset n = vglobal->fila_buffer.front();
               vglobal->fila_buffer.pop();
               pthread_mutex_unlock(&vglobal->mutex_b);
               


               pthread_mutex_lock(&vglobal->mutex_c);

               //Acessa hash de linhas

               for(itr = n.begin(); itr != n.end(); ++itr){
                    
                    itz = vglobal->SuperMap_aux.find(itr->first);
                    

                    if(!(itz != vglobal->SuperMap_aux.end())){

                         unordered_map<string, int > class_aux;
                         InitHashIntersection(vglobal->classesD,&class_aux);
                         vglobal->SuperMap_aux.insert({itr->first,class_aux});
                    
                    }
                    


                    itz = vglobal->SuperMap_aux.find(itr->first);

                    // cout << "linha: " << itr->first;

                    //Acessando a hash de tamanhos de vetores nas matrizes
                    map<int, MATRIX_string>::iterator itb;
                    for(itb = itr->second.begin(); itb != itr->second.end(); ++itb){
                         
                    
                         // cout << " tam: " << itb->first << endl;
                         for(vector<string> vec: itb->second){
                              
                              vector<int> vec_result;
                              
                              if(vec.size() == 1){

                                   itt = vglobal->itensD->find(vec[0]);
                                   
                                   if(itt != vglobal->itensD->end()){
                                        
                                        vec_result = itt->second;

                                        vglobal->cache->insert({vec[0], vec_result});
                                   }

                              }else{

                                   string s1, s2;
                                   vector<int> vec1, vec2;
                                   bool var_bool = false;
                                   
                                   string aux_cache = "";

                                   for(string str: vec){
                                   
                                        if(var_bool){

                                             aux_cache.append(s1).append(" ");
                                             s2.assign(str);
                                             vec2 = vglobal->itensD->find(s2)->second;
                                             
                                             vec_result.clear();
                                             s1.clear();
                                             aux_cache.append(s2);
                                             
                                             //Verifica na Cache se a combinaçãi ja esta presente
                                             itv = vglobal->cache->find(aux_cache);
                                             if(itv != vglobal->cache->end()){
                                                  
                                                  vec_result = itv->second;

                                             }else{

                                                  set_intersection(
                                                       vec1.begin(), vec1.end(),
                                                       vec2.begin(),vec2.end(),
                                                       back_inserter(vec_result)
                                                  );

                                                  vglobal->cache->insert({aux_cache,vec_result});
                                             }

                                             vec1 = vec_result; 
                                             s1.assign(aux_cache);

                                        }else{
                                             
                                             var_bool = true;
                                             s1.assign(str);
                                             vec1 = vglobal->itensD->find(s1)->second;

                                        } 
                                   }

                              } 
               
                              IntersectionOnClass(vglobal->classesD,&itz->second,vec_result);
                         }         
                    }
               }

               pthread_mutex_unlock(&vglobal->mutex_c);
               
          }
     }

     pthread_exit(arg);
}

void PreecheQueue(

     estrutura_global *vglobal,
     SUPER_DATAset *data_set,
     unordered_map< string, vector<int>> *itensD,
     unordered_map<string, vector<int>> *classesD,
     unordered_map<string, vector<int>> *cache,
     unordered_map<string, int > *class_inter
){

     vglobal->itensD = itensD;
     vglobal->classesD = classesD;
     vglobal->cache = cache;
     vglobal->class_inter = class_inter;


     SUPER_DATAset::iterator it;

     for(it = data_set->begin(); it != data_set->end(); ++it){

          vglobal->fila_buffer.push(*it);
     }
}