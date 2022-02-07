#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include "Solution.h"

using namespace std;

Graph* readingProblemInstance(ifstream &inputFile, int directed, int weightedEdge, int weightedNode)
{
    int idNodeSource, idNodeTarget, nodeWeight, order;
    unsigned int cluster;
    int idNode;
    char g;

    string line, garb;

    /*Os tres getline seguintes fazem a leitura das 3 linhas que devem ser ignoradas no arquivo*/
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::getline(inputFile, line);

    std::getline(inputFile, line); //faz a leitura da linha a ser operada

    std::stringstream oss; //passa o buffer lido para uma stringstream

    oss<<line;

    std::getline(oss, garb, ';'); //le apenas a primeira linha

    int i = garb.find('='); //acha o delimitador


    string temp = garb.substr(i+1, garb.length()-2); //pega apenas o numero de cluster

    cluster = stoi(temp); //passa o numero de cluster para um inteiro

    cout<<"Cluster = "<<cluster<<endl;

    oss.clear();
    garb.clear();

    std::getline(inputFile, line);
    std::getline(inputFile, line);
    char space = 32;
    oss<<line;
    std::getline(oss, garb, '\n');

    i = garb.find(space);

    order = stoi(garb.substr(i, garb.find('v')-2));

    oss.clear();

    Graph* graphToReturn = new Graph(order, directed, weightedEdge, weightedNode, cluster);

    /* Ignora as linhas */
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::getline(inputFile, line);

    /* Ignora linha */
    std::getline(inputFile, line);

    /*O for abaixo insere os nós*/
    for(int cont = 0; cont < order; cont++){
        inputFile>>idNode;
        inputFile>>nodeWeight;

        graphToReturn->setLastIdUsed(graphToReturn->getLastIdUsed() + 1);
        graphToReturn->insertNode(graphToReturn->getLastIdUsed(), idNode, nodeWeight);
    }

    std::getline(inputFile, line); //ignora o resto da linha onde estao os ultimos nós e pula para a próxima

    /* Ignora as linhas */
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::getline(inputFile, line);

    inputFile>>g; //pega o primeiro '('

    /*o while abaixo insere as arestas*/
    while(g != ';'){
        inputFile>>idNodeSource; //pega o source

        inputFile>>g; //pega a ','
        inputFile>>idNodeTarget; //pega o target

        inputFile>>g; //pega o ')'

        graphToReturn->insertEdge(idNodeSource, idNodeTarget, 1);

        inputFile>>g; //atualiza
    }

    return graphToReturn; /*retorna o grafo criado*/
}

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if(!graph->getWeightedEdge() && !graph->getWeightedNode()){

        while(input_file >> idNodeSource >> idNodeTarget) {
            graph->insertEdge(idNodeSource, idNodeTarget, 1);
        }

    } else if(graph->getWeightedEdge() && !graph->getWeightedNode() ){

        float edgeWeight;

        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }

    } else if(graph->getWeightedNode() && !graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, 1);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    } else if(graph->getWeightedNode() && graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }

    return graph;
}


int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Subgrafo vertice-induzido pelo fecho transitivo direto" << endl;
    cout << "[2] Subgrafo vertice-induzido pelo fecho transitivo indireto" << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[4] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[5] Arvore Geradora Minima de Prim" << endl;
    cout << "[6] Arvore Geradora Minima de Kruskal" << endl;
    cout << "[7] Imprimir caminhamento em largura" << endl;
    cout << "[8] Imprimir ordenacao topologica" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Graph* graph, ofstream& output_file){

    switch (selecao) {

        //Subgrafo vértice-induzido pelo fecho transitivo direto;
        case 1:{

            int name;

            cout << "Selecionado: Subgrafo vertice-induzido pelo fecho transitivo direto" << endl;
            cout << "Digite a seguir o numero do vertice: " << endl;
            cin >> name;

            graph->getVertexInducedDirectTransitiveClosure(name, output_file);

            cout << "Subgrafo produzido foi inserido no arquivo de saida." << endl;
            break;
        }
        //Subgrafo vértice-induzido pelo fecho transitivo indireto;
        case 2:{

            int name;

            cout << "Selecionado: Subgrafo vertice-induzido pelo fecho transitivo indireto" << endl;
            cout << "Digite a seguir o numero do vertice: " << endl;
            cin >> name;

            graph->getVertexInducedIndirectTransitiveClosure(name, output_file);

            cout << "Subgrafo produzido foi inserido no arquivo de saida." << endl;
            break;
        }
        //Caminho mínimo entre dois vértices usando Dijkstra;
        case 3:{
            int idSource, idTarget;

            cout << "Selecionado: Caminho minimo entre dois vertices usando Dijkstra" << endl;
            cout << "Digite a seguir o numero do primeiro vertice (origem): " << endl;
            cin >> idSource;
            cout << "Digite a seguir o numero do segundo vertice (destino): " << endl;
            cin >> idTarget;

            graph->dijkstra(idSource, idTarget, output_file);

            cout << "Caminho percorrido pelo algoritmo para encontrar o minimo entre os dois vertices usando Dijkstra foi inserido no arquivo de saida." << endl;

            break;
        }
        //Caminho mínimo entre dois vértices usando Floyd;
        case 4:{
            int idSource, idTarget;

            cout << "Selecionado: Caminho minimo entre dois vertices usando Floyd" << endl;
            cout << "Digite a seguir o id do primeiro vertice (origem): " << endl;
            cin >> idSource;
            cout << "Digite a seguir o id do segundo vertice (destino): " << endl;
            cin >> idTarget;

            graph->floydWarshall(idSource, idTarget, output_file);

            cout << "Caminho percorrido pelo algoritmo para encontrar o minimo entre os dois vertices usando Floyd foi inserido no arquivo de saida." << endl;

            break;
        }
        //Algoritmo de Prim;
        case 5:{
            /*int numVertices;
            int id;

            cout << "Selecionado: Algoritmo de Prim" << endl;
            cout << "Digite o número de vertices: " << endl;
            cin >> numVertices;

            vector<int> vertices;
            cout << "Digite cada vertice a seguir: " << endl;
            for(int i = 0; i < numVertices; i++) {
                cin >> id;
                vertices.push_back(id);
            }

            graph->algoritmoPrim(vertices);*/

            cout << "Algoritmo de Prim indisponivel." << endl;
            break;
        }
        //Algoritmo de Kruskal;
        case 6:{
            /*int numVertices;
            int id;

            cout << "Selecionado: Algoritmo de Kruskal" << endl;
            cout << "Digite o número de vertices: " << endl;
            cin >> numVertices;

            vector<int> vertices;
            cout << "Digite cada vertice a seguir: " << endl;
            for(int i = 0; i < numVertices; i++) {
                cin >> id;
                vertices.push_back(id);
            }

            graph->algoritmoKruskal(vertices);*/
            cout << "Algoritmo de Kruskal indisponivel." << endl;
            break;
        }
        //Busca em largura;
        case 7:{

            int id;
            cout << "Selecionado: Busca em largura" << endl;
            cout << "Digite o numero do vertice: ";
            cin >> id;

            graph->breadthFirstSearch(id, output_file);
            cout << "Busca em largura foi inserido no arquivo de saida." << endl;
            break;
        }
        //Ordenação Topologica;
       case 8:{
            graph->topologicalSorting();
            break;
        }
        case 0: {
            cout << "EXIT" << endl;
            break;
        }
        default:
        {
            cout << " Error!!! invalid option!!" << endl;
        }

    }
}

int mainMenu(ofstream& output_file, Graph* graph){

    int selecao = 1;

    while(selecao != 0){
        // system("clear");
        selecao = menu();

        if(output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;

    }

    return 0;
}

void leAlphas(float *alphas, ifstream& alphas_file) {
    for(int i = 0; i < 10; i++) {
        alphas_file >> alphas[i];
    }
}


int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    /*if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size()){
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1]);
    output_file.open(argv[2], ios::out);



    Graph* graph;

    if (input_file.is_open()) {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    } else cout << "Unable to open " << argv[1];


    mainMenu(output_file, graph);



    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();*/

    if(argc < 4){
        cout<<"Missing arguments!"<<endl;
        cout<<"Expected: at least 4"<<endl;
        cout<<"Given: "<<argc<<endl;
        return 1;
    }

    string executable(argv[0]);
    string nameOfFile(argv[1]);
    string instance;

    ifstream inputFile;
    ofstream result_file;
    ofstream result_file_greedy;
    ofstream result_file_random;

    inputFile.open(argv[1], ios::in);
    result_file.open("results.txt", ios::out|ios::app);

    result_file_greedy.open("results_Greedy.txt", ios::out|ios::app);
    result_file_random.open("results_Random.txt", ios::out|ios::app);

    Graph *graph;
    Solution *solution;
    float *alphas = new float[10];

    graph = readingProblemInstance(inputFile, 0, 0, 1);


    if(graph != nullptr){
        if(atoi(argv[2]) == 0){
            // chamar o algoritmo guloso


            solution = graph->greedy();

            result_file_greedy<<"Solution"<<endl;
            solution->printClustersInSolution(result_file_greedy);
            result_file_greedy << "Qualidade da solução: ";

            result_file_greedy << solution->getTotalGAP() << endl;
        }
        else if(atoi(argv[2]) == 1){
            cout<<"\nExecuting algorithm\n"<<endl;
            // chamar o algoritmo guloso reativo
            solution = graph->greedyRandom(atof(argv[4]), atoi(argv[3]));
            cout<<"\nAlgorithm executed\n"<<endl;
            result_file_random<<"Solution"<<endl;
            solution->printClustersInSolution(result_file_random);
            result_file_random << "Qualidade da solução: ";

            result_file_random << solution->getTotalGAP() << endl;
        }
        else if(atoi(argv[2]) == 2){
            // chamar o algoritmo guloso reativo randomizado

            ifstream alphas_file;
            alphas_file.open(argv[4]);
            leAlphas(alphas, alphas_file);
            for(int i = 0; i < 10; i++)
                cout << alphas[i] << " ";
            solution = graph->greedReactiveRandom(alphas, atoi(argv[3]), 10, 10);
            alphas_file.close();
            result_file<<"Solution"<<endl;
            solution->printClustersInSolution(result_file);
            result_file << "Qualidade da solução: ";

            result_file << solution->getTotalGAP() << endl;
        }
        else{
            cout<<"Error: missing parameter!"<<endl;
        }
    }
    else{
        cout<<"Error: Graph was not initialized!"<<endl;
        return 1;
    }

    inputFile.close();
    result_file.close();

    delete graph;
    delete solution;
    delete alphas;

    return 0;
}

