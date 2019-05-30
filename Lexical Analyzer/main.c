#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RESERVEDNUMBER 10
#define KEYCOUNT 5


typedef struct KUYRUK {
    char degisken[101];
    struct KUYRUK *onceki, *sonraki;
} kuyruk;

kuyruk *ilk = NULL, *son, *yeni, *sil;

void ekle(char degisken[],char karakter);
void cikar();
void listele();
void kelime_al(kuyruk *atanacak_deger, char dizi[]);
void kelimemi_al(char dizi[]);



char okunan_degerim[32]={'\0'};
int karakter_degeri =0, satir_say=0, a=0;
char parse_cumlem[500][500]={'\0'};



char* reservedWords[]={"int","move","to","loop","times","out"
    ,"newline","add","sub","from"};
enum keyMap{INTEGER,MOVE,TO,LOOP,TIMES,OUT,NEWLINE,ADD,SUB,FROM};
char* elements[]={"identifier","openparanthesis","closeparanthesis",
    "commaoperand","endoflinecharacter","keyword","intconst","stringconst"};
enum elementMap{IDENTIFIER,OPENPARANTHESIS,CLOSEPARANTHESIS,COMMAOPERAND
    ,ENDOFLINECHARACTER,KEYWORD,INTCONST,STRINGCONST};
enum countMap{identifier  ,paranthesis ,keyword ,comma ,endofline};
void skipSpace(FILE* f);
int getLexeme(FILE* f,char** lexeme);
void lexicalAnalyze(char* );
void printCounts();
char* lookup(FILE*,char* lexeme);
char *l;
int lineNumber=1;

//Al
int intAl(FILE* f);
int identifierAl(FILE* f);
int endoflineAl(FILE* f);
int moveAl(FILE* f);
int intconstIdentifierAl(FILE* f);
int toAl(FILE* f);
int outAl(FILE* f);
int commaAl(FILE* f);
int stringConstAl(FILE* f);
int subAl(FILE* f);
int fromAl(FILE* f);
int loopAl(FILE* f);
int timesAl(FILE* f);
int openParanthesisAl(FILE* f);
int closeParanthesisAl(FILE* f);
//işlemler
int tanimlama(FILE *f);
int atama(FILE*f);
int ekleme(FILE* f);
int cikarma(FILE* f);
int output(FILE* f);
void identifierIntconstError();
void undefinedVariable();
void gotoNewLine(FILE* f);
void errorCatch();
int dongu(FILE* f);
int main(int argc,char * argv[])
{
    int a=0,karakter_sayaci=0;
    
   
    l=malloc(300*sizeof(char));
    printf("Give a file name:");
    scanf("%s",l);
    strcat(l,".txt");
    lexicalAnalyze(l);
    undefinedVariable();
    identifierIntconstError();
    errorCatch();
    printCounts();
    
    
    printf("\n");
    
    return 0;
}
void identifierIntconstError(){
    FILE* f=fopen("result.txt","r");
    if(f==NULL)
        printf("Dosya acilirken bir hata olustu.");
    int where=0;
    while((fscanf(f,"%s",l))&&!feof(f)){//first word tip
        if(strcmp(l,elements[IDENTIFIER])==0){//keyword
            fscanf(f,"%s",l);
            if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                where++;
                continue;
            }
            if(strlen(l)>20){
                printf("Error : Variable length must be maximum 20. %s in %d. program line.\n",l,where);
            }
        }else{
            if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                where++;
                continue;
            }else{
                if(strcmp(l,elements[INTCONST])==0){
                    fscanf(f,"%s",l);
                    if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                        ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                        where++;
                        continue;
                    }
                    if(strlen(l)>100){
                        printf("Error : Intconst must contains 100 digit. %s in %d. program line.\n",l,where);
                        continue;
                    }
                    int a=1;
                    char x;
                    for(;a<strlen(l);a++){
                        x=l[a];
                        if((64<x&&x<91)||(96<x&&x<123)){
                            printf("Error : Intconst must not contain alphabetic character. %s in %d. program line.\n",l,where);
                            break;
                        }
                    }
                }
            }
            
        }
        
    }
    fclose(f);
}
void undefinedVariable(){
    FILE* f=fopen("result.txt","r");
    if(f==NULL)
        printf("Dosya acilirken bir hata olustu.");
    int i=0;
    while((fscanf(f,"%s",l))&&!feof(f)){//first word tip
        if(strcmp(l,elements[IDENTIFIER])==0){//keyword
            i++;
        }
    }
    char* variables[i];
    rewind(f);
    i=0;
    int where=1;
    while((fscanf(f,"%s",l))&&!feof(f)){//first word tip
        if(strcmp(l,reservedWords[INTEGER])==0){//keyword
            fscanf(f,"%s",l);
            if(strcmp(l,elements[IDENTIFIER])==0){
                fscanf(f,"%s",l);
                if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                    ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                    where++;
                    continue;
                }
                variables[i]=(char*)malloc(strlen(l)*sizeof(char));
                strcpy(variables[i],l);
                i++;
            }else{
                if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                    ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                    where++;
                    continue;
                }
            }
        }else{
            if(strcmp(l,elements[IDENTIFIER])==0){
                fscanf(f,"%s",l);
                if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                    ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                    where++;
                    continue;
                }
                int a=0,var=0;
                for(;a<i;a++){
                    if(strcmp(l,variables[a])==0){
                        var=1;
                        break;
                    }
                }
                if(!var){
                    printf("Error : Undefined variable %s in %d. program line.\n",l,where);
                }
            }else{
                if(((strcmp(l,reservedWords[ADD])==0)||(strcmp(l,reservedWords[SUB])==0)||(strcmp(l,reservedWords[LOOP])==0)
                    ||(strcmp(l,reservedWords[MOVE])==0)||(strcmp(l,reservedWords[OUT])==0)||(strcmp(l,reservedWords[INTEGER])==0))){
                    where++;
                    continue;
                }
                
            }
        }
    }
    fclose(f);
}
void errorCatch(){
    FILE* f=fopen("result.txt","r");
    if(f==NULL)
        printf("Dosya acilirken bir hata olustu.");
    while((fscanf(f,"%s",l))&&!feof(f)){//first word tip
        if(strcmp(l,elements[KEYWORD])==0){//keyword
            fscanf(f,"%s",l);
            if(tanimlama(f)||atama(f)||ekleme(f)||cikarma(f)||output(f)||dongu(f)){
                
            }
        }else{//Error
            printf("Error : Expected keyword not %s in %d. program line.\n",l,lineNumber);
            gotoNewLine(f);
        }
    }
    fclose(f);
}
void printCounts(){
    printf("---Counts of Lexeme Types---\n");
    FILE* fr=fopen("result.txt","r");
    if(fr==NULL)
        printf("Dosya acilirken bir hata olustu.");
    char* lexeme=malloc(300*sizeof(char));
    fscanf(fr,"%s",lexeme);
    int counts[5]={0};
    int i=0;
    while(!feof(fr)){
        if(strcmp(lexeme,"identifier")==0){
            counts[identifier]++;
            fscanf(fr,"%s",lexeme);
        }else {
            if(strcmp(lexeme,"openparanthesis")==0||strcmp(lexeme,"closeparanthesis")==0){
                counts[paranthesis]++;
            }
            else{
                if(strcmp(lexeme,"keyword")==0){
                    counts[keyword]++;
                    fscanf(fr,"%s",lexeme);
                }else{
                    if(strcmp(lexeme,"commaoperand")==0){
                        counts[comma]++;
                    }else{
                        if(strcmp(lexeme,"endoflinecharacter")==0)
                            counts[endofline]++;
                    }
                }
            }
        }
        fscanf(fr,"%s",lexeme);
    }
    for(i=0;i<KEYCOUNT;i++)
        printf("%s: %d units\n",elements[i],counts[i]);
    fclose(fr);
    
}
void lexicalAnalyze(char * fileName){
    FILE* f=fopen(fileName,"r");
    FILE* fw=fopen("result.txt","w");
    if(f==NULL)
        printf("Dosya acilirken bir hata olustu.");
    skipSpace(f);
    char* lexeme=malloc(300*sizeof(char));
    while(!feof(f)){
        fscanf(f,"%s",lexeme);
        int result;
    A:
        if((result=contains(lexeme))!=-1){
            //string const mu
            int z=1;
            if(strcmp(lexeme,"}")==0){
                z=0;
            }
            if(z&&strcmp(lookup(f,lexeme),"stringconst")==0){
                int i=1;
                char x;
                for(;i<strlen(lexeme);i++){
                    x=lexeme[i];
                    i++;
                    if(x=='"'){
                        break;
                    }
                }
                x=lexeme[i];
                lexeme[i]='\0';
                fprintf(fw,"stringconst %s\n",lexeme);
                
                if(strcmp(lexeme, "to")!=0  && strcmp(lexeme, "from")!=0)
                    ekle(lexeme, '&');
                
                while(okunan_degerim[a]!='\0'){
                    okunan_degerim[a]='\0';
                    a++;
                }
                if(okunan_degerim[a]=='\0')
                    a=0;
                
                int a=i+1;
                lexeme[0]=x;
                for(i=1;i<strlen(lexeme);i++){
                    lexeme[i]=lexeme[a];
                }
                goto A;
            }else{
                //beklenmeyen diğer karakterler
                char *lexeme1=malloc(300*sizeof(char));
                int i=0;
                for(;i<result;i++)
                    lexeme1[i]=lexeme[i];
                
                lexeme1[i]='\0';
                char ortadaki=lexeme[i];
                int a=++i;
                for(;i<strlen(lexeme);i++){
                    lexeme[i-a]=lexeme[i];
                }
                lexeme[i-a]='\0';
                if(strcmp(lexeme1," ")!=0&&strcmp(lexeme1,"\n")!=0&&strcmp(lexeme1,"")!=0){
                    fprintf(fw,"%s %s\n",lookup(f,lexeme1),lexeme1);
                
                    if(strcmp(lexeme, "to" )!=0 && strcmp(lexeme, "from")!=0)
                        ekle(lexeme1, '&');
                    
                    while(okunan_degerim[a]!='\0'){
                        okunan_degerim[a]='\0';
                        a++;
                    }
                    if(okunan_degerim[a]=='\0')
                        a=0;
                    
                }
                if(ortadaki=='.'){
                    fprintf(fw,"endoflinecharacter\n");
                    
                    for(int i=0;ilk!=NULL;i++){
                        
                        cikar();
                        a=0;
                        
                        while(okunan_degerim[a]!='\0'){
                            parse_cumlem[satir_say][karakter_degeri]=okunan_degerim[a];
                            karakter_degeri++;
                            a++;
                        }
                        
                        parse_cumlem[satir_say][karakter_degeri]=' ';
                        karakter_degeri++;
                        for(a=0;a<32;a++){
                            okunan_degerim[a]='\0';
                        }
                        
                    }
                    
                    karakter_degeri=0;
                    satir_say++;
                    
                
                }
                else{
                    if(strcmp(&ortadaki,"")!=0&&strcmp(&ortadaki," ")!=0){
                        fprintf(fw,"%s\n",lookup(f,&ortadaki));
                        
                        
                    }
                }
                if(strcmp(lookup(f,lexeme),"{")==0)
                    continue;
                if(strcmp(lexeme,"\0")!=0&&strcmp(lexeme,"\n")!=0&&strcmp(lexeme," ")!=0){
                    fprintf(fw,"%s %s\n",lookup(f,lexeme),lexeme);
                    
                    if(strcmp(lexeme, "to")!=0 && strcmp(lexeme, "from")!=0)
                        ekle(lexeme, '&');
                    while(okunan_degerim[a]!='\0'){
                        okunan_degerim[a]='\0';
                        a++;
                    }
                    if(okunan_degerim[a]=='\0')
                        a=0;
                    
                }
                
            }
        }else{
            if(strcmp(lookup(f,lexeme),"")==0)
                continue;
            if(strcmp(lexeme,"\0")!=0&&strcmp(lexeme,"\n")!=0&&strcmp(lexeme," ")!=0){
                fprintf(fw,"%s %s\n",lookup(f,lexeme),lexeme);
                
                if(strcmp(lexeme, "to")!=0 && strcmp(lexeme, "from")!=0)
                    ekle(lexeme, '&');
                while(okunan_degerim[a]!='\0'){
                    okunan_degerim[a]='\0';
                    a++;
                }
                if(okunan_degerim[a]=='\0')
                    a=0;
               
            }
        }
    }
    fclose(f);
    fclose(fw);
}
void gotoNewLine(FILE* f){
    fseek(f,-(strlen(l)*sizeof(char)),1);
    while(fscanf(f,"%s",l)&&!feof(f)&&((strcmp(l,reservedWords[ADD])!=0)&&(strcmp(l,reservedWords[SUB])!=0)&&(strcmp(l,reservedWords[LOOP])!=0)
                                       &&(strcmp(l,reservedWords[MOVE])!=0)&&(strcmp(l,reservedWords[OUT])!=0)&&(strcmp(l,reservedWords[INTEGER])!=0))){
    }
    fseek(f,-(strlen(l)*sizeof(char)),1);
    fseek(f,-(sizeof("keyword")),1);
    lineNumber++;
}
void skipSpace(FILE* f){
    char x=getc(f);
    while(((x==' ')||(x=='\n'))){
        x=getc(f);
    }
    if(!feof(f))
        fseek(f,-sizeof(char),1);
}
int contains(char* lexeme){
    int i=0;
    char x=lexeme[i];
    while(x!='\0'){
        if(!((64<x&&x<91)||(96<x&&x<123)||x=='_'||(47<x&&x<58))){
            return i;
        }
        i++;
        x=lexeme[i];
    }
    return -1;
}
char* lookup(FILE* f,char* lexeme){
    char x=lexeme[0];
    switch(x){
        case '[':return "openparanthesis";
        case ']':return "closeparanthesis";
        case '{':{
            char a=fgetc(f);
            while(a!='}'&&!feof(f)){
                a=fgetc(f);
            }
            if(feof(f)){
                printf("Error : expected close curly bracket of commandline\n");
            }
            return "{";
        }
        case '}':{
            printf("Error : curly bracket of commandline can not be closed without curly bracket of commandline opening\n");
            return "";
        };
        case '"':return "stringconst";
        case ',':return "commaoperand";
    }
    if(47<x&&x<58)
        return "intconst";
    else{
        int i=0;
        for(;i<RESERVEDNUMBER;i++){
            if(strcmp(reservedWords[i],lexeme)==0){
                return "keyword";
            }
        }
        if((64<x&&x<91)||(96<x&&x<123)){
            return "identifier";
        }else{
            return "unsupported word";
        }
    }
}
int intAl(FILE* f){
    if(strcmp(l,reservedWords[INTEGER])==0){//int size.
        return 1;
    }
    return 0;
}
int identifierAl(FILE* f){
    fscanf(f,"%s",l);//second word tip
    if(strcmp(l,elements[IDENTIFIER])==0){//size.
        fscanf(f,"%s",l);
        return 1;
    }
    printf("Error: expected identifier not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int endoflineAl(FILE* f){
    fscanf(f,"%s",l);//third word
    if(strcmp(l,elements[ENDOFLINECHARACTER])!=0){
        printf("Error : Expected endoflinecharacter not %s in %d. program line.\n",l,lineNumber);
        gotoNewLine(f);
    }else
        lineNumber++;
    
    return 0;
}
int moveAl(FILE* f){
    if(strcmp(l,reservedWords[MOVE])==0)//move 25|size to sum.
        return 1;
    return 0;
}
int intconstIdentifierAl(FILE* f){
    fscanf(f,"%s",l);//second word ti
    if(strcmp(l,elements[IDENTIFIER])==0||strcmp(l,elements[INTCONST])==0){
        fscanf(f,"%s",l);
        return 1;
    }
    printf("Error: expected intconst or identifier not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int toAl(FILE* f){
    fscanf(f,"%s",l);
    fscanf(f,"%s",l);
    if(strcmp(l,reservedWords[TO])==0)
        return 1;
    printf("Error: expected  keyword('to') not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int outAl(FILE* f){
    if(strcmp(l,reservedWords[OUT])==0)
        return 1;
    return 0;
}
int commaAl(FILE* f){
    fscanf(f,"%s",l);
    if(strcmp(l,elements[COMMAOPERAND])==0)
        return 1;
    printf("Error: expected commaoperand not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int stringConstAl(FILE* f){
    fscanf(f,"%s",l);
    if(strcmp(l,elements[STRINGCONST])==0){
        fscanf(f,"%s",l);
        return 1;
    }
    printf("Error: expected stringconst not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int subAl(FILE* f){
    if(strcmp(l,reservedWords[SUB])==0)
        return 1;
    return 0;
    
}
int fromAl(FILE* f){
    fscanf(f,"%s",l);//third word tip
    fscanf(f,"%s",l);//third word
    if(strcmp(l,reservedWords[FROM])==0)
        return 1;
    printf("Error: expected keyword('from') not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int loopAl(FILE* f){
    if(strcmp(l,reservedWords[LOOP])==0)
        return 1;
    return 0;
}
int timesAl(FILE* f){
    fscanf(f,"%s",l);//third word tip
    fscanf(f,"%s",l);//third word
    if(strcmp(l,reservedWords[TIMES])==0)
        return 1;
    printf("Error: expected keyword('times') not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int openParanthesisAl(FILE* f){
    fscanf(f,"%s",l);
    if(strcmp(l,elements[OPENPARANTHESIS])==0)
        return 1;
    printf("Error: expected openparanthesis not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int closeParanthesisAl(FILE* f){
    fscanf(f,"%s",l);
    if(strcmp(l,elements[CLOSEPARANTHESIS])==0)
        return 1;
    printf("Error: expected closeparanthesis not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}
int addAl(FILE* f){
    if(strcmp(l,reservedWords[ADD])==0)
        return 1;
    return 0;
}
int stringconstIdentifierAl(FILE* f){
    fscanf(f,"%s",l);
    if(strcmp(l,elements[KEYWORD])==0){
        fscanf(f,"%s",l);
        if(strcmp(l,reservedWords[NEWLINE])==0)
            return 1;
        else{
            printf("Error: expected keyword('newline') not %s in %d. program line\n",l,lineNumber);
            gotoNewLine(f);
            return 0;
        }
        
    }
    if(strcmp(l,elements[STRINGCONST])==0||strcmp(l,elements[IDENTIFIER])==0){
        fscanf(f,"%s",l);
        return 1;
    }
    printf("Error: expected stringconst or identifier not %s in %d. program line\n",l,lineNumber);
    gotoNewLine(f);
    return 0;
}

int tanimlama(FILE *f){
    
    if(intAl(f)){
        if(identifierAl(f)){
            endoflineAl(f);
            return 1;
        }
    }
    return 0;
}
int atama(FILE*f){
    if(moveAl(f)){
        if(intconstIdentifierAl(f)){
            if(toAl(f)){
                if(identifierAl(f)){
                    endoflineAl(f);
                    return 1;
                }
            }
        }
    }
    return 0;
}
int ekleme(FILE* f){
    if(addAl(f)){
        if(intconstIdentifierAl(f)){
            if(toAl(f)){
                if(identifierAl(f)){
                    endoflineAl(f);
                }
            }
        }
    }
    return 0;
}
int cikarma(FILE* f){
    if(subAl(f)){
        if(intconstIdentifierAl(f)){
            if(fromAl(f)){
                if(identifierAl(f)){
                    endoflineAl(f);
                    return 1;
                }
            }
        }
    }
    return 0;
}
int output(FILE* f){
    if(outAl(f)){
        if(stringconstIdentifierAl(f)){
            fscanf(f,"%s",l);
            if(strcmp(l,elements[ENDOFLINECHARACTER])==0)
                return 1;
            else{
                fseek(f,-(strlen(l)*sizeof(char)),1);
                while(commaAl(f)){
                    if(!stringconstIdentifierAl(f))
                        return 0;
                    else{
                        fscanf(f,"%s",l);
                        if(strcmp(l,elements[ENDOFLINECHARACTER])==0)
                            return 1;
                        else
                            fseek(f,-(strlen(l)*sizeof(char)),1);
                    }
                }
            }
            
        }
    }
    return 0;
}
int dongu(FILE* f){
    if(loopAl(f)){
        if(intconstIdentifierAl(f)){
            if(timesAl(f)){
                fscanf(f,"%s",l);
                if(strcmp(l,elements[OPENPARANTHESIS])==0){
                    while(!feof(f)){
                        fscanf(f,"%s",l);
                        if(strcmp(l,elements[CLOSEPARANTHESIS])==0){
                            return 1;
                        }else{
                            if(strcmp(l,elements[KEYWORD])!=0){
                                printf("Error: expected keyword not %s in %d. not program line\n",l,lineNumber);
                                gotoNewLine(f);
                                return 0;
                            }
                            fscanf(f,"%s",l);
                            if(tanimlama(f)||atama(f)||ekleme(f)||cikarma(f)||output(f)||dongu(f)){
                                
                            }
                        }
                    }
                    printf("Error: expected closeparanthesis not %s in %d. program line\n",l,lineNumber);
                    gotoNewLine(f);
                }else{
                    fseek(f,-(strlen(l)*sizeof(char)),1);
                    if(tanimlama(f)||atama(f)||ekleme(f)||cikarma(f)||output(f)){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}




void kelime_al(kuyruk *atanacak_deger, char dizi[]){
    int i=0;
    for(i=0;dizi[i]!='\0';i++){
        atanacak_deger->degisken[i]=dizi[i];
    }
}


void kelimemi_al(char dizi[]){
    int i=0;
    for(i=0;dizi[i]!='\0';i++){
        okunan_degerim[i]=dizi[i];
    }
}



void ekle(char degisken[],char karakter) {
    yeni = (kuyruk*) malloc(sizeof (kuyruk));
    if(degisken!=NULL)
        kelime_al(yeni, degisken);
    else if(karakter!='&')
        yeni->degisken[0]=karakter;
    
    yeni->sonraki = NULL;
    
    if (ilk == NULL) {
        ilk = (kuyruk *) malloc(sizeof (kuyruk));
        yeni->onceki = NULL;
        ilk = yeni;
        son = ilk;
    } else {
        son->sonraki = yeni;
        yeni->onceki = son;
        son = son->sonraki;
    }
}

void cikar() {
    if (ilk == NULL) {
        printf("Kuyruk bos\n");
    } else {
        sil = (kuyruk*) malloc(sizeof (kuyruk));
        sil = ilk;
        ilk = ilk->sonraki;
        printf("%s Kuyruktan cikarildi\n", sil->degisken);
        kelimemi_al(sil->degisken);
        free(sil);
    }
}


void listele() {
    if (ilk == NULL) {
        printf("Kuyruk Bos\n");
    } else {
        kuyruk *gecici = ilk;
        while (gecici != NULL) {
            printf("%s \n", gecici->degisken);
            gecici = gecici->sonraki;
        }
        printf("\n");
    }
}
























