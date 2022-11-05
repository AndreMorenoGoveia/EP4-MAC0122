#include <stdio.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0
#define preto 1
#define azul -1



/* Função que printa uma representação do tabuleiro em seu estado */
void print_tab(int*** tab, int n);



/* Função que encaixa um elemento na matriz de acordo com as posições fornecidas*/
void encaixa(int*** tab, int lin, int col, int cor);



/* Função que escolhe a jogada de acordo com o estado do tabuleiro*/
int escolheJogada(int*** tab, int n, int cor, int *lin, int *col);



/* Função que confere se alguém ganhou e quem ganhou*/
char ganhou(int*** tab, int n, int lin, int col);


/* Função que detecta se o tabuleiro está cheio */
bool encheu(int*** tab, int n);





int main(void){

    int i, j, k;
    int n;
    int*** tab;
    int lin, col;
    char buffer[6];
    int cor;
    int g;
    bool b = true;


    printf("Digite o tamanho do tabuleiro\n");
    scanf("%d", &n);

    printf("Digite a cor que voce deseja jogar(preto ou azul)\n");
    scanf("%s", buffer);
    cor = buffer[1] == 'z' ? -1 : 1;


    /* Aloca memória dinamicamente para a matriz tridimensional */
    tab = (int***) malloc(n*sizeof(int**));

    for(i = 0; i < n; i++){

        tab[i] = (int**) malloc(n*sizeof(int*));

        for(j = 0; j < n; j++)
            tab[i][j] = (int*) calloc(n, sizeof(int));

    }

    if(cor == -1){
        escolheJogada(tab, n, preto, &lin, &col);
        encaixa(tab, lin, col, preto);
        print_tab(tab, n);
    }

    while(b){

        printf("Qual eh a sua proxima jogada (linha, coluna)?\n");
        scanf("%d %d", &lin, &col);

        encaixa(tab, lin, col, cor);
        g = ganhou(tab, n, lin, col);
        if(g == preto){
            print_tab(tab, n);
            printf("O preto venceu!!!\n");
            break;
        }
        else if(g == azul){
            print_tab(tab, n);
            printf("O azul venceu!!!\n");
            break;
        }

        if(escolheJogada(tab, n, cor*(-1), &lin, &col) == n){

            b = false;

            g = ganhou(tab, n, lin, col);
            if(g == preto)
                printf("O preto venceu!!!\n");
            else if(g == azul)
                printf("O azul venceu!!!\n");
            else
                printf("Deu Velha!!!\n");

        }
        else{

            encaixa(tab, lin, col, cor*(-1));
            print_tab(tab, n);
            if(encheu(tab, n)){
                printf("Deu Velha!!!\n");
                b = false;
            }

        }

    }


    return 0;

}



void print_tab(int*** tab, int n){

    int i, j, k, l;

    printf("\n");

    for(i = 0; i < n; i++){


        


        for(k = n - 1; k >= 0; k--){

            for(j = 0; j < i; j++)
                for(l = 0; l <= n; l++)
                    printf("  ");


            for(j = 0; j < n; j++){
        
                if(tab[i][j][k] == 1)
                    printf("X ");

                else if(tab[i][j][k] == -1)
                    printf("O ");

                else
                    printf("  ");

            }

            printf("\n");

        }
        for(j = 0; j < i; j++)
            for(l = 0; l <= n; l++)
                printf("  ");
        for(j = 0; j < n; j++)
            printf("# ");
        printf("\n");

    }

}



void encaixa(int*** tab, int lin, int col, int cor){

    int k = 0;
    while(tab[lin][col][k] != 0) k++;

    tab[lin][col][k] = cor;

}



bool ganhou(int*** tab, int n, int lin, int col){

    int i, j, k, alt, cor_atual;

    for(alt = 0; alt < n && tab[lin][col][alt]; alt++);
    alt--;


    cor_atual = tab[lin][col][alt];

    /* Eixo x */
    for(i = 0; i < n; i++)
        if(tab[i][col][alt] != cor_atual)
            i = n;
    
    if(i == n)
        return cor_atual;

    /* Eixo y */
    for(i = 0; i < n; i++)
        if(tab[lin][i][alt] != cor_atual)
            i = n;
    
    if(i == n)
        return cor_atual;

    /* Eixo z */
    if(alt == n - 1){
        for(i = alt; i >= 0; i--)
            if(tab[lin][col][i] != cor_atual)
                i = -1;
        
        if(i == -1)
            return cor_atual;
    }

    /* Diagonais plano xy */
    if(lin == col){

        for(i = 0, j = 0; i < n; i++, j++)
            if(tab[i][j][alt] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }
    if(lin + col == n - 1){

        for(i = 0, j = n-1; i < n; i++, j--)
            if(tab[i][j][alt] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }

    /* Diagonais plano xz*/
    if(lin == alt){

        for(i = 0, j = 0; i < n; i++, j++)
            if(tab[i][col][j] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }
    if(lin + alt == n - 1){

        for(i = 0, j = n-1; i < n; i++, j--)
            if(tab[i][col][j] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }

    /* Diagonais plano yz*/
    if(col == alt){

        for(i = 0, j = 0; i < n; i++, j++)
            if(tab[lin][i][j] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }
    if(alt + col == n - 1){

        for(i = 0, j = n-1; i < n; i++, j--)
            if(tab[lin][i][j] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }

    /* Diagonais planos xyz */
    if(lin == col && col == alt){

        for(i = 0, j = 0, k = 0; i < n; i++, j++, k++)
            if(tab[i][j][k] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }
    if(lin + col == n - 1 && lin + alt == n - 1){

        for(i = n - 1, j = 0, k = 0; i < n; i--, j++, k++)
            if(tab[i][j][k] != cor_atual)
                j = n;

        if(j == n)
            return cor_atual;

    }
    if(col + lin == n - 1 && col + alt == n - 1){

        for(i = 0, j = n - 1, k = 0; i < n; i++, j--, k++)
            if(tab[i][j][k] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }
    if(alt + lin == n - 1 && alt + col == n - 1){

        for(i = 0, j = 0, k = n - 1; i < n; i++, j++, k--)
            if(tab[i][j][k] != cor_atual)
                i = n;

        if(i == n)
            return cor_atual;

    }

    return 0;

}



bool encheu(int*** tab, int n){

    int i, j;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(tab[i][j][n-1] == 0)
                return false;

    return true;

}

int escolheJogada(int*** tab, int n, int cor, int *lin, int *col){

    *lin = 0;
    *col = 0;
    return 0;


}