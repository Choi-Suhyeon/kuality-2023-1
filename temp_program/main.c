#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const unsigned kMaxNum,
                   kMaxCnt;
} Level;

const char * const kQuitMenu  = "What do you want next?\n 1. [S]tart New Game\n 2. [Q]uit This Game\n> ",
           * const kLevelMenu = "Select a Level.\n 1. [E]asy\n 2. [I]intermediate\n 3. [H]ard\n> ";

static inline void flush(void) {
    while (getchar() != '\n');
}

bool playUpDownGame(const Level * const kLvl) {
    srand((unsigned) time(NULL));
    
    const unsigned kRandNum = rand() % (kLvl->kMaxNum + 1);

    unsigned count = kLvl->kMaxCnt,
             input = 0;

    while (count--) {
        printf("\nNUMBER > ");
        scanf("%u", &input);

        if      (input > kLvl->kMaxNum) puts("[E] OUT OF RANGE VAL");
        else if (input > kRandNum)      puts("[-] DOWN");
        else if (input < kRandNum)      puts("[+] UP");
        else                            return true;
    }

    return false;
}

int main(void) {
    const Level kEasy = { .kMaxNum = 100, .kMaxCnt = 15 },
                kItrm = { .kMaxNum = 150, .kMaxCnt = 13 },
                kHard = { .kMaxNum = 200, .kMaxCnt = 11 };

    char ifToQuit = '\0',
         level    = '\0';

    puts("\t[Up Down Game]\n");

    while (true) {
        printf("%s", kLevelMenu);
        scanf("%c", &level);
        
        puts((NULL ||
            level == '1' || level == 'E' ? playUpDownGame(&kEasy) :
            level == '2' || level == 'I' ? playUpDownGame(&kItrm) :
            level == '3' || level == 'H' ? playUpDownGame(&kHard) :
            false) 
                ? "Congratulations. You Won!"
                : "Sorry, You Lose TT");

        while (true) {
            flush();
            printf("\n%s", kQuitMenu);
            scanf("%c", &ifToQuit);
            
            if (ifToQuit == '1' || ifToQuit == 'S') break;

            if (ifToQuit == '2' || ifToQuit == 'Q') goto PROGRAM_END; 
        }

        flush();
    }

    PROGRAM_END:
    puts("Thank you for playing~");

    return 0;
}