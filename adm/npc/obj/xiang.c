// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// xiang.c 具有当机时候保存玩家物品的箱子

inherit ITEM;
inherit F_SAVE;

int is_container() { return 1; }
int no_limit_amount() { return 1; }
int clean_up() { return 1; }

nosave int load;

string query_save_file()
{
        string id;

        if (! stringp(id = query("owner")) ) return 0;
        return DATA_DIR + "room/" + id + "/" + id;
}

void save_autoload()
{
        object  *inv;
        int     i, amount;
        string  obs;
        mapping autoload;

        autoload = ([ ]);

        inv = all_inventory();

        for (i = 0; i < sizeof(inv); i++)
        {
                reset_eval_cost();
                if (inv[i]->query("unique") ||
                    inv[i]->is_character() ||
                    inv[i]->is_no_clone())
                        continue;

                obs = base_name(inv[i]);
                if (! amount = inv[i]->query_amount())
                        amount = 1;

                if (amount > 9000) amount = 9000;

                autoload[obs] += amount;
        }

        delete("autoload");
        set("autoload", autoload);
}

int save()
{
        int res;
        save_autoload();
        res = ::save();
        return res;
}

object make_inventory(string file)
{
        object ob;

        if (! objectp(ob = new(file)))
                ob = new("/clone/food/xiandan");

        if (ob->query_amount())
                ob->set_amount(1);

        ob->set("startroom", base_name(this_object()));
        ob->move(this_object());
        return ob;
}

void restore_autoload()
{
        mapping ob_list, ob;
        string *list;
        int i, j;
        object obj;

        set("no_clean_up", 1);

        if (! mapp(ob_list = query("autoload")))
                return;

        list = keys(ob_list);

        if (sizeof(list) < 1 || sizeof(list) > 200)
                return;

        ob = allocate_mapping(sizeof(ob_list));

        for (i = 0; i < sizeof(list); i++)
        {
                reset_eval_cost();
                // Allocate an array if we have multiple same object specified.
                if (undefinedp(ob[list[i]]) &&
                    intp(ob_list[list[i]]) &&
                    ob_list[list[i]] > 1)
                {
                        if (ob_list[list[i]] > 9000)
                                ob_list[list[i]] = 9000;
                        ob[list[i]] = allocate(ob_list[list[i]]);
                }

                switch (ob_list[list[i]])
                {
                case 1:
                        if (! ob[list[i]]) ob[list[i]] = make_inventory(list[i]);

                        if (environment(ob[list[i]]) != this_object())
                                destruct(ob[list[i]]);

                        break;

                default:
                        obj = make_inventory(list[i]);
                        if (obj->query_amount())
                        {
                                obj->set_amount(ob_list[list[i]]);
                                obj->move(this_object());
                                if (environment(obj) != this_object())
                                        destruct(obj);
                        } else
                        {
                                destruct(obj);
                                for (j = 0; j < ob_list[list[i]]; j++)
                                {
                                        // If the object is gone, make another one.
                                        reset_eval_cost();
                                        if (! objectp(ob[list[i]][j]))
                                        {
                                                ob[list[i]][j] = make_inventory(list[i]);
                                                continue;
                                        }
                                        if (environment(ob[list[i]][j]) != this_object())
                                                destruct(ob[list[i]][j]);
                                }
                        }
                }
        }
        delete("autoload");
        save();
}

void create()
{
        set_name("聚宝箱", ({ "ju baoxiang", "baoxiang", "xiang" }));
        set_weight(1000);
        set_max_encumbrance(10000000);
        set("owner", "lonely");
        if (clonep())
                set_default_object(__FILE__);
        else {
                set_max_encumbrance(100000);
                set("long", "一个四周边缘镶嵌着珍珠玛瑙的箱子，好像可以将东西放在里面。\n");
                set("value", 100);
                set("unit", "个");
                set("no_get", 1);
        }
        setup();
}

/*
void init()
{
        string owner;
        object env;

        if (! load)
        {
                env = environment(this_object());
                owner = (string)env->query("room_owner_id");
                set("owner", owner);
                restore();
                restore_autoload();
                load = 1;
        }
}
*/

int remove()
{
        save();
}
