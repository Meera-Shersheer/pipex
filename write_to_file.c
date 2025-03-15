#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Open (or create) the file for writing
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        // Handle error if file couldn't be opened
        perror("Error opening file");
        return 1;
    }

    // Write a message to the file
    const char *message = "Hello, this is a test message!";
    if (write(fd, message, 29) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file descriptor after writing
    close(fd);
    printf("Message written to output.txt\n");

    return 0;
}

