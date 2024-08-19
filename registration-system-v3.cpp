#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Usuario {
    string nome;
    int idade;
    string email;
};

void adicionarUsuario() {
    Usuario usuario;

    cout << "Digite o nome do usuario: ";
    cin.ignore();
    getline(cin, usuario.nome);

    cout << "Digite a idade do usuario: ";
    cin >> usuario.idade;

    cout << "Digite o email do usuario: ";
    cin.ignore();
    getline(cin, usuario.email);

    ofstream arquivo("usuarios.txt", ios::app);

    if (arquivo.is_open()) {
        arquivo << usuario.nome << "," << usuario.idade << "," << usuario.email << endl;
        arquivo.close();

        cout << "Usuario adicionado com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

void visualizarUsuarios() {
    ifstream arquivo("usuarios.txt");

    if (arquivo.is_open()) {
        string linha;

        while (getline(arquivo, linha)) {
            cout << linha << endl;
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

void editarUsuario() {
    string nomeAntigo;
    cout << "Digite o nome do usuario que deseja editar: ";
    cin.ignore();
    getline(cin, nomeAntigo);

    ifstream arquivoAntigo("usuarios.txt");
    ofstream arquivoNovo("temp.txt");

    if (arquivoAntigo.is_open() && arquivoNovo.is_open()) {
        string linha;
        string conteudoNovo;

        while (getline(arquivoAntigo, linha)) {
            size_t posicao = linha.find(nomeAntigo);
            if (posicao != string::npos) {
                cout << "Digite o novo nome do usuario: ";
                getline(cin, conteudoNovo);
                linha.replace(posicao, nomeAntigo.length(), conteudoNovo);
            }
            arquivoNovo << linha << endl;
        }

        arquivoAntigo.close();
        arquivoNovo.close();

        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");

        cout << "Usuario editado com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

void excluirUsuario() {
    string nomeUsuario;
    cout << "Digite o nome do usuario que deseja excluir: ";
    cin.ignore();
    getline(cin, nomeUsuario);

    ifstream arquivoAntigo("usuarios.txt");
    ofstream arquivoNovo("temp.txt");

    if (arquivoAntigo.is_open() && arquivoNovo.is_open()) {
        string linha;

        while (getline(arquivoAntigo, linha)) {
            size_t posicao = linha.find(nomeUsuario);
            if (posicao == string::npos) {
                arquivoNovo << linha << endl;
            }
        }

        arquivoAntigo.close();
        arquivoNovo.close();

        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");

        cout << "Usuario excluído com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

int main() {
    int opcao;

    cout << "Bem-vindo ao Sistema de Cadastro!" << endl;

    do {
        cout << "Selecione uma opcao:" << endl;
        cout << "1 - Adicionar usuario" << endl;
        cout << "2 - Visualizar usuarios" << endl;
        cout << "3 - Editar usuario" << endl;
        cout << "4 - Excluir usuario" << endl;
        cout << "5 - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarUsuario();
                break;
            case 2:
                visualizarUsuarios();
                break;
            case 3:
                editarUsuario();
                break;
            case 4:
                excluirUsuario();
                break;
            case 5:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opcao inválida." << endl;
                break;
        }
    } while (opcao != 5);

    return 0;
}