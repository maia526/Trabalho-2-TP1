#include <stdio.h>
struct Usuario{
    int ocupado = 0;
    char nome[200];
    long long cpf;
};

void cadastrar_usuario(Usuario usuarios[])
{
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 0)
        {
            usuarios[i].ocupado = 1;
            printf("CPF: ");
            scanf("%lld", &usuarios[i].cpf);
            printf("Nome: ");
            getchar();
            gets(usuarios[i].nome);
            
            break;
        }
    }
}

void listar_usuarios(Usuario usuarios[])
{
    for (int i = 0; i < 100; i++)
    {
        if(usuarios[i].ocupado == 1)
        {
            printf("\n%s", usuarios[i].nome);
            printf("\n%lld", usuarios[i].cpf);
        }
    }
}

void excluir_usuario(Usuario usuarios[])
{
    long long cpf_excluir;
    printf("Digite o CPF: ");
    scanf("%lld", &cpf_excluir);
    
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].cpf == cpf_excluir)
            usuarios[i].ocupado = 0;
    }
}

void menu_cadastro_usuarios(Usuario usuarios[])
{
    while(true)
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
         listar_usuarios(usuarios);
     if (entrada == 4)
         break;
    }
}

void menu_cadastro_livros()
{
    while(true)
    {
    int entrada;
    printf("\n---Menu do Cadastro de Livros---");
    printf("\n1-Cadastrar livro");
    printf("\n2-Excluir livro");
    printf("\n3-Listar livros");
    printf("\n4-Voltar\n");
    scanf("%d", &entrada);

    // if (entrada == 1)
    //     cadastrar_livro();
    // if (entrada == 2)
    //     excluir_livro();
    // if (entrada == 3)
    //     listar_livros();
     if (entrada == 4)
         break;
    }
}

void menu_cadastro_emprestimo_devolucao()
{
    while(true)
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

void menu_principal(Usuario usuarios[])
{
    while(true)
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
        menu_cadastro_usuarios(usuarios);
    }
        
    if (entrada == 2)
    {
        menu_cadastro_livros();
        
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
    menu_principal(usuarios);
}
