#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

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

    char buffer[256];

    while (true) {
        int bytesRead = read(serialPort, buffer, sizeof(buffer) - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Adiciona null terminator

            // Verifica se os dados contêm apenas caracteres imprimíveis
            for (int i = 0; i < bytesRead; ++i) {
                if (!isprint(buffer[i])) {
                    std::cerr << "Aviso: Caractere não imprimível detectado." << std::endl;
                    // Pode decidir o que fazer em caso de caractere não imprimível
                }
            }

            std::cout << "Recebido: " << buffer << std::endl;
        } else if (bytesRead < 0) {
            std::cerr << "Erro ao ler da porta serial." << std::endl;
            break;
        }
    }

    close(serialPort);

    return 0;
}

