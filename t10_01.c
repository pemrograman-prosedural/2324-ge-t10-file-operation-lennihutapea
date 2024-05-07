// 12S23023 - Lenni Febriyani
// 12S23031 - Matthew Pangihutan

#include <stdio.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/repository.h"

void get_line(FILE *_stream, char *_buffer, unsigned int _size)
{
    char ch = '\0';
    unsigned int i = 0;
    _buffer[i] = '\0';
    while (i < _size && (ch = fgetc(_stream)) != '\n')
    {
        if (ch == '\r')
        {
            continue;
        }
        if (ch == '\n')
        {
            break;
        }
        _buffer[i++] = ch;
        _buffer[i] = '\0';
    }
}

int main(int _argc, char **_argv)
{
struct dorm_t *dorms = malloc(100 * sizeof(struct dorm_t));
    struct student_t *students = malloc(100 * sizeof(struct student_t));
    char input[100];
    char id[12];
    char student_name[40];
    char year[5];
    char dorm_name[40];
    unsigned short capacity;
    char *tesk_sementara;
    int idx_s, idx_d;
    int std = 0, dr = 0;
    char *data;

    FILE *open_file_student = NULL;
    //  FILE *output_file_student = NULL;
    FILE *open_file_dorm = NULL;
    open_file_student = fopen("storage/student-repository.txt", "r");
    open_file_dorm = fopen("storage/dorm-repository.txt", "r");

    // output_file_student = fopen("./storage/student-repository.txt", "a");

    while (1)
    {
        char buffer[100];
        buffer[0] = '\0';
        get_line(open_file_dorm, buffer, 100);
        if (feof(open_file_dorm))
        {
            break;
        }
        data = strtok(buffer, "|");
        strcpy(dorm_name, data);
        data = strtok(NULL, "|");
        capacity = atoi(data);
        data = strtok(NULL, "|");
        if (strcmp(data, "male") == 0)
        {
            dorms[dr] = create_dorm(dorm_name, capacity, GENDER_MALE);
        }
        else if (strcmp(data, "female") == 0)
        {
            dorms[dr] = create_dorm(dorm_name, capacity, GENDER_FEMALE);
        }
        dr++;
    }

    while (1)
    {
        char buffer[100];
        buffer[0] = '\0';
        get_line(open_file_student, buffer, 100);
        if (feof(open_file_student))
        {
            break;
        }
        tesk_sementara = strtok(buffer, "|");
        strcpy(id, tesk_sementara);
        tesk_sementara = strtok(NULL, "|");
        strcpy(student_name, tesk_sementara);
        tesk_sementara = strtok(NULL, "|");
        strcpy(year, tesk_sementara);
        tesk_sementara = strtok(NULL, "|");
        if (strcmp(tesk_sementara, "male") == 0)
        {
            students[std] = create_student(id, student_name, year, GENDER_MALE);
        }
        else if (strcmp(tesk_sementara, "female") == 0)
        {
            students[std] = create_student(id, student_name, year, GENDER_FEMALE);
        }
        std++;
    }
    fclose(open_file_student);
    do
    {
        fflush(stdin);
        input[0] = '\0';
        int c = 0;
        while (1)
        {
            char x = getchar();
            if (x == '\r')
            {
                continue;
            }
            if (x == '\n')
            {
                break;
            }
            input[c] = x;
            input[++c] = '\0';
        }
        data = strtok(input, "#");
        if (strcmp(data, "---") == 0)
        {
            break;
        }
        else if (strcmp(data, "student-print-all") == 0)
        {
            print_student(students, std);
        }
        else if (strcmp(data, "student-print-all-detail") == 0)
        {
            print_student_detail(students, std);
        }
        else if (strcmp(data, "student-add") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(student_name, data);
            data = strtok(NULL, "#");
            strcpy(year, data);
            data = strtok(NULL, "#");
            if (strcmp(data, "male") == 0)
            {
                students[std] = create_student(id, student_name, year, GENDER_MALE);
            }
            else if (strcmp(data, "female") == 0)
            {
                students[std] = create_student(id, student_name, year, GENDER_FEMALE);
            }
            std++;
        }
        else if (strcmp(data, "dorm-print-all") == 0)
        {
            print_dorm(dorms, dr);
        }
        else if (strcmp(data, "dorm-print-all-detail") == 0)
        {
            print_detaildorm(dorms, dr);
        }
        else if (strcmp(input, "dorm-add") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            data = strtok(NULL, "#");
            capacity = atoi(data);
            data = strtok(NULL, "#");
            if (strcmp(data, "male") == 0)
            {
                dorms[dr] = create_dorm(dorm_name, capacity, GENDER_MALE);
            }
            else if (strcmp(data, "female") == 0)
            {
                dorms[dr] = create_dorm(dorm_name, capacity, GENDER_FEMALE);
            }
            dr++;
        }
        else if (strcmp(data, "assign-student") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            idx_s = 0;
            idx_d = 0;
            for (int w = 0; w < std; w++)
            {
                if (strcmp(students[w].id, id) == 0)
                {
                    idx_s = w;
                    break;
                }
            }
            for (int w = 0; w < std; w++)
            {
                if (strcmp(dorms[w].name, dorm_name) == 0)
                {
                    idx_d = w;
                    break;
                }
            }
            assign_student(&students[idx_s], &dorms[idx_d], id, dorm_name);
        }
        else if (strcmp(data, "move-student") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            idx_s = 0;
            idx_d = 0;
            for (int w = 0; w < std; w++)
            {
                if (strcmp(students[w].id, id) == 0)
                {
                    idx_s = w;
                    break;
                }
            }
            for (int w = 0; w < dr; w++)
            {
                if (strcmp(dorms[w].name, dorm_name) == 0)
                {
                    idx_d = w;
                    break;
                }
            }
            if (students[idx_s].dorm == NULL)
            {
                assign_student(&students[idx_s], &dorms[idx_d], id, dorm_name);
            }
            else
            {
                for (int w = 0; w < dr; w++)
                {
                    if (strcmp(students[idx_s].dorm->name, dorms[w].name) == 0)
                    {
                        move_student(&students[idx_s], &dorms[idx_d], &dorms[w], id, dorm_name);
                        break;
                    }
                }
            }
        }
    } while (1);
    free(students);
    free(dorms);
    
    return 0;
}