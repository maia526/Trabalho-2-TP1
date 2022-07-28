#include <stdio.h>
#include <string.h>
struct Usuario{
    int ocupado = 0;    //todos começam com ocupado = 0. se for 1, significa que há um usuário cadastrado naquela posição. se for 0 significa que aquela posição pode ser usada para cadastrar outro usuário
    char nome[200];
    long long cpf;
};

void cadastrar_usuario(Usuario usuarios[])
{
    bool ja_tem = false;
    long long cpf_cadastrar;

    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 0)
        {
            for (int j = 0; j < 1; )
            {
                ja_tem = false;
                printf("CPF: ");
                scanf("%lld", &cpf_cadastrar);
                
                for (int k = 0; k < 100; k++)   //verificar se já há algum usuário cadastrado com mesmo cpf
                {
                    if (usuarios[k].ocupado == 1)   //se a posição for de um usuário cadastrado
                    {
                        if (cpf_cadastrar == usuarios[k].cpf)   //se os cpfs forem os mesmos
                            ja_tem = true;  //já tem esse cpf cadastrado
                            
                    }
                    
                }
                if ((cpf_cadastrar >= 10000000000 && cpf_cadastrar <= 99999999999) && ja_tem == false)  //se cpf tem 11 digitos e não há outra pesspa com mesmo cpf
                {
                    usuarios[i].cpf = cpf_cadastrar;    //atribuir o cpf à pessoa
                    j++;    //sair do loop cpf
                    //se não, pede o cpf de novo
                }
                
            }
            //loop acima não está funcionando. ele tem que pedir para o usuário colocar o cpf novamente se o cpf não tiver 11 dígitos, ou se já houver outra pessoa com mesmo cpf
            
            for (int j = 0; j < 1; )
            {
                printf("Nome: ");
                getchar();
                gets(usuarios[i].nome);
                
                if (strlen(usuarios[i].nome) >= 4)  //se o tamanho da string for maior ou igual a 4
                    j++;    //sair do loop nome
                //se não, pede o nome novamente
                
            }
            //se colocar um nome com menos de 3 letras, o programa pede para colocar o nome novamente, mas quando os usuários são listados a primeira letra do nome não aparece

            usuarios[i].ocupado = 1;    //caso passe pelas condições acima, a posição passa a ser ocupada pelo usuário novo.

            break;  //e volta para o menu_cadastro_usuario
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