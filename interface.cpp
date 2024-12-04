#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

sql::Connection* conectar() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* conn;

        driver = sql::mysql::get_mysql_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "root", "");
        conn->setSchema("seguradora_porto");
        return conn;
    }
    catch (sql::SQLException& e) {
        cerr << "Erro de conexão: " << e.what() << endl;
        cerr << "Código de erro: " << e.getErrorCode() << endl;
        cerr << "Estado SQL: " << e.getSQLState() << endl;
        return nullptr;
    }
}

void menu_principal() {
    cout << "--- Terminal de Controle - Seguradora Porto ---\n";
    cout << "1. Gerenciar Proprietários\n";
    cout << "2. Gerenciar Veículos\n";
    cout << "3. Gerenciar Endereços de Proprietários\n";
    cout << "4. Gerenciar Apólices\n";
    cout << "5. Sair\n";
}

void gerenciar_proprietarios(sql::Connection* conn) {
    while (true) {
        cout << "--- Gerenciar Proprietários ---\n";
        cout << "1. Listar Proprietários\n";
        cout << "2. Adicionar Proprietário\n";
        cout << "3. Atualizar Proprietário\n";
        cout << "4. Remover Proprietário\n";
        cout << "5. Voltar\n";
        string escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        if (escolha == "1") {
            pstmt = conn->prepareStatement("SELECT * FROM Proprietario;");
            res = pstmt->executeQuery();
            while (res->next()) {
                cout << "ID: " << res->getInt("id") << ", Nome: " << res->getString("nome") << ", Email: " << res->getString("email") << "\n";
            }
            delete res;
        }
        else if (escolha == "2") {
            string cpf, nome, email, fone;
            cout << "CPF: "; cin >> cpf;
            cout << "Nome: "; cin >> nome;
            cout << "Email: "; cin >> email;
            cout << "Fone: "; cin >> fone;

            pstmt = conn->prepareStatement("INSERT INTO Proprietario (cpf, nome, email, fone) VALUES (?, ?, ?, ?)");
            pstmt->setString(1, cpf);
            pstmt->setString(2, nome);
            pstmt->setString(3, email);
            pstmt->setString(4, fone);
            pstmt->executeUpdate();
            cout << "Proprietário adicionado com sucesso!\n";
        }
        else if (escolha == "3") {
            string id, nome, email, fone;
            cout << "ID do proprietário para atualizar: "; cin >> id;
            cout << "Novo Nome: "; cin >> nome;
            cout << "Novo Email: "; cin >> email;
            cout << "Novo Fone: "; cin >> fone;

            pstmt = conn->prepareStatement("UPDATE Proprietario SET nome=?, email=?, fone=? WHERE id=?");
            pstmt->setString(1, nome);
            pstmt->setString(2, email);
            pstmt->setString(3, fone);
            pstmt->setString(4, id);
            pstmt->executeUpdate();
            cout << "Proprietário atualizado com sucesso!\n";
        }
        else if (escolha == "4") {
            string id;
            cout << "ID do proprietário para remover: "; cin >> id;

            pstmt = conn->prepareStatement("DELETE FROM Proprietario WHERE id=?");
            pstmt->setString(1, id);
            pstmt->executeUpdate();
            cout << "Proprietário removido com sucesso!\n";
        }
        else if (escolha == "5") {
            break;
        }
        else {
            cout << "Opção inválida.\n";
        }
    }
}

void gerenciar_veiculos(sql::Connection* conn) {
    while (true) {
        cout << "--- Gerenciar Veículos ---\n";
        cout << "1. Listar Veículos\n";
        cout << "2. Adicionar Veículo\n";
        cout << "3. Atualizar Veículo\n";
        cout << "4. Remover Veículo\n";
        cout << "5. Voltar\n";
        string escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        if (escolha == "1") {
            pstmt = conn->prepareStatement("SELECT * FROM Veiculo;");
            res = pstmt->executeQuery();
            while (res->next()) {
                cout << "ID: " << res->getInt("id") << ", Placa: " << res->getString("placa") << ", Modelo: " << res->getString("modelo") << "\n";
            }
            delete res;
        }
        else if (escolha == "2") {
            string id_resp, placa, modelo, ano, cor, fotos;
            cout << "ID do Proprietário: "; cin >> id_resp;
            cout << "Placa: "; cin >> placa;
            cout << "Modelo: "; cin >> modelo;
            cout << "Ano (YYYY-MM-DD): "; cin >> ano;
            cout << "Cor: "; cin >> cor;
            cout << "Fotos (URL): "; cin >> fotos;

            pstmt = conn->prepareStatement("INSERT INTO Veiculo (id_resp, placa, modelo, ano, cor, fotos) VALUES (?, ?, ?, ?, ?, ?)");
            pstmt->setString(1, id_resp);
            pstmt->setString(2, placa);
            pstmt->setString(3, modelo);
            pstmt->setString(4, ano);
            pstmt->setString(5, cor);
            pstmt->setString(6, fotos);
            pstmt->executeUpdate();
            cout << "Veículo adicionado com sucesso!\n";
        }
        else if (escolha == "3") {
            string id, modelo, cor, fotos;
            cout << "ID do veículo para atualizar: "; cin >> id;
            cout << "Novo Modelo: "; cin >> modelo;
            cout << "Nova Cor: "; cin >> cor;
            cout << "Nova URL de Fotos: "; cin >> fotos;

            pstmt = conn->prepareStatement("UPDATE Veiculo SET modelo=?, cor=?, fotos=? WHERE id=?");
            pstmt->setString(1, modelo);
            pstmt->setString(2, cor);
            pstmt->setString(3, fotos);
            pstmt->setString(4, id);
            pstmt->executeUpdate();
            cout << "Veículo atualizado com sucesso!\n";
        }
        else if (escolha == "4") {
            string id;
            cout << "ID do veículo para remover: "; cin >> id;

            pstmt = conn->prepareStatement("DELETE FROM Veiculo WHERE id=?");
            pstmt->setString(1, id);
            pstmt->executeUpdate();
            cout << "Veículo removido com sucesso!\n";
        }
        else if (escolha == "5") {
            break;
        }
        else {
            cout << "Opção inválida.\n";
        }
    }
}

void gerenciar_enderecos(sql::Connection* conn) {
    while (true) {
        cout << "--- Gerenciar Endereços de Proprietários ---\n";
        cout << "1. Listar Endereços\n";
        cout << "2. Adicionar Endereço\n";
        cout << "3. Atualizar Endereço\n";
        cout << "4. Remover Endereço\n";
        cout << "5. Voltar\n";
        string escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        if (escolha == "1") {
            pstmt = conn->prepareStatement("SELECT * FROM Endereco;");
            res = pstmt->executeQuery();
            while (res->next()) {
                cout << "ID: " << res->getInt("id") << ", Rua: " << res->getString("rua")
                    << ", Número: " << res->getString("numero") << ", Cidade: " << res->getString("cidade")
                    << ", CEP: " << res->getString("cep") << "\n";
            }
            delete res;
        }
        else if (escolha == "2") {
            string id_resp, rua, numero, cidade, estado, cep;
            cout << "ID do Proprietário: "; cin >> id_resp;
            cout << "Rua: "; cin.ignore(); getline(cin, rua);
            cout << "Número: "; cin >> numero;
            cout << "Cidade: "; cin.ignore(); getline(cin, cidade);
            cout << "Estado: "; cin >> estado;
            cout << "CEP: "; cin >> cep;

            pstmt = conn->prepareStatement("INSERT INTO Endereco (id_resp, rua, numero, cidade, estado, cep) VALUES (?, ?, ?, ?, ?, ?)");
            pstmt->setString(1, id_resp);
            pstmt->setString(2, rua);
            pstmt->setString(3, numero);
            pstmt->setString(4, cidade);
            pstmt->setString(5, estado);
            pstmt->setString(6, cep);
            pstmt->executeUpdate();
            cout << "Endereço adicionado com sucesso!\n";
        }
        else if (escolha == "3") {
            string id, rua, numero, cidade, estado, cep;
            cout << "ID do endereço para atualizar: "; cin >> id;
            cout << "Nova Rua: "; cin.ignore(); getline(cin, rua);
            cout << "Novo Número: "; cin >> numero;
            cout << "Nova Cidade: "; cin.ignore(); getline(cin, cidade);
            cout << "Novo Estado: "; cin >> estado;
            cout << "Novo CEP: "; cin >> cep;

            pstmt = conn->prepareStatement("UPDATE Endereco SET rua=?, numero=?, cidade=?, estado=?, cep=? WHERE id=?");
            pstmt->setString(1, rua);
            pstmt->setString(2, numero);
            pstmt->setString(3, cidade);
            pstmt->setString(4, estado);
            pstmt->setString(5, cep);
            pstmt->setString(6, id);
            pstmt->executeUpdate();
            cout << "Endereço atualizado com sucesso!\n";
        }
        else if (escolha == "4") {
            string id;
            cout << "ID do endereço para remover: "; cin >> id;

            pstmt = conn->prepareStatement("DELETE FROM Endereco WHERE id=?");
            pstmt->setString(1, id);
            pstmt->executeUpdate();
            cout << "Endereço removido com sucesso!\n";
        }
        else if (escolha == "5") {
            break;
        }
        else {
            cout << "Opção inválida.\n";
        }
    }
}

void gerenciar_apolices(sql::Connection* conn) {
    while (true) {
        cout << "--- Gerenciar Apólices ---\n";
        cout << "1. Listar Apólices\n";
        cout << "2. Adicionar Apólice\n";
        cout << "3. Atualizar Apólice\n";
        cout << "4. Remover Apólice\n";
        cout << "5. Voltar\n";
        string escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        if (escolha == "1") {
            pstmt = conn->prepareStatement("SELECT * FROM Apolice;");
            res = pstmt->executeQuery();
            while (res->next()) {
                cout << "ID: " << res->getInt("id") << ", ID do Veículo: " << res->getInt("id_veiculo")
                    << ", Valor: R$" << res->getDouble("valor") << ", Data de Início: " << res->getString("data_inicio")
                    << ", Data de Término: " << res->getString("data_termino") << "\n";
            }
            delete res;
        }
        else if (escolha == "2") {
            string id_veiculo, valor, data_inicio, data_termino;
            cout << "ID do Veículo: "; cin >> id_veiculo;
            cout << "Valor: R$ "; cin >> valor;
            cout << "Data de Início (YYYY-MM-DD): "; cin >> data_inicio;
            cout << "Data de Término (YYYY-MM-DD): "; cin >> data_termino;

            pstmt = conn->prepareStatement("INSERT INTO Apolice (id_veiculo, valor, data_inicio, data_termino) VALUES (?, ?, ?, ?)");
            pstmt->setString(1, id_veiculo);
            pstmt->setDouble(2, stod(valor));
            pstmt->setString(3, data_inicio);
            pstmt->setString(4, data_termino);
            pstmt->executeUpdate();
            cout << "Apólice adicionada com sucesso!\n";
        }
        else if (escolha == "3") {
            string id, valor, data_inicio, data_termino;
            cout << "ID da apólice para atualizar: "; cin >> id;
            cout << "Novo Valor: R$ "; cin >> valor;
            cout << "Nova Data de Início (YYYY-MM-DD): "; cin >> data_inicio;
            cout << "Nova Data de Término (YYYY-MM-DD): "; cin >> data_termino;

            pstmt = conn->prepareStatement("UPDATE Apolice SET valor=?, data_inicio=?, data_termino=? WHERE id=?");
            pstmt->setDouble(1, stod(valor));
            pstmt->setString(2, data_inicio);
            pstmt->setString(3, data_termino);
            pstmt->setString(4, id);
            pstmt->executeUpdate();
            cout << "Apólice atualizada com sucesso!\n";
        }
        else if (escolha == "4") {
            string id;
            cout << "ID da apólice para remover: "; cin >> id;

            pstmt = conn->prepareStatement("DELETE FROM Apolice WHERE id=?");
            pstmt->setString(1, id);
            pstmt->executeUpdate();
            cout << "Apólice removida com sucesso!\n";
        }
        else if (escolha == "5") {
            break;
        }
        else {
            cout << "Opção inválida.\n";
        }
    }
}

void main_menu(sql::Connection* conn) {
    while (true) {
        menu_principal();
        string escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        if (escolha == "1") {
            gerenciar_proprietarios(conn);
        }
        else if (escolha == "2") {
            gerenciar_veiculos(conn);
        }
        else if (escolha == "3") {
            gerenciar_enderecos(conn);
        }
        else if (escolha == "4") {
            gerenciar_apolices(conn);
        }
        else if (escolha == "5") {
            cout << "Encerrando o terminal...\n";
            break;
        }
        else {
            cout << "Opção inválida.\n";
        }
    }
}

int main() {
    sql::Connection* conn = conectar();

    if (conn) {
        cout << "Conexão estabelecida com sucesso!\n";
        main_menu(conn);
        conn->close();
    }
    else {
        cout << "Erro ao conectar ao banco de dados.\n";
    }

    delete conn;
    return 0;
}
