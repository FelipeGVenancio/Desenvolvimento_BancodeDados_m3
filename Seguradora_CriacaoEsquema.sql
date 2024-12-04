-- CRIAÇÃO DE ESQUEMA E TABELAS
CREATE SCHEMA seguradora_porto;
use seguradora_porto;
-- SET SQL_SAFE_UPDATES = 0;
-- DROP SCHEMA seguradora_porto;

-- Proprietario(id, cpf, nome, email, fone)]
-- DROP TABLE Proprietario;
CREATE TABLE Proprietario (
    id integer PRIMARY KEY auto_increment,    
    cpf varchar(12) NOT NULL UNIQUE,
	nome varchar(100) NOT NULL,
    email varchar(200) UNIQUE,
    fone varchar(16) NOT NULL
);

-- Veiculo(id, id_resp, placa, modelo, ano, cor, fotos)
-- DROP TABLE Veiculo;
CREATE TABLE Veiculo (
    id INT PRIMARY KEY auto_increment,
	id_resp INT NOT NULL,
    placa VARCHAR(7) NOT NULL UNIQUE,
    modelo VARCHAR(100) NOT NULL,
	ano date,
	cor VARCHAR(100),
	fotos VARCHAR(100),
    CONSTRAINT fk_veiculo_resp FOREIGN KEY (id_resp) REFERENCES Proprietario(id)
);

-- Proprietario_endereço(id, id_tutor, cep, rua, numero, complemento, cidade, uf)
-- DROP TABLE Proprietario_endereco;
CREATE TABLE Proprietario_endereco (
    id INT PRIMARY KEY auto_increment,
	id_resp integer NOT NULL,
	cep varchar(12) NOT NULL,
    rua varchar(100),
    numero integer NOT NULL,
    compl varchar(50),
    cidade varchar(50),
    uf varchar(2),
	CONSTRAINT fk_propend_prop FOREIGN KEY (id_resp) REFERENCES Proprietario(id)
	-- ON DELETE CASCADE
);

-- Apolice(id, id_resp, id_veiculo, premio, dt_validade, cobertura)
-- DROP TABLE Apolice;
CREATE TABLE Apolice (
    id INT PRIMARY KEY auto_increment,
	id_resp INT NOT NULL,
    id_veiculo INT NOT NULL,
  	premio decimal(5,2),
    dt_validade date,
    cobertura varchar(99),
    CONSTRAINT fk_apl_resp FOREIGN KEY (id_resp) REFERENCES Proprietario(id), 
    CONSTRAINT fk_apl_veiculo FOREIGN KEY (id_veiculo) REFERENCES Veiculo(id)
);


