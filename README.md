# 📟 Projeto FreeRTOS – Sistema de Monitoramento com 3 Tarefas

Este projeto simula um sistema embarcado utilizando o sistema operacional de tempo real **FreeRTOS**, implementado em C, e com três tarefas principais: leitura de botão, processamento e controle de LED. Ele foi desenvolvido como parte das atividades do programa **Embarcatech**.

## 👨‍💻 Autor

**Carlos Michael da Silva Sousa**

## 🎯 Objetivo

Criar uma aplicação embarcada que utilize **três tarefas concorrentes**, implementadas com FreeRTOS, para simular um sistema de monitoramento simples com **botão e LED**. O projeto foi estruturado para demonstrar a comunicação entre tarefas e o controle cooperativo em tempo real.

## 🧠 Estrutura do Projeto

- **Tarefa 1 – Leitura do Botão:** executada a cada 100ms, simula a leitura de um botão físico.
- **Tarefa 2 – Processamento:** recebe o estado do botão e decide se deve acionar a tarefa do LED.
- **Tarefa 3 – Controle do LED:** controla o LED com base nas instruções da Tarefa 2 (liga/desliga).

A comunicação entre as tarefas é feita utilizando **filas (queues)** do FreeRTOS, garantindo sincronização e troca de dados eficiente.

## 🛠️ Tecnologias e Ferramentas

- Linguagem C
- FreeRTOS
- Ambiente de desenvolvimento para embarcados (ex: VS Code + SDK)
- Simulação de GPIOs (botão e LED)

## 🔄 Fluxo de Execução

1. A **Tarefa 1** verifica o estado do botão (simulado) e envia para uma fila.
2. A **Tarefa 2** lê essa fila, e se detectar o botão pressionado, envia sinal para a Tarefa 3.
3. A **Tarefa 3** acende ou apaga o LED com base na mensagem recebida.

## 📂 Organização de Arquivos
project_with_rtos/ 

├── main.c # Código principal do projeto com criação das tarefas 

├── FreeRTOSConfig.h # Configurações do FreeRTOS 

├── CMakeLists.txt # Script de build 

└── README.md


## 💡 Como Rodar

1. Clone o repositório:
   ```bash
   git clone https://github.com/Seinenk/Projeto_FreeRTOS.git

2. Configure o SDK e toolchain para sua placa (ex: Raspberry Pi Pico).

3. Compile o projeto com CMake.

4. Carregue o .uf2 na sua placa embarcada.

5. Observe a execução das tarefas no terminal ou simulador.

## ✅ Resultados

- O LED responde corretamente à simulação do botão.

- As tarefas se comunicam de forma sincronizada via fila.

- O sistema é modular e expansível para projetos maiores com múltiplos sensores e atuadores.
