#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

char program[1024],paper[1024];
int  ptr=512,stack[1024],sp=0;
void run()
{
    int size=0,pc=0;
    for(;program[size]!='\0';++size);
    for(;pc<size;++pc)
    {
        if(!sp && program[pc]==']'){printf("sp is zero.\n");break;}
        switch(program[pc])
        {
            case '+':++paper[ptr];break;
            case '-':--paper[ptr];break;
            case '[':stack[sp]=pc;++sp;break;
            case ']':pc=paper[ptr]?stack[sp-1]:pc;sp-=(!paper[ptr]);break;
            case '>':++ptr;break;
            case '<':--ptr;break;
            case ',':scanf("%c",&paper[ptr]);break;
            case '.':printf("%c",paper[ptr]);break;
        }
        if(ptr>=1024 || ptr<0){printf("paper out of range.\n");break;}
        if(sp>=1024){printf("sp out of range.\n");break;}
    }
    printf("\n");
    return;
}
int main(int argc, char* argv[])
{
    if(argc != 2){
        char quit[2] = "q";
        printf("Brainfuck Interpreter v1.0, have fun\nType q and Enter to quit.\n");
        while(strcmp(program,quit)){
            printf(">>> ");
            scanf("%s",program);
            int i=0;
            for(;i<1024;++i)paper[i]='\0';
            run();
        }
        return 0;
    }

    const char *filename = argv[1];
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Can't open file "<<filename<<endl;
        return 1;
    }
    string line;
    while (getline(file,line)){
        strcpy(program,line.c_str());
        int i=0;
        for(;i<1024;++i)paper[i]='\0';
        run();
    }
    file.close();
    return 0;

}
