#include <stdio.h>
void cadastrar_usuario()
{

}


bool menu_cadastro_usuarios()
{
    int entrada;
    printf("\n---Menu cadastro usuario---");
    printf("\n1-Cadastrar usuario");
    printf("\n2-Excluir usuario");
    printf("\n3-Listar usuarios");
    printf("\n4-Voltar");

    if (entrada == 1)
        cadastrar_usuario();
    if (entrada == 2)
        excluir_usuario();
    if (entrada == 3)
        listar_usuarios();
    if (entrada == 4)
        return true;
}

bool menu_cadastro_livros()
{
    int entrada;
    printf("\n---Menu do Cadastro de Livros---");
    printf("\n1-Cadastrar livro");
    printf("\n2-Excluir livro");
    printf("\n3-Listar livros");
    printf("\n4-Voltar");

    if (entrada == 1)
        cadastrar_livro();
    if (entrada == 2)
        excluir_livro();
    if (entrada == 3)
        listar_livros();
    if (entrada == 4)
        return true;
}

bool menu_cadastro_emprestimo_devolucao()
{
    int entrada;
    printf("\n---Menu de Emprestimo e Devolucao---");
    printf("\n1-Emprestar livro");
    printf("\n2-Devolver livro");
    printf("\n3-Listar emprestimos");
    printf("\n4-Voltar");

    if (entrada == 1)
        emprestar_livro();
    if (entrada == 2)
        devolve_livro();
    if (entrada == 3)
        listar_emprestimos();
    if (entrada == 4)
        return true;
}

void menu_principal()
{
    int entrada;
    printf("\n---Menu principal---");
    printf("\n1-Cadastro de usuarios");
    printf("\n2-Cadastro de livros");
    printf("\n3-Emprestimo/devolucao");
    printf("\n4-Fim");
    
    scanf("%d", &entrada);
    bool continuar = true;
    if (entrada == 1)
    {
        continuar = menu_cadastro_usuarios();
        if (continuar == true)
            menu_principal();
    }
        
    if (entrada == 2)
    {
        continuar = menu_cadastro_livros();
        if (continuar == true)
            menu_principal();
    }

    if (entrada == 3)
    {
        continuar = menu_cadastro_emprestimo_devolucao();
        if (continuar == true)
            menu_principal();
    }

    if (entrada == 4)
        break;
}

int main()
{
    menu_principal();
}
