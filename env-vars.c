#include "shell.h"

int display_env_vars(info_t *details) {
    display_str_list(details->env);
    return 0;
}

char *find_env_value(info_t *details, const char *name) {
    list_t *element = details->env;
    char *match;

    while (element) {
        match = match_prefix(element->str, name);
        if (match && *match)
            return match;
        element = element->next;
    }

    return NULL;
}

int set_env_variable(info_t *details) {
    if (details->argc != 3) {
        error_puts("Invalid number of arguments\n");
        return 1;
    }

    if (update_env(details, details->argv[1], details->argv[2]))
        return 0;

    return 1;
}

int remove_env_variable(info_t *details) {
    int index;

    if (details->argc < 2) {
        error_puts("Insufficient arguments.\n");
        return -1;
    }

    for (index = 1; index < details->argc; index++) {
        if (!unset_environment(details, details->argv[index])) {
            error_puts("Could not remove environment variable.\n");
            return -1;
        }
    }

    return 0;
}

int fill_env_list(info_t *details) {
    list_t *element = NULL;
    size_t index;

    for (index = 0; environ[index]; index++)
        append_node(&element, environ[index]);

    details->env = element;
    return 0;
}
