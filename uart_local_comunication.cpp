#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "UARTConfig.h"


struct Event {
    std::string timestamp;
    std::string controllerId;
    std::string payload;

    // Adicione a função de comparação para eventos
    bool operator==(const Event& other) const {
        return (timestamp == other.timestamp &&
                controllerId == other.controllerId &&
                payload == other.payload);
    }
    // Adicione outros membros da estrutura, se necessário...
};

// Função para converter uma string de data/hora para string
std::string parseTimestamp(const std::string& timestampString) {
    return timestampString;
}

void processPayload(const std::string& lineString, std::string& payloadData) {
    size_t payloadPos = lineString.find("Payload: ");
    payloadData = "";
    if (payloadPos != std::string::npos) {
        // Avançar para o início do payload
        payloadPos += 9;

        // Encontrar a posição da vírgula após o payload
        size_t commaPos = lineString.find(",", payloadPos);
        if (commaPos != std::string::npos) {
            // Extrair e imprimir o Accelerometer data
            payloadData = lineString.substr(payloadPos, commaPos - payloadPos);
            std::cout << "Payload IF: " << payloadData << std::endl;
        } else {
            // Se não houver vírgula, o payload é o restante da linha após "Payload: "
            payloadData = lineString.substr(payloadPos);
            std::cout << "Payload ELSE: " << payloadData << std::endl;
        }
    }
}

void processControllerId(const std::string& lineString, std::string& controllerIdData) {
    size_t controllerIdPos = lineString.find("ID do Controlador: ");
    controllerIdData = "";
    if (controllerIdPos != std::string::npos) {
        // Avançar para o início do ID do Controlador
        controllerIdPos += 19;

        // Encontrar a posição da vírgula após o ID do Controlador
        size_t commaPosID = lineString.find(",", controllerIdPos);
        if (commaPosID != std::string::npos) {
            controllerIdData = lineString.substr(controllerIdPos, commaPosID - controllerIdPos);
            std::cout << "IDCONTROLLER IF: " << controllerIdData << std::endl;
        } else {
            controllerIdData = lineString.substr(controllerIdPos);
            std::cout << "IDCONTROLLER ELSE: " << controllerIdData << std::endl;
        }
    }
}

void processTimestamp(const std::string& lineString, std::string& timestampData) {
    size_t timestampPos = lineString.find("Data/Hora: ");
    timestampData = "";
    if (timestampPos != std::string::npos) {
        // Avançar para o início do timestamp
        timestampPos += 11;

        // Extrair o timestamp até o final da linha
        timestampData = lineString.substr(timestampPos);
    }
}

void saveEventListToFile(const std::vector<Event>& eventList, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída '" << filename << "' para escrita." << std::endl;
        return;
    }

    for (const auto& event : eventList) {
        outputFile << "ID do Controlador: " << event.controllerId
                   << ", Payload: " << event.payload
                   << ", Data/Hora: " << event.timestamp << std::endl;
    }

    outputFile.close();
    std::cout << "Lista de eventos salva em " << filename << std::endl;
}

bool isDuplicateEvent(const Event& newEvent, const std::vector<Event>& eventList) {
    return std::find(eventList.begin(), eventList.end(), newEvent) != eventList.end();
}

int main() {
    UARTConfig uart("/dev/ttyACM0", B115200);

    if (!uart.openPort() || !uart.configurePort()) {
        return 1;
    }

    std::vector<Event> eventList;

    char buffer[256];
    char lineBuffer[256];
    int lineIndex = 0;

    while (true) {
        int bytesRead = read(uart.getSerialPort(), buffer, sizeof(buffer) - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] == '\n') {
                    lineBuffer[lineIndex] = '\0';
                    std::cout << "Recebido: " << lineBuffer << std::endl;

                    std::string lineString(lineBuffer);

                    std::string payloadData;
                    processPayload(lineString, payloadData);

                    std::string controllerIdData;
                    processControllerId(lineString, controllerIdData);

                    std::string timestampData;
                    processTimestamp(lineString, timestampData);

                    // Converter a string de timestamp para string e atribuir ao evento
                    Event event;
                    event.controllerId = controllerIdData; // Preencha conforme necessário
                    event.payload = payloadData;
                    event.timestamp = timestampData;

                    if (!isDuplicateEvent(event, eventList)) {
                        eventList.push_back(event);
                        saveEventListToFile(eventList, "eventList13.txt");
                    }

                    lineIndex = 0;
                } else {
                    lineBuffer[lineIndex] = buffer[i];
                    ++lineIndex;

                    if (lineIndex >= sizeof(lineBuffer)) {
                        std::cerr << "Aviso: Tamanho do buffer da linha excedido." << std::endl;
                        lineIndex = 0;
                    }
                }
            }
        } else if (bytesRead < 0) {
            std::cerr << "Erro ao ler da porta serial." << std::endl;
            break;
        }
    }

    close(uart.getSerialPort());

    return 0;
}
