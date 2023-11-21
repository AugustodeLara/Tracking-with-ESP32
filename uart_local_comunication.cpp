#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>

struct Event {
    tm timestamp;
    int controllerId;
    std::string payload;

    // Adicione a função de comparação para eventos
    bool operator==(const Event& other) const {
        return (timestamp.tm_hour == other.timestamp.tm_hour &&
                timestamp.tm_min == other.timestamp.tm_min &&
                timestamp.tm_sec == other.timestamp.tm_sec &&
                controllerId == other.controllerId &&
                payload == other.payload);
    }
    // Adicione outros membros da estrutura, se necessário...
};

void saveEventListToFile(const std::vector<Event>& eventList, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída '" << filename << "' para escrita." << std::endl;
        return;
    }

    for (const auto& event : eventList) {
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%I:%M:%S %p", &event.timestamp);

        outputFile << "ID do Controlador: " << event.controllerId
                   << ", Payload: " << event.payload
                   << ", Data/Hora: " << event.timestamp.tm_hour << ":" << event.timestamp.tm_min << ":" << event.timestamp.tm_sec << " AM" << std::endl;
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

    tm startTime = {}; // Inicialize conforme necessário
    tm endTime = {};   // Inicialize conforme necessário

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

                    Event event;
                    if (sscanf(lineBuffer, "ID do Controlador: %d, Payload: %[^,], Data/Hora: %d:%d:%d",
                               &event.controllerId, const_cast<char*>(event.payload.c_str()),
                               &event.timestamp.tm_hour, &event.timestamp.tm_min, &event.timestamp.tm_sec) == 5) {
                        if (!isDuplicateEvent(event, eventList)) {
                            eventList.push_back(event);
                            saveEventListToFile(eventList, "eventList.txt"); // Adição aqui
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

