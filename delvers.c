#include <time.h>
#include <stdlib.h>
#include <stdio.h>


char *MODS[] = {
    "0", "0", "0",
    "-3",
    "-2", "-2",
    "-1", "-1", "-1",
    " ", " ", " ", " ",
    "+1", "+1", "+1",
    "+2", "+2",
    "+3"
};
int MODS_INT[] = {
    0, 0, 0,
    -3,
    -2, -2,
    -1, -1, -1,
    0, 0, 0, 0,
    1, 1, 1,
    2, 2,
    3
};

int roll(int n_dice, int sides)
{
    int result = 0;
    for (int i = 0; i < n_dice; i++)
    {
        result += (rand() % sides) + 1;
    }
    return result;
}

struct dndclass
{
    char *name;
    int hd;
    int thac0_by_level[15];
    int spells;
};

struct dndclass fighter = {
    .name = "fighter",
    .hd = 8,
    .thac0_by_level = {20, 19, 19, 19, 17, 17, 17, 14, 14, 14, 12, 12, 12, 10, 10},
    .spells = 0
};

struct character
{
    char *name;
    struct dndclass their_class;
    int level;
    int hp;
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
};

struct character roll_new_character(char *name, struct dndclass their_class)
{
    struct character new_character = {
        .name = name,
        .their_class = their_class,
        .level = 1,
        .hp = their_class.hd,
        .strength = roll(3, 6),
        .dexterity = roll(3, 6),
        .constitution = roll(3, 6),
        .intelligence = roll(3, 6),
        .wisdom = roll(3, 6),
        .charisma = roll(3, 6),
    };
    new_character.hp += MODS_INT[new_character.constitution];
    return new_character;
}

void level_up(struct character *pc) {
    pc->hp += roll(1, pc->their_class.hd) + MODS_INT[pc->constitution];
    pc->level += 1;
}

int get_thac0(struct character *pc) {
    return pc->their_class.thac0_by_level[pc->level];
}

char *SHEET_TEMPLATE =
    "NAME: %-15s LEVEL: %d\n"
    "CLASS: %-14s XP: 9\n"
    "STRENGTH:     %-2d %-4s HP: %d\n"
    "DEXTERITY:    %-2d %-4s AC: 9\n"
    "CONSTITUTION: %-2d %-4s THAC0: %d\n"
    "INTELLIGENCE: %-2d %-4s MOVE: 9'\n"
    "WISDOM:       %-2d %s\n"
    "CHARISMA:     %-2d %s\n\n";

void print_character_sheet(struct character *pc) {
    printf(
        SHEET_TEMPLATE,
        pc->name,
        pc->level,
        pc->their_class.name,
        pc->strength,
        MODS[pc->strength],
        pc->hp,
        pc->dexterity,
        MODS[pc->dexterity],
        pc->constitution,
        MODS[pc->constitution],
        get_thac0(pc),
        pc->intelligence,
        MODS[pc->intelligence],
        pc->wisdom,
        MODS[pc->wisdom],
        pc->charisma,
        MODS[pc->charisma]
    );
}

int main(int argc, char* argv[])
{
    srand(time(0));

    struct character pc = roll_new_character("Otis Crune", fighter);
    for (int i = 1; i < atoi(argv[1]); i++) {level_up(&pc);}
    print_character_sheet(&pc);
    return 0;
}