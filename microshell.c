#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int ft_strlen(char *str){
    int i = 0;
    while (i[str]) i++;
    return i;
}

int ft_error(char *str){
    write(2, str, ft_strlen(str));
    return 1;
}

int ft_cd(char **av , int i){
    return i != 2?  ft_error("error: cd: bad arguments\n"): chdir(1[av]) == -1? ft_error("error: cd: cannot change directory to "), ft_error(1[av]), ft_error("\n"): 0;
}

int ft_exec(char **av, char **ev, int i){
    int fd[2], code, sep = i[av] && !strcmp(i[av], "|");
    if (sep && pipe(fd) == -1) return ft_error("error: fatal\n");
    int pid = fork();
    if (!pid){
        av[i] = 0;
        if (sep && (dup2(1[fd], 1) == -1 || close(1[fd]) == -1 || close(0[fd]) == -1)) return ft_error("error: fatal\n");
        execve(*av, av, ev);
        return ft_error("error: cannot execute "), ft_error(*av), ft_error("\n");
    }
    waitpid(pid, &code, 0);
    if (sep && (dup2(0[fd], 0) == -1 || close(1[fd]) == -1 || close(0[fd]) == -1)) return ft_error("error: fatal\n");
    return WEXITSTATUS(code);
}

int main(int ac, char **av, char **ev){
    int i = 0, code = 0;
    if (ac > 1){
        while (i++[av] && i[av]){
            av += i;
            i = 0;
            while (i[av] && strcmp(i[av], "|") && strcmp(i[av], ";")) i++;
            !strcmp(*av, "cd")? code = ft_cd(av, i): i? code = ft_exec(av, ev, i): 0;
        }
    }
    return code;
}
