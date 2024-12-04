#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
    ELSE_TOKEN,
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
    FOR_TOKEN,
    TO_TOKEN,
    DOWNTO_TOKEN,
    DIEZE_TOKEN,
    ERREUR_TOKEN
} TokenType;

typedef enum
{
    TPROG,
    TCONST,
    TVAR,
} TSYM;

typedef struct
{
    char Nom[100];
    TSYM TIDF;
    int Adresse;
    int Value; // For constants
} T_TAB_IDF;

typedef struct
{
    TokenType cls;
    char nom[256];
} TSym_Cour;

typedef enum{
    ADD,
    SUB,
    MUL,
    DIV,
    EQL,
    NEQ,
    GTR,
    LSS,
    GEQ,
    LEQ,
    PRN,
    INN,
    INTc,
    LDIv,
    LDAa,
    LDV,
    STO,
    BRNi,
    BZEi,
    HLT,
} P_code;

typedef struct{
    P_code code[200];
    int arg[200];
    int PC;
    int offset;
} P_table;

P_table p_table;

void initialize_p_table() {
    p_table.PC = -1;
    p_table.offset = 0;
}

void Generer1(P_code code) {
    if(p_table.PC >= 199) {
        printf("Program too long\n");
        exit(1);
    }
    p_table.PC++;
    p_table.code[p_table.PC] = code;
    p_table.arg[p_table.PC] = 0;
}

void Generer2(P_code code, int arg) {
    if(p_table.PC >= 199) {
        printf("Program too long\n");
        exit(1);
    }
    p_table.PC++;
    p_table.code[p_table.PC] = code;
    p_table.arg[p_table.PC] = arg;
}

TSym_Cour symCour;
TSym_Cour symPre;
char car_cour;
FILE *file;
T_TAB_IDF TAB_IDFS[100];
int NBR_IDFS = 0;
int line_number = 1;

void AfficherToken(TSym_Cour SYM);
void Sym_Suiv();
void Erreur(const char *code_err);
void INSTS();
void Lire_Car();
void testSymbole(TokenType token);
void CONST_DECL();
void VAR_DECL();
void Bloc();
void EXP();
void TERM();
void FACT();
void COND();
void INST();
void Program();
int rechercherIDFConst(char *nom);
int rechercherIDFVar(char *nom);
int rechercherIDF(char *nom);
int IDexists(char *nom);
void printSymbolTable();
void printPCode();
void toLowerCase(char *str);
int getAdresse(char *nom);
TSYM getIdType(char *nom);
int getValue(char *nom);

int rechercherIDFConst(char *nom)
{
    int i = 0;
    while (i < NBR_IDFS)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0 && TAB_IDFS[i].TIDF == TCONST)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int rechercherIDFVar(char *nom)
{
    int i = 0;
    while (i < NBR_IDFS)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0 && TAB_IDFS[i].TIDF == TVAR)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int rechercherIDF(char *nom)
{
    int i = 0;
    while (i < NBR_IDFS)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int IDexists(char *nom)
{
    int i = 0;
    while (i < NBR_IDFS)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int getAdresse(char *nom)
{
    for (int i = 0; i < NBR_IDFS; i++)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0)
        {
            return TAB_IDFS[i].Adresse;
        }
    }
    Erreur("Variable not found in symbol table");
    return -1;
}

TSYM getIdType(char *nom)
{
    for (int i = 0; i < NBR_IDFS; i++)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0)
        {
            return TAB_IDFS[i].TIDF;
        }
    }
    Erreur("Identifier not found in symbol table");
    return -1;
}

int getValue(char *nom)
{
    for (int i = 0; i < NBR_IDFS; i++)
    {
        if (strcmp(TAB_IDFS[i].Nom, nom) == 0)
        {
            return TAB_IDFS[i].Value;
        }
    }
    Erreur("Identifier not found in symbol table");
    return -1;
}

const char *getTokenName(TokenType token)
{
    switch (token)
    {
    case PROGRAM_TOKEN:
        return "PROGRAM_TOKEN";
    case VAR_TOKEN:
        return "VAR_TOKEN";
    case CONST_TOKEN:
        return "CONST_TOKEN";
    case PV_TOKEN:
        return "PV_TOKEN";
    case ID_TOKEN:
        return "ID_TOKEN";
    case PRG_TOKEN:
        return "PRG_TOKEN";
    case PRD_TOKEN:
        return "PRD_TOKEN";
    case END_TOKEN:
        return "END_TOKEN";
    case EGAL_TOKEN:
        return "EGAL_TOKEN";
    case BEGIN_TOKEN:
        return "BEGIN_TOKEN";
    case VIRG_TOKEN:
        return "VIRG_TOKEN";
    case AFFECT_TOKEN:
        return "AFFECT_TOKEN";
    case THEN_TOKEN:
        return "THEN_TOKEN";
    case IF_TOKEN:
        return "IF_TOKEN";
    case ELSE_TOKEN:
        return "ELSE_TOKEN";
    case WHILE_TOKEN:
        return "WHILE_TOKEN";
    case WRITE_TOKEN:
        return "WRITE_TOKEN";
    case READ_TOKEN:
        return "READ_TOKEN";
    case DO_TOKEN:
        return "DO_TOKEN";
    case FOR_TOKEN:
        return "FOR_TOKEN";
    case TO_TOKEN:
        return "TO_TOKEN";
    case DOWNTO_TOKEN:
        return "DOWNTO_TOKEN";
    case NUM_TOKEN:
        return "NUM_TOKEN";
    case PT_TOKEN:
        return "PT_TOKEN";
    case PLUS_TOKEN:
        return "PLUS_TOKEN";
    case DIFF_TOKEN:
        return "DIFF_TOKEN";
    case SUP_TOKEN:
        return "SUP_TOKEN";
    case INF_TOKEN:
        return "INF_TOKEN";
    case INFEG_TOKEN:
        return "INFEG_TOKEN";
    case SUPEG_TOKEN:
        return "SUPEG_TOKEN";
    case MOINS_TOKEN:
        return "MOINS_TOKEN";
    case MULTI_TOKEN:
        return "MULTI_TOKEN";
    case DIV_TOKEN:
        return "DIV_TOKEN";
    case DIEZE_TOKEN:
        return "DIEZE_TOKEN";
    case ERREUR_TOKEN:
        return "ERREUR_TOKEN";
    default:
        return "UNKNOWN_TOKEN";
    }
}

void testSymbole(TokenType token)
{
    if (symCour.cls == token)
    {
        symPre = symCour;
        Sym_Suiv();
    }
    else
    {
        printf("Expected token: %s but found token: %s\n", getTokenName(token), getTokenName(symCour.cls));
        printf("Token: %s\n", symCour.nom);
        Erreur("Syntax error");
    }
}

void CONST_DECL()
{
    if (symCour.cls == CONST_TOKEN)
    {
        testSymbole(CONST_TOKEN);

        do
        {
            testSymbole(ID_TOKEN);
            toLowerCase(symPre.nom);
            if (IDexists(symPre.nom))
            {
                Erreur("Identifier already declared");
            }
            else
            {
                TAB_IDFS[NBR_IDFS].TIDF = TCONST;
                strncpy(TAB_IDFS[NBR_IDFS].Nom, symPre.nom, sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1);
                TAB_IDFS[NBR_IDFS].Nom[sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1] = '\0';
                NBR_IDFS++;
            }
            testSymbole(EGAL_TOKEN);
            testSymbole(NUM_TOKEN);
            int value = atoi(symPre.nom);
            TAB_IDFS[NBR_IDFS - 1].Value = value;

            testSymbole(PV_TOKEN);
        } while (symCour.cls == ID_TOKEN);
    }
}

void VAR_DECL()
{
    if (symCour.cls == VAR_TOKEN)
    {
        testSymbole(VAR_TOKEN);
        do
        {
            testSymbole(ID_TOKEN);
            toLowerCase(symPre.nom);
            if (IDexists(symPre.nom))
            {
                Erreur("Duplicate identifier declaration");
            }
            else
            {
                TAB_IDFS[NBR_IDFS].TIDF = TVAR;
                strncpy(TAB_IDFS[NBR_IDFS].Nom, symPre.nom, sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1);
                TAB_IDFS[NBR_IDFS].Nom[sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1] = '\0';
                TAB_IDFS[NBR_IDFS].Adresse = p_table.offset;
                NBR_IDFS++;
                p_table.offset++;
            }
            while (symCour.cls == VIRG_TOKEN)
            {
                testSymbole(VIRG_TOKEN);
                testSymbole(ID_TOKEN);
                toLowerCase(symPre.nom);
                if (IDexists(symPre.nom))
                {
                    Erreur("Duplicate identifier declaration");
                }
                else
                {
                    TAB_IDFS[NBR_IDFS].TIDF = TVAR;
                    strncpy(TAB_IDFS[NBR_IDFS].Nom, symPre.nom, sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1);
                    TAB_IDFS[NBR_IDFS].Nom[sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1] = '\0';
                    TAB_IDFS[NBR_IDFS].Adresse = p_table.offset;
                    NBR_IDFS++;
                    p_table.offset++;
                }
            }
            testSymbole(PV_TOKEN);
        } while (symCour.cls == ID_TOKEN);
    }
}

void Bloc()
{
    CONST_DECL();
    VAR_DECL();
    Generer2(INTc, p_table.offset);
    testSymbole(BEGIN_TOKEN);
    INSTS();
    testSymbole(END_TOKEN);
    Generer1(HLT);
}

void EXP()
{
    TERM();
    while (symCour.cls == PLUS_TOKEN || symCour.cls == MOINS_TOKEN)
    {
        TokenType op = symCour.cls;
        Sym_Suiv();
        TERM();
        if (op == PLUS_TOKEN)
        {
            Generer1(ADD);
        }
        else if (op == MOINS_TOKEN)
        {
            Generer1(SUB);
        }
    }
}

void TERM()
{
    FACT();
    while (symCour.cls == MULTI_TOKEN || symCour.cls == DIV_TOKEN)
    {
        TokenType op = symCour.cls;
        Sym_Suiv();
        FACT();
        if (op == MULTI_TOKEN)
        {
            Generer1(MUL);
        }
        else if (op == DIV_TOKEN)
        {
            Generer1(DIV);
        }
    }
}

void FACT()
{
    switch (symCour.cls)
    {
    case ID_TOKEN:
        testSymbole(ID_TOKEN);
        toLowerCase(symPre.nom);
        if (!rechercherIDF(symPre.nom))
        {
            Erreur("Identifier not declared");
        }
        else
        {
            TSYM idType = getIdType(symPre.nom);
            if (idType == TVAR)
            {
                int addr = getAdresse(symPre.nom);
                Generer2(LDV, addr);
            }
            else if (idType == TCONST)
            {
                int value = getValue(symPre.nom);
                Generer2(LDIv, value);
            }
        }
        break;
    case NUM_TOKEN:
        testSymbole(NUM_TOKEN);
        {
            int value = atoi(symPre.nom);
            Generer2(LDIv, value);
        }
        break;
    case PRG_TOKEN:
        testSymbole(PRG_TOKEN);
        EXP();
        testSymbole(PRD_TOKEN);
        break;
    default:
        Erreur("Syntax error in FACT");
        break;
    }
}

void COND()
{
    EXP();
    if (symCour.cls == EGAL_TOKEN || symCour.cls == DIFF_TOKEN ||
        symCour.cls == SUP_TOKEN || symCour.cls == INF_TOKEN ||
        symCour.cls == INFEG_TOKEN || symCour.cls == SUPEG_TOKEN)
    {
        TokenType op = symCour.cls;
        Sym_Suiv();
        EXP();
        switch (op)
        {
            case EGAL_TOKEN:
                Generer1(EQL);
                break;
            case DIFF_TOKEN:
                Generer1(NEQ);
                break;
            case SUP_TOKEN:
                Generer1(GTR);
                break;
            case INF_TOKEN:
                Generer1(LSS);
                break;
            case INFEG_TOKEN:
                Generer1(LEQ);
                break;
            case SUPEG_TOKEN:
                Generer1(GEQ);
                break;
            default:
                Erreur("Invalid operator in condition");
                break;
        }
    }
    else
    {
        Erreur("Expected a comparison operator");
    }
}

void INST()
{
    switch (symCour.cls)
    {
    case ID_TOKEN:
    {
        testSymbole(ID_TOKEN);
        toLowerCase(symPre.nom);
        if (!rechercherIDFVar(symPre.nom))
        {
            Erreur("Variable not declared for assignment");
        }
        int addr = getAdresse(symPre.nom);
        testSymbole(AFFECT_TOKEN);
        EXP();
        Generer2(STO, addr);
        break;
    }
    case BEGIN_TOKEN:
        testSymbole(BEGIN_TOKEN);
        INSTS();
        testSymbole(END_TOKEN);
        break;
    case IF_TOKEN:
    {
        testSymbole(IF_TOKEN);
        COND();
        testSymbole(THEN_TOKEN);
        int patchIndex = p_table.PC + 1;
        Generer2(BZEi, 0); // Placeholder
        INST();
        if (symCour.cls == ELSE_TOKEN)
        {
            int elsePatchIndex;
            testSymbole(ELSE_TOKEN);
            elsePatchIndex = p_table.PC + 1;
            Generer2(BRNi, 0); // Placeholder
            p_table.arg[patchIndex] = p_table.PC + 1; // Backpatch BZEi
            INST();
            p_table.arg[elsePatchIndex] = p_table.PC + 1; // Backpatch BRNi
        }
        else
        {
            p_table.arg[patchIndex] = p_table.PC + 1; // Backpatch BZEi
        }
        break;
    }
    case WHILE_TOKEN:
    {
        testSymbole(WHILE_TOKEN);
        int loopStart = p_table.PC + 1;
        COND();
        testSymbole(DO_TOKEN);
        int exitJumpIndex = p_table.PC + 1;
        Generer2(BZEi, 0); // Placeholder
        INST();
        Generer2(BRNi, loopStart);
        p_table.arg[exitJumpIndex] = p_table.PC + 1; // Backpatch BZEi
        break;
    }
    case FOR_TOKEN:
    {
        testSymbole(FOR_TOKEN);
        testSymbole(ID_TOKEN);
        toLowerCase(symPre.nom);
        if (!rechercherIDFVar(symPre.nom))
        {
            Erreur("Variable not declared for FOR loop");
        }
        int loopVarAddr = getAdresse(symPre.nom);
        testSymbole(EGAL_TOKEN);
        EXP();
        Generer2(STO, loopVarAddr);

        TokenType direction = symCour.cls;
        if (direction == TO_TOKEN || direction == DOWNTO_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur("Expected 'to' or 'downto' in FOR loop");
        }

        // Save the limit value
        int limitVarAddr = p_table.offset++;
        EXP();
        Generer2(STO, limitVarAddr);

        testSymbole(DO_TOKEN);
        int loopStart = p_table.PC + 1;
        // Load loop variable and limit value
        Generer2(LDV, loopVarAddr);
        Generer2(LDV, limitVarAddr);

        // Compare loop variable and limit value
        if (direction == TO_TOKEN)
        {
            Generer1(LEQ); // loopVar <= limitVar
        }
        else // DOWNTO_TOKEN
        {
            Generer1(GEQ); // loopVar >= limitVar
        }

        int exitJumpIndex = p_table.PC + 1;
        Generer2(BZEi, 0); // Placeholder

        INST();

        // Update loop variable
        Generer2(LDV, loopVarAddr);
        Generer2(LDIv, (direction == TO_TOKEN) ? 1 : -1);
        Generer1(ADD);
        Generer2(STO, loopVarAddr);

        Generer2(BRNi, loopStart);
        p_table.arg[exitJumpIndex] = p_table.PC + 1; // Backpatch BZEi
        break;
    }
    case READ_TOKEN:
    {
        testSymbole(READ_TOKEN);
        testSymbole(PRG_TOKEN);
        do
        {
            testSymbole(ID_TOKEN);
            toLowerCase(symPre.nom);
            if (!rechercherIDFVar(symPre.nom))
            {
                Erreur("Variable not declared for READ");
            }
            int addr = getAdresse(symPre.nom);
            Generer1(INN);
            Generer2(STO, addr);
            if (symCour.cls == VIRG_TOKEN)
            {
                testSymbole(VIRG_TOKEN);
            }
            else
            {
                break;
            }
        } while (1);
        testSymbole(PRD_TOKEN);
        break;
    }
    case WRITE_TOKEN:
    {
        testSymbole(WRITE_TOKEN);
        testSymbole(PRG_TOKEN);
        do
        {
            EXP();
            Generer1(PRN);
            if (symCour.cls == VIRG_TOKEN)
            {
                testSymbole(VIRG_TOKEN);
            }
            else
            {
                break;
            }
        } while (1);
        testSymbole(PRD_TOKEN);
        break;
    }
    default:
        Erreur("Syntax error in INST");
        break;
    }
}

void INSTS()
{
    INST();
    while (symCour.cls == PV_TOKEN)
    {
        testSymbole(PV_TOKEN);
        if (symCour.cls == END_TOKEN)
            break;
        INST();
    }
}

void Program()
{
    testSymbole(PROGRAM_TOKEN);
    testSymbole(ID_TOKEN);
    toLowerCase(symPre.nom);
    if (IDexists(symPre.nom))
    {
        Erreur("Identifier already declared");
    }
    else
    {
        TAB_IDFS[NBR_IDFS].TIDF = TPROG;
        strncpy(TAB_IDFS[NBR_IDFS].Nom, symPre.nom, sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1);
        TAB_IDFS[NBR_IDFS].Nom[sizeof(TAB_IDFS[NBR_IDFS].Nom) - 1] = '\0';
        NBR_IDFS++;
    }
    testSymbole(PV_TOKEN);
    Bloc();
    testSymbole(PT_TOKEN);
}

void Lire_Car()
{
    car_cour = fgetc(file);
    if (car_cour == '\n')
    {
        line_number++;
    }
}

void Erreur(const char *message)
{
    fprintf(stderr, "Error at line %d: %s. Current token: '%s'\n", line_number, message, symCour.nom);
    exit(EXIT_FAILURE);
}

void lire_mot()
{
    int i = 0;
    while (isalnum(car_cour) && i < 255)
    {
        symCour.nom[i++] = car_cour;
        Lire_Car();
    }
    symCour.nom[i] = '\0';
    toLowerCase(symCour.nom);
    if (strcmp(symCour.nom, "const") == 0)
    {
        symCour.cls = CONST_TOKEN;
    }
    else if (strcmp(symCour.nom, "program") == 0)
    {
        symCour.cls = PROGRAM_TOKEN;
    }
    else if (strcmp(symCour.nom, "var") == 0)
    {
        symCour.cls = VAR_TOKEN;
    }
    else if (strcmp(symCour.nom, "begin") == 0)
    {
        symCour.cls = BEGIN_TOKEN;
    }
    else if (strcmp(symCour.nom, "end") == 0)
    {
        symCour.cls = END_TOKEN;
    }
    else if (strcmp(symCour.nom, "if") == 0)
    {
        symCour.cls = IF_TOKEN;
    }
    else if (strcmp(symCour.nom, "then") == 0)
    {
        symCour.cls = THEN_TOKEN;
    }
    else if (strcmp(symCour.nom, "else") == 0)
    {
        symCour.cls = ELSE_TOKEN;
    }
    else if (strcmp(symCour.nom, "while") == 0)
    {
        symCour.cls = WHILE_TOKEN;
    }
    else if (strcmp(symCour.nom, "do") == 0)
    {
        symCour.cls = DO_TOKEN;
    }
    else if (strcmp(symCour.nom, "read") == 0)
    {
        symCour.cls = READ_TOKEN;
    }
    else if (strcmp(symCour.nom, "write") == 0)
    {
        symCour.cls = WRITE_TOKEN;
    }
    else if (strcmp(symCour.nom, "for") == 0)
    {
        symCour.cls = FOR_TOKEN;
    }
    else if (strcmp(symCour.nom, "to") == 0)
    {
        symCour.cls = TO_TOKEN;
    }
    else if (strcmp(symCour.nom, "downto") == 0)
    {
        symCour.cls = DOWNTO_TOKEN;
    }
    else
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
    printf("%s          %s\n", SYM.nom, getTokenName(SYM.cls));
}

void Sym_Suiv()
{
    while (isspace(car_cour))
    {
        Lire_Car();
    }

    if (car_cour == EOF)
    {
        symCour.cls = DIEZE_TOKEN;
        strcpy(symCour.nom, "EOF");
        return;
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
                Erreur("Unknown character ':'");
            }
            break;
        default:
            symCour.cls = ERREUR_TOKEN;
            sprintf(symCour.nom, "%c", car_cour);
            Erreur("Unknown character");
            Lire_Car();
            break;
        }
    }
    AfficherToken(symCour);
}

void printSymbolTable()
{
    printf("\nSymbol Table:\n");
    for (int i = 0; i < NBR_IDFS; i++)
    {
        printf("Name: '%s', Type: %s", TAB_IDFS[i].Nom,
                (TAB_IDFS[i].TIDF == TVAR) ? "Variable" : (TAB_IDFS[i].TIDF == TCONST) ? "Constant"
                                                                                        : "Program");
        if (TAB_IDFS[i].TIDF == TVAR)
            printf(", Address: %d\n", TAB_IDFS[i].Adresse);
        else if (TAB_IDFS[i].TIDF == TCONST)
            printf(", Value: %d\n", TAB_IDFS[i].Value);
        else
            printf("\n");
    }
    printf("\n");
}

void printPCode()
{
    printf("\nGenerated p_code:\n");
    for (int i = 0; i <= p_table.PC; i++)
    {
        printf("%d: %d", i, p_table.code[i]);
        if (p_table.code[i] == INTc || p_table.code[i] == LDIv ||
            p_table.code[i] == LDV || p_table.code[i] == STO ||
            p_table.code[i] == BRNi || p_table.code[i] == BZEi)
        {
            printf(" %d", p_table.arg[i]);
        }
        printf("\n");
    }
}

void toLowerCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main()
{
    initialize_p_table(); // Initialize the p_code table
    char filename[256];
    printf("Enter the filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file '%s'.\n", filename);
        return 1;
    }
    Lire_Car();
    Sym_Suiv();
    Program();
    printf("Semantic analysis finished, no errors.\n");
    printSymbolTable();
    printPCode(); // Optional: print generated p_code
    fclose(file);
    return 0;
}
