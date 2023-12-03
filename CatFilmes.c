#include "TARVBFM.h"

//Função p/ ler arquivo.txt e colocando os elemtos do tipo TFM* na árvore B;
TARVB* arquivotxt_p_arvb(TARVB *a, int t, char* filmes){
    FILE *fp = fopen(filmes, "r");
    if(!fp) return NULL;
    char nome[81], diretor[51], genero[31];
    int lancamento, duracao;
    int l1, ch;
    TFM *novof;
    while(1){
        l1 = fscanf(fp, " %80[^/]/%d/%50[^/]/%30[^/]/%d\n", nome, &lancamento, diretor, genero, &duracao);
        if(l1!=5) break;
        ch = hash_filme(nome, lancamento);
        novof = cria_filme(nome, diretor, genero, lancamento, duracao);
        a = TARVB_Insere(a, ch, novof, t);
    }
    fclose(fp);
    return a;
}

//Retorna todos os elementos da arvore em um vetor;
TFM** arv_p_vat(TARVB *a, TFM** vetf, int *tam){
    if(a){
        int i;
        for(i=0; i<=a->nchaves-1; i++){
            vetf = arv_p_vat(a->filho[i], vetf, tam);
            (*tam)++;
            vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));
            vetf[(*tam)-1] = a->filmes[i];
        }
        return vetf = arv_p_vat(a->filho[i], vetf, tam);
    }
    return vetf;
}


/*Funções p/ resolver os casos pedidos*/
//num == 1. leitura de TFM* diretamente do terminal.
TFM* scanfilme(){
    TFM* novo = (TFM*)malloc(sizeof(TFM));
    char titulo[81], diretor[51], genero[31];
    int lancamento, duracao;
    printf("Digite o nome do filme:\n");
    scanf(" %80[^\n]", titulo);
    printf("Digite o ano de lancamento:\n");
    scanf("%d", &lancamento);
    printf("Digite o nome do diretor:\n");
    scanf(" %50[^\n]", diretor);
    printf("Digite o genero do filme:\n");
    scanf(" %30[^\n]", genero);
    printf("Digite a duracao em minutos:\n");
    scanf("%d", &duracao);
    strcpy(novo->titulo, titulo);
    novo->lancamento = lancamento;
    strcpy(novo->diretor, diretor);
    strcpy(novo->genero, genero);
    novo->duracao = duracao;
    return novo;
}

//num==3: Altera ou não campos especificos de um TFM* ja existente.
TFM* altera_campos(TFM *f){
    char titulo[81], diretor[51], genero[31];
    int lancamento, duracao;
    printf("\nCaso deseje alterar um campo digete a nova info caso contrario digite -1\n");
    printf("Digite o nome do filme:\n");
    scanf(" %80[^\n]", titulo);
    printf("Digite o ano de lancamento:\n");
    scanf("%d", &lancamento);
    printf("Digite o nome do diretor:\n");
    scanf(" %50[^\n]", diretor);
    printf("Digite o genero do filme:\n");
    scanf(" %30[^\n]", genero);
    printf("Digite a duracao em minutos:\n");
    scanf("%d", &duracao);
    if(strcmp(titulo, "-1") != 0) strcpy(f->titulo, titulo);
    if(lancamento != -1) f->lancamento = lancamento;
    if(strcmp(diretor, "-1") != 0) strcpy(f->diretor, diretor);
    if(strcmp(genero, "-1") != 0) strcpy(f->genero, genero);
    if(duracao != -1) f->duracao = duracao;
    return f;
}

//num == 4 || 5; Percorre a arvore procurando os filmes de um diretor especifico retorna um vertor de TFM*;
TFM** busca_diretor(TARVB *a, TFM** vetf, char* diretor, int *tam){
    if(!a) return vetf;
    if(!a->folha){
        int i;
        for(i=0;i<a->nchaves;i++){
            if(a->filho[i]) vetf = busca_diretor(a->filho[i], vetf, diretor, tam);
            if(strcmp(a->filmes[i]->diretor, diretor) == 0){ //verificação se filme é do diretor pedido.
                (*tam)++;
                vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));
                vetf[(*tam)-1] = a->filmes[i];
            }
        }
        vetf = busca_diretor(a->filho[i], vetf, diretor, tam);
    } else{
        int i;
        for(i=0;i<a->nchaves;i++){
            if(strcmp(a->filmes[i]->diretor, diretor) == 0){
                (*tam)++;
                vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));
                vetf[(*tam)-1] = a->filmes[i];
            }
        }
    }
    return vetf;
}

/*num == 6. Percorre a ávore procurando o todos os filmes de um determinado
genero inclusive os de com mais de um genero*/
TFM** busca_genero(TARVB *a, TFM** vetf, char* genero, int *tam){
    if(!a) return vetf;
    if(!a->folha){
        int i;
        for(i=0;i<a->nchaves;i++){
            if(a->filho[i]) vetf = busca_genero(a->filho[i], vetf, genero, tam);
            char gen[31];
            strcpy(gen, a->filmes[i]->genero);
            int ini=0, fim, cm = strlen(gen);
            for(fim=0;fim<cm;fim++){
                if((strncmp(&gen[fim], " | ", 3) == 0)||(fim == cm-1)){//verificação se achou um genero caso exita mais de um
                    if(strcmp(&gen[ini], genero) == 0){//compara o genero encontrado com o genero pedido.
                        (*tam)++;
                        vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));//guarda no vetor caso o mesmo filme tenha mais de 1 genero so verifica até achar.
                        vetf[(*tam)-1] = a->filmes[i];        
                        break;
                    }
                    ini = fim + 3;
                }
            }
        }
        vetf = busca_genero(a->filho[i], vetf, genero, tam);
    } else{
        int i;
        for(i=0;i<a->nchaves;i++){
            char gen[31];
            strcpy(gen, a->filmes[i]->genero);
            int ini=0, fim, cm = strlen(gen);
            for(fim=0;fim<cm;fim++){
                if((strncmp(&gen[fim], " | ", 3) == 0)||(fim == cm-1)){
                    if(strcmp(&gen[ini], genero) == 0){
                        (*tam)++;
                        vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));
                        vetf[(*tam)-1] = a->filmes[i];        
                        break;
                    }
                    ini = fim + 3;
                }
            }
        }
    }
    return vetf;
}

//num==7. Percorre a arvore procurando todos os filmes de uma franquia.
TFM** busca_franquia(TARVB *a, TFM** vetf, char* franquia, int *tam){
    if(!a) return vetf;
    if(!a->folha){
        int i;
        for(i=0;i<a->nchaves;i++){
            if(a->filho[i]) vetf = busca_franquia(a->filho[i], vetf, franquia, tam);
            char fram[81];
            int ini = 0, fim, cm = strlen(a->filmes[i]->titulo);//percorre pelo nome do filme até bater com a franquia ou acabar.
            for(fim=1;fim<cm;fim++){
                strncpy(fram, a->filmes[i]->titulo, fim);
                fram[fim+1] = '\0';
                if(strcmp(franquia, fram)==0){
                    (*tam)++;
                    vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));//adiciona no vetor e segue em frente.
                    vetf[(*tam)-1] = a->filmes[i];        
                    break;
                }
            }
        }
        vetf = busca_franquia(a->filho[i], vetf, franquia, tam);
    }else{
        int i;
        for(i=0;i<a->nchaves;i++){
            char fram[81];
            int ini=0, fim, cm = strlen(a->filmes[i]->titulo);
            for(fim=1;fim<cm;fim++){
                strncpy(fram, a->filmes[i]->titulo, fim);
                fram[fim+1] = '\0';
                if(strcmp(franquia, fram)==0){
                    (*tam)++;
                    vetf = (TFM**)realloc(vetf, sizeof(TFM*)*(*tam));
                    vetf[(*tam)-1] = a->filmes[i];        
                    break;
                }
            }
        }
    }
    return vetf;
}

int main(void){
    char arquivo[21];
    TARVB *arvore = TARVB_Inicializa();
    int t;
    printf("Digite o caminho do arquivo .txt do catalogo de filmes:\n");
    scanf(" %20[^\n]", arquivo);
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    arvore = TARVB_Cria(t);
    arvore = arquivotxt_p_arvb(arvore, t, arquivo);
    printf("\n\tDigite\t\n0: p/ insercao\n1: p/ remocao\n2: p/ busca\n3: alteracao de info subordinada\n4: Buscar todos os filmes de um diretor\n");
    printf("5: Retirada de todos os filmes de um diretor\n6: Retira todos os filmes do mesmo genero\n7: Remove todos os filmes de uma franquia\n<0 :encerrar\n");
    scanf("%d",&num);
    TFM** vetf = NULL;
    while (num >=0){//obs: modificaçoes no arquivo somente quando encerrar o programa.
        if(num == 0){
            TFM* f = scanfilme();
            int Hs = hash_filme(f->titulo, f->lancamento);
            arvore = TARVB_Insere(arvore, Hs, f, t);
        }
        else if(num == 1){
            char titulo[81];
            int lancamento, Hs;
            printf("\nDigite o titulo e o ano de lancamento do filme/serie respc. que sera removido:\n");
            scanf(" %80[^\n]", titulo);
            scanf("%d", &lancamento);
            Hs = hash_filme(titulo, lancamento);
            arvore = TARVB_Retira(arvore, Hs, t);
            //Remoção no arquivo .txt sera feita no fim quando a arvore é carrega de volta p/ o arquivo.
        }else if(num == 2){
            char titulo[81];
            int lancamento, Hs, pos;
            printf("\nDigite o titulo e o ano de lancamento do filme/serie respc. que sera removido:\n");
            scanf(" %80[^\n]", titulo);
            scanf("%d", &lancamento);
            Hs = hash_filme(titulo, lancamento);
            TARVB *tmp = Busca_filmes(arvore, Hs, &pos);
            if(tmp) imprime_filme(tmp->filmes[pos]);
            else printf("Não Encontrado Tente novamente\n");
        }else if(num == 3){
            //Busca elem ma arvb, modifica elem, remove versão antiga da arvb, e adiciona a versão nova; assim chaves podem ser modificadas.
            char titulo[81];
            int lancamento, Hs, pos;
            printf("\nDigite o titulo e o ano de lancamento do filme/serie respc. que sera removido:\n");
            scanf(" %80[^\n]", titulo);
            scanf("%d", &lancamento);
            Hs = hash_filme(titulo, lancamento);
            TARVB *tmp = Busca_filmes(arvore, Hs, &pos);
            if(tmp){
                TFM *f = tmp->filmes[pos];
                f = altera_campos(f);
                arvore = TARVB_Retira(arvore, Hs, t);
                Hs = hash_filme(f->titulo, f->lancamento);
                arvore = TARVB_Insere(arvore, Hs, f, t);
            }else printf("Não encontrado tente novamente\n");
        }else if(num == 4){
            char diretor[51];
            printf("Digite o nome do Diretor\n");
            scanf(" %50[^\n]", diretor);
            int tam = 0, i;
            vetf = busca_diretor(arvore, vetf, diretor, &tam);
            if(tam > 0){
                for(i=0;i<tam;i++) imprime_filme(vetf[i]);
            }else printf("Nenhum filme encontrado tente novamente\n");

        }else if(num == 5){
            char diretor[51];
            printf("Digite o nome do Diretor\n");
            scanf(" %50[^\n]", diretor);
            int tam = 0, i, Hs;
            vetf = busca_diretor(arvore, vetf, diretor, &tam);
            if(tam > 0){
                for(i=0;i<tam;i++){
                    imprime_filme(vetf[i]);
                    Hs = hash_filme(vetf[i]->titulo, vetf[i]->duracao);
                    arvore = TARVB_Retira(arvore, Hs, t);
                }
                printf("Foram removidos\n");
            }else printf("Nenhum filme encontrado tente novamente\n");

        }else if(num==6){
            char genero[31];
            printf("Digite o Genero\n");
            scanf(" %30[^\n]", genero);
            int tam = 0, i, Hs;
            vetf = busca_genero(arvore, vetf, genero, &tam);
            if(tam >0){    
                for(i=0;i<tam;i++){
                    imprime_filme(vetf[i]);
                    Hs = hash_filme(vetf[i]->titulo, vetf[i]->lancamento);
                    arvore = TARVB_Retira(arvore, Hs, t);
                }
                printf("\tForam Removidos\n");
            }else printf("Nenhum filme encontrado tente novamente\n");
        }else if(num == 7){
            char franquia[81];
            printf("Digite a franquia\n");
            scanf(" %80[^\n]", franquia);
            int tam = 0, i, Hs;
            vetf = busca_franquia(arvore, vetf, franquia, &tam);
            if(tam >0){
                for(i=0;i<tam;i++){
                    imprime_filme(vetf[i]);
                    Hs = hash_filme(vetf[i]->titulo, vetf[i]->lancamento);
                    arvore = TARVB_Retira(arvore, Hs, t);
                }
                printf("\tForam Removidos\n");
            }else printf("Nenhum filme encontrado tente novamente\n");
        }else{
            printf("Digite algo valido\n");
        }
        printf("\n\tDigite\t\n0: p/ insercao\n1: p/ remocao\n2: p/ busca\n3: alteracao de info subordinada\n4: Buscar todos os filmes de um diretor\n");
        printf("5: Retirada de todos os filmes de um diretor\n6: Retira todos os filmes do mesmo genero\n7: Remove todos os filmes de uma franquia\n<0 :encerrar\n");
        scanf("%d",&num);
    }
    
    //Reescreve os elementos da arvore no txt;
    int i,l1,tam=0;
    vetf = arv_p_vat(arvore, vetf, &tam);
    FILE *fp = fopen(arquivo, "w");
    if(!fp){
        printf("\nERRO AO ABRIR ARQUIVO\n");
        return 1;
    }
    for(i=0;i<tam;i++){
        l1 = fprintf(fp, "%s/%d/%s%s/%d\n", vetf[i]->titulo, vetf[i]->lancamento, vetf[i]->diretor, vetf[i]->genero, vetf[i]->duracao);
    }
    fclose(fp);

    //TARVB_Imprime(arvore);
    free(vetf);
    TARVB_Libera(arvore);
    return 0;
}