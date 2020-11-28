// chard.c
// From ES2
// Modified by Xiang@XKX
// Updated by Doing

// #pragma optimize
// #pragma save_binary

#define HUMAN_RACE "/adm/daemons/race/human"
#define MONSTER_RACE "/adm/daemons/race/monster"
#define BEAST_RACE "/adm/daemons/race/beast"
#define STOCK_RACE "/adm/daemons/race/stock"
#define BIRD_RACE "/adm/daemons/race/bird"
#define FISH_RACE "/adm/daemons/race/fish"
#define SNAKE_RACE "/adm/daemons/race/snake"
#define INSECT_RACE "/adm/daemons/race/insect"

void create() { seteuid(getuid()); }

void setup_char(object ob)
{
        string race;
        mapping my;

        if (! stringp(race = ob->query("race")))
        {
                race = "����";
                ob->set("race", "����");
        }

        my = ob->query_entire_dbase();
        if (userp(ob))
        {
                // avoid excess neili
                if ((int)my["max_neili"] > (int)ob->query_neili_limit())
                        my["max_neili"] = (int)ob->query_neili_limit();

                // avoid excess jingli
                if ((int)my["max_jingli"] > (int)ob->query_jingli_limit())
                        my["max_jingli"] = (int)ob->query_jingli_limit();
        }

        switch(race) {
                case "����":
                        HUMAN_RACE->setup_human(ob);
                        break;
                case "��ħ":
                        MONSTER_RACE->setup_monster(ob);
                        break;
                case "Ұ��":
                        BEAST_RACE->setup_beast(ob);
                        break;
                case "����":
                        STOCK_RACE->setup_stock(ob);
                        break;
                case "����":
                        BIRD_RACE->setup_bird(ob);
                        break;
                case "����":
                        FISH_RACE->setup_fish(ob);
                        break;
                case "����":
                        SNAKE_RACE->setup_snake(ob);
                        break;
                case "����":
                        INSECT_RACE->setup_insect(ob);
                        break;
                default:
                        error("Chard: undefined race " + race + ".\n");
        }

        if (undefinedp(my["jing"]))
                my["jing"] = my["max_jing"];
        if (undefinedp(my["qi"]))
                my["qi"] = my["max_qi"];

        if (undefinedp(my["eff_jing"]) || my["eff_jing"] > my["max_jing"])
                my["eff_jing"] = my["max_jing"];
        if (undefinedp(my["eff_qi"]) || my["eff_qi"] > my["max_qi"])
                my["eff_qi"] = my["max_qi"];

        if (undefinedp(my["shen_type"])) my["shen_type"] = 0;

        if (undefinedp(my["shen"]))
        {
                if (userp(ob))
                        my["shen"] = 0;
                else
                        my["shen"] = my["shen_type"] * my["combat_exp"] / 10;
        }

        if (! ob->query_max_encumbrance())
                ob->set_max_encumbrance(ob->query_str() * 5000);

        ob->reset_action();
}

varargs object make_corpse(object victim, object killer)
{
        int i;
        object corpse, *inv;

        if (victim->is_ghost())
        {
                inv = all_inventory(victim);
                inv->owner_is_killed(killer);
                inv -= ({ 0 });
                i = sizeof(inv);
                while(i--) inv[i]->move(environment(victim));
                return 0;
        }

        corpse = new(CORPSE_OB);
        //add by rama ��corpse��ǰ��¼��
        corpse->set_name( victim->name(1) + "��ʬ��", ({ "corpse" }) );
        corpse->set("long", victim->long()
                + "Ȼ����" + gender_pronoun(victim->query("gender"))
                + "�Ѿ����ˣ�ֻʣ��һ��ʬ�徲�����������\n");
        corpse->set("age", victim->query("age"));
        corpse->set("gender", victim->query("gender"));
        corpse->set("victim_name", victim->name(1));
        corpse->set("combat_exp", victim->query("combat_exp"));
        corpse->set_weight( victim->query_weight() );
        corpse->set_max_encumbrance( victim->query_max_encumbrance() );
        corpse->set("my_killer", victim->query_temp("my_killer"));

        corpse->make_corpse(victim, killer);
        return corpse;
}
