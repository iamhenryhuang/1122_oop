#include "battle.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"
#include <cstdlib>

// add your code to implement the Battle class here
Battle::Battle(Player* player, Enemy* enemy) : player(player), enemy(enemy), state(ACTION_SELECTING) {
    actionPlayerSelected = ATTACK;
}

Battle::~Battle() {
    delete player;
    delete enemy;
}

int Battle::damageCalculate(BattleAction attackerAction, BattleAction targetAction, int damage) {
    double multiplier = 1.0;
    if (attackerAction == FORCE_ATTACK) {
        multiplier = FORCE_ATTACK_MULTIPLIER;
    } else if (attackerAction == ATTACK) {
        multiplier = ATTACK_MULTIPLIER;
    } else if (attackerAction == DEFEND || attackerAction == HEAL) {
        return 0;
    }

    if (targetAction == DEFEND) {
        multiplier /= DEFEND_MULTIPLIER;
    } else if (targetAction == FORCE_ATTACK || targetAction == HEAL) {
        multiplier *= FORCE_ATTACK_MULTIPLIER;
    }

    return static_cast<int>(damage * multiplier);
}

ProcessInfo Battle::run(InputState action) {
    switch (state) {
        case ACTION_SELECTING:
            switch (action) {
                case ACTION_UP:
                    actionPlayerSelected = static_cast<BattleAction>((static_cast<int>(actionPlayerSelected) - 1 + BATTLE_ACTION_COUNT_PLAYER) % BATTLE_ACTION_COUNT_PLAYER);
                    break;
                case ACTION_DOWN:
                    actionPlayerSelected = static_cast<BattleAction>((static_cast<int>(actionPlayerSelected) + 1) % BATTLE_ACTION_COUNT_PLAYER);
                    break;
                case ACTION_CONFIRM:
                    actionEnemySelected = static_cast<BattleAction>(rand() % BATTLE_ACTION_COUNT_ENEMY); // 随机选择敌人行动
                    damageToPlayer = damageCalculate(actionEnemySelected, actionPlayerSelected, enemy->getAttack());
                    damageToEnemy = damageCalculate(actionPlayerSelected, actionEnemySelected, player->getAttack());

                    if (actionPlayerSelected == HEAL) {
                        player->heal(player->getHealPower());
                    } else {
                        enemy->hurt(damageToEnemy);
                    }

                    if (actionEnemySelected == HEAL) {
                        enemy->heal(enemy->getAttack());
                    } else {
                        player->hurt(damageToPlayer);
                    }

                    if (player->getHealth() <= 0) {
                        state = PLAYER_DEAD;
                    } else if (enemy->getHealth() <= 0) {
                        state = ENEMY_DEAD;
                    } else {
                        state = TURN_END;
                    }
                    break;
                default:
                    break;
            }
            break;
        case TURN_END:
            state = ACTION_SELECTING;
            break;
        case PLAYER_DEAD:
            return BATTLE_FINISH_PLAYER_DEAD;
        case ENEMY_DEAD:
            return BATTLE_FINISH_PLAYER_WIN;
    }

    return CONTINUE;
}

std::string Battle::BattleActionToString(BattleAction action) {
    switch(action) {
        case FORCE_ATTACK:
            return "force attack";
        case ATTACK:
            return "attack";
        case DEFEND:
            return "defend";
        case HEAL:
            return "heal";
        default:
            return "none";
    }
}

std::string repeat(const std::string& input, unsigned num) {
    std::string s;
    s.reserve(input.size() * num);
    while (num--) s += input;
    return s;
}

void Battle::render() {
    // remember screen size is defined in controller/enviroment.h

    // line 1
    AnsiPrint("\n", black, black);

    // life bar and name
    const int windowEdge = 1;
    const int lifeBarWidth = GAME_WINDOW_SIZE_X - windowEdge * 2; // 2 means left and right edge

    int playerHealthBlocks = (int) double(player->getHealth()) / double(player->getMaxHealth()) * lifeBarWidth;
    int enemyHealthBlocks = (int) double(enemy->getHealth()) / double(enemy->getMaxHealth()) * lifeBarWidth;

    std::string playerLifeBar = repeat("██", playerHealthBlocks) + repeat("__", (lifeBarWidth - playerHealthBlocks));
    std::string enemyLifeBar = repeat("__", (lifeBarWidth - enemyHealthBlocks)) + repeat("██", enemyHealthBlocks);

    // line 2
    AnsiPrint("  ", black, black);
    AnsiPrint(playerLifeBar.c_str(), blue, black);
    AnsiPrint("\n", black, black);

    // line 3
    AnsiPrint("  ", black, black);
    AnsiPrint(player->getName().c_str(), blue, black);
    AnsiPrint("\n", black, black);

    // line 4
    AnsiPrint("  ", black, black);
    AnsiPrint(std::string((GAME_WINDOW_SIZE_X - windowEdge * 2) * GAME_WINDOW_ONEBLOCK_WIDTH - enemy->getName().size(), ' ').c_str(), black, black);
    AnsiPrint(enemy->getName().c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 5
    AnsiPrint("  ", black, black);
    AnsiPrint(enemyLifeBar.c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 6~12
    AnsiPrint("\n\n\n\n\n\n\n", black, black);

    switch (state) {
        case ACTION_SELECTING: {
            // line 13 ~ 20
            AnsiPrint("  Please select your action:\n\n", white, black);
            AnsiPrint("    1) Force Attack\n", (actionPlayerSelected == FORCE_ATTACK ? yellow : white), black);
            AnsiPrint("    2) Attack\n", (actionPlayerSelected == ATTACK ? yellow : white), black);
            AnsiPrint("    3) Defend\n", (actionPlayerSelected == DEFEND ? yellow : white), black);
            AnsiPrint("    4) Heal\n\n", (actionPlayerSelected == HEAL ? yellow : white), black);
            AnsiPrint("  Press Enter to confirm.\n\n", white, black);

            break;
        }

        case TURN_END: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("performed the ", white, black);
            AnsiPrint(BattleActionToString(actionPlayerSelected).c_str(), yellow, black);
            AnsiPrint(" on the ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 14 15
            AnsiPrint("  ", black, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(" performed the ", white, black);
            AnsiPrint(BattleActionToString(actionEnemySelected).c_str(), yellow, black);
            AnsiPrint(" on ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 16
            AnsiPrint("  You ", blue, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(damageToEnemy).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 17 18
            AnsiPrint("  Enemy ", red, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(damageToPlayer).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 19 20
            AnsiPrint("  Press any key to continue.\n\n", white, black);
            break;
        }

        case ENEMY_DEAD: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("defeated ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", blue, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }

        case PLAYER_DEAD: {
            // line 13
            AnsiPrint("  You ", red, black);
            AnsiPrint("were defeated by ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", red, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }
    }
}
