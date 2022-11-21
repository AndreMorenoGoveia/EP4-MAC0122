#include <stdio.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0
#define preto 1
#define azul -1

/* Função que printa uma representação do tabuleiro em seu estado */
void print_tab(int ***tab, int n);

/* Função que encaixa um elemento na matriz de acordo com as posições fornecidas*/
void encaixa(int ***tab, int lin, int col, int cor);

/* Função que escolhe a jogada de acordo com o estado do tabuleiro*/
int escolheJogada(int ***tab, int n, int cor, int *lin, int *col);

/* Função que confere se alguém ganhou e quem ganhou*/
char ganhou(int ***tab, int n, int lin, int col);

/* Função que detecta se o tabuleiro está cheio */
bool encheu(int ***tab, int n);

int main(void)
{

    int i, j, k;
    int n;
    int ***tab;
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
    tab = (int ***)malloc(n * sizeof(int **));

    for (i = 0; i < n; i++)
    {

        tab[i] = (int **)malloc(n * sizeof(int *));

        for (j = 0; j < n; j++)
            tab[i][j] = (int *)calloc(n, sizeof(int));
    }

    if (cor == -1)
    {
        escolheJogada(tab, n, preto, &lin, &col);
        encaixa(tab, lin, col, preto);
        print_tab(tab, n);
    }

    while (b)
    {

        printf("Qual eh a sua proxima jogada (linha, coluna)?\n");
        scanf("%d %d", &lin, &col);

        encaixa(tab, lin, col, cor);
        g = ganhou(tab, n, lin, col);
        if (g == preto)
        {
            print_tab(tab, n);
            printf("O preto venceu!!!\n");
            break;
        }

        else if (g == azul)
        {
            print_tab(tab, n);
            printf("O azul venceu!!!\n");
            break;
        }

        if (escolheJogada(tab, n, cor * (-1), &lin, &col) == n)
        {

            b = false;

            g = ganhou(tab, n, lin, col);
            if (g == preto)
                printf("O preto venceu!!!\n");
            else if (g == azul)
                printf("O azul venceu!!!\n");
            else
                printf("Deu Velha!!!\n");
        }
        else
        {

            encaixa(tab, lin, col, cor * (-1));
            print_tab(tab, n);
            g = ganhou(tab, n, lin, col);
            if (g == preto)
            {
                printf("O preto venceu!!!\n");
                b = false;
            }

            else if (g == azul)
            {
                printf("O azul venceu!!!\n");
                b = false;
            }

            if (encheu(tab, n))
            {
                printf("Deu Velha!!!\n");
                b = false;
            }
        }
    }

    return 0;
}

void print_tab(int ***tab, int n)
{

    int i, j, k, l;

    printf("\n");

    for (i = 0; i < n; i++)
    {

        for (k = n - 1; k >= 0; k--)
        {

            for (j = 0; j < i; j++)
                for (l = 0; l <= n; l++)
                    printf(" ");

            for (j = 0; j < n; j++)
            {

                if (tab[i][j][k] == 1)
                    printf("X ");

                else if (tab[i][j][k] == -1)
                    printf("O ");

                else
                    printf("  ");
            }

            printf("\n");
        }

        for (j = 0; j < i; j++)
            for (l = 0; l <= n; l++)
                printf(" ");
        for (j = 0; j < n; j++)
            printf("# ");
        printf("\n");
    }
}

void encaixa(int ***tab, int lin, int col, int cor)
{

    int k = 0;
    while (tab[lin][col][k] != 0)
        k++;

    tab[lin][col][k] = cor;
}

bool ganhou(int ***tab, int n, int lin, int col)
{

    int i, j, k, alt, cor_atual;

    for (alt = 0; alt < n && tab[lin][col][alt]; alt++)
        ;
    alt--;

    cor_atual = tab[lin][col][alt];

    /* Eixo x */
    for (i = 0; i < n; i++)
        if (tab[i][col][alt] != cor_atual)
            i = n;

    if (i == n)
        return cor_atual;

    /* Eixo y */
    for (i = 0; i < n; i++)
        if (tab[lin][i][alt] != cor_atual)
            i = n;

    if (i == n)
        return cor_atual;

    /* Eixo z */
    if (alt == n - 1)
    {
        for (i = alt; i >= 0; i--)
            if (tab[lin][col][i] != cor_atual)
                i = -1;

        if (i == -1)
            return cor_atual;
    }

    /* Diagonais plano xy */
    if (lin == col)
    {

        for (i = 0, j = 0; i < n; i++, j++)
            if (tab[i][j][alt] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    if (lin + col == n - 1)
    {

        for (i = 0, j = n - 1; i < n; i++, j--)
            if (tab[i][j][alt] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    /* Diagonais plano xz*/
    if (lin == alt)
    {

        for (i = 0, j = 0; i < n; i++, j++)
            if (tab[i][col][j] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    if (lin + alt == n - 1)
    {

        for (i = 0, j = n - 1; i < n; i++, j--)
            if (tab[i][col][j] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    /* Diagonais plano yz*/
    if (col == alt)
    {

        for (i = 0, j = 0; i < n; i++, j++)
            if (tab[lin][i][j] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    if (alt + col == n - 1)
    {

        for (i = 0, j = n - 1; i < n; i++, j--)
            if (tab[lin][i][j] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    /* Diagonais xyz */
    if (lin == col && col == alt)
    {

        for (i = 0, j = 0, k = 0; i < n; i++, j++, k++)
            if (tab[i][j][k] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }
    if (lin + col == n - 1 && lin + alt == n - 1)
    {

        for (i = n - 1, j = 0, k = 0; j < n; i--, j++, k++)
            if (tab[i][j][k] != cor_atual)
                j = n;

        if (j == n)
            return cor_atual;
    }
    if (col + lin == n - 1 && col + alt == n - 1)
    {

        for (i = 0, j = n - 1, k = 0; i < n; i++, j--, k++)
            if (tab[i][j][k] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }
    if (alt + lin == n - 1 && alt + col == n - 1)
    {

        for (i = 0, j = 0, k = n - 1; i < n; i++, j++, k--)
            if (tab[i][j][k] != cor_atual)
                i = n;

        if (i == n)
            return cor_atual;
    }

    return 0;
}

bool encheu(int ***tab, int n)
{

    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (tab[i][j][n - 1] == 0)
                return false;

    return true;
}

int escolheJogada(int ***tab, int n, int cor, int *lin, int *col){

    const int ataque = 50;
    const int defesa = 50;
    const int abertura = 50;

    int i, j, k, i0, j0, k0;
    int **pontos;
    int pontMax;
    int somaAtual;
    int h;
    int atual = cor * (-1);
    int meus, dele;

    /* Aloca a memória do sistema de pontuações*/
    pontos = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        pontos[i] = (int *)calloc(n, sizeof(int));

    /* Confere se há impossibilidades de jogada */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (tab[i][j][n - 1])
                pontos[i][j] = -2;

    /* Parte principal do código */
    for (i = 0; i < n; i++){

        for (j = 0; j < n; j++){

            if (!pontos[i][j]){

                /* Mede a altura do elemento */
                for (h = 0; tab[i][j][h]; h++);

                /******************************
                Pontua para os melhores locais
                *******************************/
                if (pontos[i][j] == 0){

                    /*** Eixo x ***/
                    meus = 0;
                    dele = 0;

                    for (i0 = 0; i0 < n; i0++){

                        if (tab[i0][j][h] == cor)
                            meus++;

                        else if (tab[i0][j][h] == cor * (-1))
                            dele++;

                    }

                    /* Confirma vitoria */
                    if (meus == n - 1){

                        *lin = i;
                        *col = j;

                        for (i = 0; i < n; i++)
                            free(pontos[i]);
                        free(pontos);

                        return 0;

                    }


                    /* Evita derrota */
                    if (dele == n - 1)
                        pontos[i][j] = n * 6000;


                    /* Pontos de ataque */
                    if (meus > 0 && dele == 0)
                        pontos[i][j] += ataque * meus;


                    /* Pontos de defesa */
                    if (dele > 0 && meus == 0)
                        pontos[i][j] += defesa * dele;
                    

                    /* Pontos de aberturas */
                    if (dele == 0 && meus == 0)
                        pontos[i][j] += abertura * n;


                    /*** Eixo y ***/
                    meus = 0;
                    dele = 0;

                    for (j0 = 0; j0 < n; j0++){

                        if (tab[i][j0][h] == cor)
                            meus++;

                        else if (tab[i][j0][h] == cor * (-1))
                            dele++;
                    }

                    /* Confirma vitoria */
                    if (meus == n - 1){

                        *lin = i;
                        *col = j;

                        for (i = 0; i < n; i++)
                            free(pontos[i]);
                        free(pontos);

                        return 0;

                    }

                    /* Evita derrota */
                    if (dele == n - 1){

                        pontos[i][j] = n * 6000;
                        continue;

                    }

                    /* Pontos de ataque */
                    if (meus > 0 && dele == 0)
                        pontos[i][j] += ataque * meus;
                    

                    /* Pontos de defesa */
                    if (dele > 0 && meus == 0)
                        pontos[i][j] += defesa * dele;


                    /* Pontos de aberturas */
                    if (dele == 0 && meus == 0)
                        pontos[i][j] += abertura * n;


                    /*** Eixo z ***/
                    meus = 0;
                    dele = 0;

                    for (k0 = h; k0 >= 0; k0--){

                        if (tab[i][j][k0] == cor)
                            meus++;

                        else if (tab[i][j][k0] == cor * (-1))
                            dele++;

                    }

                    /* Confirma vitoria */
                    if (meus == n - 1){

                        *lin = i;
                        *col = j;

                        for (i = 0; i < n; i++)
                            free(pontos[i]);
                        free(pontos);

                        return 0;

                    }

                    /* Evita derrota */
                    if (dele == n - 1){

                        pontos[i][j] = n * 6000;
                        continue;

                    }

                    /* Pontos de ataque */
                    if (meus > 0 && dele == 0)
                        pontos[i][j] += ataque * meus;


                    /* Pontos de defesa */
                    if (dele > 0 && meus == 0)
                        pontos[i][j] += defesa * dele;
                    

                    /* Pontos de aberturas */
                    if (dele == 0 && meus == 0)
                        pontos[i][j] += abertura * n;
            


                    /*** Diagonais plano xy ***/
                    /** Diagonal 1 **/
                    if (i == j){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, j0 = 0; i0 < n; i0++, j0++){

                            if (tab[i0][j0][h] == cor)
                                meus++;

                            else if (tab[i0][j0][h] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;


                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                    
                    }

                    /** Diagonal 2 **/
                    if (i + j == n - 1){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, j0 = n - 1; i0 < n; i0++, j0--){

                            if (tab[i0][j0][h] == cor)
                                meus++;

                            else if (tab[i0][j0][h] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }

                    /*** Diagonais plano xz ***/
                    /** Diagonal 1 **/
                    if (i == h){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, k0 = 0; i0 < n; i0++, k0++){

                            if (tab[i0][j][k0] == cor)
                                meus++;

                            else if (tab[i0][j][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;


                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;

                    }

                    /** Diagonal 2 **/
                    if (i + h == n - 1){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, k0 = n - 1; i0 < n; i0++, k0--){

                            if (tab[i0][j][k0] == cor)
                                meus++;

                            else if (tab[i0][j][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;

                    }

                    /*** Diagonais plano yz ***/
                    /** Diagonal 1 **/
                    if (j == h){

                        meus = 0;
                        dele = 0;

                        for (j0 = 0, k0 = 0; j0 < n; j0++, k0++){

                            if (tab[i][j0][k0] == cor)
                                meus++;

                            else if (tab[i][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;


                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }

                    /** Diagonal 2 **/
                    if (j + h == n - 1){

                        meus = 0;
                        dele = 0;

                        for (j0 = 0, k0 = n - 1; j0 < n; j0++, k0--){

                            if (tab[i][j0][k0] == cor)
                                meus++;

                            else if (tab[i][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }

                    /*** Diagonais xyz ***/
                    /** Diagonal 1 **/
                    if (i == j && j == h){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, j0 = 0, k0 = 0; j0 < n; i0++, j0++, k0++){

                            if (tab[i0][j0][k0] == cor)
                                meus++;

                            else if (tab[i0][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }


                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;

                    }

                    /** Diagonal 2 **/
                    if (i + j == n - 1 && i + h == n - 1){

                        meus = 0;
                        dele = 0;

                        for (i0 = n - 1, j0 = 0, k0 = 0; j0 < n; i0--, j0++, k0++){

                            if (tab[i0][j0][k0] == cor)
                                meus++;

                            else if (tab[i0][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;


                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }

                    /** Diagonal 3 **/
                    if (j + i == n - 1 && j + h == n - 1){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, j0 = n - 1, k0 = 0; i0 < n; i0++, j0--, k0++){

                            if (tab[i0][j0][k0] == cor)
                                meus++;

                            else if (tab[i0][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }

                    /** Diagonal 4 **/
                    if (h + i == n - 1 && h + j == n - 1){

                        meus = 0;
                        dele = 0;

                        for (i0 = 0, j0 = 0, k0 = n - 1; i0 < n; i0++, j0++, k0--){

                            if (tab[i0][j0][k0] == cor)
                                meus++;

                            else if (tab[i0][j0][k0] == cor * (-1))
                                dele++;

                        }

                        /* Confirma vitoria */
                        if (meus == n - 1){

                            *lin = i;
                            *col = j;

                            for (i = 0; i < n; i++)
                                free(pontos[i]);
                            free(pontos);

                            return 0;

                        }

                        /* Evita derrota */
                        if (dele == n - 1){

                            pontos[i][j] = n * 6000;
                            continue;

                        }

                        /* Pontos de ataque */
                        if (meus > 0 && dele == 0)
                            pontos[i][j] += ataque * meus;
                        

                        /* Pontos de defesa */
                        if (dele > 0 && meus == 0)
                            pontos[i][j] += defesa * dele;
                        

                        /* Pontos de aberturas */
                        if (dele == 0 && meus == 0)
                            pontos[i][j] += abertura * n;
                        
                    }
                }
            }


            /***********************************************
            Confere se sua jogada não vai entregar a vitória
            ***********************************************/
            if (h < n - 1 && pontos[i][j] < 6000*n && pontos[i][j] > -2){

                /* Horizontal */
                for (i0 = 0; i0 < n; i0++)
                    if (tab[i0][j][h + 1] != cor * (-1) && i0 != i)
                        i0 = n;

                if (i0 == n){

                    pontos[i][j] = -1;
                    continue;

                }

                /* Vertical */
                for (j0 = 0; j0 < n; j0++)
                    if (tab[i][j0][h + 1] != cor * (-1) && j0 != j)
                        j0 = n;

                if (j0 == n){
        
                    pontos[i][j] = -1;
                    continue;

                }

                /* Diagonal plano xy */
                if (i == j){

                    for (i0 = 0, j0 = 0; i0 < n; i0++, j0++)
                        if (tab[i0][j0][h + 1] != cor * (-1) && i0 != i)
                            i0 = n;

                    if (i0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (i + j == n - 1){

                    for (i0 = 0, j0 = n - 1; i0 < n; i0++, j0--)
                        if (tab[i0][j0][h + 1] != cor * (-1) && i0 != i)
                            i0 = n;

                    if (i0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                /* Diagonal plano xz */
                if (i == h + 1){

                    for (i0 = 0, k0 = 0; i0 < n; i0++, k0++)
                        if (tab[i0][j][k0] != cor * (-1) && i0 != i)
                            i0 = n;

                    if (i0 == n){
            
                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (i + h == n - 2){

                    for (i0 = 0, k0 = n - 1; i0 < n; i0++, k0--)
                        if (tab[i0][j][k0] != cor * (-1) && i0 != i)
                            i0 = n;

                    if (i0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                /* Diagonal plano yz */
                if (j == h + 1){

                    for (j0 = 0, k0 = 0; j0 < n; j0++, k0++)
                        if (tab[i][j0][k0] != cor * (-1) && j0 != j)
                            j0 = n;

                    if (j0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (i + h == n - 2){

                    for (j0 = 0, k0 = n - 1; j0 < n; j0++, k0--)
                        if (tab[i][j0][k0] != cor * (-1) && j0 != j)
                            j0 = n;

                    if (j0 == n){
            
                        pontos[i][j] = -1;
                        continue;
                    
                    }

                }

                /* Diagonais xyz */
                if (i == j && j == h + 1){

                    for (i0 = 0, j0 = 0, k0 = 0; j0 < n; i0++, j0++, k0++)
                        if (tab[i0][j0][k0] != cor * (-1) && j0 != j)
                            j0 = n;

                    if (j0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (i + j == n - 1 && i + h == n - 2){

                    for (i0 = n - 1, j0 = 0, k0 = 0; j0 < n; i0--, j0++, k0++)
                        if (tab[i0][j0][k0] != cor * (-1) && j0 != j)
                            j0 = n;

                    if (j0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (j + i == n - 1 && j + h == n - 2){

                    for (i0 = 0, j0 = n - 1, k0 = 0; i0 < n; i0++, j0--, k0++)
                        if (tab[i0][j0][k0] != cor * (-1) && i0 != i)
                            j0 = n;

                    if (i0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

                if (h + i == n - 2 && h + j == n - 2){

                    for (i0 = 0, j0 = 0, k0 = n - 1; j0 < n; i0++, j0++, k0--)
                        if (tab[i0][j0][k0] != cor * (-1) && i0 != i)
                            j0 = n;

                    if (j0 == n){

                        pontos[i][j] = -1;
                        continue;

                    }

                }

            }

        }

    }

    /* Pega o valor de maior pontuação e joga suas coordenadas nos ponteiros lin e col*/
    pontMax = pontos[0][0];
    *lin = 0;
    *col = 0;
    for (i = 0; i < n; i++){

        for (j = 0; j < n; j++){

            if (pontos[i][j] > pontMax){

                pontMax = pontos[i][j];
                *lin = i;
                *col = j;

            }

        }

    }

    /* Libera a memória alocada */
    for (i = 0; i < n; i++)
        free(pontos[i]);
    free(pontos);

    if (pontMax == -2)
        return n;

    return 0;

}