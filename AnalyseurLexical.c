#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    PROGRAM_TOKEN,
    VAR_TOKEN,
    CONST_TOKEN,
    PV_TOKEN,
    ID_TOKEN,
    PRG_TOKEN,
    PRD_TOKEN,
    END_TOKEN,
    EGAL_TOKEN,
    BEGIN_TOKEN,
    VIRG_TOKEN,
    AFFECT_TOKEN,
    THEN_TOKEN,
    IF_TOKEN,
    WHILE_TOKEN,
    WRITE_TOKEN,
    READ_TOKEN,
    DO_TOKEN,
    NUM_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    DIFF_TOKEN,
    SUP_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUPEG_TOKEN,
    MOINS_TOKEN,
    MULTI_TOKEN,
    DIV_TOKEN,
    DIEZE_TOKEN,
    ERREUR_TOKEN
} TokenType;

typedef struct
{
    TokenType cls;
    char nom[256];
} TSym_Cour;

TSym_Cour symCour; 
char car_cour;
FILE *file;

void Lire_Car()
{
    car_cour = fgetc(file);
}

void Erreur(const char *code_err)
{
    printf("Erreur: %s\n", code_err);
}

void lire_mot()
{
    int i = 0;
    while (isalpha(car_cour) && i < 255)
    {
        symCour.nom[i++] = car_cour;
        Lire_Car();
    }
    symCour.nom[i] = '\0';
    if (strcmp(symCour.nom, "const") == 0)
    {
        symCour.cls = CONST_TOKEN;
    } else if(strcmp(symCour.nom, "program") == 0)
    {
        symCour.cls = PROGRAM_TOKEN;
    } else if(strcmp(symCour.nom, "var") == 0)
    {
        symCour.cls = VAR_TOKEN;
    } else if(strcmp(symCour.nom, "begin") == 0)
    {
        symCour.cls = BEGIN_TOKEN;
    } else if(strcmp(symCour.nom, "end") == 0)
    {
        symCour.cls = END_TOKEN;
    } else if(strcmp(symCour.nom, "if") == 0)
    {
        symCour.cls = IF_TOKEN;
    } else if(strcmp(symCour.nom, "then") == 0)
    {
        symCour.cls = THEN_TOKEN;
    } else if(strcmp(symCour.nom, "while") == 0)
    {
        symCour.cls = WHILE_TOKEN;
    } else if(strcmp(symCour.nom, "do") == 0)
    {
        symCour.cls = DO_TOKEN;
    } else if(strcmp(symCour.nom, "read") == 0)
    {
        symCour.cls = READ_TOKEN;
    } else if(strcmp(symCour.nom, "write") == 0)
    {
        symCour.cls = WRITE_TOKEN;
    } else
    {
        symCour.cls = ID_TOKEN;
    }
}

void lire_nombre()
{
    int i = 0;
    while (isdigit(car_cour) && i < 255)
    {
        symCour.nom[i++] = car_cour;
        Lire_Car();
    }
    symCour.nom[i] = '\0';
    symCour.cls = NUM_TOKEN;
}

void AfficherToken(TSym_Cour SYM)
{
    switch (SYM.cls)
    {
    case PROGRAM_TOKEN:
        printf("%s          %s\n", SYM.nom, "PROGRAM_TOKEN");
        break;
    case VAR_TOKEN:
        printf("%s          %s\n", SYM.nom, "VAR_TOKEN");
        break;
    case CONST_TOKEN:
        printf("%s          %s\n", SYM.nom, "CONST_TOKEN");
        break;
    case PV_TOKEN:
        printf("%s          %s\n", " ;     ", "PV_TOKEN");
        break;
    case ID_TOKEN:
        printf("%s          %s\n", SYM.nom, "ID_TOKEN");
        break;
    case PRG_TOKEN:
        printf("%s          %s\n", " (     ", "PRG_TOKEN");
        break;
    case PRD_TOKEN:
        printf("%s          %s\n", "  )    ", "PRD_TOKEN");
        break;
    case END_TOKEN:
        printf("%s          %s\n", SYM.nom, "END_TOKEN");
        break;
    case EGAL_TOKEN:
        printf("%s          %s\n", "  =    ", "EGAL_TOKEN");
        break;
    case BEGIN_TOKEN:
        printf("%s          %s\n", SYM.nom, "BEGIN_TOKEN");
        break;
    case VIRG_TOKEN:
        printf("%s          %s\n", "  ,    ", "VIRG_TOKEN");
        break;
    case AFFECT_TOKEN:
        printf("%s          %s\n", "  :=   ", "AFFECT_TOKEN");
        break;
    case THEN_TOKEN:
        printf("%s          %s\n", SYM.nom, "THEN_TOKEN");
        break;
    case IF_TOKEN:
        printf("%s          %s\n", SYM.nom, "IF_TOKEN");
        break;
    case WHILE_TOKEN:
        printf("%s          %s\n", SYM.nom, "WHILE_TOKEN");
        break;
    case WRITE_TOKEN:
        printf("%s          %s\n", SYM.nom, "WRITE_TOKEN");
        break;
    case READ_TOKEN:
        printf("%s          %s\n", SYM.nom, "READ_TOKEN");
        break;
    case DO_TOKEN:
        printf("%s          %s\n", SYM.nom, "DO_TOKEN");
        break;
    case NUM_TOKEN:
        printf("%s          %s\n", SYM.nom, "NUM_TOKEN");
        break;
    case PT_TOKEN:
        printf("%s          %s\n", "  .    ", "PT_TOKEN");
        break;
    case PLUS_TOKEN:
        printf("%s          %s\n", "  +    ", "PLUS_TOKEN");
        break;
    case DIFF_TOKEN:
        printf("%s          %s\n", "  <>   ", "DIFF_TOKEN");
        break;
    case SUP_TOKEN:
        printf("%s          %s\n", "  >    ", "SUP_TOKEN");
        break;
    case INF_TOKEN:
        printf("%s          %s\n", "  <    ", "INF_TOKEN");
        break;
    case INFEG_TOKEN:
        printf("%s          %s\n", "  <=   ", "INFEG_TOKEN");
        break;
    case SUPEG_TOKEN:
        printf("%s          %s\n", "  >=   ", "SUPEG_TOKEN");
        break;
    case MOINS_TOKEN:
        printf("%s          %s\n", "  -    ", "MOINS_TOKEN");
        break;
    case MULTI_TOKEN:
        printf("%s          %s\n", "  *    ", "MULTI_TOKEN");
        break;
    case DIV_TOKEN:
        printf("%s          %s\n", "  /    ", "DIV_TOKEN");
        break;
    case DIEZE_TOKEN:
        printf("%s          %s\n", "  EOF  ", "DIEZE_TOKEN");
        break;
    default:
        printf("%s", "ERR_TOKEN");
        break;
    }
}

void Sym_Suiv()
{
    while (isspace(car_cour))
    {
        Lire_Car();
    }

    if (isalpha(car_cour))
    {
        lire_mot();
    }
    else if (isdigit(car_cour))
    {
        lire_nombre();
    }
    else
    {
        switch (car_cour)
        {
        case '+':
            symCour.cls = PLUS_TOKEN;
            strcpy(symCour.nom, "+");
            Lire_Car();
            break;
        case '-':
            symCour.cls = MOINS_TOKEN;
            strcpy(symCour.nom, "-");
            Lire_Car();
            break;
        case '*':
            symCour.cls = MULTI_TOKEN;
            strcpy(symCour.nom, "*");
            Lire_Car();
            break;
        case '/':
            symCour.cls = DIV_TOKEN;
            strcpy(symCour.nom, "/");
            Lire_Car();
            break;
        case '=':
            symCour.cls = EGAL_TOKEN;
            strcpy(symCour.nom, "=");
            Lire_Car();
            break;
        case ';':
            symCour.cls = PV_TOKEN;
            strcpy(symCour.nom, ";");
            Lire_Car();
            break;
        case ',':
            symCour.cls = VIRG_TOKEN;
            strcpy(symCour.nom, ",");
            Lire_Car();
            break;
        case '.':
            symCour.cls = PT_TOKEN;
            strcpy(symCour.nom, ".");
            Lire_Car();
            break;
        case '(':
            symCour.cls = PRG_TOKEN;
            strcpy(symCour.nom, "(");
            Lire_Car();
            break;
        case ')':
            symCour.cls = PRD_TOKEN;
            strcpy(symCour.nom, ")");
            Lire_Car();
            break;
        case '<':
            Lire_Car();
            if (car_cour == '=')
            {
                symCour.cls = INFEG_TOKEN;
                strcpy(symCour.nom, "<=");
                Lire_Car();
            }
            else if (car_cour == '>')
            {
                symCour.cls = DIFF_TOKEN;
                strcpy(symCour.nom, "<>");
                Lire_Car();
            }
            else
            {
                symCour.cls = INF_TOKEN;
                strcpy(symCour.nom, "<");
            }
            break;
        case '>':
            Lire_Car();
            if (car_cour == '=')
            {
                symCour.cls = SUPEG_TOKEN;
                strcpy(symCour.nom, ">=");
                Lire_Car();
            }
            else
            {
                symCour.cls = SUP_TOKEN;
                strcpy(symCour.nom, ">");
            }
            break;
        case ':':
            Lire_Car();
            if (car_cour == '=')
            {
                symCour.cls = AFFECT_TOKEN;
                strcpy(symCour.nom, ":=");
                Lire_Car();
            }
            else
            {
                symCour.cls = ERREUR_TOKEN;
                strcpy(symCour.nom, ":");
                Erreur("Caractère ':' inconnu ou incomplet");
            }
            break;
        case EOF:
            symCour.cls = DIEZE_TOKEN;
            strcpy(symCour.nom, "EOF");
            break;
        default:
            symCour.cls = ERREUR_TOKEN;
            Erreur("Caractère inconnu");
            Lire_Car();
            break;
        }
    }
    AfficherToken(symCour);
}

int main()
{
    char filename[256];

    printf("Enter the filename: ");
    scanf("%255s", filename);
    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }
    Lire_Car();

    while (symCour.cls != DIEZE_TOKEN)
    {
        Sym_Suiv();
    }
    fclose(file);
    return 0;
}
