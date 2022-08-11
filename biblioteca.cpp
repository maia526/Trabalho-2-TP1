#include <stdio.h>
#include <string.h>
#include <time.h>

struct Data
{
    int dia;
    int mes;
    int ano;
};

/* Recupera a data/hora atual da máquina */
void data_hora_atual(int &dia, int &mes, int &ano,
    int &hora, int &min, int &seg)
{
    time_t t = time(NULL);
    struct tm lt = *localtime(&t);

    ano = lt.tm_year + 1900;
    mes = lt.tm_mon + 1;
    dia = lt.tm_mday;
    hora = lt.tm_hour;
    min = lt.tm_min;
    seg = lt.tm_sec;
}

/* Recupera a data atual da máquina */
Data data_atual()
{
    int h, m, s;
    Data dt;

    data_hora_atual(dt.dia, dt.mes, dt.ano, h, m, s);

    return dt;
}

/* Verifica se ano é bissexto */
bool eh_bissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

/* Retorna o número de dias de um mês/ano */
int numero_dias_mes(int mes, int ano)
{
    int dias[] = { 31, eh_bissexto(ano) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return mes >= 1 && mes <= 12 && ano > 0 ? dias[mes - 1] : -1;
}

/* Verifica se os valores de dia, mês e ano formam uma data válida */
bool eh_data_valida(int dia, int mes, int ano)
{
    return ano > 0 &&
        mes >= 1 && mes <= 12 &&
        dia >= 1 && dia <= numero_dias_mes(mes, ano);
}

/* Verifica se os valores de dia, mês e ano da struct Data formam uma data válida */
bool eh_data_valida(Data dt)
{
    return eh_data_valida(dt.dia, dt.mes, dt.ano);
}

/* Verifica se dt1 é maior que dt2 */
bool maior(Data dt1, Data dt2)
{
    return dt1.ano > dt2.ano ||
        (dt1.ano == dt2.ano && dt1.mes > dt2.mes) ||
        (dt1.ano == dt2.ano && dt1.mes == dt2.mes && dt1.dia > dt2.dia);
}

/* Verifica se dt1 é menor que dt2 */
bool menor(Data dt1, Data dt2)
{
    return dt1.ano < dt2.ano ||
        (dt1.ano == dt2.ano && dt1.mes < dt2.mes) ||
        (dt1.ano == dt2.ano && dt1.mes == dt2.mes && dt1.dia < dt2.dia);
}

/* Verifica se dt1 é igual a dt2 */
bool igual(Data dt1, Data dt2)
{
    return dt1.dia == dt2.dia &&
        dt1.mes == dt2.mes &&
        dt1.ano == dt2.ano;
}

/* Retorna a data dt incrementada em UM dia */
Data incrementa(Data dt)
{
    dt.dia++;
    if (dt.dia > numero_dias_mes(dt.mes, dt.ano))
    {
        dt.dia = 1;
        dt.mes++;
        if (dt.mes > 12)
        {
            dt.mes = 1;
            dt.ano++;
        }
    }

    return dt;
}

/* Retorna a data dt incrementada em N dias */
Data incrementa(Data dt, int n)
{
    for (int i = 0; i < n; i++)
        dt = incrementa(dt);

    return dt;
}

/* Retorna a data dt decrementada em UM dia */
Data decrementa(Data dt)
{
    dt.dia--;
    if (dt.dia < 1)
    {
        dt.mes--;
        if (dt.mes < 1)
        {
            dt.mes = 12;
            dt.ano--;
        }
        dt.dia = numero_dias_mes(dt.mes, dt.ano);
    }

    return dt;
}

/* Retorna a data dt decrementada em N dias */
Data decrementa(Data dt, int n)
{
    for (int i = 0; i < n; i++)
        dt = decrementa(dt);

    return dt;
}

/* Retorna a diferença, em dias, entre dt_ini e dt_fim
   Se dt_ini > dt_fim retorna um valor negativo */
int diferenca(Data dt_ini, Data dt_fim)
{
    int dias;

    if (dt_ini.mes == dt_fim.mes && dt_fim.ano == dt_fim.ano)
        dias = dt_fim.dia - dt_ini.dia;
    else if (dt_fim.ano == dt_fim.ano)
    {
        // Até o fim do mês inicial
        dias = numero_dias_mes(dt_ini.mes, dt_ini.ano) - dt_ini.dia;

        for (int mes = dt_ini.mes + 1; mes < dt_fim.mes; mes++)
            dias += numero_dias_mes(mes, dt_ini.ano);

        // Até o dia do mês final
        dias += dt_fim.dia;
    }
    else
    {
        dias = numero_dias_mes(dt_ini.mes, dt_ini.ano) - dt_ini.dia;

        for (int mes = dt_ini.mes + 1; mes <= 12; mes++)
            dias += numero_dias_mes(mes, dt_ini.ano);

        // Do ano inicial+1 até ano final-1
        for (int ano = dt_ini.ano + 1; ano < dt_fim.ano; ano++)
            dias += eh_bissexto(ano) ? 366 : 365;

        // Início do ano até mês final-1
        for (int mes = 1; mes < dt_fim.mes; mes++)
            dias += numero_dias_mes(mes, dt_fim.ano);

        dias += dt_fim.dia;
    }

    return dias;
}

struct Usuario
{
    int ocupado = 0; // todos começam com ocupado = 0. se for 1, significa que há um usuário cadastrado naquela posição. se for 0 significa que aquela posição pode ser usada para cadastrar outro usuário
    int tem_emprestimo = 0; //0 se não há empréstimo, 1 se há
    int codigo_livro;
    char nome[30];
    long long cpf;
    char nome_livro[30];
    char nome_autor[30];
    Data data_emprestimo;
    Data data_devolucao;
};

struct Livro
{
    char nome[30];
    char titulo[30];
    int codigo;
    int ano;
    int ocupado = 0;    // todos começam com ocupado = 0. se for 1, significa que há um livro cadastrado naquela posição. se for 0 significa que aquela posição pode ser usada para cadastrar outro livro
    int emprestado = 0; //0 se não está emprestado, 1 se está
    long long cpf;
    char nome_usuario[30];
    Data data_emprestimo;
    Data data_devolucao;

};

void ordena_titulo(Livro livros[], int qtd)
{
    int i, j, aux;
    for (i = 0; i < qtd - 1; i++)
    {
        for (j = i + 1; j < qtd; j++)
        {
            int resultado = strcmp(livros[i].titulo, livros[i + 1].titulo);

            if (resultado > 0)
            {
                Livro aux = livros[i];
                livros[i] = livros[j];
                livros[j] = aux;
            }
        }
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
        if (usuarios[i].ocupado == 0)   //se a posição não está ocupada (0), ela vai ser usada para um novo usuário
        {
            //ler cpf
            for (int j = 0; j < 1;)
            {
                ja_tem = false;
                printf("CPF: ");
                scanf("%lld", &cpf_cadastrar);

                for (int k = 0; k < 100; k++)
                {
                    if (usuarios[k].ocupado == 1)   //verifica entre os usuários já cadastrados
                    {
                        if (cpf_cadastrar == usuarios[k].cpf)   //se o cpf deles é igual o que se quer cadastrar
                            ja_tem = true;  //se cpf já está cadastrado, ja_tem = true
                    }
                }
                if ((cpf_cadastrar >= 10000000000 && cpf_cadastrar <= 99999999999) && ja_tem == false)  //verifica se cpf tem 11 dígitos e se não há cpf igual já cadastrado
                {
                    usuarios[i].cpf = cpf_cadastrar;    //atribui o cpf à struct
                    j++;
                }
                else
                {
                    printf("Erro: CPF ja cadastrado.\n");  //se falhar em uma das duas condições acima, mensagem de erro
                }
            }

            //ler cpf
            for (int j = 0; j < 1;)
            {
                char temp[1000];
                printf("Nome: ");
                getchar();
                gets(temp);
                strupr(temp);

                if (strlen(temp) >= 4 && strlen(temp) <= 30)    //se o nome tem no mínimo 4 e no máximo 30 caracteres
                {
                    strcpy(usuarios[i].nome, temp); //atribui nome à struct
                    j++;
                }

                else
                    printf("Erro: nome invalido.\n");
            }

            usuarios[i].ocupado = 1;    //posição é marcada como ocupada
            printf("\nUsuario cadastrado com sucesso!\n");

            break;
        }
    }
}

void listar_usuarios(Usuario usuarios[], Livro livros[])
{
    int qtd_usuarios = 0;
    ordena_cpf(usuarios, 100);

    puts("--------------------------------------------------");
    puts("CPF         Nome");
    puts("--------------------------------------------------");
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 1)
        {
            if (usuarios[i].tem_emprestimo == 1)
            {
                printf("%lld %s\n", usuarios[i].cpf, usuarios[i].nome);
                printf("\tEmprestimo: %d/%d/%d\n", usuarios[i].data_emprestimo.dia, usuarios[i].data_emprestimo.mes, usuarios[i].data_emprestimo.ano);
                printf("\tTitulo: %s\n", usuarios[i].nome_livro);
                printf("\tAutor: %s\n", usuarios[i].nome_autor);
            }
            else
                printf("%lld %s\n", usuarios[i].cpf, usuarios[i].nome);
        }
            

    }
    puts("--------------------------------------------------");
}

void excluir_usuario(Usuario usuarios[])
{
    long long cpf_excluir;
    bool tem = false;
    printf("Digite o CPF: ");
    scanf("%lld", &cpf_excluir);

    //verifica se cpf existe em alguma posição da struct
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

        //se existe
        if (tem == true)
        {
            for (int i = 0; i < 100; i++)
            {
                //se o usuário não tem nenhum empréstimo registrado, marcar posição como livre (1)
                if (usuarios[i].cpf == cpf_excluir)
                    if (usuarios[i].tem_emprestimo == 0)
                        usuarios[i].ocupado = 0;
                k++;    //termina loop
                if (usuarios[i].tem_emprestimo == 1)
                    printf("\nUsuario tem emprestimo em andamento.\n");
            }
        }
        if (tem == false)   //se não existe, erro
        {
            printf("\nCPF nao consta no sistema\n");
        }
    }
}

void cadastrar_livro(Usuario usuarios[], Livro livros[])
{
    bool ja_tem = false;
    int codigo_cadastrar;

    for (int i = 0; i < 100; i++)
    {
        //achar posição livre
        if (livros[i].ocupado == 0)
        {
            for (;;)
            {
                ja_tem = false;
                printf("Codigo: ");
                scanf("%d", &codigo_cadastrar);

                //verifica se código já está cadastrado
                for (int k = 0; k < 100; k++)
                {
                    if (livros[k].ocupado == 1)
                    {
                        if (codigo_cadastrar == livros[k].codigo)
                            ja_tem = true;
                    }
                }
                //verifica se código tem até 6 dígitos e não existe no sistema
                if (codigo_cadastrar <= 999999 && ja_tem == false)
                {
                    //se sim, atribui à struct na posição livre
                    livros[i].codigo = codigo_cadastrar;
                    break;
                }
                else
                    printf("Erro: Livro ja cadastrado.\n");
            }

            //le nome
            for (;;)
            {
                fflush(stdin);
                char temp[1000];
                printf("Titulo: ");
                gets(temp);
                strupr(temp);

                if (strlen(temp) >= 4 && strlen(temp) <= 30)
                {
                    strcpy(livros[i].nome, temp);
                    break;
                }

                else
                    printf("Erro: nome invalido.\n");
            }

            //le titulo
            for (;;)
            {
                fflush(stdin);
                char temp[1000];
                printf("Autor: ");
                gets(temp);
                strupr(temp);

                if (strlen(temp) >= 4 && strlen(temp) <= 30)
                {
                    strcpy(livros[i].titulo, temp);
                    break;
                }

                else
                    printf("Erro: titulo invalido.\n");
            }

            //le ano de publicação
            for (;;)
            {
                printf("Ano de publicacao: ");
                scanf("%d", &livros[i].ano);

                if (livros[i].ano >= 1900 && livros[i].ano <= 2050)
                    break;
                else
                    printf("Erro: ano invalido.\n");
            }

            livros[i].ocupado = 1;  //marca posição como ocupada
            printf("\nLivro cadastrado com sucesso!\n");

            break;
        }
    }
}

void excluir_livro(Usuario usuarios[], Livro livros[])
{
    int codigo_excluir;
    bool tem = false;
    bool emprestado = true;
    int pos;
    printf("Digite o codigo: ");
    scanf("%d", &codigo_excluir);

    for (int i = 0; i < 100; i++)
    {
        //verifica se código existe, e guarda a posição
        if (codigo_excluir == livros[i].codigo)
        {
            tem = true;
            pos = i;

            if (livros[i].emprestado == 0)  //verifica se livro está emprestado
                emprestado = false;

            if (tem)
                break;
        }
    }

    if (tem && !emprestado) //se existe e não está emprestado, marca posição como ocupada
    {
        livros[pos].ocupado = 0;
        printf("\nExclusao realizada com sucesso!\n");
    }
}

void listar_livros(Usuario usuarios[], Livro livros[])
{
    int qtd_livros = 0;
    ordena_titulo(livros, 100);

    puts("-------------------------------------------------------------------------");
    puts("Codigo Titulo                         Autor                           Ano");
    puts("-------------------------------------------------------------------------");
    for (int i = 0; i < 100; i++)
    {
        if (livros[i].ocupado == 1)
        {
            if (livros[i].emprestado == 1)
            {
                printf("%d ", livros[i].codigo);
                printf("%s", livros[i].titulo);
                for (int j = 0; j < 31 - strlen(livros[i].titulo); j++)
                    printf(" ");
                printf("%s", livros[i].nome);
                for (int j = 0; j < 31 - strlen(livros[i].nome); j++)
                    printf(" ");
                printf("%d\n", livros[i].ano);

                printf("\tEmprestimo: %d/%d/%d\n", livros[i].data_emprestimo.dia, livros[i].data_emprestimo.mes, livros[i].data_emprestimo.ano);
                printf("\tDevolucao: %d/%d/%d\n", livros[i].data_devolucao.dia, livros[i].data_devolucao.mes, livros[i].data_devolucao.ano);
                printf("\tCPF: %lld\n", livros[i].cpf);
                printf("\tNome: %s", livros[i].nome_usuario);
            }

            else
            {
                printf("%d ", livros[i].codigo);
                printf("%s", livros[i].titulo);
                for (int j = 0; j < 31 - strlen(livros[i].titulo); j++)
                    printf(" ");
                printf("%s", livros[i].nome);
                for (int j = 0; j < 31 - strlen(livros[i].nome); j++)
                    printf(" ");
                printf("%d\n", livros[i].ano);
            
            } 
        }
    }
    puts("-----------------------------------------------------------------------");

}

void emprestar_livro(Usuario usuarios[], Livro livros[])
{
    long long cpf_emprestimo;
    int codigo_emprestimo;
    bool tem = false;
    int pos_usuario, pos_livro;
    bool ja_tem_emprestimo = false;

    for (int i = 0; i < 1; )
    {
        ja_tem_emprestimo = false;
        //le cpf
        printf("\nCPF do usuario: ");
        scanf("%lld", &cpf_emprestimo);

        for (int j = 0; j < 100; j++)
        {
            if (usuarios[j].ocupado == 1)
            {
                //verifica se cpf existe e guarda posição
                if (usuarios[j].cpf == cpf_emprestimo)
                {
                    tem = true;
                    pos_usuario = j;

                    //verifica se usuário tem empréstimo registrado
                    if (usuarios[j].tem_emprestimo == 1)
                        ja_tem_emprestimo = true;
                }
            }
        }
        if (tem)
        {
            //se existe e tem empréstimo
            if (ja_tem_emprestimo)
            {
                printf("\nErro: CPF ja possui emprestimo!");
            }
            else
                i++;
        }
        else    //se não existe
            printf("\nErro: CPF nao cadastrado!");
    }

    tem = false;
    for (int i = 0; i < 1; )
    {
        ja_tem_emprestimo = false;

        //le codigo
        printf("\nCodigo do livro: ");
        scanf("%d", &codigo_emprestimo);

        for (int j = 0; j < 100; j++)
        {
            if (livros[j].ocupado == 1)
            {
                //verifica se codigo existe e guarda posição
                if (livros[j].codigo == codigo_emprestimo)
                {
                    pos_livro = j;
                    tem = true;

                    //verifica se livro está emprestado
                    if (livros[j].emprestado == 1)
                    {
                        ja_tem_emprestimo = true;
                    }
                }
            }
        }
        if (tem)
        {
            if (ja_tem_emprestimo)
            {
                printf("\nErro: Livro ja esta emprestado.");
            }
            else
                i++;
        }
        else
            printf("\nErro: Livro nao cadastrado.");
    }

    //marca usuário como tendo empréstimo
    usuarios[pos_usuario].tem_emprestimo = 1;
    //atribui codigo do livro ao usuário
    usuarios[pos_usuario].codigo_livro = livros[pos_livro].codigo;
    strcpy(usuarios[pos_usuario].nome_livro, livros[pos_livro].titulo);
    strcpy(usuarios[pos_livro].nome_autor, livros[pos_livro].nome);
    //marca livro como emprestado
    livros[pos_livro].emprestado = 1;

    livros[pos_livro].cpf = usuarios[pos_usuario].cpf;
    strcpy(livros[pos_livro].nome_usuario, usuarios[pos_usuario].nome);

    //gera data da entrega
    Data dataEntrega = incrementa(data_atual(), 7);
    //atribui data de hoje para o livro
    livros[pos_livro].data_emprestimo = data_atual();
    //atribui data da entrega para o livro
    livros[pos_livro].data_devolucao = dataEntrega;

    usuarios[pos_usuario].data_emprestimo = data_atual();
    //atribui data da entrega para o livro
    usuarios[pos_usuario].data_devolucao = dataEntrega;

    // printf("Data do emprestimo: %d/%d/%d\n", livros[pos_livro].data_emprestimo.dia, livros[pos_livro].data_emprestimo.mes, livros[pos_livro].data_emprestimo.ano);
    // printf("Data da devolucao: %d/%d/%d\n", livros[pos_livro].data_devolucao.dia, livros[pos_livro].data_devolucao.mes, livros[pos_livro].data_devolucao.ano);

    printf("\nEmpresitmo concedido!\n");
    printf("Nome: %s", livros[pos_livro].nome);
    printf("\nTitulo: %s", livros[pos_livro].titulo);
    printf("\nData emprestimo: %d/%d/%d\n", livros[pos_livro].data_emprestimo.dia, livros[pos_livro].data_emprestimo.mes, livros[pos_livro].data_emprestimo.ano);
    printf("Data devolucao: %d/%d/%d\n", livros[pos_livro].data_devolucao.dia, livros[pos_livro].data_devolucao.mes, livros[pos_livro].data_devolucao.ano);


}

Data leDataEntrega(Livro livros[], Usuario usuarios[], long long cpfUsuario, int pos_usuario, int pos_livro)
{
    //milton, essa função não tá funcionando direito, falta ajeitar ela, fazer a função de listar empréstimos e formatar o printf das outras funções de listagem 
    int input;
    int diaEntrega, mesEntrega, anoEntrega;
    Data d;
    Usuario usuario = usuarios[pos_usuario];
    while (true)
    {
        printf("Digite a data de entrega no fomato DDMMAAAA: ");
        scanf("%d", &input);
        if (input > 99999999 || input < 1000000)
            printf("Digite no formato DDMMAAAA\n");
        else
        {
            anoEntrega = input % 10000;
            mesEntrega = (input /= 10000) % 100;
            diaEntrega = (input /= 100);
            d.ano = anoEntrega;
            d.mes = mesEntrega;
            d.dia = diaEntrega;
            if (eh_data_valida(d) &&
                (maior(d, livros[pos_livro].data_emprestimo) ||
                    igual(d, livros[pos_livro].data_emprestimo)) &&
                (menor(d, data_atual()) || igual(d, data_atual()))) // válido e maior ou igual à data de retirada e menor ou igual à data atual
                break;
            puts("Erro: Data de devolucao invalida!");
        }
    }
    return d;
}

void devolve_livro(Usuario usuarios[], Livro livros[])
{
    long long cpf_devolver;
    bool tem = false;
    int pos_usuario, pos_livro;
    long data_devolver;
    Data d;
    int diaEntrega, mesEntrega, anoEntrega;
    bool emprestado = true;


    //ler o cpf
    for (int i = 0; i < 1; )
    {
        printf("\nCPF: ");
        scanf("%lld", &cpf_devolver);

        for (int j = 0; j < 100; j++)
        {
            tem = false;
            emprestado = false;
            if (cpf_devolver == usuarios[j].cpf)    //verifica se cpf esta cadastrado
            {
                tem = true;
                pos_usuario = j;    //registra a posição do usuario no vetor

                if (usuarios[j].tem_emprestimo == 1)    //verifica se tem emprestimo registrado no cpf
                {
                    if (usuarios[j].tem_emprestimo = 1)
                        emprestado = true;
                }
                break;
            }
        }

        if (tem == false)
            printf("\nErro: Usuario nao cadastrado!");

        if (tem == true && emprestado == false)
            printf("\nErro: O usuario nao tem emprestimo!");

        if (tem == true && emprestado == true)
            i++;
    }


    int codigo_devolver = usuarios[pos_usuario].codigo_livro;   //obtem o código do livro registrado no cpf
    for (int i = 0; i < 100; i++)
    {
        if (livros[i].codigo == codigo_devolver)
        {
            pos_livro = i;  //registra a posição do livro no vetor
            break;
        }
    }

    Data data;
    data = leDataEntrega(livros, usuarios, cpf_devolver, pos_usuario, pos_livro);   //obtem a data da entrega
    livros[pos_livro].emprestado = 0;   //registra livro como disponível
    usuarios[pos_usuario].tem_emprestimo = 0;   //regitsra usuário como não tendo empréstimos

    printf("\nDevolucao realizada com sucesso ");
    if (diferenca(data, livros[pos_livro].data_devolucao) >= 0) //se a data de entrega for menor ou igual que o limite
        printf("dentro do prazo!\n");
    else
        printf("com atraso de %d dia(s)!\n", diferenca(livros[pos_livro].data_devolucao, data));    //se a fata de entrega for maior

    printf("Nome: %s", usuarios[pos_usuario].nome);
    printf("\nTitulo: %s", livros[pos_livro].titulo);
}

void listar_emprestimos(Livro livros[], Usuario usuarios[])
{
    int qtd_usuarios = 0;
    ordena_cpf(usuarios, 100);

    puts("-------------------------------------------------------------");
    puts("CPF         Nome       Codigo      Titulo   Emprestimo    Devolucao");
    puts("------------------------------------------------------------");
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i].ocupado == 1 && usuarios[i].tem_emprestimo == 1)
            printf("%lld %s %d %s  %d/%d/%d  %d/%d/%d\n", usuarios[i].cpf, usuarios[i].nome, usuarios[i].codigo_livro, usuarios[i].nome_livro, usuarios[i].data_emprestimo.dia, usuarios[i].data_emprestimo.mes, usuarios[i].data_emprestimo.ano, usuarios[i].data_devolucao.dia, usuarios[i].data_devolucao.mes, usuarios[i].data_devolucao.ano);

    }
    puts("--------------------------------------------------");
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

void menu_cadastro_emprestimo_devolucao(Usuario usuarios[], Livro livros[])
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

        if (entrada == 1)
            emprestar_livro(usuarios, livros);
        if (entrada == 2)
            devolve_livro(usuarios, livros);
        if (entrada == 3)
            listar_emprestimos(livros, usuarios);
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
            menu_cadastro_emprestimo_devolucao(usuarios, livros);
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
