// group_quest:waidi Ⱥ�����񡪡��������

#include <ansi.h>
#include "waidi.h"

void create()
{
        seteuid(getuid());

        if (!select_quest())
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIR "��Ⱥ������" NOR; }

int select_quest()
{
        object *all_user;
        object ob;

        all_user = users();
        all_user = filter_array(all_user,(: $1->query("combat_exp") > 200000 :));
        all_user = filter_array(all_user,(: not_wizard :));
        all = sizeof(users());

        if (all<10) 
                return 0;                       //���̫�٣���ֹ��������
        if (all>80)
                all = 80;

        if (!(place = GROUP_QUEST_D->query_place()))
                return 0;

        if (!(the_nation = GROUP_QUEST_D->query_nation()))
                return 0;

        story = all_story[random(sizeof(all_story))];

        return 1;
}

string create_waidi()
{
        object ob,obj;
        int i,lvl,special;
        string title;

        title = GROUP_QUEST_D->get_title(the_nation,1);
        special = random(all);          //���ѡ��һ����з���һ����ʯ��Ƭ
        for (i = 0;i < all;i ++)
        {
                lvl = random(17) + 1;
                ob = GROUP_QUEST_D->create_npc(the_nation,lvl);
                GROUP_QUEST_D->place_npc(ob,"Ⱥ������",place,lvl);
                ob->set("title",title);
                ob->random_move();
                ob->random_move();
                ob->random_move();
                ob->random_move();
                if (i == special)
                {
                        obj = new(special_stone[random(sizeof(special_stone))]);
                        obj->move(ob);
                }
        }
        GROUP_QUEST_D->set_enemy(all);
        return "��ͽ�Ǹߺ�����������" + filter_color(title) + "���������ǵ�����Ǯ�ƣ�������ɱ������";
}

string jiuming()
{
        int i;
        object npc = 0;
        string npc_dir,the_place;
        string msg;
        string the_file;
        mixed *file;

        the_place = place;
        if (!stringp(npc_dir = place_npcfile[the_place]))
                return "��С���󺰣�������������";

        seteuid(getuid());
        file = get_dir(npc_dir, -1);
        file = filter_array(file,(: $1[1] != -2 :));
        if (! sizeof(file))
                return "��С���󺰣�������������";
        i = 0;
        msg = "";
        while(1)
        {
                i ++;
                if ( i > 20) break;
                the_file = file[random(sizeof(file))][0];
                if (the_file[strlen(the_file) - 2..strlen(the_file) - 1] != ".c")
                        continue;
                if (!objectp(npc = new(npc_dir + the_file)))
                        continue;
                if (!living(npc))
                {
                        destruct(npc);
                        continue;
                } else
                        break;
        }
        if (!npc)
                return "��С���󺰣�������������";

        if (npc->query("gender") == "Ů��" && random(2))
        {
                msg = npc->name() + woman_jiuming[random(sizeof(woman_jiuming))];
                destruct(npc);
        } else
        {
                msg = npc->name() + all_jiuming[random(sizeof(all_jiuming))];
                destruct(npc);
        }
        
        if (!msg || msg == "")
                return "��С���󺰣�������������";
        else
                return msg;
}

mixed query_quest_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg,"place",HIY + place + NOR + WHT);
                msg = replace_string(msg,"the_nation",HIY + the_nation + NOR + WHT);
        }
        return msg;
}

int not_wizard(object ob)
{
        if (wizardp(ob)) return 0;
        return 1;
}

mixed check()
{
        return all_story[random(sizeof(all_story))];
}

