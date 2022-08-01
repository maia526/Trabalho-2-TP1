#include <stdio.h>
#include <string.h>
struct Usuario
{
    int ocupado = 0; // todos começam com ocupado = 0. se for 1, significa que há um usuário cadastrado naquela posição. se for 0 significa que aquela posição pode ser usada para cadastrar outro usuário
    int repetiu_nome = 0;
    int tem_emprestimo = 0;
    char nome_livro[30];
    char nome[15];
    char sobrenome[15];
    long long cpf;
};

struct Livro
{
    char nome[15];
    char sobrenome[15];
    char titulo[30];
    int codigo;
    int ano;
    int ocupado = 0;
    int emprestado = 0;
};

void ordena_titulo(Livro livros[], int qtd) {
   bool trocou = true;
   int k = qtd-1;

   while (k > 0 && trocou)
   {
     trocou = false;
     for (int i = 0; i < k; i++) {

       int resultado = stricmp(livros[i].titulo, livros[i+1].titulo);

       if (resultado > 0) {
         char aux[31];

         strcpy(aux, livros[i+1].titulo);            // aux = palavras[i+1]
         strcpy(livros[i+1].titulo, livros[i].titulo);    // palavras[i+1] = palavras[i]
         strcpy(livros[i].titulo, aux);              // palavras[i] = aux
         trocou = true;
       }
     }
     k--;
   }
}

void ordena_cpf(Usuario usuarios[], int qtd_usuarios)
{
    int i, j, aux;
    for (i = 0; i < qtd_usuarios - 1; i++)
    {
        for (j = i + 1; j < qtd_usuarios; j++)
        {
            if (usuarios[i].cpf > usuarios[j].cpf)
            {
                Usuario aux = usuarios[i];
                usuarios[i] = usuarios[j];
                usuarios[j] = aux;
            }
        }
    }
}

void cadastrar_usuario(Usuario usuarios[])
{
    bool ja_tem = false;
    long long cpf_cadastrar;

    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 0)
        {
            for (int j = 0; j < 1;)
            {
                ja_tem = false;
                printf("CPF: ");
                scanf("%lld", &cpf_cadastrar);

                for (int k = 0; k < 100; k++)
                {
                    if (usuarios[k].ocupado == 1)
                    {
                        if (cpf_cadastrar == usuarios[k].cpf)
                            ja_tem = true;
                    }
                }
                if ((cpf_cadastrar >= 10000000000 && cpf_cadastrar <= 99999999999) && ja_tem == false)
                {
                    usuarios[i].cpf = cpf_cadastrar;
                    j++;
                }
                else
                    printf("CPF invalido.\n");
            }

            for (int j = 0; j < 1;)
            {

                printf("Nome: ");
                scanf(" %s", usuarios[i].nome);
                strupr(usuarios[i].nome);
                printf("Sobrenome: ");
                scanf(" %s", usuarios[i].sobrenome);
                strupr(usuarios[i].sobrenome);

                if (strlen(usuarios[i].nome) >= 4 && strlen(usuarios[i].sobrenome) >= 1)
                    j++;
                else
                    printf("Nome invalido.\n");
            }

            usuarios[i].ocupado = 1;

            break;
        }
    }
}

void listar_usuarios(Usuario usuarios[], Livro livros[])
{
    int qtd_usuarios = 0;
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 1)
            qtd_usuarios++;
    }
    ordena_cpf(usuarios, qtd_usuarios);

    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 1)
        {
            printf("\n%s", usuarios[i].nome);
            printf(" %s", usuarios[i].sobrenome);
            printf("\n%lld\n", usuarios[i].cpf);
        }
    }
}

void excluir_usuario(Usuario usuarios[])
{
    long long cpf_excluir;
    bool tem = false;
    printf("Digite o CPF: ");
    scanf("%lld", &cpf_excluir);

    for (int k = 0; k < 1; k++)
    {
        for (int i = 0; i < 100; i++)
        {
            if (usuarios[i].ocupado == 1)
            {
                if (cpf_excluir == usuarios[i].cpf)
                    tem = true;
            }
        }

        if (tem == true)
        {
            for (int i = 0; i < 100; i++)
            {
                // esse tem.emprestimo é para verificar se o usuario tem algum emprestimo em andamento. se tiver não pode deletar. caso dê problema com isso mais para a frente é aqui que tem que ver provavelmente
                if (usuarios[i].cpf == cpf_excluir)
                    if (usuarios[i].tem_emprestimo == 0)
                        usuarios[i].ocupado = 0;
                k++;
                if (usuarios[i].tem_emprestimo == 1)
                    printf("\nUsuario tem emprestimo em andamento.\n");
            }
        }
        if (tem == false)
        {
            printf("\nCPF nao consta no sistema\n");
        }
    }
}

void cadastrar_livro(Usuario usuarios[], Livro livros[])
{
    bool ja_tem = false;
    long long codigo_cadastrar;

    for (int i = 0; i < 100; i++)
    {
        if (livros[i].ocupado == 0)
        {
            for (int j = 0; j < 1;)
            {
                ja_tem = false;
                printf("Codigo: ");
                scanf("%d", &codigo_cadastrar);

                for (int k = 0; k < 100; k++)
                {
                    if (livros[k].ocupado == 1)
                    {
                        if (codigo_cadastrar == livros[k].codigo)
                            ja_tem = true;
                    }
                }
                if (codigo_cadastrar <= 999999 && ja_tem == false)
                {
                    livros[i].codigo = codigo_cadastrar;
                    printf("\n%d\n", livros[i].codigo);
                    j++;
                }
                else
                    printf("Codigo invalido.\n");
            }

            for (int j = 0; j < 1;)
            {

                printf("Nome do autor: ");
                scanf(" %s", livros[i].nome);
                strupr(livros[i].nome);
                printf("Sobrenome do autor: ");
                scanf(" %s", livros[i].sobrenome);
                strupr(livros[i].sobrenome);

                if (strlen(livros[i].nome) >= 4 && strlen(livros[i].sobrenome) >= 1)
                    j++;
                else
                    printf("Nome invalido.\n");
            }

            for (int j = 0; j < 1;)
            {

                printf("Titulo (sem espaços): ");
                scanf(" %s", livros[i].titulo);
                strupr(livros[i].titulo);

                if (strlen(livros[i].titulo) >= 4)
                    j++;
                if (strlen(livros[i].titulo) < 4)
                    printf("Titulo invalido.\n");
            }

            for (int j = 0; j < 1;)
            {
                printf("Ano de publicacao: ");
                scanf("%d", &livros[i].ano);

                if (livros[i].ano >= 1900 && livros[i].ano <= 2050)
                    j++;
                else
                    printf("Ano invalido.\n");
            }

            livros[i].ocupado = 1;

            break;
        }
    }
}

void excluir_livro(Usuario usuarios[], Livro livros[])
{
    int codigo_excluir;
    bool tem = false;
    bool emprestado = true;
    printf("Digite o codigo: ");
    scanf("%d", &codigo_excluir);

    for (int k = 0; k < 1; k++)
    {
        for (int i = 0; i < 100; i++)
        {
            if (livros[i].ocupado == 1)
            {
                if (codigo_excluir == livros[i].codigo)
                    tem = true;
                if (livros[i].emprestado == 0)
                    emprestado = false;
            }
        }

        if (tem == true)
        {
            for (int i = 0; i < 100; i++)
            {
                // esse tem.emprestimo é para verificar se o usuario tem algum emprestimo em andamento. se tiver não pode deletar. caso dê problema com isso mais para a frente é aqui que tem que ver provavelmente
                if (emprestado == false)
                    if (usuarios[i].tem_emprestimo == 0)
                        usuarios[i].ocupado = 0;
                k++;
                if (emprestado == true)
                    printf("\nLivro esta emprestado, nao e possivel exclui-lo.\n");
            }
        }
        if (tem == false)
        {
            printf("\nCodigo nao consta no sistema\n");
        }
    }
}

void listar_livros(Usuario usuarios[], Livro livros[])
{
    int qtd_livros = 0;
    for (int i = 0; i < 100; i++)
    {
        if (livros[i].ocupado == 1)
            qtd_livros++;
    }
    ordena_titulo(livros, qtd_livros);

    for (int i = 0; i < 100; i++)
    {
        if (livros[i].ocupado == 1)
        {
            printf("\n%s\n", livros[i].titulo);
            printf(" %s %s", livros[i].nome, livros[i].sobrenome);
            printf("\n%d\n", livros[i].codigo);
            printf("\n%d", livros[i].ano);
        }
    }
}

void menu_cadastro_usuarios(Usuario usuarios[], Livro livros[])
{
    while (true)
    {
        int entrada;
        printf("\n---Menu cadastro usuario---");
        printf("\n1-Cadastrar usuario");
        printf("\n2-Excluir usuario");
        printf("\n3-Listar usuarios");
        printf("\n4-Voltar\n");
        scanf("%d", &entrada);

        if (entrada == 1)
            cadastrar_usuario(usuarios);
        if (entrada == 2)
            excluir_usuario(usuarios);
        if (entrada == 3)
            listar_usuarios(usuarios, livros);
        if (entrada == 4)
            break;
    }
}

void menu_cadastro_livros(Usuario usuarios[], Livro livros[])
{
    while (true)
    {
        int entrada;
        printf("\n---Menu do Cadastro de Livros---");
        printf("\n1-Cadastrar livro");
        printf("\n2-Excluir livro");
        printf("\n3-Listar livros");
        printf("\n4-Voltar\n");
        scanf("%d", &entrada);

        if (entrada == 1)
            cadastrar_livro(usuarios, livros);
        if (entrada == 2)
            excluir_livro(usuarios, livros);
        if (entrada == 3)
            listar_livros(usuarios, livros);
        if (entrada == 4)
            break;
    }
}

void menu_cadastro_emprestimo_devolucao()
{
    while (true)
    {
        int entrada;
        printf("\n---Menu de Emprestimo e Devolucao---");
        printf("\n1-Emprestar livro");
        printf("\n2-Devolver livro");
        printf("\n3-Listar emprestimos");
        printf("\n4-Voltar\n");
        scanf("%d", &entrada);

        //  if (entrada == 1)
        //      emprestar_livro();
        //  if (entrada == 2)
        //      devolve_livro();
        //  if (entrada == 3)
        //      listar_emprestimos();
        if (entrada == 4)
            break;
    }
}

void menu_principal(Usuario usuarios[], Livro livros[])
{
    while (true)
    {
        int entrada;
        printf("\n---Menu principal---");
        printf("\n1-Cadastro de usuarios");
        printf("\n2-Cadastro de livros");
        printf("\n3-Emprestimo/devolucao");
        printf("\n4-Fim\n");

        scanf("%d", &entrada);

        if (entrada == 1)
        {
            menu_cadastro_usuarios(usuarios, livros);
        }

        if (entrada == 2)
        {
            menu_cadastro_livros(usuarios, livros);
        }

        if (entrada == 3)
        {
            menu_cadastro_emprestimo_devolucao();
        }

        if (entrada == 4)
            break;
    }
}

int main()
{
    Usuario usuarios[100];
    Livro livros[100];
    menu_principal(usuarios, livros);
}