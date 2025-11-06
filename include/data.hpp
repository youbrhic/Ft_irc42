/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:44 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/05 18:07:11 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

struct QuizQuestion
{
    std::string emojis;
    std::string correct_answer;
    std::string wrong_answers[3];
};

#define QUIZ_QUESTIONS_COUNT 120

#define QUIZ_QUESTIONS_DATA { \
    {"🦸 🛡️ 🌀", "captain_america", {"iron_man", "thor", "hulk"}}, \
    {"🐉 🔥 🏰", "game_of_thrones", {"witcher", "merlin", "vikings"}}, \
    {"🇸🇦 ⛪ 🕋", "islam", {"christianity", "judaism", "hinduism"}}, \
    {"🦇 🌃 🕶️", "batman", {"superman", "spiderman", "aquaman"}}, \
    {"🚀 🌌 👽", "star_wars", {"star_trek", "dune", "guardians_of_the_galaxy"}}, \
    {"🏹 🌲 🐦", "hunger_games", {"maze_runner", "divergent", "percy_jackson"}}, \
    {"🌟 🧙‍♂️ ⚔️", "lord_rings", {"harry_potter", "narnia", "hobbit"}}, \
    {"🏴‍☠️ 🗺️ 💰", "pirates_caribbean", {"treasure_island", "goonies", "master_and_commander"}}, \
    {"🕵️‍♂️ 🔍 🧩", "sherlock_holmes", {"poirot", "nancy_drew", "miss_marple"}}, \
    {"🐾 🦒 🦁", "madagascar", {"zootopia", "lion_king", "ice_age"}}, \
    {"👩‍🎤 🎶 🌟", "bohemian_rhapsody", {"rocketman", "mamma_mia", "greatest_showman"}}, \
    {"🕶️ 🕴️ 💊", "matrix", {"inception", "john_wick", "terminator"}}, \
    {"🛶 🐅 🌊", "life_of_pi", {"castaway", "moana", "avatar"}}, \
    {"🦖 🏞️ 🧪", "jurassic_park", {"king_kong", "godzilla", "lost_world"}}, \
    {"👩‍🚀 🌌 🛰️", "interstellar", {"gravity", "arrival", "ad_astra"}}, \
    {"🐧 🎤 🎶", "happy_feet", {"rio", "zootopia", "penguins_madagascar"}}, \
    {"🎩 🐰 ✨", "the_prestige", {"now_you_see_me", "the_illusionist", "harry_potter"}}, \
    {"🕵️‍♂️ 🚗 💥", "gta_v", {"mafia_iii", "watch_dogs_2", "red_dead_redemption_2"}}, \
    {"⚔️ 🧙‍♂️ 🏞️", "the_witcher_3", {"skyrim", "red_dead_redemption_2", "dark_souls"}}, \
    {"🧟‍♂️ 🧠 💀", "resident_evil", {"left_for_dead", "dead_space", "the_walking_dead"}}, \
    {"🏙️ 🚗 🏁", "grand_theft_auto_v", {"red_dead_redemption_2", "mafia_iii", "watch_dogs_2"}}, \
    {"🧙‍♂️ 🔮 ⚔️", "the_witcher_3", {"skyrim", "dark_souls", "red_dead_redemption_2"}}, \
    {"🧟‍♂️ 🔫 🏙️", "resident_evil", {"left_for_dead", "dead_space", "the_walking_dead"}}, \
    {"🌍 🦧 🚀", "planet_of_apes", {"king_kong", "jurassic_world", "interstellar"}}, \
    {"🕷️ 🕸️ 🏙️", "spiderman", {"batman", "superman", "deadpool"}}, \
    {"👩‍🎤 🌟 🎸", "rockstar", {"bohemian_rhapsody", "greatest_showman", "whiplash"}}, \
    {"👑 👸 🏰", "frozen", {"brave", "tangled", "cinderella"}}, \
    {"🚗 🏁 💨", "fast_and_furious", {"need_for_speed", "rush", "gone_in_sixty_seconds"}}, \
    {"🐍 🍎 👩‍🦰", "adam_and_eve", {"hercules", "troy", "spartacus"}}, \
    {"🤖 🔫 👦", "terminator", {"matrix", "robocop", "i_robot"}}, \
    {"🕰️ 🔄 🧑‍🤝‍🧑", "groundhog_day", {"inception", "time_traveler", "edge_of_tomorrow"}}, \
    {"🐦 🍎 🌳", "angry_birds", {"rio", "zootopia", "madagascar"}}, \
    {"🐕 🥺 🌈", "marley_and_me", {"hachi", "homeward_bound", "dog_purpose"}}, \
    {"🍿 🎭 🎬", "cinema_paradiso", {"the_artist", "la_la_land", "the_pianist"}}, \
    {"🧛 🩸 🌌", "twilight", {"dracula", "vampire_diaries", "underworld"}}, \
    {"🎤 👨 🎹", "ray", {"bohemian_rhapsody", "elvis", "walk_the_line"}}, \
    {"🦸‍♂️ 🌍 🛠️", "iron_man", {"captain_america", "thor", "black_panther"}}, \
    {"🌍 🦅 🔥", "avatar", {"moana", "tarzan", "prince_of_egypt"}}, \
    {"🕵️‍♂️ 🏴‍☠️ 💀", "national_treasure", {"indiana_jones", "da_vinci_code", "treasure_island"}}, \
    {"🚢 💔 🏝️", "titanic", {"the_notebook", "romancing_the_stone", "gone_with_the_wind"}}, \
    {"🦊 🦁 🐯", "zootopia", {"madagascar", "ice_age", "kung_fu_panda"}}, \
    {"⚡ 🏰 🧙", "harry_potter", {"lord_of_rings", "narnia", "percy_jackson"}}, \
    {"🧟‍♂️ ⚔️ 🔫", "resident_evil", {"dead_rising", "left_for_dead", "the_walking_dead"}}, \
    {"🕹️ 🧙‍♂️ 🏰", "diablo", {"dark_souls", "warcraft", "torchlight"}}, \
    {"👑 ⚔️ 🏰", "age_of_empires", {"civilization", "rome_total_war", "warcraft"}}, \
    {"🧙‍♂️ 🔮 ⚔️", "witcher_3", {"skyrim", "dark_souls", "elden_ring"}}, \
    {"⚔️ 🏰 🏹", "chivalry_2", {"for honor", "mount_and_blade", "conqueror's_blade"}}, \
    {"🚗 🏁 🚙", "grand_theft_auto_v", {"red_dead_redemption_2", "mafia_iii", "watch_dogs_2"}}, \
    {"🐍 🌵 🏝️", "snake", {"pacman", "asteroids", "pong"}}, \
    {"🏎️ 🚗 🏁", "gran_turismo", {"forza_horizon", "need_for_speed", "dirt_rally"}}, \
    {"💪 🏋️‍♂️ 🥇", "rocky", {"creed", "raging_bull", "million_dollar_baby"}}, \
    {"🎩 🐇 ⏳", "alice_in_wonderland", {"wizard_of_oz", "neverland", "narnia"}}, \
    {"⚔️ 🏰 🏹", "braveheart", {"gladiator", "spartacus", "kingdom_of_heaven"}}, \
    {"🧙‍♂️ 🏞️ 🌋", "hobbit", {"lord_of_rings", "game_of_thrones", "the_witcher"}}, \
    {"🎮 🏆 🕹️", "ready_player_one", {"tron", "matrix", "jumanji"}}, \
    {"🚢 🧭 🗺️", "castaway", {"life_of_pi", "the_beach", "tom_hanks_movies"}}, \
    {"🏙️ 🦸‍♂️ 💀", "deadpool", {"spiderman", "batman", "iron_man"}}, \
    {"🏁 🚗 🏎️", "rush", {"le_mans", "ford_v_ferrari", "days_of_thunder"}}, \
    {"🎥 🏆 🏅", "la_la_land", {"the_artist", "moulin_rouge", "chicago"}}, \
    {"🍂 🍃 🦌", "the_revenant", {"blood_diamond", "apocalypto", "the_road"}}, \
    {"🌍 🧑‍🚀 🚀", "gravity", {"interstellar", "apollo_13", "martian"}}, \
    {"🎭 🏆 🥂", "the_social_network", {"steve_jobs", "the_king_speech", "moneyball"}}, \
    {"🇺🇸 ⚽ 🏈", "united_states", {"canada", "mexico", "brazil"}}, \
    {"🇮🇹 🍝 🏛️", "italy", {"france", "spain", "greece"}}, \
    {"🇧🇷 ⚽ 🏖️", "brazil", {"argentina", "colombia", "peru"}}, \
    {"🇦🇷 🐄 🍷", "argentina", {"chile", "uruguay", "paraguay"}}, \
    {"🇬🇧 🍻 🏰", "united_kingdom", {"france", "ireland", "scotland"}}, \
    {"🇩🇪 🍺 🚗", "germany", {"austria", "switzerland", "poland"}}, \
    {"🇪🇸 🏖️ 🍷", "spain", {"portugal", "italy", "france"}}, \
    {"🇮🇳 🕌 🍛", "india", {"pakistan", "nepal", "bangladesh"}}, \
    {"🇯🇵 🍣 🗻", "japan", {"china", "south_korea", "taiwan"}}, \
    {"🇷🇺 🏒 🏰", "russia", {"ukraine", "belarus", "kazakhstan"}}, \
    {"🇮🇪 🥔 🍺", "ireland", {"united_kingdom", "scotland", "wales"}}, \
    {"🇦🇺 🦘 🏄‍♂️", "australia", {"new_zealand", "fiji", "tonga"}}, \
    {"🇨🇦 🍁 🏒", "canada", {"united_states", "mexico", "greenland"}}, \
    {"🛕 🕉️ 🕊️", "india_religion", {"islam", "christianity", "buddhism"}}, \
    {"✝️ 📖 ⛪", "christianity", {"islam", "judaism", "hinduism"}}, \
    {"🔯 🕍 ⛽", "judaism", {"christianity", "islam", "buddhism"}}, \
    {"🌍 💵 🏦", "global_economy", {"china_economy", "us_economy", "india_economy"}}, \
    {"💶 🇨🇭 🏦", "swiss_economy", {"german_economy", "french_economy", "austrian_economy"}}, \
    {"💷 🇬🇧 💰", "british_economy", {"us_economy", "eurozone", "indian_economy"}}, \
    {"💵 🇺🇸 🏙️", "us_economy", {"china_economy", "brazil_economy", "japan_economy"}}, \
    {"🇯🇵 💴 🏯", "japan_economy", {"south_korea_economy", "china_economy", "taiwan_economy"}}, \
    {"🇮🇳 ₹ 💵", "india_economy", {"china_economy", "us_economy", "indonesia_economy"}}, \
    {"🇩🇪 € 🏭", "german_economy", {"france_economy", "austria_economy", "switzerland_economy"}}, \
    {"💵 🏙️ 🏗️", "brazil_economy", {"china_economy", "us_economy", "india_economy"}}, \
    {"🍕 🍝 🥖", "italian_food", {"mexican_food", "japanese_food", "chinese_food"}}, \
    {"🍣 🍤 🍙", "japanese_food", {"korean_food", "chinese_food", "thai_food"}}, \
    {"🧙‍♂️ 🏰 ⚔️", "elder_scrolls", {"skyrim", "fallout", "witcher_3"}}, \
    {"🦸‍♂️ 💥 🏙️", "spiderman_ps4", {"batman_arkham", "spiderman_ps5", "iron_man_ps4"}}, \
    {"🚗 💨 🏁", "forza_horizon", {"need_for_speed", "gran_turismo", "dirt_rally"}}, \
    {"🎮 🎲 🕹️", "tetris", {"snake", "pac_man", "pong"}}, \
    {"🦇 🎮 💻", "batman_arkham", {"spiderman_ps4", "god_of_war", "assassins_creed"}}, \
    {"🧟‍♂️ ⚔️ 🔫", "resident_evil", {"dead_rising", "left_for_dead", "the_walking_dead"}}, \
    {"🕹️ 🧙‍♂️ 🏰", "diablo", {"dark_souls", "warcraft", "torchlight"}}, \
    {"👑 ⚔️ 🏰", "age_of_empires", {"civilization", "rome_total_war", "warcraft"}}, \
    {"🧙‍♂️ 🔮 ⚔️", "witcher_3", {"skyrim", "dark_souls", "elden_ring"}}, \
    {"⚔️ 🏰 🏹", "chivalry_2", {"for honor", "mount_and_blade", "conqueror's_blade"}}, \
    {"🚗 🏁 🚙", "grand_theft_auto_v", {"red_dead_redemption_2", "mafia_iii", "watch_dogs_2"}}, \
    {"🐍 🌵 🏝️", "snake", {"pacman", "asteroids", "pong"}}, \
    {"🏎️ 🚗 🏁", "gran_turismo", {"forza_horizon", "need_for_speed", "dirt_rally"}}, \
    {"⚔️ 👑 🏰", "total_war", {"age_of_empires", "civilization", "rome_total_war"}}, \
    {"🧛‍♂️ 🌙 🏰", "castlevania", {"metroid", "hollow_knight", "dark_souls"}}, \
    {"🎮 🏰 🧙‍♂️", "final_fantasy", {"dragon_quest", "chrono_trigger", "tales_of_symphonia"}}, \
    {"👾 🕹️ 🏆", "space_invaders", {"pac_man", "pong", "galaga"}}, \
    {"💣 🏁 🎮", "bomberman", {"dig_dug", "pacman", "asteroids"}}, \
    {"🎮 🏃‍♂️ 🏅", "super_mario_bros", {"sonic_the_hedgehog", "donkey_kong", "mega_man"}}, \
    {"🎮 👾 🏆", "galaga", {"space_invaders", "missile_command", "asteroids"}}, \
    {"🐎 🌄 🤠", "red_dead_redemption_2", {"grand_theft_auto_v", "assassins_creed", "far_cry"}}, \
    {"🧟‍♂️ 🏹 💀", "resident_evil", {"left_for_dead", "the_walking_dead", "dead_rising"}}, \
    {"🗡️ 🏰 🛡️", "assassins_creed", {"red_dead_redemption_2", "far_cry", "watch_dogs"}}, \
    {"🚗 💥 🏙️", "grand_theft_auto_v", {"red_dead_redemption_2", "watch_dogs_2", "mafia_iii"}}, \
    {"🧙‍♂️ ⚔️ 🔮", "the_witcher_3", {"skyrim", "elden_ring", "dark_souls"}}, \
    {"🐴 🏙️ 🏞️", "red_dead_redemption_2", {"grand_theft_auto_v", "mafia_iii", "far_cry"}}, \
    {"🧟‍♂️ 🧠 🔫", "resident_evil", {"left_for_dead", "the_walking_dead", "dead_space"}}, \
    {"🗡️ 🏹 🛡️", "assassins_creed", {"red_dead_redemption_2", "skyrim", "the_witcher_3"}}, \
    {"🚗 💨 💥", "grand_theft_auto_v", {"red_dead_redemption_2", "watch_dogs", "mafia_iii"}}, \
    {"🎩 🧙‍♂️ 🏰", "skyrim", {"fallout", "the_witcher_3", "red_dead_redemption_2"}}, \
    {"🎮 🏞️ 🐎", "red_dead_redemption_2", {"grand_theft_auto_v", "far_cry", "assassins_creed"}}, \
    {"🧟‍♂️ ⚔️ 🔫", "resident_evil", {"dead_rising", "the_last_of_us", "outlast"}}, \
    {"🧙‍♂️ 💀 🏰", "assassins_creed", {"red_dead_redemption_2", "far_cry", "skyrim"}}, \
    {"💥 🏙️ 🚙", "grand_theft_auto_v", {"red_dead_redemption_2", "watch_dogs_2", "mafia_iii"}}, \
    {"🍩 🍔 🍕", "american_food", {"mexican_food", "italian_food", "chinese_food"}}, \
    {"🍜 🥢 🍚", "chinese_food", {"japanese_food", "thai_food", "korean_food"}}, \
    {"🍛 🌶️ 🍲", "indian_food", {"mexican_food", "thai_food", "chinese_food"}}, \
    {"🍔 🍟 🍕", "fast_food", {"american_food", "mexican_food", "italian_food"}}, \
    {"🌮 🌯 🍚", "mexican_food", {"italian_food", "american_food", "japanese_food"}}, \
    {"🥗 🥒 🥑", "vegetarian_food", {"vegan_food", "indian_food", "chinese_food"}}, \
    {"🥩 🍖 🍗", "meat_food", {"vegan_food", "vegetarian_food", "american_food"}}, \
    {"🥨 🍺 🌭", "german_food", {"italian_food", "french_food", "american_food"}}, \
}

#endif