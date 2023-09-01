#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform case-insensitive string comparison
int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
            return 1;
        s1++;
        s2++;
    }
    return 0;
}

void searchAndReplace(char *line, const char *search, const char *replace, int case_sensitive) {
    char *pos;
    while ((pos = strstr(line, search)) != NULL) {
        // Replace the search term with the replace term
        int searchLength = strlen(search);
        int replaceLength = strlen(replace);
        memmove(pos + replaceLength, pos + searchLength, strlen(pos + searchLength) + 1);
        memcpy(pos, replace, replaceLength);
        line = pos + replaceLength;
    }
}

int main() {
    char filename[100];
    char search[100];
    char replace[100];
    char line[256];
    int line_number = 0;
    int case_sensitive = 0;
    char encoding[10];
    int count_occurrences = 0;

    printf("Enter the filename: ");
    scanf("%s", filename);

    printf("Enter the word or phrase to search: ");
    scanf("%s", search);

    printf("Enter the word or phrase to replace (or leave blank for search only): ");
    scanf("%s", replace);

    if (strlen(replace) > 0) {
        printf("Do you want a case-sensitive search and replace? (0 for no, 1 for yes): ");
        scanf("%d", &case_sensitive);
    }

    printf("Enter the file encoding (e.g., utf-8, ascii): ");
    scanf("%s", encoding);

    printf("Do you want to count the total occurrences of '%s' in '%s'? (0 for no, 1 for yes): ", search, filename);
    scanf("%d", &count_occurrences);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    printf("Occurrences of '%s' in '%s':\n", search, filename);

    int total_occurrences = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char line_copy[256];
        strcpy(line_copy, line);

        char *line_ptr = line;
        char *search_ptr = search;

        if (!case_sensitive) {
            // Convert both line and search string to lowercase for case-insensitive search
            while (*line_ptr != '\0') {
                *line_ptr = tolower((unsigned char)*line_ptr);
                line_ptr++;
            }
            while (*search_ptr != '\0') {
                *search_ptr = tolower((unsigned char)*search_ptr);
                search_ptr++;
            }
        }

        if (strstr(line, search) != NULL) {
            if (strlen(replace) > 0) {
                searchAndReplace(line_copy, search, replace, case_sensitive);
                printf("Line %d (Replaced): %s", line_number, line_copy);
            } else {
                printf("Line %d: %s", line_number, line);
            }
            if (count_occurrences) {
                total_occurrences++;
            }
        }
    }

    fclose(file);

    if (count_occurrences) {
        printf("Total occurrences of '%s' in '%s': %d\n", search, filename, total_occurrences);
    }

    return 0;
}
