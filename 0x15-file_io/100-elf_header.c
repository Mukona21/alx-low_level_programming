#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 64

void display_elf_header(Elf64_Ehdr *header);

int main(int argc, char *argv[])
{
    int fd;
    ssize_t read_bytes;
    Elf64_Ehdr header;
    
    // check the number of arguments
    if (argc != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }
    
    // open the file
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Unable to open file '%s'\n", argv[1]);
        exit(98);
    }
    
    // read the header
    read_bytes = read(fd, &header, sizeof(header));
    if (read_bytes != sizeof(header))
    {
        dprintf(STDERR_FILENO, "Error: Unable to read header from file '%s'\n", argv[1]);
        close(fd);
        exit(98);
    }
    
    // check if it is an ELF file
    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
    {
        dprintf(STDERR_FILENO, "Error: '%s' is not an ELF file\n", argv[1]);
        close(fd);
        exit(98);
    }
    
    // display the header
    display_elf_header(&header);
    
    // close the file
    close(fd);
    return 0;
}

void display_elf_header(Elf64_Ehdr *header)
{
    char *magic = (char *)header->e_ident;
    
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", magic[i]);
    printf("\n");
    
    printf("  Class:                             ");
    switch (header->e_ident[EI_CLASS])
    {
        case ELFCLASSNONE: printf("none\n"); break;
        case ELFCLASS32: printf("ELF32\n"); break;
        case ELFCLASS64: printf("ELF64\n"); break;
        default: printf("<unknown>\n"); break;
    }
    
    printf("  Data:                              ");
    switch (header->e_ident[EI_DATA])
    {
        case ELFDATANONE: printf("none\n"); break;
        case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
        default: printf("<unknown>\n"); break;
    }
    
    printf("  Version:                           %d\n", header->e_ident[EI_VERSION]);
    
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV: printf("UNIX System V ABI\n"); break;
        case ELFOSABI_HPUX: printf("HP-UX ABI\n"); break;
        case ELFOSABI_NETBSD: printf("NetBSD ABI\n"); break;
        case ELFOSABI_LINUX: printf("Linux ABI\n"); break;
        case ELFOSABI_SOLARIS: printf("Solaris ABI\n"); break;
        case ELF
