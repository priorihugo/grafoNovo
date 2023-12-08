#include "../includes/Solucao.h"

Solucao::Solucao()
{
    this->rotas = new vector<Rota*>();
}

Solucao::Solucao(int tamanho , int capacidade)
{
    this->rotas = new vector<Rota*>();
    this->rotas->resize(tamanho);

    for(size_t i = 0 ; i < this->rotas->size() ; i++){
        this->rotas->at(i) = new Rota(capacidade);
    }
}

Solucao::~Solucao()
{
    //dtor
}

float Solucao::getQualidade(){
    float total = 0;
    for(size_t i = 0 ; i < this->rotas->size() ; i ++){
        total += rotas->at(i)->getCusto();
    }
    return total;

}

Rota* Solucao::getRota(int index){
    return this->rotas->at(index);
}



void Solucao::imprime(){

    for (size_t j = 0; j < this->rotas->size(); j++)
    {
        Rota* rotaimprime = this->getRota(j);
        cout << "[" << j <<"]";
        rotaimprime->imprime();
    }
    cout <<"Qualidade: " << this->getQualidade() << endl;
}

string Solucao::getParaTXT(){

    stringstream ss;
    
    for (size_t j = 0; j < this->rotas->size(); j++)
    {
        Rota* rotaimprime = this->getRota(j);
        ss << "[" << j <<"]";
        ss << rotaimprime->getParaTXT();
    }
    ss << "Qualidade: " << this->getQualidade() << endl;

    return ss.str();
}