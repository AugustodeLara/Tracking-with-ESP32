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
    int serialPort = open("/dev/ttyACM0", O_RDWR);

    if (serialPort == -1) {
        std::cerr << "Erro ao abrir a porta serial." << std::endl;
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Erro ao obter os atributos da porta serial." << std::endl;
        return 1;
    }

    // Configuração da porta serial...
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (cfsetispeed(&tty, B115200) != 0 || cfsetospeed(&tty, B115200) != 0) {
        std::cerr << "Erro ao configurar a velocidade da porta serial." << std::endl;
        return 1;
    }

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        std::cerr << "Erro ao aplicar os atributos da porta serial." << std::endl;
        return 1;
    }
    // Fim da configuração da porta serial

    std::vector<Event> eventList;

    char buffer[256];
    char lineBuffer[256];
    int lineIndex = 0;

    while (true) {
        int bytesRead = read(serialPort, buffer, sizeof(buffer) - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] == '\n') {
                    lineBuffer[lineIndex] = '\0';
                    std::cout << "Recebido: " << lineBuffer << std::endl;

                    std::string lineString(lineBuffer);

                    // Encontrar a posição da string "Payload: "
                    size_t payloadPos = lineString.find("Payload: ");
                    std::string payloadData = "";
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

                    // Encontrar a posição da string "ID do Controlador: "
                    size_t controllerIdPos = lineString.find("ID do Controlador: ");
                    std::string controllerIdData = "";
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

                    size_t timestampPos = lineString.find("Data/Hora: ");
                    std::string timestampData = "";
                    if (timestampPos != std::string::npos) {
                        // Avançar para o início do timestamp
                        timestampPos += 12;

                        // Extrair o timestamp
                        timestampData = lineString.substr(timestampPos);

                        // Remover espaços extras
                        timestampData.erase(std::remove_if(timestampData.begin(), timestampData.end(), ::isspace), timestampData.end());

                        // Converter a string de timestamp para string e atribuir ao evento
                        Event event;
                        event.controllerId = controllerIdData; // Preencha conforme necessário
                        event.payload = payloadData;
                        event.timestamp = timestampData;

                        if (!isDuplicateEvent(event, eventList)) {
                            eventList.push_back(event);
                            saveEventListToFile(eventList, "eventList1690.txt");
                        }
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

    close(serialPort);

    return 0;
}
